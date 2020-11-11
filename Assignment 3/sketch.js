let range;
let width = 250;
let height = 200;

let root;
let data = [];

function drawGrid()
{
    for(var x = 0; x < width; x += width / 10)
    {
        for(var y = 0; y < height; y += height / 5)
        {
            stroke(125, 125, 125);
            strokeWeight(1);
            line(x, 0, x, height);
            line(0, y, width, y);
        }
    }
}

function drawPoints()
{
    for(let p of data)
    {
        fill(255, 255, 255);
        circle(p[0], height - p[1], 7); // height -y para q se dibuje apropiadamente
        textSize(8);
        text(p[0] + ',' + p[1], p[0] + 5, height - p[1]);// height -y para q se dibuje apropiadamente
    }
}

function drawRange()
{
    stroke(0, 255, 0);
    strokeWeight(1);
    noFill();
    rectMode(RADIUS);
    if(range instanceof Rectangle)
        rect(range.x, range.y, range.w, range.h);
    else if(range instanceof Circle)
        circle(range.x, range.y, 2 * range.r);
}

function setup()
{
    //range = new Circle(0, 0, 50);
    range = new Rectangle(0, 0, 50, 50);

    createCanvas(width, height);
    background(0);
    for(let i = 0; i < 12; ++i)
    {
        var x = Math.floor(Math.random() * height);
        var y = Math.floor(Math.random() * height);
        data.push([x, y]);
    }
    root = build_kdtree(data);
    console.log(root);
    console.log("K:");
    console.log(K);
    console.log("Altura del arbol:");
    console.log(getHeight(root));

    console.log(generate_dot(root));
    console.log("Raiz:");
    console.log(root);
    console.log("Los nodos son:");
    console.log(data);
}

function draw()
{
    background(0);
    drawGrid();
    drawPoints();

    range.x = mouseX;
    range.y = mouseY;

    let found = [];
    if(range instanceof Circle)
        range_query_circle(root, [range.x, height - range.y], range.r, found);
    else if(range instanceof Rectangle)
        range_query_rec(root, [range.x, height - range.y], range.w, range.h, found);

    for(let p of found)
    {
        stroke(0, 255, 127);
        strokeWeight(4);
        point(p[0], height - p[1]);
    }

    drawRange();
}
