#ifndef CATINTERFACE_HPP
#define CATINTERFACE_HPP

#include <QString>

#include <PluginInterface.hpp>

/**
 * Interface to give informations to the cat.
 *
 * If you give info to the cat, it will display it after (cats can't keep a secret).
 *
 * To give info to a cat, you need to look for the key `PluginCat_info` in the metadata.
 */
class CatInterface
{
public:
	virtual ~CatInterface() = default;

	/**
	 * Give info to the cat.
	 * You need to provide the plugin that must be castable to PluginCat.
	 * Otherwise, the info will be lost.
	 */
	virtual void giveInfo(PluginInterface* plugin, const QString& info) = 0;
};

#endif // CATINTERFACE_HPP
