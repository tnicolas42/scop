/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:16 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/23 14:03:44 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		reset_transform(t_transform *transform)
{
	transform->position.x = 0;
	transform->position.y = 0;
	transform->position.z = 0;
	transform->rotation.x = 0;
	transform->rotation.y = 0;
	transform->rotation.z = 0;
	transform->scale.x = 1;
	transform->scale.y = 1;
	transform->scale.z = 1;
}

void		set_camera_pos(void)
{
	g_a->cam.position.x = 0;
	g_a->cam.position.y = -g_a->object.description.max_size * CAMERA_POS_Y;
	g_a->cam.position.z = 0;
	g_a->cam.target.x = 0;
	g_a->cam.target.y = 0;
	g_a->cam.target.z = 0;
	g_a->cam.vert_vector.x = 0;
	g_a->cam.vert_vector.y = 0;
	g_a->cam.vert_vector.z = 1;
	g_a->cam.near = g_a->object.description.max_size / CAMERA_NEAR;
	g_a->cam.far = g_a->object.description.max_size * CAMERA_FAR;
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
		exit(EXIT_FAILURE);
	g_a->object.objects->name = NULL;
	g_a->object.objects->next = NULL;
	if (!(g_a->object.objects->groups = malloc(sizeof(t_obj_group))))
		exit(EXIT_FAILURE);
	g_a->object.objects->groups->name = NULL;
	g_a->object.objects->groups->next = NULL;
	g_a->object.objects->groups->verticles = NULL;
	g_a->object.objects->groups->faces = NULL;
}

static void	init_a(void)
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
	init_object();
	set_camera_pos();
	reset_transform(&(g_a->transform));
}

void	read_header(char *filename, t_texture *texture)
{
	FILE	*file;

	if ((file = fopen(filename, "r")) == NULL)
	{
		ft_printf("fail to open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	fseek(file, 18, SEEK_SET);
	fread(&texture->w, 4, 1, file);
	fread(&texture->h, 4, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&texture->bpp, 2, 1, file);
	fclose(file);
	texture->opp = texture->bpp / 8;
	texture->sl = texture->w * texture->opp;
	texture->w < 0 ? texture->w = -texture->w : 0;
	texture->h < 0 ? texture->h = -texture->h : 0;
	texture->size = texture->sl * texture->h;
}

void	get_image(t_texture *texture, char *buffer, int i)
{
	int	h;
	int	j;
	int	size;

	h = 0;
	size = texture->size * 2;
	if (!(texture->img = malloc(sizeof(unsigned char) * size)))
		exit(EXIT_FAILURE);
	while (i >= 0)
	{
		i -= texture->sl;
		j = 0;
		while (j < texture->sl)
		{
			texture->img[h + j] = (unsigned char)buffer[i + j + 2];
			texture->img[h + j + 1] = (unsigned char)buffer[i + j + 1];
			texture->img[h + j + 2] = (unsigned char)buffer[i + j];
			j += 3;
		}
		h += texture->sl;
	}
}

void	load_bmp(char *filename)
{
	t_texture	texture;
	int			fd;
	int			i;
	char		*buffer;

	read_header(filename, &texture);
	buffer = (char*)malloc(sizeof(char) * texture.size + 1);
	if ((fd = open(filename, O_RDWR)) == -1)
	{
		ft_printf("fail to open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	lseek(fd, 54, SEEK_SET);
	i = read(fd, buffer, texture.size);
	get_image(&texture, buffer, i);
	ft_strdel((char**)&buffer);
	close(fd);
}

void		init(void)
{
	init_a();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!glfwInit())
	{
		ft_putstr("Error when loading GLFW\n");
		exit(1);
	}
	g_a->window = glfwCreateWindow(SC_WIDTH, SC_HEIGHT, "scop", NULL, NULL);
	if (!g_a->window)
	{
		ft_putstr("Error when loading GLFW\n");
		exit(1);
	}
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(g_a->window, (void(*)(GLFWwindow *, int, int, int, int))
		(size_t)&key_callback);
	glfwSetScrollCallback(g_a->window, scroll_callback);
	glfwSetMouseButtonCallback(g_a->window, mouse_button_callback);
	glfwSetCursorPosCallback(g_a->window, cursor_position_callback);
	glfwMakeContextCurrent(g_a->window);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_3D);
	load_bmp("textures/metal.bmp");
}

static void free_g_a2(t_obj_group *group)
{
	t_obj_face			*tmp_face[2];
	t_obj_verticle_lst	*tmp_verticle[2];

	tmp_face[0] = group->faces;
	while(tmp_face[0])
	{
		tmp_verticle[0] = tmp_face[0]->verticles;
		while (tmp_verticle[0])
		{
			tmp_verticle[1] = tmp_verticle[0];
			tmp_verticle[0] = tmp_verticle[0]->next;
			free(tmp_verticle[1]);
		}
		tmp_face[1] = tmp_face[0];
		tmp_face[0] = tmp_face[0]->next;
		free(tmp_face[1]);
	}
	tmp_verticle[0] = group->verticles;
	while (tmp_verticle[0])
	{
		tmp_verticle[1] = tmp_verticle[0];
		tmp_verticle[0] = tmp_verticle[0]->next;
		free(tmp_verticle[1]);
	}
}

static void	free_g_a(void)
{
	t_obj_obj			*tmp_obj[2];
	t_obj_group			*tmp_group[2];

	tmp_obj[0] = g_a->object.objects;
	while (tmp_obj[0])
	{
		tmp_group[0] = tmp_obj[0]->groups;
		while (tmp_group[0])
		{
			free_g_a2(tmp_group[0]);
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
	glfwDestroyWindow(g_a->window);
	glfwTerminate();
	free_g_a();
}
