/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:49:57 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 14:05:38 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

int			obj_not_implemented(t_obj obj_info, char **args, int line_nb)
{
	(void)args;
	(void)line_nb;
	if (PRINT_NOT_IMPLEMENTED)
		ft_printf("line %d: %s (%s) is not implemented\n",
			line_nb, obj_info.name, obj_info.description);
	return (SUCCESS);
}

int			obj_comment(t_obj obj_info, char **args, int line_nb)
{
	(void)obj_info;
	(void)args;
	(void)line_nb;
	return (SUCCESS);
}

static int	obj_verticle_1(t_obj obj_info, char *arg, t_obj_verticle_lst *new,
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
		return (ft_error(false, "line %d: %s (%s) not enouth arguments (need"
			" 3)\n", line_nb, obj_info.name, obj_info.description));
	}
	nb = atof(arg);
	if (i == 1)
		new->v.position.x = nb;
	else if (i == 2)
		new->v.position.y = nb;
	else if (i == 3)
		new->v.position.z = nb;
	return (SUCCESS);
}

int			obj_verticle(t_obj obj_info, char **args, int line_nb)
{
	t_obj_verticle_lst	*new;
	int					i;

	if (!(new = malloc(sizeof(t_obj_verticle_lst))))
		ft_error(true, NULL);
	i = 0;
	while (++i < 4)
	{
		if (obj_verticle_1(obj_info, args[i], new, ft_2arg(i, line_nb)) ==
		ERROR)
			return (ERROR);
	}
	if (args[i] != 0)
	{
		free(new);
		return (ft_error(false, "line %d: %s (%s) too many arguments (need"
			" 3)\n", line_nb, obj_info.name, obj_info.description));
	}
	if (g_a->object.objects->groups->verticles)
		new->v.id = g_a->object.objects->groups->verticles->v.id + 1;
	else
		new->v.id = 1;
	new->next = g_a->object.objects->groups->verticles;
	g_a->object.objects->groups->verticles = new;
	return (SUCCESS);
}
