#pragma once
#include <map>
#include <string>

class Pipe
{
	static inline int id_count = 0;
	int id;
public:
	std::string name;
	double lenght;
	int diam;
	bool repair;

	Pipe() {
		++id_count;
		id = id_count;
		name = " ";
		lenght = 0;
		diam = 0;
		repair = 0;

	}
	Pipe(std::string p_name, double p_lenght, int p_diam, bool p_repair) {
		++id_count;
		id = id_count;
		name = p_name;
		lenght = p_lenght;
		diam = p_diam;
		repair = p_repair;

	}
	Pipe(int id_c, std::string p_name, double p_lenght, int p_diam, bool p_repair) {

		id = id_c;
		name = p_name;
		lenght = p_lenght;
		diam = p_diam;
		repair = p_repair;

	}


	void Print();
	void Push(std::map <int, Pipe>& myMap, Pipe pipe);
	void SetId(int id_m);
};