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
