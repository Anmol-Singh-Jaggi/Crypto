#include<iostream>
#include<sstream>
#include<map>
#include<utility>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cassert>
#include<set>
using namespace std;

vector<string> encrypt(string& message,const vector<int>& key)
{
    int rows=message.size()/key.size()+message.size()%key.size();  // The number of rows in the ciphertext...
    int cols=key.size();  // The number of columns in the ciphertext...
    vector<string> encryption(rows,string(cols,0));
    int last_row=rows-1,last_col=cols-(rows*cols-(int)message.size())-1;
    // (last_row,last_col) = coordinates of the last non-null character of the ciphertext...
    int k=1,message_iterator=0;
    while(k<=cols)
    {
        for(int j=0; j<cols; j++)
        {
            if(key[j]==k)
            {
                for(int i=0; i<rows; i++)
                {
                    if(i<last_row||(i==last_row&&j<=last_col))
                    {
                        encryption[i][j]=message[message_iterator++];
                    }
                }
                break;
            }
        }
        k++;
    }
    assert(message_iterator==(int)message.size());
    return encryption;
}

string decrypt(vector<string>& encryption,const vector<int>& key)
{
    string decryption;
    int k=1;
    while(k<=(int)encryption[0].size())
    {
        for(int j=0; j<(int)encryption[0].size(); j++)
        {
            if(key[j]==k)
            {
                for(int i=0; i<(int)encryption.size(); i++)
                {
                    if(encryption[i][j])
                    {
                        decryption+=encryption[i][j];
                    }
                }
                break;
            }
        }
        k++;
    }
    return decryption;
}

void show_encryption(const vector<string>& encryption,const vector<int>& key)
{
    for(int i=0; i<(int)key.size(); i++)
    {
        cout<<key[i]<<" ";
    }
    cout<<"\n";
    for(int i=0; i<(int)encryption.size(); i++)
    {
        for(int j=0; j<(int)encryption[i].size(); j++)
        {
            cout<<encryption[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

vector<int> input_key(const string& key_input)
{
    vector<int> key;
    stringstream ss(key_input);
    int temp;
    while(ss>>temp)
        key.push_back(temp);
    return key;
}
int main()
{
    srand(time(NULL));
    string message;
    cout<<"Enter message to encrypt [a-z] - ";
    getline(cin,message);
    string key_input;
    cout<<"Enter the key [ 1-indexed permutation of columns ]  ";
    getline(cin,key_input);
    vector<int> key=input_key(key_input);
    vector<string> encryption=encrypt(message,key);
    cout<<"The encrypted message is -: \n\n";
    show_encryption(encryption,key);
    string decryption=decrypt(encryption,key);
    cout<<"The decrypted message is - "<<decryption<<"\n";
}
