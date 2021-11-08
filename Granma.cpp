// Granma.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;


vector<string> DICT;
vector<string> M;
constexpr char ABET[] =	
{
	'A', 'B', 'C','D', 'E', 'F', 'G', 'H','I',
	'J', 'K', 'L','M','N','O', 'P', 'Q', 'R',
	'S', 'T','U','V', 'W', 'X', 'Y', 'Z'
};

int find_pos(const char c)
{
	for (size_t i = 0; i < 26; i++) { if (c == ABET[i]) return i; }
}

string sort(string s)
{
	string str(s);
	for (size_t i = 1; i < s.size(); i++)
	{
		char key(s[i]);
		int j = i - 1;
		while ((j > -1) && (find_pos(key) < find_pos(s[j])) )
		{
			s[j + 1] = s[j];
			j--;
		}
		s[j + 1] = key;
	}
	return s;
}

bool not_aorder(const string a, const string b)
{
	for (size_t i = 0; i < a.size(); i++)	//here we are sure that the sizes are correct by the insertion propriety
	{
		if (a[i] != b[i])
		{
			if (find_pos(a[i]) > find_pos(b[i]))
			{
				return 1;
			}
		}
	}
	return 0; // all in order
}

int sort_bysize()
{
	string key = DICT[DICT.size() - 1]; // last added
	int j = DICT.size() - 2;
	while ((j > -1 )&& (key.size() < DICT[j].size()))
	{
		DICT[j + 1] = DICT[j];
		j--;
	}
	DICT[j + 1] = key;
	return j + 1;
}

bool more_diff(const string a, const string b)
{
	string v(a);
	string w(b);
	sort(v);
	sort(w);
	int count_a(0);
	int count_b(0);
	for (size_t i = 0; i < a.size() - 1; i++)
	{
		if (v[i + 1] == v[i]) count_a++;
		if (w[i + 1] == w[i]) count_b++;
	}
	if (count_a > count_b) return 1;
	else return 0;
}

void sort(const int pos)
{
	string key = DICT[pos];
	int j = pos - 1;
	while ((j > -1) && (key.size() == DICT[j].size()) && b)	// another bool function
	{
		DICT[j + 1] = DICT[j];
		j--;
	}
	DICT[j + 1] = key;
	key = DICT[j+1];
	while ((j > -1) && (key.size() == DICT[j].size()) && b)	// another bool function
	{
		DICT[j + 1] = DICT[j];
		j--;
	}
	DICT[j + 1] = key;
	key = DICT[j+1];
	while ((j > -1) && (key.size() == DICT[j].size()) && b)	// another bool function
	{
		DICT[j + 1] = DICT[j];
		j--;
	}
	DICT[j + 1] = key;
}

void read_dict()
{
	string s;
	cin >> s;
	while (s != ".")
	{
		int pos1, pos2, pos3;
		DICT.push_back(s); 
		int pos = sort_bysize(); // sort by size and return index
		sort(pos);
		cin >> s;
	}
}

void read_m()
{
	string s;
	cin >> s;
	while (s != "*")
	{
		M.push_back(s);
		cin >> s;
	}
}

int main()
{
	read_dict();
	read_m();
	for (auto el : DICT) { cout << el << endl; }
	for (auto el : M) { cout << el << endl; }
	  
	
}

