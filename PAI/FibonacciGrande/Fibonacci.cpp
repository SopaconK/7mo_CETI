#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>> fibo;


vector<int> sum(vector<int> &a, vector<int> &b){
    int sz=max(a.size(), b.size());
    bool carry=0;
    vector<int> ans;
    int i=0;
    while( i<sz){
        int x=0, y=0;
        if(i<a.size()) x=a[i];
        if(i<b.size()) y=b[i];
        x+=y;
        x+=carry;
        if(x>=100000000){
            carry=1;
        }
        else{
            carry=0;
        }
        ans.push_back(x%100000000);
        i++;
    }
    if(carry){
        ans.push_back(1);
    }
    return ans;
}

void fib(int n){
    int i=2;
   while(i<=n){
    fibo[i]=sum(fibo[i-1], fibo[i-2]);
    i++;
   }
}


void imprimir (vector<int> &a){
    int i=a.size()-1;
    while( i>=0){
        string s=to_string(a[i]);
        int c=s.size();
        if(i!=a.size()-1){
        while(c<8){
            cout<<"0";
            c++;
        }
        }
        cout<<s;
        i--;
    }

}


int main(){
    int n;
    cout<<"Cual fibonacci?"<<endl;
    cin>>n;  
    fibo.resize(n+1);  
    fibo[0]={0};
    fibo[1]={1};
    fib(n);
    imprimir(fibo[n]);
    
}