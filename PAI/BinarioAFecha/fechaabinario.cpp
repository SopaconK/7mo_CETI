#include<iostream>
using namespace std;



int main(){
    int dia,mes,ano;
    cin>>dia>>mes>>ano;
    int binario=dia+32*mes+512*ano;
    cout<<binario<<endl;
}