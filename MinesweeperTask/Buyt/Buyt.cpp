#include "Buyt.h"
#include "Minesweeper.h"
#include "GameTimer.h"
#include <random>

#include "ResizeButton.h"


Buyt::Buyt(QWidget* parent)
	: QMainWindow(parent)
{
	int width = 1024;
	int height = 720;

	QWidget* window = new QWidget();
	setCentralWidget(window);
	setFixedSize(width, height);
	window -> setFixedSize(width, height);


	auto grid = new CellGrid();
	auto smile = new Smile(grid, window);
	auto timer = new GameTimer(grid, smile, window);
	auto minesweeper = new Minesweeper(grid, smile, window);

	auto resizeButton8x8 = new ResizeButton(8, 8, grid, window);
	resizeButton8x8->setGeometry(625, 0, 50, 50);

	auto resizeButton16x16 = new ResizeButton(16, 16, grid, window);
	resizeButton16x16->setGeometry(675, 0, 50, 50);

	auto resizeButton32x32 = new ResizeButton(32, 32, grid, window);
	resizeButton32x32->setGeometry(725, 0, 50, 50);
}

Buyt::~Buyt()
{
}
