/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:19:42 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 11:56:54 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	draw_verticles(t_obj_group *group)
{
	t_obj_verticle_lst	*tmp;
	t_vector3			center;

	center = g_a->object.description.center;
	tmp = group->verticles;
	while (tmp)
	{
		glBegin(GL_POINTS);
		glColor3ub(255, 255, 255);
		glVertex3d(tmp->v.position.x - center.x,
			tmp->v.position.y - center.y,
			tmp->v.position.z - center.z);
		glEnd();
		tmp = tmp->next;
	}
}

static void	set_color(t_obj_group *group)
{
	if (group->transition_state == T_OFF)
		return ;
	else if (group->transition_state == T_DOWN)
	{
		group->transition_val -= TRANSITION_DOWN_SPEED;
		if (group->transition_val < 0)
		{
			group->transition_val = 0;
			group->transition_state = T_UP;
			group->used_texture_bmp = group->used_texture_bmp->next;
			if (group->used_texture_bmp == NULL)
				group->used_texture_bmp = group->textures_bmp;
		}
	}
	else if (group->transition_state == T_UP)
	{
		group->transition_val += TRANSITION_UP_SPEED;
		if (group->transition_val > 255)
		{
			group->transition_val = 255;
			group->transition_state = T_OFF;
		}
	}
}

static void	draw_faces_1(t_obj_group *group, t_obj_face *tmp, t_vector3 center)
{
	t_obj_verticle_lst	*verticle_tmp;
	t_obj_texture_lst	*texture_tmp;
	t_obj_normal_lst	*normal_tmp;

	verticle_tmp = tmp->verticles;
	texture_tmp = tmp->texture_coord;
	normal_tmp = tmp->normales;
	while (verticle_tmp && texture_tmp)
	{
		if (normal_tmp->vn.id > 0)
			glNormal3d(normal_tmp->vn.position.x,
				normal_tmp->vn.position.y, normal_tmp->vn.position.z);
		if (group->used_texture_bmp == NULL ||
		group->used_texture_bmp->t.is_default_tex)
			glColor3ub(ft_min(tmp->color.x, group->transition_val),
				ft_min(tmp->color.y, group->transition_val),
				ft_min(tmp->color.z, group->transition_val));
		glTexCoord2d(texture_tmp->t.position.x, texture_tmp->t.position.y);
		glVertex3d(verticle_tmp->v.position.x - center.x,
			verticle_tmp->v.position.y - center.y,
			verticle_tmp->v.position.z - center.z);
		verticle_tmp = verticle_tmp->next;
		texture_tmp = texture_tmp->next;
		normal_tmp = normal_tmp->next;
	}
}

static void	draw_faces(t_obj_group *group)
{
	t_obj_face			*tmp;
	t_vector3			center;

	if (group->used_texture_bmp == NULL)
		glBindTexture(GL_TEXTURE_2D, 0);
	else
		glBindTexture(GL_TEXTURE_2D, group->used_texture_bmp->t.gl_texture);
	center = g_a->object.description.center;
	tmp = group->faces;
	set_color(group);
	while (tmp)
	{
		glBegin(GL_POLYGON);
		glColor3ub(group->transition_val, group->transition_val,
			group->transition_val);
		draw_faces_1(group, tmp, center);
		glEnd();
		tmp = tmp->next;
	}
}

void		draw(void)
{
	t_obj_obj		*tmp_obj;
	t_obj_group		*tmp_group;

	tmp_obj = g_a->object.objects;
	while (tmp_obj)
	{
		tmp_group = tmp_obj->groups;
		while (tmp_group)
		{
			if (g_a->draw_faces == true)
				draw_faces(tmp_group);
			if (g_a->draw_verticles == true)
				draw_verticles(tmp_group);
			tmp_group = tmp_group->next;
		}
		tmp_obj = tmp_obj->next;
	}
}
