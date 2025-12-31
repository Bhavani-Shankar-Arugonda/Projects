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
