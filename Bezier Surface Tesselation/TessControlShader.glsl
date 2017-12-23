#version 410

//per-vertex attributes for the entire patch
//these come from the vertex shader
in vec3 vsPosition[]; //size of array = number of control points in input patch

//tessellation levels chosen by the user

uniform float customOuterTessFactor;
uniform float customInnerTessFactor;

//specifies that the output patch will have 16 control points
layout(vertices = 16) out;

//per-control point outputs

out vec3 tcPosition[];//size of array = number of control points in output patch

//per-patch outputs

patch out vec3 patchColor;

/*
Implicitly defined variables:

in int gl_PrimitiveID; //index of the current output patch
in int gl_InvocationID; //index of the current output control point in the current output patch
in int gl_PatchVerticesIn; //number of control points in input patch

patch out float gl_TessLevelOuter[4];
patch out float gl_TessLevelInner[2];
*/

void main()
{
	//TODO
	//per-output-control-point stuff
	tcPosition[gl_InvocationID] = vsPosition[gl_InvocationID];

	//per-patch stuff
	//It does not matter that the same thing will be executed for every output control point,
	//because it is done in parallel, so time is not wasted

	gl_TessLevelOuter[0] = customOuterTessFactor;
	gl_TessLevelOuter[1] = customOuterTessFactor;
	gl_TessLevelOuter[2] = customOuterTessFactor;
	gl_TessLevelOuter[3] = customOuterTessFactor;

	gl_TessLevelInner[0] = customInnerTessFactor;
	gl_TessLevelInner[1] = customInnerTessFactor;

	vec3 col[7];
	col[0] = vec3(1.0,1.0,1.0);
	col[1] = vec3(0.0,0.0,1.0);
	col[2] = vec3(0.0,1.0,0.0);
	col[3] = vec3(1.0,0.0,0.0);
	col[4] = vec3(0.0,1.0,1.0);
	col[5] = vec3(1.0,0.0,1.0);
	col[6] = vec3(1.0,1.0,0.0);
	

	
	int j=0;
	int counter = gl_PrimitiveID;
	while (counter>7){counter = counter - 7;}
	j = j + counter;




	
	patchColor = col[j];

}