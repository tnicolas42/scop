/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:00:18 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 14:02:56 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	init_object_1(void)
{
	g_a->object.objects->name = NULL;
	g_a->object.objects->next = NULL;
	if (!(g_a->object.objects->groups = malloc(sizeof(t_obj_group))))
		ft_error(true, NULL);
	g_a->object.objects->groups->name = NULL;
	g_a->object.objects->groups->next = NULL;
	g_a->object.objects->groups->verticles = NULL;
	g_a->object.objects->groups->textures = NULL;
	g_a->object.objects->groups->normales = NULL;
	g_a->object.objects->groups->textures_bmp = NULL;
	g_a->object.objects->groups->used_texture_bmp = NULL;
	g_a->object.objects->groups->faces = NULL;
	g_a->object.objects->groups->transition_state = T_UP;
	g_a->object.objects->groups->transition_val = 0;
	g_a->object.material.ambient.x = MATERIAL_AMBIENT_R;
	g_a->object.material.ambient.y = MATERIAL_AMBIENT_G;
	g_a->object.material.ambient.z = MATERIAL_AMBIENT_B;
	g_a->object.material.diffuse.x = MATERIAL_DIFFUSE_R;
	g_a->object.material.diffuse.y = MATERIAL_DIFFUSE_G;
	g_a->object.material.diffuse.z = MATERIAL_DIFFUSE_B;
	g_a->object.material.specular.x = MATERIAL_SPECULAR_R;
	g_a->object.material.specular.y = MATERIAL_SPECULAR_G;
	g_a->object.material.specular.z = MATERIAL_SPECULAR_B;
	g_a->object.material.shininess = MATERIAL_SHININESS;
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
		ft_error(true, NULL);
	init_object_1();
}

void		init_a(void)
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
	g_a->draw_verticles = DRAW_VERTICLES;
	g_a->draw_faces = DRAW_FACES;
	g_a->is_auto_moving = AUTO_MOVING;
	init_object();
	set_camera_pos();
	reset_transform(&(g_a->transform));
}
