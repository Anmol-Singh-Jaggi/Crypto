#include<iostream>
#include<utility>
#include<algorithm>
#include<cstdlib>
#include<cassert>
using namespace std;

const int alphabet_size = 128; // ASCII 0-127...

// ROT13 is actually a Caesar Cipher with key being half the alphabet size...
// Key is actually the number of shifts to be performed...
void CaesarCipherEncrypt(string& message,const int& key=alphabet_size/2)
{
    for(int i=0; i<(int)message.size(); i++)
    {
        message[i]=((message[i]+key)%alphabet_size);
    }
}

int main()
{
    string message;
    cout<<"Enter message to encrypt [ASCII 0-127] - ";
    getline(cin,message);
    CaesarCipherEncrypt(message);
    cout<<"The encrypted message is - "<<message<<"\n";
    // The decryption algo is exactly same as the encyption algo...
    CaesarCipherEncrypt(message);
    cout<<"The decrypted message is - "<<message<<"\n";
}
