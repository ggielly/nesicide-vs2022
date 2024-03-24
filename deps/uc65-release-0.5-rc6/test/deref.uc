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

address ptr
byte a
word b
long c
dword d

; Tests for various address dereferencing scenarios
export sub main
	ptr = $0200
	
	a = (byte)ptr
	b = (word)ptr[1]
	c = (long)ptr[3]
	d = (dword)ptr[6]
	(byte)ptr[10] = a	
	(word)ptr[11] = b	
	(long)ptr[13] = c	
	(dword)ptr[16] = d
	(word)ptr[20] = (word)ptr[1] + (word)ptr[11]
end sub

; All vectors must be present
export sub frame
end sub

; Return statements for interrupt subs automatically use the rti instruction.
export sub interrupt
end sub
