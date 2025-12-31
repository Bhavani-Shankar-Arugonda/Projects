public class CircularQueue
{
    private int front=0;
    private int rear=0;
    private int queue[];
    private int size=0;
    
    
    CircularQueue(int n)
    {   
         queue = new int[n];
    }
    
    public void enqueue(int a)
    {
        if(isFull())
        {
            System.out.println("Queue Is Full");
            return;
        }
        
        
        if(front == queue.length)
        {
            front=0;
            queue[front++]=a;
            size++;
        }
        else
        {
            queue[front++]=a;
            size++;
        }
    }
    
    public void dequeue()
    {
        if(isEmpty())
        {
            System.out.println("Queue Is Empty");
            return;
        }
        
        if(rear == queue.length)
        {
            System.out.println("Removed Element : "+queue[rear]);
            rear=0;
            size--;
        }
        else
        {
            System.out.println("Removed Element : "+queue[rear++]);
            size--;
        }
    }
    
    public boolean isFull()
    {
        return size==queue.length;    
    }
    
    public boolean isEmpty()
    {
        return size==0;
    }
   
    public void displayElements()
    {
            if(front>=rear)
            {
                for(int i=rear; i<front; i++)
                {
                    System.out.print(queue[i]+" ");
                }
            }
            else
            {
                for(int i=front-1;i>=0;i--)
                {
                    System.out.print(queue[i]+" ");
                }
                
                for(int i=queue.length-1; i>=rear;i--)
                {
                    System.out.print(queue[i]+" ");
                }
            }
    }
}
