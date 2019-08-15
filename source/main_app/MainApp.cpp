#include "MainApp.hpp"
#include "ui_MainApp.h"

#include <QJsonDocument>

#include <PluginInterface.hpp>
#include <utils.hpp>

MainApp::MainApp(QWidget* parent) :
	QWidget(parent),
	_ui(std::make_unique<Ui::MainApp>()),
	_plugins(utils::loadPlugins())
{
	_ui->setupUi(this);

	// fill the combobox
	for (const auto& plugin : _plugins)
		_ui->comboBox->addItem(utils::getPluginName(*plugin));

	connect(_ui->comboBox, &QComboBox::currentTextChanged, this, &MainApp::changePlugin);
	if (_ui->comboBox->count())
		changePlugin(_ui->comboBox->currentText());
}

MainApp::~MainApp() = default;

void MainApp::changePlugin(const QString& pluginName)
{
	_ui->contentEdit->clear();
	_ui->metadataEdit->clear();

	auto* plugin = utils::getPlugin(std::cbegin(_plugins), std::cend(_plugins), pluginName);
	if (plugin)
	{
		_ui->contentEdit->setPlainText(utils::getPluginInterface(*plugin)->contents());
		_ui->metadataEdit->setPlainText(QJsonDocument(utils::getPluginMetadataFull(*plugin)).toJson(QJsonDocument::Indented));
	}
}
