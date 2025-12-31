import java.util.*;

public class Book {
    public String bookName;
    public String author;
    private List<Page> pages;
    
    Book(String bookName,String author){
        this.bookName=bookName;
        this.author=author;
        pages=new ArrayList<>();
    }

    public void addPage(Page page)
    {
        pages.add(page);
    }

    public int countKeywordOccurences(String Keyword)
    {
        int k=0;
        for(Page page:pages)
        {
            k=k+page.countKeywordOccurences(Keyword);
        }
        return k;
    }
}
