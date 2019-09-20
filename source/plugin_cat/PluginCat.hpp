#ifndef PLUGINCAT_HPP
#define PLUGINCAT_HPP

#include <PluginInterface.hpp>

/**
 * Plugin representing a cat.
 *
 * A cat simple wants to say that it is a cat.
 *
 * A cat can be eaten by a dog: it exposes DogEnemy on "PluginDog_enemies".
 *
 * A cat is not friend with anyone. Though, others can provide it some information:
 * it exposes CatInfo on "PluginCat_info" entry point. CatInfo has one method with the
 * following signature: `void giveInfo(const QString& info)`.
 */
class PluginCat : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID PluginInterfaceIID)
	Q_INTERFACES(PluginInterface)

public:
	PluginCat(QObject *parent = nullptr);
	virtual ~PluginCat() override = default;

	virtual const QString &name() const noexcept override;
	virtual QString contents() override;

	// not exposed
	void setInfo(QString info) noexcept;

public:
	inline static const QString _name = "PluginCat";

private:
	QString _info;
};

#endif // PLUGINCAT_HPP
