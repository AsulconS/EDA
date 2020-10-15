#include <cubeMesh.hpp>

bool  CubeMesh::s_hasLazyLoaded {false};
float CubeMesh::s_primitiveMesh[CUBE_MESH_VERTEX_DATA_SIZE] {};

CubeMesh::CubeMesh()
    : m_VAO {0},
      m_VBO {0}
{
    if(!s_hasLazyLoaded)
    {
        loadPrimitiveData();
        s_hasLazyLoaded = true;
    }

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(s_primitiveMesh), s_primitiveMesh, GL_STATIC_DRAW);

    // 0. Pos Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // 1. UV Coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

CubeMesh::~CubeMesh()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VBO);
}

void CubeMesh::draw(const Shader& shader)
{
    shader.use();
    glBindVertexArray(m_VAO);
        glCullFace(GL_FRONT);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glCullFace(GL_BACK);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void CubeMesh::loadPrimitiveData()
{
    int index {0};
    std::ifstream file;
    file.open("cube.mesh");

    if(file.is_open())
    {
        float fin;
        while(file.good() && index < CUBE_MESH_VERTEX_DATA_SIZE)
        {
            file >> fin;
            s_primitiveMesh[index] = fin;
            ++index;
        }
    }
    else
    {
        std::cerr << "cube.mesh is corrupted or does not exist" << std::endl;
    }

    file.close();
}
