#ifndef CATINFO_HPP
#define CATINFO_HPP

#include <QMetaType>

#include "CatInterface.hpp"

class CatInfo : public CatInterface
{
public:
	virtual ~CatInfo() override = default;

	virtual void giveInfo(PluginInterface* plugin, const QString& info) override;
};

Q_DECLARE_METATYPE(CatInfo)

#endif // CATINFO_HPP
