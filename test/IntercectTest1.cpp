#include "pch.h"
#include "CppUnitTest.h"
#include "..\Intersection_points\shapes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntercectTest1
{
	TEST_CLASS(IntercectTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			line Line;
			line Line1;
			Line.generate_line(7, 6, 5, 4);
			Line1.generate_line(2, 4, 6, 9);
			Assert::AreEqual(false, Line.getSlope() == Line1.getSlope());
		}

		TEST_METHOD(TestMethod2)
		{
			line Line;
			line Line1;
			Line.generate_line(7, 6, 5, 4);
			Line1.generate_line(1, 4, 6, 9);
			Assert::AreEqual(true, Line.getSlope() == Line1.getSlope());
		}

		TEST_METHOD(TestMethod3)
		{
			line Line;
			Line.generate_line(233, 5, 244, 5);
			Assert::AreEqual(true, Line.getSlope() == 0);
		}

		TEST_METHOD(TestMethod4)
		{
			line Line;
			Line.generate_line(233, 5, 233, 9);
			Assert::AreEqual(true, Line.getSlope() == infinite);
		}

		TEST_METHOD(TestMethod5)
		{
			line Line;
			Line.generate_line(233, 5, 233, 9);
			line Line1;
			Line1.generate_line(0, 0, 1, 0);
			int sizebefore = intersect_points.size();
			Line.getIntersectWithLine(Line1);
			Assert::AreEqual(true, intersect_points.size() == sizebefore + 1);
		}

		TEST_METHOD(TestMethod6)
		{
			line Line;
			Line.generate_line(233, 5, 233, 9);
			line Line1;
			Line1.generate_line(222, 5, 222, 9);
			int sizebefore = intersect_points.size();
			Line.getIntersectWithLine(Line1);
			Assert::AreEqual(false, intersect_points.size() == sizebefore);
		}

		TEST_METHOD(TestMethod7)
		{
			line Line;
			Line.generate_line(0, 0, 0, 1);
			circle C;
			C.generate_circle(1, 0, 2);
			int sizebefore = intersect_points.size();
			C.getIntersectWithLine(Line);
			Assert::AreEqual(true, intersect_points.size() == sizebefore + 2);
		}

		TEST_METHOD(TestMethod8)
		{
			line Line;
			Line.generate_line(0, 0, 0, 1);
			circle C;
			C.generate_circle(2, 0, 1);
			int sizebefore = intersect_points.size();
			C.getIntersectWithLine(Line);
			Assert::AreEqual(false, intersect_points.size() == sizebefore);
		}

		TEST_METHOD(TestMethod9)
		{
			line Line;
			Line.generate_line(33, 2, 1, 9);
			circle C;
			C.generate_circle(0, 0, 15);
			int sizebefore = intersect_points.size();
			C.getIntersectWithLine(Line);
			Assert::AreEqual(false, intersect_points.size() == sizebefore);
		}

		TEST_METHOD(TestMethod10)
		{
			line Line;
			Line.generate_line(13, 20, 31, 69);
			circle C;
			C.generate_circle(5, 5, 6);
			int sizebefore = intersect_points.size();
			C.getIntersectWithLine(Line);
			Assert::AreEqual(false, intersect_points.size() == sizebefore);
		}
	};
}
