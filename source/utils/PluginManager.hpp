#ifndef PLUGINMANAGER_HPP
#define PLUGINMANAGER_HPP

#include <memory>
#include <vector>

#include <QHash>
#include <QList>
#include <QPluginLoader>
#include <QtGlobal>

#include "PluginInterface.hpp"

#if defined(utils_EXPORT)
#	define UTILS_SHARED_EXPORT Q_DECL_EXPORT
#elif defined(utils_IMPORT)
#	define UTILS_SHARED_EXPORT Q_DECL_IMPORT
#endif

#ifndef UTILS_SHARED_EXPORT
#	define UTILS_SHARED_EXPORT
#endif

/**
 * Singletong that manages the plugins.
 *
 * This class is a singleton, you can access it through its get() method.
 *
 * PluginManager can load the plugins that are in the same folder as the executable thanks to
 * the method loadPlugins(). You can then access to the plugins with getPlugins(), or to a specific
 * by providing its name to getPlugin().
 *
 * PluginLManager also takes care of the EntryPoint. Entry points are grouped by their names.
 */
class UTILS_SHARED_EXPORT PluginManager
{
public:
	/** @return the singleton instance of this class. */
	static PluginManager &get();

	PluginManager(const PluginManager &) = delete; // can't copy
	PluginManager(const PluginManager &&) = delete; // or move
	PluginManager &operator=(const PluginManager &) = delete;
	PluginManager &operator=(const PluginManager &&) = delete;

	/**
	 * Loads the plugins.
	 *
	 * Loads all the shared library files that can be used as a plugin in this application.
	 * The files must be in the same folder as the executable.
	 */
	void loadPlugins();
	/** @return the plugin with the given name. */
	PluginInterface *getPlugin(const QString &name);
	/** @return all the loaded plugins. */
	std::vector<PluginInterface *> getPlugins();

	/**
	 * Register a new entry point.
	 *
	 * It is possible to register multiple class to the same entry point name. Though,
	 * you shouldn't register multiple time the same class...
	 *
	 * @param entryname the name of the entry point we want to register on
	 * @param entrypoint the new class associated with this entry point.
	 */
	void registerEntryPoint(QString entryname, EntryPoint entrypoint);
	/** @return all the classes registered on the given entry point. */
	QList<EntryPoint> getEntryPoints(const QString &entryname) const;
	/** @return all the entry point names. */
	QList<QString> getEntryNames() const;

private:
	/** Private constructor because of singleton. */
	PluginManager() {}

private:
	/** Store all the plugins with their name as a key. */
	QHash<QString, std::shared_ptr<QPluginLoader>> _plugins;
	/** Store all the entry points (multimap: entry point name as a key, and then classes associated to this name). */
	QHash<QString, EntryPoint> _entrypoints;
};

#endif // PLUGINMANAGER_HPP
