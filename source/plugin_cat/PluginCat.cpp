#include "PluginCat.hpp"

#include <QVariant>
#include "DogEnnemy.hpp"

PluginCat::PluginCat(QObject* parent) : QObject(parent)
{
	// we NEED to initialize a QVariant to make QMetaType work correctly...
	QVariant::fromValue(DogEnnemy());
}

const QString& PluginCat::name() const noexcept
{
	static QString _name = "PluginCat";
	return _name;
}

QString PluginCat::contents()
{
	return "I am a cat!";
}
