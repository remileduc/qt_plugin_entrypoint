#ifndef PLUGININTERFACE_HPP
#define PLUGININTERFACE_HPP

#include <QtPlugin>

/** String ID of the plugin */
#define PluginInterfaceIID "remileduc.qt_plugin_entrypoint.PluginInterface/v1.0"

/**
 * Plugin interface for this example program.
 */
class PluginInterface
{
public:
	virtual ~PluginInterface() = default;

	/** @return the name of the plugin */
	virtual const QString &name() const noexcept = 0;
	/** @return the contents of the plugin */
	virtual QString contents() = 0;
};

Q_DECLARE_INTERFACE(PluginInterface, PluginInterfaceIID)

/** Structure representing an entry point.
 *
 * An entry point is an object that is registered on a specific key (@see PluginManager::registerEntryPoint())
 * and implements some specific functions that can be used by other plugins.
 */
struct EntryPoint
{
	/** The meta object that is linked to the class that can be used by other plugins. */
	const QMetaObject *meta;
	/** Plugin owner of the entry point. */
	PluginInterface *plugin;
};

#endif // PLUGININTERFACE_HPP
