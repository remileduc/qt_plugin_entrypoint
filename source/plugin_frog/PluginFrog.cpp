#include "PluginFrog.hpp"

PluginFrog::PluginFrog(QObject* parent) : QObject(parent)
{
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
