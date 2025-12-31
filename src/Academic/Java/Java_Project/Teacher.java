/**
 * This class implements all the functionalities of a teacher of a particular subject.
 * It stores all the data corresponding to the students into text files corresponding to the subject.
 * 
 * @author BHAVANI SHANKAR ARUGONDA
 * @version 01-05-2025
 */


import java.io.*;
import java.util.*;

public class Teacher {
    String fileName;
    String teacherId;

    Teacher(String subject, String teacherId) {
        this.fileName = subject + ".txt";
        this.teacherId = teacherId;

        try {
            File file = new File(fileName);
            if (!file.exists()) {
                System.out.println("File does not exist. Creating: " + fileName);
                file.createNewFile(); 
            } else {
                DeleteEmptyLines();
            }
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private void DeleteEmptyLines() {
        List<String> nonEmptyLines = new ArrayList<>();
        try (Scanner sc = new Scanner(new File(fileName))) {
            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                if (!line.trim().isEmpty()) {
                    nonEmptyLines.add(line);
                }
            }
            try (FileWriter writer = new FileWriter(fileName, false)) {
                for (String line : nonEmptyLines) {
                    writer.write(line + "\n");
                }
            }
        } catch (IOException e) {
            System.out.println("Error during empty line removal: " + e.getMessage());
        }
    }

    private void copyFiles(String sourceFile, String destinationFile) {
        File src = new File(sourceFile);
        File dest = new File(destinationFile);

        try (Scanner sc = new Scanner(src); FileWriter writer = new FileWriter(dest, false)) {
            while (sc.hasNextLine()) {
                writer.write(sc.nextLine() + "\n");
            }
        } catch (IOException e) {
            System.out.println("Error during file copy: " + e.getMessage());
        }
    }

    public static boolean isStudentExist(String id, String FILENAME) {
        File file = new File(FILENAME);
        if (!file.exists()) {
            System.out.println("File not found: " + FILENAME);
            return false;
        }

        boolean isExist = false;
        try (Scanner sc = new Scanner(file)) {
            while (sc.hasNextLine()) {
                if (sc.nextLine().trim().equals(id)) {
                    isExist = true;
                    break;
                }
            }
        } catch (IOException e) {
            System.out.println("Error checking student existence: " + e.getMessage());
        }
        return isExist;
    }

    public void addStudent(String studentId, String newName, String minor1, String minor2, String minor3, String major) {
        if (isStudentExist(studentId,fileName)) {
            System.out.println("Student Already Exists, Cannot Add!!");
            return;
        }

        try (FileWriter add = new FileWriter(fileName, true)) {
            add.write(studentId + "\n");
            add.write(newName + "\n");
            add.write(minor1 + "\n");
            add.write(minor2 + "\n");
            add.write(minor3 + "\n");
            add.write(major + "\n");
        } catch (IOException e) {
            System.out.println("Error adding student: " + e.getMessage());
        }
    }

    public void displayData() {
        try (Scanner sc = new Scanner(new File(fileName))) {
            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                if (!line.trim().isEmpty()) {
                    System.out.println(line);
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }

    public void updateData(String studentId, String newName, String minor1, String minor2, String minor3, String major) {
        if (!isStudentExist(studentId,fileName)) {
            System.out.println("Student Does Not Exist, Cannot Update!!");
            return;
        }
    
        try {
            File tempFile = File.createTempFile("temp", ".txt");
            File file = new File(fileName);
            try (Scanner sc = new Scanner(file); FileWriter update = new FileWriter(tempFile)) {
                while (sc.hasNextLine()) {
                    String line = sc.nextLine();
    
                    if (line.trim().equals(studentId)) {
                        
                        update.write(studentId + "\n");
                        update.write(newName + "\n");
                        update.write(minor1 + "\n");
                        update.write(minor2 + "\n");
                        update.write(minor3 + "\n");
                        update.write(major + "\n");
    
                        for (int i = 0; i < 5 && sc.hasNextLine(); i++) {
                            sc.nextLine();
                        }
                    } else {
                        update.write(line + "\n");
                    }
                }
            }
    
            copyFiles(tempFile.getAbsolutePath(), fileName);
            tempFile.delete();
            System.out.println("Data updated successfully.");
        } catch (IOException e) {
            System.out.println("Error updating student data: " + e.getMessage());
        }
    }

    public void deleteData(String studentId)
    {
        if (!isStudentExist(studentId,fileName)) {
            System.out.println("Student Does Not Exist, Cannot Delete!!");
            return;
        }
        
        try {
            File tempFile = File.createTempFile("temp", ".txt");
            File file = new File(fileName);
            try (Scanner sc = new Scanner(file); FileWriter update = new FileWriter(tempFile)) {
                while (sc.hasNextLine()) {
                    String line = sc.nextLine();
    
                    if (line.trim().equals(studentId)) {
    
                        for (int i = 0; i < 5 && sc.hasNextLine(); i++) {
                            sc.nextLine();
                        }
                    } else {
                        update.write(line + "\n");
                    }
                }
            }
    
            copyFiles(tempFile.getAbsolutePath(), fileName);
            tempFile.delete();
            System.out.println("Data deleted successfully.");
        } catch (IOException e) {
            System.out.println("Error deleting student data: " + e.getMessage());
        }
    }
}
