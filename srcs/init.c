/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:16 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/27 11:41:43 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		reset_transform(t_transform *transform)
{
	transform->position.x = 0;
	transform->position.y = 0;
	transform->position.z = 0;
	transform->rotation.x = 90;
	transform->rotation.y = -90;
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
	g_a->object.objects->groups->textures = NULL;
	g_a->object.objects->groups->normales = NULL;
	g_a->object.objects->groups->textures_bmp = NULL;
	g_a->object.objects->groups->used_texture_bmp = NULL;
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
	g_a->is_auto_moving = AUTO_MOVING;
	init_object();
	set_camera_pos();
	reset_transform(&(g_a->transform));
}

static void	create_bmp_header(char *filename, t_bmp_texture_lst *texture)
{
	FILE	*file;

	if ((file = fopen(filename, "r")) == NULL)
	{
		ft_printf("fail to open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	fseek(file, 18, SEEK_SET);
	fread(&texture->t.w, 4, 1, file);
	fread(&texture->t.h, 4, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&texture->t.bpp, 2, 1, file);
	fclose(file);
	texture->t.opp = texture->t.bpp >> 3;
	texture->t.sl = texture->t.w * texture->t.opp;
	texture->t.w < 0 ? texture->t.w = -texture->t.w : 0;
	texture->t.h < 0 ? texture->t.h = -texture->t.h : 0;
	texture->t.size = texture->t.sl * texture->t.h;
}

static void	create_bmp_img(t_bmp_texture_lst *texture, char *buffer, int i)
{
	int	j;
	int k;
	int	l;

	if (!(texture->t.img = malloc(sizeof(unsigned char) * texture->t.size)))
		exit(EXIT_FAILURE);
	l = 0;
	while ((i -= texture->t.sl) >= 0)
	{
		j = -texture->t.opp;
		while ((j += texture->t.opp) < texture->t.sl)
		{
			k = -1;
			while (++k < texture->t.opp)
				texture->t.img[l + j + k] = (unsigned char)buffer[i + j + (texture->t.opp - k - 1)];
		}
		l += texture->t.sl;
	}
}

static void	create_gl_texture(t_bmp_texture_lst *texture)
{
	glGenTextures(1, &(texture->t.gl_texture));
	glBindTexture(GL_TEXTURE_2D, texture->t.gl_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->t.w, texture->t.h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->t.img);
}

void	load_bmp(char *filename)
{
	t_bmp_texture_lst	*texture;
	int					fd;
	int					i;
	char				*buffer;

	if (!(texture = malloc(sizeof(t_bmp_texture_lst))))
		exit(EXIT_FAILURE);
	create_bmp_header(filename, texture);
	buffer = (char*)malloc(sizeof(char) * texture->t.size + 1);
	if ((fd = open(filename, O_RDWR)) == -1)
	{
		ft_printf("fail to open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	lseek(fd, 54, SEEK_SET);
	i = read(fd, buffer, texture->t.size);
	create_bmp_img(texture, buffer, i);
	ft_strdel((char**)&buffer);
	close(fd);
	create_gl_texture(texture);
	texture->next = g_a->object.objects->groups->textures_bmp;
	g_a->object.objects->groups->textures_bmp = texture;
	g_a->object.objects->groups->used_texture_bmp = texture;
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
	glEnable(GL_TEXTURE_2D);
	load_bmp("textures/metal.bmp");
	load_bmp("textures/tiles.bmp");
	if (ENABLE_SHADER)
		init_shader();
}

static void free_g_a2(t_obj_group *group)
{
	t_obj_face			*tmp_face[2];
	t_obj_verticle_lst	*tmp_verticle[2];
	t_obj_texture_lst	*tmp_texture[2];
	t_bmp_texture_lst	*tmp_bmp_texture[2];

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
