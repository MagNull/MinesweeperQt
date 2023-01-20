#pragma once
#include <QPushButton>
#include <qtmetamacros.h>

#include "CellGrid.h"

class ResizeButton : public QPushButton
{
	Q_OBJECT
public:
	ResizeButton(int sizeX, int sizeY, CellGrid* grid, QWidget* parent);

private:
	int m_sizeX;
	int m_sizeY;
};
