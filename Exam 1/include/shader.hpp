#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdio>
#include <cstring>
#include <iostream>

class Shader
{
public:
    Shader(const char* shaderName);
    ~Shader();

    void use() const;

    void setFloat(const char* name, float x);

    void setVec2(const char* name, float x, float y);
    void setVec3(const char* name, float x, float y, float z);
    void setVec4(const char* name, float x, float y, float z, float w);

    void setMat2(const char* name, const glm::mat2& m);
    void setMat3(const char* name, const glm::mat3& m);
    void setMat4(const char* name, const glm::mat4& m);

private:
    bool m_flag;
    GLuint m_vs;
    GLuint m_fs;
    GLuint m_shader;

    char* m_vsSrc;
    char* m_fsSrc;

    bool loadShaderFromFile(char** srcTarget, const char* path);

    void compileShader(GLuint* shader, const char* type);
    void linkProgram();
};

#endif // SHADER_HPP
