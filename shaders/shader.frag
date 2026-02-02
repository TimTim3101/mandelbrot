#version 330 core

in vec2 uv;
out vec4 FragColor;

uniform float scale;
uniform float centerX;
uniform float centerY;

void main() {

    float re = (uv.x - .6f) * scale * 1.75 + centerX;
    float im = (uv.y - .5f) * scale - centerY;

    vec2 c = vec2(re,im);
    vec2 z = vec2(0.f, 0.f);
    int iterations = 0;

    while (iterations < 300) {
        z = vec2(z.x * z.x - z.y * z.y,
                 2.f * z.x * z.y
        ) + c;

        // dot(z,z) = z.x * z.x + z.y * z.y
        if (dot(z,z) > 4.f) break;
        ++iterations;
    }
    float t = float(iterations) / 300.;
    FragColor = vec4(t, t, t*t, 1.f);
}
