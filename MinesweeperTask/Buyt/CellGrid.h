#pragma once
#include <QGridLayout>
#include "Cell.h"


class CellGrid : public QGridLayout
{
	Q_OBJECT

public:
	CellGrid() = default;

	~CellGrid() override
	{
		Clean();
	}

public:
	void CreateGrid(QMargins margins, QWidget& target);

	std::vector<Cell*> GetCellsInRadius(int radius, Cell& cell) const;
	void GenerateMines(Cell& exclude);
	void OpenCell(Cell& cell);

	int GetMinesAmount() const
	{
		return m_minesAmount;
	}

	void SetSize(int sizeX, int sizeY)
	{
		m_sizeX = sizeX;
		m_sizeY = sizeY;
	}

private:
	void Clean();
	void CheckMines();
private:
	std::vector<Cell*> m_cells;
	int m_remainCells;
	bool m_minesGenerated = false;
	int m_sizeX = 0;
	int m_sizeY = 0;
	int m_minesAmount;

private slots:
	void OnCellClicked(Cell& cell, Qt::MouseButton button);
	void OnCellExploded(Cell& cell);
	void OnAllMinesFound() const;
signals:
	void CellClicked(Cell& cell, Qt::MouseButton button);
	void CellExploded();
	void AllMinesFound();
};
