#ifndef CSYMBOLWATCHMODEL_H
#define CSYMBOLWATCHMODEL_H

#include <QAbstractTableModel>
#include <QList>

enum
{
	SymbolWatchCol_Symbol = 0,
	SymbolWatchCol_Address,
	SymbolWatchCol_Size,
	SymbolWatchCol_Value,
	SymbolWatchCol_Segment,
	SymbolWatchCol_File,
	SymbolWatchCol_MAX
};

struct WatchedItem
{
	QString symbol;
	QString file;
	int segment;
};

class CSymbolWatchModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit CSymbolWatchModel(bool editable, QObject* parent = nullptr);
	~CSymbolWatchModel() override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role) override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	void removeRow(int row, const QModelIndex& parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
	void insertRow(QString text, int addr = -1, const QModelIndex& parent = QModelIndex());

	QList<WatchedItem> getItems() { return m_items; }
	void setItems(QList<WatchedItem> items) { m_items = items; }

	int resolveSymbol(QString text, int addr = -1) const;

public slots:
	void update();
	void sort(int column, Qt::SortOrder order) override;

private:
	QList<WatchedItem> m_items;
	int m_currentSortColumn;
	Qt::SortOrder m_currentSortOrder;
	int m_currentItemCount;
	bool m_editable;
	char* m_modelStringBuffer;
};

#endif // CSYMBOLWATCHMODEL_H
