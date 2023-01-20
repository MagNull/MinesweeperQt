#include "ResizeButton.h"


ResizeButton::ResizeButton(int sizeX, int sizeY, CellGrid* grid, QWidget* parent)
	: QPushButton(parent)
	  , m_sizeX(sizeX)
	  , m_sizeY(sizeY)
{
	setText(QString::number(m_sizeX) + "x" + QString::number(m_sizeY));
	connect(this, &QPushButton::clicked, this, [this, grid]
	{
		grid->SetSize(m_sizeX, m_sizeY);
	});
}
