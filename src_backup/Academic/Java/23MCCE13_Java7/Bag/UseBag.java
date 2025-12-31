import java.util.*;

public class UseBag {
    public static void main(String[] args)
    {
        
        Scanner sc= new Scanner(System.in);
        Bag bag=new Bag();

        int s=0;
        
        while(s!=-1)
        {
            System.out.println("Enter 1 to Add Book / Enter 2 to search Book By Keyword / Enter 3 to search book with most occurences / Enter -1 to exit");
            s=sc.nextInt();
            sc.nextLine();
            switch (s) {
                case 1:
                    System.out.print("Enter Book Name : ");
                    String bookName=sc.nextLine();
                    System.out.println();
                    System.out.print("Enter Author Name : ");
                    String author=sc.nextLine();
                    System.out.println();

                    Book book = new Book(bookName,author);

                    int a=0;
                    while(a!=-1)
                    {
                        System.out.println("Enter 1 to Add Page or -1 to exit.");
                        a=sc.nextInt();
                        sc.nextLine();
                        if(a!=-1){
                            System.out.print("Enter The Content of the page : ");
                            String text=sc.nextLine();
                            System.out.println();
                            Book.Page page = book.new Page(text);
                            book.addPage(page); 
                        }
                    }
                    bag.insertBook(book);
                    break;
                
                case 2:
                    System.out.print("Enter the Keyword : ");
                    String Keyword=sc.nextLine();
                    System.out.println();

                    bag.searchBookByKeyword(Keyword);
                    break;
                case 3:
                    System.out.print("Enter the Keyword : ");
                    String keyword=sc.nextLine();
                    System.out.println();
            
                    bag.searchBookWithMostOccurences(keyword);
                    break;
                default:
                    break;
            }
        }
    }
}
