#ifndef CBREAKPOINTINFO_H
#define CBREAKPOINTINFO_H

#define NUM_BREAKPOINTS 10

#include <stdlib.h>
#include <stdint.h>

using eBreakpointType = enum
{
	eBreakOnCPUExecution = 0,
	eBreakOnCPUMemoryAccess,
	eBreakOnCPUMemoryRead,
	eBreakOnCPUMemoryWrite,
	eBreakOnCPUState,
	eBreakOnCPUEvent,
	eBreakOnPPUFetch,
	eBreakOnOAMPortalAccess,
	eBreakOnOAMPortalRead,
	eBreakOnOAMPortalWrite,
	eBreakOnPPUPortalAccess,
	eBreakOnPPUPortalRead,
	eBreakOnPPUPortalWrite,
	eBreakOnPPUState,
	eBreakOnPPUEvent,
	eBreakOnAPUState,
	eBreakOnAPUEvent,
	eBreakOnMapperState,
	eBreakOnMapperEvent,
	// The following breakpoint is not settable, it is internal only.
	eBreakOnPPUCycle
};

using eBreakpointTarget = enum
{
	eBreakInCPU = 0,
	eBreakInPPU,
	eBreakInAPU,
	eBreakInMapper
};

using eBreakpointCondition = enum
{
	eBreakIfAnything = 0,
	eBreakIfEqual,
	eBreakIfNotEqual,
	eBreakIfGreaterThan,
	eBreakIfLessThan,
	eBreakIfExclusiveMask,
	eBreakIfInclusiveMask
};

using eBreakpointItemType = enum
{
	eBreakpointItemAddress = 0,
	eBreakpointItemRegister,
	eBreakpointItemEvent,
	eBreakpointItemNone
};

using eBreakpointConditionType = enum
{
	eBreakpointConditionNone = 0,
	eBreakpointConditionTest
};

using eBreakpointDataType = enum
{
	eBreakpointDataNone = 0,
	eBreakpointDataPure,
	eBreakpointDataPick
};

class CBreakpointEventInfo
{
public:
	CBreakpointEventInfo(const char* name, bool (*evalFunc)(struct _BreakpointInfo* pBreakpoint, int data),
	                     int elements, const char* displayFormat, int elementRadix, const char* item1Name = nullptr,
	                     const char* item2Name = nullptr)
	{
		m_name = name;
		m_evalFunc = evalFunc;
		m_elements = elements;
		m_displayFormat = displayFormat;
		m_elementRadix = elementRadix;
		m_item1Name = item1Name;
		m_item2Name = item2Name;
	}

	const char* GetName(void) const
	{
		return m_name;
	}

	const char* GetItemName(int item) const
	{
		if (item == 0)
		{
			return m_item1Name;
		}
		else
		{
			return m_item2Name;
		}
	}

	int GetNumElements(void) const
	{
		return m_elements;
	}

	const char* GetDisplayFormat(void) const
	{
		return m_displayFormat;
	}

	int GetElementRadix(void) const
	{
		return m_elementRadix;
	}

	bool Evaluate(struct _BreakpointInfo* pBreakpoint, int data) const
	{
		return m_evalFunc(pBreakpoint, data);
	}

private:
	const char* m_name;
	bool (*m_evalFunc)(struct _BreakpointInfo* pBreakpoint, int data);
	int m_elements;
	const char* m_displayFormat;
	int m_elementRadix;
	const char* m_item1Name;
	const char* m_item2Name;
};

using BreakpointInfo = struct _BreakpointInfo
{
	int type; // Opaque for overrideability.
	bool enabled;
	eBreakpointTarget target;
	eBreakpointItemType itemType;
	int event;
	CBreakpointEventInfo* pEvent;
	uint32_t item1;
	uint32_t item1Physical;
	uint32_t item2;
	uint32_t itemActual;
	uint32_t itemMask;
	bool itemMaskExclusive;
	eBreakpointConditionType conditionType;
	int condition;
	eBreakpointDataType dataType;
	int data; // depending on type this field will be real value or index of bitfield value...
	bool hit;
};

using BreakpointStatus = enum _BreakpointStatus
{
	Breakpoint_Idle = 0,
	Breakpoint_Hit,
	Breakpoint_Disabled
};

class CBreakpointInfo
{
public:
	CBreakpointInfo();
	virtual ~CBreakpointInfo();
	void ConstructBreakpoint(BreakpointInfo* pBreakpoint, int type, eBreakpointItemType itemType, int event, int item1,
	                         int item1Physical, int item2, int mask, bool maskExclusive,
	                         eBreakpointConditionType conditionType, int condition, eBreakpointDataType dataType,
	                         int data, bool enabled);
	int add_breakpoint(const BreakpointInfo* pBreakpoint);
	int AddBreakpoint(int type, eBreakpointItemType itemType, int event, int item1, int item1Physical, int item2,
	                  int mask, bool maskExclusive, eBreakpointConditionType conditionType, int condition,
	                  eBreakpointDataType dataType, int data, bool enabled);
	void ModifyBreakpoint(int bp, const BreakpointInfo* pBreakpoint);
	void RemoveBreakpoint(int index);
	int FindExactMatch(int type, eBreakpointItemType itemType, int event, int item1, int item1_physical, int item2,
	                   int mask, bool maskExclusive, eBreakpointConditionType condition_type, int condition,
	                   eBreakpointDataType data_type, int data) const;
	void ToggleEnabled(int bp);
	void SetEnabled(int bp, bool enabled);
	BreakpointStatus GetStatus(int idx) const;
	virtual void GetPrintable(int idx, char* msg) = 0; // Must be provided by subclass.
	virtual void GetHitPrintable(int idx, char* hmsg) = 0; // Must be provided by subclass.
	int GetNumBreakpoints(void) const
	{
		return m_numBreakpoints;
	}

	BreakpointInfo* GetBreakpoint(int idx)
	{
		return &(m_breakpoint[idx]);
	}

protected:
	// Must be provided by subclass.
	virtual void ModifyBreakpoint(BreakpointInfo* pBreakpoint, int type, eBreakpointItemType itemType, int event,
	                              int item1, int item1Physical, int item2, int mask, bool maskExclusive,
	                              eBreakpointConditionType conditionType, int condition, eBreakpointDataType dataType,
	                              int data, bool enabled) = 0;

protected:
	BreakpointInfo m_breakpoint[NUM_BREAKPOINTS];
	int m_numBreakpoints;
};

#endif // CBREAKPOINTINFO_H
