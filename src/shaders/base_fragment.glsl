#version 330 core
in vec4 color;

void main() {
    gl_FragColor = vec4(color.rgb, 1.0);
}
