// BasePalette.h: interface for the CBasePalette class.
//
//////////////////////////////////////////////////////////////////////

#if !defined ( C64_BASE_PALETTE_H )
#define C64_BASE_PALETTE_H

#include <stdint.h> // for standard base types...
#include <string.h> // for memcpy...
#include <stdio.h> // for sprintf...

#define RGB_VALUE(r,g,b) ( ((r&0xFF)<<24)|((g&0xFF)<<16)|((b&0xFF)<<8) )

class CBasePalette
{
public:
   static inline uint8_t GetPaletteIndex (const int8_t red, const int8_t green, const int8_t blue )
   {
      int i;
      for ( i = 0; i < 16; i++ )
      {
         if ( (red == GetPaletteR(i)) &&
              (blue == GetPaletteB(i)) &&
              (green == GetPaletteG(i)) )
         {
            return i;
         }
      }
      return -1;
   }
   static inline uint32_t GetPalette (const int idx )
   {
      return *(m_palette_base_+idx);
   }
   static inline int8_t GetPaletteR (const int idx )
   {
      return *(*(m_palette_rg_bs_+idx)+0);
   }
   static inline int8_t GetPaletteG (const int idx )
   {
      return *(*(m_palette_rg_bs_+idx)+1);
   }
   static inline int8_t GetPaletteB (const int idx )
   {
      return *(*(m_palette_rg_bs_+idx)+2);
   }
   static void calculate_variants ( void );
   CBasePalette()
   {
      calculate_variants ();
   };

protected:
   static uint32_t m_palette_base_[16];
   static int8_t   m_palette_rg_bs_[16][3];
};

#endif
