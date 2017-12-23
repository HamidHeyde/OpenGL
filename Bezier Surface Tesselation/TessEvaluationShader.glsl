#version 410

//the first parameter specifies our abstract patch is a quad (other options: triangles, isolines)
//the second parameter specifies the tessellation method, but it only matters when the tessellation factors are not integers
//the third parameter specifies that the generated triangles should have counter-clockwise winding
layout(quads, equal_spacing, ccw) in;
//you may need to change the triangle winding order depending on your implementation of the assignment

//control points received from the tessellation control shader
in vec3 tcPosition[];

//per-patch inputs received from the tessellation control shader

patch in vec3 patchColor;

//uniform variables

uniform mat4 matWorld;
uniform mat4 matView;
uniform mat4 matProjection;

out vec3 teViewNormal;
out vec3 teToEye;
out vec3 teColor;

/*
Implicitly defined:

in vec3 gl_TessCoord; //coordinates of the current point on the abstract patch (only x & y are used for quads and isolines)
in int gl_PatchVerticesIn; //number of control points in patch received from tessellation control shader
in int gl_PrimitiveID; //index of the current patch received from tessellation control shader
out vec4 gl_Position;
*/

void BezierCoreMat(out mat4 Core_x, out mat4 Core_y, out mat4 Core_z) 
{
		mat4 Base = mat4(
				-1, 3, -3, 1,
				 3, -6, 3, 0,
				-3, 3, 0, 0,
				 1, 0, 0, 0);
	
		mat4 Base_Transposed = transpose(Base);

		mat4 Point_x = mat4(
			tcPosition[0].x, tcPosition[1].x, tcPosition[2].x, tcPosition[3].x, 
			tcPosition[4].x, tcPosition[5].x, tcPosition[6].x, tcPosition[7].x, 
			tcPosition[8].x, tcPosition[9].x, tcPosition[10].x, tcPosition[11].x, 
			tcPosition[12].x, tcPosition[13].x, tcPosition[14].x, tcPosition[15].x );

		mat4 Point_y = mat4(
			tcPosition[0].y, tcPosition[1].y, tcPosition[2].y, tcPosition[3].y, 
			tcPosition[4].y, tcPosition[5].y, tcPosition[6].y, tcPosition[7].y, 
			tcPosition[8].y, tcPosition[9].y, tcPosition[10].y, tcPosition[11].y, 
			tcPosition[12].y, tcPosition[13].y, tcPosition[14].y, tcPosition[15].y );

		mat4 Point_z = mat4(
			tcPosition[0].z, tcPosition[1].z, tcPosition[2].z, tcPosition[3].z, 
			tcPosition[4].z, tcPosition[5].z, tcPosition[6].z, tcPosition[7].z, 
			tcPosition[8].z, tcPosition[9].z, tcPosition[10].z, tcPosition[11].z, 
			tcPosition[12].z, tcPosition[13].z, tcPosition[14].z, tcPosition[15].z );


		Core_x = Base * Point_x * Base_Transposed;
		Core_y = Base * Point_y * Base_Transposed;
		Core_z = Base * Point_z * Base_Transposed;
}

void main()
{
	//TODO
	
	//--------------Position W element
	gl_Position.w = 1;
	//--------------Color
	teColor =  patchColor;

	

	//--------------U and V Positions
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;


	//--------------Calculating The Points
	//--------------//--------------//--------------

	
	mat4 cx, cy, cz;
	BezierCoreMat(cx, cy, cz);

	mat4 dxv, dyv, dzv;
	mat4 dxu, dyu, dzu;

	dxv = dxu = cx;
	dyv = dyu = cy;
	dzv = dzu = cz;

    vec4 U = vec4(u*u*u, u*u, u, 1);
    vec4 V = vec4(v*v*v, v*v, v, 1);

    float x = dot(cx * V, U);
    float y = dot(cy * V, U);
    float z = dot(cz * V, U);
    
	gl_Position.xyz = -vec3(x, y, z);


	//--------------Positioning The Points
	//--------------//--------------//--------------
	//Model
	gl_Position = matWorld * gl_Position;
	//View
	gl_Position = matView * gl_Position;

	//--------------To Eye
	teToEye = -normalize(gl_Position.xyz);

	//Projection
	gl_Position = matProjection * gl_Position;


	//--------------Calculating The Normal
	//--------------//--------------//--------------

	//--------------derivitive U
	vec4 dUu = vec4(3*u*u, 2*u, 1, 0);
    vec4 dVu = vec4(v*v*v, v*v, v, 1);

	float xu = dot(dxu * dVu, dUu);
    float yu = dot(dyu * dVu, dUu);
    float zu = dot(dzu * dVu, dUu);
	
	vec3 uElement = vec3 (xu,yu,zu);

	//--------------derivitive V
	vec4 dUv = vec4(u*u*u, u*u, u, 1);
    vec4 dVv = vec4(3*v*v, 2*v, 1, 0);

	float xv = dot(dxv * dVv, dUv);
    float yv = dot(dyv * dVv, dUv);
    float zv = dot(dzv * dVv, dUv);

	vec3 vElement = vec3 (xv,yv,zv);

	//--------------NORMAL
	vec3 norm = normalize(cross(uElement,vElement));

	//--------------Normal to Clip Space
	mat3 normalTransform = mat3(matView * matWorld);
	teViewNormal = normalize(normalTransform * norm);

}