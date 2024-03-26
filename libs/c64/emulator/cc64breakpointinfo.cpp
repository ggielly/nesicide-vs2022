#include "cbreakpointinfo.h"

#include "c64_emulator_core.h"

#include "cc646502.h"
#include "cc64sid.h"

cc64_breakpoint_info::cc64_breakpoint_info()
= default;

void cc64_breakpoint_info::ModifyBreakpoint ( BreakpointInfo* p_breakpoint, int type, const eBreakpointItemType item_type, const int event, const int item1, const int item1_physical, const int item2, const int mask, const bool mask_exclusive, const eBreakpointConditionType condition_type, const int condition, const eBreakpointDataType data_type, const int data, const bool enabled )
{
   p_breakpoint->hit = false;
   p_breakpoint->enabled = enabled;
   p_breakpoint->itemActual = -1;
   p_breakpoint->type = static_cast<eBreakpointType>(type);
   p_breakpoint->pEvent = nullptr;

   switch ( type )
   {
      case eBreakOnCPUExecution:
      case eBreakOnCPUMemoryAccess:
      case eBreakOnCPUMemoryRead:
      case eBreakOnCPUMemoryWrite:
         p_breakpoint->target = eBreakInCPU;
         break;
   }

   p_breakpoint->conditionType = condition_type;
   p_breakpoint->condition = condition;
   p_breakpoint->itemType = item_type;
   p_breakpoint->event = event;

   // Events not supported yet.
   p_breakpoint->pEvent = nullptr;

   p_breakpoint->item1 = item1;
   p_breakpoint->item1Physical = item1_physical;
   p_breakpoint->item2 = item2;
   p_breakpoint->itemMask = mask;
   p_breakpoint->itemMaskExclusive = mask_exclusive;
   p_breakpoint->dataType = data_type;
   p_breakpoint->data = data;
}

void cc64_breakpoint_info::GetPrintable (const int idx, char* msg )
{
   char printableAddress[32];

   switch ( m_breakpoint[idx].type )
   {
      case eBreakOnCPUExecution:
         c64_get_printable_physical_address(printableAddress,
                                            m_breakpoint[idx].item1,
                                            m_breakpoint[idx].item1Physical);

         if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
         {
            sprintf ( msg, "Break if CPU executes at %s",
                      printableAddress );
         }
         else
         {
            sprintf ( msg, "Break if CPU executes between address %s and %04X",
                      printableAddress,
                      m_breakpoint[idx].item2 );
         }
         break;
      case eBreakOnCPUMemoryAccess:

         switch ( m_breakpoint[idx].condition )
         {
            case eBreakIfAnything:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU reads or writes anything at address %04X",
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU reads or writes anything between address %04X and %04X",
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfEqual:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU reads or writes %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU reads or writes %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfNotEqual:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU reads or writes anything but %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU reads or writes anything but %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfGreaterThan:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU reads or writes greater than %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU reads or writes greater than %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfLessThan:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU reads or writes less than %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU reads or writes less than %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
         case eBreakIfExclusiveMask:

            if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
            {
               sprintf ( msg, "Break if CPU reads or writes anything in the exclusive mask %02X at address %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1 );
            }
            else
            {
               sprintf ( msg, "Break if CPU reads or writes anything in the exclusive mask %02X between address %04X and %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1,
                         m_breakpoint[idx].item2 );
            }

            break;
         case eBreakIfInclusiveMask:

            if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
            {
               sprintf ( msg, "Break if CPU reads or writes anything in the inclusive mask %02X at address %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1 );
            }
            else
            {
               sprintf ( msg, "Break if CPU reads or writes anything in the inclusive mask %02X between address %04X and %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1,
                         m_breakpoint[idx].item2 );
            }

            break;
         }

         break;
      case eBreakOnCPUMemoryRead:

         switch ( m_breakpoint[idx].condition )
         {
            case eBreakIfAnything:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU reads anything at address %04X",
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU reads anything between address %04X and %04X",
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfEqual:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU reads %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU reads %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfNotEqual:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU reads anything but %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU reads anything but %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfGreaterThan:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU reads greater than %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU reads greater than %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfLessThan:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU reads less than %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU reads less than %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
         case eBreakIfExclusiveMask:

            if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
            {
               sprintf ( msg, "Break if CPU reads anything in the exclusive mask %02X at address %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1 );
            }
            else
            {
               sprintf ( msg, "Break if CPU reads anything in the exclusive mask %02X between address %04X and %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1,
                         m_breakpoint[idx].item2 );
            }

            break;
         case eBreakIfInclusiveMask:

            if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
            {
               sprintf ( msg, "Break if CPU reads anything in the inclusive mask %02X at address %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1 );
            }
            else
            {
               sprintf ( msg, "Break if CPU reads anything in the inclusive mask %02X between address %04X and %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1,
                         m_breakpoint[idx].item2 );
            }

            break;
         }

         break;
      case eBreakOnCPUMemoryWrite:

         switch ( m_breakpoint[idx].condition )
         {
            case eBreakIfAnything:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU writes anything at address %04X",
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU writes anything between address %04X and %04X",
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfEqual:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU writes %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU writes %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfNotEqual:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU writes anything but %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU writes anything but %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfGreaterThan:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU writes greater than %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU writes greater than %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
            case eBreakIfLessThan:

               if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
               {
                  sprintf ( msg, "Break if CPU writes less than %02X at address %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1 );
               }
               else
               {
                  sprintf ( msg, "Break if CPU writes less than %02X between address %04X and %04X",
                            m_breakpoint[idx].data,
                            m_breakpoint[idx].item1,
                            m_breakpoint[idx].item2 );
               }

               break;
         case eBreakIfExclusiveMask:

            if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
            {
               sprintf ( msg, "Break if CPU writes anything in the exclusive mask %02X at address %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1 );
            }
            else
            {
               sprintf ( msg, "Break if CPU writes anything in the exclusive mask %02X between address %04X and %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1,
                         m_breakpoint[idx].item2 );
            }

            break;
         case eBreakIfInclusiveMask:

            if ( m_breakpoint[idx].item1 == m_breakpoint[idx].item2 )
            {
               sprintf ( msg, "Break if CPU writes anything in the inclusive mask %02X at address %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1 );
            }
            else
            {
               sprintf ( msg, "Break if CPU writes anything in the inclusive mask %02X between address %04X and %04X",
                         m_breakpoint[idx].data,
                         m_breakpoint[idx].item1,
                         m_breakpoint[idx].item2 );
            }

            break;
         }
         break;
   }
}

void cc64_breakpoint_info::GetHitPrintable (const int idx, char* hmsg )
{
   char*          msg = hmsg;

   msg += sprintf ( msg, "BREAK: " );
   GetPrintable(idx,msg);
}
