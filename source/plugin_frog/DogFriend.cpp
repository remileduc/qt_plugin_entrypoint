#include "DogFriend.hpp"

#include <utils.hpp>

#include "CatInterface.hpp"

QString DogFriend::cry()
{
	// send info to the cat
	const auto plugins = utils::loadPlugins();
	for (const auto& plugin : plugins)
	{
		QJsonValue json = utils::getPluginMetadata(*plugin)["PluginCat_info"];
		if (!json.isString())
			return "";

		QString classname = json.toString();
		int id = QMetaType::type(classname.toStdString().c_str());
		if (id == QMetaType::UnknownType)
			return "";

		auto* infoclass = static_cast<CatInterface*>(QMetaType::create(id));
		infoclass->giveInfo(utils::getPluginInterface(*plugin), "I think I saw a dog in the area...");
		QMetaType::destroy(id, infoclass);
	}

	return "croak";
}
