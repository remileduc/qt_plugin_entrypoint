#ifndef DOGENNEMY_HPP
#define DOGENNEMY_HPP

#include <QMetaType>

#include "DogInterface.hpp"

class DogEnnemy : public DogInterface
{
public:
	virtual ~DogEnnemy() override = default;

	virtual QString cry() override;
};

Q_DECLARE_METATYPE(DogEnnemy)

#endif // DOGENNEMY_HPP
