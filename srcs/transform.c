#include <scop.h>

void move_object(double delta_x, double delta_y)
{
	if (g_a->key_mouse.is_mouse_left_pressed && !g_a->key_mouse.is_ctrl_pressed)
	{
		g_a->transform.position.x += -delta_x * MOVING_SPEED_MOUSE;
		g_a->transform.position.z += delta_y * MOVING_SPEED_MOUSE;
	}
	if ((g_a->key_mouse.is_mouse_left_pressed && g_a->key_mouse.is_ctrl_pressed) ||
		(g_a->key_mouse.is_mouse_right_pressed))
	{
		g_a->transform.rotation.x += -delta_y * ROTATE_SPEED_MOUSE;
		g_a->transform.rotation.z += -delta_x * ROTATE_SPEED_MOUSE;
	}
}

void transform(void)
{
	glTranslated(g_a->transform.position.x,
				 g_a->transform.position.y,
				 g_a->transform.position.z);
	glRotated(g_a->transform.rotation.x, 1, 0, 0);
	glRotated(g_a->transform.rotation.y, 0, 1, 0);
	glRotated(g_a->transform.rotation.z, 0, 0, 1);
	glScaled(g_a->transform.scale.x,
			 g_a->transform.scale.y,
			 g_a->transform.scale.z);
}

void set_camera(void)
{
	gluLookAt(g_a->cam.position.x, g_a->cam.position.y, g_a->cam.position.z,
			  g_a->cam.target.x, g_a->cam.target.y, g_a->cam.target.z,
			  g_a->cam.vert_vector.x, g_a->cam.vert_vector.y, g_a->cam.vert_vector.z);
}