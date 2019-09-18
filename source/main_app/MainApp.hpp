#ifndef MAINAPP_HPP
#define MAINAPP_HPP

#include <memory>

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
 */
class MainApp : public QWidget
{
	Q_OBJECT

public:
	MainApp(QWidget *parent = nullptr);
	virtual ~MainApp() override;

protected slots:
	/** Update information displayed. */
	void changePlugin(const QString &pluginName);

private:
	std::unique_ptr<Ui::MainApp> _ui;
};

#endif // MAINAPP_HPP
