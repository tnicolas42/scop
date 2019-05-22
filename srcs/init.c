/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:16 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/22 16:00:43 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		reset_transform(t_transform *transform)
{
	transform->position.x = 0;
	transform->position.y = 0;
	transform->position.z = 0;
	transform->rotation.x = 0;
	transform->rotation.y = 0;
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
	g_a->cam.near = g_a->object.description.max_size / CAMERA_NEAR;
	g_a->cam.far = g_a->object.description.max_size * CAMERA_FAR;
}

static void	init_object(void)
{
	g_a->object.description.size.x = 0;
	g_a->object.description.size.y = 0;
	g_a->object.description.size.z = 0;
	g_a->object.description.min.x = 0;
	g_a->object.description.min.y = 0;
	g_a->object.description.min.z = 0;
	g_a->object.description.max.x = 0;
	g_a->object.description.max.y = 0;
	g_a->object.description.max.z = 0;
	g_a->object.description.center.x = 0;
	g_a->object.description.center.y = 0;
	g_a->object.description.center.z = 0;
	g_a->object.description.max_size = 0;
	reset_transform(&(g_a->object.transform));
	if (!(g_a->object.objects = malloc(sizeof(t_obj_obj))))
		exit(EXIT_FAILURE);
	g_a->object.objects->name = NULL;
	g_a->object.objects->next = NULL;
	if (!(g_a->object.objects->groups = malloc(sizeof(t_obj_group))))
		exit(EXIT_FAILURE);
	g_a->object.objects->groups->name = NULL;
	g_a->object.objects->groups->next = NULL;
	g_a->object.objects->groups->verticles = NULL;
	g_a->object.objects->groups->faces = NULL;
}

static void	init_a(void)
{
	if (g_a == NULL)
		if (!(g_a = malloc(sizeof(t_a))))
			exit(1);
	g_a->key_mouse.is_ctrl_pressed = false;
	g_a->key_mouse.is_shift_pressed = false;
	g_a->key_mouse.is_mouse_left_pressed = false;
	g_a->key_mouse.is_mouse_right_pressed = false;
	g_a->key_mouse.mouse_x = -1;
	g_a->key_mouse.mouse_y = -1;
	init_object();
	set_camera_pos();
	reset_transform(&(g_a->transform));
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
