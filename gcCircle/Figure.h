#pragma once
#include <Windows.h>

class Figure
{
public:
	Figure(const int size, const int offsetX, const int offsetY, COLORREF m_color);

	virtual void draw(const HDC& hdc) = 0;
	virtual bool isInnerPoint(const int x, const int y) = 0;

	void moveTo(const int x, const int y);
	void move(const int x, const int y);

	void startDragging(const int x, const int y);
	void drag(const int x, const int y);
	bool isDragging() const;
	void stopDragging(const int x, const int y);

protected:
	int m_size;
	int m_offsetX;
	int m_offsetY;
	COLORREF m_color;

	bool m_isDragging;
	int m_dragOffsetX;
	int m_dragOffsetY;
};
