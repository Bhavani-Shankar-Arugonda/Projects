public class sll{
    Node head;

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

    public void insertAtEnd(int d)
    {
        Node newnode=new Node(d);
        if (head == null) {
            head = newnode;
            return;
        }
        Node temp= head;
        while(temp.next!=null)
        {
            temp=temp.next;
        }
        temp.setNext(newnode);
    }

    public void DeleteByValue(int d) {
        if (head == null)
        {
            System.out.println("List is empty!!");
            return;
        }

        while (head != null && head.data == d) {
            head = head.next;
        }

        if (head == null) return;

        Node temp = head;

        
        while (temp.next != null) {
            if (temp.next.data == d)
            {
                temp.next = temp.next.next;
            } else
            {
                temp = temp.next;
            }
        }
    }


    public void getSum()
    {
        Node temp=head;
        int sum = 0;
        while(temp.next!=null)
        {
            sum += temp.data;
            temp=temp.next;
        }
        sum+=temp.data;
        System.out.println(sum);
    }

    public void display()
    {
        if(head==null)
        {
            System.out.println("List is empty!!");
            return;
        }
        Node temp=head;
        while(temp.next!=null)
        {
            System.out.print(temp.data);
            if(temp.next!=null)
            {
                System.out.print("->");
            }
            temp=temp.next;
        }
        System.out.println(temp.data);
    }

}