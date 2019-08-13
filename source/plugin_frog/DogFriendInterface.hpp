#ifndef DOGFRIENDINTERFACE_HPP
#define DOGFRIENDINTERFACE_HPP

#include <QString>

/**
 * Interface for friends of dogs.
 *
 * A friend of dogs need to say his cry.
 *
 * In order to be able to be friend with a dog, also need to add then entry
 * `PluginDog_friend` associated to the name of the class implementing this
 * interface.
 *
 * Finally, you need to expose the class with `Q_DECLARE_METATYPE`.
 */
class DogFriendInterface
{
public:
	virtual ~DogFriendInterface() = default;

	virtual QString cry()  = 0;
};

#endif // DOGFRIENDINTERFACE_HPP
