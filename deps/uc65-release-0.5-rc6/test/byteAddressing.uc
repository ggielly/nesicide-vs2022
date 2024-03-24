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

; Byte addressing tests

; The main subroutine is made the reset vector, the frame subroutine is made the
; NMI vector and the interrupt subroutine is made the IRQ vector. These
; subroutines must be exported to be seen as vectors.
export sub main
	dword flags
	
	flags.a = $12
	flags.b = $34
	flags.c = $56
	flags.d = $78
	if flags == $12345678
		flags = 0
	end if
end sub

; All vectors must be present
export sub frame
end sub

; Return statements for interrupt subs automatically use the rti instruction.
export sub interrupt
end sub
