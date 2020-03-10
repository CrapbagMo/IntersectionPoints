#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
using namespace std;

Unordered_map intersect_points;
vector<pair<line, double>> lines;	// 斜率存下
vector<circle> circles;

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
		
		if (shape == 'L') {
			double x1, y1, x2, y2;
			in >> x1;
			in >> y1;
			in >> x2;
			in >> y2;
			line Line;
			Line.generate_line(x1, y1, x2, y2);
			double slope = Line.getSlope();
		
			for (pair<line, double> it : lines) {
				if (it.second == slope) {	//平行
					continue;
				}
				else {
					Line.getIntersectWithLine(it.first);
				}
			}

			for (circle it : circles) {
				it.getIntersectWithLine(Line);
			}

			lines.push_back(make_pair(Line, slope));
		}

		else if (shape == 'C') {
			double x0, y0, r;
			in >> x0;
			in >> y0;
			in >> r;
			circle newCircle;
			newCircle.generate_circle(x0, y0, r);

			for (pair<line, double> it : lines) {
				newCircle.getIntersectWithLine(it.first);
			}

			for (circle it : circles) {
				newCircle.getIntersectWithCircle(it);
			}
			circles.push_back(newCircle);
		}

		else {
			cout << "wrong type!" << endl;
			out << "wrong type!" << endl;
		}
	}

	out << intersect_points.size();

}

