#include<iostream>
#include<map>
#include<utility>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cassert>
#include<set>
using namespace std;

const int alphabet_size = 26; // 'a'-'z'...
const int codomain_size=126-33+1; // ASCII 33-126...

vector<vector<char> > mapping(alphabet_size);
map<char,char> inverse_mapping;

void permute(vector<char>& char_order)
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
    int max_per_char=codomain_size/alphabet_size;

    vector<char> char_order(codomain_size);
    for(int i=0; i<codomain_size; i++)
    {
        char_order[i]=i+33;  // First place them in their original ASCII order...
    }

    permute(char_order);  // Randomly permute them...
    int char_order_iterator=0;
    for(int i=0; i<alphabet_size; i++)
    {
        mapping[i].resize((rand()%max_per_char)+1);
        for(int j=0; j<(int)mapping[i].size(); j++)
        {
            assert(char_order_iterator<(int)char_order.size());  // For debugging...
            mapping[i][j]=char_order[char_order_iterator++];  // For encryption...
            inverse_mapping[mapping[i][j]]=i+'a';  // For decryption...
        }
    }
}

void encrypt(string& message)
{
    for(int i=0; i<(int)message.size(); i++)
    {
        if(message[i]>='a'&&message[i]<='z')
        {
            message[i]=mapping[message[i]-'a'][rand()%mapping[message[i]-'a'].size()];
        }
        else
        {
            cout<<"Illegal alphabet '"<<message[i]<<"' in the message!!\n\nExiting\n\n";
            exit(1);
        }
    }
}

void decrypt(string& message)
{
    for(int i=0; i<(int)message.size(); i++)
    {
        message[i]=inverse_mapping[message[i]];
    }
}

void show_details()
{
    for(int i=0; i<26; i++)
    {
        cout<<"mapping["<<char('a'+i)<<"] = { ";
        for(int j=0; j<(int)mapping[i].size(); j++)
        {
            cout<<mapping[i][j]<<" ";
        }
        cout<<"}\n";
    }
    cout<<"\n\n";
    for(const auto& it:inverse_mapping)
    {
        cout<<"\ninv_mapping["<<it.first<<"] = "<<it.second;
    }
}
int main()
{
    srand(time(NULL));
    init();
    string message;
    cout<<"\n\nEnter message to encrypt [a-z] - ";
    getline(cin,message);
    encrypt(message);
    cout<<"The encrypted message is - "<<message<<"\n";
    decrypt(message);
    cout<<"The decrypted message is - "<<message<<"\n";
}
