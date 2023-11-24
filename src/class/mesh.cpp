#include "mesh.h"
#include "proc-mesh.h"

// FOR DEBUG
std::vector<Mesh> createMeshes() {
    std::vector<Mesh> meshes;

    std::vector<float> cubeVertices = {
        //top square
        -0.5f, 0.5f, -0.5f, // A0
        0.5f, 0.5f, -0.5f, // B1
        0.5f, 0.5f, 0.5f, // C2
        -0.5f, 0.5f, 0.5f, // D3
        //bottom square
        -0.5f, -0.5f, -0.5f, // E4
        0.5f, -0.5f, -0.5f, // F5
        0.5f, -0.5f, 0.5f, // G6
        -0.5f, -0.5f, 0.5f // H7
    };
    std::vector<U32> cubeIndices = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,

        4, 5,
        5, 6,
        6, 7,
        7, 4,

        0, 4,
        1, 5,
        2, 6,
        3, 7
    };

    Mesh cubeMesh = {
        cubeVertices,
        cubeIndices,
        {3, GL_FLOAT, 3 * sizeof(float)},
        GL_LINES,
        cubeVertices.size() / 3,
        cubeIndices.size(),
        glm::vec3(1.0f, 0.0f, 0.0f)
    };

    meshes.push_back(cubeMesh);
    meshes.push_back(createSphereMesh(40, glm::vec3(-1.0f, 0.0f, 0.0f)));

    return meshes;
}

