#ifndef DOGINTERFACE_HPP
#define DOGINTERFACE_HPP

#include <QString>

/**
 * Interface for friends or ennemies of dogs.
 *
 * A friends and ennemies of dogs need to say his cry.
 *
 * In order to be able to be friend with a dog, also need to add then entry
 * `PluginDog_friend` for friends, and `PluginDog_ennemies` for ennemies,
 * associated to the name of the class implementing this interface.
 *
 * Finally, you need to expose the class with `Q_DECLARE_METATYPE`.
 */
class DogInterface
{
public:
	virtual ~DogInterface() = default;

	/** @return the cry of the animal */
	virtual QString cry() = 0;
};

#endif // DOGINTERFACE_HPP
