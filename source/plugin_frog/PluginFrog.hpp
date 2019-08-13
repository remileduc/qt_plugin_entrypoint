#ifndef PLUGINFROG_HPP
#define PLUGINFROG_HPP

#include <PluginInterface.hpp>

/**
 * Plugin representing a frog.
 *
 * A frog simple wants to say that it is a frog.
 *
 * A frog can be eaten by cats, but is friend with dogs.
 */
class PluginFrog : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID PluginInterfaceIID FILE "PluginFrog.json")
	Q_INTERFACES(PluginInterface)

public:
	PluginFrog(QObject* parent = nullptr);
	virtual ~PluginFrog() override = default;

	virtual const QString& name() const noexcept override;
	virtual QString contents() override;
};

#endif // PLUGINFROG_HPP
