#ifndef DOGFRIEND_HPP
#define DOGFRIEND_HPP

#include <QMetaType>

#include "DogInterface.hpp"

class DogFriend : public DogInterface
{
public:
	virtual ~DogFriend() override = default;

	virtual QString cry() override;
};

Q_DECLARE_METATYPE(DogFriend)

#endif // DOGFRIEND_HPP
