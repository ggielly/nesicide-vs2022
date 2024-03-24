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

; Assignment operator tests

export sub main
	word a
	a = 0
	a += 30
	a -= 10
	a <<= 4
	a >>= 2
	a &= $1ff0
	a |= $8000
	a ^= $ffff
	
	; Optimized increment and decrement tests
	byte b
	dword c
	b += 1
	b -= 1
	c += 1
	c -= 1
end sub

; All vectors must be present
export sub frame
end sub

; Return statements for interrupt subs automatically use the rti instruction.
export sub interrupt
end sub
