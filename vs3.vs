#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float brightness; //Adjusts the color of the vertices by multiplying in some positive value
uniform vec3 originLoc; //Provides the source of a ripple for distance calculations

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor * (1 + 0.8 * (1/(.0000001+(abs(distance(abs(distance(aPos, originLoc)), brightness))))));
}