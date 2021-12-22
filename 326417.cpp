#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

string sort(string& s)
{
	string str(s);
	for (size_t i = 1; i < s.size(); i++)
	{
		char key(s[i]);
		int j = i - 1;
		while ((j > -1) && (key < s[j]))
		{
			s[j + 1] = s[j];
			j--;
		}
		s[j + 1] = key;
	}
	return s;
}



int sort_bysize(vector<def>& dict)
{
	def key = dict[dict.size() - 1]; // last added
	int j = dict.size() - 2;
	while ((j > -1) && (key.word.size() < dict[j].word.size()))
	{
		dict[j + 1] = dict[j];
		j--;
	}
	dict[j + 1] = key;
	return j + 1;
}

bool more_diff(const string a, const string b)
{
	string v(a), w(b);
	v = sort(v);
	w = sort(w);
	int count_a(1), count_b(1);
	for (size_t i = 0; i < a.size() - 1; i++)
	{
		if (v[i + 1] != v[i]) count_a++;
		if (w[i + 1] != w[i]) count_b++;
	}
	if (count_a < count_b) return 1;
	else return 0;
}

bool cond(def key, int j, int i, vector<def>& dict)
{
	switch (i)
	{
	case 1: return more_diff(key.word, dict[j].word); break;
	case 2: return dict[j].alpha > key.word; break;
	case 3: return  dict[j].word > key.word; break;
	}
	return 1;
}

void sort(vector<def>& dict, const int pos, int& p, int i)
{
	def key = dict[pos];
	int j = pos - 1;
	while ((j > -1) && (key.word.size() == dict[j].word.size()) && cond(key, j, i, dict))
	{
		dict[j + 1] = dict[j];
		j--;
	}
	dict[j + 1] = key;
	p = j + 1;
}

bool check_lowercase(string& word)
{
	const string NOT_IN_CAPITAL_LETTERS("The word is not purely in capital letters");
	for (size_t i = 0; i < word.size(); i++)
	{
		if (word[i] < 65 || word[i]> 90)
		{
			cout << NOT_IN_CAPITAL_LETTERS<< endl;
			return true;
			
			break;
		}
	}
	return false;
}

void check_double(int& index, vector<def>& dict)		//check done after sorting.
{
	const string DOUBLE_WORD("Each word can be present only once");
	if (index > 0)
	{
		if (dict[index].word == dict[index - 1].word)
		{
			cout << DOUBLE_WORD << endl;
			exit(0);
		}
	}
}

void read_dict(vector<def>& dict)
{
	const string EMPTY_DICO("The dictionnary cannot be empty");
	string s;
	cin >> s;	//add empty dico check
	while (s != ".")
	{
		if (check_lowercase(s)) exit(0);
		int pos1, pos2;
		def w;
		w.word = s;
		w.alpha = sort(s);
		dict.push_back(w);
		int pos = sort_bysize(dict); // sort by size and return index
		sort(dict, pos, pos1, 1);
		sort(dict, pos1, pos2, 2);
		sort(dict, pos2, pos2, 3);
		check_double(pos2, dict);
		cin >> s;
	}
	if (dict.size() == 0)
	{
		cout << EMPTY_DICO << endl;
		exit(0);
	}
}

string read_mline(bool& star, bool& lowercase)
{
	string message("");
	string s;
	cin >> s;
	while ((s != ".") && (s!= "*"))
	{
		if (check_lowercase(s)) lowercase = true;
		message += s;
		cin >> s;
	}
	if (s == "*") star = 1;
	return message;
}

bool message_contient_mot(const string alpha, const string alpha_m)
{
	unsigned int j(0);
	for (unsigned int i = 0; i < alpha_m.size(); i++)
	{
		if (alpha[j] == alpha_m[i])
		{
			if (j == alpha.size() - 1) return 1;
			j++;
		}
	}
	return 0;
}

void move_back(vector<def>& message, int pos)
{
	def key = message[pos];
	for (unsigned int i = pos; i < message.size() - 1; i++)
	{
		message[i] = message[i + 1];
	}
	message[message.size() - 1] = key;
}

string message_soustraire_mot(string message, string alpha)
{
	unsigned int j(0);
	string aux("");
	for (unsigned i = 0; i < message.size(); i++)
	{
		if (j < alpha.size())
		{
			if (message[i] != alpha[j])
			{
				aux += message[i];
			}
			else j++;
		}
		else aux += message[i];
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
	cout << endl;
}

vector<string> ajouter(vector<string> anagramme, string mot)
{
	vector<string> aux(anagramme);
	aux.push_back(mot);
	return aux;
}

bool rech_anagramme(vector<def> dico, string alpha_m, vector<string> anagram)
{
	int dsize(dico.size());
	if (dsize == 0) return 0;
	bool success(0);
	for (int i= 0; i < dsize; i++)
	{
		if (message_contient_mot(dico[i].alpha, alpha_m))
		{
			vector<string> a_next = ajouter(anagram, dico[i].word);
			string alpha_m_next;
			alpha_m_next = message_soustraire_mot(alpha_m, dico[i].alpha);
			if (alpha_m_next.size() == 0)
			{
				display(a_next);
				success = true;
			}
			else
			{
				vector<def> dico_next(enlever_mot(dico, i));
				if (rech_anagramme(dico_next, alpha_m_next, a_next) == 1) success = 1;
			}
		}
	}
	return success;
}

void affiche_dict(vector<def>& d)
{
	for (size_t i = 0; i < d.size(); i++)
	{
		cout << d[i].word << endl;
	}
	cout << endl;
}

int main()
{
	const string NO_ANAGRAM("There is no anagram for this message and this dictionnary");
	vector<def> DICT;
	read_dict(DICT);
	affiche_dict(DICT);
	bool star(0);
	while (!star)
	{
		bool lowercase(false);
		string message(read_mline((star),lowercase));
		if ( lowercase == true )
		{
			cout << endl;
			continue;
		}
		string alpha_m = sort(message);
		vector<string> anagram;
		if (!rech_anagramme(DICT, alpha_m, anagram))
		{
			cout << NO_ANAGRAM<< endl;
			cout << endl;
		}
	}
	return 0;
}
