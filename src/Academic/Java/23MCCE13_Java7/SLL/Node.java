public class Node{
    int data;
    Node next=null;

    Node(int d){
        this.data=d;
        this.next=null;
    }

    Node(int d, Node n)
    {
        this.data=d;
        this.next=n;
    }

    public void setNext(Node n)
    {
        this.next=n;
    }
}