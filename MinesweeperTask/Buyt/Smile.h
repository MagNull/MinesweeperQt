#pragma once
#include "CellGrid.h"

class Smile : public QPushButton
{
	Q_OBJECT
public:
	Smile(CellGrid* grid, QWidget* parent);
private:
	CellGrid* m_grid;
	QIcon smile;
	QIcon explodeSmile;
	QIcon winSmile;
private slots:
	void OnClick();
	void OnCellExploded();
	void OnMinesFound();
signals:
	void Restarted();
};
