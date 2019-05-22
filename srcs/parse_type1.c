/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:49:57 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/22 20:40:00 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

int		obj_not_implemented(t_obj obj_info, char **args, int line_nb)
{
	(void)args;
	(void)line_nb;
	ft_printf("line %d: %s (%s) is not implemented\n",
		line_nb, obj_info.name, obj_info.description);
	return (SUCCESS);
}

int		obj_comment(t_obj obj_info, char **args, int line_nb)
{
	(void)obj_info;
	(void)args;
	(void)line_nb;
	return (SUCCESS);
}

int		obj_verticle(t_obj obj_info, char **args, int line_nb)
{
	t_obj_verticle_lst	*new;
	float				nb;
	int					i;

	if (!(new = malloc(sizeof(t_obj_verticle_lst))))
		exit(EXIT_FAILURE);
	i = 1;
	while (i < 4)
	{
		if (args[i] == 0)
		{
			ft_printf("line %d: %s (%s) not enouth arguments (need 3 arguments)\n",
				line_nb, obj_info.name, obj_info.description);
			free(new);
			return (ERROR);
		}
		nb = atof(args[i]);
		if (i == 1)
			new->v.position.x = nb;
		else if (i == 2)
			new->v.position.y = nb;
		else if (i == 3)
			new->v.position.z = nb;
		i++;
	}
	if (args[i] != 0)
	{
		ft_printf("line %d: %s (%s) too many arguments (need 3 arguments)\n",
			line_nb, obj_info.name, obj_info.description);
		free(new);
		return (ERROR);
	}
	if (g_a->object.objects->groups->verticles)
		new->v.id = g_a->object.objects->groups->verticles->v.id + 1;
	else
		new->v.id = 1;
	new->next = g_a->object.objects->groups->verticles;
	g_a->object.objects->groups->verticles = new;
	return (SUCCESS);
}

int		obj_texture(t_obj obj_info, char **args, int line_nb)
{
	t_obj_texture_lst	*new;
	float				nb;
	int					i;

	if (!(new = malloc(sizeof(t_obj_texture_lst))))
		exit(EXIT_FAILURE);
	i = 1;
	while (i < 3)
	{
		if (args[i] == 0)
		{
			ft_printf("line %d: %s (%s) not enouth arguments (need 2 arguments)\n",
				line_nb, obj_info.name, obj_info.description);
			free(new);
			return (ERROR);
		}
		nb = atof(args[i]);
		if (i == 1)
			new->t.position.x = nb;
		else if (i == 2)
			new->t.position.y = nb;
		i++;
	}
	if (args[i] != 0)
	{
		ft_printf("line %d: %s (%s) too many arguments (need 2 arguments)\n",
			line_nb, obj_info.name, obj_info.description);
		free(new);
		return (ERROR);
	}
	if (g_a->object.objects->groups->textures)
		new->t.id = g_a->object.objects->groups->textures->t.id + 1;
	else
		new->t.id = 1;
	new->next = g_a->object.objects->groups->textures;
	g_a->object.objects->groups->textures = new;
	return (SUCCESS);
}

int		obj_faces(t_obj obj_info, char **args, int line_nb)
{
	t_obj_face			*new;
	t_obj_verticle_lst	*verticle_tmp1;
	t_obj_verticle_lst	*verticle_tmp2;
	int					nb;
	char				**data;
	int					i;
	int					j;

	if (!(new = malloc(sizeof(t_obj_face))))
		exit(EXIT_FAILURE);
	new->verticles = NULL;
	i = 1;
	while (args[i] != 0)
	{
		data = ft_strsplit(args[i], '/');
		j = 0;
		while (data[j])
		{
			if (j >= 3)
			{
				ft_printf("line %d: %s (%s) invalid argument (int/int/int) %s\n",
					line_nb, obj_info.name, obj_info.description, args[i]);
				ft_free_tab(1, data);
				free(new);
				return (ERROR);
			}
			nb = ft_atoi(data[j]);
			if (nb == 0)
			{
				ft_printf("line %d: %s (%s) invalid argument %s\n",
					line_nb, obj_info.name, obj_info.description, args[i]);
				ft_free_tab(1, data);
				free(new);
				return (ERROR);
			}
			if (j == 0)
			{
				verticle_tmp1 = g_a->object.objects->groups->verticles;
				if (nb > verticle_tmp1->v.id)
				{
					ft_printf("line %d: %s (%s) verticle id to high (max %d) %s\n",
						line_nb, obj_info.name, obj_info.description, verticle_tmp1->v.id, args[i]);
					ft_free_tab(1, data);
					free(new);
					return (ERROR);
				}
				while (verticle_tmp1->v.id > nb)
					verticle_tmp1 = verticle_tmp1->next;
				if (!(verticle_tmp2 = malloc(sizeof(t_obj_verticle_lst))))
					exit(EXIT_FAILURE);
				verticle_tmp2->v = verticle_tmp1->v;
				verticle_tmp2->next = new->verticles;
			}
			j++;
		}
		if (j < 1)
		{
			ft_printf("line %d: %s (%s) invalid argument (int/int/...) %s\n",
				line_nb, obj_info.name, obj_info.description, args[i]);
			ft_free_tab(1, data);
			free(new);
			return (ERROR);
		}
		new->verticles = verticle_tmp2;

		ft_free_tab(1, data);
		i++;
	}
	if (i < 4)
	{
		ft_printf("line %d: %s (%s) not enouth arguments (at least 3)\n",
			line_nb, obj_info.name, obj_info.description);
		free(new);
		return (ERROR);
	}
	new->next = g_a->object.objects->groups->faces;
	g_a->object.objects->groups->faces = new;
	return (SUCCESS);
}
