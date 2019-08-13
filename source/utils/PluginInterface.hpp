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
	virtual const QString& name() const noexcept = 0;
	/** @return the contents of the plugin */
	virtual QString contents() = 0;
};

Q_DECLARE_INTERFACE(PluginInterface, PluginInterfaceIID)

#endif // PLUGININTERFACE_HPP
