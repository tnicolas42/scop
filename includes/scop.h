/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:14:13 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/22 20:24:30 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <libft.h>
# include <fcntl.h>
# include <stdbool.h>
# include <scop_struct.h>

# define SC_WIDTH 640
# define SC_HEIGHT 480

# define MOVING_SPEED_MOUSE 0.01
# define MOVING_SPEED_KEYBOARD 0.1
# define ROTATE_SPEED_MOUSE 0.2
# define ROTATE_SPEED_KEYBOARD 10
# define ZOOM_SPEED_MOUSE 0.02
# define ZOOM_SPEED_KEYBOARD 0.15
# define ZOOM_MIN 0.1
# define ZOOM_MAX 15

# define CAMERA_POS_Y 2
# define CAMERA_NEAR CAMERA_POS_Y
# define CAMERA_FAR 50

# define SUCCESS 1
# define ERROR 0

# define NB_TYPE_OBJ_FILE 11

# define DRAW_VERTICLES false
# define DRAW_FACES true

extern t_a		*g_a;

void			reset_transform(t_transform *transform);
void			set_camera_pos(void);
void			init(void);
void			quit(void);

int				obj_not_implemented(t_obj obj_info, char **args, int line_nb);
int				obj_comment(t_obj obj_info, char **args, int line_nb);
int				obj_verticle(t_obj obj_info, char **args, int line_nb);
int				obj_texture(t_obj obj_info, char **args, int line_nb);
int				obj_faces(t_obj obj_info, char **args, int line_nb);
void			parse(char *filename);

void			error_callback(int error, const char *description);
void			cursor_position_callback(GLFWwindow *window, double xpos,
					double ypos);
void			mouse_button_callback(GLFWwindow *window, int button,
					int action, int mods);
void			scroll_callback(GLFWwindow *window, double xoffset,
					double yoffset);
void			key_callback(GLFWwindow *window, int key, int scancode,
					int action);

void			loop(void);
void			move_object(double delta_x, double delta_y);
void			zoom_object(double offset);
void			transform(void);
void			set_camera(float ratio);
void			draw(void);

#endif
