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
        let x = this.boundary.x;
        let y = this.boundary.y;
        let w = this.boundary.w;
        let h = this.boundary.h;

        this.northwest = new QuadTree(new Rectangle(x - w / 2, y - h / 2, w / 2, h / 2), this.capacity);
        this.northeast = new QuadTree(new Rectangle(x + w / 2, y - h / 2, w / 2, h / 2), this.capacity);
        this.southwest = new QuadTree(new Rectangle(x - w / 2, y + h / 2, w / 2, h / 2), this.capacity);
        this.southeast = new QuadTree(new Rectangle(x + w / 2, y + h / 2, w / 2, h / 2), this.capacity);

        this.divided = true;
    }

    insert(point)
    {
        if(!this.boundary.contains(point))
        {
            return false;
        }
        if(this.points.length < this.capacity)
        {
            this.points.push(point);
            return true;
        }
        else
        {
            if(!this.divided)
            {
                this.subdivide();
            }
            if(this.northwest.insert(point))
            {
                return true;
            }
            if(this.northeast.insert(point))
            {
                return true;
            }
            if(this.southeast.insert(point))
            {
                return true;
            }
            if(this.southwest.insert(point))
            {
                return true;
            }
        }
    }

    query(range, found)
    {
        if(!this.boundary.intersects(range))
        {
            return;
        }
        else
        {
            for(let p of this.points)
            {
                if(range.contains(p))
                {
                    found.push(p);
                }
            }
            if(this.divided)
            {
                this.northwest.query(range, found);
                this.northeast.query(range, found);
                this.southeast.query(range, found);
                this.southwest.query(range, found);
            }
        }
    }

    show()
    {
        stroke(255);
        strokeWeight(1);
        noFill();
        rectMode(RADIUS);
        rect(this.boundary.x, this.boundary.y, this.boundary.w, this.boundary.h);
        if(this.divided)
        {
            this.northwest.show();
            this.northeast.show();
            this.southwest.show();
            this.southeast.show();
        }
        for(let p of this.points)
        {
            strokeWeight(2);
            point(p.x, p.y);
        }
    }
}
