#include "CompStation.h"
#include <iostream>
using namespace std;


void CompStation::Print()
{
	cout << id << endl;
	cout << "CS name: " << name << endl;
	cout << "The number of workshops: " << workshops << endl;
	cout << "The number of working workshops: " << working_workshops << endl;
	cout << "Efficiency: " << efficiency << endl;
}

void CompStation::Push(std::map<int, CompStation>& myMap, CompStation cs)
{
	myMap.emplace(id, cs);
}

void CompStation::SetId(int id_m)
{
	id_count = id_m;
}
