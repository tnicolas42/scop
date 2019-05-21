#include <scop.h>

void    loop(void)
{
	while (!glfwWindowShouldClose(g_a->window))
	{
		float ratio;
        int width, height;

		glLoadIdentity( );

        glfwGetFramebufferSize(g_a->window, &width, &height);
		glViewport(0, 0, width, height);
        ratio = width / (float) height;
		glMatrixMode(GL_PROJECTION);
		gluPerspective(70,ratio,1,1000);

		set_camera();
		transform();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw();

        glFlush();
		glfwSwapBuffers(g_a->window);
		glfwPollEvents();
		usleep(10 * 1000);
	}
}