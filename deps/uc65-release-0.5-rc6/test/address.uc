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

; Tests for tables, files the address data type and address dereferencing

; Defines a shape
type shapedef
	byte	partsPerFrame	; How many parts this shape has in a given frame
	word	ofsInFile		; Relative offset into the frame file at which this
							; shape's frame data starts
end type

; Defines a single NES OAM animation frame element
type framedef
	byte	tile			; Tile index (assumes the proper tileset is loaded)
	byte	attr			; Attribute byte (assumes left-facing)
	byte	ofsx			; X offset from object origin
	byte	ofsy			; Y offset from object origin
end type

; Define all the shapes in our game
export table shapeTable of shapedef
	partsPerFrame=1,	ofsInFile=$0000		; Bullet
	partsPerFrame=4,	ofsInFile=$0008		; Blob
end table

; Data file of all frames
export file frameData
	; Bullet frame 0
	framedef tile=$00,attr=$00,ofsx=$fc,ofsy=$fc
	; Bullet frame 1
	framedef tile=$00,attr=$01,ofsx=$fc,ofsy=$fc
	; Blob frame 0
	framedef tile=$01,attr=$02,ofsx=$f8,ofsy=$00
	framedef tile=$02,attr=$02,ofsx=$00,ofsy=$00
	framedef tile=$03,attr=$02,ofsx=$f8,ofsy=$08
	framedef tile=$04,attr=$02,ofsx=$00,ofsy=$08
	; Example of mixing built-in data types
	word	$1337,	$baad,	$beef
end file

; Main routine
export sub main
	; Fill out a shape structure with data from our shape table
	shapedef s
	s.partsPerFrame = shapeTable.partsPerFrame[1]
	s.ofsInFile = shapeTable.ofsInFile[1]
	
	; Output the first frame of our shape into the OAM buffer
	address oam
	oam = $0200
	address frame
	frame = @frameData + s.ofsInFile
	byte x
	byte y
	byte attr
	byte tile
	while s.partsPerFrame != 0
		tile = (byte)frame
		attr = (byte)frame[1]
		x = (byte)frame[2]
		y = (byte)frame[3]
		(byte)oam = x
		(byte)oam[1] = tile
		(byte)oam[2] = attr
		(byte)oam[3] = y
		frame = frame + 4
		oam = oam + 4
		s.partsPerFrame = s.partsPerFrame - 1
	end while
end sub

; All vectors must be present
export sub frame
end sub

; Return statements for interrupt subs automatically use the rti instruction.
export sub interrupt
end sub
