/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:19:42 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/23 17:40:20 by tnicolas         ###   ########.fr       */
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

static void	draw_faces(t_obj_group *group)
{
	t_obj_face			*tmp;
	t_obj_verticle_lst	*verticle_tmp;
	t_obj_texture_lst	*texture_tmp;
	t_obj_normal_lst	*normal_tmp;
	t_vector3			center;

	if (group->used_texture_bmp == NULL)
		glBindTexture(GL_TEXTURE_2D, 0);
	else
		glBindTexture(GL_TEXTURE_2D, group->used_texture_bmp->t.gl_texture);
	center = g_a->object.description.center;
	tmp = group->faces;
	while (tmp)
	{
		glBegin(GL_POLYGON);
		glColor3ub(100, 100, 100);
		verticle_tmp = tmp->verticles;
		texture_tmp = tmp->texture_coord;
		normal_tmp = tmp->normales;
		while (verticle_tmp && texture_tmp)
		{
			if (normal_tmp->vn.id > 0)
				glNormal3d(normal_tmp->vn.position.x,
					normal_tmp->vn.position.y, normal_tmp->vn.position.z);
			glTexCoord2d(texture_tmp->t.position.x, texture_tmp->t.position.y);
			glVertex3d(verticle_tmp->v.position.x - center.x,
				verticle_tmp->v.position.y - center.y,
				verticle_tmp->v.position.z - center.z);
			verticle_tmp = verticle_tmp->next;
			texture_tmp = texture_tmp->next;
			normal_tmp = normal_tmp->next;
		}
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
