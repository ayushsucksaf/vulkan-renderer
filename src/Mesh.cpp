#include "Mesh.h"
#include <cmath>

// --- cube ---
// 8 corners, 6 faces, 2 triangles per face = 12 triangles = 36 indices
// we reuse vertices via index buffer instead of repeating them
Mesh Mesh::cube(glm::vec3 color) {
    Mesh m;
    m.vertices = {
        {{ -0.5f, -0.5f,  0.5f }, color},
        {{  0.5f, -0.5f,  0.5f }, color},
        {{  0.5f,  0.5f,  0.5f }, color},
        {{ -0.5f,  0.5f,  0.5f }, color},
        {{ -0.5f, -0.5f, -0.5f }, color},
        {{  0.5f, -0.5f, -0.5f }, color},
        {{  0.5f,  0.5f, -0.5f }, color},
        {{ -0.5f,  0.5f, -0.5f }, color},
    };
    m.indices = {
        0, 1, 2, 2, 3, 0,  // front
        4, 6, 5, 6, 4, 7,  // back
        4, 5, 1, 1, 0, 4,  // bottom
        3, 2, 6, 6, 7, 3,  // top
        4, 0, 3, 3, 7, 4,  // left
        1, 5, 6, 6, 2, 1,  // right
    };
    return m;
}

// --- sphere ---
// math: parametric sphere using spherical coordinates
// a point on a sphere is defined by two angles:
//   theta (φ) — vertical angle from top (0 to π)
//   phi   (θ) — horizontal angle around (0 to 2π)
// x = r * sin(φ) * cos(θ)
// y = r * sin(φ) * sin(θ)
// z = r * cos(φ)
// stacks = horizontal rings, slices = vertical columns
Mesh Mesh::sphere(int stacks, int slices, glm::vec3 color) {
    Mesh m;
    const float PI = 3.14159265358979f;

    for (int i = 0; i <= stacks; i++) {
        float phi = PI * i / stacks;  // 0 to π
        for (int j = 0; j <= slices; j++) {
            float theta = 2.0f * PI * j / slices;  // 0 to 2π

            float x = sin(phi) * cos(theta);
            float y = sin(phi) * sin(theta);
            float z = cos(phi);

            // color based on position for visual variety
            m.vertices.push_back({ { x * 0.5f, y * 0.5f, z * 0.5f }, color });
        }
    }

    // connect the rings with triangles
    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            uint16_t a = i * (slices + 1) + j;
            uint16_t b = a + slices + 1;

            m.indices.push_back(a);
            m.indices.push_back(b);
            m.indices.push_back(a + 1);

            m.indices.push_back(b);
            m.indices.push_back(b + 1);
            m.indices.push_back(a + 1);
        }
    }
    return m;
}

// --- pyramid ---
// 5 vertices: 4 base corners + 1 apex at top
// base is a square, 4 triangular sides + 2 triangles for the base
Mesh Mesh::pyramid(glm::vec3 color) {
    Mesh m;
    m.vertices = {
        {{ -0.5f, -0.5f, 0.0f }, color},  // base — front left
        {{  0.5f, -0.5f, 0.0f }, color},  // base — front right
        {{  0.5f,  0.5f, 0.0f }, color},  // base — back right
        {{ -0.5f,  0.5f, 0.0f }, color},  // base — back left
        {{  0.0f,  0.0f, 1.0f }, color},  // apex
    };
    m.indices = {
        0, 2, 1, 0, 3, 2,  // base — fixed winding
        0, 1, 4,            // front side
        1, 2, 4,            // right side
        2, 3, 4,            // back side
        3, 0, 4,            // left side
    };
    return m;
}