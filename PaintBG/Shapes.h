#pragma once
#include <math.h>
#include <vector>
using namespace std;

class Shapes
{
protected:

public:
	COLORREF bgColor;
	int isFill, isThin;
	int x1, y1, x2, y2, style;
	Shapes();
	void SetColor(COLORREF NewColor) { bgColor = NewColor; }
	Shapes(int a1, int b1, int a2, int b2)
	{
		x1 = a1;
		x2 = a2;
		y1 = b1;
		y2 = b2;
		isFill = 0;
		bgColor = RGB(0, 0, 0);
	}
	Shapes(int a1, int b1, int a2, int b2, int fill, int thin, int color)
	{
		x1 = a1;
		x2 = a2;
		y1 = b1;
		y2 = b2;
		isFill = fill;
		isThin = thin;
		bgColor = color;
	}
	virtual int getMinX()
	{
		if (x1 < x2)
			return x1;
		return x2;
	}
	virtual int getMaxX()
	{
		if (x1 < x2)
			return x2;
		return x1;
	}
	virtual int getMinY()
	{
		if (y1 < y2)
			return y1;
		return y2;
	}
	virtual int getMaxY()
	{
		if (y1 < y2)
			return y2;
		return y1;
	}
	virtual void Build(CPoint cur) {}
	virtual CPoint lastP() { CPoint p(0, 0); return p; }
	virtual void Draw(CDC *dc) = 0;
	virtual bool isEx(CPoint p) = 0;
	virtual ~Shapes(void);
};
class MyRectangle :public Shapes
{
public:
	MyRectangle();
	MyRectangle(int a1, int b1, int a2, int b2)
		:Shapes(a1, b1, a2, b2)
	{
		style = 0;
	}
	MyRectangle(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color) //בונה מלבן חדש בהתאם למצב האפשרויות הנוספות 
		:Shapes(a1, b1, a2, b2, fill, thin, color)
	{
		style = 0;
	}
	void Draw(CDC *dc)
	{
		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		dc->SelectObject(&myPen);
		if (isFill)
			myBrush.CreateSolidBrush(bgColor);
		else
			myBrush.CreateSolidBrush(RGB(240, 240, 240));

		dc->SelectObject(myBrush);
		dc->Rectangle(x1, y1, x2, y2);
	}
	bool isEx(CPoint p)
	{
		int minX = getMinX(), maxX = getMaxX(), minY = getMinY(), maxY = getMaxY();
		if (!(p.x < minX || p.x > maxX || p.y < minY || p.y > maxY))
			return 1;
		return 0;
	}
};

class MySquare :public MyRectangle //ריבוע יורש ממלבן את ערכי נקודותיו
{
public:
	MySquare();
	MySquare(int a1, int b1, int a2, int b2)
		:MyRectangle(a1, b1, a2, b2)
	{
		style = 1;
	}
	MySquare(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color)
		:MyRectangle(a1, b1, a2, b2, fill, thin, color)
	{
		style = 1;
	}

	void Draw(CDC *dc)
	{
		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		dc->SelectObject(&myPen);
		if (isFill)
			myBrush.CreateSolidBrush(bgColor);
		else
			myBrush.CreateSolidBrush(RGB(240, 240, 240));
		dc->SelectObject(myBrush);

		if (abs((x1 - x2) == (y1 - y2)))
		{
			dc->Rectangle(x1, y1, x2, y2);
		}
		else
		{
			y1 = y2 - abs(x1 - x2);
			dc->Rectangle(x1, y1, x2, y2);
		}
	}
};
class MyEllipse :public MyRectangle
{
public:
	MyEllipse();
	MyEllipse(int a1, int b1, int a2, int b2)
		:MyRectangle(a1, b1, a2, b2)
	{
		style = 2;
	}
	MyEllipse(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color)
		:MyRectangle(a1, b1, a2, b2, fill, thin, color)
	{
		style = 2;
	}
	void Draw(CDC *dc)
	{
		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		dc->SelectObject(&myPen);
		if (isFill)
			myBrush.CreateSolidBrush(bgColor);
		else
			myBrush.CreateSolidBrush(RGB(240, 240, 240));
		dc->SelectObject(myBrush);
		dc->Ellipse(x1, y1, x2, y2);
	}
};

class MyCircle :public MyEllipse {
public:
	MyCircle();
	MyCircle(int a1, int b1, int a2, int b2)
		:MyEllipse(a1, b1, a2, b2)
	{
		style = 3;
	}
	MyCircle(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color)
		:MyEllipse(a1, b1, a2, b2, fill, thin, color)
	{
		style = 3;
	}
	void Draw(CDC *dc)
	{
		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		dc->SelectObject(&myPen);
		if (isFill)
			myBrush.CreateSolidBrush(bgColor);
		else
			myBrush.CreateSolidBrush(RGB(240, 240, 240));
		dc->SelectObject(myBrush);
		if (abs((x1 - x2) == (y1 - y2)))
		{
			dc->Ellipse(x1, y1, x2, y2);
		}
		else
		{
			y1 = y2 - abs(x1 - x2);
			dc->Ellipse(x1, y1, x2, y2);
		}
	}
};

class MyTriangle :public Shapes
{
public:
	MyTriangle();
	MyTriangle(int a1, int b1, int a2, int b2)
		:Shapes(a1, b1, a2, b2)
	{
		style = 4;
	}
	MyTriangle(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color)
		:Shapes(a1, b1, a2, b2, fill, thin, color)
	{
		style = 4;
	}
	void Draw(CDC *dc)
	{
		CPoint pt[3];
		pt[0].SetPoint(x1, y2);
		pt[1].SetPoint(x2, y2);
		pt[2].SetPoint((x1 + x2) / 2, y1);
		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		dc->SelectObject(&myPen);
		if (isFill)
			myBrush.CreateSolidBrush(bgColor);
		else
			myBrush.CreateSolidBrush(RGB(240, 240, 240));
		dc->SelectObject(myBrush);
		dc->Polygon(pt, 3);
	}
	bool isEx(CPoint p)
	{
		int minX = getMinX(), maxX = getMaxX(), minY = getMinY(), maxY = getMaxY();
		if (!(p.x < minX || p.x > maxX || p.y < minY || p.y > maxY))
			return 1;
		return 0;
	}

};
class MyLine :public Shapes {
public:
	MyLine();
	MyLine(int a1, int b1, int a2, int b2)
		:Shapes(a1, b1, a2, b2)
	{
		style = 5;
	}
	MyLine(int a1, int b1, int a2, int b2, int thin, COLORREF color)
		:Shapes(a1, b1, a2, b2, 0, thin, color)
	{
		style = 5;
	}
	void Draw(CDC *dc)
	{
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		dc->SelectObject(&myPen);
		dc->MoveTo(x1, y1);
		dc->LineTo(x2, y2);
	}

	bool isEx(CPoint p)
	{
		int yy = y1 - y2, xx = x1 - x2;
		int minX = getMinX(), maxX = getMaxX(), minY = getMinY(), maxY = getMaxY();
		double m = (double)yy / (double)xx;
		if ((p.y - y1 - m * (p.x - x1)) > -7 && (p.y - y1 - m * (p.x - x1) < 7) && (!(p.x < minX || p.x > maxX || p.y < minY || p.y > maxY)))
			return 1;
		return 0;
	}
};

