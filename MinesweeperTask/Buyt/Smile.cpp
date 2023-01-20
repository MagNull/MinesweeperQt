#include "Smile.h"

Smile::Smile(CellGrid* grid, QWidget* parent) : QPushButton(parent), m_grid(grid)
{
	smile = QIcon("Image/smiley1.ico");
	explodeSmile = QIcon("Image/smiley3.ico");
	winSmile = QIcon("Image/winSmile.ico");

	setIcon(smile);
	setIconSize(size());
	setFlat(true);
	setFixedSize(50, 50);
	setGeometry(parentWidget()->width() / 2 - width(), 0, 50, 50);

	connect(this, &Smile::clicked, this, &Smile::OnClick);
	connect(grid, &CellGrid::CellExploded, this, &Smile::OnCellExploded);
	connect(grid, &CellGrid::AllMinesFound, this, &Smile::OnMinesFound);

	show();
}

void Smile::OnClick()
{
	setIcon(smile);
	m_grid->CreateGrid(QMargins(0, 50, 0, 0), *parentWidget());
	emit Restarted();
}

void Smile::OnMinesFound()
{
	setIcon(winSmile);
}


void Smile::OnCellExploded()
{
	setIcon(explodeSmile);
}
