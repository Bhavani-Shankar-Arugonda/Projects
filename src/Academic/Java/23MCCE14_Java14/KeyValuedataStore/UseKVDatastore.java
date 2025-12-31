public class UseKVDatastore {

    public static void getFreqCount(String s){
        char[] Array=s.toCharArray();
        Character[] keyArray=new Character[Array.length];
        Integer[] valueArray=new Integer[keyArray.length];

        KVDatastore<Character,Integer> obj= new KVDatastore<Character,Integer>(keyArray,valueArray);

        for(int i=0;i<Array.length;i++)
        {
            Integer value=obj.get(Array[i]);
            if(obj.get(Array[i]) == null)
            {
                obj.put(Character.valueOf(Array[i]),1);
                
            }
            else{
                obj.put(Character.valueOf(Array[i]),++value);
            }
        }
        obj.display();
    }

    public static void main(String[] args)
    {
        getFreqCount("ababcdabddc");
    }
}
