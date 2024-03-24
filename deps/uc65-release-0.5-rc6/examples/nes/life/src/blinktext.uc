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

; Blinking-caret text output library

import "nes.uc"

; Blinktext character lookup table entry
type charTransEntry
	byte glyphTile
end type

; Entries are for byte values $20 to $5f. Unsupported characters are assigned
; value $30
table charTrans of charTransEntry
	glyphTile=$31
	glyphTile=$24
	glyphTile=$30
	glyphTile=$25
	glyphTile=$30
	glyphTile=$30
	glyphTile=$29
	glyphTile=$2d
	glyphTile=$2e
	glyphTile=$30
	glyphTile=$30
	glyphTile=$2a
	glyphTile=$27
	glyphTile=$28
	glyphTile=$2f
	glyphTile=$00
	glyphTile=$01
	glyphTile=$02
	glyphTile=$03
	glyphTile=$04
	glyphTile=$05
	glyphTile=$06
	glyphTile=$07
	glyphTile=$08
	glyphTile=$09
	glyphTile=$26
	glyphTile=$30
	glyphTile=$30
	glyphTile=$30
	glyphTile=$30
	glyphTile=$30
	glyphTile=$30
	glyphTile=$0a
	glyphTile=$0b
	glyphTile=$0c
	glyphTile=$0d
	glyphTile=$0e
	glyphTile=$0f
	glyphTile=$10
	glyphTile=$11
	glyphTile=$12
	glyphTile=$13
	glyphTile=$14
	glyphTile=$15
	glyphTile=$16
	glyphTile=$17
	glyphTile=$18
	glyphTile=$19
	glyphTile=$1a
	glyphTile=$1b
	glyphTile=$1c
	glyphTile=$1d
	glyphTile=$1e
	glyphTile=$1f
	glyphTile=$20
	glyphTile=$21
	glyphTile=$22
	glyphTile=$23
	glyphTile=$30
	glyphTile=$30
	glyphTile=$30
	glyphTile=$30
	glyphTile=$2c
end table

constant caretGlyph = $2b

;; Executes a blinktext script starting at the given screen coordinates
;; @param src Source address of the blinktext script
;; @param x Starting screen X coordinate
;; @param y Starting screen Y coordinate
export sub blinkText address src, byte x, byte y
	
end sub

