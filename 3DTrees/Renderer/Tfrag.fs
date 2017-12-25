#version 410

in vec4 dstColor;
in vec2 texCoordinate;

uniform sampler2D tex;
out vec4 finalcolor;

void main(){

finalcolor = texture(tex, texCoordinate).rgba;

}
