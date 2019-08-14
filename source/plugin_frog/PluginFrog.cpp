#include "PluginFrog.hpp"

#include <QVariant>
#include "DogFriend.hpp"

PluginFrog::PluginFrog(QObject* parent) : QObject(parent)
{
	// we NEED to initialize a QVariant to make QMetaType work correctly...
	QVariant::fromValue(DogFriend());
}

const QString& PluginFrog::name() const noexcept
{
	static QString _name = "PluginFrog";
	return _name;
}

QString PluginFrog::contents()
{
	return "I am a frog!";
}
