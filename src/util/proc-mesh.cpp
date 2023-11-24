#include "proc-mesh.h"

Mesh createSphereMesh(U32 detail, glm::vec3 pos) {
    std::vector<float> vertices = {};
    std::vector<U32> indices = {};

    double angle = (2 * PI) / detail;
    U32 numLat = (detail / 4) - 1;

    for (U32 i = 0; i < (numLat * 2) + 1; i++) {
        for (U32 j = 0; j < detail; j++) {
            double latSin = std::sin(angle * (int)(numLat - i));
            double latCos = std::cos(angle * (int)(numLat - i));

            vertices.push_back(std::cos(angle * j) * latCos); // X
            vertices.push_back(latSin);                       // Y
            vertices.push_back(std::sin(angle * j) * latCos); // Z

            indices.push_back(j + (detail * i));
            indices.push_back(((j + 1) % detail) + (detail * i));
        }
    }
    for (U32 i = 0; i < numLat * 2; i++) {
        for (U32 j = 0; j < detail; j++) {
            indices.push_back(j + (detail * i));
            indices.push_back(j + (detail * (i + 1)));
        }
    }
    vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f);
    vertices.push_back(0.0f); vertices.push_back(-1.0f); vertices.push_back(0.0f);
    for (U32 i = 0; i < detail; i++) {
        indices.push_back((vertices.size() / 3) - 2); indices.push_back(i);
        indices.push_back((vertices.size() / 3) - 1); indices.push_back(i + (detail * numLat * 2));
    }

    return {
        vertices,
        indices,
        {3, GL_FLOAT, 3 * sizeof(float)},
        GL_LINES,
        vertices.size() / 3,
        indices.size(),
        pos
    };
}
