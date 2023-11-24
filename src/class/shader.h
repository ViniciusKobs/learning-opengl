#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "types.h"

class Shader
{
    public:
        Shader(const char* vertexPath, const char* fragmentPath, bool* success);
        ~Shader();

        void Use();
        unsigned int GetID();

    protected:

    private:
        U32 ID;

        void CheckCompileErrors(unsigned int shader, std::string type, bool* success);
};

#endif // SHADER_H
