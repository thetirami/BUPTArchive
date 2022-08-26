;(V-(X*Y＋Z-540))/X
DATA SEGMENT
    X DW 0010H		
    Y DW 0123H
    Z DW 7890H
    V DW 3456H
    QR DW ?         ;存放商
    REMAINDER DW ?  ;存放余数
DATA ENDS 

STACK SEGMENT STACK
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,SS:STACK
START:
    MOV AX,DATA
    MOV DS,AX 	        ;初始化DS
    
    MOV AX,X 	        ;AX←X
    IMUL Y		        ;DX：AX←X*Y
    MOV CX,AX		
    MOV BX,DX	        ;暂存在BX，CX中,人家的解是DX:AX
    MOV AX,Z		
    CWD	                ;Z扩展 ，默认dx是ax的高位
    ADD CX,AX
    ADC BX,DX	        ;BX：CX←X*Y＋Z 这些都是两个寄存器表示一个数的加法       
    SUB CX,540
    SBB BX,0	        ;可能有借位
    MOV AX,V		
    CWD		            ;扩展V
    SUB AX,CX
    SBB DX,BX
    IDIV X
    MOV QR,AX 		    ;保存商
    MOV REMAINDER,DX	;保存余数      
    
    MOV AH,4CH
    INT 21H	            ;程序结束，返回到DOS
CODE ENDS               ;码段结束
    END START	        ;结束汇编，指定程序入口地址                           
