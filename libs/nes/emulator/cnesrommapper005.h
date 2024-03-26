#if !defined ( ROM_MAPPER005_H )
#define ROM_MAPPER005_H

#include "cnesrom.h"
#include "cnesapu.h"

class CNAMETABLEFILLER: public CMEMORY
{
public:
   CNAMETABLEFILLER() : CMEMORY(0x5106,1) {}
   virtual ~CNAMETABLEFILLER() {};

   // Code/Data logger support functions
   CCodeDataLogger* LOGGER (uint32_t virtAddr = 0);
   CCodeDataLogger* LOGGERATPHYSADDR (uint32_t physAddr);

   void OPCODEMASK ( uint32_t virtAddr, uint8_t mask ) {}
   virtual void OPCODEMASKATPHYSADDR ( uint32_t physAddr, uint8_t mask ) {}

   uint8_t MEM (uint32_t addr);
   void MEM (uint32_t addr, uint8_t data);
   uint8_t MEMATPHYSADDR (uint32_t absAddr);
   void MEMATPHYSADDR (uint32_t absAddr, uint8_t data);

   uint8_t* MEMPTR (uint32_t addr) { return m_pBank[0]->MEMPTR(0); }

   void REMAP(uint32_t virt, uint32_t phys) {}
   void REMAPEXT(uint32_t virt, CMEMORYBANK* phys) {}

   uint32_t SLOC ( uint32_t virtAddr ) { return 1; }
   virtual const char* DISASSEMBLY ( uint32_t virtAddr ) { return "???"; }
   virtual const char* DISASSEMBLYATPHYSADDR ( uint32_t physAddr, char* buffer ) { return "???"; }

   uint32_t TOTALSIZE() const { return 0; }

protected:
   uint8_t m_tileFill;
   uint8_t m_attrFill;
};

class CROMMapper005 : public CROM
{
private:
   CROMMapper005();
public:
   static inline CROMMapper005* CARTFACTORY() { return new CROMMapper005(); }
   virtual ~CROMMapper005();

   void RESET ( bool soft );
   uint32_t HMAPPER ( uint32_t addr );
   void HMAPPER ( uint32_t addr, uint8_t data );
   uint32_t LMAPPER ( uint32_t addr );
   void LMAPPER ( uint32_t addr, uint8_t data );
   void SYNCPPU ( uint32_t ppuCycle, uint32_t ppuAddr );
   void SYNCCPU ( bool write, uint16_t addr, uint8_t data );
   void SETCPU ( void );
   void SETPPU ( void );
   uint32_t DEBUGINFO ( uint32_t addr );
   uint16_t AMPLITUDE ( void );
   static void SOUNDENABLE (const uint32_t mask ) { m_soundEnableMask = mask; }

   // Internal accessors for mapper information inspector...
   // Note: called directly!
   uint32_t IRQENABLED ( void )
   {
      return m_irqEnabled;
   }
   uint32_t IRQASSERTED ( void )
   {
      return m_irqStatus;
   }
   uint32_t IRQSCANLINE ( void )
   {
      return m_irqScanline;
   }
   uint32_t SPRITEMODE ( void )
   {
      return m_sprite8x16Mode;
   }
   uint32_t PPUCYCLE ( void )
   {
      return m_ppuCycle;
   }
   uint32_t VRAM ( uint32_t addr );
   uint32_t CHRMEM ( uint32_t addr );

protected:
   // MMC5
   CNAMETABLEFILLER* m_pFILLmemory;
   uint8_t m_prgMode;
   uint8_t m_chrMode;
   uint8_t m_chrHigh;
   uint8_t m_irqScanline;
   uint8_t m_irqEnabled;
   uint8_t m_irqStatus;
   uint8_t m_exRamMode;
   int32_t m_sc1;
   int32_t m_sc2;
   int32_t m_sc3;
   int32_t m_sc4;
   bool          m_prgRAM [ 3 ];
   bool          m_wp;
   uint32_t m_ppuCycle;
   uint32_t m_ppuAddr;
   uint16_t m_chrReg_a[8];
   uint16_t m_chrReg_b[4];
   uint16_t m_chrBank_a[8];
   uint16_t m_chrBank_b[8];
   uint8_t  m_prg[4];
   uint8_t m_wp1;
   uint8_t m_wp2;
   uint8_t  m_mult1;
   uint8_t  m_mult2;
   uint16_t m_timer;
   bool     m_timerIrq;
   uint16_t m_prod;
   uint8_t m_8x16e;
   uint8_t m_8x16z;
   uint8_t m_lastChr;
   uint8_t  m_reg[46];

   CAPUSquare m_square[2];
   CAPUDMC    m_dmc;
   int16_t    m_out[1024];

   uint32_t   m_sprite8x16Mode;
   uint32_t   m_lastPPUCycle;

   static uint32_t  m_soundEnableMask;
};

#endif
