#include<iostream>
#include<algorithm>
using namespace std;

class Fraccion{
    public:
        int entero;
        int numerador;
        int denominador;
        Fraccion(int a, int b): numerador(a), denominador(b){
            int d=abs(__gcd(numerador, denominador));
            if(d!=0){
                numerador/=d;
                denominador/=d;
                entero=numerador/denominador;
                numerador%=denominador;
            }
        }
        
};


Fraccion sum(Fraccion a, Fraccion b){
    int num=a.numerador*b.denominador+a.denominador*b.numerador;
    int den=a.denominador*b.denominador;
    num+=(a.entero+b.entero)*den;
    return Fraccion(num,den);
}

Fraccion resta(Fraccion a, Fraccion b){
    int num=a.numerador*b.denominador-a.denominador*b.numerador;
    int den=a.denominador*b.denominador;
    num+=(a.entero-b.entero)*den;
    return Fraccion(num,den);
}

Fraccion mult(Fraccion a, Fraccion b){
    int num=(a.numerador+a.entero*a.denominador)*(b.numerador+b.entero*b.denominador);
    int den=a.denominador*b.denominador;
    return Fraccion(num,den);
}

Fraccion div(Fraccion a, Fraccion b){
    int num=(a.numerador+a.entero*a.denominador)*b.denominador;
    int den=a.denominador*(b.numerador+b.entero*b.denominador);
    return Fraccion(num,den);
}


void Imprimir(Fraccion x){
    if(x.entero!=0){
        cout<<x.entero<<" ";
    }
    if(x.numerador!=0){
        cout<<x.numerador<<"/"<<x.denominador<<endl;
    }
    if(x.entero==0 && x.numerador==0){
        cout<<0<<endl;
    }
}


int main(){
    int a,b,c,d;
    cout<<"Dame numerador primera fraccion"<<endl;
    cin>>a;
    cout<<"Dame denominador primera fraccion"<<endl;
    cin>>b;
    cout<<"Dame numerador segunda fraccion"<<endl;
    cin>>c;
    cout<<"Dame denominador segunda fraccion"<<endl;
    cin>>d;
    if(b==0 || d==0){
        cout<<"No puedes dividir entre 0";
        return -1;
    }
    Fraccion x=Fraccion(a,b);
    Fraccion y=Fraccion(c,d);
    cout<<"Elige operacion 1:+ 2:- 3:* 4: /"<<endl;
    int op;
    cin>>op;
    if(op==1){
        Imprimir(sum(x,y));
    }
    if(op==2){
        Imprimir(resta(x,y));
    }
    if(op==3){
        Imprimir(mult(x,y));
    }
    if(op==4){
        if(y.numerador==0){
            cout<<"No puedes dividir entre 0"<<endl;
        }
        else Imprimir(div(x,y));
    }
}