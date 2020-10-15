#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define  STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <shader.hpp>
#include <cubeMesh.hpp>
#include <octree.hpp>

#include <ctime>
#include <cstdlib>
#include <iostream>

bool qPress {false};
bool ePress {false};
bool wPress {false};
bool sPress {false};
bool aPress {false};
bool dPress {false};
bool zPress {false};
bool xPress {false};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        qPress = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE)
    {
        qPress = false;
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        ePress = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
    {
        ePress = false;
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        wPress = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
    {
        wPress = false;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        sPress = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
    {
        sPress = false;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        aPress = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
    {
        aPress = false;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        dPress = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
    {
        dPress = false;
    }
    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        zPress = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE)
    {
        zPress = false;
    }
    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        xPress = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE)
    {
        xPress = false;
    }
}

int main()
{
    // Intialize and configure OpenGL/GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OcTree", nullptr, nullptr);
    if(window == nullptr)
    {
        std::cerr << "Failed to create GLFW Window"  << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    Shader cshader {"shaders/cubeShader"};
    Shader pshader {"shaders/pointShader"};

    float pointVertexData[] = {0.0f, 0.0f, 0.0f};
    GLuint pointVAO;
    GLuint pointVBO;
    glGenVertexArrays(1, &pointVAO);
    glGenBuffers(1, &pointVBO);

    glBindVertexArray(pointVAO);

    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertexData), pointVertexData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width {};
    int height {};
    int nrChannels {};
    unsigned char* data = stbi_load("res/textures/vignette.jpg", &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to Load Texture" << std::endl;
    }
    stbi_image_free(data);

    float cameraRot {0.0f};
    float cameraRadius {4.0f};

    glm::vec3 up {0.0f, 1.0f, 0.0f};

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    model = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    cshader.use();
    cshader.setVec3("color", 0.12f, 0.64f, 0.40f);
    cshader.setMat4("model", model);
    cshader.setMat4("projection", projection);

    pshader.use();
    pshader.setVec3("color", 0.38f, 0.38f, 0.13f);
    pshader.setMat4("model", model);
    pshader.setMat4("projection", projection);

    float deltaTime {0.0f};

    float lastFrame {0.0f};
    float currentFrame {0.0f};

    int gw {200};
    int gh {200};
    int gd {200};

    int qcx {0};
    int qcy {0};
    int qcz {0};
    int qcw {gw / 2};
    int qch {gh / 2};
    int qcd {gd / 2};

    Cube cube {0, 0, 0, gw, gh, gd};

    srand(time(nullptr));
    OcTree octree {cube, 4};
    for(int i = 0; i < 256; ++i)
    {
        int rx = -gw + rand() % (2 * gw + 1);
        int ry = -gh + rand() % (2 * gh + 1);
        int rz = -gd + rand() % (2 * gd + 1);
        octree.insert({rx, ry, rz});
    }
    octree.insert({   0, -100,  -50});
    octree.insert({-100, -100,  -50});
    octree.insert({   0, -100, -100});
    octree.insert({-110, -100,  -50});
    octree.insert({   0, -141,  -50});

    std::vector<Point> query;

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processInput(window);

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if(qPress)
        {
            cameraRot -= deltaTime;
        }
        if(ePress)
        {
            cameraRot += deltaTime;
        }

        if(wPress)
        {
            qcz -= 256.0f * deltaTime;
        }
        if(sPress)
        {
            qcz += 256.0f * deltaTime;
        }
        if(aPress)
        {
            qcx -= 256.0f * deltaTime;
        }
        if(dPress)
        {
            qcx += 256.0f * deltaTime;
        }
        if(zPress)
        {
            qcy += 256.0f * deltaTime;
        }
        if(xPress)
        {
            qcy -= 256.0f * deltaTime;
        }

        float camX = sin(cameraRot) * cameraRadius;
        float camZ = cos(cameraRot) * cameraRadius;
        view = glm::lookAt(glm::vec3 {camX, 1.0f, camZ}, glm::vec3 {0.0f, 0.0f, 0.0f}, up);

        cshader.use();
        cshader.setMat4("view", view);
        pshader.use();
        pshader.setMat4("view", view);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        octree.show(cshader, pshader, texture, pointVAO, gw, gh, gd);

        glClear(GL_DEPTH_BUFFER_BIT);

        query.clear();
        octree.query(Cube {qcx, qcy, qcz, qcw, qch, qcd}, query);

        glEnable(GL_BLEND);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        CubeMesh mesh;
        cshader.use();
        cshader.setVec3("color", 0.75f, 0.25f, 0.25f);
        float sx = static_cast<float>(qcw) / static_cast<float>(gw);
        float sy = static_cast<float>(qch) / static_cast<float>(gh);
        float sz = static_cast<float>(qcd) / static_cast<float>(gd);
        float ndcpx = static_cast<float>(qcx) / static_cast<float>(gw);
        float ndcpy = static_cast<float>(qcy) / static_cast<float>(gh);
        float ndcpz = static_cast<float>(qcz) / static_cast<float>(gd);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3 {ndcpx, ndcpy, ndcpz});
        model = glm::scale(model, glm::vec3 {sx, sy, sz});
        cshader.setMat4("model", model);
        glBindTexture(GL_TEXTURE_2D, texture);
        mesh.draw(cshader);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_BLEND);

        glClear(GL_DEPTH_BUFFER_BIT);

        pshader.use();
        pshader.setVec3("color", 0.75f, 0.25f, 0.25f);
        for(const Point& p : query)
        {
            ndcpx = static_cast<float>(p.x) / static_cast<float>(gw);
            ndcpy = static_cast<float>(p.y) / static_cast<float>(gh);
            ndcpz = static_cast<float>(p.z) / static_cast<float>(gd);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3 {ndcpx, ndcpy, ndcpz});
            pshader.setMat4("model", model);
            glBindVertexArray(pointVAO);
                glDrawArrays(GL_POINTS, 0, 1);
            glBindVertexArray(0);
        }

        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &pointVBO);
    glDeleteVertexArrays(1, &pointVAO);
    glfwTerminate();
    return 0;
}
