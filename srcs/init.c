#include <scop.h>

static void init_a(void)
{
	a.key_mouse.is_ctrl_pressed = false;
	a.key_mouse.is_mouse_left_pressed = false;
	a.key_mouse.is_mouse_right_pressed = false;
	a.key_mouse.mouse_x = -1;
	a.key_mouse.mouse_y = -1;

	a.cam.position.x = 0;
	a.cam.position.y = -5;
	a.cam.position.z = 0;
	a.cam.target.x = 0;
	a.cam.target.y = 0;
	a.cam.target.z = 0;
	a.cam.vert_vector.x = 0;
	a.cam.vert_vector.y = 0;
	a.cam.vert_vector.z = 1;

	a.transform.position.x = 0;
	a.transform.position.y = 0;
	a.transform.position.z = 0;
	a.transform.rotation.x = 0;
	a.transform.rotation.y = 0;
	a.transform.rotation.z = 0;
	a.transform.scale.x = 1;
	a.transform.scale.y = 1;
	a.transform.scale.z = 1;
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
	a.window = glfwCreateWindow(SC_WIDTH, SC_HEIGHT, "scop", NULL, NULL);
	if (!a.window)
	{
		ft_putstr("Error when loading GLFW\n");
		exit(1);
	}
	glfwMakeContextCurrent(a.window);
	glfwSetKeyCallback(a.window, key_callback);
	glfwSetScrollCallback(a.window, scroll_callback);
	glfwSetMouseButtonCallback(a.window, mouse_button_callback);
	glfwSetCursorPosCallback(a.window, cursor_position_callback);

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
}

void quit()
{
	glfwDestroyWindow(a.window);
	glfwTerminate();
}