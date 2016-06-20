#include<iostream>
#include<utility>
#include<algorithm>
#include<cstdlib>
#include<cassert>
using namespace std;

const int alphabet_size = 128; // ASCII 0-127...

// Pad the key to it as long as the message...
void pad_key(string& key,const string& message)
{
    string new_key(message);
    for(int i=(int)key.size(); i<(int)new_key.size(); i++)
    {
        new_key[i]=key[i%key.size()];
    }
    key=new_key;
}

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
    cout<<"Enter the key [ASCII 0-127] - ";
    getline(cin,key);
    pad_key(key,message);
    encrypt(message,key);
    cout<<"The encrypted message is - "<<message<<"\n";
    decrypt(message,key);
    cout<<"The decrypted message is - "<<message<<"\n";
}
