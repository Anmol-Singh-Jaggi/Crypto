#include<iostream>
#include<utility>
#include<algorithm>
#include<cstdlib>
#include<cassert>
using namespace std;

const int alphabet_size = 128; // ASCII 0-127...

// Key is actually the number of shifts to be performed...
void CaesarCipherEncrypt(string& message,const int& key)
{
    for(int i=0; i<(int)message.size(); i++)
    {
        message[i]=((message[i]+key)%alphabet_size);
    }
}

void CaesarCipherDecrypt(string& message,const int& key)
{
    for(int i=0; i<(int)message.size(); i++)
    {
        message[i]=((message[i]-key+alphabet_size)%alphabet_size);
    }
}

int main()
{
    string message;
    int key;
    cout<<"Enter message to encrypt [ASCII 0-127] - ";
    getline(cin,message);
    cout<<"Enter the key [ Number of shifts ] - ";
    cin>>key;
    CaesarCipherEncrypt(message,key);
    cout<<"The encrypted message is - "<<message<<"\n";
    CaesarCipherDecrypt(message,key);
    cout<<"The decrypted message is - "<<message<<"\n";
}
