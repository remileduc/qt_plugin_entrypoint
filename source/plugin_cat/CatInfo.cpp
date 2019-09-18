#include "CatInfo.hpp"

#include <algorithm>

#include <PluginManager.hpp>

#include "PluginCat.hpp"

void CatInfo::giveInfo(const QString &info)
{
	// first, retrieve the plugin
	const auto &cats = PluginManager::get().getEntryPoints("PluginCat_info");
	auto it = std::find_if(std::cbegin(cats), std::cend(cats), [](const auto &ep) { return ep.meta == &CatInfo::staticMetaObject; });
	if (it == std::cend(cats))
		return;
	// then we store the info
	auto *cat = dynamic_cast<PluginCat *>(it->plugin);
	if (cat)
		cat->setInfo(info);
}
