#pragma once
#include "Figure.h"

class Circle : public Figure
{
public:
	Circle(const int size, const int offsetX, const int offsetY, COLORREF m_color);
	void draw(const HDC& hdc) override;
	bool isInnerPoint(const int x, const int y) override;
};

