#pragma once
#include <map>
#include <vector>
#include <unordered_map>
constexpr auto infinite = 2333333.33;
using namespace std;

struct pair_hash {		// ����hash
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& p) {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);
		return h1 ^ h2;
	}
};


using Vote = pair<double, double>;
using Unordered_map = unordered_map<Vote, int, pair_hash>;
typedef pair<double, double> point;

extern Unordered_map intersect_points;

// ֱ��
class line {

private :		// ��׼���̱�ʾ
	double A;
	double B;
	double C;	

public:

	void generate_line(int x1, int y1, int x2, int y2) {		//��ABC
		A = (double)y2 - y1;
		B = (double)x1 - x2;
		C = (double)x2 * y1 - x1 * y2;
	}

	void generate_line(double a, double b, double c) {		//��ABC
		A = a;
		B = b;
		C = c;
	}

	double getSlope() {		// б��
		if (A == 0) {
			return 0;
		}
		else if (B == 0) {
			return infinite;
		}
		else {
			return -(A / B);
		}
	}

	bool parallel(line another) {		
		return A * another.B == B * another.A;
	}

	double getA() {
		return A;
	}

	double getB() {
		return B;
	}

	double getC() {
		return C;
	}

	double getDistance(point p) {	// �㵽ֱ�ߵľ���
		return (A * p.first + B * p.second + C) / sqrt(A * A + B * B);
	}

	void getIntersectWithLine(line another) {
		double x = (another.C * B - C * another.B) / (A * another.B - another.A * B);
		double y = (C * another.A - another.C * A) / (A * another.B - another.A * B);
		intersect_points[make_pair(x, y)] = 1;
	}
};

/*class circle {
private:
	int x0, y0, r;

public:

	void generate_circle(int x0, int y0, int r) {
		this->x0 = x0;
		this->y0 = y0;
		this->r = r;
	}

	void getIntersectWithCircle(circle another) {

		int x1 = another.x0;
		int y1 = another.y0;
		int r1 = another.r;

		if (x0 == x1 && y0 == y1) {	//ͬ��
			return;			//�뾶���Ҳ��0
		}
		else {
			double dis = sqrt((x1 - x0) * (x1 - x0) +
				(y1 - y0) * (y1 - y0));
			if (dis > r + r1 || dis < abs(r - r1)) {

			}
		}
	}
};*/