#ifndef PROC-MESH_H_INCLUDED
#define PROC-MESH_H_INCLUDED

# define PI 3.14159265358979323846

#include <iostream>
#include <vector>
#include <cmath>

#include "mesh.h"
#include "types.h"

Mesh createSphereMesh(U32 detail, glm::vec3);

#endif // PROC-MESH_H_INCLUDED
