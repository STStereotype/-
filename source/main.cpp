#include <iostream>
#include <fstream>
#include "task.h"

using namespace std;

int main()
{
	std::vector<unit> units;
	std::vector<int> result;
	std::vector<std::string> str;

	int count = 0;

	// input
	std::ifstream in("input.txt");
	if (in.is_open())
	{
		in >> count;
		unit t;
		for (int i = 0; i < count; i++)
		{
			in >> t.position.x >> t.position.y;
			in >> t.direction.x >> t.direction.y;
			in >> t.fov_deg >> t.distance;
			units.push_back(t);
		}
		in.close();
	}
	
	// invoke
	Task::checkVisible(units, result);

	std::ofstream out;
	out.open("output.txt");
	if (out.is_open())
	{
		for (int i = 0; i < count; i++)
			out << result[i] << std::endl;
		out.close();
	}
	return 0;
}
