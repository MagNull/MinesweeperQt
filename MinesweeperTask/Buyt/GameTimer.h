#pragma once
#include <QLabel>
#include <QTimer>

#include "Smile.h"
#include "CellGrid.h"

class GameTimer : public QLabel
{
public:
	GameTimer(CellGrid* grid, Smile* smile, QWidget* parent);
private:
	void RestartTimer();

private:
	int m_timerValue = 0;
	QTimer m_timer = QTimer(this);
private slots:
	void OnExploded();
	void OnSmileClicked();
};
