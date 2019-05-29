/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:16 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 14:02:25 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		reset_transform(t_transform *transform)
{
	transform->position.x = 0;
	transform->position.y = 0;
	transform->position.z = 0;
	transform->rotation.x = 90;
	transform->rotation.y = -90;
	transform->rotation.z = 0;
	transform->scale.x = 1;
	transform->scale.y = 1;
	transform->scale.z = 1;
}

void		set_camera_pos(void)
{
	g_a->cam.position.x = 0;
	g_a->cam.position.y = -g_a->object.description.max_size * CAMERA_POS_Y;
	g_a->cam.position.z = 0;
	g_a->cam.target.x = 0;
	g_a->cam.target.y = 0;
	g_a->cam.target.z = 0;
	g_a->cam.vert_vector.x = 0;
	g_a->cam.vert_vector.y = 0;
	g_a->cam.vert_vector.z = 1;
	g_a->cam.near = g_a->object.description.max_size * CAMERA_NEAR;
	g_a->cam.far = g_a->object.description.max_size * CAMERA_FAR;
}

static void	init_1(void)
{
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(g_a->window, (void(*)(GLFWwindow *, int, int, int, int))
		(size_t)&key_callback);
	glfwSetScrollCallback(g_a->window, scroll_callback);
	glfwSetMouseButtonCallback(g_a->window, mouse_button_callback);
	glfwSetCursorPosCallback(g_a->window, cursor_position_callback);
	glEnable(GL_TEXTURE_2D);
	load_bmp("textures/metal.bmp", false);
	load_bmp("textures/tiles.bmp", false);
	load_bmp("textures/unicorn.bmp", false);
	load_bmp("textures/default.bmp", true);
	if (ENABLE_SHADER)
	{
		glEnable(GL_LIGHTING);
		init_shader();
	}
}

void		init(void)
{
	init_a();
	srand(time(NULL));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!glfwInit())
		ft_error(true, "Error when loading GLFW\n");
	g_a->window = glfwCreateWindow(SC_WIDTH, SC_HEIGHT, "scop", NULL, NULL);
	if (!g_a->window)
		ft_error(true, "Error when loading GLFW\n");
	glfwMakeContextCurrent(g_a->window);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	init_1();
}
