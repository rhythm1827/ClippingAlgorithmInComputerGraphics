#include<bits/stdc++.h>

int Xmin, Ymin, Xmax, Ymax;

void writePixel(int x, int y)
{
	printf("(x,y) = (%d,%d)\n", x, y);
}

void midPoint(int x0, int y0, int x1, int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int d = 2 * dy - dx;
	int changeE = 2 * dy;
	int changeNE = 2 * (dy - dx);
	int x = x0;
	int y = y0;
	writePixel(x, y);
	while (x < x1)
	{
		if (d <= 0)
		{
			d += changeE;
			x++;
		}
		else
		{
			d += changeNE;
			x++;
			y++;
		}
		writePixel(x, y);
	}
}
int computeCode(double x, double y)
{
	int ans = 0;
	if (x < Xmin)
		ans |= 1;
	else if (x > Xmax)
		ans |= 2;
	if (y < Ymin)
		ans |= 4;
	else if (y > Ymax)
		ans |= 8;
	return ans;
}

void cohenLineClipping(double x1, double y1, double x2, double y2)
{
	double x, y;
	int code0 = computeCode(x1, y1);
	int code1 = computeCode(x2, y2);
	bool accept = false;
	while (true)
	{
		if ((code0 == 0) && (code1 == 0))
		{
			accept = true;
			break;
		}
		else if (code0 & code1)
			break;
		else
		{
			int outcode;
			if (code0 != 0)
				outcode = code0;
			else
				outcode = code1;
			if (outcode & 8)
			{
				x = x1 + (x2 - x1) * (Ymax - y1) / (y2 - y1);
				y = Ymax;
			}
			else if (outcode & 4)
			{
				x = x1 + (x2 - x1) * (Ymin - y1) / (y2 - y1);
				y = Ymin;
			}
			else if (outcode & 2)
			{
				y = y1 + (y2 - y1) * (Xmax - x1) / (x2 - x1);
				x = Xmax;
			}
			else if (outcode & 1)
			{
				y = y1 + (y2 - y1) * (Xmin - x1) / (x2 - x1);
				x = Xmin;
			}
			if (outcode == code0)
			{
				x1 = x;
				y1 = y;
				code0 = computeCode(x1, y1);
			}
			else
			{
				x2 = x;
				y2 = y;
				code1 = computeCode(x2, y2);
			}
		}
	}
	if (accept == true)
	{
		printf("Line accepted from (%d, %d) to (%d, %d)\nand touching points are given below.\n", (int)x1, (int)y1, (int)x2, (int)y2);
		midPoint(x1, y1, x2, y2);
	}
	else
		printf("Line rejected due to both endpoints are outside rectangle or in same region.\n");
}

int main()
{
	double x1, y1, x2, y2;
	Xmin = 10, Ymin = 10, Xmax = 50, Ymax = 50;
	int n;
	for (;;)
	{
		printf("|  Enter points  |\n");
		printf("X1: ");
		scanf_s("%lf", &x1);
		printf("\tY1: ");
		scanf_s("%lf", &y1);
		printf("X2: ");
		scanf_s("%lf", &x2);
		printf("\tY2: ");
		scanf_s("%lf", &y2);
		cohenLineClipping(x1, y1, x2, y2);
		printf("Enter 0 for break and any other key for new clipping!!");
		scanf_s("%d", &n);
		if (n == 0)
			break;
	}
	return 0;
}



