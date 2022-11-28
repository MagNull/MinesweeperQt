#include "CellGrid.h"
#include <algorithm>


void CellGrid::CreateGrid(QMargins margins, QWidget& target)
{
	Clean();
	if (m_sizeX == 0 || m_sizeY == 0)
	{
		return;
	}

	m_minesAmount = m_sizeX * m_sizeY / 5;
	setContentsMargins(margins);
	setSpacing(0);
	m_cells.reserve(m_sizeY * m_sizeX);
	auto cellSize = (target.height() - margins.top()) / m_sizeY;
	for (auto i = 0; i < m_sizeX * m_sizeY; i++)
	{
		auto cell = new Cell(&target);
		cell->setFixedSize(cellSize, cellSize);
		cell->setIconSize(QSize(cellSize, cellSize));

		connect(cell, &Cell::Clicked, this, &CellGrid::OnCellClicked);
		connect(cell, &Cell::Exploded, this, &CellGrid::OnCellExploded);

		m_cells.push_back(cell);
		addWidget(cell, i % m_sizeY, i / m_sizeX);
	}
	connect(this, &CellGrid::AllMinesFound, this, &CellGrid::OnAllMinesFound);
	target.setLayout(this);
	m_minesGenerated = false;
	m_remainCells = m_sizeX * m_sizeY - m_minesAmount;
}

void CellGrid::OnCellClicked(Cell& cell, Qt::MouseButton button)
{
	if (!m_minesGenerated)
	{
		GenerateMines(cell);
		m_minesGenerated = true;
	}
	emit CellClicked(cell, button);
}

void CellGrid::OnCellExploded(Cell& cell)
{
	for (auto c : m_cells)
	{
		disconnect(c, &Cell::Clicked, this, &CellGrid::OnCellClicked);
		if (&cell == c)
			continue;
		c->Show();
	}
	emit CellExploded();
}

void CellGrid::OnAllMinesFound() const
{
	for (auto c : m_cells)
	{
		disconnect(c, &Cell::Clicked, this, &CellGrid::OnCellClicked);
	}
}

void CellGrid::CheckMines()
{
	if (m_remainCells > 0)
		return;
	for (auto c : m_cells)
	{
		c->Show();
	}
	emit AllMinesFound();
}


void CellGrid::GenerateMines(Cell& exclude)
{
	for (auto i = 0; i < m_minesAmount; i++)
	{
		auto cell = m_cells[rand() % m_cells.size()];
		if (cell->HasMine() || cell == &exclude)
		{
			i--;
			continue;
		}
		cell->SetMine();
	}
}


std::vector<Cell*> CellGrid::GetCellsInRadius(int radius, Cell& cell) const
{
	std::vector<Cell*> cells;
	int cellX;
	int cellY;
	int spanX;
	int spanY;
	getItemPosition(indexOf(&cell), &cellY, &cellX, &spanX, &spanY);
	for (auto x = -radius; x <= radius; x++)
	{
		for (auto y = -radius; y <= radius; y++)
		{
			auto item = itemAtPosition(cellY + y, cellX + x);
			if (item == nullptr)
				continue;
			auto index = indexOf(item->widget());
			if (index != -1)
			{
				cells.push_back(dynamic_cast<Cell*>(itemAt(index)->widget()));
			}
		}
	}

	return cells;
}

void CellGrid::OpenCell(Cell& cell)
{
	if (cell.GetState() != Closed)
		return;
	if (cell.HasMine())
	{
		cell.Explode();
		return;
	}

	cell.SetState(Open);
	m_remainCells--;
	cell.setIcon(QIcon());

	auto cells = GetCellsInRadius(1, cell);
	auto mines = std::count_if(cells.begin(), cells.end(), [](Cell* cell)
	{
		return cell->HasMine();
	});
	if (mines == 0)
	{
		for (auto c : cells)
		{
			OpenCell(*c);
		}
	}
	else
	{
		cell.setText(QString::number(mines));
	}
	CheckMines();
}

void CellGrid::Clean()
{
	for (auto c : m_cells)
	{
		removeWidget(c);
		disconnect(c, &Cell::Clicked, this, &CellGrid::OnCellClicked);
		disconnect(c, &Cell::Exploded, this, &CellGrid::OnCellExploded);
		delete c;
	}
	m_cells.clear();
}
