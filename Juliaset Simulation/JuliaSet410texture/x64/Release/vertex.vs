#version 410

layout(location = 0) in  vec2 position;
layout(location = 1) in  vec4 color;

out vec4 dstColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
dstColor = color;
gl_Position = projection * view * model * vec4(position,0.0,1.0);
}
