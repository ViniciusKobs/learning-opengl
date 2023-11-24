#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "mesh.h"
#include "types.h"

struct RenderObject
{
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLenum mode;
    GLsizei icount;
    glm::mat4 model;
};

class Renderer
{
    public:
        Renderer(bool* success);
        ~Renderer();

        void CreateObject(Mesh mesh);

        void Clear(float r, float g, float b, float a);
        void DrawObjects(U32 id);

        void SetWireframeMode();
        void SetModelMat(glm::mat4 mat);
        void SetViewMat(glm::mat4 mat);
        void SetProjectionMat(glm::mat4 mat);

    protected:

    private:
        std::vector<RenderObject> objects;
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        void Draw(GLuint ebo, GLuint vao, GLenum mode, GLsizei icount, U32 id);
};

#endif // RENDERER_H
