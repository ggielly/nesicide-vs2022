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

; End of line comments

; ROM statements tell the compiler what ROM bank to place ROM-able code and data
; into.
rom 0

; RAM statements tell the compiler what RAM bank to place variables into.
ram 1

; Variables outside of functions have global scope
dword global

; Anything declared as export can be imported from another file
export byte somePig

; A fast variable is placed into zero-page
fast byte myCounter

; Compile-time constants are declared as such
constant bigWord = 17890
constant redundant = bigWord

; Subroutines can have parameters, but do not return values
sub doesNothing byte first, byte second
	; Variables declared inside of a subroutine have local scope
	byte b
	word w
	long l
	dword d
	
	; Using constants
	w = redundant
	b = 225
	l = w
	d = l + b
	
	b = first
	w = first + second
	
	; If / Else If / Else, with nesting
	if first == 7
		b = 0
	else if w == $7890
		b = 1
		if l == $567890
			b = 2
		else if d == $12345678
			b = 3
		else
			b = 5
		end if
	else
		b = 4
	end if
	
	; While loops test a precondition before each itteration
	b = 0
	while b == 0
		b = 1
	end while
	
	; Loops can execute forever or until a post-condition is true
	loop
		b = 0
		loop
			b = b + 1
		end loop when b == 4
	end loop
	
	; Break and continue
	loop
		break
		continue
		loop
			break
			break 2
			continue
			continue 2
		end loop
	end loop
end sub

; The main subroutine is made the reset vector, the frame subroutine is made the
; NMI vector and the interrupt subroutine is made the IRQ vector. These
; subroutines must be exported to be seen as vectors.
export sub main
end sub

; All vectors must be present
export sub frame
end sub

; Return statements for interrupt subs automatically use the rti instruction.
export sub interrupt
end sub
