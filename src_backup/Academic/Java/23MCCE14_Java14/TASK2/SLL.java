package TASK2;

public class SLL<T> {
    private Node<T> head;

    public void insertAt(T data, int pos) {
        Node<T> newNode = new Node<>(data);

        if (pos < 0) {
            throw new IndexOutOfBoundsException("Invalid position: " + pos);
        }

        if (pos == 0) {
            newNode.next = head;
            head = newNode;
            return;
        }

        Node<T> current = head;
        int index = 0;

        while (current != null && index < pos - 1) {
            current = current.next;
            index++;
        }

        if (current == null) {
            throw new IndexOutOfBoundsException("Position out of bounds: " + pos);
        }

        newNode.next = current.next;
        current.next = newNode;
    }

    public void delete(T data) {
        if (head == null) {
            System.out.println("List is empty. Nothing to delete.");
            return;
        }

        if (head.data.equals(data)) {
            head = head.next;
            System.out.println("Deleted: " + data);
            return;
        }

        Node<T> current = head;
        while (current.next != null && !current.next.data.equals(data)) {
            current = current.next;
        }

        if (current.next == null) {
            System.out.println("Element not found: " + data);
            return;
        }

        current.next = current.next.next;
        System.out.println("Deleted: " + data);
    }

    public void display() {
        if (head == null) {
            System.out.println("List is empty.");
            return;
        }

        Node<T> current = head;
        System.out.print("Linked List: ");
        while (current != null) {
            System.out.print(current.data + " → ");
            current = current.next;
        }
        System.out.println("null");
    }
}
