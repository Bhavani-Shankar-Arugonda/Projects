class List
{
    int []arr = new int[50];
    int size;
    List(int newarr[],int n)
    {
        for(int i =0;i<n;i++)
        {
            arr[i] = newarr[i];
        }
        size = n;
    }
    int find(int value)
    {
        int i;
        if(size == 0)
        {
            return 100;
        }
        for(i = 0;i<size;i++)
        {
            if(arr[i] == value)
            {
                return i;
            }
        }
        if(i == size)
        {
            System.out.println("The element is not found");
            i = 100;
        }
        return i;
    }
    void insert(int value)
    {
        arr[size] = value;
        ++size;
    }
    void delete(int value)
    {
        int i = 0;
        if(size == 0)
        {
            System.out.println("The given element is not found");
            return;
        }
        for(i = 0;i<size;i++)
        {
            if(arr[i] == value)
            {
                break;
            }
            
        }
        if(i == size)
        {
            System.out.println("The given element is not found");
            return;
        }
        arr[i] = 0;
        int j = i+1;
        while(j < size)
        {
            arr[i] = arr[j];
            arr[j] = 0;
            i++;
            j++;
        }
        size--;
    }
    void display()
    {
        for(int i =0;i<size;i++)
        {
            System.out.print(arr[i] + " ");
        }
    }
}