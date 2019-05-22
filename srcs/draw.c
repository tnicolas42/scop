/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:19:42 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/22 15:39:00 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	draw_verticles(void)
{
	t_obj_verticle_lst	*tmp;
	t_vector3			center;

	center = g_a->object.description.center;
	tmp = g_a->object.objects->groups->verticles;
	while (tmp)
	{
		glBegin(GL_POINTS);
		glColor3ub(255, 255, 255);
		glVertex3d(tmp->v.position.x - center.x, tmp->v.position.y - center.y, tmp->v.position.z - center.z);
		glEnd();
		tmp = tmp->next;
	}
}

static void	draw_faces(void)
{
	t_obj_face			*tmp;
	t_obj_verticle_lst	*verticle_tmp;
	t_vector3			center;

	center = g_a->object.description.center;
	tmp = g_a->object.objects->groups->faces;
	while (tmp)
	{
		glBegin(GL_POLYGON);
		glColor3ub(255, 255, 255);
		verticle_tmp = tmp->verticles;
		while (verticle_tmp)
		{
			glVertex3d(verticle_tmp->v.position.x - center.x,
				verticle_tmp->v.position.y - center.y,
				verticle_tmp->v.position.z - center.z);
			verticle_tmp = verticle_tmp->next;
		}
		glEnd();
		tmp = tmp->next;
	}
}

void		draw(void)
{
	// draw_verticles();
	draw_faces();
}
