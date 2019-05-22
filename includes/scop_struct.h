/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:26:40 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/22 16:00:29 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_STRUCT_H
# define SCOP_STRUCT_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLU
# include <GLFW/glfw3.h>

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
	struct s_obj_verticle	*next;
}					t_obj_verticle;

typedef struct		s_obj_verticle_lst
{
	t_obj_verticle				v;
	struct s_obj_verticle_lst	*next;
}					t_obj_verticle_lst;

/*
**	chained list with all faces (v ...)
*/

typedef struct		s_obj_face
{
	t_obj_verticle_lst	*verticles;
	struct s_obj_face	*next;
}					t_obj_face;

/*
**	chained list with all groups (g ...)
*/

typedef struct		s_obj_group
{
	char				*name;
	t_obj_verticle_lst	*verticles;
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
**  global object with all informations about the project
*/

typedef struct		s_a
{
	t_cam			cam;
	t_transform		transform;
	t_object		object;
	GLFWwindow		*window;
	t_key_mouse		key_mouse;
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
