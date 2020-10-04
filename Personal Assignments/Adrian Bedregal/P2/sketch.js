let qt;
let range;

function setup()
{
    createCanvas(800, 800);

    let boundary = new Rectangle(400, 400, 400, 400);

    qt = new QuadTree(boundary, 4);
    range = new Rectangle(400, 400, 100, 100);

    for(let i = 0; i < 500; ++i)
    {
        let p = new Point(random(800), random(800));
        qt.insert(p);
    }

    console.log(qt);
}

function draw()
{
    background(0);
    qt.show();

    range.x = mouseX;
    range.y = mouseY;

    let found = [];
    qt.query(range, found);

    stroke(0, 255, 0);
    strokeWeight(1);
    noFill();
    rectMode(RADIUS);
    rect(range.x, range.y, range.w, range.h);

    for(let p of found)
    {
        stroke(0, 255, 0);
        strokeWeight(4);
        point(p.x, p.y);
    }
}

function mousePressed()
{
    let m = new Point(mouseX, mouseY);
    qt.insert(m);

    return false;
}
