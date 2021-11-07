// Granma.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;


vector<string> DICT;
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
	for (size_t i = 0; i < a.size(); i++)	//here we are sure that the sizes are correct by the insertion theorem
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
int sort_byfreq(const int pos)
{
	string key = DICT[pos];
	int j = pos - 1;
	while ((j > -1) && (key.size() == DICT[j].size()) && more_diff(key, DICT[j]))
	{
		DICT[j + 1] = DICT[j];
		j--;
	}
	DICT[j + 1] = key;
	return j + 1;
}

int sort_byalpha(const int pos)
{
	string key = DICT[pos];
	string s(sort(key)); // in a order
	int j = pos - 1;
	while ((j > -1) && (s.size() == DICT[j].size()) && not_aorder(sort(DICT[j]),s))
	{
		DICT[j + 1] = DICT[j];
		j--;
	}
	DICT[j + 1] = key;
	return j + 1;
}

void sort_aorder(const int pos)
{
	string key = DICT[pos];
	string s(sort(key)); // in a order
	int j = pos - 1;
	while ((j > -1) && (s.size() == DICT[j].size()) && not_aorder(DICT[j], s))
	{
		DICT[j + 1] = DICT[j];
		j--;
	}
	DICT[j + 1] = key;
}

void read_input()
{
	string s;
	cin >> s;
	while (s != ".")
	{
		DICT.push_back(s); 
		int pos = sort_bysize(); // sort by size and return index
		int pos2 = sort_byfreq(pos);
		int pos3 = sort_byalpha(pos2);
		sort_aorder(pos3);
		cin >> s;
	}
}

int main()
{
	read_input();
	for (auto el : DICT) { cout << el << endl; }
	
	
}

