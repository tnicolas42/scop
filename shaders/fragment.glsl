#version 120

void main (void)
{
	vec4 color = gl_Color;
	color.w = 1.0;
	color.x = 0.5;

	gl_FragColor = color;
}