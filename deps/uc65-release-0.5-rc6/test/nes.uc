; uc65 - Micro Code for 6502/NES
; Copyright (C) 2013  Norman B. Lancaster
; 
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; 
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.

; Test NES library, used by import.uc

; Port definitions
export port ppuControl = $2000
export port ppuMask = $2001
export port ppuStatus = $2002
export port ppuScroll = $2005
export port ppuAddress = $2006
export port ppuData = $2007
export port apuDmcFrequencey = $4010
export port oamDma = $4014
export port controller1 = $4016
export port apuFrameCounter = $4017
export port mmuControl = $8000
export port mmuData = $8001

rom __librom__
ram __libram__

; Read controller data
export sub readController as byte
	byte bits
	bits = 0
	
	; Controller strobe
	controller1 = 1
	controller1 = 0
	
	; Controller reading loop
	asm
		ldx #08
		loop:
			lda controller1
			and #03
			cmp #01
			ror readController_bits
			dex
			bne loop
	end asm
	
	return bits
end sub
