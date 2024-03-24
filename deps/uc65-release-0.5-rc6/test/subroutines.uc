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

; Subroutines

sub sum byte a, byte b as byte
	return a + b
end sub

sub bigSum dword a, dword b as dword
	return a + b
end sub

sub shortLeet as byte
	return 137
end sub

; Various subroutine tests
export sub main
	byte c
	sum 2, c + 4
	c = sum 1 + 14, 7
	
	dword d
	d = bigSum 472985, c
	
	; Should give a loss of precision warning
	sum c, d
	
	; Regression test for defects found in 0.4 RC-1, subroutines with return
	; value and no parameter list
	c = shortLeet
end sub

export sub frame
end sub

export sub interrupt
end sub
