#pragma once
#include "gas_transmission_network.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <queue>
#include "Utilities.h"



using namespace std;
ostream& operator << (ostream& out, Pipe p) {
	return out << p.name << endl << p.lenght << endl << p.diam << endl << p.repair << endl;

}

ostream& operator << (ostream& out, CompStation cs) {
	return out << cs.name << endl << cs.workshops << endl << cs.working_workshops << endl << cs.efficiency << endl;

}

ostream& operator << (ostream& out, Edge ed) {
	return out << ed.start_p << endl << ed.end_p << endl << ed.pipe_id << endl << ed.weight << endl;

}


void gas_transmission_network::CreatePipe()
{
	string p_name;
	double p_lenght;
	int p_diam;
	set <string> dm = {"500","700","1000","1400" };
	bool p_repair;
	string er_output;

	cout << "Enter pipe name: ";
	getline(cin, p_name);
	getline(cin, p_name);
	cerr << p_name << endl;
	cout << "Enter pipe lenght in meters: ";
	p_lenght = correctInput(1., "Lenght must be double");
	cout << "Enter pipe diametr in milimeters ( 500, 700, 1000, 1400): ";
	p_diam = corretctInput_int(dm, "Diametr must be 500, 700, 1000 or 1400");
	cout << "Enter 0 if pipe is working or another integer if repairing: ";
	p_repair = corretctInput_int(1, "Repairing status must be integer");

	Pipe pipe(p_name, p_lenght, p_diam, p_repair);

	pipe.Push(all_p, pipe);
}

void gas_transmission_network::CreatePipe(int& p_diam)
{
	string p_name;
	double p_lenght;
	bool p_repair;
	string er_output;

	cout << "Enter pipe name: ";
	getline(cin, p_name);
	getline(cin, p_name);
	cerr << p_name << endl;
	cout << "Enter pipe lenght in meters: ";
	p_lenght = correctInput(1., "Lenght must be double");
	cout << "Enter 0 if pipe is working or another integer if repairing: ";
	p_repair = corretctInput_int(1, "Repairing status must be integer");

	Pipe pipe(p_name, p_lenght, p_diam, p_repair);

	pipe.Push(all_p, pipe);
}

void gas_transmission_network::CreateCs()
{
	string cs_name;
	int cs_workshops;
	int cs_working_workshops;
	double cs_efficiency;

	cout << "Enter comressor station name: ";
	getline(cin, cs_name);
	getline(cin, cs_name);
	cerr << cs_name << endl;
	cout << "Enter number of workshops: ";
	cs_workshops = corretctInput_int(1, "Workshops quantity must be integer");
	cout << "Enter number of  working workshops: ";
	cs_working_workshops = corretctInput_int(1, "Working workshops quantity must be integer");
	while (cs_working_workshops > cs_workshops)
	{
		if (cs_working_workshops > cs_workshops)
		{
			cout << "nubmer of working worshops must be less then number of workshops" << endl;
			cout << "Enter number of  working workshops: ";
			cs_working_workshops = corretctInput_int(1, "Working workshops quantity must be integer");
		};
	};
	cout << "Enter compressor station efficiency: ";
	cs_efficiency = correctInput(1., "Efficiency must be double");


	CompStation cs(cs_name, cs_workshops, cs_working_workshops, cs_efficiency);
	cs.Push(all_cs, cs);
}

void gas_transmission_network::PushToLinks(Edge ed)
{
	int new_gr = 1;
	int gr_num = 0;
	for (auto& ln : links) {


		if ((ln.second.CsIds.find(ed.end_p) != ln.second.CsIds.end() || ln.second.CsIds.find(ed.start_p) != ln.second.CsIds.end()) && (gr_num != ln.first && gr_num != 0)) {
			new_gr = 0;

			for (auto cs : ln.second.CsIds) {
				links[gr_num].CsIds.insert(cs);

			}
			for (auto ed1 : ln.second.edges) {
				links[gr_num].edges.push_back(ed1);
			}

			links.erase(ln.first);
			break;


		}

		if (ln.second.CsIds.find(ed.end_p) != ln.second.CsIds.end() || ln.second.CsIds.find(ed.start_p) != ln.second.CsIds.end()) {
			new_gr = 0;
			gr_num = ln.first;
		}

	}
	if (new_gr) {
		id_count++;
		graph_number = id_count;
		links.emplace(graph_number, Graph(ed));
	}
	else {
		links[gr_num].CsIds.insert(ed.end_p);
		links[gr_num].CsIds.insert(ed.start_p);
		links[gr_num].edges.push_back(ed);
		links[gr_num].incedent[ed.start_p].push_back(ed.end_p);
	}

}

void gas_transmission_network::show_pipes()
{
	cout << "Pipes: " << endl;

	for (auto& pipe : all_p) {
		pipe.second.Print();
	}


	cout << endl;
}

void gas_transmission_network::show_pipes(map <int, Pipe>& all_pp)
{
	cout << "Pipes: " << endl;

	for (auto& pipe : all_pp) {
		pipe.second.Print();
	}


	cout << endl;
}

void gas_transmission_network::show_cs()
{
	cout << "Compressor stations: " << endl;

	for (auto& cs : all_cs) {
		cs.second.Print();
	}

	cout << endl;
}

void gas_transmission_network::show_cs(map <int, CompStation>& all_cs1)
{
	cout << "Compressor stations: " << endl;

	for (auto& cs : all_cs1) {
		cs.second.Print();
	}

	cout << endl;
}

void gas_transmission_network::save_file()
{
	ofstream out;
	string f_name;
	if (all_p.size() > 0 && all_cs.size() > 0) {
		cout << "Enter file name: ";
		cin >> f_name;
		cerr << f_name << '\n';
		out.open("saves/" + f_name + ".txt");
		if (out.is_open() && all_p.size() > 0 && all_cs.size() > 0) {
			out << all_p.size() << endl;
			for (auto& pipe : all_p) {
				out << pipe.first << endl << pipe.second;
			}
			out << all_cs.size() << endl;
			for (auto& cs : all_cs) {
				out << cs.first << endl << cs.second;
			}
			out << links.size() << endl;
			for (auto ln : links) {
				out << ln.second.edges.size() << endl;
				for (auto ed : ln.second.edges) {
					out << ed;
				}
			}

		}
		out.close();
		cout << "File has been saved " << endl;
	}
	else {
		cout << "There are now objects, create some objects before saving" << endl;
	};
}

void gas_transmission_network::load_file()
{
	ifstream fin;
	string path = "saves";
	vector <filesystem::path> file_names;
	bool searched = false;
	string searshing_file;
	int number;
	int link_number;

	for (const auto& entry : filesystem::directory_iterator(path))
	{
		file_names.push_back(entry.path().filename());
		cout << entry.path().filename() << endl;
	}

	cout << "Enter file name: ";
	cin >> searshing_file;
	cerr << searshing_file << '\n';

	for (filesystem::path& fname : file_names) {
		if (fname == searshing_file)
		{
			searched = true;

			fin.open("saves/" + searshing_file);
			if (fin.is_open()) {
				cout << "start importing" << endl;
				fin >> number;
				for (int i = 0; i < number; i++) {
					int id;
					string p_name;
					double p_lenght;
					int p_diam;
					bool p_repair;

					fin >> id >> p_name >> p_lenght >> p_diam >> p_repair;
					Pipe p(id, p_name, p_lenght, p_diam, p_repair);
					p.Push(all_p, p);
					p.SetId(id);
				}
				fin >> number;
				for (int i = 0; i < number; i++) {
					int id;
					string cs_name;
					int cs_workshops;
					int cs_working_workshops;
					double cs_efficiency;

					fin >> id >> cs_name >> cs_workshops >> cs_working_workshops >> cs_efficiency;
					CompStation cs(id, cs_name, cs_workshops, cs_working_workshops, cs_efficiency);
					cs.Push(all_cs, cs);
					cs.SetId(id);
				}
				fin >> number;
				for (int i = 0; i < number; i++) {
					fin >> link_number;

					for (int i = 0; i < link_number; i++) {
						int CsID1;
						int CsID2;
						int p_id;
						int weight;

						fin >> CsID1 >> CsID2 >> p_id >> weight;
						Edge ed(CsID1, CsID2, p_id, weight);
						PushToLinks(ed);
						all_p[p_id].Push(link_p, all_p[p_id]);
					}

				}
				cout << "File has been imported" << endl << endl;
			}
			else {
				cout << "ERROR" << endl;
			}
			fin.close();
		};
	}
	if (!searched)
	{
		cout << "Wrong file name" << endl;
	}

}

void gas_transmission_network::Edit_or_remove_p(vector<int> editing_id)
{
	string fun;
	cout << "Enter remove(r) or change repairing status(c) ";
	cin >> fun;
	if (fun == "r") {
		for (int id : editing_id) {
			if (link_p.find(id) != link_p.end()) {
				for (auto& ln : links) {
					int index = 0;
					for (auto& ed : ln.second.edges) {
						if (ed.pipe_id == id) {
							ln.second.edges.erase(ln.second.edges.begin() + index);
						}
						index++;
					}
					if (ln.second.edges.size() == 0) {
						links.erase(ln.first);
					}
				}

			}
			all_p.erase(id);

		}
		cout << "Pipes has been removed" << endl << endl;
	}
	else if (fun == "c") {
		for (int id : editing_id) {
			all_p[id].repair = !all_p[id].repair;
		}
		cout << "Pipes has been changed" << endl << endl;
	}
	else {
		cout << "Wrong command";
	}
}

void gas_transmission_network::Edit_or_remove_cs(vector<int> editing_id)
{
	string fun;
	cout << "Enter remove(r) , add (+) or reduce(-) working workshop ";
	cin >> fun;
	if (fun == "r") {
		for (int id : editing_id) {
			all_cs.erase(id);
			for (auto& ln : links) {
				if (ln.second.CsIds.find(id) != ln.second.CsIds.end()) {
					int index = 0;
					for (auto& ed : ln.second.edges) {
						if (ed.end_p == id || ed.start_p == id) {
							ln.second.edges.erase(ln.second.edges.begin() + index);
						}
						index++;
					}
				}
				if (ln.second.edges.size() == 0) {
					links.erase(ln.first);
				}
			}
		}

		cout << " CS has been removed" << endl << endl;
	}
	else if (fun == "+") {
		for (int id : editing_id) {
			if (all_cs[id].working_workshops + 1 <= all_cs[id].workshops) {
				all_cs[id].working_workshops++;
			}
		}
		cout << "Cs has been changed" << endl << endl;
	}
	else if (fun == "-") {
		for (int id : editing_id) {
			if (all_cs[id].working_workshops - 1 > 0) {
				all_cs[id].working_workshops--;
			}
		}
		cout << "Cs has been changed" << endl << endl;
	}
	else {
		cout << "Wrong command";
	}
}

void gas_transmission_network::Filter_pipes_name()
{
	map <int, Pipe> filter_p;
	string name_part;
	vector <int> editing_id;

	cout << "Enter name for filter: ";
	cin >> name_part;

	for (auto& pipe : all_p) {
		if (pipe.second.name.find(name_part) != string::npos) {
			pipe.second.Push(filter_p, pipe.second);
			editing_id.push_back(pipe.first);
		}
	}
	if (filter_p.size() == 0) {
		cout << "There are no pipes with such pipe name" << endl;
	}
	else {
		show_pipes(filter_p);
		cout << endl;
	}

	cout << "Enter yes if you want to edit these pipes ";
	cin >> name_part;
	if (name_part == "yes") {
		Edit_or_remove_p(editing_id);
	}
}

void gas_transmission_network::Filter_pipes_repair()
{
	map <int, Pipe> filter_p;
	string repairing_status;
	vector <int> editing_id;

	cout << "Enter you want filter repairing(enter r) or working(enter w) pipes: ";
	cin >> repairing_status;

	while (1) {
		if (repairing_status == "r") {
			for (auto& pipe : all_p) {
				if (pipe.second.repair) {
					pipe.second.Push(filter_p, pipe.second);
					editing_id.push_back(pipe.first);
				}
			}
			if (filter_p.size() == 0) {
				cout << "There are no repairing pipes " << endl;
				break;
			}
			else {
				show_pipes(filter_p);
				cout << endl;
				break;
			}
		}
		else if (repairing_status == "w") {
			for (auto& pipe : all_p) {
				if (!pipe.second.repair) {
					pipe.second.Push(filter_p, pipe.second);
					editing_id.push_back(pipe.first);
				}
			}
			if (filter_p.size() == 0) {
				cout << "There are no working pipes " << endl;
				break;
			}
			else {
				show_pipes(filter_p);
				cout << endl;
				break;
			}
		}
		else {
			cout << "Wrong command" << endl;
			cout << "Enter you want filter repairing(enter r) or working(enter w) pipes: ";
			cin >> repairing_status;
		}
	}
	cout << "Enter yes if you want to edit these pipes ";
	cin >> repairing_status;
	if (repairing_status == "yes") {
		Edit_or_remove_p(editing_id);
	}
}

void gas_transmission_network::Filter_cs_name()
{
	map <int, CompStation> filter_cs;
	string name_part;
	vector <int> editing_id;

	cout << "Enter name for filter: ";
	cin >> name_part;

	for (auto& cs : all_cs) {
		if (cs.second.name.find(name_part) != string::npos) {
			cs.second.Push(filter_cs, cs.second);
			editing_id.push_back(cs.first);
		}
	}
	if (filter_cs.size() == 0) {
		cout << "There are no cs with such cs name" << endl;
	}
	else {
		show_cs(filter_cs);
		cout << endl;
	}

	cout << "Enter yes if you want to edit these cs ";
	cin >> name_part;
	if (name_part == "yes") {
		Edit_or_remove_cs(editing_id);
	}

}

void gas_transmission_network::Filter_cs_percent()
{
	map <int, CompStation> filter_cs;
	string func;
	int per;
	vector <int> editing_id;

	cout << "Enter the condition: equal(e) less(l) or more(r) ";
	cin >> func;
	cout << "Enter percent:  ";
	per = corretctInput_int(1, "Percent must be integer");

	if (func == "e") {
		for (auto& cs : all_cs) {
			if ((cs.second.working_workshops * 100) / cs.second.workshops == per) {
				cs.second.Push(filter_cs, cs.second);
				editing_id.push_back(cs.first);
			}
		}
		if (filter_cs.size() == 0) {
			cout << "There are no such cs" << endl;
		}
		else {
			show_cs(filter_cs);
			cout << endl;
		}
	}
	else if (func == "l") {
		for (auto& cs : all_cs) {
			if ((cs.second.working_workshops * 100) / cs.second.workshops < per) {
				cs.second.Push(filter_cs, cs.second);
				editing_id.push_back(cs.first);
			}
		}
		if (filter_cs.size() == 0) {
			cout << "There are no such cs" << endl;
		}
		else {
			show_cs(filter_cs);
			cout << endl;
		}

	}
	else if (func == "m") {
		for (auto& cs : all_cs) {
			if ((cs.second.working_workshops * 100) / cs.second.workshops > per) {
				cs.second.Push(filter_cs, cs.second);
				editing_id.push_back(cs.first);
			}
		}
		if (filter_cs.size() == 0) {
			cout << "There are no such cs" << endl;
		}
		else {
			show_cs(filter_cs);
			cout << endl;
		}
	}
	else {
		cout << "Wrong condition" << endl;
	}
	cout << "Enter yes if you want to edit these cs ";
	cin >> func;
	if (func == "yes") {
		Edit_or_remove_cs(editing_id);
	}

}

void gas_transmission_network::Filter()
{
	int filter_num;

	cout << "1 Filter pipes by name" << endl
		<< "2 Filter pipes by repairing status" << endl
		<< "3 Filter cs by name" << endl
		<< "4 Filter cs by % of working workshops" << endl << endl;

	cout << "Enter command number: ";
	filter_num = corretctInput_int(1, "Unexpected command, command number must be integer");

	switch (filter_num) {
	case 1:
		Filter_pipes_name();
		break;
	case 2:
		Filter_pipes_repair();
		break;
	case 3:
		Filter_cs_name();
		break;
	case 4:
		Filter_cs_percent();
		break;

	default:
		cout << "Unexpected command";
		break;

	}
}

void gas_transmission_network::Batch_editing_p()
{
	string line_id;
	char* str_id;
	int id_p;
	vector <int> editing_id;
	stringstream ss;

	show_pipes(all_p);
	cout << "Enter id of pipes: ";
	cin.ignore();
	getline(cin, line_id);
	char* l_id = _strdup(line_id.c_str());
#pragma warning(suppress : 4996)
	str_id = strtok(l_id, " , ");

	while (str_id) {
		if (Is_int(str_id)) {
			id_p = stoi(str_id);
			if (all_p.find(id_p) != all_p.end()) {
				editing_id.push_back(id_p);


			}
			else {
				cout << "No such id" << endl;
				editing_id = {};
				break;
			}
		}
		else {
			cout << "Id must be integer" << endl;
			editing_id = {};
			break;
		}
#pragma warning(suppress : 4996)
		str_id = strtok(0, " , ");
	}
	if (editing_id.size() != 0) {
		Edit_or_remove_p(editing_id);
	}
}

void gas_transmission_network::Batch_editing_cs()
{
	string line_id;
	char* str_id;
	int id_cs;
	vector <int> editing_id;
	stringstream ss;

	show_cs(all_cs);
	cout << "Enter id of cs: ";
	cin.ignore();
	getline(cin, line_id);
	char* l_id = _strdup(line_id.c_str());
#pragma warning(suppress : 4996)
	str_id = strtok(l_id, " , ");

	while (str_id) {
		if (Is_int(str_id)) {
			id_cs = stoi(str_id);
			if (all_cs.find(id_cs) != all_cs.end()) {
				editing_id.push_back(id_cs);


			}
			else {
				cout << "No such id" << endl;
				editing_id = {};
				break;
			}
		}
		else {
			cout << "Id must be integer" << endl;
			editing_id = {};
			break;
		}
#pragma warning(suppress : 4996)
		str_id = strtok(0, " , ");
	}
	if (editing_id.size() != 0) {
		Edit_or_remove_cs(editing_id);
	}
}

void gas_transmission_network::Link_cs()
{
	int CsID1;
	int CsID2;
	int p_diam;
	bool searched = 0;
	set <string> dm = { "500","700","1000","1400" };

	if (all_cs.size() < 2) {
		cout << "There must be more than 2 cs to link them" << endl << endl;;
	}
	else
	{
		show_cs();
		cout << "Enter first cs id ";
		CsID1 = corretctInput_int(1, "Id must be integer");
		while (all_cs.find(CsID1) == all_cs.end()) {
			cout << "No such cs id";
			CsID1 = corretctInput_int(1, "Id must be integer");
		}
		cout << "Enter second cs id ";
		CsID2 = corretctInput_int(1, "Id must be integer");
		while (all_cs.find(CsID2) == all_cs.end() || CsID2 == CsID1) {
			cout << "No such cs id or it is first id";
			CsID2 = corretctInput_int(1, "Id must be integer");
		}

		cout << "Enter pipe diametr  ( 500, 700, 1000, 1400) ";
		p_diam = corretctInput_int(dm, "Diametr must be 500, 700, 1000 or 1400");

		for (auto& pipe : all_p) {
			if (pipe.second.diam == p_diam && link_p.find(pipe.first) == link_p.end()) {
				searched = 1;
				cout << "Cs has been  linked with pipe:" << endl;
				pipe.second.Print();
				cout << endl;
				pipe.second.Push(link_p, pipe.second);
				Edge ed(CsID1, CsID2, pipe.first, pipe.second.lenght);
				PushToLinks(ed);

			}
		}
		if (!searched) {
			cout << "There are no suitable pipe" << endl << "Creating new pipe" << endl;
			CreatePipe(p_diam);
			for (auto& pipe : all_p) {
				if (pipe.second.diam == p_diam && link_p.find(pipe.first) == link_p.end()) {
					searched = 1;
					cout << "Cs has been  linked with pipe:" << endl;
					pipe.second.Print();
					cout << endl;
					pipe.second.Push(link_p, pipe.second);
					Edge ed(CsID1, CsID2, pipe.first, pipe.second.lenght);
					PushToLinks(ed);
				}
			}
		}



	}
}

void Edge::Print()
{
	cout << "CS with id " << start_p << " is connected with CS with id " << end_p << " using a pipe with id " << pipe_id << endl;
}

void gas_transmission_network::show_links()
{
	cout << "Links:" << endl;
	for (auto& link : links) {
		cout << "Graph " << link.first << endl;
		for (auto ed : link.second.edges) {
			ed.Print();
		}
	}
	cout << endl;
}

void Graph::dfs(int vertex, std::vector<int>& ans, std::vector<bool>& used, bool& cycle, std::set <int>& us_to, int start)
{
	used[vertex] = true;
	us_to.insert(vertex);
	for (size_t i = 0; i < incedent[vertex].size(); ++i) {
		if (vertex == start) {
			us_to.clear();
		}
		if (!cycle) {
			int to = incedent[vertex][i];
			if (us_to.find(to) != us_to.end()) {
				cycle = true;
				break;
			}
			else {
				us_to.insert(to);

				if (!used[to]) dfs(to, ans, used, cycle, us_to, start);
			}
		}
	}
	ans.push_back(vertex);

}


void gas_transmission_network::TopologicalSort()
{
	vector <int> ans;

	for (auto& link : links) {
		cout << "Graph " << link.first << endl;
		std::vector <bool> used(101, false);
		bool Cycle = false;

		ans.clear();
		for (int i = 0; i < link.second.incedent.size(); ++i) {
			set <int> us_to;
			if (!used[i] && link.second.incedent[i].size() != 0) {


				link.second.dfs(i, ans, used, Cycle, us_to, i);
			}
		}
		reverse(ans.begin(), ans.end());
		if (Cycle) {
			cout << "Error This graph has cycle  ";
		}
		else {
			cout << "Sorted: ";
			for (int i = 0; i < ans.size(); ++i) cout << ans[i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void gas_transmission_network::del_cs_graph()
{
	int id;
	show_links();
	cout << "Enter cs id ";
	id = corretctInput_int(1, "Id must be integer");
	for (auto& ln : links) {
		if (ln.second.CsIds.find(id) != ln.second.CsIds.end()) {
			int index = 0;
			for (auto& ed : ln.second.edges) {
				if (ed.end_p == id || ed.start_p == id) {
					ln.second.edges.erase(ln.second.edges.begin() + index);
				}
				index++;
			}
		}
		if (ln.second.edges.size() == 0) {
			links.erase(ln.first);
		}
	}

}

void gas_transmission_network::Dijkstra()
{
	int st_vertex, end_vertex;
	cout << "Enter first vertex: ";
	cin >> st_vertex;
	cerr << st_vertex;
	cout << "Enter second vertex: ";
	cin >> end_vertex;
	cerr << end_vertex;
	for (auto& link : links) {
		if (link.second.CsIds.find(st_vertex) != link.second.CsIds.end()) {
			vector <pair <int, int> >path_lenghts(link.second.CsIds.size() + 1, make_pair(-1, INT16_MAX));
			vector <bool> used_v(link.second.CsIds.size() + 1, false);
			vector <int> ans;
			bool f = false;
			std::vector <bool> used(101, false);
			bool Cycle = false;

			ans.clear();
			set <int> us_to;
			link.second.dfs(st_vertex, ans, used, Cycle, us_to, st_vertex);

			for (auto i : ans) {
				if (i == end_vertex) f = true;
			}
			if (f) {
				used_v[st_vertex] = true;
				path_lenghts[st_vertex] = make_pair(-1, 0);
				int active_v = st_vertex;
				while (!used_v[end_vertex]) {
					for (auto ed : link.second.edges) {
						if (ed.start_p == active_v && ed.weight + path_lenghts[active_v].second < path_lenghts[ed.end_p].second) {
							path_lenghts[ed.end_p] = make_pair(active_v, ed.weight + path_lenghts[active_v].second);

						}
					}
					int min_weight = INT16_MAX;
					for (int i = 0; i < link.second.CsIds.size() + 1; i++) {
						if (path_lenghts[i].second < min_weight && !used_v[i]) {
							min_weight = path_lenghts[i].second;
							active_v = i;
						}
					}
					used_v[active_v] = true;
				}
				ans.clear();
				active_v = end_vertex;
				while (active_v != st_vertex) {
					active_v = path_lenghts[active_v].first;
					ans.push_back(active_v);

				}
				cout << "aaaaaaaaa" << endl;
				reverse(ans.begin(), ans.end());
				cout << "Minimal path lenght: " << path_lenghts[end_vertex].second << endl;
				cout << "Path: ";
				for (int v : ans) {
					cout << v << " --> ";
				}
				cout << end_vertex << endl;

			}
			else cout << "There is no way from " << st_vertex << " to " << end_vertex << endl << endl;


		}
	}

	cout << endl;
}

void gas_transmission_network::maxFlow()
{
	vector <double> weight_row(links[1].CsIds.size() + 1, 0.0);
	vector<vector<double>> weight_matrix(links[1].CsIds.size() + 1, weight_row);

	for (auto ed : links[1].edges) {
		if (all_p[ed.pipe_id].repair == true) {
			weight_matrix[ed.start_p][ed.end_p] = 0.0;
		}
		else {
			weight_matrix[ed.start_p][ed.end_p] = all_p[ed.pipe_id].lenght;
		}
	}


	int source, sink;
	cout << "Enter source id: ";
	cin >> source;
	cerr << source;

	cout << "Enter sink id: ";
	cin >> sink;
	cerr << sink;

	vector<int> parent(links[1].CsIds.size() + 1, -1);
	int max_flow = 0;

	while (true) {
		parent.assign(links[1].CsIds.size() + 1, -1);
		queue <pair <int, double> > q;
		q.push({ source, DBL_MAX });
		parent[source] = source;


		while (!q.empty()) {
			int u = q.front().first;
			double path_flow = q.front().second;
			q.pop();

			for (int v = 0; v < links[1].CsIds.size() + 1; v++) {
				if (parent[v] == -1 && weight_matrix[u][v] > 0) {

					parent[v] = u;
					int min_capacity;
					if (path_flow < weight_matrix[u][v]) {
						min_capacity = path_flow;
					}
					else {
						min_capacity = weight_matrix[u][v];
					}

					if (v == sink) {

						while (v != source) {
							u = parent[v];
							weight_matrix[u][v] -= min_capacity;
							weight_matrix[v][u] += min_capacity;
							v = u;
						}
						max_flow += min_capacity;
						break;
					}
					q.push({ v, min_capacity });
				}
			}
		}

		if (parent[sink] == -1)
			break;
	}

	cout << "Max flow from " << source << " to " << sink << " equal " << max_flow << endl << endl;
}

void gas_transmission_network::del_p_graph() {
	int id;
	show_links();
	cout << "Enter pipe id ";
	id = corretctInput_int(1, "Id must be integer");
	for (auto& ln : links) {
		int index = 0;
		for (auto& ed : ln.second.edges) {
			if (ed.pipe_id == id) {
				ln.second.edges.erase(ln.second.edges.begin() + index);
			}
			index++;
		}
		if (ln.second.edges.size() == 0) {
			links.erase(ln.first);
		}
	}

}


