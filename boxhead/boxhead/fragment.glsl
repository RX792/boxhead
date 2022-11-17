#version 330 

in vec3 out_Color;
out vec4 FragColor;

void main(){
FragColor = vec4(out_Color, 1.0);
}
