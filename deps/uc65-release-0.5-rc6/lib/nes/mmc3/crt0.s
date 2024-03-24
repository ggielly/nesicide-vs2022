; Micro Code 65 Common Run-Time for ca65 Assembler
.import frame, main, interrupt

.SEGMENT "HEAD"
	.byte $4E, $45, $53, $1A	; "NES" header
	.byte $10					; PRG-ROM / 16k
	.byte $00					; CHR-ROM / 8k
	.byte $42					; Mapper 4 (MMC3), battery-backed SRAM
	.byte $00					; Mapper 4 (MMC3)
	.byte $00					; No mapper variant
	.byte $00					; No extended ROM pages
	.byte $70					; 8kb Battery-backed SRAM
	.byte $09					; 32kb non-battery-backed SRAM
	.byte $00					; NTSC video system
	.byte $00					; No Vs. System hardware
	.byte $00, $00				; Researved

.SEGMENT "VECT"
	.word frame, main, interrupt

