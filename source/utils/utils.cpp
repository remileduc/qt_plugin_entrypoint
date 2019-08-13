#include "utils.hpp"

#include <algorithm>

#include <QCoreApplication>
#include <QDir>

#include "PluginInterface.hpp"

std::vector<std::unique_ptr<QPluginLoader>> utils::loadPlugins()
{
	using pluginvect = std::vector<std::unique_ptr<QPluginLoader>>;

	pluginvect plugins;
	QDir pluginsDir(QCoreApplication::instance()->applicationDirPath());
	const auto entryList = pluginsDir.entryList(QDir::Files);

	for (const auto& fileName : entryList)
	{
		auto plugin = std::make_unique<QPluginLoader>(fileName);
		if (qobject_cast<PluginInterface*>(plugin->instance()))
			plugins.emplace_back(std::move(plugin));
	}
	return plugins;
}

QPluginLoader* utils::getPlugin(decltype(std::cbegin(loadPlugins())) cbegin, decltype(std::cend(loadPlugins())) cend, const QString& pluginName)
{
	auto it = std::find_if(cbegin, cend, [&pluginName](const auto& p) -> bool { return getPluginName(*p) == pluginName; });

	return it != cend ? it->get() : nullptr;
}

PluginInterface* utils::getPluginInterface(QPluginLoader& loader)
{
	return qobject_cast<PluginInterface*>(loader.instance());
}

QString utils::getPluginName(QPluginLoader& loader)
{
	auto *tmp = qobject_cast<PluginInterface*>(loader.instance());
	return tmp ? tmp->name() : "";
}

QJsonObject utils::getPluginMetadata(const QPluginLoader& loader)
{
	const auto& md = loader.metaData()["MetaData"];

	return md.isObject() ? md.toObject() : QJsonObject();
}

QJsonObject utils::getPluginMetadataFull(const QPluginLoader& loader)
{
	return loader.metaData();
}
