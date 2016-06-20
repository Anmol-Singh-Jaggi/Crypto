#include<iostream>
#include<utility>
#include<algorithm>
#include<cstdlib>
#include<cassert>
using namespace std;

const int alphabet_size = 128; // ASCII 0-127...

pair<int,int> extended_gcd(int a,int b)  // a and b must be coprime.. Returns "x" in the equation "1 = x(a) + y(b)"..
{
    pair<int,int> coeffa(1,0);  // a=a(1) + b(0)
    pair<int,int> coeffb(0,1);  // b=a(0) + b(1)
    pair<int,int> temp;
    int q,r;
    do
    {
        q=a/b;
        r=a%b;
        temp=coeffb;
        coeffb=make_pair(coeffa.first-q*coeffb.first,coeffa.second-q*coeffb.second);
        coeffa=temp;
        a=b;
        b=r;
    }
    while(r);
    return coeffa;
}

int inverse_mod(int n,int mod)  // Calculate ans = (n inverse) modulo (mod) such that (ans*n)%mod = 1...
{
    assert(__gcd(n,mod)==1);
    return (extended_gcd(n,mod).first+mod)%mod;
}

// (a,b) forms the key...
void AffineCipherEncrypt(string& message,const int& a,const int& b)
{
    for(int i=0; i<(int)message.size(); i++)
    {
        message[i]=(message[i]*a+b)%alphabet_size;
    }
}

void AffineCipherDecrypt(string& message,const int& a,const int& b)
{
    int a_inv=inverse_mod(a,alphabet_size);
    for(int i=0; i<(int)message.size(); i++)
    {
        message[i]=((message[i]-b+alphabet_size)*a_inv)%alphabet_size;
    }
}

int main()
{
    string message;
    int a,b;  // (a,b) form the key...
    cout<<"Enter message to encrypt [ASCII 0-127] ";
    getline(cin,message);
    cout<<"Enter a number coprime with "<<alphabet_size<<" ";
    cin>>a;
    cout<<"Enter another number ";
    cin>>b;
    AffineCipherEncrypt(message,a,b);
    cout<<"The encrypted message is - "<<message<<"\n";
    AffineCipherDecrypt(message,a,b);
    cout<<"The decrypted message is - "<<message<<"\n";
}
