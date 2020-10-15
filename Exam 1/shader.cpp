#include <shader.hpp>

Shader::Shader(const char* shaderName)
    : m_vs     {0},
      m_fs     {0},
      m_shader {0},
      m_vsSrc  {nullptr},
      m_fsSrc  {nullptr}
{
    std::size_t pathLen {strlen(shaderName) + 4};

    char* path {new char[pathLen]};
    strcpy(path, shaderName);
    strcat(path, ". s");

    path[pathLen - 3] = 'v';
    m_flag = loadShaderFromFile(&m_vsSrc, path);
    path[pathLen - 3] = 'f';
    m_flag = loadShaderFromFile(&m_fsSrc, path);
    delete[] path;

    if(!m_flag)
    {
        m_vs = glCreateShader(GL_VERTEX_SHADER);
        m_fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_vs, 1, &m_vsSrc, nullptr);
        glShaderSource(m_fs, 1, &m_fsSrc, nullptr);

        compileShader(&m_vs, "Vertex Shader");
        compileShader(&m_fs, "Fragment Shader");

        linkProgram();
    }
}

Shader::~Shader()
{
    if(m_vsSrc != nullptr)
    {
        delete[] m_vsSrc;
    }
    if(m_fsSrc != nullptr)
    {
        delete[] m_fsSrc;
    }

    if(m_vs)
    {
        glDetachShader(m_shader, m_vs);
        glDeleteShader(m_vs);
    }
    if(m_fs)
    {
        glDetachShader(m_shader, m_fs);
        glDeleteShader(m_fs);
    }
    if(m_shader)
    {
        glDeleteProgram(m_shader);
    }
}

void Shader::use() const
{
    glUseProgram(m_shader);
}


void Shader::setFloat(const char* name, float x)
{
    glUniform1f(glGetUniformLocation(m_shader, name), x);
}

void Shader::setVec2(const char* name, float x, float y)
{
    glUniform2f(glGetUniformLocation(m_shader, name), x, y);
}

void Shader::setVec3(const char* name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(m_shader, name), x, y, z);
}

void Shader::setVec4(const char* name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_shader, name), x, y, z, w);
}

void Shader::setMat2(const char* name, const glm::mat2& m)
{
    glUniformMatrix3fv(glGetUniformLocation(m_shader, name), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setMat3(const char* name, const glm::mat3& m)
{
    glUniformMatrix3fv(glGetUniformLocation(m_shader, name), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setMat4(const char* name, const glm::mat4& m)
{
    glUniformMatrix4fv(glGetUniformLocation(m_shader, name), 1, GL_FALSE, glm::value_ptr(m));
}

bool Shader::loadShaderFromFile(char** srcTarget, const char* path)
{
    int c {0};
    int size {0};
    FILE* file {fopen(path, "r")};
    if(file)
    {
        while(getc(file) != EOF)
        {
            ++size;
        }
        *srcTarget = new char[size + 1];

        size = 0;
        rewind(file);
        while((c = getc(file)) != EOF)
        {
            (*srcTarget)[size] = c;
            ++size;
        }
        (*srcTarget)[size] = '\0';
        fclose(file);
        return 0;
    }
    std::cerr << "Failed Opening File " << path << std::endl;
    return 1;
}

void Shader::compileShader(GLuint* shader, const char* type)
{
    if(m_flag)
    {
        return;
    }

    int success;
    char infoLog[512];
    glCompileShader(*shader);
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(*shader, 512, nullptr, infoLog);
        std::cerr << "Failed to Compile " << type << '\n' << infoLog << std::endl;
        m_flag = 1;
    }
}

void Shader::linkProgram()
{
    if(m_flag)
    {
        return;
    }

    int success;
    char infoLog[512];
    m_shader = glCreateProgram();
    glAttachShader(m_shader, m_vs);
    glAttachShader(m_shader, m_fs);
    glLinkProgram(m_shader);
    glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(m_shader, 512, nullptr, infoLog);
        std::cerr << "Failed to Link Shader\n" << infoLog << std::endl;
        m_flag = 1;
    }
}
