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

; Composite types test file

rom 0
ram 1

; Player type
type player
	word x
	word y
	byte hp
	byte hpMax
end type

; Bullet type
type bullet
	word x
	word y
	byte damage
end type

; The bullets
bullet bullets[10]

; Demonstration purposes only
export sub main
	; Our player
	player p
	p.x = 7
	p.y = 183
	p.hpMax = 92
	p.hp = p.hpMax
	
	byte idx
	idx = 0
	while idx < 10
		if bullets.x[idx] == p.x
			if bullets.y[idx] == p.y
				p.hp = p.hp - bullets.damage[idx]
			end if
		end if
		idx = idx + 1
	end while
end sub

; All vectors must be present
export sub frame
end sub

; Return statements for interrupt subs automatically use the rti instruction.
export sub interrupt
end sub
