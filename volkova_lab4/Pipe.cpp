#include "Pipe.h"
#include <iostream>

using namespace std;

void Pipe::Print() {
	cout << id << endl;
	cout << "Pipe name: " << name << endl;
	cout << "Pipe length: " << lenght << endl;
	cout << "Pipe diameter: " << diam << endl;
	cout << "Under repair: " << repair << endl;
}

void Pipe::Push(std::map<int, Pipe>& myMap, Pipe pipe)
{
	myMap.emplace(id, pipe);
}

void Pipe::SetId(int id_m)
{
	id_count = id_m;
}

