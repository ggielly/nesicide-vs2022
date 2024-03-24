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

; Test out the port and asm features

; Some NES ports
export port ppuControl = $2000
export port ppuMask = $2001
export port apuDmcFrequencey = $4010
export port apuFrameCounter = $4017

export sub main
	; Init code
	apuFrameCounter = $40
	apuDmcFrequencey = 0
	ppuControl = 0
	ppuMask = 0
	
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
end sub

export sub frame
end sub

export sub interrupt
end sub
