#include "CatInfo.hpp"

#include "PluginCat.hpp"

void CatInfo::giveInfo(PluginInterface* plugin, const QString& info)
{
	auto* cat = dynamic_cast<PluginCat*>(plugin);
	if (cat)
		cat->setInfo(info);
}
