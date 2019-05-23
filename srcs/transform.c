/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:24:30 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/22 19:42:14 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	move_object(double delta_x, double delta_y)
{
	if (g_a->key_mouse.is_mouse_left_pressed && !g_a->key_mouse.is_ctrl_pressed)
	{
		g_a->transform.position.x += -delta_x * MOVING_SPEED_MOUSE * g_a->object.description.max_size;
		g_a->transform.position.z += delta_y * MOVING_SPEED_MOUSE * g_a->object.description.max_size;
	}
	if ((g_a->key_mouse.is_mouse_left_pressed && g_a->key_mouse.is_ctrl_pressed)
	|| (g_a->key_mouse.is_mouse_right_pressed))
	{
		g_a->transform.rotation.x += -delta_y * ROTATE_SPEED_MOUSE;
		g_a->transform.rotation.y += -delta_x * ROTATE_SPEED_MOUSE;
	}
}

void	zoom_object(double offset)
{
	double zoom_add;

	zoom_add = offset * g_a->transform.scale.x;
	if (g_a->transform.scale.x + zoom_add < ZOOM_MIN)
		g_a->transform.scale.x = ZOOM_MIN;
	else if (g_a->transform.scale.x + zoom_add > ZOOM_MAX)
		g_a->transform.scale.x = ZOOM_MAX;
	else
		g_a->transform.scale.x += zoom_add;
	if (g_a->transform.scale.y + zoom_add < ZOOM_MIN)
		g_a->transform.scale.y = ZOOM_MIN;
	else if (g_a->transform.scale.y + zoom_add > ZOOM_MAX)
		g_a->transform.scale.y = ZOOM_MAX;
	else
		g_a->transform.scale.y += zoom_add;
	if (g_a->transform.scale.z + zoom_add < ZOOM_MIN)
		g_a->transform.scale.z = ZOOM_MIN;
	else if (g_a->transform.scale.z + zoom_add > ZOOM_MAX)
		g_a->transform.scale.z = ZOOM_MAX;
	else
		g_a->transform.scale.z += zoom_add;
}

void	transform(void)
{
	if (g_a->is_auto_moving)
		g_a->transform.rotation.y += AUTO_MOVING_SPEED;
	glTranslated(g_a->transform.position.x,
		g_a->transform.position.y,
		g_a->transform.position.z);
	glRotated(g_a->transform.rotation.x, 1, 0, 0);
	glRotated(g_a->transform.rotation.y, 0, 1, 0);
	glRotated(g_a->transform.rotation.z, 0, 0, 1);
	glScaled(g_a->transform.scale.x,
		g_a->transform.scale.y,
		g_a->transform.scale.z);
}

void	set_camera(float ratio)
{
	set_camera_pos();
	glMatrixMode(GL_PROJECTION);
	gluPerspective(70, ratio, g_a->cam.near, g_a->cam.far);
	gluLookAt(g_a->cam.position.x, g_a->cam.position.y, g_a->cam.position.z,
		g_a->cam.target.x, g_a->cam.target.y, g_a->cam.target.z,
		g_a->cam.vert_vector.x, g_a->cam.vert_vector.y, g_a->cam.vert_vector.z);
}
