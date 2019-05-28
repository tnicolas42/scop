/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tim <tim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:49:57 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/28 18:47:53 by tim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

int		obj_not_implemented(t_obj obj_info, char **args, int line_nb)
{
	(void)args;
	(void)line_nb;
	if (PRINT_NOT_IMPLEMENTED)
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

static int obj_verticle_1(t_obj obj_info, char *arg, t_obj_verticle_lst *new,
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
		return ft_error(false, "line %d: %s (%s) not enouth arguments (need"
			" 3)\n", line_nb, obj_info.name, obj_info.description);
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

int		obj_verticle(t_obj obj_info, char **args, int line_nb)
{
	t_obj_verticle_lst	*new;
	int					i;

	if (!(new = malloc(sizeof(t_obj_verticle_lst))))
		ft_error(true, NULL);
	i = 1;
	while (i < 4)
	{
		if (obj_verticle_1(obj_info, args[i], new, ft_2arg(i, line_nb)) == ERROR)
			return (ERROR);
		i++;
	}
	if (args[i] != 0)
	{
		free(new);
		return ft_error(false, "line %d: %s (%s) too many arguments (need"
			" 3)\n", line_nb, obj_info.name, obj_info.description);
	}
	if (g_a->object.objects->groups->verticles)
		new->v.id = g_a->object.objects->groups->verticles->v.id + 1;
	else
		new->v.id = 1;
	new->next = g_a->object.objects->groups->verticles;
	g_a->object.objects->groups->verticles = new;
	return (SUCCESS);
}

static int obj_texture_1(t_obj obj_info, char *arg, t_obj_texture_lst *new,
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
			return ft_error(false, "line %d: %s (%s) not enouth args (need "
				"2 or 3)\n", line_nb, obj_info.name, obj_info.description);
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

int		obj_texture(t_obj obj_info, char **args, int line_nb)
{
	t_obj_texture_lst	*new;
	int					i;

	if (!(new = malloc(sizeof(t_obj_texture_lst))))
		ft_error(true, NULL);
	i = 1;
	while (i < 4)
	{
		if (obj_texture_1(obj_info, args[i], new, ft_2arg(i, line_nb)) == ERROR)
			return (ERROR);
		if (args[i] == NULL && i >= 3)
			break ;
		i++;
	}
	if (args[i] != 0)
	{
		free(new);
		return ft_error(false, "line %d: %s (%s) too many arguments (need 2 "
			"or 3)\n", line_nb, obj_info.name, obj_info.description);
	}
	if (g_a->object.objects->groups->textures)
		new->t.id = g_a->object.objects->groups->textures->t.id + 1;
	else
		new->t.id = 1;
	new->next = g_a->object.objects->groups->textures;
	g_a->object.objects->groups->textures = new;
	return (SUCCESS);
}

static int obj_normal_1(t_obj obj_info, char *arg, t_obj_normal_lst *new,
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
		return ft_error(false, "line %d: %s (%s) not enouth arguments (need 3)\n",
			line_nb, obj_info.name, obj_info.description);
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

int		obj_normal(t_obj obj_info, char **args, int line_nb)
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
		return ft_error(false, "line %d: %s (%s) too many arguments (need 3)\n",
			line_nb, obj_info.name, obj_info.description);
	}
	if (g_a->object.objects->groups->normales)
		new->vn.id = g_a->object.objects->groups->normales->vn.id + 1;
	else
		new->vn.id = 1;
	new->next = g_a->object.objects->groups->normales;
	g_a->object.objects->groups->normales = new;
	return (SUCCESS);
}

static int	parse_one_face_element(t_obj_face *new, char *arg)
{
	char				*str_ptr;
	int					act_val;
	int					get_nb;
	void				*tmp[2];

	act_val = 0;
	str_ptr = arg;
	while (act_val < 3)
	{
		if (*str_ptr == '/' || *str_ptr == '\0')
			get_nb = -1;
		else
			get_nb = atoi(str_ptr);
		if (act_val == 0)
		{
			tmp[0] = (void*)get_verticle_by_id(get_nb);
			if (tmp[0] == NULL)
				return (ERROR);

			if (!(tmp[1] = malloc(sizeof(t_obj_verticle_lst))))
				ft_error(true, NULL);
			((t_obj_verticle_lst*)(tmp[1]))->v = ((t_obj_verticle_lst*)(tmp[0]))->v;
			((t_obj_verticle_lst*)(tmp[1]))->next = new->verticles;
			new->verticles = tmp[1];
		}
		else if (act_val == 1)
		{
			if (get_nb == -1)
			{
				if (!(tmp[1] = malloc(sizeof(t_obj_texture_lst))))
					ft_error(true, NULL);
				((t_obj_texture_lst*)(tmp[1]))->t.id = 0;
				((t_obj_texture_lst*)(tmp[1]))->t.position = new->verticles->v.position;
				((t_obj_texture_lst*)(tmp[1]))->next = new->texture_coord;
				new->texture_coord = ((t_obj_texture_lst*)(tmp[1]));
			}
			else
			{
				tmp[0] = (void*)get_texture_by_id(get_nb);
				if (tmp[0] == NULL)
					return (ERROR);

				if (!(tmp[1] = malloc(sizeof(t_obj_texture_lst))))
					ft_error(true, NULL);
				((t_obj_texture_lst*)(tmp[1]))->t = ((t_obj_texture_lst*)(tmp[0]))->t;
				((t_obj_texture_lst*)(tmp[1]))->next = new->texture_coord;
				new->texture_coord = tmp[1];
			}
		}
		else if (act_val == 2)
		{
			if (get_nb == -1)
			{
				if (!(tmp[1] = malloc(sizeof(t_obj_normal_lst))))
					ft_error(true, NULL);
				((t_obj_normal_lst*)(tmp[1]))->vn.id = 0;
				((t_obj_normal_lst*)(tmp[1]))->next = new->normales;
				new->normales = ((t_obj_normal_lst*)(tmp[1]));
			}
			else
			{
				tmp[0] = (void*)get_normal_by_id(get_nb);
				if (tmp[0] == NULL)
					return (ERROR);

				if (!(tmp[1] = malloc(sizeof(t_obj_normal_lst))))
					ft_error(true, NULL);
				((t_obj_normal_lst*)(tmp[1]))->vn = ((t_obj_normal_lst*)(tmp[0]))->vn;
				((t_obj_normal_lst*)(tmp[1]))->next = new->normales;
				new->normales = tmp[1];
			}
		}
		while (*str_ptr != '\0')
		{
			if (*str_ptr == '/')
			{
				str_ptr++;
				break ;
			}
			str_ptr++;
		}
		act_val++;
	}
	return (SUCCESS);
}

int		obj_faces(t_obj obj_info, char **args, int line_nb)
{
	t_obj_face			*new;
	int					i;

	if (!(new = malloc(sizeof(t_obj_face))))
		ft_error(true, NULL);
	new->verticles = NULL;
	new->texture_coord = NULL;
	i = 0;
	while (args[++i] != 0)
		if (parse_one_face_element(new, args[i]) == ERROR)
		{
			free(new);
			return ft_error(false, "line %d: %s (%s) invalid argument %s\n",
				line_nb, obj_info.name, obj_info.description, args[i]);
		}
	if (i < 4 && ft_free(1, new))
		return ft_error(false, "line %d: %s (%s) not enouth arguments (at least"
			" 3)\n", line_nb, obj_info.name, obj_info.description);
	new->color.x = rand() % (MAX_GREY_COLOR - MIN_GREY_COLOR) + MIN_GREY_COLOR;
	new->color.y = new->color.x;
	new->color.z = new->color.x;
	new->next = g_a->object.objects->groups->faces;
	g_a->object.objects->groups->faces = new;
	return (SUCCESS);
}
