;编程把4位组合BCD码转换为二进制数。

; (千位数×10＋百位数)×10＋十位数)×10＋个位数
;=千位数×1000＋百位数×100＋十位数×10＋个位数

;×10采用子程序设计(入口参数、出口参数均为AX)

;千位数、百位数、十位数、个位数如何取得？

DATA SEGMENT
    BCDNUM DW 1968H
    BINNUM DW ?
DATA ENDS 

STACK SEGMENT STACK
STACK ENDS 

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,SS:STACK
START:
    MOV AX,DATA
    MOV DS,AX
    
    MOV AX,BCDNUM	    ;取BCD码
    MOV BX,AX
    MOV DX,AX	        ;暂存至BX、DX中
    AND AX,0F000H
    MOV CL,12
    SHR AX,CL	        ;取千位数
    CALL MUL10	        ;千位数×10 ? AX
    AND BX,0F00H
    MOV CL,8
    SHR BX,CL	        ;取百位数
    ADD AX,BX	        ;千位数×10 ＋百位数? AX
    CALL MUL10          ;（千位数×10 ＋百位数）×10 ? A
    MOV BX,DX
    AND BX,00F0H
    MOV CL,4
    SHR BX,CL		    ;取十位数
    ADD AX,BX           ;（千位数×10 ＋百位数）×10＋十位数 ? AX
    CALL MUL10
    MOV BX,DX
    AND BX,000FH	    ;取个位数
    ADD AX,BX
    MOV BINNUM, AX
    
    MOV AH,4CH
    INT 21H

MUL10 PROC               ;移位3次=8倍，加上移位1次=2倍，等于乘10
    PUSH BX
    SHL AX,1
    MOV BX,AX
    SHL AX,2
    ADD AX,BX
    POP BX
    RET
MUL10 ENDP

CODE ENDS
    END START