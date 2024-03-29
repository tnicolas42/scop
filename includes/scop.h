/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:14:13 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 14:03:30 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <libft.h>
# include <fcntl.h>
# include <stdbool.h>
# include <scop_struct.h>

# define SC_WIDTH 1000
# define SC_HEIGHT 800

# define MOVING_SPEED_MOUSE 0.01
# define MOVING_SPEED_KEYBOARD 0.1
# define ROTATE_SPEED_MOUSE 0.2
# define ROTATE_SPEED_KEYBOARD 10
# define ZOOM_SPEED_MOUSE 0.02
# define ZOOM_SPEED_KEYBOARD 0.15
# define AUTO_MOVING_SPEED 0.6
# define ZOOM_MIN 0.1
# define ZOOM_MAX 15
# define TRANSITION_DOWN_SPEED 8
# define TRANSITION_UP_SPEED 3

# define CAMERA_POS_Y 1.5
# define CAMERA_NEAR 0.5
# define CAMERA_FAR 50

# define SUCCESS 1
# define ERROR 0

# define NB_TYPE_OBJ_FILE 11

# define DRAW_VERTICLES false
# define DRAW_FACES true
# define AUTO_MOVING true
# define PRINT_NOT_IMPLEMENTED false

# define ENABLE_SHADER true
# define SHADER_VERTEX_PATH "shaders/vertex.glsl"
# define SHADER_FRAGMENT_PATH "shaders/fragment.glsl"
# define MIN_GREY_COLOR 45
# define MAX_GREY_COLOR 200

# define MATERIAL_AMBIENT_R 0.5
# define MATERIAL_AMBIENT_G 0.5
# define MATERIAL_AMBIENT_B 0.5
# define MATERIAL_DIFFUSE_R 0.3
# define MATERIAL_DIFFUSE_G 0.3
# define MATERIAL_DIFFUSE_B 0.3
# define MATERIAL_SPECULAR_R 0.08
# define MATERIAL_SPECULAR_G 0.08
# define MATERIAL_SPECULAR_B 0.08
# define MATERIAL_SHININESS 1

extern t_a			*g_a;

void				init_shader(void);

void				reset_transform(t_transform *transform);
void				set_camera_pos(void);
void				load_bmp(char *filename, bool default_tex);
void				init_a(void);
void				init(void);
void				quit(void);

int					obj_not_implemented(t_obj obj_info, char **args,
						int line_nb);
int					obj_comment(t_obj obj_info, char **args, int line_nb);
int					obj_verticle(t_obj obj_info, char **args, int line_nb);
int					obj_texture(t_obj obj_info, char **args, int line_nb);
int					obj_normal(t_obj obj_info, char **args, int line_nb);
int					obj_faces(t_obj obj_info, char **args, int line_nb);
void				parse(char *filename);

void				error_callback(int error, const char *description);
void				cursor_position_callback(GLFWwindow *window, double xpos,
						double ypos);
void				mouse_button_callback(GLFWwindow *window, int button,
						int action, int mods);
void				scroll_callback(GLFWwindow *window, double xoffset,
						double yoffset);
void				key_callback(GLFWwindow *window, int key, int scancode,
						int action);

void				loop(void);
void				move_object(double delta_x, double delta_y);
void				zoom_object(double offset);
void				transform(void);
void				set_camera(float ratio);
void				draw(void);

t_obj_verticle_lst	*get_verticle_by_id(int id);
t_obj_texture_lst	*get_texture_by_id(int id);
t_obj_normal_lst	*get_normal_by_id(int id);
int					ft_error(bool exit_, char *msg, ...);

#endif
