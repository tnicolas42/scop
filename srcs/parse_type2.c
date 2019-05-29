/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:04:24 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 14:05:37 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static int	obj_texture_1(t_obj obj_info, char *arg, t_obj_texture_lst *new,
uint64_t i_linenb)
{
	float				nb;
	int					i;
	int					line_nb;

	i = ft_get2arg(i_linenb, 0);
	line_nb = ft_get2arg(i_linenb, 1);
	if (arg == NULL)
	{
		if (i < 3)
		{
			free(new);
			return (ft_error(false, "line %d: %s (%s) not enouth args (need "
				"2 or 3)\n", line_nb, obj_info.name, obj_info.description));
		}
		else
			return (SUCCESS);
	}
	nb = atof(arg);
	if (i == 1)
		new->t.position.x = nb;
	else if (i == 2)
		new->t.position.y = nb;
	else if (i == 3)
		new->t.position.z = nb;
	return (SUCCESS);
}

int			obj_texture(t_obj obj_info, char **args, int line_nb)
{
	t_obj_texture_lst	*new;
	int					i;

	if (!(new = malloc(sizeof(t_obj_texture_lst))))
		ft_error(true, NULL);
	i = 0;
	while (++i < 4)
	{
		if (obj_texture_1(obj_info, args[i], new, ft_2arg(i, line_nb)) == ERROR)
			return (ERROR);
		if (args[i] == NULL && i >= 3)
			break ;
	}
	if (args[i] != 0 && ft_free(1, new))
	{
		return (ft_error(false, "line %d: %s (%s) too many arguments (need 2 "
			"or 3)\n", line_nb, obj_info.name, obj_info.description));
	}
	if (g_a->object.objects->groups->textures)
		new->t.id = g_a->object.objects->groups->textures->t.id + 1;
	else
		new->t.id = 1;
	new->next = g_a->object.objects->groups->textures;
	g_a->object.objects->groups->textures = new;
	return (SUCCESS);
}

static int	obj_normal_1(t_obj obj_info, char *arg, t_obj_normal_lst *new,
uint64_t i_linenb)
{
	float				nb;
	int					i;
	int					line_nb;

	i = ft_get2arg(i_linenb, 0);
	line_nb = ft_get2arg(i_linenb, 1);
	if (arg == NULL)
	{
		free(new);
		return (ft_error(false, "line %d: %s (%s) not enouth arguments (need 3)"
			"\n", line_nb, obj_info.name, obj_info.description));
	}
	nb = atof(arg);
	if (i == 1)
		new->vn.position.x = nb;
	else if (i == 2)
		new->vn.position.y = nb;
	else if (i == 3)
		new->vn.position.z = nb;
	return (SUCCESS);
}

int			obj_normal(t_obj obj_info, char **args, int line_nb)
{
	t_obj_normal_lst	*new;
	int					i;

	if (!(new = malloc(sizeof(t_obj_normal_lst))))
		ft_error(true, NULL);
	i = 1;
	while (i < 4)
	{
		if (obj_normal_1(obj_info, args[i], new, ft_2arg(i, line_nb)) == ERROR)
			return (ERROR);
		i++;
	}
	if (args[i] != 0)
	{
		free(new);
		return (ft_error(false, "line %d: %s (%s) too many arguments (need 3)"
			"\n", line_nb, obj_info.name, obj_info.description));
	}
	if (g_a->object.objects->groups->normales)
		new->vn.id = g_a->object.objects->groups->normales->vn.id + 1;
	else
		new->vn.id = 1;
	new->next = g_a->object.objects->groups->normales;
	g_a->object.objects->groups->normales = new;
	return (SUCCESS);
}
