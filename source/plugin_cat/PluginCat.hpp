#ifndef PLUGINCAT_HPP
#define PLUGINCAT_HPP

#include <PluginInterface.hpp>

/**
 * Plugin representing a cat.
 *
 * A cat simple wants to say that it is a cat. 
 *
 * A cat can be eaten by a dog.
 *
 * A cat is not friend with anyone.
 */
class PluginCat : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID PluginInterfaceIID FILE "PluginCat.json")
	Q_INTERFACES(PluginInterface)

public:
	PluginCat(QObject* parent = nullptr);
	virtual ~PluginCat() override = default;

	virtual const QString& name() const noexcept override;
	virtual QString contents() override;
};

#endif // PLUGINCAT_HPP
