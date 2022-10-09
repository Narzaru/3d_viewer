#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 24) out;

uniform vec2 ScreenSize;
uniform int DrawType;

void ReplaceVerticesWithCircle(vec4 position, float len) {
    position.x = position.x / position.w;
    position.y = position.y / position.w;
    position.z = position.z / position.w;
    position.w = 1.0;

    float width = ScreenSize.x;
    float height = ScreenSize.y;

    float x_len = len * height / width;
    float y_len = len;

    gl_Position = position + vec4(-x_len, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(-sqrt(2) / 2 * x_len, sqrt(2) / 2 * y_len, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(-sqrt(2) / 2 * x_len, -sqrt(2) / 2 * y_len, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(0.0, y_len, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(0.0, -y_len, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(sqrt(2) / 2 * x_len, sqrt(2) / 2 * y_len, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(sqrt(2) / 2 * x_len, -sqrt(2) / 2 * y_len, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(x_len, 0.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}

void ReplaceVerticesWithSquare(vec4 position, float len) {
    position.x = position.x / position.w;
    position.y = position.y / position.w;
    position.z = position.z / position.w;
    position.w = 1.0;

    float width = ScreenSize.x;
    float height = ScreenSize.y;

    float x_len = len * height / width;
    float y_len = len;

    gl_Position = position + vec4(-x_len, y_len, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(-x_len, -y_len, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(x_len, y_len, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(x_len, -y_len, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}

void main() {
    float CircleSize = 0.01;
    if (DrawType == 0) {
        for (int i = 0; i < 3; ++i) {
            ReplaceVerticesWithCircle(gl_in[i].gl_Position, CircleSize);
        }
    } else if (DrawType == 1) {
        for (int i = 0; i < 3; ++i) {
            ReplaceVerticesWithSquare(gl_in[i].gl_Position, CircleSize);
        }
    }
}
