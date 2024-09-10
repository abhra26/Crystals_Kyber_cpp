#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

class Rq{
/*
Ring polynomial: Zq[X]/(X^n+1)
n = 2^n'-1; n'=9 => n=256
*/
private:
    int Q;
    vector<int> Coeffs;

public:
     
    Rq(vector<int> coeffs, int q){ // Constructor 
        int n = coeffs.size() - 1; 
        Coeffs = coeffs;
        Q = q;
        normalise();
    }
    
    Rq operator+(const Rq& other) const{ // Over-riding "+" operator 
        vector<int> result(max(Coeffs.size(),other.Coeffs.size()),0);
        for (int i=0;i<Coeffs.size();i++){
            result[i] += Coeffs[i];
        }
        for (int j=0;j<other.Coeffs.size();j++){
            result[j] += other.Coeffs[j];
        }
        
        return Rq(result,Q);
    }
    
    Rq operator*(const Rq& other) const{ // Over-riding "*" operator 
        vector<int> result(Coeffs.size()+other.Coeffs.size()-1,0);
        for (int i=0;i<Coeffs.size();i++){
            for (int j=0;j<other.Coeffs.size();j++){
                result[i+j] = (Coeffs[i]*other.Coeffs[j]) % Q;
            }
        }
        
        int deg = result.size() - Coeffs.size() - 1;
        int mult =0;
        for (int i=0;i<deg;i++){
            mult = result[i];
            result[i+ Coeffs.size()] -= mult;
            result[i] = 0;
        }
        
        vector<int> final_result(Coeffs.size(),0);
        int index = deg+1;
        
        for (int j=0;j<Coeffs.size();j++){
            final_result[j] = result[index];
            index++;
        }
        
        return Rq(final_result,Q);
    }
    
    Rq operator*(int scalar){ //Multiply with scalar
        vector<int> result(Coeffs.size(),0);
        for (int i=0;i<Coeffs.size();i++){
            result[i] = Coeffs[i]*scalar;
        }
        
        return Rq(result,Q);
    }

    Rq operator%(int scalar){ // Overiding "%" operator
        vector<int> result(Coeffs.size(),0);
        for (int i=0;i<Coeffs.size();i++){
            result[i] = Coeffs[i]%scalar;
        }

        return Rq(result,Q);
    }
    
    Rq pow(int scalar) const { //Over-riding Power operator
        vector<int> result(Coeffs.size(),0);
        int temp = 0;
        if (scalar == 0){
            return Rq({1},Q);
        }
        
        else{
            
            for (int i=0;i<Coeffs.size();i++){
                temp = Coeffs[i];
                for (int j=0;j<scalar;j++){
                    temp *= temp;
                }
                result[i] = temp;
            }
            return Rq(result,Q);
        }
    
    }
    
    void normalise(){ // Brings coeffs in range (-q/2,q/2]
        for(int i=0;i<Coeffs.size();i++){
            if (Coeffs[i]>=Q){
                Coeffs[i] = Coeffs[i] % Q;
            }
        }
    }
    
    //Getters and Setters
    void setCoeffs(vector<int> coeffs){
        Coeffs = coeffs;
    }
    
    void setQ(int q){
        Q = q;
    }
    
    vector<int> getCoeffs(){
        return Coeffs;
    }
    
    int getQ(){
        return Q;
    }
    
    // Print Functions
    void Print(){ //Function to print polynomial
        int n = Coeffs.size()-1;
        for (int i=0;i<Coeffs.size();i++){
            if (i==n){
                cout<<"("<<Coeffs[i]<<")";
            }
            else{
                cout<<"("<<Coeffs[i]<<")x^"<<n-i<<"+";
            }
        }
    }
    
};