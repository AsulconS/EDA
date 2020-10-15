#ifndef CUBE_MESH_HPP
#define CUBE_MESH_HPP

#include <glad/glad.h>

#include <shader.hpp>

#include <fstream>
#include <iostream>

#define CUBE_MESH_VERTEX_DATA_SIZE 180

class CubeMesh
{
public:
    CubeMesh();
    ~CubeMesh();

    void draw(const Shader& shader);

private:
    void loadPrimitiveData();

    GLuint m_VAO;
    GLuint m_VBO;

    static bool  s_hasLazyLoaded;
    static float s_primitiveMesh[CUBE_MESH_VERTEX_DATA_SIZE];
};

#endif // CUBE_MESH_HPP
