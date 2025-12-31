
import java.util.PriorityQueue;
import java.util.Queue;

public class arraylist {
    public static void main(String[] args) {
        Queue<Integer> numbers = new PriorityQueue<>();
        numbers.offer(5);
        numbers.offer(1);
        numbers.offer(3);
        numbers.offer(2);
        numbers.offer(4);

        System.out.println("Priority Queue: " + numbers); // Output order is not guaranteed, but retrieval is prioritized

        System.out.println("Polled element: " + numbers.poll()); // Retrieves and removes the head (smallest element)
        System.out.println("Priority Queue after poll(): " + numbers);

        System.out.println("Peeked element: " + numbers.peek()); // Retrieves, but does not remove, the head
        System.out.println("Priority Queue after peek(): " + numbers);

        System.out.println("Removed element: " + numbers.remove());  //removes the head of the queue
        System.out.println("Priority Queue after remove(): " + numbers);

        System.out.println("Element: " + numbers.element()); // Retrieves, but does not remove, the head
    }
}