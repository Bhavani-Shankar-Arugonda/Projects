public class BinaryTree {
    Node root;
    
    BinaryTree() {
        root = null;
    }
    
    public void insert(int value) {
        Node newNode = new Node(value);
        if (root == null) {
            root = newNode;
            return;
        }

        Queue queue = new Queue();
        queue.enqueue(root);

        while (!queue.isEmpty())
        {
            Node temp = queue.dequeue();

            if (temp.left == null) {
                temp.left = newNode;
                return;
            } else {
                queue.enqueue(temp.left);
            }

            if (temp.right == null) {
                temp.right = newNode;
                return;
            } else {
                queue.enqueue(temp.right);
            }
        }
    }

    public boolean search(int value) {
        if (root == null) return false;

        Queue queue = new Queue();
        queue.enqueue(root);

        while (!queue.isEmpty()) {
            Node temp = queue.dequeue();
            if (temp.data == value) return true;

            if (temp.left != null) queue.enqueue(temp.left);
            if (temp.right != null) queue.enqueue(temp.right);
        }
        return false;
    }

    public void delete(int value) {
        if (root == null) return;

        Queue queue = new Queue();
        queue.enqueue(root);

        Node keyNode = null, lastNode = null, parent = null;

        while (!queue.isEmpty()) {
            lastNode = queue.dequeue();

            if (lastNode.data == value) {
                keyNode = lastNode;
            }

            if (lastNode.left != null) {
                parent = lastNode;
                queue.enqueue(lastNode.left);
            }
            if (lastNode.right != null) {
                parent = lastNode;
                queue.enqueue(lastNode.right);
            }
        }

        if (keyNode != null) {
            keyNode.data = lastNode.data;
            if (parent.left == lastNode) parent.left = null;
            else parent.right = null;
        }
    }

    public void inOrderTraversal(Node node) {
        if (node == null) return;
        inOrderTraversal(node.left);
        System.out.print(node.data + " ");
        inOrderTraversal(node.right);
    }

    public void preOrderTraversal(Node node) {
        if (node == null) return;
        System.out.print(node.data + " ");
        preOrderTraversal(node.left);
        preOrderTraversal(node.right);
    }

    public void postOrderTraversal(Node node) {
        if (node == null) return;
        postOrderTraversal(node.left);
        postOrderTraversal(node.right);
        System.out.print(node.data + " ");
    }
}