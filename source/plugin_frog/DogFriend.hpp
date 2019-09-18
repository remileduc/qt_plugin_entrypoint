#ifndef DOGFRIEND_HPP
#define DOGFRIEND_HPP

#include <QObject>

/**
 * Entry point for "PluginDog_friends" key.
 *
 * This class tells the dog that frogs are friends.
 *
 * It is expected that dogs will call the method cry(). This is why, in this method,
 * the frog will try to warn the cat that there is a dog.
 */
class DogFriend : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE DogFriend(QObject *parent = nullptr) : QObject(parent) {}

	/**
	 * @return the cry of the frog: "croak".
	 *
	 * It will also try to warn the cat that there is a dog.
	 */
	Q_INVOKABLE QString cry();
};

#endif // DOGFRIEND_HPP
