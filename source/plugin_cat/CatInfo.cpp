#include "CatInfo.hpp"

#include <algorithm>

#include <PluginManager.hpp>

#include "PluginCat.hpp"

void CatInfo::giveInfo(const QString &info)
{
	auto *cat = dynamic_cast<PluginCat *>(PluginManager::get().getPlugin(PluginCat::_name));
	if (cat)
		cat->setInfo(info);
}
