#ifndef _SCOP_H_
# define _SCOP_H_

# include <libft.h>
# include <stdbool.h>

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLU
# include <GLFW/glfw3.h>

# define SC_WIDTH 640
# define SC_HEIGHT 480

# define MOVING_SPEED_KEY 0.2
# define MOVING_SPEED_MOUSE 0.01
# define ROTATE_SPEED_MOUSE 0.2
# define ZOOM_SPEED 0.02
# define ZOOM_MIN 0.1
# define ZOOM_MAX 5

typedef struct  s_vector3
{
    double      x;
    double      y;
    double      z;
}               t_vector3;

typedef struct  s_key_mouse
{
    bool        is_ctrl_pressed;
    bool        is_mouse_left_pressed;
    bool        is_mouse_right_pressed;
    int         mouse_x;
    int         mouse_y;
}               t_key_mouse;


typedef struct  s_cam
{
    t_vector3   position;
    t_vector3   target;
    t_vector3   vert_vector;
}               t_cam;

typedef struct  s_transform
{
    t_vector3   position;
    t_vector3   rotation;
    t_vector3   scale;
}               t_transform;

typedef struct  s_a
{
    t_cam       cam;
    t_transform transform;
    GLFWwindow  *window;
    t_key_mouse key_mouse;

}               t_a;

extern t_a      a;

void    init(void);
void    quit(void);

void    error_callback(int error, const char* description);
void    cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void    mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void    scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void    loop(void);
void    move_object(double delta_x, double delta_y);
void    transform(void);
void    set_camera(void);
void    draw(void);

#endif
