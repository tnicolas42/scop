/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:50:25 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/23 16:37:37 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_obj_verticle_lst	*get_verticle_by_id(int id)
{
	t_obj_verticle_lst	*verticle_tmp;

	verticle_tmp = g_a->object.objects->groups->verticles;
	if (id > verticle_tmp->v.id || id < 1)
		return (NULL);
	while (verticle_tmp->v.id > id)
		verticle_tmp = verticle_tmp->next;
	return verticle_tmp;
}

t_obj_texture_lst	*get_texture_by_id(int id)
{
	t_obj_texture_lst	*texture_tmp;

	texture_tmp = g_a->object.objects->groups->textures;
	if (id > texture_tmp->t.id || id < 1)
		return (NULL);
	while (texture_tmp->t.id > id)
		texture_tmp = texture_tmp->next;
	return texture_tmp;
}

t_obj_normal_lst	*get_normal_by_id(int id)
{
	t_obj_normal_lst	*tmp;

	tmp = g_a->object.objects->groups->normales;
	if (id > tmp->vn.id || id < 1)
		return (NULL);
	while (tmp->vn.id > id)
		tmp = tmp->next;
	return tmp;
}
