#version 410

in vec2 uv;
uniform sampler2D planeTex;
out vec4 color;

#define M_PI 3.141592653589793
#define epsilon 0.0001f
#define saturate(x) clamp(x, 0, 1)

const vec3 eyePosition = vec3(0, 0, 0);
const float fovHalfAngle = M_PI / 8;

const vec3 planePoint = vec3(0, -1, -4);
const vec3 planeNormal = normalize(vec3(0, 1, 1));
const vec3 planeTangent = normalize(vec3(1, 0, 0));
const vec3 planeBitangent = normalize(vec3(0, 1, -1));

const vec3 sphereCenter = vec3(0, 0, -4);
const float sphereRadius = 0.75;

const float beamWidth = 2;
const float beamIntensity = 300;

const vec3 beamCenter = vec3(5, 5, 3);

const vec3 beamCenter1 = vec3(5, 5, 4);
const vec3 beamCenter2 = vec3(5, 5, 3);
const vec3 beamCenter3 = vec3(5, 5, 6);
const vec3 beamCenter4 = vec3(5, 5, 7);

const vec3 sphereColor = vec3(0.8, 0.8, 0.8);
const vec3 lightColor = vec3(1, 1, 1);

const float sphereReflectivity = 0.8;
const float planeReflectivity = 0.1;

//returns texture coordinates for a given point on the plane
vec2 getPlaneTexCoords(vec3 contactPoint)
{
	vec3 disp = contactPoint - planePoint;
	return 0.2 * vec2(dot(disp, planeTangent), 1 - dot(disp, planeBitangent));
}

//suggested helper functions

bool rayPlaneIntersection(vec3 rayOrigin, vec3 rayDir,
	out vec3 contactPoint)
	{
		bool result;

		float Condition = (rayDir.x * planeNormal.x) + (rayDir.y * planeNormal.y) + (rayDir.z * planeNormal.z);

		if(Condition == 0.0)
		{
			
			result = false;
		}
		else
		{

			float t = (((planeNormal.x*rayOrigin.x) + (planeNormal.y*rayOrigin.y) + (planeNormal.z*rayOrigin.z)) + 
			(-((planeNormal.x*planePoint.x)+(planeNormal.y*planePoint.y)+(planeNormal.z*planePoint.z))));

			t = t * -1;
			t = t / Condition;

			//Intersection Point
			contactPoint.x = rayDir.x * t  + rayOrigin.x;
			contactPoint.y = rayDir.y * t  + rayOrigin.y;
			contactPoint.z = rayDir.z * t  + rayOrigin.z;

			result = true;
		}

		return result;
	}

bool raySphereIntersection(vec3 rayOrigin, vec3 rayDir,
	out vec3 contactPoint, out vec3 contactNormal)
	{
		bool result;

		float a = (rayDir.x*rayDir.x) + (rayDir.y*rayDir.y) + (rayDir.z*rayDir.z); 

		float b = 2* ((rayDir.x * (rayOrigin.x-sphereCenter.x))+(rayDir.y * (rayOrigin.y-sphereCenter.y))+(rayDir.z * (rayOrigin.z-sphereCenter.z)));
		
		float c = ((sphereCenter.x*sphereCenter.x) + (sphereCenter.y*sphereCenter.y) +(sphereCenter.z*sphereCenter.z));
		c = c + ((rayOrigin.x*rayOrigin.x)+(rayOrigin.y*rayOrigin.y)+(rayOrigin.z*rayOrigin.z));
		c = c - 2*((sphereCenter.x*rayOrigin.x)+(sphereCenter.y*rayOrigin.y)+(sphereCenter.z*rayOrigin.z));
		c = c  - (sphereRadius*sphereRadius);


		float delta  = (b*b) - (4*(a*c));

		if(delta > 0.0) 
		{
			float t;
			float t1 = (-b - sqrt(delta)) / (2.0 * a);
			float z1 = rayDir.z * t1;

			float t2 = (-b + sqrt(delta)) / (2.0 * a);
			float z2 = rayDir.z * t2;

			if (z2>z1) {t = t2;}
			else {t = t1;}

			t = t1;
			
			
			//???????????????? Calculate Intersection Point ????????????????
			contactPoint.x = rayDir.x * t + rayOrigin.x;
			contactPoint.y = rayDir.y * t + rayOrigin.y;
			contactPoint.z = rayDir.z * t + rayOrigin.z;

			//???????????????? Calculate Normal at Point????????????????
			contactNormal = normalize ((contactPoint - sphereCenter) /sphereRadius);
			
			result = true;
		}
		else
		{
			result = false;
		}

		return result;
	}

vec3 getOneBounceColor(vec3 rayDir, vec3 contactPoint, vec3 contactNormal, vec3 lightPos, bool sphere)
{
	float spec=0.0;
	vec3 OutgoingRayReflection = normalize(reflect(rayDir, contactNormal));
	vec3 PointLightVector = normalize(lightPos - contactPoint);

	

	if (sphere)
	{
		spec = max(dot(OutgoingRayReflection, PointLightVector),0.0);
		spec +=  pow(spec, sphereReflectivity);
	}
	else
	{
		vec3 OutRaySphereContactPoint;
		vec3 OutRaySphereContactNormal;

		if(raySphereIntersection(contactPoint, PointLightVector, OutRaySphereContactPoint, OutRaySphereContactNormal)== false)
		{
			spec = max(dot(OutgoingRayReflection, PointLightVector),0.0);
			spec +=  pow(spec, planeReflectivity);
		}
	}

	return (spec * lightColor);
}

vec3 getTwoBounceColor(vec3 rayDir, vec3 contactPoint, vec3 contactNormal, vec3 lightPos, bool sphere)
{
	vec3 result;
	
	if (sphere)
	{
		result = getOneBounceColor(rayDir, contactPoint, contactNormal, lightPos, true);

		vec3 RayPlaneContactPoint1;
		vec3 ReflectedOutgoingRay = normalize(reflect(rayDir,contactNormal));

		if (rayPlaneIntersection(contactPoint, ReflectedOutgoingRay, RayPlaneContactPoint1))
		{
			float linex = RayPlaneContactPoint1.x - contactPoint.x;
			float liney = RayPlaneContactPoint1.y - contactPoint.y;
			float linez = RayPlaneContactPoint1.z - contactPoint.z;

			float distance = sqrt((linex*linex) + (liney*liney) + (linez*linez));
			if (distance<1.38)
			{
				result = getOneBounceColor(ReflectedOutgoingRay, RayPlaneContactPoint1, planeNormal, lightPos, true); 
				result = result * texture(planeTex, getPlaneTexCoords(RayPlaneContactPoint1)).rgb;

			}
		}
	}
	else
	{
		

		result = getOneBounceColor(rayDir, contactPoint, contactNormal, lightPos, false);

		vec3 OutRaySphereContactPoint;
		vec3 OutRaySphereContactNormal;
		vec3 ReflectedOutgoingRay = normalize(reflect(rayDir,contactNormal));

		if(raySphereIntersection(contactPoint, ReflectedOutgoingRay, OutRaySphereContactPoint, OutRaySphereContactNormal))
		{
			result = result * lightColor * 1.08;
		}

	}

	return result;
}

void main()
{
	color = vec4(0, 0, 0, 1);
	const float divideBy = 400;

	vec3 incomingRayDirection = -normalize(vec3(uv * fovHalfAngle, -1.0));

	//TODO

	vec3 RaySphereContactPoint;
	vec3 RaySphereContactNormal;
	vec3 RayPlaneContactPoint;	
	
	float counter = 0;
	vec3 D = vec3(0.0,0.0,0.0);
	vec3 LightsSource[100];
	vec3 DoubleBounce[100];

	for (int i=0;i<100;i++)
	{
		LightsSource[i].x = beamCenter.x;
		LightsSource[i].y = beamCenter.y;
		LightsSource[i].z = beamCenter.z+(i*0.2);
		
		if(i>10) 
		{
			LightsSource[i].x = beamCenter.x+0.2;
			LightsSource[i].z = beamCenter.z+((i-10)*0.2);
		}
		if(i>20) 
		{
			LightsSource[i].x = beamCenter.x+0.4;
			LightsSource[i].z = beamCenter.z+((i-20)*0.2);
		}
		if(i>30) 
		{
			LightsSource[i].x = beamCenter.x+0.6;
			LightsSource[i].z = beamCenter.z+((i-30)*0.2);
		}
		if(i>40) 
		{
			LightsSource[i].x = beamCenter.x+0.8;
			LightsSource[i].z = beamCenter.z+((i-40)*0.2);
		}
		if(i>50) 
		{
			LightsSource[i].x = beamCenter.x+1.0;
			LightsSource[i].z = beamCenter.z+((i-50)*0.2);
		}
		if(i>60) 
		{
			LightsSource[i].x = beamCenter.x+1.2;
			LightsSource[i].z = beamCenter.z+((i-60)*0.2);
		}
		if(i>70) 
		{
			LightsSource[i].x = beamCenter.x+1.4;
			LightsSource[i].z = beamCenter.z+((i-70)*0.2);
		}
		if(i>80) 
		{
			LightsSource[i].x = beamCenter.x+1.6;
			LightsSource[i].z = beamCenter.z+((i-80)*0.2);
		}
		if(i>90) 
		{
			LightsSource[i].x = beamCenter.x+1.8;
			LightsSource[i].z = beamCenter.z+((i-90)*0.2);
		}
	}
	



	if (raySphereIntersection(eyePosition, -incomingRayDirection, RaySphereContactPoint, RaySphereContactNormal))
	{
		for (int i=0;i<100;i++)
		{
			DoubleBounce[i] = getTwoBounceColor(-incomingRayDirection, RaySphereContactPoint, RaySphereContactNormal, LightsSource[i], true);
			D += DoubleBounce[i];
			counter++;
		}

		D /= counter;


		color = vec4(sphereColor,1.0);
		color = color * vec4(D,1.0);

	}
	else if (rayPlaneIntersection(eyePosition, -incomingRayDirection, RayPlaneContactPoint))
	{
		for (int i=0;i<100;i++)
		{
			DoubleBounce[i] = getTwoBounceColor(-incomingRayDirection, RayPlaneContactPoint, planeNormal, LightsSource[i], false);
			D += DoubleBounce[i];
			counter++;
		}

		D /= counter;

		color = vec4(texture(planeTex, getPlaneTexCoords(RayPlaneContactPoint)).rgb,1.0);
		color = color * vec4(D,1.0);


	}

	//TODO

	color = color * beamIntensity;
	color.rgb = saturate(color.rgb / divideBy);

}