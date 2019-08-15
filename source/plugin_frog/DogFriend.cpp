#include "DogFriend.hpp"

#include <utils.hpp>

#include "CatInterface.hpp"
#include "PluginFrog.hpp"

QString DogFriend::cry()
{
	// send info to the cat
	const auto plugins = utils::loadPlugins();
	for (const auto& plugin : plugins)
	{
		if (utils::getPluginName(*plugin) == PluginFrog::_name)
			continue;

		QJsonValue json = utils::getPluginMetadata(*plugin)["PluginCat_info"];
		if (!json.isString())
			return "";

		int id = QMetaType::type(json.toString().toStdString().c_str());
		if (id == QMetaType::UnknownType)
			return "";

		auto* infoclass = static_cast<CatInterface*>(QMetaType::create(id));
		infoclass->giveInfo(utils::getPluginInterface(*plugin), "I think I saw a dog in the area...");
		QMetaType::destroy(id, infoclass);
	}

	return "croak";
}
