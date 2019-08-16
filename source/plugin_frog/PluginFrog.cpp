#include "PluginFrog.hpp"

#include "DogFriend.hpp"

PluginFrog::PluginFrog(QObject* parent) : QObject(parent)
{
	// we NEED to register to make QMetaType work correctly...
	qRegisterMetaType<DogFriend>();
}

const QString& PluginFrog::name() const noexcept
{
	return PluginFrog::_name;
}

QString PluginFrog::contents()
{
	return "I am a frog!";
}
