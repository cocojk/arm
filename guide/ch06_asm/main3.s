;// ____________________________________________________________________
;//
;// Copyright (c) 2002, Andrew N. Sloss, Dominic Symes, Chris Wright
;// All rights reserved.
;// ____________________________________________________________________
;// 
;// NON-COMMERCIAL USE License
;// 
;// Redistribution and use in source and binary forms, with or without 
;// modification, are permitted provided that the following conditions 
;// are met: 
;//
;// 1. For NON-COMMERCIAL USE only.
;// 
;// 2. Redistributions of source code must retain the above copyright 
;//    notice, this list of conditions and the following disclaimer. 
;//
;// 3. Redistributions in binary form must reproduce the above 
;//    copyright notice, this list of conditions and the following 
;//    disclaimer in the documentation and/or other materials provided 
;//    with the distribution. 
;//
;// 4. All advertising materials mentioning features or use of this 
;//    software must display the following acknowledgement:
;//
;//    This product includes software developed by Andrew N. Sloss,
;//    Chris Wright and Dominic Symes. 
;//
;//  THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
;//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
;//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
;//  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
;//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
;//  OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
;//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
;//  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
;//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
;//  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
;//  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
;//  OF SUCH DAMAGE. 
;//
;// If you have questions about this license or would like a different
;// license please email : andrew@sloss.net
;//

        AREA    |.text|, CODE, READONLY
                
        EXPORT  main
        
        IMPORT  |Lib$$Request$$armlib|, WEAK
        IMPORT  __main      ; C library entry
        IMPORT  printf      ; prints to stdout
        
i       RN 4
        
        ; int main(void)
main
        STMFD   sp!, {i, lr}
        MOV     i, #0
loop
        ADR     r0, print_string
        MOV     r1, i
        MUL     r2, i, i
        BL      printf
        ADD     i, i, #1
        CMP     i, #10
        BLT     loop
        LDMFD   sp!, {i, pc}
        
print_string
        DCB     "Square of %d is %d\n", 0
        
        END
