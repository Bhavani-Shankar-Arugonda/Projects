/**
 * This is the main function.
 * It validates teachers and brings together all the supporting classes.
 *
 * @author BHAVANI SHANKAR ARUGONDA
 * @version 01-05-2025
 */

import java.util.*;
public class GradeCalculator
{
    static String teacherId[]={"ood","cbot","it","sands","itlab","toc","oodlab"};
    static String subjects[]={"ood","cbot","it","sAnds","itLab","toc","oodLab"};
    private static boolean authenticateTeacher(String id, String subject)
    {
        for(int i=0; i<teacherId.length; i++)
        {
            if(id.equals(teacherId[i])&& subject.equals(subjects[i]))
            {
                return true;
            }
        }
        return false;
    }
    
    public static void main(String[] args)
    {
        String teacherId;
        String studentId;
        
        Scanner sc = new Scanner(System.in);
        
        
        int s=0;
        while(s!=-1)
        {
            System.out.println("Enter 1 to Student access\nEnter 2 to Teacher access\nEnter -1 to exit.\n");
            System.out.print("Enter choice : ");
            s=sc.nextInt();
            switch(s)
            {
                case 1:
                    System.out.println("Enter id to get grades : ");
                    sc.nextLine();
                    String Id = sc.nextLine();
                    Student student = new Student(Id);
                    student.Grades();
                    break;
                case 2:
                    System.out.println("\nSubjects : \nood\ncbot\nit\nsAnds\nitLab\ntoc\noodLab\n");
                    System.out.println("Enter teaching subject : ");
                    sc.nextLine();
                    String subject=sc.nextLine();
                    System.out.println("\nEnter teacher password /same as the subject/\n");
                    String id=sc.nextLine();
                    if(authenticateTeacher(id,subject))
                    {
                        System.out.println("\nAuthentication Sucessful!!\n");
                        Teacher teacher=new Teacher(subject,id);
                        int s2=0;
                        while(s2!=-1)
                        {
                            System.out.println("\nEnter 1 to add student\nEnter 2 to update student details\nEnter 3 to delete a student\nEnter 4 to display student data\nEnter -1 to go back to previous menu.\n");
                            System.out.print("Enter choice : ");
                            s2=sc.nextInt();
                            sc.nextLine();
                            switch(s2)
                            {
                                case 1:
                                    System.out.println("");
                                    System.out.print("Enter Student id :");
                                    String STUDENTID = sc.nextLine();
                                    System.out.print(System.lineSeparator()+"Enter Student name :");
                                    String NAME = sc.nextLine();
                                    System.out.print(System.lineSeparator()+"Enter Student minor1 marks, weights with no spaces :");
                                    String MINOR1 = sc.nextLine();
                                    System.out.print(System.lineSeparator()+"Enter Student minor2 marks, weights with no spaces :");
                                    String MINOR2 = sc.nextLine();
                                    System.out.print(System.lineSeparator()+"Enter Student minor3/assignment marks, weights with no spaces :");
                                    String MINOR3 = sc.nextLine();
                                    System.out.print(System.lineSeparator()+"Enter Student major marks, weights with no spaces :");
                                    String MAJOR = sc.nextLine();
                                    
                                    teacher.addStudent(STUDENTID,NAME,MINOR1,MINOR2,MINOR3,MAJOR);
                                    System.out.println("");
                                    break;
                                case 2:
                                    System.out.println("");
                                    System.out.print("Enter Student id to be updated:");
                                    String STUDENTid = sc.nextLine();
                                    System.out.print("\nEnter Student name :");
                                    String N = sc.nextLine();
                                    System.out.print("\nEnter Student minor1 marks, weights with no spaces :");
                                    String M1 = sc.nextLine();
                                    System.out.print("\nEnter Student minor2 marks, weights with no spaces :");
                                    String M2 = sc.nextLine();
                                    System.out.print("\nEnter Student minor3/assignment marks, weights with no spaces :");
                                    String M3 = sc.nextLine();
                                    System.out.print("\nEnter Student major marks, weights with no spaces :");
                                    String MAJ = sc.nextLine();
                                    
                                    teacher.updateData(STUDENTid,N,M1,M2,M3,MAJ);
                                    System.out.println("");
                                    break;
                                case 3:
                                    System.out.println("");
                                    System.out.print("Enter Student id to be delete:");
                                    String i = sc.nextLine();
                                    teacher.deleteData(i);
                                    System.out.println("");
                                    break;
                                case 4:
                                    teacher.displayData();
                                    break;
                                
                            }
                        }
                    }
                    break;
            }
        }
    }
}