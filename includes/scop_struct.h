/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:26:40 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/27 11:31:50 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_STRUCT_H
# define SCOP_STRUCT_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLU
# include <GLFW/glfw3.h>

/*
**	simple object with information about the coordinate (x, y, z and w)
*/

typedef struct		s_vector4
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_vector4;

/*
**	simple object with information about the coordinate (x, y, and z)
*/

typedef struct		s_vector3
{
	double			x;
	double			y;
	double			z;
}					t_vector3;

/*
**	simple object with information about the coordinate (x and y)
*/

typedef struct		s_vector2
{
	double			x;
	double			y;
}					t_vector2;

/*
**	general informations about the mouse and the keyboard
*/

typedef struct		s_key_mouse
{
	bool			is_ctrl_pressed;
	bool			is_shift_pressed;
	bool			is_mouse_left_pressed;
	bool			is_mouse_right_pressed;
	int				mouse_x;
	int				mouse_y;
}					t_key_mouse;

/*
**	all informations about the camera
*/

typedef struct		s_cam
{
	t_vector3		position;
	t_vector3		target;
	t_vector3		vert_vector;
	double			near;
	double			far;
}					t_cam;

/*
**	transform of an object (position, rotation and scale)
*/

typedef struct		s_transform
{
	t_vector3		position;
	t_vector3		rotation;
	t_vector3		scale;
}					t_transform;

/*
**	global description of an object
*/

typedef struct		s_description
{
	t_vector3		size;
	t_vector3		min;
	t_vector3		max;
	t_vector3		center;
	double			max_size;
}					t_description;

/*
**	chained list with all verticles (v ...)
*/

typedef struct		s_obj_verticle
{
	int						id;
	t_vector3				position;
}					t_obj_verticle;

typedef struct		s_obj_verticle_lst
{
	t_obj_verticle				v;
	struct s_obj_verticle_lst	*next;
}					t_obj_verticle_lst;

/*
**	chained list with all normales (vn ...)
*/

typedef struct		s_obj_normal
{
	int						id;
	t_vector3				position;
}					t_obj_normal;

typedef struct		s_obj_normal_lst
{
	t_obj_normal				vn;
	struct s_obj_normal_lst	*next;
}					t_obj_normal_lst;

/*
**	chained list with all textures coordinates (vt ...)
*/

/*
**	used to save textures (BMP)
**		id -> id of the texture (from 1 to n)
**		img -> the image data
**		w -> the image width (in pixel)
**		h -> the image height (in pixel)
**		sl -> size of a line (in octet)
**		bpp -> bits per pixel (24)
**		opp -> octet per pixel (3) = bpp / 8
*/

typedef struct		s_bmp_texture
{
	GLuint			gl_texture;
	unsigned char	*img;
	int				size;
	int				w;
	int				h;
	int				sl;
	short			bpp;
	short			opp;
}					t_bmp_texture;

typedef struct		s_bmp_texture_lst
{
	t_bmp_texture				t;
	struct s_bmp_texture_lst	*next;
}					t_bmp_texture_lst;

typedef struct		s_obj_texture
{
	int				id;
	t_vector3		position;
}					t_obj_texture;

typedef struct		s_obj_texture_lst
{
	t_obj_texture				t;
	struct s_obj_texture_lst	*next;
}					t_obj_texture_lst;

/*
**	chained list with all faces (v ...)
*/

typedef struct		s_obj_face
{
	t_obj_verticle_lst	*verticles;
	t_obj_texture_lst	*texture_coord;
	t_obj_normal_lst	*normales;
	struct s_obj_face	*next;
}					t_obj_face;

/*
**	chained list with all groups (g ...)
*/

typedef struct		s_obj_group
{
	char				*name;
	t_obj_verticle_lst	*verticles;
	t_obj_texture_lst	*textures;
	t_obj_normal_lst	*normales;
	t_bmp_texture_lst	*textures_bmp;
	t_bmp_texture_lst	*used_texture_bmp;
	t_obj_face			*faces;
	struct s_obj_group	*next;
}					t_obj_group;

/*
**	chained list with all objects (o ...)
*/

typedef struct		s_obj_obj
{
	char				*name;
	t_obj_group			*groups;
	struct s_obj_obj	*next;
}					t_obj_obj;

/*
**	all informations about an object
*/

typedef struct		s_object
{
	t_description	description;
	t_transform		transform;
	t_obj_obj		*objects;
}					t_object;

/*
**	all informations about the shaders
*/

typedef struct		s_shader
{
	GLuint			vert_id;
	GLuint			frag_id;
	GLuint			program;
}					t_shader;

/*
**  global object with all informations about the project
*/

typedef struct		s_a
{
	t_cam			cam;
	t_transform		transform;
	t_object		object;
	GLFWwindow		*window;
	t_shader		shader;
	t_key_mouse		key_mouse;
	bool			draw_verticles;
	bool			draw_faces;
	bool			is_auto_moving;
}					t_a;

/*
**	used in parsing to link code with function
*/

typedef struct		s_obj
{
	char			*name;
	int				(*func)(struct s_obj, char**, int);
	char			*description;
}					t_obj;

#endif
