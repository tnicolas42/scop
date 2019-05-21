/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:21:56 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/21 16:53:06 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	loop(void)
{
	float	ratio;
	int		width;
	int		height;

	while (!glfwWindowShouldClose(g_a->window))
	{
		glLoadIdentity();
		glfwGetFramebufferSize(g_a->window, &width, &height);
		glViewport(0, 0, width, height);
		ratio = width / (float)height;
		set_camera(ratio);
		transform();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw();
		glFlush();
		glfwSwapBuffers(g_a->window);
		glfwPollEvents();
		usleep(10 * 1000);
	}
}
