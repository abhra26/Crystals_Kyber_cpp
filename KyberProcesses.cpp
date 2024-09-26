#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include "Kyber.cpp"
#include "Rq.cpp"

using namespace std;

class KyberProcess{
private:
    Rq** A;
    Rq* S;
    Rq* T;
    Rq* Message;
    Rq* u;
    Rq* v;
    Rq* Decipher;
    int Q;
    int n;
    int k;

public:

    KyberProcess(int N, int K, int q){
        n = N;
        k = K;
        Q = q;
    }

    Rq** T(Rq** A){ // Transpose of A 
    
        Rq **array = (Rq **)malloc(k * sizeof(Rq *));
            for (int i = 0; i < k; i++) {
                array[i] = (Rq *)malloc(k * sizeof(Rq));
            }
            
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                array[i][j] = A[j][i];
            }
        }
        
        return array;
    }

    Rq** PublicKey(){

        CRYSTALS_KYBER K1(n,k,Q);

        A = K1.GEN_A_matrix();
        S = K1.GEN_SECRET();
        T = K1.GEN_PK(A,S);

        cout<<"PUBLIC KEY GENERATION SUCCESSFUL"<<endl;
    }

    vector<vector<char>> GEN_2D_ARR(int rows, int cols) {
        vector<vector<char>> array(rows, vector<char>(cols));
        return array;
    }

    string text_to_binary(const string& text) {
        string binary;
        for (char c : text) {
            for (int i = 7; i >= 0; i--) {
                binary += (c & (1 << i)) ? '1' : '0';
            }
        }

        // Pad to nearest multiple of 256
        int padding = 256 - (binary.size() % 256);
        if (padding != 256) {
            binary.append(padding, '0');
        }

        return binary;
    }

    vector<vector<char>> Create_Chunks(const string& text) {
        string binary_stream = text_to_binary(text);
        int CHUNKS = binary_stream.size() / 256;
        int BITS = 256;

        vector<vector<char>> chunk_bin = GEN_2D_ARR(CHUNKS, BITS);

        for (int i = 0; i < CHUNKS; i++) {
            for (int j = 0; j < BITS; j++) {
                chunk_bin[i][j] = binary_stream[i * BITS + j];
            }
        }

        return chunk_bin;
    }

    int EncodeMSG(const string& text){ // Returns Encoded message in polynomial form
        vector<vector<char>> Chunks = Create_Chunks(text);
        int HIGH = 1;
        int LOW = 0;
        int size = 256;
        int mult = Q/2;
        int chunk_count = Chunks.size();
        Rq* Stream = (Rq*)malloc(256*sizeof(Rq));
        vector<int> arr(size,0);
        for (int i=0;i<chunk_count;i++){

            for(int j=0;j<size;j++){
                if (Chunks[i][j] == '1'){
                    arr[j] = HIGH* mult;
                }
                else{
                    arr[j] = LOW;
                }
            } // Char -> int

            Stream[i] = Rq(arr,Q);
        }
        
        Message = Stream;
        cout<<"MESSAGE PREPROCESSED"<<endl;

        return chunk_count;
    }

    void Encrypt(const string& text){
        int size = EncodeMSG(text);
        int random_arr[] = {-1,0,1};
        int index = 0;

        CRYSTALS_KYBER obj(n,k,Q);

        Rq** A_T = obj.T(A);
        Rq* R = (Rq*)malloc(k*sizeof(Rq));
        Rq* e1 = (Rq*)malloc(k*sizeof(Rq));
        Rq* result_u = (Rq*)malloc(k*sizeof(Rq));
        vector<int> arr1(n,0);
        vector<int> arr2(n,0);

        for (int i=0;i<k;i++){
            for (int j=0;j<n;j++){
                index = rand()%3;
                arr1[j] = random_arr[index];
            }
            R[i] = Rq(arr1,Q);

            for (int j=0;j<n;j++){
                index = rand()%3;
                arr2[j] = random_arr[index];
            }
            e1[i] = Rq(arr2,Q);
        }

        //result_u = A_T*r +e1 have to do 

        for (int i=0;i<k;i++){\
            result_u[i] = e1[i];
            for (int j=0;j<k;j++){
                result_u[i] = result_u[i] + A_T[i][j]*R[j]; 
            }
        }

        u = result_u;
        cout<<"U Generated"<<endl;

    }

};
