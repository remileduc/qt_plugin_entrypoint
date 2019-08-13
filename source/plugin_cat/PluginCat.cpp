#include "PluginCat.hpp"

PluginCat::PluginCat(QObject* parent) : QObject(parent)
{
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
