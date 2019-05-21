/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:16 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/21 17:01:43 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		reset_transform(void)
{
	g_a->transform.position.x = 0;
	g_a->transform.position.y = 0;
	g_a->transform.position.z = 0;
	g_a->transform.rotation.x = 0;
	g_a->transform.rotation.y = 0;
	g_a->transform.rotation.z = 0;
	g_a->transform.scale.x = 1;
	g_a->transform.scale.y = 1;
	g_a->transform.scale.z = 1;
}

void		set_camera_pos(void)
{
	g_a->cam.position.x = 0;
	g_a->cam.position.y = -g_a->description.max_size * CAMERA_POS_Y;
	g_a->cam.position.z = 0;
	g_a->cam.target.x = 0;
	g_a->cam.target.y = 0;
	g_a->cam.target.z = 0;
	g_a->cam.vert_vector.x = 0;
	g_a->cam.vert_vector.y = 0;
	g_a->cam.vert_vector.z = 1;
	g_a->cam.near = g_a->description.max_size / CAMERA_NEAR;
	g_a->cam.far = g_a->description.max_size * CAMERA_FAR;
}

static void	init_a(void)
{
	if (g_a == NULL)
		if (!(g_a = malloc(sizeof(t_a))))
			exit(1);
	g_a->key_mouse.is_ctrl_pressed = false;
	g_a->key_mouse.is_mouse_left_pressed = false;
	g_a->key_mouse.is_mouse_right_pressed = false;
	g_a->key_mouse.mouse_x = -1;
	g_a->key_mouse.mouse_y = -1;
	g_a->description.size.x = 0;
	g_a->description.size.y = 0;
	g_a->description.size.z = 0;
	set_camera_pos();
	reset_transform();
}

void		init(void)
{
	init_a();
	if (!glfwInit())
	{
		ft_putstr("Error when loading GLFW\n");
		exit(1);
	}
	g_a->window = glfwCreateWindow(SC_WIDTH, SC_HEIGHT, "scop", NULL, NULL);
	if (!g_a->window)
	{
		ft_putstr("Error when loading GLFW\n");
		exit(1);
	}
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(g_a->window, (void(*)(GLFWwindow *, int, int, int, int))
		(size_t)&key_callback);
	glfwSetScrollCallback(g_a->window, scroll_callback);
	glfwSetMouseButtonCallback(g_a->window, mouse_button_callback);
	glfwSetCursorPosCallback(g_a->window, cursor_position_callback);
	glfwMakeContextCurrent(g_a->window);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
}

void		quit(void)
{
	glfwDestroyWindow(g_a->window);
	glfwTerminate();
	free(g_a);
}
