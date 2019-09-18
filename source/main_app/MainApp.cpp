#include "MainApp.hpp"
#include "ui_MainApp.h"

#include <algorithm>

#include <PluginInterface.hpp>
#include <PluginManager.hpp>

MainApp::MainApp(QWidget *parent) : QWidget(parent), _ui(std::make_unique<Ui::MainApp>())
{
	_ui->setupUi(this);

	// fill the combobox
	for (const auto &plugin : PluginManager::get().getPlugins())
		_ui->comboBox->addItem(plugin->name());

	connect(_ui->comboBox, &QComboBox::currentTextChanged, this, &MainApp::changePlugin);
	if (_ui->comboBox->count())
		changePlugin(_ui->comboBox->currentText());
}

MainApp::~MainApp() = default;

void MainApp::changePlugin(const QString &pluginName)
{
	_ui->contentEdit->clear();
	_ui->metadataEdit->clear();

	auto *plugin = PluginManager::get().getPlugin(pluginName);
	if (plugin)
	{
		_ui->contentEdit->setPlainText(plugin->contents());
		// fill entry points
		QString mdcontent;
		const auto &pmanager = PluginManager::get();
		for (const auto &entriename : pmanager.getEntryNames())
		{
			const auto &list = pmanager.getEntryPoints(entriename);
			auto it = std::find_if(std::cbegin(list), std::cend(list), [&plugin](const auto &entrypoint) { return entrypoint.plugin == plugin; });
			if (it != std::cend(list))
				mdcontent += plugin->name() + " exposes '" + it->meta->className() + "' on '" + entriename + "'\n";
		}
		_ui->metadataEdit->setPlainText(mdcontent);
	}
}
