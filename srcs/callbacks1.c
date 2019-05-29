/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:56:08 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 13:56:18 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	key_callback_1(int key, int action, int revert)
{
	if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (g_a->key_mouse.is_ctrl_pressed)
			g_a->transform.rotation.x += ROTATE_SPEED_KEYBOARD * revert;
		else
			g_a->transform.position.x += MOVING_SPEED_KEYBOARD *
				g_a->object.description.max_size * revert;
	}
	if (key == GLFW_KEY_Y && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (g_a->key_mouse.is_ctrl_pressed)
			g_a->transform.rotation.y += ROTATE_SPEED_KEYBOARD * revert;
		else
			g_a->transform.position.y += MOVING_SPEED_KEYBOARD *
				g_a->object.description.max_size * revert;
	}
	if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (g_a->key_mouse.is_ctrl_pressed)
			g_a->transform.rotation.z += ROTATE_SPEED_KEYBOARD * revert;
		else
			g_a->transform.position.z += MOVING_SPEED_KEYBOARD *
				g_a->object.description.max_size * revert;
	}
}

static void	key_callback_2(int key, int action)
{
	if ((key == GLFW_KEY_UP || key == GLFW_KEY_W) &&
	(action == GLFW_PRESS || action == GLFW_REPEAT))
		g_a->transform.position.z += MOVING_SPEED_KEYBOARD *
			g_a->object.description.max_size;
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S) &&
	(action == GLFW_PRESS || action == GLFW_REPEAT))
		g_a->transform.position.z -= MOVING_SPEED_KEYBOARD *
			g_a->object.description.max_size;
	if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_A) &&
	(action == GLFW_PRESS || action == GLFW_REPEAT))
		g_a->transform.position.x -= MOVING_SPEED_KEYBOARD *
			g_a->object.description.max_size;
	if ((key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) &&
	(action == GLFW_PRESS || action == GLFW_REPEAT))
		g_a->transform.position.x += MOVING_SPEED_KEYBOARD *
			g_a->object.description.max_size;
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		g_a->object.objects->groups->transition_state = T_DOWN;
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
		g_a->is_auto_moving = !g_a->is_auto_moving;
}

static void	key_callback_3(int key, int action)
{
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
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		g_a->draw_verticles = !g_a->draw_verticles;
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		g_a->draw_faces = !g_a->draw_faces;
	if ((key == GLFW_KEY_MINUS || key == GLFW_KEY_KP_SUBTRACT) &&
	(action == GLFW_PRESS || action == GLFW_REPEAT))
		zoom_object(-ZOOM_SPEED_KEYBOARD);
	if ((key == GLFW_KEY_EQUAL || key == GLFW_KEY_KP_ADD) &&
	(action == GLFW_PRESS || action == GLFW_REPEAT))
		zoom_object(ZOOM_SPEED_KEYBOARD);
}

void		key_callback(GLFWwindow *window, int key, int scancode, int action)
{
	int		revert;

	(void)scancode;
	revert = (g_a->key_mouse.is_shift_pressed) ? -1 : 1;
	key_callback_1(key, action, revert);
	key_callback_2(key, action);
	key_callback_3(key, action);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
