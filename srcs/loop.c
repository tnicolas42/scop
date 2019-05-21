#include <scop.h>

void    loop(void)
{
	while (!glfwWindowShouldClose(a.window))
	{
		float ratio;
        int width, height;

		glLoadIdentity( );

        glfwGetFramebufferSize(a.window, &width, &height);
		glViewport(0, 0, width, height);
        ratio = width / (float) height;
		glMatrixMode(GL_PROJECTION);
		gluPerspective(70,ratio,1,1000);

		set_camera();
		transform();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw();

        glFlush();
		glfwSwapBuffers(a.window);
		glfwPollEvents();
		usleep(10 * 1000);
	}
}