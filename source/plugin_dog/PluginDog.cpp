#include "PluginDog.hpp"

#include <utils.hpp>

#include "DogFriendInterface.hpp"

PluginDog::PluginDog(QObject* parent) : QObject(parent)
{
}

const QString& PluginDog::name() const noexcept
{
	static QString _name = "PluginDog";
	return _name;
}

QString PluginDog::contents()
{
	QString content = "I am a dog!\n\n";

	// check if there are some friends
	const auto plugins = utils::loadPlugins();
	for (const auto& plugin : plugins)
	{
		if (plugin->instance() == this)
			continue;

		QJsonValue json = utils::getPluginMetadata(*plugin)["PluginDog_friend"];
		if (!json.isString())
			continue;

		QString classname = json.toString();
		int id = QMetaType::type(classname.toStdString().c_str());
		if (id == QMetaType::UnknownType)
			continue;

		auto* friendclass = static_cast<DogFriendInterface*>(QMetaType::create(id));
		content += QString("I am a friend with '%1': %2\n").arg(utils::getPluginName(*plugin), friendclass->cry());
		QMetaType::destroy(id, friendclass);
	}

	return content;
}
