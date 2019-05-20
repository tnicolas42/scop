
#include <scop.h>

void error_callback(int error, const char* description)
{
    ft_dprintf(STDERR_FILENO, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void draw()
{
	glBegin(GL_QUADS);

	glColor3ub(0,0,255);
	glVertex2d(-0.75,-0.75);
	glVertex2d(-0.75,0.75);
	glColor3ub(255,0,0);
	glVertex2d(0.75,0.75);
	glVertex2d(0.75,-0.75);

	glEnd();
}

int main(int ac, char **av)
{
	if (!glfwInit())
	{
		ft_putstr("Error when loading GLFW\n");
		exit(1);
	}
	glfwSetErrorCallback(error_callback);

	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(640, 480, "scop", NULL, NULL);
	if (!window)
	{
		ft_putstr("Error when loading GLFW\n");
		exit(1);
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
        ratio = width / (float) height;

		glClear(GL_COLOR_BUFFER_BIT);
        draw();
        glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();
		usleep(100 * 1000);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}