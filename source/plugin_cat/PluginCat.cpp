#include "PluginCat.hpp"

#include "CatInfo.hpp"
#include "DogEnnemy.hpp"

PluginCat::PluginCat(QObject* parent) : QObject(parent)
{
	// we NEED to register to make QMetaType work correctly...
	qRegisterMetaType<CatInfo>();
	qRegisterMetaType<DogEnnemy>();
}

const QString& PluginCat::name() const noexcept
{
	static QString _name = "PluginCat";
	return _name;
}

QString PluginCat::contents()
{
	return "I am a cat!\n\n" + _info;
}

void PluginCat::setInfo(QString info) noexcept
{
	_info = info;
}
