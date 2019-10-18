#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string subKey[16];

int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
			60, 52, 44, 36, 28, 20, 12, 4,
			62, 54, 46, 38, 30, 22, 14, 6,
			64, 56, 48, 40, 32, 24, 16, 8,
			57, 49, 41, 33, 25, 17, 9,  1,
			59, 51, 43, 35, 27, 19, 11, 3,
			61, 53, 45, 37, 29, 21, 13, 5,
			63, 55, 47, 39, 31, 23, 15, 7};

int IP_1[] = {40, 8, 48, 16, 56, 24, 64, 32,
			  39, 7, 47, 15, 55, 23, 63, 31,
			  38, 6, 46, 14, 54, 22, 62, 30,
			  37, 5, 45, 13, 53, 21, 61, 29,
			  36, 4, 44, 12, 52, 20, 60, 28,
			  35, 3, 43, 11, 51, 19, 59, 27,
			  34, 2, 42, 10, 50, 18, 58, 26,
			  33, 1, 41,  9, 49, 17, 57, 25};

int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
			   1, 58, 50, 42, 34, 26, 18,
			  10,  2, 59, 51, 43, 35, 27,
			  19, 11,  3, 60, 52, 44, 36,
			  63, 55, 47, 39, 31, 23, 15,
			   7, 62, 54, 46, 38, 30, 22,
			  14,  6, 61, 53, 45, 37, 29,
			  21, 13,  5, 28, 20, 12,  4};

int PC_2[] = {14, 17, 11, 24,  1,  5,
			   3, 28, 15,  6, 21, 10,
			  23, 19, 12,  4, 26,  8,
			  16,  7, 27, 20, 13,  2,
			  41, 52, 31, 37, 47, 55,
			  30, 40, 51, 45, 33, 48,
			  44, 49, 39, 56, 34, 53,
			  46, 42, 50, 36, 29, 32};

int E[] = {32,  1,  2,  3,  4,  5,
		    4,  5,  6,  7,  8,  9,
		    8,  9, 10, 11, 12, 13,
		   12, 13, 14, 15, 16, 17,
		   16, 17, 18, 19, 20, 21,
		   20, 21, 22, 23, 24, 25,
		   24, 25, 26, 27, 28, 29,
		   28, 29, 30, 31, 32,  1};


int S_BOX[8][4][16] = {
	{  
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},  
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},  
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, 
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} 
	},
	{  
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},  
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, 
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},  
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}  
	}, 
	{  
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},  
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},  
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},  
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}  
	}, 
	{  
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},  
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},  
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},  
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}  
	},
	{  
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},  
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},  
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},  
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}  
	},
	{  
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},  
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},  
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},  
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}  
	}, 
	{  
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},  
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},  
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},  
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}  
	}, 
	{  
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},  
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},  
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},  
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}  
	} 
};

int P[] = {16,  7, 20, 21,
		   29, 12, 28, 17,
		    1, 15, 23, 26,
		    5, 18, 31, 10,
		    2,  8, 24, 14,
		   32, 27,  3,  9,
		   19, 13, 30,  6,
		   22, 11,  4, 25 };

//int shiftBits[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

string Bin2str(string str){
    string res;
    string temp;
    int i=0;
    for(i=0;i<16;i++){
        temp=str.substr(0,4);
        str.erase(0,4);
        if(!temp.compare("0000")){
            res+="0";
        }
        else if(!temp.compare("0001")){
            res+="1";
        }
        else if(!temp.compare("0010")){
            res+="2";
        }
        else if(!temp.compare("0011")){
            res+="3";
        }
        else if(!temp.compare("0100")){
            res+="4";
        }
        else if(!temp.compare("0101")){
            res+="5";
        }
        else if(!temp.compare("0110")){
            res+="6";
        }
        else if(!temp.compare("0111")){
            res+="7";
        }
        else if(!temp.compare("1000")){
            res+="8";
        }
        else if(!temp.compare("1001")){
            res+="9";
        }
        else if(!temp.compare("1010")){
            res+="A";
        }
        else if(!temp.compare("1011")){
            res+="B";
        }
        else if(!temp.compare("1100")){
            res+="C";
        }
        else if(!temp.compare("1101")){
            res+="D";
        }
        else if(!temp.compare("1110")){
            res+="E";
        }
        else if(!temp.compare("1111")){
            res+="F";
        }        
    }
    return res;
}

string str2Bin(string sHex){
    string sReturn = "";
			for (int i = 0; i < sHex.length (); ++i)
			{
				switch (sHex [i])
				{
					case '0': sReturn.append ("0000"); break;
					case '1': sReturn.append ("0001"); break;
					case '2': sReturn.append ("0010"); break;
					case '3': sReturn.append ("0011"); break;
					case '4': sReturn.append ("0100"); break;
					case '5': sReturn.append ("0101"); break;
					case '6': sReturn.append ("0110"); break;
					case '7': sReturn.append ("0111"); break;
					case '8': sReturn.append ("1000"); break;
					case '9': sReturn.append ("1001"); break;
					case 'A': sReturn.append ("1010"); break;
					case 'B': sReturn.append ("1011"); break;
					case 'C': sReturn.append ("1100"); break;
					case 'D': sReturn.append ("1101"); break;
					case 'E': sReturn.append ("1110"); break;
					case 'F': sReturn.append ("1111"); break;
				}
			}
			return sReturn;
}

string leftRotate(string str,int d){
    string s=str;
    reverse(s.begin(), s.begin()+d); 
    reverse(s.begin()+d, s.end()); 
    reverse(s.begin(), s.end()); 
    return s;
}

void generateKey(string key){
    string res="";
    string left="",right="";
    string init;
    int i,j,dis=0;
    //do for PC-1
    for(i=0;i<56;i++){
        res+=key[PC_1[i]-1];
    }

    init.assign(res);
    for(i=0;i<16;i++){
        string concat="";
        string ans="";
        //split into L,R
        left.assign(init,0,28);
        right.assign(init,28,28);

        //left rotate
        if(i==0||i==1||i==8||i==15){
            dis=1;
        }
        else
        {
            dis=2;
        }

        left=leftRotate(left,dis);
        right=leftRotate(right,dis);
    
        concat.assign(left);
        concat+=right;
        //assign for next rounds' L,R
        init.assign(concat);

        //do PC-2
        for(j=0;j<48;j++){
            ans+=concat[PC_2[j]-1];
        }

        subKey[i].assign(ans);
    }
}

string int2str(int num){
    int i;
    string ans="";
    switch (num)
    {
    case 0:
        ans.append("0000");
        break;
    case 1:
        ans.append("0001");
        break;
    case 2:
        ans.append("0010");
        break;
    case 3:
        ans.append("0011");
        break;
    case 4:
        ans.append("0100");
        break;
    case 5:
        ans.append("0101");
        break;
    case 6:
        ans.append("0110");
        break;
    case 7:
        ans.append("0111");
        break;
    case 8:
        ans.append("1000");
        break;
    case 9:
        ans.append("1001");
        break;
    case 10:
        ans.append("1010");
        break;
    case 11:
        ans.append("1011");
        break;
    case 12:
        ans.append("1100");
        break;
    case 13:
        ans.append("1101");
        break;
    case 14:
        ans.append("1110");
        break;
    case 15:
        ans.append("1111");
        break;
    }
    return ans;
}

string f_function(string str,int round){
    string expand="",myXOR="",sub="";
    string key,afterSBOX,finalresult="";
    key.assign(subKey[15-round]);
    int i,j;
    //expand 32bits to 48bits
    for(i=0;i<48;i++){
        expand+=str[E[i]-1];
    }

    //XOR with subKey
    for(i=0;i<48;i++){
        if(expand[i]==key[i]){
            myXOR+='0';
        }
        else
        {
            myXOR+='1';
        }
    }

    //replace with s_box
    for(i=0;i<8;i++){
        sub=myXOR.substr(i*6,6);
        int row=(sub[0]-'0')*2+(sub[5]-'0');
        int col=(sub[1]-'0')*8+(sub[2]-'0')*4+(sub[3]-'0')*2+(sub[4]-'0');
        int ansInSBox=S_BOX[i][row][col];
        afterSBOX.append(int2str(ansInSBox));
    }
    //replace with p permutation
    for(i=0;i<32;i++){
        finalresult+=afterSBOX[P[i]-1];
    }
    return finalresult;
}

string decrypt(string plain){
    string ipstr="",left,right;
    string newLeft;
    string f;
    string cipher="",cur;
    int i,j;
    //do IP to plaintext
    for(i=0;i<64;i++){
        ipstr+=plain[IP[i]-1];
    }
    
    left.assign(ipstr,0,32);
    right.assign(ipstr,32,32);

    for(i=0;i<16;i++){
        f.assign(f_function(right,i));
        newLeft.assign(right);
        right="";
        //do XOR :left and f
        for(j=0;j<32;j++){
            if(left[j]==f[j]){
                right.append("0");
            }
            else{
                right.append("1");
            }
        }
        left.assign(newLeft);
    }

    //combine L16&R16
    cur.assign(right);
    cur.append(left);

    //do IP-1
    for(i=0;i<64;i++){
        cipher+=cur[IP_1[i]-1];
    }
    
    return cipher;
}

int main(int argc,char *argv[]){
    string plain;
    string key_str;
    string cipher_text;

    key_str.assign(argv[1]);
    cipher_text.assign(argv[2]);

    //delete "0x" in string
    cipher_text.erase(0,2);
    key_str.erase(0,2);
    
    //turn plaintext and key into binary
    string cipher = str2Bin(cipher_text);
    string key= str2Bin(key_str);

    generateKey(key);

    plain.assign(decrypt(cipher));
    plain=(Bin2str(plain));

    string res="0x";
    for(int i=0;i<plain.length();i++){
        res+=tolower(plain[i]);
    }

    cout<<res<<endl;
    return 0;
}