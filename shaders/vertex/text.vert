#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;

out vec2 TexCoord;

uniform int screenWidth;
uniform int screenHeight;
uniform float cameraWidth;
uniform float cameraHeight;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool isUI;

void main()
{
	vec2 ratio = vec2(
		screenWidth / cameraWidth,
		screenHeight / cameraHeight
	);
	if (isUI) {
		gl_Position = projection * model * vec4(aPos, 1.0);
	}
	else {
		vec3 pos = vec3(aPos.xy - ratio, aPos.z);

		pos.xy /= ratio;
		gl_Position = projection * view * model * vec4(pos.xy, 0.01, 1.0);
	}
	TexCoord = aTextCoord;
}
