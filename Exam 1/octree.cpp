#include <octree.hpp>

Cube::Cube()
{
}

Cube::Cube(int x, int y, int z, int w, int h, int d)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    this->h = h;
    this->d = d;
}

Cube::Cube(const Cube& o)
{
    //centro del paralelepipedo
    this->x = o.x;
    this->y = o.y;
    this->z = o.z;

    this->w = o.w;
    this->h = o.h;
    this->d = o.d;
}

bool Cube::contains(const Point& point) const
{
    return (abs(point.x - this->x) < this->w &&
            abs(point.y - this->y) < this->h &&
            abs(point.z - this->z) < this->d );
}

bool Cube::intersects(const Cube& range) const
{
    return (abs(range.x - this->x) < range.w + this->w &&
            abs(range.y - this->y) < range.h + this->h &&
            abs(range.z - this->z) < range.d + this->d);
}

OcTree::OcTree(const Cube& boundary, int capacity)
{
    this->capacity  = capacity;
    this->boundary  = new Cube {boundary};
    this->cubeMesh  = new CubeMesh {};
    this->isDivided = false;
}

OcTree::~OcTree()
{
    delete boundary;
    delete cubeMesh;

    if(isDivided)
    {
        delete frontnortheast;
        delete frontnorthwest;
        delete frontsoutheast;
        delete frontsouthwest;

        delete backnortheast;
        delete backnorthwest;
        delete backsoutheast;
        delete backsouthwest;
    }
}

void OcTree::subdivide()
{
    int x = this->boundary->x;
    int y = this->boundary->y;
    int z = this->boundary->z;
    int w = this->boundary->w;
    int h = this->boundary->h;
    int d = this->boundary->d;

    Cube fne(x+w/2, y+h/2, z+d/2, w/2, h/2, d/2);
    Cube fnw(x-w/2, y+h/2, z+d/2, w/2, h/2, d/2);
    Cube fse(x+w/2, y-h/2, z+d/2, w/2, h/2, d/2);
    Cube fsw(x-w/2, y-h/2, z+d/2, w/2, h/2, d/2);
    Cube bne(x+w/2, y+h/2, z-d/2, w/2, h/2, d/2);
    Cube bnw(x-w/2, y+h/2, z-d/2, w/2, h/2, d/2);
    Cube bse(x+w/2, y-h/2, z-d/2, w/2, h/2, d/2);
    Cube bsw(x-w/2, y-h/2, z-d/2, w/2, h/2, d/2);

    this->frontnortheast = new OcTree(fne,this->capacity); 
    this->frontnorthwest = new OcTree(fnw,this->capacity);
    this->frontsoutheast = new OcTree(fse,this->capacity);
    this->frontsouthwest = new OcTree(fsw,this->capacity);

    this->backnortheast  = new OcTree(bne,this->capacity); 
    this->backnorthwest  = new OcTree(bnw,this->capacity);
    this->backsoutheast  = new OcTree(bse,this->capacity);
    this->backsouthwest  = new OcTree(bsw,this->capacity); 

    this->isDivided = true;
}

void OcTree::insert(const Point& point)
{
    if(!this->boundary->contains(point))
    {
        return;
    }

    if(this->points.size() < this->capacity)
    {
        this->points.push_back(point);
    }
    else
    {
        if(!this->isDivided)
        {
            this->subdivide();
        }

        this->frontnortheast->insert(point);
        this->frontnorthwest->insert(point);
        this->frontsoutheast->insert(point);
        this->frontsouthwest->insert(point);
        this->backnortheast->insert(point);
        this->backnorthwest->insert(point);
        this->backsoutheast->insert(point);
        this->backsouthwest->insert(point);
    }
}

void OcTree::query(const Cube& range, std::vector<Point>& found) const
{
    if(this->boundary->intersects(range))
    {
        for(int p = 0; p < points.size(); ++p)
        {
            if(range.contains(points[p]))
            {
                found.push_back(points[p]);
            }
        }

        if(this->isDivided)
        {
            this->frontnortheast->query(range, found);
            this->frontnorthwest->query(range, found);
            this->frontsoutheast->query(range, found);
            this->frontsouthwest->query(range, found);
            this->backnortheast->query(range, found);
            this->backnorthwest->query(range, found);
            this->backsoutheast->query(range, found);
            this->backsouthwest->query(range, found);
        }
    }
}

void OcTree::show(Shader& cshader, Shader& pshader, GLuint texture, GLuint pointVAO, int gw, int gh, int gd, float scaleFactor)
{
    glm::mat4 model;

    // Draw Cube
    if(this->isDivided)
    {
        this->frontnortheast->show(cshader, pshader, texture, pointVAO, gw, gh, gd, 1.1f);
        this->frontnorthwest->show(cshader, pshader, texture, pointVAO, gw, gh, gd, 1.1f);
        this->frontsoutheast->show(cshader, pshader, texture, pointVAO, gw, gh, gd, 1.1f);
        this->frontsouthwest->show(cshader, pshader, texture, pointVAO, gw, gh, gd, 1.1f);
        this->backnortheast->show(cshader, pshader, texture, pointVAO, gw, gh, gd, 1.1f);
        this->backnorthwest->show(cshader, pshader, texture, pointVAO, gw, gh, gd, 1.1f);
        this->backsoutheast->show(cshader, pshader, texture, pointVAO, gw, gh, gd, 1.1f);
        this->backsouthwest->show(cshader, pshader, texture, pointVAO, gw, gh, gd, 1.1f);
    }
    cshader.use();
    cshader.setVec3("color", 0.12f, 0.64f, 0.40f);
    float sx = static_cast<float>(this->boundary->w) / (static_cast<float>(gw) * scaleFactor);
    float sy = static_cast<float>(this->boundary->h) / (static_cast<float>(gh) * scaleFactor);
    float sz = static_cast<float>(this->boundary->d) / (static_cast<float>(gd) * scaleFactor);
    float ndcpx = static_cast<float>(this->boundary->x) / static_cast<float>(gw);
    float ndcpy = static_cast<float>(this->boundary->y) / static_cast<float>(gh);
    float ndcpz = static_cast<float>(this->boundary->z) / static_cast<float>(gd);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3 {ndcpx, ndcpy, ndcpz});
    model = glm::scale(model, glm::vec3 {sx, sy, sz});
    cshader.setMat4("model", model);
    glBindTexture(GL_TEXTURE_2D, texture);
    this->cubeMesh->draw(cshader);

    // Draw Points
    pshader.use();
    pshader.setVec3("color", 0.38f, 0.38f, 0.13f);
    model = glm::mat4(1.0f);
    for(const Point& p : this->points)
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
}
