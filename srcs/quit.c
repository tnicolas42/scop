/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:59:13 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 14:00:35 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	free_g_a_element_1(t_obj_group *group, t_obj_face *tmp_face[2],
	t_obj_verticle_lst *tmp_verticle[2], t_obj_texture_lst *tmp_texture[2])
{
	tmp_face[0] = group->faces;
	while (tmp_face[0])
	{
		tmp_verticle[0] = tmp_face[0]->verticles;
		while (tmp_verticle[0])
		{
			tmp_verticle[1] = tmp_verticle[0];
			tmp_verticle[0] = tmp_verticle[0]->next;
			free(tmp_verticle[1]);
		}
		tmp_texture[0] = tmp_face[0]->texture_coord;
		while (tmp_texture[0])
		{
			tmp_texture[1] = tmp_texture[0];
			tmp_texture[0] = tmp_texture[0]->next;
			free(tmp_texture[1]);
		}
		tmp_face[1] = tmp_face[0];
		tmp_face[0] = tmp_face[0]->next;
		free(tmp_face[1]);
	}
}

static void	free_g_a_element_2(t_obj_group *group,
	t_obj_verticle_lst *tmp_verticle[2], t_obj_texture_lst *tmp_texture[2],
	t_bmp_texture_lst *tmp_bmp_texture[2])
{
	tmp_verticle[0] = group->verticles;
	while (tmp_verticle[0])
	{
		tmp_verticle[1] = tmp_verticle[0];
		tmp_verticle[0] = tmp_verticle[0]->next;
		free(tmp_verticle[1]);
	}
	tmp_texture[0] = group->textures;
	while (tmp_texture[0])
	{
		tmp_texture[1] = tmp_texture[0];
		tmp_texture[0] = tmp_texture[0]->next;
		free(tmp_texture[1]);
	}
	tmp_bmp_texture[0] = group->textures_bmp;
	while (tmp_bmp_texture[0])
	{
		tmp_bmp_texture[1] = tmp_bmp_texture[0];
		tmp_bmp_texture[0] = tmp_bmp_texture[0]->next;
		free(tmp_bmp_texture[1]->t.img);
		free(tmp_bmp_texture[1]);
	}
}

static void	free_g_a_element(t_obj_group *group)
{
	t_obj_face			*tmp_face[2];
	t_obj_verticle_lst	*tmp_verticle[2];
	t_obj_texture_lst	*tmp_texture[2];
	t_bmp_texture_lst	*tmp_bmp_texture[2];

	free_g_a_element_1(group, tmp_face, tmp_verticle, tmp_texture);
	free_g_a_element_2(group, tmp_verticle, tmp_texture, tmp_bmp_texture);
}

static void	free_g_a(void)
{
	t_obj_obj			*tmp_obj[2];
	t_obj_group			*tmp_group[2];

	if (g_a == NULL)
		return ;
	tmp_obj[0] = g_a->object.objects;
	while (tmp_obj[0])
	{
		tmp_group[0] = tmp_obj[0]->groups;
		while (tmp_group[0])
		{
			free_g_a_element(tmp_group[0]);
			tmp_group[1] = tmp_group[0];
			tmp_group[0] = tmp_group[0]->next;
			free(tmp_group[1]->name);
			free(tmp_group[1]);
		}
		tmp_obj[1] = tmp_obj[0];
		tmp_obj[0] = tmp_obj[0]->next;
		free(tmp_obj[1]->name);
		free(tmp_obj[1]);
	}
	free(g_a);
}

void		quit(void)
{
	if (g_a == NULL)
		return ;
	glfwDestroyWindow(g_a->window);
	glfwTerminate();
	free_g_a();
}
