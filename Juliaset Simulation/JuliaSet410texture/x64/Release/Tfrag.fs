#version 410

in vec4 dstColor;
in vec2 texCoordinate;

uniform sampler2D tex;
out vec4 finalcolor;

void main(){
//finalcolor = dstColor;
finalcolor = texture(tex, texCoordinate).rgba;
//finalcolor = texture(tex, texCoordinate).rgba * dstColor;
}
