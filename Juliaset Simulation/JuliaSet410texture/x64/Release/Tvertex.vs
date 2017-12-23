#version 410

layout(location = 0) in  vec3 position;
layout(location = 1) in  vec4 color;
layout(location = 2) in  vec2 textureCoordinate;

out vec4 dstColor;
out vec2 texCoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
texCoordinate = textureCoordinate;
dstColor = color;
gl_Position = projection * view * model * vec4(position,1.0);
}
