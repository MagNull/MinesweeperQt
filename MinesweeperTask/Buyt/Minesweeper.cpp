#include "Minesweeper.h"

Minesweeper::Minesweeper(CellGrid* cellGrid, Smile* smile, QWidget* parent) : QObject(parent), m_pGrid(cellGrid),
                                                                              m_flagsRemains(m_pGrid->GetMinesAmount())
{
	connect(cellGrid, &CellGrid::CellClicked, this, &Minesweeper::OnCellClicked);
	connect(smile, &Smile::Restarted, this, [this]
	{
		m_flagsRemains = m_pGrid->GetMinesAmount();
		UpdateFlags();
	});
	m_remainsFlagsLabel = new QLabel(parent);
	m_remainsFlagsLabel->setFixedSize(45, 45);
	m_remainsFlagsLabel->setGeometry(900, 0, 50, 50);

	auto font = m_remainsFlagsLabel->font();
	font.setPointSize(20); //magic number... hehe
	m_remainsFlagsLabel->setFont(font);

	m_remainsFlagsLabel->show();
	UpdateFlags();
}

void Minesweeper::UpdateFlags() const
{
	m_remainsFlagsLabel->setText(QString::number(m_flagsRemains));
}


void Minesweeper::OnCellClicked(Cell& cell, Qt::MouseButton button)
{
	if (button == Qt::MouseButton::LeftButton)
	{
		m_pGrid->OpenCell(cell);
	}
	else
	{
		if (cell.GetState() == Closed && m_flagsRemains == 0)
			return;

		cell.ToggleFlag();
		if (cell.GetState() == Mark)
			m_flagsRemains--;
		else if (cell.GetState() == Closed)
			m_flagsRemains++;
		UpdateFlags();
	}
}
