class BPQ
{
    constructor(size)
    {
        this.size = size;
        this.queue = [];
    }

    insert(val, priority)
    {
        if(this.queue.length < this.size)
            this.queue.push({data:val, priority:priority});
        else
        { //si esta lleno
            if( this.queue[this.queue.length - 1].priority > priority)
                this.queue[this.queue.length - 1] = {data:val, priority:priority};
        }

        this.queue.sort(function (a, b)
        {
            return (a.priority - b.priority);
        });
    }
}
