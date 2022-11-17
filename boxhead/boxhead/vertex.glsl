#version 330 

layout(location=0)in vec3 in_Position;
layout(location=1)in vec3 in_Color;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

uniform vec3 color;
uniform vec3 pos;



out vec3 out_Color;


void main(){

gl_Position = projectionTransform * viewTransform * modelTransform * vec4(in_Position, 1.0);
out_Color= in_Color;
}


