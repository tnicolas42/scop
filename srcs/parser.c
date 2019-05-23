/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:47:35 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/23 16:29:34 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_obj		g_obj[NB_TYPE_OBJ_FILE] =
{
	{"#", obj_comment, "comment"},
	{"o", obj_not_implemented, "object name"},
	{"g", obj_not_implemented, "group name"},
	{"v", obj_verticle, "verticle"},
	{"vt", obj_texture, "texture coordinate"},
	{"vn", obj_normal, "normal"},
	{"f", obj_faces, "face"},
	{"l", obj_not_implemented, "line element"},
	{"s", obj_not_implemented, "smooth shading can be disabled"},
	{"mtllib", obj_not_implemented, "external .mtl file name"},
	{"usemtl", obj_not_implemented, "material name"}
};

static void	parse_line(char *line, int line_nb)
{
	char	**words;
	int		i;
	i = 0;
	while (line[i])
	{
		line[i] = (line[1] == '\t') ? ' ' : line[i];
		i++;
	}
	if (!(words = ft_strsplit(line, ' ')))
		exit(EXIT_FAILURE);
	if (words[0] == 0)
		return ;
	i = 0;
	while (i < NB_TYPE_OBJ_FILE)
	{
		if (ft_strcmp(words[0], g_obj[i].name) == 0)
		{
			if (g_obj[i].func(g_obj[i], words, line_nb) == ERROR)
				exit(EXIT_FAILURE);
			break ;
		}
		i++;
	}
	if (i >= NB_TYPE_OBJ_FILE)
	{
		ft_printf("invalid command %s (line %d): %s\n", words[0], line_nb, line);
		ft_free_tab(1, words);
		exit(EXIT_FAILURE);
	}
	ft_free_tab(1, words);
}

static void	set_sizes()
{
	t_obj_verticle_lst	*tmp;
	double				max_size;

	tmp = g_a->object.objects->groups->verticles;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		g_a->object.description.min.x = (tmp->v.position.x < g_a->object.description.min.x) ? tmp->v.position.x : g_a->object.description.min.x;
		g_a->object.description.max.x = (tmp->v.position.x > g_a->object.description.max.x) ? tmp->v.position.x : g_a->object.description.max.x;
		g_a->object.description.min.y = (tmp->v.position.y < g_a->object.description.min.y) ? tmp->v.position.y : g_a->object.description.min.y;
		g_a->object.description.max.y = (tmp->v.position.y > g_a->object.description.max.y) ? tmp->v.position.y : g_a->object.description.max.y;
		g_a->object.description.min.z = (tmp->v.position.z < g_a->object.description.min.z) ? tmp->v.position.z : g_a->object.description.min.z;
		g_a->object.description.max.z = (tmp->v.position.z > g_a->object.description.max.z) ? tmp->v.position.z : g_a->object.description.max.z;
		tmp = tmp->next;
	}
	g_a->object.description.size.x = g_a->object.description.max.x - g_a->object.description.min.x;
	g_a->object.description.size.y = g_a->object.description.max.y - g_a->object.description.min.y;
	g_a->object.description.size.z = g_a->object.description.max.z - g_a->object.description.min.z;
	g_a->object.description.center.x = (g_a->object.description.max.x + g_a->object.description.min.x) / 2;
	g_a->object.description.center.y = (g_a->object.description.max.y + g_a->object.description.min.y) / 2;
	g_a->object.description.center.z = (g_a->object.description.max.z + g_a->object.description.min.z) / 2;
	max_size = g_a->object.description.size.x;
	max_size = (g_a->object.description.size.y > max_size) ? g_a->object.description.size.y : max_size;
	max_size = (g_a->object.description.size.z > max_size) ? g_a->object.description.size.z : max_size;
	if (max_size == 0)
		max_size = 1;
	g_a->object.description.max_size = max_size;
}

static void	parse_file(int fd)
{
	char	*line;
	int		line_nb;
	int		ret_gnl;

	ret_gnl = GNL_LINE_READ;
	line_nb = 1;
	while (ret_gnl == GNL_LINE_READ)
	{
		ret_gnl = get_next_line(fd, &line);
		if (ret_gnl == GNL_ERROR)
		{
			ft_printf("invalid file format\n");
			exit(EXIT_FAILURE);
		}
		else if (ret_gnl == GNL_LINE_READ)
		{
			parse_line(line, line_nb);
			free(line);
		}
		line_nb += 1;
	}
}

void		parse(char *filename)
{
	int		fd;

	if ((fd = open(filename, 'r')) < 0)
	{
		ft_printf("invalid filename %s\n", filename);
		exit(EXIT_FAILURE);
	}
	parse_file(fd);
	close(fd);
	set_sizes();
}
