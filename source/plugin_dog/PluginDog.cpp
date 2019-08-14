#include "PluginDog.hpp"

#include <utils.hpp>

#include "DogInterface.hpp"

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
		content += checkFriends(*plugin);
		content += checkEnnemies(*plugin);
	}

	return content;
}

QString PluginDog::checkFriends(QPluginLoader& plugin)
{
	QJsonValue json = utils::getPluginMetadata(plugin)["PluginDog_friend"];
	if (!json.isString())
		return "";

	QString classname = json.toString();
	int id = QMetaType::type(classname.toStdString().c_str());
	if (id == QMetaType::UnknownType)
		return "";

	auto* friendclass = static_cast<DogInterface*>(QMetaType::create(id));
	QString str = QString("I am a friend with '%1': '%2'\n").arg(utils::getPluginName(plugin), friendclass->cry());
	QMetaType::destroy(id, friendclass);

	return str;
}

QString PluginDog::checkEnnemies(QPluginLoader& plugin)
{
	QJsonValue json = utils::getPluginMetadata(plugin)["PluginDog_ennemies"];
	if (!json.isString())
		return "";

	QString classname = json.toString();
	int id = QMetaType::type(classname.toStdString().c_str());
	if (id == QMetaType::UnknownType)
		return "";

	auto* friendclass = static_cast<DogInterface*>(QMetaType::create(id));
	QString str = QString("I EAT '%1': '%2'\n").arg(utils::getPluginName(plugin), friendclass->cry());
	QMetaType::destroy(id, friendclass);

	return str;
}
