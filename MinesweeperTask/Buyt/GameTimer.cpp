#include "GameTimer.h"

GameTimer::GameTimer(CellGrid* grid, Smile* smile, QWidget* parent) : QLabel(parent)
{
	setFixedSize(75, 50);
	setGeometry(50, 0, 75, 50);

	auto font = this->font();
	font.setPointSize(20); //magic number... hehe
	setFont(font);

	connect(grid, &CellGrid::CellExploded, this, &GameTimer::OnExploded);
	connect(grid, &CellGrid::AllMinesFound, this, [this]
	{
		m_timer.stop();
	});
	connect(smile, &Smile::clicked, this, &GameTimer::OnSmileClicked);

	setText(QString::number(m_timerValue));
	connect(&m_timer, &QTimer::timeout, this, [this]
	{
		m_timerValue += 1;
		setText(QString::number(m_timerValue));
	});
	m_timer.setInterval(1000);
	m_timer.start();

	show();
}

void GameTimer::OnExploded()
{
	m_timer.stop();
}

void GameTimer::OnSmileClicked()
{
	RestartTimer();
}

void GameTimer::RestartTimer()
{
	m_timerValue = 0;
	setText(QString::number(m_timerValue));
	m_timer.start();
}
