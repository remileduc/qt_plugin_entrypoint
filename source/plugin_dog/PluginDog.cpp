#include "PluginDog.hpp"

#include <memory>

#include <QMetaMethod>

#include <PluginManager.hpp>

PluginDog::PluginDog(QObject *parent) : QObject(parent)
{
}

const QString &PluginDog::name() const noexcept
{
	static QString _name = "PluginDog";
	return _name;
}

QString PluginDog::contents()
{
	QString content = "I am a dog!\n\n";

	// check if there are some friends
	content += checkFriends();
	content += checkEnemies();

	return content;
}

QString PluginDog::checkFriends() const
{
	const auto &friends = PluginManager::get().getEntryPoints("PluginDog_friends");

	QString str;
	for (const auto &friendep : friends)
	{
		std::unique_ptr<QObject> qobj(friendep.meta->newInstance());
		if (!qobj)
			continue;

		QString cry;
		bool callok = QMetaObject::invokeMethod(qobj.get(), "cry", Qt::DirectConnection, Q_RETURN_ARG(QString, cry));
		if (callok)
			str += QString("I am a friend with '%1': '%2'\n").arg(friendep.plugin->name(), cry);
	}

	return str;
}

QString PluginDog::checkEnemies() const
{
	const auto &friends = PluginManager::get().getEntryPoints("PluginDog_enemies");

	QString str;
	for (const auto &friendep : friends)
	{
		std::unique_ptr<QObject> qobj(friendep.meta->newInstance());
		if (!qobj)
			continue;

		QString cry;
		bool callok = QMetaObject::invokeMethod(qobj.get(), "cry", Qt::DirectConnection, Q_RETURN_ARG(QString, cry));
		if (callok)
			str += QString("I EAT '%1': '%2'\n").arg(friendep.plugin->name(), cry);
	}

	return str;
}
