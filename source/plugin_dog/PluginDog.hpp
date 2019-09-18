#ifndef PLUGINDOG_HPP
#define PLUGINDOG_HPP

#include <PluginInterface.hpp>

/**
 * Plugin representing a dog.
 *
 * A dog simple wants to say that it is a dog. The dogs seek for enemies (they eat them) and friends.
 *
 * In order to be friend or enemy of a dog, you need to provide a class on one of these entry points:
 * - "PluginDog_friends"
 * - "PluginDog_enemies"
 *
 * The exposed class should have a function with the following signature:
 * `QString cry()`.
 */
class PluginDog : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID PluginInterfaceIID)
	Q_INTERFACES(PluginInterface)

public:
	PluginDog(QObject *parent = nullptr);
	virtual ~PluginDog() override = default;

	virtual const QString &name() const noexcept override;
	virtual QString contents() override;

private:
	/** @return the friends and their cry. */
	QString checkFriends() const;
	/** @return the enemies. */
	QString checkEnemies() const;
};

#endif // PLUGINDOG_HPP
