/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:04:33 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 14:05:06 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static int	parse_one_face_element_3(t_obj_face *new, int get_nb, void *tmp[2])
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
		((t_obj_normal_lst*)(tmp[1]))->vn = ((t_obj_normal_lst*)
			(tmp[0]))->vn;
		((t_obj_normal_lst*)(tmp[1]))->next = new->normales;
		new->normales = tmp[1];
	}
	return (SUCCESS);
}

static int	parse_one_face_element_2(t_obj_face *new, int get_nb, void *tmp[2])
{
	if (get_nb == -1)
	{
		if (!(tmp[1] = malloc(sizeof(t_obj_texture_lst))))
			ft_error(true, NULL);
		((t_obj_texture_lst*)(tmp[1]))->t.id = 0;
		((t_obj_texture_lst*)(tmp[1]))->t.position =
			new->verticles->v.position;
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
		((t_obj_texture_lst*)(tmp[1]))->t = ((t_obj_texture_lst*)
			(tmp[0]))->t;
		((t_obj_texture_lst*)(tmp[1]))->next = new->texture_coord;
		new->texture_coord = tmp[1];
	}
	return (SUCCESS);
}

static int	parse_one_face_element_1(t_obj_face *new, int act_val, int get_nb,
	void *tmp[2])
{
	if (act_val == 0)
	{
		tmp[0] = (void*)get_verticle_by_id(get_nb);
		if (tmp[0] == NULL)
			return (ERROR);
		if (!(tmp[1] = malloc(sizeof(t_obj_verticle_lst))))
			ft_error(true, NULL);
		((t_obj_verticle_lst*)(tmp[1]))->v = ((t_obj_verticle_lst*)
			(tmp[0]))->v;
		((t_obj_verticle_lst*)(tmp[1]))->next = new->verticles;
		new->verticles = tmp[1];
	}
	else if (act_val == 1)
	{
		if (parse_one_face_element_2(new, get_nb, tmp) == ERROR)
			return (ERROR);
	}
	else if (act_val == 2)
	{
		if (parse_one_face_element_3(new, get_nb, tmp) == ERROR)
			return (ERROR);
	}
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
		if (parse_one_face_element_1(new, act_val, get_nb, tmp) == ERROR)
			return (ERROR);
		while (*str_ptr != '\0')
		{
			if (*str_ptr == '/' && str_ptr++)
				break ;
			str_ptr++;
		}
		act_val++;
	}
	return (SUCCESS);
}

int			obj_faces(t_obj obj_info, char **args, int line_nb)
{
	t_obj_face			*new;
	int					i;

	if (!(new = malloc(sizeof(t_obj_face))))
		ft_error(true, NULL);
	new->verticles = NULL;
	new->texture_coord = NULL;
	i = 0;
	while (args[++i] != 0)
		if (parse_one_face_element(new, args[i]) == ERROR && ft_free(1, new))
		{
			return (ft_error(false, "line %d: %s (%s) invalid argument %s\n",
				line_nb, obj_info.name, obj_info.description, args[i]));
		}
	if (i < 4 && ft_free(1, new))
	{
		return (ft_error(false, "line %d: %s (%s) not enouth arguments (at "
			"least 3)\n", line_nb, obj_info.name, obj_info.description));
	}
	new->color.x = rand() % (MAX_GREY_COLOR - MIN_GREY_COLOR) + MIN_GREY_COLOR;
	new->color.y = new->color.x;
	new->color.z = new->color.x;
	new->next = g_a->object.objects->groups->faces;
	g_a->object.objects->groups->faces = new;
	return (SUCCESS);
}
