#include "renderer.h"

Renderer::Renderer(bool* success)
{
    if (!gladLoadGL(glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      *success = false;
    }
}

Renderer::~Renderer()
{
    for (U32 i = 0; i < objects.size(); i++) {
        glDeleteVertexArrays(1, &objects[i].VAO);
        glDeleteBuffers(1, &objects[i].VBO);
    }

}

void Renderer::CreateObject(Mesh mesh) {
    glm::mat4 identity = glm::mat4(1.0f);
    RenderObject obj = {0, 0, 0, mesh.mode, mesh.icount, glm::translate(identity, mesh.worldPos)};

    glGenVertexArrays(1, &obj.VAO);
    glGenBuffers(1, &obj.VBO);
    glGenBuffers(1, &obj.EBO);

    glBindVertexArray(obj.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, obj.VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.EBO);

    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float), mesh.vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, mesh.attrib.asize, mesh.attrib.type, GL_FALSE, mesh.attrib.stride, (void*)0);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(U32), mesh.indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    objects.push_back(obj);
}

void Renderer::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(GLuint EBO, GLuint VAO, GLenum mode, GLsizei vcount, U32 id) {
    int modelLoc = glGetUniformLocation(id, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(id, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int projectionLoc = glGetUniformLocation(id, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(mode, vcount, GL_UNSIGNED_INT, 0);
}

void Renderer::DrawObjects(U32 id) {
    for (U32 i = 0; i < objects.size(); i++) {
        SetModelMat(objects[i].model);
        Draw(objects[i].EBO, objects[i].VAO, objects[i].mode, objects[i].icount, id);
    }
}

void Renderer::SetWireframeMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::SetModelMat(glm::mat4 mat) {
    model = mat;
}
void Renderer::SetViewMat(glm::mat4 mat) {
    view = mat;
}
void Renderer::SetProjectionMat(glm::mat4 mat) {
    projection = mat;
}
