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

; Array tests

export sub main
	dword test[4]
	
	test[0] = $87654321
	test.a[1] = $21
	
	byte idx
	idx = 3
	test[idx] = 0
	
	if test[0] == $87654321
		test[idx] = 0
	end if
	
	idx += 1
	test[idx] = 4
	idx += 1
	test[idx] = 5
	idx += 2
	test[idx] = 6
end sub

export sub frame
end sub

export sub interrupt
end sub
