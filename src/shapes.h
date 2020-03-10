#pragma once
#include <map>
#include <vector>
#include <unordered_map>
constexpr auto infinite = 2333333.33;
using namespace std;

struct pair_hash {		// ����hash
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& p) const {
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

	void generate_line(double x1, double y1, double x2, double y2) {		//��ABC
		A = y2 - y1;
		B = x1 - x2;
		C = x2 * y1 - x1 * y2;
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

class circle {
private:
	double x0, y0, r;

public:

	void generate_circle(double x0, double y0, double r) {
		this->x0 = x0;
		this->y0 = y0;
		this->r = r;
	}

	void getIntersectWithLine(line Line) {
		double A = Line.getA();
		double B = Line.getB();
		double C = Line.getC();

		line newline;
		newline.generate_line(B, -A, A * y0 - B * x0);
		point center = make_pair(x0, y0);
		double dis = newline.getDistance(center);

		double x = (newline.getC() * B - C * newline.getB()) / (A * newline.getB() - newline.getA() * B);
		double y = (C * newline.getA() - newline.getA()) / (A * newline.getB() - newline.getA() * B);
		point foot = make_pair(x, y);

		//����Բ�ĵ�ֱ�ߵľ����ж��Ƿ��н���

		if (dis < r) {
			// ��������
			pair<double, double> mini = make_pair(B / sqrt(A * A + B * B), -A / sqrt(A * A + B * B));
			double base = sqrt(r * r - dis * dis);
			point p1;
			p1 = make_pair(foot.first + mini.first * base,
				foot.second + mini.second * base);
			point p2;
			p2 = make_pair(foot.first - mini.first * base,
				foot.second - mini.second * base);
			intersect_points[p1] = 1;
			intersect_points[p2] = 1;
		}
		else if(dis == r) {
			// ����Ϊ����
			intersect_points[foot] = 1;
		}
		else {	//�޽���
			return;
		}
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
			if (dis <= r + r1 || dis >= abs(r - r1)) {	// �⽻���ڽ�
				line newline;
				newline.generate_line(2 * x1 - 2 * x0, 2 * y1 - 2 * y0, 
					-x1 * x1 + x0 * x0 - y1 * y1 + y0 * y0 + r1 * r1 - r * r);
				getIntersectWithLine(newline);
			}
		}
	}
};