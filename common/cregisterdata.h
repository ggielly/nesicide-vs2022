#ifndef CREGISTERDATA_H
#define CREGISTERDATA_H

#include <cassert>

#include "stdarg.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

enum
{
	eMemory_REGISTER_BASE = 0x2000 // Must be unique from eMemory_MEMORY_BASE in cmemorydata.h
};

#define eMemory_CPUregs (eMemory_REGISTER_BASE+0)
#define eMemory_PPUregs (eMemory_REGISTER_BASE+1)
#define eMemory_PPUoam (eMemory_REGISTER_BASE+2)
#define eMemory_IOregs (eMemory_REGISTER_BASE+3)
#define eMemory_cartMapper (eMemory_REGISTER_BASE+4)
#define eMemory_SIDregs (eMemory_REGISTER_BASE+5)



class CBitfieldData final
{
public:
	CBitfieldData(const char* name, char start, char width, const char* displayFormat, int values, ...)
	{
		int idx;
		m_name_ = name;
		m_values_ = values;
		m_start_ = start;
		m_width_ = width;
		m_display_format_ = displayFormat;
		char m_lsb = start;
		int m_msb = start + width - 1;

		if (values)
		{
			va_list va;

			va_start(va, values);
			m_value_ = new char* [values];

			for (idx = 0; idx < values; idx++)
			{
				char* temp = (char*)va_arg(va, const char*);
				m_value_[idx] = new char[strlen(temp) + 6]; // account for raw addition
				sprintf(m_value_[idx], "%X: %s", idx, temp);
			}

			va_end(va);
		}
	}


	virtual ~CBitfieldData()
	{
		delete  m_name_;
		delete [] m_value_;
	}
	

	char GetWidth(void) const
	{
		return m_width_;
	}

	char GetLsb(void) const
	{
		return m_lsb_;
	}

	char GetMsb(void) const
	{
		return m_msb_;
	}

	int GetNumValues(void) const
	{
		return m_values_;
	}

	const char* GetName(void) const
	{
		return m_name_;
	}

	const char* GetDisplayFormat(void) const
	{
		return m_display_format_;
	}

	char* GetValue(int data) const
	{
		//data >>= m_start;
		assert(m_value_);
		data &= ((1 << m_width_) - 1);
		
		return m_value_[data];
	}

	int GetValueRaw(int data) const
	{
		//data >>= m_start;
		assert(m_value_);
		data &= ((1 << m_width_) - 1);
		return data; 
	}

	char* GetValueByIndex(const int index) const
	{
		return m_value_[index];
	}

	int InsertValue(int data, int bits_to_insert) const
	{
		int mask = ((1 << m_width_) - 1);
		mask <<= m_start_;
		data &= (~(mask));
		bits_to_insert <<= m_start_;
		data |= bits_to_insert;
		return data;
	}

	/* 
protected:
	/*const char* m_name;
	const char* m_displayFormat;
	char m_start;
	char m_width;
	char m_lsb;
	char m_msb;
	char** m_value;
	uint8_t m_values;

	const char* m_name_;
	const char* m_display_format_;
	uint8_t m_start_;
	uint8_t m_width_;
	uint8_t m_lsb_;
	uint8_t m_msb_;
	char** m_value_;
	int m_values_;
	*/

	protected:
		const char* m_name_;
		const char* m_display_format_;
		char  m_start_;
		char  m_width_;
		char  m_lsb_;
		char  m_msb_;
		char** m_value_;
		int   m_values_;

private:
	//CBitfieldData* p_bitfield_;

	
};


using setRegFunc = void(*)(uint32_t, uint32_t);
using getRegFunc = uint32_t(*)(uint32_t);

class CRegisterData final
{
public:
	CRegisterData(const int addr, const char* name, const getRegFunc get, const setRegFunc set, const int fields, CBitfieldData** tbl_field)
	{
		m_addr = addr;
		m_name = name;
		m_fields = fields;
		m_field = tbl_field;
		m_get = get;
		m_set = set;
	}

	virtual ~CRegisterData()
	{
	};

	const char* GetName(void) const
	{
		return m_name;
	}

	int GetNumBitfields(void) const
	{
		return m_fields;
	}

	CBitfieldData* GetBitfield(const int field) const
	{
		return m_field[field];
	}

	int GetAddr(void) const
	{
		return m_addr;
	}

	void Set(const uint32_t data) const { m_set(m_addr, data); }
	uint32_t get() const { return m_get(m_addr); }

protected:
	int m_addr;
	const char* m_name;
	int m_fields;
	CBitfieldData** m_field;
	getRegFunc m_get;
	setRegFunc m_set;
};

class CRegisterDatabase
{
public:
	CRegisterDatabase(const int type, const int rows, const int columns, const int registers, CRegisterData** tbl_registers,
	                  const char** row_headings, const char** column_headings)
	{
		m_type = type;
		m_register_ = tbl_registers;
		m_registers_ = registers;
		m_rows_ = rows;
		m_columns_ = columns;
		m_row_headings_ = row_headings;
		m_column_headings_ = column_headings;
	}

	int GetType() const { return m_type; }

	bool Contains(const int addr) const
	{
		for (int idx = 0; idx < m_registers_; idx++)
		{
			if (m_register_[idx]->GetAddr() == addr)
			{
				return true;
			}
		}
		return false;
	}

	CRegisterData** GetRegisters() const { return m_register_; }
	CRegisterData* GetRegister(const int idx) const { return m_register_[idx]; }

	int GetRegisterAt(const int addr)
	{
		for (int idx = 0; idx < m_registers_; idx++)
		{
			if (m_register_[idx]->GetAddr() == addr)
			{
				return idx;
			}
		}
		return -1;
	}

	//int GetNumRegisters() const { return m_registers_; }
	int GetNumRegisters() const { return m_registers_; }
	int GetNumRows() const { return m_rows_; }
	int GetNumColumns() const { return m_columns_; }
	const char* GetRowHeading(const int idx) { return m_row_headings_[idx]; }
	const char* GetColumnHeading(const int idx) { return m_column_headings_[idx]; }

protected:
	int m_type;
	CRegisterData** m_register_;
	int m_registers_;
	int m_rows_;
	int m_columns_;
	const char** m_row_headings_;
	const char** m_column_headings_;
};

using regDBFunc = CRegisterDatabase* (*)();

#endif // CREGISTERDATA_H
