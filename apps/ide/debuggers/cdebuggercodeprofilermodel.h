#ifndef CDEBUGGERCODEPROFILERMODEL_H
#define CDEBUGGERCODEPROFILERMODEL_H

#include <QAbstractTableModel>
#include <QList>

enum
{
	CodeProfilerCol_Symbol = 0,
	CodeProfilerCol_Address,
	CodeProfilerCol_Size,
	CodeProfilerCol_Calls,
	CodeProfilerCol_File,
	CodeProfilerCol_MAX
};

struct ProfiledItem
{
	QString file;
	QString symbol;
	QString address;
	unsigned int size;
	unsigned int count;

	bool operator==(const ProfiledItem& rI)
	{
		if ((rI.file == file) &&
			(rI.symbol == symbol) &&
			(rI.address == address) &&
			(rI.size == size))
		{
			return true;
		}
		return false;
	}
};

class CDebuggerCodeProfilerModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit CDebuggerCodeProfilerModel(QObject* parent = 0);
	~CDebuggerCodeProfilerModel() override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	QList<ProfiledItem> getItems() { return m_items; }
	void clear() { m_items.clear(); }

signals:

public slots:
	void update();
	void sort(int column, Qt::SortOrder order) override;

private:
	QList<ProfiledItem> m_items;
	int m_currentSortColumn;
	Qt::SortOrder m_currentSortOrder;
	int m_currentItemCount;
	char* m_modelStringBuffer;
};

#endif // CDEBUGGERCODEPROFILERMODEL_H
