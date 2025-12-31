package TASK2;




/**
 * Write a description of class Node here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */

   public class Node<T> {
    T data;
    Node<T> next;

    public Node(T data) {
        this.data = data;
        this.next = null;
    }
}


