#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class GraM
{
public:
	char start_symbol = 'R';
	vector<char> nterm_sym;
	vector<char> term_sym;
	vector<pair<char, string>> rule;
	char eps = 'e';
	void term_vvod()
	{
		string str;
		cout << "Input terminal symbols: ";
		getline(cin, str);
		for (int i = 0; i < str.length(); ++i)
		{
			term_sym.push_back(str[i]);
		}
		term_sym.push_back(eps);
	}

	void nterm_vvod()
	{
		string str;
		cout << "Input nonterminal symbols: ";
		getline(cin, str);
		for (int i = 0; i < str.length(); ++i)
		{
			nterm_sym.push_back(str[i]);
		}
	}
	void vivod_term()
	{
		cout << "Terminal symbols: ";
		for (int i = 0; i < term_sym.size(); ++i)
		{
			cout << term_sym[i] << ' ';
		}
		cout << endl;
	}

	void vivod_nterm()
	{
		cout << "Nonterminal symbols: ";
		for (int i = 0; i < nterm_sym.size(); ++i)
		{
			cout << nterm_sym[i] << ' ';
		}
		cout << endl;
	}
};
class Rules : public GraM
{
public:
	char nterm;
	void rules()
	{
		GraM::nterm_vvod();
		GraM::term_vvod();
		int kolvo_rules;
		int flag = 0;
		cout << "Enter amount of rules: ";
		cin >> kolvo_rules;
		if ((!cin) || (kolvo_rules <= 0))
		{
			cout << " please enter carefully" << endl;
			exit(0);
		}
		string term;
		for (int i = 0; i < kolvo_rules; ++i)
		{
			cout << "Enter nonterminal symbol in rule: ";
			cin >> nterm;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			auto result = find(nterm_sym.begin(), nterm_sym.end(), nterm);
			if (result == nterm_sym.end())
			{
				cout << "incorrect";
				exit(0);
			}
			cout << "Enter terminal symbols in rule: ";
			cin >> term;
			for (int i = 0; i < term.length(); ++i)
			{
				auto result_1 = find(term_sym.begin(), term_sym.end(), term[i]);
				auto result_2 = find(nterm_sym.begin(), nterm_sym.end(), term[i]);
				if ((result_2 != nterm_sym.end()) || (result_1 != term_sym.end()))
				{
					flag = 1;
				}
				else
				{
					flag = 0;
					break;
				}
			}
			if (flag == 0)
			{
				cout << "incorrect" << endl;
				exit(0);
			}
			cout << endl;
			cout << endl;
			rule.push_back(make_pair(nterm, term));
		}
		GraM::vivod_nterm();
		GraM::vivod_term();
	}
	void rules_print()
	{
		for (int i = 0; i < rule.size(); ++i)
		{
			cout << rule[i].first << " -> " << rule[i].second << endl;
		}
	}
};
class Functions : public Rules
{
public:
	vector<pair<char, string>> nn_rules;
	vector<pair<char, string>> n_rules;
	void functions_nedostizhimie()
	{
		int flag = 0;
		Rules::rules();
		cout << "Rules before:" << endl;
		Rules::rules_print();
		for (auto i = rule.begin() + 1; i != rule.end(); ++i)
		{
			flag = 0;
			char symb_left_part = i->first;
			for (auto j = rule.begin(); j != rule.end(); ++j)
			{
				if (i != j)
				{

					auto found = j->second.find(symb_left_part);
					if (found != string::npos)
					{
						flag = 1;
						break;
					}
				}
			}
			if (flag == 0)
			{
				rule.erase(i--);
			}
		}
		cout << "Rules after remove nedostizhimie:" << endl;
		Rules::rules_print();
	}
	void functions_nerazreshimie()
	{
		int current = 0;
		int flag = 0;
		int flag_2 = 0;
		for (auto i = rule.begin() + 1; i != rule.end(); ++i)
		{
			flag_2 = 0;
			flag = 0;
			for (auto j = rule.begin(); j != rule.end(); ++j)
			{

				char symb_left_part = j->first;
				string str = i->second;
				if (i != j)
				{
					for (int k = 0; k < str.length(); ++k)
					{
						flag_2 = 0;
						auto result = find(nterm_sym.begin(), nterm_sym.end(), str[k]);
						if (result != nterm_sym.end())
						{
							flag_2 = 1;
						}
						if (flag_2 == 1)
						{
							int flag_3 = 1;
							for (auto s = rule.begin(); s != rule.end(); ++s)
							{
								char symb_left_part_2 = s->first;
								if (str[k] == s->first)
								{
									current = current + 1;
									flag_3 = 0;
								}
							}
							if (current == 1)
							{
								flag = 1;
							}
							current = 0;
							if (flag_3 == 1)
							{
								flag = 1;
								break;
							}
						}
					}
				}
				if (flag == 1)
				{
					break;
				}
			}
			if (flag == 1)
			{
				rule.erase(i--);
			}
		}
		cout << "Rules after remove nerazreshimie:" << endl;
		Rules::rules_print();
	}
	void smesh_remove()
	{
		string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int flag_1 = 0;
		int flag_2 = 0;
		string f;
		char n_nterm;

		for (auto i = rule.begin(); i != rule.end(); ++i)
		{

			for (int j = 0; j < term_sym.size(); ++j)
			{
				f = term_sym[j];
				auto found_1 = i->second.find(f);
				if (found_1 != string::npos)
				{
					++flag_1;
				}
			}
			for (int j = 0; j < nterm_sym.size(); ++j)
			{
				f = nterm_sym[j];
				auto found_2 = i->second.find(f);
				if (found_2 != string::npos)
				{
					++flag_2;
				}
			}

			if ((i->second.length() >= 2) && (flag_1 >= 1))
			{
				for (int k = 0; k < term_sym.size(); ++k)
				{
					f = term_sym[k];
					auto found_3 = i->second.find(f);
					if ((found_3 != string::npos) && (found_3 != eps))
					{
						for (int j = 0; j < alph.length(); ++j)
						{
							n_nterm = alph[j];
							auto found_4 = find(nterm_sym.begin(), nterm_sym.end(), n_nterm);
							if (found_4 == nterm_sym.end())
							{
								nterm_sym.push_back(n_nterm);
								for (int h = 0; h < i->second.length(); ++h)
								{
									for (int r = 0; r < f.length(); ++r)
									{
										if (i->second[h] == f[r])
										{
											i->second[h] = n_nterm;
										}
									}
								}
								n_rules.push_back(make_pair(n_nterm, f));
								break;
							}
						}
					}
				}
			}
		}
		cout << "Rules after remove smeshanie " << endl;
		for (int i = 0; i < rule.size(); ++i)
		{
			n_rules.push_back(make_pair(rule[i].first, rule[i].second));
		}
		for (int i = 0; i < n_rules.size(); ++i)
		{
			cout << n_rules[i].first << " -> " << n_rules[i].second << endl;
		}
	}
	void long_rules()
	{
		string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		string n_r;
		string nn_r;
		char n_nterm;
		char nn_nterm;
		string s = "";
		for (auto it = n_rules.begin(); it != n_rules.end(); ++it)
		{
			if (it->second.length() > 2)
			{
				for (int i = 0; i < it->second.length(); ++i)
				{
					if (i % 2 == 0)
					{
						n_r = it->second.substr(0, 2);
						nn_r = it->second.substr(2, 2);
						for (int k = 0; k < it->second.length(); ++k)
						{
							it->second.erase(k);
						}
						for (int k = 0; k < alph.length(); ++k)
						{
							n_nterm = alph[k];
							auto found = find(nterm_sym.begin(), nterm_sym.end(), n_nterm);
							if (found == nterm_sym.end())
							{
								nterm_sym.push_back(n_nterm);
								it->second += n_nterm;
								break;
							}
						}
						for (int j = 0; j < alph.length(); ++j)
						{
							nn_nterm = alph[j];
							auto found = find(nterm_sym.begin(), nterm_sym.end(), nn_nterm);
							if (found == nterm_sym.end())
							{
								nterm_sym.push_back(nn_nterm);
								it->second += nn_nterm;
								break;
							}
						}
						nn_rules.push_back(make_pair(n_nterm, n_r));
						nn_rules.push_back(make_pair(nn_nterm, nn_r));
					}
				}
			}
		}
		cout << "rules after remove long" << endl;
		for (int i = 0; i < n_rules.size(); ++i)
		{
			nn_rules.push_back(make_pair(n_rules[i].first, n_rules[i].second));
		}
		for (int i = 0; i < nn_rules.size(); ++i)
		{
			cout << nn_rules[i].first << " -> " << nn_rules[i].second << endl;
		}
	}
	void eps_rules_remove()
	{
		for (auto iter = nn_rules.begin(); iter != nn_rules.end(); ++iter)
		{
			auto found = iter->second.find(eps);
			if ((found != string::npos) && (iter->first != start_symbol))
			{
				nn_rules.erase(iter--);
			}
		}
		cout << "rules after remove eps" << endl;
		for (int i = 0; i < nn_rules.size(); ++i)
		{
			cout << nn_rules[i].first << " -> " << nn_rules[i].second << endl;
		}
	}
};
int main()
{
	Functions func;
	func.functions_nedostizhimie();
	func.functions_nerazreshimie();
	func.smesh_remove();
	func.long_rules();
	func.eps_rules_remove();
	return 0;
}