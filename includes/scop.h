/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:14:13 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/21 16:06:53 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <libft.h>
# include <stdbool.h>
# include <scop_struct.h>

# define SC_WIDTH 640
# define SC_HEIGHT 480

# define MOVING_SPEED_KEY 0.2
# define MOVING_SPEED_MOUSE 0.01
# define ROTATE_SPEED_MOUSE 0.2
# define ZOOM_SPEED 0.02
# define ZOOM_MIN 0.1
# define ZOOM_MAX 5

# define SUCCESS 1
# define ERROR 0

extern t_a	*g_a;

void		reset_transform(void);
void		init(void);
void		quit(void);

void		error_callback(int error, const char *description);
void		cursor_position_callback(GLFWwindow *window, double xpos,
				double ypos);
void		mouse_button_callback(GLFWwindow *window, int button, int action,
				int mods);
void		scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void		key_callback(GLFWwindow *window, int key, int scancode, int action,
				int mods);

void		loop(void);
void		move_object(double delta_x, double delta_y);
void		transform(void);
void		set_camera(void);
void		draw(void);

#endif
