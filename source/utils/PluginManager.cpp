#include "PluginManager.hpp"

#include <QCoreApplication>
#include <QDir>

PluginManager &PluginManager::get()
{
	static PluginManager _pm;
	return _pm;
}

void PluginManager::loadPlugins()
{
	QDir pluginsDir(QCoreApplication::instance()->applicationDirPath());
	const auto entryList = pluginsDir.entryList(QDir::Files);

	for (const auto &fileName : entryList)
	{
		auto plugin = std::make_shared<QPluginLoader>(fileName);
		auto *pinterface = qobject_cast<PluginInterface *>(plugin->instance());
		if (pinterface && !_plugins.contains(pinterface->name()))
			_plugins.insert(pinterface->name(), plugin); // only reason why we use shared_ptr is because we can't emplace in QHash so we need copy...
		else
			plugin->unload();
	}
}

PluginInterface *PluginManager::getPlugin(const QString &name)
{
	return _plugins.contains(name) ? qobject_cast<PluginInterface *>(_plugins[name]->instance()) : nullptr;
}

std::vector<PluginInterface *> PluginManager::getPlugins()
{
	std::vector<PluginInterface *> plugs;
	plugs.reserve(_plugins.size());

	PluginInterface *pinterface = nullptr;
	for (auto &plugin : _plugins)
	{
		pinterface = qobject_cast<PluginInterface *>(plugin->instance());
		if (pinterface)
			plugs.push_back(pinterface);
	}
	return plugs;
}

void PluginManager::registerEntryPoint(QString entryname, EntryPoint entrypoint)
{
	_entrypoints.insertMulti(std::move(entryname), std::move(entrypoint));
}

QList<EntryPoint> PluginManager::getEntryPoints(const QString &entryname) const
{
	return _entrypoints.values(entryname);
}

QList<QString> PluginManager::getEntryNames() const
{
	return _entrypoints.keys();
}
