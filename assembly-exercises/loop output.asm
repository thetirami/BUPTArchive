DATA SEGMENT 
DATA ENDS

STACK SEGMENT STACK 
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,ES:EDATA,SS:STACK
START:
    MOV AX,DATA
    MOV DS,AX
    MOV CX,8    
    MOV BL,0CEH
AGAIN:
    SHL BL,1
    MOV DL,00H
    ADC DL,30H
    MOV AH,02H
    INT 21H
    LOOP AGAIN
    MOV AH,4CH
    INT 21H
CODE ENDS
    END START