#include "cdebuggerbitfielddisplaymodel.h"
#include <cstdio> // needed for sprintf_s

CDebuggerBitfieldDisplayModel::CDebuggerBitfieldDisplayModel(const regDBFunc reg_db, QObject*)
{
	m_regDB = reg_db;
	m_register = 0;
	m_modelStringBuffer = new char[512];
}

CDebuggerBitfieldDisplayModel::~CDebuggerBitfieldDisplayModel()
{
	delete [] m_modelStringBuffer;
}

QVariant CDebuggerBitfieldDisplayModel::data(const QModelIndex& index, const int role) const
{
	char* p_values = m_modelStringBuffer;

	if (!index.isValid())
	{
		return {};
	}

	auto pRegister = static_cast<CRegisterData*>(index.internalPointer());
	CBitfieldData* pBitfield = pRegister->GetBitfield(index.row());
	uint32_t reg_data = pRegister->Get();

/*	if (role == Qt::ToolTipRole)
	{
		if (pBitfield->GetNumValues())
		{
			p_values += sprintf(p_values, "<pre>");

			for (int value = 0; value < pBitfield->GetNumValues(); value++)
			{
				if (value == pBitfield->GetValueRaw(reg_data))
				{
					p_values += sprintf(p_values, "<b>%s</b>", pBitfield->GetValueByIndex(value));
				}
				else
				{
					p_values += sprintf(p_values, "%s", pBitfield->GetValueByIndex(value));
				}

				if (value < pBitfield->GetNumValues() - 1)
				{
					p_values += sprintf(p_values, "\n");
				}
			}

			p_values += sprintf(p_values, "</pre>");
			return {m_modelStringBuffer};
		}
	}

	sprintf correction 
	*/

	if (role == Qt::ToolTipRole)
	{
		if (pBitfield->GetNumValues())
		{
			p_values += sprintf_s(p_values, sizeof(m_modelStringBuffer) - (p_values - m_modelStringBuffer), "<pre>");

			for (int value = 0; value < pBitfield->GetNumValues(); value++)
			{
				if (value == pBitfield->GetValueRaw(reg_data))
				{
					p_values += sprintf_s(p_values, sizeof(m_modelStringBuffer) - (p_values - m_modelStringBuffer), "<b>%s</b>", pBitfield->GetValueByIndex(value));
				}
				else
				{
					p_values += sprintf_s(p_values, sizeof(m_modelStringBuffer) - (p_values - m_modelStringBuffer), "%s", pBitfield->GetValueByIndex(value));
				}

				if (value < pBitfield->GetNumValues() - 1)
				{
					p_values += sprintf_s(p_values, sizeof(m_modelStringBuffer) - (p_values - m_modelStringBuffer), "\n");
				}
			}

			p_values += sprintf_s(p_values, sizeof(m_modelStringBuffer) - (p_values - m_modelStringBuffer), "</pre>");
			return { m_modelStringBuffer };
		}
	}



	if (role == Qt::DisplayRole)
	{
		if (pBitfield->GetNumValues())
		{
			sprintf(m_modelStringBuffer, "%s", pBitfield->GetValue(reg_data));
		}
		else
		{
			sprintf(m_modelStringBuffer, pBitfield->GetDisplayFormat(), pBitfield->GetValueRaw(reg_data));
		}

		return {m_modelStringBuffer};
	}
	else if (role == Qt::EditRole)
	{
		sprintf(m_modelStringBuffer, pBitfield->GetDisplayFormat(), reg_data);
		return {m_modelStringBuffer};
	}

	return {};
}

Qt::ItemFlags CDebuggerBitfieldDisplayModel::flags(const QModelIndex&) const
{
	Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	return flags;
}

QVariant CDebuggerBitfieldDisplayModel::headerData(const int section, const Qt::Orientation orientation, const int role) const
{
	if (role != Qt::DisplayRole)
	{
		return {};
	}

	if (orientation == Qt::Horizontal)
	{
		sprintf(m_modelStringBuffer, "Value");
	}
	else
	{
		if (m_regDB())
		{
			CBitfieldData* pBitfield = m_regDB()->GetRegister(m_register)->GetBitfield(section);

			if (pBitfield->GetWidth() == 1)
			{
				sprintf(m_modelStringBuffer, "[%d] %s", pBitfield->GetLsb(), pBitfield->GetName());
			}
			else
			{
				sprintf(m_modelStringBuffer, "[%d:%d] %s", pBitfield->GetMsb(), pBitfield->GetLsb(),
				        pBitfield->GetName());
			}
		}
	}

	return {m_modelStringBuffer};
}

bool CDebuggerBitfieldDisplayModel::setData(const QModelIndex& index, const QVariant& value, int)
{
	int data;
	bool ok = false;

	if (m_regDB())
	{
		data = value.toString().toInt(&ok, 16);

		if (ok)
		{
			m_regDB()->GetRegister(m_register)->Set(data);
			emit dataChanged(index, index);
		}
	}

	return ok;
}

QModelIndex CDebuggerBitfieldDisplayModel::index(const int row, const int column, const QModelIndex&) const
{
	if ((row >= 0) && (column >= 0))
	{
		if (m_regDB())
		{
			return createIndex(row, column, m_regDB()->GetRegister(m_register));
		}
	}

	return {};
}

int CDebuggerBitfieldDisplayModel::rowCount(const QModelIndex&) const
{
	if (m_regDB())
	{
		return m_regDB()->GetRegister(m_register)->GetNumBitfields();
	}

	// Nothing to display here...
	return 0;
}

int CDebuggerBitfieldDisplayModel::columnCount(const QModelIndex&) const
{
	if (m_regDB())
	{
		return 1;
	}

	// Nothing to display here...
	return 0;
}

void CDebuggerBitfieldDisplayModel::update()
{
	emit layoutChanged();
}
