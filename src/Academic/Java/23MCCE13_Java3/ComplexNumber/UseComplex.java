class UseComplex
{
    static Complex retGreater(Complex m, Complex n){
        if (m.a >= n.a && m.b >=n.b){
            return m;
        }else if(n.a >= m.a && n.b >= m.b){
            return n;
        }else{
            return null;
        }
        
    }
    public static void main(String[] args){
        
        Complex c1 = new Complex(1,1);
        System.out.print("Complex Number C1 :");
        c1.display();

        Complex c2 = new Complex(1,2);
        System.out.print("Complex Number C2 :");
        c2.display();

        Complex c3 = c2.multiplyWith(c1); 
        System.out.print("Complex Number C1*C2 :");
        c3.display();

        Complex c4 = c1.divisionWith(c2);
        System.out.print("Complex Number C1/C2 :"); 
        c4.display();
    }
}

