#include<iostream>
using namespace std;


int main(){
    int binario;
    cin>>binario;
    int dia, mes,ano;
    dia=binario%32;
    binario/=32;
    mes=binario%16;
    ano=binario/=16;
    int diaspormes[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(mes<1 || mes>12){
        cout<<"Mes incorrecto"<<endl;
        return -1;
    }
    bool bisiesto=false;
    if(ano%4==0){
        if(ano%100==0){
            if(ano%400==0)bisiesto=true;
            else bisiesto=false;
        }
        else{
            bisiesto=true;
        }
    }
    if(bisiesto) diaspormes[2]++;
    if(dia<1 || dia>diaspormes[mes]){
        cout<<"Dia incorrecto";
        return -1;
    }
    cout<<dia<<" "<<mes<<" "<<ano<<endl;


    


}