class Student{
    String name;
    int id;
    String regno;
    int[] marks;
    
    Student(String name, int id, String regno, int[] marks)
    {
	this.name = name;
	this.id = id;
	this.regno = regno;
	this.marks = marks;	
    }
    private String getGrade(int mark)
    {
       if(mark>=85)
         return "A+";
       else if(mark>74 && mark<=84)
          return "A";
       else if(mark>64 && mark<=74)
          return "B+";
       else if(mark>59 && mark <=64)
          return "B";
       else if(mark>49 && mark<=59)
       	  return "C";
       	else if(mark>39 && mark<=50)
       	   return "D";
       	else 
       	   return "F";
     }
    @Override
 
    public boolean equals(Object o)
    {
    if (o == this)
        return true;
    if (o == null || getClass()!= o.getClass())
        return false;
    Student other = (Student)o; 
    for (int i = 0; i < this.marks.length; i++)
    {
        if (!getGrade(this.marks[i]).equals(getGrade(other.marks[i])))
        {
            return false;
        }
    }
    return true;
   }
   
    @Override
    public int hashCode()
    {
        int sum = 0;
        for(int i = 0; i < marks.length; i++)
        {
            String grade = getGrade(marks[i]); 
            for(int j = 0; j < grade.length(); j++)
            {
                sum += (int) grade.charAt(j); 
            }
        }
        return sum;
    }


    @Override
    public String toString()
    {
      String result = "Name: "+name+"\n"+"ID No: "+id+"\n"+"Reg No: "+regno+"\n"+"Grades: ";
      for(int mark:marks)
      {
         result = result + getGrade(mark) + " ";
      }
      return result.trim();
    }
    
}