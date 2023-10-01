#include "Figure.h"

Figure::Figure(const int size, const int offsetX, const int offsetY, COLORREF _m_color) :
	m_size(size),
	m_offsetX(offsetX),
	m_offsetY(offsetY),
	m_color(_m_color)
{
	m_isDragging = false;
}

void Figure::moveTo(const int x, const int y)
{
	m_offsetX = x;
	m_offsetY = y;
}

void Figure::move(const int x, const int y)
{
	m_offsetX += x;
	m_offsetY += y;
}

void Figure::startDragging(const int x, const int y)
{
	if (isInnerPoint(x, y)) {
		m_isDragging = true;
		m_dragOffsetX = x - m_offsetX;
		m_dragOffsetY = y - m_offsetY;
	}
}

void Figure::drag(const int x, const int y)
{
	if (m_isDragging) {
		m_offsetX = x - m_dragOffsetX;
		m_offsetY = y - m_dragOffsetY;
	}
}

bool Figure::isDragging() const
{
	return m_isDragging;
}

void Figure::stopDragging(const int x, const int y)
{
	m_isDragging = false;
}
