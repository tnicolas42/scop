/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:19:42 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/21 16:48:57 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	draw(void)
{
	double sz;

	sz = g_a->description.size.x / 2;
	glBegin(GL_QUADS);
	glColor3ub(255, 0, 0);
	glVertex3d(-sz, sz, sz);
	glVertex3d(sz, sz, sz);
	glVertex3d(sz, sz, -sz);
	glVertex3d(-sz, sz, -sz);
	glEnd();
	glBegin(GL_QUADS);
	glColor3ub(0, 255, 0);
	glVertex3d(-sz, sz, -sz);
	glVertex3d(sz, sz, -sz);
	glVertex3d(sz, -sz, -sz);
	glVertex3d(-sz, -sz, -sz);
	glEnd();
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 255);
	glVertex3d(-sz, -sz, -sz);
	glVertex3d(-sz, sz, -sz);
	glVertex3d(-sz, sz, sz);
	glVertex3d(-sz, -sz, sz);
	glEnd();
	glBegin(GL_QUADS);
	glColor3ub(255, 255, 0);
	glVertex3d(-sz, -sz, sz);
	glVertex3d(-sz, sz, sz);
	glVertex3d(sz, sz, sz);
	glVertex3d(sz, -sz, sz);
	glEnd();
	glBegin(GL_QUADS);
	glColor3ub(255, 0, 255);
	glVertex3d(-sz, -sz, sz);
	glVertex3d(sz, -sz, sz);
	glVertex3d(sz, -sz, -sz);
	glVertex3d(-sz, -sz, -sz);
	glEnd();
	glBegin(GL_QUADS);
	glColor3ub(0, 255, 255);
	glVertex3d(sz, -sz, sz);
	glVertex3d(sz, sz, sz);
	glVertex3d(sz, sz, -sz);
	glVertex3d(sz, -sz, -sz);
	glEnd();
}
