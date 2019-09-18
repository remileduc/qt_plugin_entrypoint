#ifndef DOGENEMY_HPP
#define DOGENEMY_HPP

#include <QObject>

/**
 * Entry point for "PluginDog_enemies" key.
 *
 * This class tells the dog that cats are enemies.
 *
 * It is expected that dogs will call the method cry().
 */
class DogEnemy : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE DogEnemy(QObject *parent = nullptr);

	/** @return the cry of the cat: "meow". */
	Q_INVOKABLE QString cry();
};

#endif // DOGENEMY_HPP
