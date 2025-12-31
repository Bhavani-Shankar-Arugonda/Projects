public class KVDatastore<T,V> {
    T[] keyArray ;
    V[] valueArray;
    int length;
    int top;

    KVDatastore(T[]kArray,V[]vArray)
    {
        if (kArray.length != vArray.length) {
            throw new IllegalArgumentException("Key and value arrays must have the same length.");
        }

        keyArray=kArray;
        valueArray=vArray;
        length=kArray.length;
        top=-1;
    }

    public void put(T a,V b)
    {
        try{
            for(int i=0; i<=top;i++)
            {
                if(a.equals(keyArray[i]))
                {
                    valueArray[i]=b;
                    return;
                }
            }
            keyArray[++top]=a;
            valueArray[top]=b;
            return;
        }catch(ArrayIndexOutOfBoundsException e)
        {
            System.out.println("Array is Already Full!! Cannot Add Element : "+e);
        }
    }

    public V get(T a)
    {
        if(top==-1)
        {
            return null;
        }
        for(int i=0; i<=top ;i++)
        {
            if(a.equals(keyArray[i]))
            {
                return valueArray[i];
            }
        }
        return null;
    }

    public void display()
    {
        System.out.println("Value   Key");
        for(int i=0; i<=top; i++)
        {
            System.out.println(keyArray[i]+"        "+valueArray[i]);
        }
    }
}
