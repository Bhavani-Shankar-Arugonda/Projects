class UseStudent{
    public static void main(String[] args)
    {
       Student s1 = new Student("A",01,"uoh01",new int[]{15,39,77,99});
       Student s2 = new Student("B",02,"uoh02",new int[]{92,44,19,46});
       Student s3 = new Student("C",03,"uoh03",new int[]{15,39,77,99});
       
       System.out.println(s1.toString());
       System.out.println(s2.toString());
       System.out.println(s3.toString());
       
       
       System.out.println("s1 and s2 have same grades: "+s1.equals(s2));
       System.out.println("s1 and s3 have same grades: "+s1.equals(s3));

       System.err.println("hash value of s1 : "+s1.hashCode());
       System.err.println("hash value of s2 : "+s2.hashCode());
       System.err.println("hash value of s3 : "+s3.hashCode());
       
    }
}