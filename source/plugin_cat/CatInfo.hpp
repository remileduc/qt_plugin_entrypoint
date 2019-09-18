#ifndef CATINFO_HPP
#define CATINFO_HPP

#include <QObject>

/**
 * Entry point for "PluginCat_info" key.
 *
 * This class can be used to provide information to the cat.
 */
class CatInfo : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE CatInfo(QObject *parent = nullptr) : QObject(parent) {}

	/**
	 * Store information in PluginCat.
	 *
	 * @param info the information to store.
	 */
	Q_INVOKABLE void giveInfo(const QString &info);
};

#endif // CATINFO_HPP
