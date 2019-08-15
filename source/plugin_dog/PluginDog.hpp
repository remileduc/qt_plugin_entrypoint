#ifndef PLUGINDOG_HPP
#define PLUGINDOG_HPP

#include <PluginInterface.hpp>

class QPluginLoader;

/**
 * Plugin representing a dog.
 *
 * A dog simple wants to say that it is a dog. If he founds any other animals he can eat,
 * he will list them.
 *
 * A dog is friend with frogs.
 */
class PluginDog : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID PluginInterfaceIID FILE "PluginDog.json")
	Q_INTERFACES(PluginInterface)

public:
	PluginDog(QObject* parent = nullptr);
	virtual ~PluginDog() override = default;

	virtual const QString& name() const noexcept override;
	virtual QString contents() override;

private:
	QString checkFriends(QPluginLoader& plugin) const;
	QString checkEnnemies(QPluginLoader& plugin) const;
};

#endif // PLUGINDOG_HPP
