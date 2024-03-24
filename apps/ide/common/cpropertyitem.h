#ifndef CPROPERTYITEM_H
#define CPROPERTYITEM_H

#include <QString>

using propertyTypeEnum = enum
{
	propertyInteger,
	propertyBoolean,
	propertyString,
	propertyEnumeration
};

struct PropertyItem
{
	QString name;
	propertyTypeEnum type;
	QString value;
};

struct PropertyEnumItem
{
	bool isSelected;
	QString symbol;
	QString value;
};

QString getEnumRawString(QList<PropertyEnumItem> items);
QString getEnumValueString(QString itemsStr);
QList<PropertyEnumItem> getEnumItems(QString itemsStr);

#endif // CPROPERTYITEM_H
