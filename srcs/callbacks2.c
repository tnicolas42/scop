/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:56:16 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 13:57:59 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		error_callback(int error, const char *description)
{
	(void)error;
	ft_error(true, "Error: %s\n", description);
}

void		cursor_position_callback(GLFWwindow *window, double xpos,
	double ypos)
{
	double	delta_x;
	double	delta_y;

	(void)window;
	if (g_a->key_mouse.mouse_x == -1 || g_a->key_mouse.mouse_y == -1)
	{
		delta_x = 0;
		delta_y = 0;
	}
	else
	{
		delta_x = g_a->key_mouse.mouse_x - xpos;
		delta_y = g_a->key_mouse.mouse_y - ypos;
	}
	g_a->key_mouse.mouse_x = xpos;
	g_a->key_mouse.mouse_y = ypos;
	move_object(delta_x, delta_y);
}

void		mouse_button_callback(GLFWwindow *window, int button, int action,
			int mods)
{
	(void)window;
	(void)mods;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		g_a->key_mouse.is_mouse_left_pressed = true;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		g_a->key_mouse.is_mouse_left_pressed = false;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		g_a->key_mouse.is_mouse_right_pressed = true;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		g_a->key_mouse.is_mouse_right_pressed = false;
}

void		scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	(void)window;
	(void)xoffset;
	zoom_object(yoffset * ZOOM_SPEED_MOUSE);
}
