class Point
{
    constructor(x, y, userData)
    {
        this.x = x;
        this.y = y;
        this.userData = userData;
    }
}

class Rectangle
{
    constructor(x, y, w, h)
    {
        this.x = x;
        this.y = y;
        this.w = w; // Width  radius
        this.h = h; // Height radius
    }

    contains(point)
    {
        return( Math.abs(point.x - this.x) < this.w &&
                Math.abs(point.y - this.y) < this.h )
    }

    intersects(range)
    {
        return( Math.abs(range.x - this.x) < range.w + this.w &&
                Math.abs(range.y - this.y) < range.h + this.h )
    }
}

class QuadTree
{
    constructor(boundary, n)
    {
        this.boundary = boundary;
        this.capacity = n;
        this.points = [];
        this.divided = false;
    }

    subdivide()
    {
        this.northeast = new QuadTree(new Rectangle(this.boundary.x + this.boundary.w / 2,
                                                    this.boundary.y - this.boundary.h / 2,
                                                    this.boundary.w / 2,
                                                    this.boundary.h / 2), this.capacity);
        this.northwest = new QuadTree(new Rectangle(this.boundary.x - this.boundary.w / 2,
                                                    this.boundary.y - this.boundary.h / 2,
                                                    this.boundary.w / 2,
                                                    this.boundary.h / 2), this.capacity);
        this.southeast = new QuadTree(new Rectangle(this.boundary.x + this.boundary.w / 2,
                                                    this.boundary.y + this.boundary.h / 2,
                                                    this.boundary.w / 2,
                                                    this.boundary.h / 2), this.capacity);
        this.southwest = new QuadTree(new Rectangle(this.boundary.x - this.boundary.w / 2,
                                                    this.boundary.y + this.boundary.h / 2,
                                                    this.boundary.w / 2,
                                                    this.boundary.h / 2), this.capacity);

        this.divided = true;
    }

    insert(point)
    {
        if(!this.boundary.contains(point))
        {
            return;
        }

        if(this.points.length < this.capacity)
        {
            this.points.push(point);
        }
        else
        {
            if(!this.divided)
            {
                this.subdivide();
            }
            this.northeast.insert(point);
            this.northwest.insert(point);
            this.southeast.insert(point);
            this.southwest.insert(point);
        }
    }

    show()
    {
        stroke(255);
        strokeWeight(1);
        noFill();
        rectMode(CENTER);
        rect(this.boundary.x, this.boundary.y, this.boundary.w * 2, this.boundary.h * 2);

        if(this.divided)
        {
            this.northeast.show();
            this.northwest.show();
            this.southeast.show();
            this.southwest.show();
        }

        for(let p of this.points)
        {
            strokeWeight(4);
            point(p.x, p.y);
        }
    }
}
