#include "dijkstra.h"
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

int main()
{
	string line;
	int v1;
	int v2;
	int weight;
	char c;

	Graph g(200);
	ifstream infile("dijkstraData.txt");

	while (getline(infile, line))
	{
		stringstream ss;
		ss << line;
		ss >> v1;

		while (ss >> v2 >> c >> weight)
		{
			g.addEdge(v1, v2, weight);
		}
	}

	unsigned int *v = g.dijkstra();

	assert(v[7] == 2599);
	assert(v[37] == 2610);
	assert(v[59] == 2947);
	assert(v[82] == 2052);
	assert(v[99] == 2367);
	assert(v[115] == 2399);
	assert(v[133] == 2029);
	assert(v[165] == 2442);
	assert(v[188] == 2505);
	assert(v[197] == 3068);
}
