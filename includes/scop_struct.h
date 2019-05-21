/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:26:40 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/21 16:06:54 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_STRUCT_H
# define SCOP_STRUCT_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLU
# include <GLFW/glfw3.h>

typedef struct	s_vector3
{
	double		x;
	double		y;
	double		z;
}				t_vector3;

typedef struct	s_key_mouse
{
	bool		is_ctrl_pressed;
	bool		is_mouse_left_pressed;
	bool		is_mouse_right_pressed;
	int			mouse_x;
	int			mouse_y;
}				t_key_mouse;

typedef struct	s_cam
{
	t_vector3	position;
	t_vector3	target;
	t_vector3	vert_vector;
}				t_cam;

typedef struct	s_transform
{
	t_vector3	position;
	t_vector3	rotation;
	t_vector3	scale;
}				t_transform;

typedef struct	s_a
{
	t_cam		cam;
	t_transform transform;
	GLFWwindow	*window;
	t_key_mouse key_mouse;

}				t_a;

#endif
