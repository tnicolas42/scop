/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tim <tim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:50:25 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/28 17:59:23 by tim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_obj_verticle_lst	*get_verticle_by_id(int id)
{
	t_obj_verticle_lst	*verticle_tmp;

	verticle_tmp = g_a->object.objects->groups->verticles;
	if (g_a->object.objects->groups->verticles == NULL
	|| id > verticle_tmp->v.id || id < 1)
		return (NULL);
	while (verticle_tmp->v.id > id)
		verticle_tmp = verticle_tmp->next;
	return verticle_tmp;
}

t_obj_texture_lst	*get_texture_by_id(int id)
{
	t_obj_texture_lst	*texture_tmp;

	texture_tmp = g_a->object.objects->groups->textures;
	if (g_a->object.objects->groups->textures == NULL
	|| id > texture_tmp->t.id || id < 1)
		return (NULL);
	while (texture_tmp->t.id > id)
		texture_tmp = texture_tmp->next;
	return texture_tmp;
}

t_obj_normal_lst	*get_normal_by_id(int id)
{
	t_obj_normal_lst	*tmp;

	tmp = g_a->object.objects->groups->normales;
	if (g_a->object.objects->groups->normales == NULL
	|| id > tmp->vn.id || id < 1)
		return (NULL);
	while (tmp->vn.id > id)
		tmp = tmp->next;
	return tmp;
}

int					ft_error(bool exit_, char *format, ...)
{
	va_list	ap;
	char	*str;
	int		ret;

	if (format == NULL)
	{
		if (exit_)
			exit(EXIT_FAILURE);
		return (ERROR);
	}
	str = NULL;
	va_start(ap, format);
	if ((ret = ft_vasprintf(&str, format, ap)) == ERROR)
	{
		va_end(ap);
		if (exit_)
			exit(EXIT_FAILURE);
		return (ERROR);
	}
	va_end(ap);
	if (str != NULL)
		if (write(STDERR_FILENO, str, ret) == -1 && ft_free(1, str))
		{
			if (exit_)
				exit(EXIT_FAILURE);
			return (ERROR);
		}
	free(str);
	if (exit_)
		exit(EXIT_FAILURE);
	return (ERROR);
}