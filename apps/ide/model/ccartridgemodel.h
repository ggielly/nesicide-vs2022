#ifndef CCARTRIDGEMODEL_H
#define CCARTRIDGEMODEL_H

#include "model/csubmodel.h"

class CCartridgeModel : public CSubModel
{
public:
	CCartridgeModel();

	QList<QUuid> getPrgRomUuids() const;
	QList<QUuid> getChrRomUuids() const;

	QList<QUuid> getUuids() const override;
	QString getName(const QUuid& uuid) const override;

	CDesignerEditorBase* createEditorWidget(const QUuid&) const override;
};

#endif // CCARTRIDGEMODEL_H
