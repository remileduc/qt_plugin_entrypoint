#include "DogEnemy.hpp"

DogEnemy::DogEnemy(QObject *parent) : QObject(parent)
{
}

QString DogEnemy::cry()
{
	return "meow";
}
