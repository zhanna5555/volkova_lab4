#pragma once
#include <string>
#include <iostream>
#include <set>

using namespace std;

bool Is_int(string s) {

	for (const char& el : s) {
		if (!isdigit(el)) {
			return 0;
		}
	}
	return 1;
}

double correctInput(double max, string er_out)
{
	string x;
	string s1 = " ";
	string s2 = " ";

	cin >> x;
	cerr << x << '\n';


	auto pos = x.find(".");
	if (pos != string::npos)
	{
		s1 = x.substr(0, pos);
		s2 = x.substr(pos + 1);
	}
	else {
		s1 = x;
		s2 = "1";

	}


	while (cin.fail() || !Is_int(s1) || !Is_int(s2))
	{
		cin.clear();
		cin.ignore(10000000, '\n');
		cout << er_out << endl;
		cin >> x;
		cerr << x << '\n';

		auto pos = x.find(".");
		if (pos != string::npos)
		{

			s1 = x.substr(0, pos);
			s2 = x.substr(pos + 1);
			cerr << s1 << s2 << "del" << '\n';

		}
		else {

			s1 = x;
			s2 = "1";
			cerr << s1 << s2 << "!!!!!!!" << '\n';

		}
	}
	return stod(x);

}

int corretctInput_int(int max, string er_out)
{
	string x;

	cin >> x;

	while (cin.fail() || !Is_int(x))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << er_out << endl;
		cin >> x;
		cerr << x << '\n';
	}
	cerr << x << '\n';
	return stoi(x);

}
int corretctInput_int(set <string> dm, string er_out)
{
	string x;

	cin >> x;

	while (cin.fail() || !Is_int(x) || dm.find(x) == dm.end())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << er_out << endl;
		cin >> x;
		cerr << x << '\n';
	}
	cerr << x << '\n';
	return stoi(x);

}