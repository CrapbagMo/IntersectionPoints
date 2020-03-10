#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
using namespace std;

Unordered_map intersect_points;
vector<line> lines;
/*vector<circle> circles;*/

int main(int argc, char *argv[])
{
	ifstream in;
	ofstream out;

	/*in.open("in_test.txt");
	out.open("out_test.txt");*/

	for (int i = 0; i < argc; i++) {	// 代替getopt()
		if (strcmp(argv[i], "-i") == 0) {
			in.open(argv[++i]);
		}
		if (strcmp(argv[i], "-o") == 0) {
			out.open(argv[++i]);
		}
	}

	int n;
	in >> n;

	for (int i = 0; i < n; i++) {
		char shape;
		in >> shape;
		if (shape != 'L') {
			cout << "out file error!" << endl;
			out << "out file error!" << endl;
			return 0;
		}
		int x1, y1, x2, y2;
		in >> x1;
		in >> y1;
		in >> x2;
		in >> y2;
		line Line;
		Line.generate_line(x1, y1, x2, y2);
		
		for (line it : lines) {
			if (it.parallel(Line)) {
				continue;
			}
			else {
				Line.getIntersectWithLine(it);
			}
		}

		lines.push_back(Line);
	}

	out << intersect_points.size();

}

