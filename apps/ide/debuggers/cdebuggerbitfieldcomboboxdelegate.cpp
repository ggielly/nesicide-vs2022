#include "cdebuggerbitfieldcomboboxdelegate.h"

CDebuggerBitfieldComboBoxDelegate::CDebuggerBitfieldComboBoxDelegate(): m_p_bitfield_(nullptr){}

QWidget* CDebuggerBitfieldComboBoxDelegate::createEditor(QWidget* parent,
                                                         const QStyleOptionViewItem& /* option */,
                                                         const QModelIndex& /* index */) const
{
	if (m_p_bitfield_)
	{
		if (m_p_bitfield_->GetNumValues())
		{
			const auto editor = new QComboBox(parent);

			for (int idx = 0; idx < m_p_bitfield_->GetNumValues(); idx++)
			{
				char data[64];
				sprintf(data, "%s", m_p_bitfield_->GetValueByIndex(idx));
				editor->addItem(data, QVariant(idx));
			}

			editor->setEditable(false);
			return editor;
		}
		else
		{
			const auto editor = new QLineEdit(parent);
			return editor;
		}
	}
	else
	{
		const auto editor = new QLineEdit(parent);
		return editor;
	}
}

void CDebuggerBitfieldComboBoxDelegate::setEditorData(QWidget* editor,
                                                      const QModelIndex& index) const
{
	// get register value from model...
	bool ok;
	int value;
	char data[8];

	// reduce to the bits we care about...
	if (m_p_bitfield_)
	{
		value = m_p_bitfield_->GetValueRaw(index.model()->data(index, Qt::EditRole).toString().toInt(&ok, 16));

		if (m_p_bitfield_->GetNumValues())
		{
			const auto comboBox = dynamic_cast<QComboBox*>(editor);
			comboBox->setCurrentIndex(value);
			comboBox->showPopup();
		}
		else
		{
			const auto edit = dynamic_cast<QLineEdit*>(editor);

			sprintf(data, m_p_bitfield_->GetDisplayFormat(), value);

			edit->setText(data);
		}
	}
	else
	{
		const auto edit = dynamic_cast<QLineEdit*>(editor);
		edit->setText(index.model()->data(index, Qt::DisplayRole).toString());
	}
}

void CDebuggerBitfieldComboBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                                     const QModelIndex& index) const
{
	// get register value from model...
	bool ok;
	int value;
	char data[8];

	if (m_p_bitfield_)
	{
		if (m_p_bitfield_->GetNumValues())
		{
			const auto combo_box = dynamic_cast<QComboBox*>(editor);

			int bitfieldValue = combo_box->currentIndex();

			value = m_p_bitfield_->InsertValue(index.model()->data(index, Qt::EditRole).toString().toInt(&ok, 16),
			                                 bitfieldValue);

			sprintf(data, m_p_bitfield_->GetDisplayFormat(), value);

			model->setData(index, data, Qt::EditRole);
		}
		else
		{
			const auto edit = dynamic_cast<QLineEdit*>(editor);

			value = m_p_bitfield_->InsertValue(index.model()->data(index, Qt::EditRole).toString().toInt(&ok, 16),
			                                 edit->text().toInt(&ok, 16));

			sprintf(data, m_p_bitfield_->GetDisplayFormat(), value);

			model->setData(index, data, Qt::EditRole);
		}
	}
}

void CDebuggerBitfieldComboBoxDelegate::updateEditorGeometry(QWidget* editor,
                                                             const QStyleOptionViewItem& option,
                                                             const QModelIndex& /* index */) const
{
	editor->setGeometry(option.rect);
}
