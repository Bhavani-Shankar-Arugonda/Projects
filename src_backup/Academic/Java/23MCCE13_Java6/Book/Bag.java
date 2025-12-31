import java.util.*;

public class Bag{
    private List<Book> books;
    private int size=0;

    Bag(){
        books= new ArrayList<>();
    }

    public void insertBook(Book book)
    {
        if(size<10)
        {
            books.add(book);
            size++;
        }
        else{
            System.out.println("Bag is full!!");
        }
    }

    public void searchBookByKeyword(String Keyword)
    {
        for(Book book:books)
        {
            int occurences=book.countKeywordOccurences(Keyword);
            if(occurences>0)
            {
                System.out.println("Book Name : "+book.bookName+" By "+book.author);
            }
        }
    }

    public void searchBookWithMostOccurences(String keyword) {
        int max = 0;
        Book maxBook = null;
    
        for (Book book : books) {
            int occurrences = book.countKeywordOccurences(keyword);
            if (occurrences > max) {
                max = occurrences;
                maxBook = book;
            }
        }
    
        if (maxBook != null) {
            System.out.println("Book With Most Occurrences: " + maxBook.bookName + 
                               " By " + maxBook.author + " (Occurrences: " + max + ")");
        } else {
            System.out.println("No books found with the keyword: " + keyword);
        }
    }
    
}