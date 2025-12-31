class SortedList extends List
{
    int size = 0;
    SortedList(int newarr[],int n)
    {
        super(newarr,n);
        int temp;   
        for(int i =0;i<n;i++)
        {
            for(int j = i+1;j<n;j++)
            {
                if(newarr[j]<newarr[i])
                {
                    temp = newarr[i];
                    newarr[i] = newarr[j];
                    newarr[j] = temp; 
                }
            }
        }
        size = n;
        for(int i =0;i<size;i++)
        {
            arr[i] = newarr[i];
        }
    }
    int find(int element)
    {
        int a = 0;
        int b = size -1;
        int m;
        int c = 1;
        while(a<=b)
        {
            m = ((a+b)/2);
            if(arr[m]== element)
            {
                System.out.println("Element found at index" + m);
                c = 0;
                return m;
            }
            else if(arr[m]< element)
            {
                a = m+1;
            }
            else
            {
                b = m-1;
            }
        }
        int min[] = new int[10];
        if(c == 1)
        {
            for(int i =0;i<size;i++)
            {
                min[i] = element - arr[i];
            }
            for(int i = 0;i<10;i++)
            {
                if(min[i]*-1>0)
                {
                    i = i*-1;
                    System.out.println("This element is not present in the list but it can be inserted at the index="+i);
                    return 0;
                }
            }
        }
        return 0;
    }
    void insert(int value)
    {
       int min[] = new int[10];
       int a = 0;
        int b = size -1;
        int m;
        int c = 0;
        while(a<=b)
        {
            m = ((a+b)/2);
            min[c] = arr[m];
            c++;
            if(arr[m]== value)
            {
                return;
            }
            else if(arr[m]< value)
            {
                a = m+1;
            }
            else
            {
                b = m-1;
            }
        }
        int el;
        if(value>arr[size-1])
        {
            ++size;
            arr[size-1] = value;
            return;
        }
        for(int i =0;i<size;i++)
            {
                min[i] = value - arr[i];
            }
            for(int i = 0;i<10;i++)
            {
                if(min[i]*-1>0)
                {
                    ++size;
                    int g = size;
                    int j = size-1;
                    while(g>i)
                    {
                        arr[g] = arr[j];
                        g--;
                        j--;
                    }
                    arr[i] = value;
                    return;
                }
            }
           
    }
    void delete(int value)
    {
        int a = 0;
        int b = size - 1;
        int m = 0;
        while(a<=b)
        {
            m = ((a+b)/2);
            if(arr[m]== value)
            {
                break;
            }
            else if(arr[m]< value)
            {
                a = m+1;
            }
            else
            {
                b = m-1;
            }
        }
        int i = m;
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
        System.out.println(size);
        for(int i =0;i<size;i++)
        {
            System.out.print(arr[i] + " ");
        }
    }
}