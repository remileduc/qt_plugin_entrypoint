#include "PluginCat.hpp"

#include <PluginManager.hpp>

#include "CatInfo.hpp"
#include "DogEnemy.hpp"

PluginCat::PluginCat(QObject *parent) : QObject(parent)
{
	// we NEED to register to make the QMetaObject available...
	auto &pmanager = PluginManager::get();
	pmanager.registerEntryPoint("PluginDog_enemies", {&DogEnemy::staticMetaObject, this});
	pmanager.registerEntryPoint("PluginCat_info", {&CatInfo::staticMetaObject, this});
}

const QString &PluginCat::name() const noexcept
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
