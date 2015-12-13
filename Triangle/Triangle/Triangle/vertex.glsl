#version 330

// Mesh variables
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec2 vertTexUV;
layout (location = 2) in vec3 vertNorm;
out vec2 fragTexUV;
out vec3 fragPos;
out vec3 fragNorm;

//uniform mat4 model;
//uniform mat4 camera;
uniform mat4 worldMatrix;

void main()
{
	 gl_Position = worldMatrix * vec4(vertPos, 1);
	 //gl_Position = camera * model * vec4(vertPos, 1); 
	 fragTexUV = vertTexUV;
	 fragPos = gl_Position.xyz;
	 fragNorm = normalize(vertNorm);
}