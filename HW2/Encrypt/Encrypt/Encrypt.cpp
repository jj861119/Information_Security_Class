#include <iostream>
#include <string>
#include<vector>
#include <bitset>
using namespace std;


int IP[8][8] = {
{58, 50, 42, 34, 26, 18, 10, 2 },
{60, 52, 44, 36, 28, 20, 12, 4 },
{62, 54, 46, 38, 30, 22, 14, 6 },
{64, 56, 48, 40, 32, 24, 16, 8 },
{57, 49, 41, 33, 25, 17,  9, 1 },
{59, 51, 43, 35, 27, 19, 11, 3 },
{61, 53, 45, 37, 29, 21, 13, 5 },
{63, 55, 47, 39, 31, 23, 15, 7 },
};
int IP_inverse[8][8] = {
{40, 8, 48, 16, 56, 24, 64, 32 },
{39, 7, 47, 15, 55, 23, 63, 31 },
{38, 6, 46, 14, 54, 22, 62, 30 },
{37, 5, 45, 13, 53, 21, 61, 29 },
{36, 4, 44, 12, 52, 20, 60, 28 },
{35, 3, 43, 11, 51, 19, 59, 27 },
{34, 2, 42, 10, 50, 18, 58, 26 },
{33, 1, 41,  9, 49, 17, 57, 25 },
};
int E[8][6] = {
{32,  1,  2,  3,  4,  5},
{ 4,  5,  6,  7,  8,  9},
{ 8,  9, 10, 11, 12, 13},
{12, 13, 14, 15, 16, 17},
{16, 17, 18, 19, 20, 21},
{20, 21, 22, 23, 24, 25},
{24, 25, 26, 27, 28, 29},
{28, 29, 30, 31, 32,  1}
};
int PC_1[8][7] = {
{57, 49, 41, 33, 25, 17,  9},
{ 1, 58, 50, 42, 34, 26, 18},
{10,  2, 59, 51, 43, 35, 27},
{19, 11,  3, 60, 52, 44, 36},
{63, 55, 47, 39, 31, 23, 15},
{ 7, 62, 54, 46, 38, 30, 22},
{14,  6, 61, 53, 45, 37, 29},
{21, 13, 5, 28, 20,  12,  4}
};
int PC_2[8][6] = {
{14, 17, 11, 24,  1,  5},
{ 3, 28, 15,  6, 21, 10},
{23, 19, 12,  4, 26,  8},
{16,  7, 27, 20, 13,  2},
{41, 52, 31, 37, 47, 55},
{30, 40, 51, 45, 33, 48},
{44, 49, 39, 56, 34, 53},
{46, 42, 50, 36, 29, 32}
};
int FUNC_P[4][8] = {
{16,  7, 20, 21, 29, 12, 28, 17},
{ 1, 15, 23, 26,  5, 18, 31, 10},
{ 2,  8, 24, 14, 32, 27,  3,  9},
{19, 13, 30,  6,  22, 11,  4, 25}
};
int S[8][4][16] = {
//S1
{
{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},
},

//S2
{
{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9},
},

//S3
{
{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},
},

//S4
{
{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14},
},

//S5
{
{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3},
},

//S6
{
{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13},
},

//S7
{
{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},
},

//S8
{
{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11},
}
};


string hex_to_bin(char hex)
{
	switch (hex)
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0011";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'a': case 'A': return "1010";
	case 'b': case 'B': return "1011";
	case 'c': case 'C': return "1100";
	case 'd': case 'D': return "1101";
	case 'e': case 'E': return "1110";
	case 'f': case 'F': return "1111";
	}
}
string bin_to_hex(string bin)
{
	string result = "0x";
	for (int i = 0; i < bin.size(); i += 4)
	{
		int count = 0;
		if (bin[i] == '1')
		{
			count += 8;
		}
		if (bin[i+1] == '1')
		{
			count += 4;
		}
		if (bin[i+2] == '1')
		{
			count += 2;
		}
		if (bin[i+3] == '1')
		{
			count += 1;
		}
		switch (count)
		{
		case 0: result += '0'; break;
		case 1: result+='1'; break;
		case 2: result+='2'; break;
		case 3: result+='3'; break;
		case 4: result+='4'; break;
		case 5: result+='5'; break;
		case 6: result+='6'; break;
		case 7: result+='7'; break;
		case 8: result+='8'; break;
		case 9: result+='9'; break;
		case 10: result+='A'; break;
		case 11: result+='B'; break;
		case 12: result+='C'; break;
		case 13: result+='D'; break;
		case 14: result+='E'; break;
		case 15: result+='F'; break;
		}
	}
	return result;
}
void generate_round_keys(string key_56,string* roundKeys)
{
	string C = key_56.substr(0, 28);
	string D = key_56.substr(28, 28);
	for (int round = 0; round < 16; round++)
	{
		//rotate 1 bit
		if ((round+1 == 1) || (round+1 == 2) || (round+1 == 9) || (round+1 == 16))
		{
			char tmp_C0 = C[0];
			char tmp_D0 = D[0];
			for (int i = 0; i < 27; i++)
			{
				C[i] = C[i + 1];
				D[i] = D[i + 1];
			}
			C[27] = tmp_C0;
			D[27] = tmp_D0;
		}
		//rotate 2 bits
		else
		{
			char tmp_C0 = C[0];
			char tmp_C1 = C[1];
			char tmp_D0 = D[0];
			char tmp_D1 = D[1];
			for (int i = 0; i < 26; i++)
			{
				C[i] = C[i + 2];
				D[i] = D[i + 2];
			}
			C[27] = tmp_C1;
			C[26] = tmp_C0;
			D[27] = tmp_D1;
			D[26] = tmp_D0;
		}

		//PC_2
		string tmpRoundKey56 = C + D;
		string roundKey(48,'x');
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				roundKey[i * 6 + j] = tmpRoundKey56[PC_2[i][j] - 1];
			}
		}
		*(roundKeys + round) = roundKey;
	}
}
string XOR(string A, string B)
{
	string XOR_result(A.size(), 'x');
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] == B[i])
		{
			XOR_result[i] = '0';
		}
		else
		{
			XOR_result[i] = '1';
		}
	}

	return XOR_result;
}
string f(string R,string roundKey)
{
	string expanded_R(48,'x');

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			expanded_R[i * 6 + j] = R[E[i][j]-1];
		}
	}

	string XOR_result = XOR(expanded_R, roundKey);
	
	string tmp_f_output = "";
	for (int i = 0; i < 48; i += 6)
	{
		string sixBits = XOR_result.substr(i, 6);
		string head_tail="";
		string mid_part="";
		head_tail+=(sixBits[0]);
		head_tail+=(sixBits[5]);
		mid_part = sixBits.substr(1, 4);
		int col, row;
		row = stoi(head_tail, nullptr, 2);
		col = stoi(mid_part, nullptr, 2);
		
		// 4 bits output of S box
		tmp_f_output += bitset<4>(S[i / 6][row][col]).to_string();
	}
	
	// Permutation
	string f_output(32,'x');
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			f_output[i * 8 + j] = tmp_f_output[FUNC_P[i][j] - 1];
		}
	}


	return f_output;
}



int main(int argc, char *argv[])
{
	string Ciphertext(64,'x');
	string key;
	string binKey="";
	string key_56(56,'x');
	string roundKeys[16];
	string Plaintext;
	string binPlaintext="";
	string p_binPlaintext(64,'x');
	key = argv[1];
	Plaintext = argv[2];
	for (int i = 2; i < 18; i++)
	{
		binPlaintext += hex_to_bin(Plaintext[i]);
	}
	
	for (int i = 2; i < 18; i++)
	{
		binKey += hex_to_bin(key[i]);
	}

	//Initial Permutation
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			p_binPlaintext[i * 8 + j] = binPlaintext[IP[i][j]-1];
		}
	}

	//turn key into 56 bits
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			key_56[i * 7 + j] = binKey[PC_1[i][j] - 1];
		}
	}
	

	generate_round_keys(key_56, roundKeys);

	//16 rounds of encryption
	string tmp_ciphertext = p_binPlaintext;
	for (int i = 0; i < 16; i++)
	{
		string L = tmp_ciphertext.substr(0, 32);
		string R = tmp_ciphertext.substr(32, 32);

		tmp_ciphertext = R + XOR(L, f(R, roundKeys[i]));
	}

	string L = tmp_ciphertext.substr(0, 32);
	string R = tmp_ciphertext.substr(32, 32);
	tmp_ciphertext = R + L;

	// Final Permutation
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Ciphertext[i * 8 + j] = tmp_ciphertext[IP_inverse[i][j] - 1];
		}
	}

	// turn to hex
	Ciphertext = bin_to_hex(Ciphertext);
	
	
	cout << Ciphertext << "\n";
	//system("PAUSE");
	return 0;
}