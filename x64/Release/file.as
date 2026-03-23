; =========================
; FULL FEATURE TEST FILE
; =========================


; ----- data -----
DATA1: .data 5, -3, 15, 0
STR1:  .string "hello"
MAT1:  .mat [2][3] 1,2,3,4,5,6

; ----- extern -----
.extern EXT_FUNC
.extern EXT_VAR

; ----- entry -----
.entry MAIN

; =========================
; CODE
; =========================

MAIN:      mov r3, r1          
           add #5, r2         
           sub DATA1, r3       

           lea STR1, r4      
           clr r5            
           not r5
           inc r5
           dec r5

           jmp LOOP          
           bne END             

           jsr EXT_FUNC        

           prn #100          
           prn r3              

           red r6            

           cmp r1, r2          
           cmp #10, r3
           cmp DATA1, r4

; ----- matrix usage -----
           mov MAT1[r1][r2], r3
           add r3, MAT1[r2][r1]

; ----- macro usage -----

LOOP:      add #1, r1
           cmp #10, r1
           bne LOOP

END:       stop

; ----- another label usage -----
FUNC:      mov r1, r2
           rts

; ----- entry reference -----
.entry FUNC