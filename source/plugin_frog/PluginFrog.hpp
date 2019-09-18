#ifndef PLUGINFROG_HPP
#define PLUGINFROG_HPP

#include <PluginInterface.hpp>

/**
 * Plugin representing a frog.
 *
 * A frog simple wants to say that it is a frog.
 *
 * A frog is friend with dogs: it exposes DogFriend on "PluginDog_friends" entry point.
 * A frog also likes cats, so it will warn them if it sees a dog: it uses the entry point "PluginCat_info".
 */
class PluginFrog : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID PluginInterfaceIID)
	Q_INTERFACES(PluginInterface)

public:
	PluginFrog(QObject *parent = nullptr);
	virtual ~PluginFrog() override = default;

	virtual const QString &name() const noexcept override;
	virtual QString contents() override;

	// not exposed
	inline static const QString _name = "PluginFrog";
};

#endif // PLUGINFROG_HPP
