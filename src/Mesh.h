#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#endif //RENDER_MESH_H

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;

    // factory functions — each one explains its math
    static Mesh cube(glm::vec3 color = {1.0f, 1.0f, 1.0f});
    static Mesh sphere(int stacks, int slices, glm::vec3 color = {1.0f, 1.0f, 1.0f});
    static Mesh pyramid(glm::vec3 color = {1.0f, 1.0f, 1.0f});
};
