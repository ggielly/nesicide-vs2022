// BasePalette.h: interface for the CBasePalette class.
//
//////////////////////////////////////////////////////////////////////

#if !defined ( NES_BASE_PALETTE_H )
#define NES_BASE_PALETTE_H

#include <stdint.h> // for standard base types...
#include <string.h> // for memcpy...
#include <stdio.h> // for sprintf...

#define RGB_VALUE(r,g,b) ( ((r&0xFF)<<24)|((g&0xFF)<<16)|((b&0xFF)<<8) )

inline void setRed(uint32_t rgb, const uint8_t r)
{
   rgb&=(~(0xFF<<24));
   rgb|=(r<<24);
}
inline void setGreen(uint32_t rgb, const uint8_t g)
{
   rgb&=(~(0xFF<<16));
   rgb|=(g<<16);
}
inline void setBlue(uint32_t rgb, const uint8_t b)
{
   rgb&=(~(0xFF<<8));
   rgb|=(b<<8);
}

class CBasePalette
{
public:
   static inline uint8_t GetPaletteIndex (const int8_t red, const int8_t green, const int8_t blue )
   {
      int i;
      for ( i = 0; i < 64; i++ )
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
   static inline uint32_t GetPalette ( int idx, const int bMonochrome = 0, const int bEmphasizeRed = 0, const int bEmphasizeGreen = 0, const int bEmphasizeBlue = 0 )
   {
      if ( bMonochrome )
      {
         idx&= 0xF0;
      }

      return *(*(m_paletteVariants+((bEmphasizeRed)|((bEmphasizeGreen)<<1)|((bEmphasizeBlue)<<2)))+idx);
   }
   static inline int8_t GetPaletteR ( int idx, const int bMonochrome = 0, const int bEmphasizeRed = 0, const int bEmphasizeGreen = 0, const int bEmphasizeBlue = 0 )
   {
      if ( bMonochrome )
      {
         idx&= 0xF0;
      }

      return *(*(*(m_paletteRGBs+((bEmphasizeRed)|((bEmphasizeGreen)<<1)|((bEmphasizeBlue)<<2)))+idx));
   }
   static inline int8_t GetPaletteG ( int idx, const int bMonochrome = 0, const int bEmphasizeRed = 0, const int bEmphasizeGreen = 0, const int bEmphasizeBlue = 0 )
   {
      if ( bMonochrome )
      {
         idx&= 0xF0;
      }

      return *(*(*(m_paletteRGBs+((bEmphasizeRed)|((bEmphasizeGreen)<<1)|((bEmphasizeBlue)<<2)))+idx)+1);
   }
   static inline int8_t GetPaletteB ( int idx, const int bMonochrome = 0, const int bEmphasizeRed = 0, const int bEmphasizeGreen = 0, const int bEmphasizeBlue = 0 )
   {
      if ( bMonochrome )
      {
         idx&= 0xF0;
      }

      return *(*(*(m_paletteRGBs+((bEmphasizeRed)|((bEmphasizeGreen)<<1)|((bEmphasizeBlue)<<2)))+idx)+2);
   }
   static inline void SetPalette (const int idx, const uint32_t color )
   {
      m_paletteVariants[0][idx] = color;
      calculate_variants ();
   }
   static inline void SetPaletteR (const int idx, const uint8_t r )
   {
      setRed(m_paletteVariants[0][idx],r);
      calculate_variants ();
   }
   static inline void SetPaletteG (const int idx, const uint8_t g )
   {
      setGreen(m_paletteVariants[0][idx],g);
      calculate_variants ();
   }
   static inline void SetPaletteB (const int idx, const uint8_t b )
   {
      setBlue(m_paletteVariants[0][idx],b);
      calculate_variants ();
   }
   static void calculate_variants ( void );
   static void RestoreBase ( void )
   {
      memcpy ( m_paletteVariants[0], m_paletteBase, sizeof(m_paletteBase) );
      calculate_variants ();
   }
   CBasePalette()
   {
      memcpy ( m_paletteVariants[0], m_paletteBase, sizeof(m_paletteBase) );
      calculate_variants ();
   };

protected:
   static int32_t m_paletteBase [ 64 ];
   static int32_t m_paletteVariants [ 8 ] [ 64 ];
   static int8_t   m_paletteRGBs [ 8 ] [ 64 ] [ 3 ];
};

#endif
