#include<iostream>
#include<utility>
#include<algorithm>
#include<cstdlib>
#include<cassert>
using namespace std;

const int alphabet_size = 128; // ASCII 0-127...

// Operation performed = Modular Addition...
void encrypt(string& message,const string& key)
{
    for(int i=0; i<(int)message.size(); i++)
    {
        message[i]=(message[i]+key[i])%alphabet_size;
    }
}

void decrypt(string& message,const string& key)
{
    for(int i=0; i<(int)message.size(); i++)
    {
        message[i]=(message[i]-key[i]+alphabet_size)%alphabet_size;
    }
}

int main()
{
    string message,key;
    cout<<"Enter message to encrypt [ASCII 0-127] - ";
    getline(cin,message);
    cout<<"Enter key to encrypt [ASCII 0-127] - ";
    getline(cin,key);
    if(key.size()!=message.size())
    {
        cout<<"Key should be atleast as long as the message !!\n";
        exit(1);
    }
    encrypt(message,key);
    cout<<"The encrypted message is - "<<message<<"\n";
    decrypt(message,key);
    cout<<"The decrypted message is - "<<message<<"\n";
}
