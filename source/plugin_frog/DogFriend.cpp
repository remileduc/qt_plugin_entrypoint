#include "DogFriend.hpp"

#include <PluginManager.hpp>

QString DogFriend::cry()
{
	// send info to the cat
	const auto &cats = PluginManager::get().getEntryPoints("PluginCat_info");
	for (const auto &cat : cats)
	{
		std::unique_ptr<QObject> qobj(cat.meta->newInstance());
		if (!qobj)
			continue;

		QMetaObject::invokeMethod(qobj.get(), "giveInfo", Qt::DirectConnection, Q_ARG(QString, "I think I saw a dog in the area..."));
	}

	return "croak";
}
