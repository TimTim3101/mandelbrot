#version 330 core

in vec2 uv;
out vec4 FragColor;

uniform float scale;
uniform float time;
uniform float centerX;
uniform float centerY;

void main() {

    float re = (uv.x - .6f) * scale * 1.75 + centerX;
    float im = (uv.y - .5f) * scale - centerY;

    // ===== Множество Мандельброта =====
    // vec2 c = vec2(re, im);
    // vec2 z = vec2(0.0f, 0.0f);

    // ===== Множество Жюлиа =====
    vec2 c = vec2(re, im);

    // smt like an animation
    // float re_t, im_t = 0.08f;
    // vec2 c = vec2(0.3f + cos(1/time)*sin(time * re_t), cos(1/time)*sin(time * im_t));
    vec2 z = vec2(cos(0.15f * time), cos(0.15f * time));

    // vec2 c = vec2(-0.7f, 0.27015f); // default
    // vec2 c = vec2(-0.8f, 0.156f);
    // vec2 c = vec2(-0.4f, 0.6f);
    // vec2 c = vec2(0.285f * sin(0.15f * time), 0.01f * sin(0.15f * time));
    // vec2 c = vec2(0.285f, 0.01f);
    // vec2 c = vec2(-0.7269f, 0.1889f);
    // vec2 c = vec2(-0.3192f, 0.6117f);

    int it = 0;

    while (it < 350) {

        // z -> z^2 + c
        // x + iy -> (x + iy)^2 + c = x^2 + 2ixy - y^2 + c
        // x + iy -> ( x^2 - y^2 ) + ( 2ixy ) + c

        z = vec2(z.x * z.x - z.y * z.y, 2.f * z.x * z.y) + c;

        if (dot(z,z) >= 4.0f) break;
        ++it;
    }
    float m = it - log2(log(length(z)));
    float t = m / 350.0f;

    // ===== Синусоидальная палитра =====
    // float r = sin(t * 6.28318f);
    // float g = sin((t + 0.33f) * 6.28318f);
    // float b = sin((t + 0.67f) * 6.28318f);
    // FragColor = vec4(r, 1.0f - g, b, 1.0f);
    // FragColor = vec4(1.0f - r, g, b, 1.0f);
    // FragColor = vec4(r, g, 1.0f - b, 1.0f);
    // FragColor = vec4(1.0f - r, g, 1.0f - b, 1.0f);
    
    // ===== Циклическая радуга =====
    float r = clamp(abs(t * 6.0f - 3.0f) - 1.0f, 0.0f, 1.0f);
    float g = clamp(2.0f - abs(t * 6.0f - 2.0f), 0.0f, 1.0f);
    float b = clamp(2.0f - abs(t * 6.0f - 4.0f), 0.0f, 1.0f);
    // FragColor = vec4(r, g, b, 1.0f);
    // FragColor = vec4(r, 1.0f - g, 1.0f - b, 1.0f);
    // FragColor = vec4(1.0f - r, 1.0f - g, b, 1.0f);
    FragColor = vec4(1.0f - r, g, 1.0f - b, 1.0f);

    // ===== Радуга с контрастом =====
    // vec3 color;
    // color.r = sin(3.14159 * t * 2.0f) * 0.8f + 0.5f;
    // color.g = sin(3.14159 * t * 2.0f + 2.094f) * 0.8f + 0.5f;
    // color.b = sin(3.14159 * t * 2.0f + 4.188f) * 0.8f + 0.5f;
    // FragColor = vec4(color, 1.0f);

    // ===== Сглаживание итераций =====
    // float smooth_t = float(it) - log2(log(dot(z,z))) / log2(2.0f);
    // smooth_t = clamp(smooth_t / 350.0f, 0.0f, 1.0f);
    // FragColor = vec4(smooth_t, smooth_t * smooth_t, smooth_t, 1.0f);

    // ===== Бирюзовая схема =====
    // FragColor = vec4(t*t, t, t, 1.0f);

    // ===== Бирюзовый градиент =====
    // FragColor = vec4(0.0f, t, t, 1.0f);

    // ===== Инвертированный бирюзовый градиент =====
    // FragColor = vec4(0.0f, 1.0f - t, 1.0f - t, 1.0f);
    
    // ===== Розовая схема =====
    // FragColor = vec4(t, t*t, t, 1.0f);

    // ===== Розовый градиент =====
    // FragColor = vec4(t, 0.0f, t, 1.0f);

    // ===== Инвертированный розовый градиент =====
    // FragColor = vec4(1.0f - t, 0.0f, 1.0f - t, 1.0f);

    // ===== Золотая схема =====
    // FragColor = vec4(t, t, t*t, 1.0f);

    // ===== Жёлтый градиент =====
    // FragColor = vec4(t, t, 0.0f, 1.0f);

    // ===== Инвертированный жёлтый градиент =====
    // FragColor = vec4(1.0f - t, 1.0f - t, 0.0f, 1.0f);

    // ===== Зелёная схема =====
    // FragColor = vec4(t*t, t, t*t, 1.0f);

    // ===== Зелёный градиент =====
    // FragColor = vec4(0.0f, t, 0.0f, 1.0f);

    // ===== Инвертированный зелёный градиент =====
    // FragColor = vec4(0.0f, 1.0f - t, 0.0f, 1.0f);

    // ===== Красная схема =====
    // FragColor = vec4(t, t*t, t*t, 1.0f);

    // ===== Красный градиент =====
    // FragColor = vec4(t, 0.0f, 0.0f, 1.0f);

    // ===== Инвертированный красный градиент =====
    // FragColor = vec4(1.0f - t, 0.0f, 0.0f, 1.0f);

    // ===== Монохромный (Ч/Б) =====
    // FragColor = vec4(t*t, t*t, t*t, 1.0f);

    // ===== Инвертированный монохромный (Ч/Б) =====
    // FragColor = vec4(1.0f - t*t, 1.0f - t*t, 1.0f - t*t, 1.0f);
}
