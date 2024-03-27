#include "c64_emulator_core.h"

#include "cc646502.h"
#include "cc64sid.h"

static char emu_version_[] = "v2.0.0"
#if defined ( QT_NO_DEBUG )
" RELEASE";
#else
" DEBUG";
#endif

char* c64GetVersion()
{
   return emu_version_;
}

//const char* hex_char = "0123456789ABCDEF";

bool __c64debug = false;

void c64EnableDebug ( void )
{
   __c64debug = true;
}

void c64DisableDebug ( void )
{
   __c64debug = false;
}


static void (*breakpoint_hook)(void) = nullptr;

void c64SetBreakpointHook ( void (*hook)(void) )
{
   breakpoint_hook = hook;
}

void c64Break ( void )
{
   if ( breakpoint_hook )
   {
      breakpoint_hook();
   }
}

uint32_t c64_get_num_colors ( void )
{
   return 16;
}

auto c64_get_printable_address(char* buffer, const uint32_t addr) -> void
{
	//sprintf(buffer, "%04X", addr);
    // Use sprintf_s with appropriate buffer size and format specifier
    sprintf_s(buffer, sizeof(buffer), "%04X", addr);

}

auto c64_get_printable_physical_address(char* buffer, const uint32_t addr, uint32_t /*absAddr*/) -> void
{
  // sprintf(buffer,"%04X",addr);
  // Use sprintf_s with appropriate buffer size and format specifier
  sprintf_s(buffer, sizeof(buffer), "%04X", addr);

}

auto c64_enable_breakpoints(bool /*enable*/) -> void
{
}

void c64StepCpu ( void )
{
}

CBreakpointInfo* c64GetBreakpointDatabase ( void )
{
   return cc646502::BREAKPOINTS();
}

CRegisterDatabase* c64GetCpuRegisterDatabase()
{
   return cc646502::REGISTERS();
}

CMemoryDatabase* c64GetCpuMemoryDatabase()
{
   return cc646502::MEMORY();
}

void c64Disassemble ()
{
   cc646502::DISASSEMBLE();
}

void c64DisassembleSingle (const uint8_t* pOpcode, char* buffer )
{
   cc646502::Disassemble(pOpcode,buffer);
}

char* c64GetDisassemblyAtAddress (const uint32_t addr )
{
   return cc646502::DISASSEMBLY(addr);
}

void c64GetDisassemblyAtPhysicalAddress (const uint32_t absAddr, char* buffer )
{
   cc646502::DISASSEMBLYATPHYSADDR(absAddr,buffer);
}

uint32_t c64GetPhysicalAddressFromAddress (const uint32_t addr )
{
   return addr;
}

uint32_t c64GetAddressFromSLOC (const uint16_t sloc )
{
   return cc646502::SLOC2VIRTADDR(sloc);
}

uint16_t c64GetSLOCFromAddress (const uint32_t addr )
{
   return cc646502::ADDR2SLOC(addr);
}

uint32_t c64GetSLOC ( uint32_t /*addr*/ )
{
   return cc646502::SLOC();
}

void c64ClearOpcodeMasks ( void )
{
   cc646502::OPCODEMASKCLR ();
}

void c64SetOpcodeMask (const uint32_t addr, const uint8_t mask )
{
   cc646502::OPCODEMASK(addr, mask);
}

void c64SetGotoAddress (const uint32_t addr )
{
   cc646502::GOTO(addr);
}

uint32_t c64GetGotoAddress ( void )
{
   return cc646502::GOTO();
}

void c64SetCPURegister (const uint32_t addr, const uint32_t data )
{
   switch ( addr )
   {
   case CPU_PC:
      cc646502::__PC(data);
      break;
   case CPU_SP:
      cc646502::_SP(data);
      break;
   case CPU_A:
      cc646502::_A(data);
      break;
   case CPU_X:
      cc646502::_X(data);
      break;
   case CPU_Y:
      cc646502::_Y(data);
      break;
   case CPU_F:
      cc646502::_F(data);
      break;
   case VECTOR_IRQ:
      // Can't chage.
      break;
   case VECTOR_RESET:
      // Can't chage.
      break;
   case VECTOR_NMI:
      // Can't chage.
      break;
   }
}

uint32_t c64GetCPURegister(const uint32_t addr )
{
   switch ( addr )
   {
   case CPU_PC:
      return cc646502::__PC();
      break;
   case CPU_SP:
      return cc646502::_SP();
      break;
   case CPU_A:
      return cc646502::_A();
      break;
   case CPU_X:
      return cc646502::_X();
      break;
   case CPU_Y:
      return cc646502::_Y();
      break;
   case CPU_F:
      return cc646502::_F();
      break;
   case VECTOR_IRQ:
      break;
   case VECTOR_RESET:
      break;
   case VECTOR_NMI:
      break;
   }
   return 0;
}

uint32_t c64GetCPUFlagNegative ( void )
{
   return 0;
}

uint32_t c64GetCPUFlagOverflow ( void )
{
   return 0;
}

uint32_t c64GetCPUFlagBreak ( void )
{
   return 0;
}

uint32_t c64GetCPUFlagDecimal ( void )
{
   return 0;
}

uint32_t c64GetCPUFlagInterrupt ( void )
{
   return 0;
}

uint32_t c64GetCPUFlagZero ( void )
{
   return 0;
}

uint32_t c64GetCPUFlagCarry ( void )
{
   return 0;
}

void c64SetCPUFlagNegative ( uint32_t /*set*/ )
{
}

void c64SetCPUFlagOverflow ( uint32_t /*set*/ )
{
}

void c64SetCPUFlagBreak ( uint32_t /*set*/ )
{
}

void c64SetCPUFlagDecimal ( uint32_t /*set*/ )
{
}

void c64SetCPUFlagInterrupt ( uint32_t /*set*/ )
{
}

void c64SetCPUFlagZero ( uint32_t /*set*/ )
{
}

void c64SetCPUFlagCarry ( uint32_t /*set*/ )
{
}

uint32_t c64GetMemory (const uint32_t addr )
{
   return cc646502::_MEM(addr);
}

void c64SetMemory (const uint32_t addr, const uint32_t data )
{
   cc646502::_MEM(addr,data);
}

uint32_t c64GetPaletteRedComponent(uint32_t /*idx*/)
{
//   return CBasePalette::GetPaletteR(idx)&0xFF;
   return 0;
}

uint32_t c64GetPaletteGreenComponent(uint32_t /*idx*/)
{
//   return CBasePalette::GetPaletteG(idx)&0xFF;
   return 0;
}

uint32_t c64GetPaletteBlueComponent(uint32_t /*idx*/)
{
//   return CBasePalette::GetPaletteB(idx)&0xFF;
   return 0;
}

void    c64SetPaletteRedComponent(uint32_t /*idx*/,uint32_t /*r*/)
{
//   CBasePalette::SetPaletteR(idx,r&0xFF);
   return;
}

void    c64SetPaletteGreenComponent(uint32_t /*idx*/,uint32_t /*g*/)
{
//   CBasePalette::SetPaletteG(idx,g&0xFF);
   return;
}

void    c64SetPaletteBlueComponent(uint32_t /*idx*/,uint32_t /*b*/)
{
//   CBasePalette::SetPaletteB(idx,b&0xFF);
   return;
}

CRegisterDatabase* c64GetSidRegisterDatabase()
{
   return CSID::REGISTERS();
}

uint32_t c64GetSID8Register (const uint32_t addr )
{
   return CSID::_MEM8(addr);
}

uint32_t c64GetSID16Register (const uint32_t addr )
{
   return CSID::_MEM16(addr);
}

void c64SetSID8Register (const uint32_t addr, const uint32_t data )
{
   CSID::_MEM8(addr,data);
}

void c64SetSID16Register (const uint32_t addr, const uint32_t data )
{
   CSID::_MEM16(addr,data);
}

void c64GetCpuSnapshot(C64CpuStateSnapshot* pSnapshot)
{
   int idx;
//   pSnapshot->pc = CC646502::__PC();
//   pSnapshot->pcAtSync = CC646502::__PCSYNC();
//   pSnapshot->sp = CC646502::_SP();
//   pSnapshot->a = CC646502::_A();
//   pSnapshot->x = CC646502::_X();
//   pSnapshot->y = CC646502::_Y();
//   pSnapshot->f = CC646502::_F();
   for ( idx = 0; idx < MEM_64KB; idx++ )
   {
      *(pSnapshot->memory+idx) = 0;//CC646502::_MEM(idx);
   }
}
