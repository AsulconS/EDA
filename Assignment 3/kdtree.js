K = 2;
size = 12;
class Node
{
    constructor(point, axis)
    {
        this.point = point;
        this.left = null;
        this.right = null;
        this.axis = axis;   // 0 = x , 1 = y
    }
}

function orderx(point1, point2)
{
    if(point1[0] > point2[0])
        return 1;
    return -1;
}

function ordery(point1, point2)
{
    if (point1[1] > point2[1])
        return 1;
    return -1;
}

function build_kdtree(points, depth = 0)
{
    if (points.length <= 0)
        return null;

    if (depth % K == 0)
        points.sort(orderx);
    else
        points.sort(ordery);

    let node = new Node(points[Math.floor(points.length / K)], depth % K);
    node.left = build_kdtree(points.slice(0, points.length / K), depth + 1);
    node.right = build_kdtree(points.slice(points.length / K + 1, points.length), depth + 1);

    return node;
}

function getHeight(node)
{
    var height = 0;
    var auxnode = node;
    while(auxnode.left != null)
    {
        auxnode = auxnode.left;
        height = height + 1;
    }
    return height;
}

function getGraf(node)
{
    let r = "";
    if (node.left != null)
    {
        r += `    "` + node.point + `" -> "` + node.left.point + `";\n`;
        r += getGraf(node.left);
    }
    if (node.right != null)
    {
        r += `    "` + node.point + `" -> "` + node.right.point + `";\n`;
        r += getGraf(node.right);
    }
    return r;
}

function generate_dot(node)
{
    let dot_i = `digraph G\n{\n`;
    let conten = getGraf(node);
    let dot_f = `}`;
    let result = dot_i + conten + dot_f;
    console.log(result);
}

function closest_point_brute_force(points, point)
{
    var closest_point = points[0];
    for (var i = 1; i < points.length; ++i)
        if (distanceBetween(point, points[i], K) < distanceBetween(point, closest_point, K))
            closest_point = points[i];

    return closest_point;
}

function naive_closest_point(node, point, depth = 0, best = null)
{
    if(best == null)
        best = node;
    else if(distanceBetween(point, node.point, K) < distanceBetween(point, best.point, K))
        best = node;

    for(var i = 0; i < K; ++i)
    {
        if(depth % K == i)
            if(node.point[i] > point[i] && node.left)
                best = naive_closest_point(node.left, point, node.axis , best)
            else if(node.right)
                best = naive_closest_point(node.right, point, node.axis , best)
    }
    return best;
}

function closest_point(node, point, depth = 0, best = null)
{
    if(best == null)
        best = node;
    else if(distanceBetween(point, node.point, K) < distanceBetween(point, best.point, K))
        best = node;

    for(var i = 0; i < K; ++i)
    {
        if(depth == i)
        {
            if(abs(point[i] - node.point[i]) < distanceBetween(point, best.point, K))
            {
                var naive_left, naive_right;
                if (node.left)
                    naive_left = closest_point(node.left, point, node.axis, best);
                if (node.right)
                    naive_right = closest_point(node.right, point, node.axis, best);

                if(node.left && node.right)
                {
                    if (distanceBetween(point, naive_left.point, K) < distanceBetween(point, naive_right.point, K))
                        best = naive_left;
                    else
                        best = naive_right;
                }
                else if(node.left)
                    best = naive_left;

                else if(node.right)
                    best = naive_right;
            }
            else
            {
                if(node.point[i] > point[i] && node.left)
                    best = closest_point(node.left, point, node.axis , best);
                else if(node.right)
                    best = closest_point(node.right, point, node.axis , best);
            }
        }
    }

    return best;
}

function knn(node, query_point, bpq, depth = 0)
{
    if(node === null) return;

    bpq.insert(node.point, distanceBetween(node.point, query_point, K)); // Insertamos el nodo visitado a la pila
    var axis = depth % K;
    var next_branch = null;
    var opposite_branch = null;

    if(query_point[axis] < node.point[axis])
    {
        next_branch = node.left;
        opposite_branch = node.right;
    }
    else
    {
        next_branch = node.right;
        opposite_branch = node.left;
    }

    knn(next_branch, query_point, bpq, depth + 1);

    // si aun hay espacio en la pila y ademas el de prioridad mayor es > a y_1-y_0
    if(bpq.queue.length < bpq.size || Math.abs(query_point[axis] - node.point[axis]) < bpq.queue[bpq.queue.length - 1].priority)
        knn(opposite_branch, query_point, bpq, depth + 1);

    return bpq;
}

function range_query_circle(node, center, radio, queue)
{
    var bpq = new BPQ(size);
    knn(node, center, bpq);

    var i = 0;
    while(i < size && bpq.queue[i].priority <= radio)
    {
        queue.push(bpq.queue[i].data);
        ++i;
    }
    return queue;
}

function range_query_rec(node, center, width, height, queue)
{
    var bpq = new BPQ(size);
    knn(node, center, bpq);

    var i = 0;
    while(i < size && Math.abs(bpq.queue[i].data[0] - center[0]) <= width && Math.abs(bpq.queue[i].data[1] - center[1]) <= height)
    {
        queue.push(bpq.queue[i].data);
        ++i;
    }
    return queue;
}
