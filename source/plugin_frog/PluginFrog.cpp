#include "PluginFrog.hpp"

#include <PluginManager.hpp>

#include "DogFriend.hpp"

PluginFrog::PluginFrog(QObject *parent) : QObject(parent)
{
	// we NEED to register to make the QMetaObject available...
	PluginManager::get().registerEntryPoint("PluginDog_friends", {&DogFriend::staticMetaObject, this});
}

const QString &PluginFrog::name() const noexcept
{
	return PluginFrog::_name;
}

QString PluginFrog::contents()
{
	return "I am a frog!";
}
