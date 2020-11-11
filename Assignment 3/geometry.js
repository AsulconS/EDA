function distanceBetween(point1, point2, k)
{
    var distance = 0;
    for(var i = 0; i < k; ++i)
        distance += (point1[i] - point2[i]) * (point1[i] - point2[i]);
    return Math.sqrt(distance);
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
        return( Math.abs(point[0] - this.x) < this.w &&
                Math.abs(point[1] - this.y) < this.h )
    }
}

class Circle
{
    constructor(x, y, r)
    {
        this.x = x;
        this.y = y;
        this.r = r; // radius
    }

    contains(point)
    {
        return distanceBetween([this.x, this.y], point, 2) <= this.r;
    }
}
