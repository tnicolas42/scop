#include <scop.h>

void    reset_transform(void)
{
    g_a->transform.position.x = 0;
	g_a->transform.position.y = 0;
	g_a->transform.position.z = 0;
	g_a->transform.rotation.x = 0;
	g_a->transform.rotation.y = 0;
	g_a->transform.rotation.z = 0;
	g_a->transform.scale.x = 1;
	g_a->transform.scale.y = 1;
	g_a->transform.scale.z = 1;
}

static int init_a(void)
{
    if (g_a == NULL)
        if (!(g_a = malloc(sizeof(t_a))))
            return (ERROR);

	g_a->key_mouse.is_ctrl_pressed = false;
	g_a->key_mouse.is_mouse_left_pressed = false;
	g_a->key_mouse.is_mouse_right_pressed = false;
	g_a->key_mouse.mouse_x = -1;
	g_a->key_mouse.mouse_y = -1;

	g_a->cam.position.x = 0;
	g_a->cam.position.y = -5;
	g_a->cam.position.z = 0;
	g_a->cam.target.x = 0;
	g_a->cam.target.y = 0;
	g_a->cam.target.z = 0;
	g_a->cam.vert_vector.x = 0;
	g_a->cam.vert_vector.y = 0;
	g_a->cam.vert_vector.z = 1;

	reset_transform();
    return (SUCCESS);
}

void init(void)
{
    init_a();

	if (!glfwInit())
	{
		ft_putstr("Error when loading GLFW\n");
		exit(1);
	}
	glfwSetErrorCallback(error_callback);
	g_a->window = glfwCreateWindow(SC_WIDTH, SC_HEIGHT, "scop", NULL, NULL);
	if (!g_a->window)
	{
		ft_putstr("Error when loading GLFW\n");
		exit(1);
	}
	glfwMakeContextCurrent(g_a->window);
	glfwSetKeyCallback(g_a->window, key_callback);
	glfwSetScrollCallback(g_a->window, scroll_callback);
	glfwSetMouseButtonCallback(g_a->window, mouse_button_callback);
	glfwSetCursorPosCallback(g_a->window, cursor_position_callback);

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
}

void quit()
{
	glfwDestroyWindow(g_a->window);
	glfwTerminate();
    free(g_a);
}