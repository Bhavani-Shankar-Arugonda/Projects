import java.io.*;
import java.util.*;

class UseSLL
{
    static void displayMenu()
    {
        System.out.println("1.To insert element");
        System.out.println("2.To delete Node");
        System.out.println("3.To find maximum value in list");
        System.out.println("4.To see length of list");
        System.out.println("5.To display list");
        System.out.println("6.Create a New SLL");
        System.out.println("7.Save SLL to file");
        System.out.println("8.Load SLL from file");
        System.out.println("9.To exit the program");
        System.out.print("\nEnter your choice : ");
    }

    static void useSLL()
    {
        SLL list = new SLL();
        Scanner sc = new Scanner(System.in);

        int choice = 0;
        displayMenu();

        while(choice != 9)
        {
            choice = sc.nextInt();
            sc.nextLine();

            switch(choice)
            {
                case 1: System.out.print("Enter postion(Node will be added after that position)(for starting list enter 0) : ");
                        int pos = sc.nextInt();
                        System.out.print("Enter Data : ");
                        list.insertAfter(pos, sc.nextInt());
                        break;
                
                case 2: System.out.print("Enter postion(that position node will be deleted) : ");
                        list.deleteNode(sc.nextInt());
                        break;
                case 3: int max = list.Max();
                        if(max != -1)
                            System.out.println("Max of list : "+max);
                        break;
                
                case 4: int length = list.length();
                        if(length != -1)
                            System.out.println("Length of List : " + length);
                        break;

                case 5:list.displayList();
                        break;

                case 6:
                        SLL newlist = new SLL();
                        list=newlist;
                        break;

                case 7:
                        System.out.println("Enter file name as .sll");
                        String name= sc.nextLine();
                        try
                        {
                            File newFile = new File(name);
                            if (!newFile.exists()){
                                newFile.createNewFile();
                            }
                            FileOutputStream fos = new FileOutputStream(newFile);
                            ObjectOutputStream oos = new ObjectOutputStream(fos);

                            oos.writeObject(list);
                            oos.close();
                              fos.close();

                        }catch(IOException e)
                        {
                            System.out.println(e);
                        }
                        break;

                case 8:
                        File directory = new File(".");
                        FilenameFilter sllFilter = new FilenameFilter() {
                        @Override
                        public boolean accept(File dir, String name) {
                            return name.toLowerCase().endsWith(".sll");
                            }
                        };

                        String[] sllFiles = directory.list(sllFilter);
                        for(int i=0; i<sllFiles.length;i++)
                        {
                            System.out.println("Enter "+i+" to load "+ sllFiles[i]);
                        }
                        int a=-1;
                        System.out.print("Enter here : ");
                        a=sc.nextInt();
                        System.out.println("");

                        File file = new File(sllFiles[a]);
                        try{
                            FileInputStream fis = new FileInputStream(file);
                            ObjectInputStream ois= new ObjectInputStream(fis);
                            Object obj = ois.readObject();
                            list = (SLL)obj;
                        }
                        catch(IOException | ClassNotFoundException e)
                        {
                            System.out.println(e);
                        }
                        break;

                case 9: System.out.println("Exiting the progam......");
                        break;

                default:    System.out.println("Error, wrong choice input, try agian!");
                            break;
            }

            if(choice != 9)
            {
                System.out.print("\nEnter your choice : ");
            }
            displayMenu();
        }
        sc.close();
    }

    public static void main(String[] args)
    {
        useSLL();
    }
}