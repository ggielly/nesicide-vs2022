; Conway's Game of Life for NES
;
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

import "nes.uc"
import "data.uc"
import "title.uc"

; Main globals
export fast byte vblankFlag

;; Turn rendering off
export sub ppuOff
	ppuControl = %00000000
	ppuMask &= %00000110
end sub

;; Turn on rendering
export sub ppuOn
	ppuControl = %10000000
	ppuMask = %00011110
end sub

export sub main
	nesInit
	nesSendPPU @dataPalette, $3f00, 32
		
	; Jump to the title screen
	titleMain
end sub

export sub frame
	; Set the vblank flag before returning
	vblankFlag += 1
end sub

export sub interrupt
end sub

