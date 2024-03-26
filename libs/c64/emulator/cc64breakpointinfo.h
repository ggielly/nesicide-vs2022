#ifndef CC64BREAKPOINTINFO_H
#define CC64BREAKPOINTINFO_H

#include "cbreakpointinfo.h"

class cc64_breakpoint_info final : public CBreakpointInfo
{
public:
   cc64_breakpoint_info();
   void GetPrintable ( int idx, char* msg ) override;
   void GetHitPrintable ( int idx, char* hmsg ) override;

protected:
   void ModifyBreakpoint ( BreakpointInfo* p_breakpoint, int type, eBreakpointItemType item_type, int event, int item1, int item1_physical, int item2, int mask, bool mask_exclusive, eBreakpointConditionType condition_type, int condition, eBreakpointDataType data_type, int data, bool enabled ) override;
};

#endif // CBREAKPOINTINFO_H
