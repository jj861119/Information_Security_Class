#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Ciphers{
    public:
    void InputPlainText(string plaintext,string key)
    {
        Plain_Text=plaintext;
        key_string=key;
    }
    void Carsar()
    {
        string ans="";
        int i,a='A',temp;
        int key=stoi(key_string);
        for(i=0;i<Plain_Text.length();i++)
        {      
            if(((int)Plain_Text[i]-key)<(int)('A'))
            {
                ans = ans + (char)(Plain_Text[i]-key+26);
            }
        else
            {
                ans = ans + (char)(Plain_Text[i]-key);
            }
        }
        for(i=0;i<ans.length();i++)
        putchar(tolower(ans[i]));
    }
    void Playfair()
    {
    int i,j,k,indexForGrid=0;
    string baseAlphabet="ABCDEFGHIKLMNOPQRSTUVWXYZ";
    string cipher;
    cipher.assign(Plain_Text);
    string key;
    key.assign(key_string);
    string ans="";
    char grid[5][5];
    char tempGrid[25];

    //delete same charactors in key
    for(i=0;i<key.size();i++)
    {
        j=i+1;
        while(j<key.size())
        {
            if(key[i]==key[j]){
                key.erase(j,1);
            }
            else
            {
                ++j;
            }
            
        }
    }
    
    //delete duplicate word with key in base
    for(i=0;i<key.length();i++){
        int num;
        num=baseAlphabet.find(key[i]);
        baseAlphabet.erase(num,1);
    }


    //create key grid

    //fill key into grid
    for(i=0;i<key.length();i++){
        tempGrid[i]=key[i];
    }


    for(i=key.length(),k=0;i<25;i++,k++){
        tempGrid[i]=baseAlphabet[k];
    }

    //turn tempGrid into 5x5 matrix
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            grid[i][j]=tempGrid[indexForGrid];
            indexForGrid++;
        }
    }

    //split cipher and search element 
    for(int z=0;z<cipher.length()/2;z++){
        int a=2*z;
        int row1,row2,col1,col2;
        for(i=0;i<5;i++){
            for(j=0;j<5;j++){
                if(grid[i][j]==cipher[a]){
                    row1=i,col1=j;
                }
                if(grid[i][j]==cipher[a+1]){
                    row2=i,col2=j;
                }
            }
        }
        //same row:take left element
        if(row1==row2){
            if(col1!=0)
                col1=col1-1;
            else
            {
                col1=4;
            }
            if(col2!=0)
                col2=col2-1;
            else
            {
                col2=4;
            }
            ans+=grid[row1][col1];
            ans+=grid[row2][col2];
        }
        //same column: take above letter
        else if(col1==col2){
            if(row1!=0)
                row1=row1-1;
            else
            {
                row1=4;
            }
            if(row2!=0)
                row2=row2-1;
            else
            {
                row2=4;
            }
            ans+=grid[row1][col1];
            ans+=grid[row2][col2];
        }
        else
        {
            ans+=grid[row1][col2];
            ans+=grid[row2][col1];
        }
        
    }
    for(i=0;i<ans.length();i++)
        putchar(tolower(ans[i]));
    }
    void Vernam()
    {
    string cipher;
    string key;
    cipher.assign(Plain_Text);
    key.assign(key_string);
    string plaintext="";
    char cipherletter,keyletter;
    int i;
    for(i=0;i<cipher.length();i++)
    {
        cipherletter=cipher[i];
        keyletter=key[i];
        int a=myXOR((int)(cipherletter-'A'),(int)(keyletter-'A'));
        char temp=(char)(a+'A');
        key+=temp;
        plaintext+=temp;
    }
    for(i=0;i<plaintext.length();i++)
        putchar(tolower(plaintext[i]));
    }
    void Row()
    {
    string cipher;
    string key;
    cipher.assign(Plain_Text);
    key.assign(key_string);
    int row;
    int emptycol;
    //how many elements in a column
    if(cipher.length()%key.length()==0)
    {
        row=cipher.length()/key.length();
        char table[row][key.length()];
        //fill table with plaintext
        for(int i=0;i<key.length();i++)
        {
            int index=0;
            int num=(int)(key[i]-48);
            for(int k=0;k<row;k++)
            {
                table[k][i]=cipher[row*(num-1)+index];
                index++;
            }
        }
        for(int i=0;i<row;i++){
            for(int j=0;j<key.length();j++){
                putchar(tolower(table[i][j]));
            }
        cout<<endl;
        }
    }
    //has empty columns
    else if((cipher.length()%key.length())!=0)
    {
        row=(cipher.length()/key.length())+1;
        emptycol=key.length()-(cipher.length()%key.length());
        int colElements[key.length()+1];

        for(int i=0;i<key.length();i++){
            if(i<emptycol){
                colElements[(int)(key[i]-'0')]=row;
            }
            else{
                colElements[(int)(key[i]-'0')]=row-1;
            }
        }

        
    
       //create table
       char table[row][key.length()];
       int indexOfDecrypt ;
       int indexOfCol;
       for(int i=0;i<key.length();i++){
           //fill elements in ith columns
            indexOfCol = (int)(key[i]-'0');
            indexOfDecrypt=0;
            for(int z=1;z<indexOfCol;z++){
                indexOfDecrypt += colElements[z];
            }
            //cout<<indexOfDecrypt<<endl;
            for(int j=0;j<colElements[indexOfCol];j++){
                table[j][i]=cipher[indexOfDecrypt+j];
            }
       }
       int sum;
        for(int z=1;z<=key.length();z++){
            sum += colElements[z];
        }
        int count=0;
       for(int i=0;i<row;i++){
        for(int j=0;j<key.length();j++)
        {   
            if(count==sum)
                break;
            putchar(tolower(table[i][j]));
            count++;
        }
       }
    }
    }
    void Rail(){
    string cipher;
    cipher.assign(Plain_Text);
    int key=stoi(key_string);
    int row=0,col=0;
    bool flag;

    // create matrix to cipher
    char rail[key][cipher.length()];

    //fill matrix
    for(int i=0;i<key;i++)
    {
        for(int j=0;j<cipher.length();j++)
        {
            rail[i][j]='\n';
        }
    }

    //mark with *
    for(int i=0;i<cipher.length();i++)
    {
        if(row==0)
            flag= true;
        if(row == key-1)
            flag = false;

        rail[row][col++]='*';

        if(flag)
            row++;
        else
            row--;
    }
    int index=0;
    for(int i=0;i<key;i++)
        for(int j=0;j<cipher.length();j++)
            {
                if(rail[i][j]=='*'&&index<cipher.length())
                    rail[i][j]=cipher[index++];
            }
    string res;

    row=0,col=0;
    for(int i=0;i<cipher.length();i++)
    {
        if(row==0)
            flag=true;
        if(row==key-1)
            flag=false;

        if(rail[row][col]!='*')
            res.push_back(rail[row][col++]);
        
        if(flag)
            row++;
        else
            row--;
    }
    for(int i= 0;i<res.length();i++)
        putchar(tolower(res[i]));
    }
private:
    int myXOR(int a,int b)
    {
        return (a|b)&(~a|~b);
    }
    string Plain_Text;
    string key_string;
    string result;
};

int main(int argc,char * argv[])
{
    Ciphers cipher;
    string result;
    if(argv[1]==string("caesar"))
    {
        cipher.InputPlainText(argv[3],argv[2]);
        cipher.Carsar();
    }
    else if (argv[1]==string("playfair"))
    {
        cipher.InputPlainText(argv[3],argv[2]);
        cipher.Playfair();
    }
    else if (argv[1]==string("vernam"))
    {
        cipher.InputPlainText(argv[3],argv[2]);
        cipher.Vernam();
    }
    else if (argv[1]==string("row"))
    {
        cipher.InputPlainText(argv[3],argv[2]);
        cipher.Row();
    }
    else if (argv[1]==string("rail_fence"))
    {
        cipher.InputPlainText(argv[3],argv[2]);
        cipher.Rail();
    }
    return 0;
}