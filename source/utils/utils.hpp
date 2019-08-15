#ifndef UTILS_HPP
#define UTILS_HPP

#include <memory>
#include <vector>

#include <QJsonObject>
#include <QPluginLoader>

class PluginInterface;

namespace utils
{
	/**
	 * Load all the plugins.
	 *
	 * Note that a QPLuginLoader is not copyable and not moveable,
	 * this is why we need to return pointers.
	 *
	 * @return the list of the loaded plugins.
	 */
	std::vector<std::unique_ptr<QPluginLoader>> loadPlugins();

	/** @return the plugin that has the given name, from the given list. If it doesn't exist, return `nullptr` */
	QPluginLoader* getPlugin(decltype(std::cbegin(loadPlugins())) cbegin, decltype(std::cend(loadPlugins())) cend, const QString& pluginName);

	/** @return the PluginInterface associated with the given plugin */
	PluginInterface* getPluginInterface(QPluginLoader& loader);

	/** @return the PluginInterface name */
	QString getPluginName(QPluginLoader& loader);

	/** @return the user metadata (content of the JSON file) for the given plugin */
	QJsonObject getPluginMetadata(const QPluginLoader& loader);

	/** @return the full metadata of the given plugin */
	QJsonObject getPluginMetadataFull(const QPluginLoader& loader);
}

#endif // UTILS_HPP
