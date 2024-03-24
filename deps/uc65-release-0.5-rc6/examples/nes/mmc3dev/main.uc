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

; Development cart test
rom 31
ram 1

; Port definitions
export port ppuControl = $2000
export port ppuMask = $2001
export port ppuStatus = $2002
export port ppuScroll = $2005
export port ppuAddress = $2006
export port ppuData = $2007
export port apuDmcFrequencey = $4010
export port oamDma = $4014
export port controller1 = $4016
export port apuFrameCounter = $4017
export port mmuControl = $8000
export port mmuData = $8001

; Place a star tile in the nametable
sub star byte x, byte y
	byte tempY
	tempY = y >> 3
	ppuAddress = tempY | $20
	tempY = y << 5
	ppuAddress = tempY | x
	ppuData = 1
end sub

; Reset vector
export sub main
	; Init code
	apuFrameCounter = $40
	apuDmcFrequencey = 0
	ppuControl = 0
	ppuMask = 0
	
	; MMU setup
	mmuControl = $00
	mmuData = 0
	mmuControl = $01
	mmuData = 2
	mmuControl = $02
	mmuData = 4
	mmuControl = $03
	mmuData = 5
	mmuControl = $04
	mmuData = 6
	mmuControl = $05
	mmuData = 7
	mmuControl = $06
	mmuData = 28
	mmuControl = $07
	mmuData = 29
	
	; Assembly block to clear RAM
	asm
		ldx #$00
		loop:
			lda #$ff	; Page $02 needs to be cleared to $FF to force OAM data
			sta	$0200,x	; off-screen. Change this page if you don't use $02 for
			lda #$00	; the OAM DMA buffer.
			sta $0000,x
			sta $0100,x
			sta $0300,x
			sta $0400,x
			sta $0500,x
			sta $0600,x
			sta $0700,x
			dex
			bne	loop
	end asm
	
	; Assembly block to wait for the PPU to warm up
	asm
		bit ppuStatus
		loop1:
			bit ppuStatus
			bpl loop1
		loop2:
			bit ppuStatus
			bpl loop2
	end asm
	
	; Load palette
	ppuAddress = $3f
	ppuAddress = $00
	ppuData = $0d
	ppuData = $31
	ppuAddress = $3f
	ppuAddress = $11
	ppuData = $29
	
	; Set up test patterns
	ppuAddress = $00
	ppuAddress = $14
	ppuData = $08
	ppuAddress = $00
	ppuAddress = $20
	ppuData = %00111100
	ppuData = %01100110
	ppuData = %01000010
	ppuData = %11000011
	ppuData = %11000011
	ppuData = %01000010
	ppuData = %01100110
	ppuData = %00111100
	
	; Set up stars
	star 1, 7
	star 9, 14
	star 19, 20
	star 22, 29
	star 30, 2
	star 3, 4
	star 8, 6
	star 13, 10
	star 17, 16
	star 24, 19
	star 26, 24
	star 27, 28
	star 31, 1
	star 4, 20
	star 7, 29
	star 1, 17
	star 3, 23
	star 28, 4
	star 24, 1
	star 31, 7
	star 28, 5

	; Enable PPU
	ppuControl = $80
	ppuMask = $1e
	
	; Main loop
	loop
	end loop
end sub

export sub frame
	; Reset PPU latches
	asm
		bit ppuStatus
	end asm
	
	; Set scroll position
	ppuScroll = 0
	ppuScroll = 0
end sub

export sub interrupt
end sub

