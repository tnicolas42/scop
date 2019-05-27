#version 120

void main(void)
{
   vec4 a = gl_Vertex;
   a.x = a.x;


   gl_Position = gl_ModelViewProjectionMatrix * a;
}