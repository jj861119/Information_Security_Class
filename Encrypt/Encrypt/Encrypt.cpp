#include <iostream>
#include <string>
#include<vector>
using namespace std;

string caesar(int key, string Plaintext)
{
	cout << Plaintext << "\n";
	string output;
	string tmp;
	for (int i = 0; i < Plaintext.size(); i++)
	{
		 tmp = Plaintext[i] + key - 32;
		 if (tmp[0] > 'Z')
		 {
			 tmp[0] -= 26;
		 }
		output += tmp[0];
	}
	return output;
}
string playfair(string key, string Plaintext)
{
	string newKey="";
	string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	string output = "";
	vector<char> keyMatrix;

	
	for (int i = 0; i < key.size(); i++)
	{
		bool duplicate = false;
		for (int j = 0; j < newKey.size(); j++)
		{
			if (key[i] == 'J')
			{
				key[i] = 'I';
			}
			if (key[i] == newKey[j])
			{
				duplicate = true;
				break;
			}
		}
		if (!duplicate)
		{
			newKey += key[i];
		}
	}

	for (int i = 0; i < newKey.size(); i++)
	{
		for (int j = 0; j < alphabet.size(); j++)
		{
			if (newKey[i] == alphabet[j])
			{
				alphabet.erase(j,1);
				break;
			}
		}
	}

	for (int i = 0; i < newKey.size(); i++)
	{
		keyMatrix.push_back(newKey[i]);
	}
	for (int i = 0; i < alphabet.size(); i++)
	{
		keyMatrix.push_back(alphabet[i]);
	}

	for (int i = 0; i < Plaintext.size(); i += 2)
	{
		int id1,id2;
		char c1, c2;
		Plaintext[i] -= 32;
		Plaintext[i+1] -= 32;
		if (Plaintext[i] == 'J')
		{
			c1 = 'I';
		}
		else
		{
			c1 = Plaintext[i];
		}
		if (Plaintext[i+1] == 'J')
		{
			c2 = 'I';
		}
		else
		{
			c2 = Plaintext[i+1];
		}

		for (int i = 0; i < keyMatrix.size(); i++)
		{
			if (keyMatrix[i] == c1)
			{
				id1 = i;
			}
			if(keyMatrix[i] == c2)
			{
				id2 = i;
			}
		}

		if (id1 / 5 == id2 / 5)
		{
			if (((id1 + 1) / 5) == (id1 / 5))
			{
				output += keyMatrix[id1 + 1];
			}
			else
			{
				output += keyMatrix[id1 - 4];
			}
			if (((id2 + 1) / 5) == (id2 / 5))
			{
				output += keyMatrix[id2 + 1];
			}
			else
			{
				output += keyMatrix[id2 - 4];
			}
		}
		else if (id1 % 5 == id2 % 5)
		{
			if ((id1 + 5) > 24)
			{
				output += keyMatrix[(id1 + 5)%25];
			}
			else
			{
				output += keyMatrix[id1 + 5];
			}
			if ((id2 + 5) > 24)
			{
				output += keyMatrix[(id2 + 5) % 25];
			}
			else
			{
				output += keyMatrix[id2 + 5];
			}
		}
		else
		{
			int col1 = (id1 % 5);
			int col2 = (id2 % 5);

			output += keyMatrix[id1 + (col2 - col1)];
			output += keyMatrix[id2 + (col1 - col2)];

		}
	}


	return output;
}
string vernam(string key, string Plaintext)
{
	int length = Plaintext.size();
	string output = "";
	for (int i = 0; i < length; i++)
	{
		Plaintext[i] -= 32;
	}
	//cout << Plaintext << "\n";
	string newKey = key + Plaintext;
	//cout << newKey << "\n";
	//cout << (('D'-65)^('O'-65)) << "\n";

	for (int i = 0; i < length; i++)
	{
		//cout << (((int)newKey[i]) ^ ((int)Plaintext[i])) << "\n";
		output += (char)((((int)newKey[i]-65) ^ ((int)Plaintext[i]-65)) + 65);
		/*if ((((int)newKey[i]) ^ ((int)Plaintext[i])) <= 25 && (((int)newKey[i]) ^ ((int)Plaintext[i])) >= 0)
		{
			output += (char)((((int)newKey[i]) ^ ((int)Plaintext[i])) + 65);
		}
		else
		{
			output += (char)(((int)newKey[i]) ^ ((int)Plaintext[i]));
		}*/
		
	}
	return output;
}
string row(string key, string Plaintext)
{
	int length = key.size();
	string output = "";
	int* order = (int*) malloc(length * sizeof(int));
	for (int i = 0; i < key.size(); i++)
	{
		*(order + (int)(key[i] - 48)-1) = i;
	}

	for (int i = 0; i < length; i++)
	{
		int col = *(order + i);
		while (col < Plaintext.size())
		{
			output += Plaintext[col]-32;
			col += length;
		}
	}

	free(order);
	return output;
}
string rail_fence(int key, string Plaintext)
{
	vector<vector<char>> railfence(key);
	string output = "";

	for (int i = 0; i < Plaintext.size(); i++)
	{
		railfence[i % key].push_back(Plaintext[i]-32);
	}

	for (int i = 0; i < key; i++)
	{
		for (int j = 0; j < railfence[i].size(); j++)
		{
			output += railfence[i][j];
		}
	}

	return output;
}

int main(int argc, char *argv[])
{
	string Ciphertext;
	string key;
	string Plaintext;
	Ciphertext = argv[1];
	key = argv[2];
	Plaintext = argv[3];
	string output;

	if (Ciphertext == "caesar")
	{
		output=caesar(stoi(key), Plaintext);
	}
	else if (Ciphertext == "playfair")
	{
		output = playfair(key, Plaintext);
	}
	else if (Ciphertext == "vernam")
	{
		output = vernam(key, Plaintext);
	}
	else if (Ciphertext == "row")
	{
		output = row(key, Plaintext);
	}
	else if (Ciphertext == "rail_fence")
	{
		output = rail_fence(stoi(key), Plaintext);
	}

	cout << output << "\n";
	system("PAUSE");
	return 0;
}