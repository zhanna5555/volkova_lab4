#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <ctype.h>
#include "gas_transmission_network.h"
#include <chrono>
#include "log.h"

using namespace std;
using namespace chrono;

redirect_stream_wrapper<istream> cin_in(cin);
bool Is_integer(string s) {

	for (const char& el : s) {
		if (!isdigit(el)) {
			return 0;
		}
	}
	return 1;
}

int CorrectIntInput(string er_out)
{
	string x;

	cin >> x;

	while (cin.fail() || !Is_integer(x))
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

void show_menu()
{
	cout << "MENU" << endl
		<< "Press 1. Add a pipe" << endl
		<< "Press 2. Add a compressor station" << endl
		<< "Press 3. Viewing all objects" << endl
		<< "Press 4. Save" << endl
		<< "Press 5. Download" << endl
		<< "Press 6. Filter" << endl
		<< "Press 7. Batch editing pipes" << endl
		<< "Press 8. Batch editing cs" << endl
		<< "Press 9. Link CS" << endl
		<< "Press 10. Topological sort" << endl
		<< "Press 11. Delete cs from graph" << endl
		<< "Press 12. Delete pipe from graph" << endl
		<< "Press 13. Dijkstra" << endl
		<< "Press 14. Max flow" << endl
		<< "Press 0. Exit" << endl << endl;
};

int main()
{
	map <int, Pipe> all_pipes;
	map <int, CompStation> all_stations;
	int option = 0;
	ofstream fout;
	gas_transmission_network gtn;
	string time = format(":%D-%M-%Y %h_%m_%s", system_clock::now());
	ofstream log("log" + time + ".txt");
	redirect_stream_wrapper cerr_out(cerr);
	if (log) {
		cerr_out.redirect(log);
	}


	while (1)
	{

		show_menu();
		cout << "Enter option: ";

		option = CorrectIntInput("Enter integer.");
		switch (option)
		{
		case 1:
			gtn.CreatePipe();
			cout << "Pipe was created." << endl << endl;
			break;
		case 2:
			gtn.CreateCs();
			cout << "Compressor station was created." << endl << endl;

			break;
		case 3:
			gtn.show_pipes();
			gtn.show_cs();
			gtn.show_links();
			break;

		case 4:
			gtn.save_file();
			break;

		case 5:

			gtn.load_file();
			break;

		case 6:
			gtn.Filter();
			break;

		case 7:
			gtn.Batch_editing_p();
			break;

		case 8:
			gtn.Batch_editing_cs();
			break;

		case 9:
			gtn.Link_cs();
			break;

		case 10:
			gtn.TopologicalSort();
			break;

		case 11:
			gtn.del_cs_graph();
			break;

		case 12:
			gtn.del_p_graph();
			break;

		case 13:
			gtn.Dijkstra();
			break;

		case 14:
			gtn.maxFlow();
			break;

		case 0:
			return 0;
		default:
			cout << "Enter a number from 0 to 7." << endl;
			break;
		}

	}

	return 0;
};
