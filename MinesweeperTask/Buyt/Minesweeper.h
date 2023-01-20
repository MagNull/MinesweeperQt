#pragma once
#include <QLabel>

#include "CellGrid.h"
#include "Smile.h"

class Minesweeper : public QObject
{
	Q_OBJECT
public:
	Minesweeper(CellGrid* cellGrid, Smile* smile, QWidget* parent);
private:
	void UpdateFlags() const;
	void OpenCell(Cell& cell);

private:
	CellGrid* m_pGrid;
	QLabel* m_remainsFlagsLabel;
	int m_flagsRemains;
private slots:
	void OnCellClicked(Cell& cell, Qt::MouseButton button);
};
