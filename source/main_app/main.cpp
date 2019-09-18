#include <QApplication>

#include <PluginManager.hpp>

#include "MainApp.hpp"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	// we load the plugins
	PluginManager::get().loadPlugins();

	// we create the main window
	MainApp mainWidget;

	// we launch the app
	mainWidget.show();
	return app.exec();
}
