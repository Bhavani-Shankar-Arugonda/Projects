/**
 * This class implements the functions related to student.
 * It calculates and prints a particular student grades.
 *
 * @author ARUGONDA BHAVANI SHANKAR
 * @version 01-05-2025
 */

import java.io.*;
import java.util.*;

public class Student
{
    String id;
    String[] subjects={"toc","ood","it","cbot","sAnds","itLab","oodLab"};
    double[] credits={3.0,3.0,3.0,4.0,4.0,2.0,2.0};
    
    public Student(String id)
    {
        this.id=id;
    }
    
    public void Grades()
    {
        System.out.println("");
        Double cgpa=0.0;
        for(int i=0; i< subjects.length;i++)
        {
            String filename=subjects[i]+".txt";
            File file = new File(filename);
            if(!Teacher.isStudentExist(id,filename))
            {
                System.out.println("Grade for "+subjects[i]+" is not available.");
                continue;
            }
            double total=0.0;
            double totalMinor1=0.0;
            double totalMinor2=0.0;
            double totalMinor3=0.0;
             
            if (!file.exists()) {
                System.out.println("grade is not available for " + subjects[i]);
            }
            else
            {
                try{
                    Scanner sc=new Scanner(file);
                    while(sc.hasNextLine())
                    {
                        String line=sc.nextLine();
                        if(line.trim().equals(id))
                        {
                            sc.nextLine();
                            try {
                                String minor1 = sc.nextLine();
                                String[] Minor1 = minor1.split(",");
                                if (Minor1.length == 2) {
                                    double mark = Double.parseDouble(Minor1[0]);
                                    double weight = Double.parseDouble(Minor1[1]);
                                    totalMinor1 = mark * weight;
                                } else {
                                    System.out.println("Invalid format in " + filename + " for student ID: " + id);
                                }
                                
                                String minor2 = sc.nextLine();
                                String[] Minor2= minor2.split(",");
                                if (Minor2.length == 2) {
                                    double mark = Double.parseDouble(Minor2[0]);
                                    double weight = Double.parseDouble(Minor2[1]);
                                    totalMinor2 = mark * weight;
                                } else {
                                    System.out.println("Invalid format in " + filename + " for student ID: " + id);
                                }
                                
                                String minor3 = sc.nextLine();
                                String[] Minor3= minor3.split(",");
                                if (Minor3.length == 2) {
                                    double mark = Double.parseDouble(Minor3[0]);
                                    double weight = Double.parseDouble(Minor3[1]);
                                    totalMinor3 = mark * weight;
                                } else {
                                    System.out.println("Invalid format in " + filename + " for student ID: " + id);
                                }
                                
                                String major = sc.nextLine();
                                String[] Major= major.split(",");
                                if (Major.length == 2) {
                                    double mark = Double.parseDouble(Major[0]);
                                    double weight = Double.parseDouble(Major[1]);
                                    total = mark * weight;
                                } else {
                                    System.out.println("Invalid format in " + filename + " for student ID: " + id);
                                }
                                
                                if(i<=4)
                                {
                                    if(totalMinor1<=totalMinor2 && totalMinor1<=totalMinor3)
                                    {
                                        total+=totalMinor2+totalMinor3;
                                    }
                                    else if(totalMinor2<=totalMinor1 && totalMinor2<=totalMinor3)
                                    {
                                        total+=totalMinor1+totalMinor3;
                                    }
                                    else 
                                    {
                                        total+=totalMinor2+totalMinor1;
                                    }
                                }
                                else{
                                    total+=totalMinor1+totalMinor2+totalMinor3;
                                }
                                
                                
                            } catch (NoSuchElementException e) {
                                System.out.println("Error: Missing grade information for student ID " + id + " in file " + filename);
                            }
                        }
                    }
                }
                catch(Exception e){
                    System.out.println(e);
                }
            }
            
            if(100>=total  && total>=85)
            {
                System.out.println("marks for subject "+subjects[i]+" is "+total+"and grade is A+");
                cgpa += 10*credits[i];
            }
            else if(84>=total  && total>=75)
            {
                System.out.println("marks for subject "+subjects[i]+" is "+total+"and grade is A");
                cgpa += 9*credits[i];
            }
            else if(74>=total  && total>=65)
            {
                System.out.println("marks for subject "+subjects[i]+" is "+total+"and grade is B+");
                cgpa += 8*credits[i];
            }
            else if(64>=total  && total>=55)
            {
                System.out.println("marks for subject "+subjects[i]+" is "+total+"and grade is B");
                cgpa += 7*credits[i];
            }
            else if(54>=total  && total>=50)
            {
                System.out.println("marks for subject "+subjects[i]+" is "+total+"and grade is C");
                cgpa += 6*credits[i];
            }
            else if(49>=total  && total>=40)
            {
                System.out.println("marks for subject "+subjects[i]+" is "+total+"and grade is D");
                cgpa += 5*credits[i];
            }
            else
            {
                System.out.println("marks for subject "+subjects[i]+" is "+total+"and grade is F");
                cgpa += 0*credits[i];
            }
        }
        
        System.out.println("SGPA : "+(cgpa/21));
        System.out.println("");
    }
}