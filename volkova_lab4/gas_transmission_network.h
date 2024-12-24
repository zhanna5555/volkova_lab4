#pragma once
#include "CompStation.h"
#include <vector>
#include "Pipe.h"
#include <set>

struct Edge {

	int start_p;
	int end_p;
	int pipe_id;
	int weight;

	Edge(int start_p1, int end_p1, int pipe_id1, int weight1) {
		start_p = start_p1;
		end_p = end_p1;
		pipe_id = pipe_id1;
		weight = weight1;
	}
	void Print();
};

struct Graph {

	std::set <int> CsIds;
	std::vector <Edge> edges;
	std::vector <std::vector <int>> incedent = {};

	Graph() {
		CsIds = {};
		edges = {};
		incedent.resize(50);
	}

	Graph(Edge ed) {
		CsIds = { ed.end_p, ed.start_p };
		edges = { ed };
		incedent.resize(50);
		incedent[ed.start_p].push_back(ed.end_p);
	};
	void dfs(int vertex, std::vector <int>& ans, std::vector <bool>& used, bool& cycle, std::set <int>& us_to, int start);
};

class gas_transmission_network
{
	static inline int id_count = 0;
	int graph_number;
public:
	std::map <int, Pipe> all_p;
	std::map <int, CompStation> all_cs;
	std::map <int, Pipe> link_p;
	std::map <int, Graph> links;

	gas_transmission_network() {
		all_p = {};
		all_cs = {};
		links = {};
	}

	void CreatePipe();
	void CreatePipe(int& p_diam);
	void CreateCs();
	void PushToLinks(Edge ed);
	void show_pipes();
	void show_pipes(std::map <int, Pipe>& all_pp);
	void show_cs();
	void show_cs(std::map <int, CompStation>& all_cs1);
	void save_file();
	void load_file();
	void Edit_or_remove_p(std::vector <int> editing_id);
	void Edit_or_remove_cs(std::vector <int> editing_id);
	void Filter_pipes_name();
	void Filter_pipes_repair();
	void Filter_cs_name();
	void Filter_cs_percent();
	void Filter();
	void Batch_editing_p();
	void Batch_editing_cs();
	void Link_cs();
	void del_cs_graph();
	void del_p_graph();
	void show_links();
	void TopologicalSort();
	void Dijkstra();
	void maxFlow();
};
