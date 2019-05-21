#include <scop.h>

void move_object(double delta_x, double delta_y)
{
	if (a.key_mouse.is_mouse_left_pressed && !a.key_mouse.is_ctrl_pressed)
	{
		a.transform.position.x += -delta_x * MOVING_SPEED_MOUSE;
		a.transform.position.z += delta_y * MOVING_SPEED_MOUSE;
	}
	if ((a.key_mouse.is_mouse_left_pressed && a.key_mouse.is_ctrl_pressed) ||
		(a.key_mouse.is_mouse_right_pressed))
	{
		a.transform.rotation.x += -delta_y * ROTATE_SPEED_MOUSE;
		a.transform.rotation.z += -delta_x * ROTATE_SPEED_MOUSE;
	}
}

void transform(void)
{
	glTranslated(a.transform.position.x,
				 a.transform.position.y,
				 a.transform.position.z);
	glRotated(a.transform.rotation.x, 1, 0, 0);
	glRotated(a.transform.rotation.y, 0, 1, 0);
	glRotated(a.transform.rotation.z, 0, 0, 1);
	glScaled(a.transform.scale.x,
			 a.transform.scale.y,
			 a.transform.scale.z);
}

void set_camera(void)
{
	gluLookAt(a.cam.position.x, a.cam.position.y, a.cam.position.z,
			  a.cam.target.x, a.cam.target.y, a.cam.target.z,
			  a.cam.vert_vector.x, a.cam.vert_vector.y, a.cam.vert_vector.z);
}