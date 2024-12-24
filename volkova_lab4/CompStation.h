#pragma once
#include <string>
#include <map>

class CompStation
{
	static inline int id_count{};
	int id;
public:
	std::string name;
	int workshops;
	int working_workshops;
	double efficiency;

	CompStation() {
		++id_count;
		id = id_count;
		name = ' ';
		workshops = 0;
		working_workshops = 0;
		efficiency = 0;
	}

	CompStation(std::string cs_name, int cs_workshops, int cs_working_workshops, double cs_efficiency) {
		++id_count;
		id = id_count;
		name = cs_name;
		workshops = cs_workshops;
		working_workshops = cs_working_workshops;
		efficiency = cs_efficiency;
	}
	CompStation(int id_c, std::string cs_name, int cs_workshops, int cs_working_workshops, double cs_efficiency) {
		id = id_c;
		name = cs_name;
		workshops = cs_workshops;
		working_workshops = cs_working_workshops;
		efficiency = cs_efficiency;
	}
	void Print();
	void Push(std::map <int, CompStation>& myMap, CompStation cs);
	void SetId(int id_m);
};