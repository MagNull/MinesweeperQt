#include "Cell.h"


std::unique_ptr<QIcon> Cell::m_pDefaultIcon;
std::unique_ptr<QIcon> Cell::m_pExplodedMineIcon;
std::unique_ptr<QIcon> Cell::m_pMineIcon;
std::unique_ptr<QIcon> Cell::m_pMarkIcon;

Cell::Cell()
{
	Init();
}

void Cell::Init()
{
	if (m_pDefaultIcon == nullptr)
		m_pDefaultIcon = std::make_unique<QIcon>("Image/tile.ico");
	if (m_pExplodedMineIcon == nullptr)
		m_pExplodedMineIcon = std::make_unique<QIcon>("Image/mine3.ico");
	if (m_pMineIcon == nullptr)
		m_pMineIcon = std::make_unique<QIcon>("Image/mine2.ico");
	if (m_pMarkIcon == nullptr)
		m_pMarkIcon = std::make_unique<QIcon>("Image/tile3.ico");

	setIcon(*m_pDefaultIcon);

	auto font = this->font();
	font.setPointSize(14); //magic number... hehe
	setFont(font);

	setFlat(true);
}

void Cell::Show()
{
	if (HasMine())
		setIcon(*m_pMineIcon);
	m_state = Open;
}


void Cell::ToggleFlag()
{
	if (m_state == Mark)
	{
		m_state = Closed;
		setIcon(*m_pDefaultIcon);
	}
	else if (m_state == Closed)
	{
		m_state = Mark;
		setIcon(*m_pMarkIcon);
	}
}

void Cell::Explode()
{
	m_state = CellState::Explode;
	setIcon(*m_pExplodedMineIcon);
	emit Exploded(*this);
}


void Cell::mousePressEvent(QMouseEvent* event)
{
	emit Clicked(*this, event->button());
}
