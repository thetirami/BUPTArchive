;输出最大值
DATA SEGMENT
    ARRAY DW 10
          DW 1,54,12,-32,24,5,2,-1,-10,12
    MAX DW ?
    MIN DW ?
    I DW 0000H
DATA ENDS

STACK SEGMENT STACK
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,ES:EDATA,SS:STACK
START:
    MOV AX,DATA              
    MOV DS,AX
    
    MOV CX,ARRAY
    DEC CX
    
    LEA SI,ARRAY;SI is the address to ARRAY
                ;change SI can be an easy way to access elems
    
    MOV AX,[SI]+2;assume the first the GREATEST
    MOV BX,[SI]+2;assume the first the LEAST
 
AGAIN:   
    ADD SI,2
    CMP AX,[SI]
    JGE DONE1
    MOV AX,[SI]
DONE1:
    CMP BX,[SI]
    JLE DONE2  
    MOV BX,[SI]
DONE2:
    LOOP AGAIN   
    
    MOV MAX,AX
    MOV MIN,BX
      
    MOV CX,16
OUTPUTMAX:
    SHL MAX,1
    MOV DL,0
    ADC DL,30H
    MOV AH,02H
    INT 21H
    LOOP OUTPUTMAX 
    
    MOV DL,13
    MOV AH,02H
    INT 21H
    MOV DL,10
    INT 21H
    
    MOV CX,16
OUTPUTMIN:
    SHL MIN,1
    MOV DL,0
    ADC DL,30H
    MOV AH,02H
    INT 21H
    LOOP OUTPUTMIN
    
    MOV AH,4CH
    INT 21H

CODE ENDS
    END START
