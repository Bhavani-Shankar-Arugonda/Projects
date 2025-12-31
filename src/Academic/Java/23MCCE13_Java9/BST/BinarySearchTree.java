class BinarySearchTree extends BinaryTree {

    public void insert(int value) {
        root = insertRec(root, value);
    }

    private Node insertRec(Node node, int value) {
        if (node == null) return new Node(value);
        if (value < node.data) node.left = insertRec(node.left, value);
        else node.right = insertRec(node.right, value);
        return node;
    }

    public boolean search(int value) {
        return searchRec(root, value);
    }

    private boolean searchRec(Node node, int value) {
        if (node == null) return false;
        if (node.data == value) return true;
        return value < node.data ? searchRec(node.left, value) : searchRec(node.right, value);
    }

    public void delete(int value) {
        root = deleteRec(root, value);
    }

    private Node deleteRec(Node node, int value) {
        if (node == null) return null;
        if (value < node.data) node.left = deleteRec(node.left, value);
        else if (value > node.data) node.right = deleteRec(node.right, value);
        else {
            if (node.left == null) return node.right;
            if (node.right == null) return node.left;
            Node minNode = findMinNode(node.right);
            node.data = minNode.data;
            node.right = deleteRec(node.right, minNode.data);
        }
        return node;
    }

    private Node findMinNode(Node node) {
        while (node.left != null) node = node.left;
        return node;
    }

    public int findMin() {
        return findMinNode(root).data;
    }

    public int findMax() {
        Node node = root;
        while (node.right != null) node = node.right;
        return node.data;
    }
}
