#version 330 core
out vec4 FragColor;
in vec4 color;

float near = 0.1;
float far  = 10.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // обратно к NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main() {
        float depth = LinearizeDepth(gl_FragCoord.z) / far;
        FragColor = vec4(vec3(depth), 1.0);
}