

public class QueueSll{
    Node front;
    Node rear;

    QueueSll()
    {
        this.front=null;
        this.rear=null;
    }

        public  void  enqueue(int d)
        {
            Node newnode = new Node(d);
            if(isEmpty())
            {
                front=newnode;
                rear=front;
                return;
            }
            rear.next=newnode;
            rear=newnode;
        }

        public void dequeue()
        {
            if(isEmpty())
            {
                System.out.println("Queue is empty!!");
                return;
            }
            front=front.next;
        }

        public void peek()
        {
            if(isEmpty())
            {
                System.out.println("Queue is empty!!");
                return;
            }

            System.out.println(front.data);
        }

        public boolean isEmpty()
        {
            return front==null;
        }

        public void display()
        {
            if(isEmpty())
            {
                System.out.println("Queue is empty!!");
                return;
            }
            Node temp=front;
            while(temp!=null)
            {
                System.out.print(temp.data);
                if(temp.next!=null)
                {
                    System.out.print("->");
                }
                temp=temp.next;
            }
            System.out.println();
        }

}