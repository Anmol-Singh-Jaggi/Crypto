#include<iostream>
#include<map>
#include<ctime>
#include<utility>
#include<algorithm>
#include<cstdlib>
#include<cassert>
using namespace std;

const int alphabet_size = 128; // ASCII 0-127...

map<char,char> mapping,inverse_mapping;
vector<char> char_order(alphabet_size);

// Generate a permutation of char_order...
void permute()
{
    int n=(int)char_order.size();
    for(int i=0; i<n; i++)
    {
        int j=(rand()%(n-i))+i;
        swap(char_order[j],char_order[i]);
    }
}

void init()
{
    srand(time(NULL));  // For rand()...

    for(int i=0; i<alphabet_size; i++)
    {
        char_order[i]=i;  // First place them in their original ASCII order...
    }

    permute();  // Randomly permute them...

    for(int i=0; i<alphabet_size; i++)
    {
        mapping[i]=char_order[i];  // For encryption...
        inverse_mapping[char_order[i]]=i;  // For decryption...
    }
}

void encrypt(string& message)
{
    for(int i=0; i<(int)message.size(); i++)
    {
        message[i]=mapping[message[i]];
    }
}

void decrypt(string& message)
{
    for(int i=0; i<(int)message.size(); i++)
    {
        message[i]=inverse_mapping[message[i]];
    }
}

int main()
{
    init();
    string message;
    cout<<"Enter message to encrypt  - ";
    getline(cin,message);
    encrypt(message);
    cout<<"The encrypted message is - "<<message<<"\n";
    decrypt(message);
    cout<<"The decrypted message is - "<<message<<"\n";
}
