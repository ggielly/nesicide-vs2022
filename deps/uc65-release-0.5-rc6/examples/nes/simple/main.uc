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

; uc65 NES Initialization, Display and Control example

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

; Using ports for sprite data manipulation in place of pointers
port spriteY = $0200
port spriteTile = $0201
port spriteAttr = $0202
port spriteX = $0203

; Put all of this into the high page of ROM and system RAM
rom 31
ram 1

; Globals
byte vblankFlag			; Incremented every vblank

; Place a star tile in the nametable
sub star byte x, byte y
	byte tempY
	tempY = y >> 3
	ppuAddress = tempY | $20
	tempY = y << 5
	ppuAddress = tempY | x
	ppuData = 1
end sub

; Read controller data
sub readController as byte
	byte bits
	bits = 0
	
	; Controller strobe
	controller1 = 1
	controller1 = 0
	
	; Controller reading loop
	asm
		ldx #08
		loop:
			lda controller1
			and #03
			cmp #01
			ror readController_bits
			dex
			bne loop
	end asm
	
	return bits
end sub

; Program entry point
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
	mmuData = 0
	mmuControl = $07
	mmuData = 1
	
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
	
	; Set up sprite
	spriteTile = 2
	spriteAttr = 0
	spriteX = 124
	spriteY = 116
	
	; Enable PPU
	ppuControl = $80
	ppuMask = $1e
	
	; Main loop
	loop
		; Wait for the vblank to end
		while vblankFlag == 0
		end while
		
		; Frame handler
		vblankFlag = 0
		byte ctrl
		ctrl = readController
		byte button
		button = ctrl & $10
		if button != 0
			if spriteY != 0
				spriteY = spriteY - 1
			end if
		end if
		button = ctrl & $20
		if button != 0
			if spriteY != 232
				spriteY = spriteY + 1
			end if
		end if
		button = ctrl & $40
		if button != 0
			if spriteX != 0
				spriteX = spriteX - 1
			end if
		end if
		button = ctrl & $80
		if button != 0
			if spriteX != 248
				spriteX = spriteX + 1
			end if
		end if
	end loop
end sub

export sub frame
	; Execute sprite DMA
	oamDma = $02
	
	; Reset PPU latches
	asm
		bit ppuStatus
	end asm
	
	; Set scroll position
	ppuScroll = 0
	ppuScroll = 0
	
	; Set the vblank flag before exit
	vblankFlag = vblankFlag + 1
end sub

export sub interrupt
end sub

