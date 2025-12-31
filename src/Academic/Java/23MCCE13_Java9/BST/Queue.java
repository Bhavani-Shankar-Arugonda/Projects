

public class Queue{

    class queueNode{
        Node treeNode;
        queueNode next;
        queueNode(Node treeNode){
            this.treeNode = treeNode;
            this.next = null;
        }
    }


    private queueNode front,rear;
    public Queue(){
        this.front = this.rear = null;
    }

    public boolean isEmpty(){
        return this.front == null;
    }

        public  void  enqueue(Node treeNode)
        {
            queueNode newnode = new queueNode(treeNode);
            if(isEmpty())
            {
                front=newnode;
                rear=front;
                return;
            }
            rear.next=newnode;
            rear=newnode;
        }

        public Node dequeue()
        {
            if(isEmpty())
            {
                System.out.println("Queue is empty!!");
                return null;
            }
            Node temp = front.treeNode;
            front = front.next;

            if (front == null) {
                rear = null;
            }

            return temp;
        }
}