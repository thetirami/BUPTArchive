;What is the top bit?

DATA SEGMENT   
DATA ENDS

STACK SEGMENT STACK
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,ES:EDATA,SS:STACK
START:
    MOV AX,DATA
    MOV DS,AX
    
    MOV DX,0EEAEH
    SHL DX,1 
    MOV DL,0H
    ADC DL,30H
    MOV AH,02H
    INT 21H
    
    MOV AH,4CH
    INT 21H
CODE ENDS
    END START
    