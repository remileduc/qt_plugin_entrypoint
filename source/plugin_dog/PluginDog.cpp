#include "PluginDog.hpp"

#include <utils.hpp>

#include "DogFriendInterface.hpp"

PluginDog::PluginDog(QObject* parent) : QObject(parent)
{
}

const QString& PluginDog::name() const noexcept
{
	static QString _name = "PluginDog";
	return _name;
}

QString PluginDog::contents()
{
	return "I am a dog";
}
