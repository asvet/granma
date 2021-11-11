#include <iostream>
#include <string>
#include <vector>
using namespace std;

constexpr char ABET[] =
{
	'A', 'B', 'C', 'D', 'E', 'F',


'G', 'H', 'I', 'J', 'K', 'L',


'M', 'N', 'O', 'P', 'Q', 'R',


'S', 'T', 'U', 'V', 'W', 'X',


'Y',  'Z'
};

struct def
{
	string word;
	string alpha;
};

struct anag
{
	string word;
	string agram;
};

vector<def> DICT;

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
		while ((j > -1) && (find_pos(key) < find_pos(s[j])))
		{
			s[j + 1] = s[j];
			j--;
		}
		s[j + 1] = key;
	}
	return s;
}

int sort_bysize()
{
	def key = DICT[DICT.size() - 1]; // last added
	int j = DICT.size() - 2;
	while ((j > -1) && (key.word.size() < DICT[j].word.size()))
	{
		DICT[j + 1] = DICT[j];
		j--;
	}
	DICT[j + 1] = key;
	return j + 1;
}
bool more_diff(const string a, const string b)
{
	string v(a), w(b);
	sort(v);
	sort(w);
	int count_a(0), count_b(0);
	for (size_t i = 0; i < a.size() - 1; i++)
	{
		if (v[i + 1] == v[i]) count_a++;
		if (w[i + 1] == w[i]) count_b++;
	}
	if (count_a > count_b) return 1;
	else return 0;
}
bool cond(def key, int j, int i)
{
	switch (i)
	{
	case 1: return more_diff(key.word, DICT[j].word); break;
	case 2: return DICT[j].alpha > key.word; break;
	case 3: return  DICT[j].word> key.word; break;
	}
}

void sort(const int pos, int& p,int i)
{
	def key = DICT[pos];
	int j = pos - 1;
	while ((j > -1) && (key.word.size() == DICT[j].word.size()) && cond(key,j,i))
	{
		DICT[j + 1] = DICT[j];
		j--;
	}
	DICT[j + 1] = key;
	p = j + 1;
}
void read_dict()
{
	string s;
	cin >> s;
	while (s != ".")
	{
		int pos1, pos2;
		def w;
		w.word = s;
		w.alpha = sort(s);
		DICT.push_back(w);
		int pos = sort_bysize(); // sort by size and return index
		sort(pos,pos1,1);
		sort(pos1, pos2, 2);
		sort(pos2, pos2, 3);
		cin >> s;
	}
}
string read_m()
{
	string message("");
	string s;
	cin >> s;
	while (s != "*")
	{
		message += s;
		cin >> s;
	}
	cout << message << endl;
	return message;
}
bool message_contient_mot(const string alpha, const string alpha_m)
{
	int j(0);
	for (size_t i = 0; i < alpha_m.size(); i++)
	{
		if (alpha[j] == alpha_m[i])
		{
			if (j == alpha.size()-1) return 1;
			j++;
		}
	}
	return 0;
}
void move_back(vector<def>& message, int pos)
{
	def key = message[pos];
	for (size_t i = pos; i < message.size()-1; i++)
	{
		message[i] = message[i + 1];
	}
	message[message.size()-1] = key;
}
string message_soustraire_mot(string message, string alpha)
{
	int j(0);
	string aux("");
	for (size_t i = 0; i < message.size(); i++)
	{
		if (j >= alpha.size()) break;
		if (message[i] != alpha[j])
		{
			aux += message[i];
		}
		else j++;
	}
	return aux;
}
vector<def> enlever_mot(vector<def> vec, int pos)
{
	vector<def> v(vec);
	move_back(v, pos);
	v.pop_back();
	return v;
}

void display(vector<string> v)
{
	for (auto el : v) { cout << el << endl; }
}
bool rech_anagramme( vector<def> dico, string alpha_m, vector<string>& anagram)
{
	int dsize(DICT.size());
	if (dsize == 0) return 0;
	bool success(0);
	string alpha_m_next;
	for (size_t i = 0; i < dsize; i++)
	{
		if (message_contient_mot(DICT[i].alpha, alpha_m))
		{
			anagram.push_back(DICT[i].alpha);
			alpha_m_next = message_soustraire_mot(alpha_m, dico[i].alpha);
			if (alpha_m_next.size() == 0)
			{
				display(anagram);
				success = true;
			}
			else
			{
				vector<def> dico_next(enlever_mot(dico, i));
				if (rech_anagramme(dico_next, alpha_m, anagram) == 1) success = 1;
			}
		}
	}
	return success;
}

int main()
{

	vector<def> DICT;
	read_dict();	//creates the vector of strings
	for (auto el : DICT)
	{
		cout << el.word << endl;

	}
	cout << "---DICTIONNARY SORTED---" << endl;
	string message(read_m());//creates a string which is the message
	//sort(message);	// gets alpha value of message
	string alpha_m = sort(message);
	vector<string> anagram;
	rech_anagramme(DICT, alpha_m, anagram);
	//string s = sort("BLABLACAR");
	//cout << s << endl;
	//string s2 = sort("BLACAR");
	//cout << s2 << endl;
	//cout << message_contient_mot(s2, s);
	//cout << message_soustraire_mot(s, s2);//string A - string B conserving the order.
	
	


}
