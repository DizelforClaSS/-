#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
using namespace std;
int* solveSystem(double a, double b, double c, double d, double e, double f);
int main()
{
	_ASSERT(solveSystem(0, 0, 0, 0, 0, 0), "0");
}

int* solveSystem(double a, double b, double c, double d, double e, double f){
	stringstream s;
	if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 0) && (f == 0))
	{
		s << '5';
	}
	else if ((a * d - c * b != 0) && ((e * d - b * f != 0) || (a * f - c * e != 0)))
	{
		double y = (a * f - c * e) / (a * d - c * b);
		double x = (d * e - b * f) / (d * a - b * c);
		s << "2 " << x << ' ' << y;
	}
	else if (((a * d - c * b == 0) && ((e * d - b * f != 0) || (a * f - c * e != 0))) ||
		(a == 0 && c == 0 && e / b != f / d) ||
		(b == 0 && d == 0 && e / a != f / c) ||
		(a == 0 && b == 0 && c == 0 && d == 0 && (e / f > 0)))
	{
		if (((a == 0 && b == 0 && e == 0 && d != 0 && c == 0) ||
			(c == 0 && d == 0 && f == 0 && b != 0 && a == 0)))
		{
			double y;
			if (b == 0)
				y = f / d;
			else if (d == 0)
				y = e / b;
			else if (e == 0 || f == 0)
				y = 0;
			s << '4' << ' ' << y;
		}
		else if (((a == 0 && b == 0 && e == 0 && c != 0 && d == 0) ||
			(c == 0 && d == 0 && f == 0 && a != 0 && b == 0)))
		{
			double x;
			if (a == 0)
				x = f / c;
			else if (c == 0)
				x = e / a;
			else if (e == 0 || f == 0)
				x = 0;
			s << '3' << ' ' << x;
		}
		else
			s << '0';
	}
	else if (a == 0 && c == 0)
	{
		double y;
		if (e == 0)
			y = f / d;
		else if (f == 0)
			y = e / b;
		else
			y = e / b;
		s << '4' << ' ' << y;
	}
	else if (b == 0 && d == 0)
	{
		double x;
		if (e == 0)
			x = f / c;
		else if (f == 0)
			x = e / a;
		else
			x = e / a;
		s << '3' << ' ' << x;
	}
	else if (b == 0 && e == 0)
	{
		double k, n;
		k = -c / d;
		n = f / d;
		s << '1' << ' ' << k << ' ' << n;
	}
	else if (d == 0 && f == 0)
	{
		double k, n;
		k = -a / b;
		n = e / b;
		s << '1' << ' ' << k << ' ' << n;
	}
	else if (a == 0 && e == 0)
	{
		double k, n;
		k = -d / c;
		n = f / c;
		s << '1' << ' ' << k << ' ' << n;
	}
	else if (c == 0 && f == 0)
	{
		double k, n;
		k = -b / a;
		n = e / a;
		s << '1' << ' ' << k << ' ' << n;
	}
	else if ((a / b == c / d))
	{
		double k, n;
		k = -c / d;
		n = f / d;
		s << '1' << ' ' << k << ' ' << n;
	}
	else
	{
		s << "are you kidding me?";
	}

	return 0;
}