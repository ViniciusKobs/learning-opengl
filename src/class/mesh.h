#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <memory>
#include <glad/gl.h>

#include <gtc/type_ptr.hpp>

#include "types.h"

struct VAttrib
{
    GLint asize;
    GLenum type;
    GLsizei stride;
};

struct Mesh {
    std::vector<float> vertices;
    std::vector<U32> indices;
    VAttrib attrib;
    GLenum mode;
    GLsizei vcount;
    GLsizei icount;
    glm::vec3 worldPos;
};

std::vector<Mesh> createMeshes();

#endif // MESH_H
