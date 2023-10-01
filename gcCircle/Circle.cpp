#include "Circle.h"
#include <cmath>

Circle::Circle(const int size, const int offsetX, const int offsetY, COLORREF m_color ) :
	Figure(size, offsetX, offsetY, m_color)
{
}

void Circle::draw(const HDC& hdc)
{
	int x = m_offsetX - m_size / 2;
	int y = m_offsetY - m_size / 2;
	HBRUSH hBrush = CreateSolidBrush(m_color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, x, y, x + m_size, y + m_size);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

bool Circle::isInnerPoint(const int x, const int y)
{
	int dx = x - m_offsetX;
	int dy = y - m_offsetY;
	return sqrt(dx * dx + dy * dy) <= m_size / 2;
}