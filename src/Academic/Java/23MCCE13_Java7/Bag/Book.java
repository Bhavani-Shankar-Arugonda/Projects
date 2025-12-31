import java.util.*;

public class Book {

    public class Page {
        private String text;
        Page(String text){
            this.text=text;
        }
    
        public String getText()
        {
            return text;
        }
    
        public int countKeywordOccurences(String keyword) {
            String[] subStrings = text.toLowerCase().split(" ");
            int count = 0;
            for (String subString : subStrings) {
                if (subString.equals(keyword.toLowerCase())) {
                    count++;
                }
            }
            return count;
        }
        
    
    }
    
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
            k=k+countKeywordOccurences(Keyword);
        }
        return k;
    }
}
