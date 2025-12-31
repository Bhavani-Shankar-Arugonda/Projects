package TASK2;

public class UseSLL {
    public static void main(String[] args) {
        SLL<String> stringList = new SLL<>();
        SLL<Integer> intList = new SLL<>();

        System.out.println("Testing String SLL:");
        stringList.insertAt("A", 0);
        stringList.insertAt("B", 1);
        stringList.insertAt("C", 2);
        stringList.display();

        stringList.delete("B");
        stringList.display();

        stringList.delete("X"); // Not in list
        stringList.display();

        System.out.println("\nTesting Integer SLL:");
        intList.insertAt(10, 0);
        intList.insertAt(20, 1);
        intList.insertAt(30, 1); // Insert 30 at position 1
        intList.display();

        intList.delete(10);
        intList.display();

        try {
            intList.insertAt(40, 10); // Invalid position
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
