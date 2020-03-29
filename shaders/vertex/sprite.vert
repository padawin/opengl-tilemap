#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float width;
uniform float height;

void main()
{
	vec3 pos = aPos;
	pos.x *= width;
	pos.y *= height;
	pos.x -= width * 0.5f;
	gl_Position = projection * view * model * vec4(pos, 1.0);
	TexCoord = aTextCoord;
}
