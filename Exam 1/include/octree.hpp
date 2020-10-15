#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.hpp>
#include <cubeMesh.hpp>

#include <cmath>
#include <vector>

struct Point
{
    int x;
    int y;
    int z;
};

class OcTree;

class Cube
{
    friend OcTree;
public:
    Cube();
    Cube(int x, int y, int z, int w, int h, int d);
    Cube(const Cube& o);

    bool contains(const Point& p) const;
    bool intersects(const Cube& range) const;

private:
    int x;
    int y;
    int z;
    int w;
    int h;
    int d;
};

class OcTree
{
public:
    OcTree(const Cube& boundary, int capacity);
    ~OcTree();

    void subdivide();
    void insert(const Point& point);
    void query(const Cube& range, std::vector<Point>& found) const;

    void show(Shader& cshader, Shader& pshader, GLuint texture, GLuint pointVAO, int gw, int gh, int gd, float scaleFactor = 1.0f);

private:
    int capacity;
    bool isDivided;
    Cube* boundary;
    CubeMesh* cubeMesh;
    std::vector<Point> points;

    OcTree* frontnortheast;
    OcTree* frontnorthwest;
    OcTree* frontsoutheast;
    OcTree* frontsouthwest;
    OcTree* backnortheast;
    OcTree* backnorthwest;
    OcTree* backsoutheast;
    OcTree* backsouthwest;
};

#endif // OCTREE_HPP
