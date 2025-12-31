

public class sll{
    public static Node head;

    sll()
    {
        this.head=null;
    }

    public  void  insertAtBiginning(int d)
    {
        Node newnode = new Node(d);
        newnode.setNext(head);
        head=newnode;
    }

    public void deleteAtBiginning()
    {
        if(head==null)
        {
            System.out.println("List is empty!!");
            return;
        }
        head=head.next;
    }

    public void insertAtEnd(int d,Node node)
    {
        if(this.head==null){
            insertAtBiginning(d);
            return;
        }

        if(node.next==null)
        {
            Node newnode=new Node(d);
            node.setNext(newnode);
            return;
        }
        insertAtEnd(d, node.next);
    }

    public void DeleteByValue(int d,Node node) {
        if(head==null)
        {
            System.out.println("List is Empty!!");
            return;    
        }

        if(head.data==d)
        {
            head=head.next;
            return;
        }
        if(node.next.data==d){
            node.next=node.next.next;
            return;
        }

        if(node.next.next!=null)
        {
            DeleteByValue(d, node.next);
        }
        return;
    }


    public int getSum(Node node ,int sum)
    {
        if(node!=null)
        {
            sum = sum+node.data;
            return getSum(node.next,sum);
        }
        else
        {
            return sum;
        }
    }

    public void display(Node node)
    {
        if(this.head==null)
        {
            System.out.println("List is empty!!");
            return;
        }
        if(node==null)
        {
            System.out.print("");
            return;
        }
        System.out.print(node.data);
        if(node.next!=null)
        {
            System.out.print("->");
        }
        display(node.next);
    }

}