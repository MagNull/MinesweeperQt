#include "Buyt.h"
#include <QtWidgets/QApplication>


int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	Buyt window;
	window.show();
	return application.exec();
}