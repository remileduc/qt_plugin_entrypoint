#ifndef DOGFRIEND_HPP
#define DOGFRIEND_HPP

#include <QMetaType>

#include "DogFriendInterface.hpp"

class DogFriend : public DogFriendInterface
{
public:
	virtual ~DogFriend() override = default;

	virtual QString cry() override;
};

Q_DECLARE_METATYPE(DogFriend)

#endif // DOGFRIEND_HPP
