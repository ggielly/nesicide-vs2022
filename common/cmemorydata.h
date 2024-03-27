#ifndef CMEMORYDATA_H
#define CMEMORYDATA_H

#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"

#define eMemory_MEMORY_BASE 0x1000 // Must be unique from eMemory_REGISTER_BASE in cregisterdata.h
#define eMemory_CPU 0
#define eMemory_PPU 1
#define eMemory_PPUpalette 2
#define eMemory_cartROM 3
#define eMemory_cartSRAM 4
#define eMemory_cartEXRAM 5
#define eMemory_cartCHRMEM 6
#define eMemory_cartVRAM 7

using setMemFunc = void(*)(uint32_t, uint32_t);
using getMemFunc = uint32_t(*)(uint32_t);
using rowHeadingFunc = void(*)(char*, uint32_t);
using cellsEditableFunc = bool(*)();
using cellColorComponentFunc = uint32_t(*)(uint32_t);

class CMemoryDatabase
{
public:
	CMemoryDatabase(int type,
	                int base,
	                int size,
	                int columns,
	                const char* name,
	                getMemFunc get,
	                setMemFunc set,
	                rowHeadingFunc rowHeading,
	                bool cellsSelectable,
	                cellColorComponentFunc cellRed = nullptr,
	                cellColorComponentFunc cellGreen = nullptr,
	                cellColorComponentFunc cellBlue = nullptr,
	                cellsEditableFunc cellsEditable = nullptr): m_extent(0), m_mirroredExtent(0)
	{
		m_type = type;
		m_base = base;
		m_columns = columns;
		m_rows = size / m_columns;
		m_size = size;
		m_name = name;
		m_get = get;
		m_set = set;
		m_rowHeading = rowHeading;
		m_cellsSelectable = cellsSelectable;
		m_cellsEditable = cellsEditable;
		m_cellRed = cellRed;
		m_cellGreen = cellGreen;
		m_cellBlue = cellBlue;
	}

	virtual ~CMemoryDatabase()
	{
	};

	const char* GetName(void) const
	{
		return m_name;
	}

	int GetType(void) const
	{
		return m_type;
	}

	int GetBase(void) const
	{
		return m_base;
	}

	int GetNumRows(void) const
	{
		return m_rows;
	}

	int GetNumColumns(void) const
	{
		return m_columns;
	}

	bool GetCellsSelectable(void) const
	{
		return m_cellsSelectable;
	}

	bool GetCellsEditable(void) const
	{
		if (m_cellsEditable)
		{
			return m_cellsEditable();
		}
		return true;
	}

	int GetSize(void) const
	{
		return m_size;
	}

	uint32_t GetCellRedComponent(int idx) const
	{
		if (m_cellRed)
		{
			return m_cellRed(idx);
		}
		return 0xFF;
	}

	uint32_t GetCellGreenComponent(int idx)
	{
		if (m_cellGreen)
		{
			return m_cellGreen(idx);
		}
		return 0xFF;
	}

	uint32_t GetCellBlueComponent(int idx)
	{
		if (m_cellBlue)
		{
			return m_cellBlue(idx);
		}
		return 0xFF;
	}

	void GetRowHeading(char* buffer, int idx) { return m_rowHeading(buffer, idx); }
	void Set(uint32_t offset, uint32_t data) { m_set(m_base + offset, data); }
	uint32_t Get(uint32_t offset) { return m_get(m_base + offset); }

protected:
	int m_type;
	int m_base;
	int m_extent;
	int m_mirroredExtent;
	bool m_cellsSelectable;
	int m_rows;
	int m_columns;
	int m_size;
	const char* m_name;
	getMemFunc m_get;
	setMemFunc m_set;
	rowHeadingFunc m_rowHeading;
	cellsEditableFunc m_cellsEditable;
	cellColorComponentFunc m_cellRed;
	cellColorComponentFunc m_cellGreen;
	cellColorComponentFunc m_cellBlue;
};

using memDBFunc = CMemoryDatabase* (*)();

#endif // CMEMORYDATA_H
