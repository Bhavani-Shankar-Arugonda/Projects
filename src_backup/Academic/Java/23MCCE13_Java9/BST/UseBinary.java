import java.util.Scanner;

public class UseBinary {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        BinaryTree bt = new BinaryTree();
        BinarySearchTree bst = new BinarySearchTree();

        System.out.println("Enter 1 to Insert into Binary Tree");
        System.out.println("Enter 2 to Insert into Binary Search Tree");
        System.out.println("Enter 3 to Search in Binary Tree");
        System.out.println("Enter 4 to Search in Binary Search Tree");
        System.out.println("Enter 5 to Delete from Binary Tree");
        System.out.println("Enter 6 to Delete from Binary Search Tree");
        System.out.println("Enter 7 for InOrder Traversal");
        System.out.println("Enter 8 for PreOrder Traversal");
        System.out.println("Enter 9 for PostOrder Traversal");
        System.out.println("Enter 10 to Exit.");
        while (true) {
            
            System.out.print("Enter your choice: ");
            int s = sc.nextInt();

            switch (s) {
                case 1:
                    System.out.print("Enter value to insert into Binary Tree: ");
                    int valBT = sc.nextInt();
                    bt.insert(valBT);
                    System.out.println(valBT + " inserted into Binary Tree.");
                    break;

                case 2:
                    System.out.print("Enter value to insert into Binary Search Tree: ");
                    int valBST = sc.nextInt();
                    bst.insert(valBST);
                    System.out.println(valBST + " inserted into Binary Search Tree.");
                    break;

                case 3:
                    System.out.print("Enter value to search in Binary Tree: ");
                    int searchBT = sc.nextInt();
                    boolean foundBT = bt.search(searchBT);
                    System.out.println(foundBT ? searchBT + " found in Binary Tree." : searchBT + " not found.");
                    break;

                case 4:
                    System.out.print("Enter value to search in Binary Search Tree: ");
                    int searchBST = sc.nextInt();
                    boolean foundBST = bst.search(searchBST);
                    System.out.println(foundBST ? searchBST + " found in Binary Search Tree." : searchBST + " not found.");
                    break;

                case 5:
                    System.out.print("Enter value to delete from Binary Tree: ");
                    int delBT = sc.nextInt();
                    bt.delete(delBT);
                    System.out.println(delBT + " deleted from Binary Tree.");
                    break;

                case 6:
                    System.out.print("Enter value to delete from Binary Search Tree: ");
                    int delBST = sc.nextInt();
                    bst.delete(delBST);
                    System.out.println(delBST + " deleted from Binary Search Tree.");
                    break;

                case 7:
                    System.out.println("InOrder Traversal:");
                    System.out.print("Binary Tree: ");
                    bt.inOrderTraversal(bt.root);
                    System.out.print("\nBinary Search Tree: ");
                    bst.inOrderTraversal(bst.root);
                    System.out.println();
                    break;

                case 8:
                    System.out.println("PreOrder Traversal:");
                    System.out.print("Binary Tree: ");
                    bt.preOrderTraversal(bt.root);
                    System.out.print("\nBinary Search Tree: ");
                    bst.preOrderTraversal(bst.root);
                    System.out.println();
                    break;

                case 9:
                    System.out.println("PostOrder Traversal:");
                    System.out.print("Binary Tree: ");
                    bt.postOrderTraversal(bt.root);
                    System.out.print("\nBinary Search Tree: ");
                    bst.postOrderTraversal(bst.root);
                    System.out.println();
                    break;

                case 10:
                    System.out.println("Exiting program...");
                    sc.close();
                    System.exit(0);
                    break;

                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }
}
