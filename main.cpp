#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime> 
#include "Kyber.cpp"

using namespace std;

int main(){

    int k = 6;
    int n = 3;
    int Q = 17;

    cout<<"%_________Testing Begins_________%"<<endl;
    cout<<"Parameters for Testing"<<endl;
    cout<<"n= "<<n<<", k= "<<k<<", Q= "<<Q<<endl;
    cout<<"\n"<<endl;

    CRYSTALS_KYBER K1 = CRYSTALS_KYBER(n,k,Q);

    Rq** A = K1.Gen_A();
    cout<<"A matrix:"<<endl;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            A[i][j].Print();
            cout<<" ";
        }
        cout<<endl;
    }
    
    cout<<endl;
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

