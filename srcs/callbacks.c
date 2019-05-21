/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:34:44 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/21 15:36:19 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	error_callback(int error, const char *description)
{
	ft_dprintf(STDERR_FILENO, "Error: %s\n", description);
}

void	cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	double	delta_x;
	double	delta_y;

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

void	mouse_button_callback(GLFWwindow *window, int button, int action,
			int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		g_a->key_mouse.is_mouse_left_pressed = true;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		g_a->key_mouse.is_mouse_left_pressed = false;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		g_a->key_mouse.is_mouse_right_pressed = true;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		g_a->key_mouse.is_mouse_right_pressed = false;
}

void	scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	double zoom_add;

	zoom_add = yoffset * ZOOM_SPEED;
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

void	key_callback(GLFWwindow *window, int key, int scancode, int action,
			int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if ((key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) ||
			(key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_PRESS))
		g_a->key_mouse.is_ctrl_pressed = true;
	else
		g_a->key_mouse.is_ctrl_pressed = false;
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
		g_a->transform.position.x += MOVING_SPEED_KEY;
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
		g_a->transform.position.x -= MOVING_SPEED_KEY;
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
		g_a->transform.position.y += MOVING_SPEED_KEY;
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
		g_a->transform.position.y -= MOVING_SPEED_KEY;
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		reset_transform();
}
