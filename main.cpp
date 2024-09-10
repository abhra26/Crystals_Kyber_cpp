#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
//#include "/home/abhraneelsaha/Desktop/HSM/Software_Files/Rq.cpp"
#include "/home/abhraneelsaha/Desktop/HSM/Software_Files/Kyber.cpp"

int main()
{
    /*
    vector<int> coeffs1 = {1,22,35,58,6,7,67,23};
    int q = 5;
    Rq P1 = Rq(coeffs1,q);
    P1.Print();
    
    vector<int> coeffs2 = {1,21,35,8,64,27,67,24};
    Rq P2 = Rq(coeffs2,q);
    P2.Print();
    cout<<endl;
    
    Rq P3 = P1+P2;
    cout<<"Addition P1+P2 = ";
    P3.Print();
    cout<<endl;
    
    Rq P4 = P1*P2;
    cout<<"Multiplication P1*P2 = ";
    P4.Print();
    cout<<endl;
    
    Rq P5 = P1.pow(2);
    cout<<"Power P1**2 = ";
    P5.Print();
    cout<<endl;
    
    Rq P6 = P1*17;
    cout<<"P1*17 = ";
    P6.Print();
    cout<<endl;
    return 0;
    */
    

    int k = 3;
    int n = 3;
    int Q = 17;

    cout<<"%_________Testing Begins_________%"<<endl;
    cout<<"Parameters for Testing"<<endl;
    cout<<"n= "<<n<<", k= "<<k<<", Q= "<<Q<<endl;
    cout<<"\n"<<endl;

    CRYSTALS_KYBER K1 = CRYSTALS_KYBER(n,k,Q);

    Rq** A = K1.GEN_A_matrix();
    cout<<"A matrix:"<<endl;
    K1.Print(A);
    cout<<"\n"<<endl;

    Rq* S = K1.GEN_SECRET();
    cout<<"S matrix:"<<endl;
    for (int i=0;i<k;i++){
        S[i].Print();
        cout<<endl;
    }
    cout<<"\n"<<endl;

    Rq* T = K1.GEN_PK(A,S);
    cout<<"T matrix:"<<endl;
    for (int i=0;i<k;i++){
        T[i].Print();
        cout<<endl;
    }
    cout<<"\n"<<endl;

    cout<<"T and A form the public key. S forms the secret key"<<endl;
    cout<<"%________END________%"<<endl;
}