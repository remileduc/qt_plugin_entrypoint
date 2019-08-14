#ifndef MAINAPP_HPP
#define MAINAPP_HPP

#include <memory>
#include <vector>

#include <QPluginLoader>
#include <QWidget>

namespace Ui
{
	class MainApp;
}

/**
 * Main widget of the application.
 *
 * This widget shows what the selected plugin says.
 * You can also change tab and show the selected plugin metadata.
 *
 * All the plugins are automatically loaded on creation of this class.
 */
class MainApp : public QWidget
{
	Q_OBJECT

public:
	MainApp(QWidget* parent = nullptr);
	virtual ~MainApp() override;

protected slots:
	void changePlugin(const QString& pluginName);

private:
	std::unique_ptr<Ui::MainApp> _ui;
	/** List of loaded plugins */
	std::vector<std::unique_ptr<QPluginLoader>> _plugins;
};

#endif // MAINAPP_HPP
