#include <iostream>

#include <QApplication>

#include "MainApp.hpp"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	// all plugins are loaded in MainApp
	MainApp mainWidget;

	mainWidget.show();
	return app.exec();
}
