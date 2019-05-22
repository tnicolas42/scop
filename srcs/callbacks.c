/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:34:44 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/22 19:38:36 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	error_callback(int error, const char *description)
{
	(void)error;
	ft_dprintf(STDERR_FILENO, "Error: %s\n", description);
}

void	cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
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

void	mouse_button_callback(GLFWwindow *window, int button, int action,
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

void	scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	double zoom_add;

	(void)window;
	(void)xoffset;
	zoom_add = yoffset * ZOOM_SPEED * g_a->transform.scale.x;
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

void	key_callback(GLFWwindow *window, int key, int scancode, int action)
{
	int		revert;

	revert = (g_a->key_mouse.is_shift_pressed) ? -1 : 1;
	(void)window;
	(void)scancode;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if ((key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) ||
			(key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_PRESS))
		g_a->key_mouse.is_ctrl_pressed = true;
	if ((key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) ||
			(key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_RELEASE))
		g_a->key_mouse.is_ctrl_pressed = false;
	if ((key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) ||
			(key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS))
		g_a->key_mouse.is_shift_pressed = true;
	if ((key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) ||
			(key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_RELEASE))
		g_a->key_mouse.is_shift_pressed = false;
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		reset_transform(&(g_a->transform));
	if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (g_a->key_mouse.is_ctrl_pressed)
			g_a->transform.rotation.x += ROTATE_SPEED_KEYBOARD * revert;
		else
			g_a->transform.position.x += MOVING_SPEED_KEYBOARD * g_a->object.description.max_size * revert;
	}
	if (key == GLFW_KEY_Y && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (g_a->key_mouse.is_ctrl_pressed)
			g_a->transform.rotation.y += ROTATE_SPEED_KEYBOARD * revert;
		else
			g_a->transform.position.y += MOVING_SPEED_KEYBOARD * g_a->object.description.max_size * revert;
	}
	if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (g_a->key_mouse.is_ctrl_pressed)
			g_a->transform.rotation.z += ROTATE_SPEED_KEYBOARD * revert;
		else
			g_a->transform.position.z += MOVING_SPEED_KEYBOARD * g_a->object.description.max_size * revert;
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		g_a->draw_verticles = !g_a->draw_verticles;
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		g_a->draw_faces = !g_a->draw_faces;
}
