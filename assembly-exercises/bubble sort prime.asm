DATA SEGMENT 
    ARRAY DB 20 DUP(127)
    LEN DB 0
    CHOICE DB 0
    MSG1 DB 'Please input the length(no more than 20):','$'
    MSG2 DB 'The value input is illegal, please input a new one:','$'
    MSG3 DB 'You will get a random sequence, and the length is ','$'
    MSG4 DB '-----Menu-----','$'
    MSG5 DB '1 - Show the sequence','$'
    MSG6 DB '2 - Sort','$'
    MSG7 DB '3 - Exit','$'
    MSG8 DB 'Input your choice:','$'
    MSG9 DB '----Goodbye----','$' 
    MSG10 DB ' in binary.','$'
    MSG11 DB 'Sort complete!','$'
DATA ENDS

STACK SEGMENT STACK
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,ES:EDATA,SS:STACK
START:
    MOV AX,DATA
    MOV DS,AX

;MACRO DEFINETION
SHOWMSG MACRO MSG
    LEA DX,MSG 
    MOV AH,09H
    INT 21H
ENDM 

NEWL MACRO
    MOV AH,02H
    MOV DL,13
    INT 21H
    MOV DL,10
    INT 21H
ENDM

PRINTC MACRO CHAR
    MOV AH,02H
    MOV DL,CHAR
    INT 21H
ENDM
;MACRO ENDS    
        
    SHOWMSG MSG1        ;BEGIN
    
    CALL INPROC         ;GET LENGTH (1-20)
    CMP BL,20
    JG ERRI1
    CMP BL,0
    JLE ERRI1
    JMP NEXT1
ERRI1:
    NEWL
    SHOWMSG MSG2
    CALL INPROC
    CMP BL,20
    JG ERRI1
    CMP BL,0
    JLE ERRI1
NEXT1:
    MOV LEN,BL          ;SAVE LEN
    NEWL   
    SHOWMSG MSG3
    CALL OUTPUTBL
    SHOWMSG MSG10 
    
    LEA SI,ARRAY        ;GENERATE RANDOM SEQ 
    MOV CH,0
    MOV CL,LEN
SET:
    CALL RAND
    MOV [SI],BL
    INC SI
    LOOP SET
OPERATION:
    NEWL    
    NEWL
    SHOWMSG MSG4        ;SHOW INFO
    NEWL
    SHOWMSG MSG5
    NEWL
    SHOWMSG MSG6
    NEWL
    SHOWMSG MSG7
    NEWL
    SHOWMSG MSG8
    
    CALL INPROC         ;EXAMINE IF 123 OR NOT
    CMP BL,3
    JG ERRI2
    CMP BL,1
    JL ERRI2
    JMP NEXT2
ERRI2:
    NEWL
    SHOWMSG MSG2
    CALL INPROC
    CMP BL,3
    JG ERRI2
    CMP BL,1
    JL ERRI2
NEXT2:   
    MOV CHOICE,BL
    CMP CHOICE,3
    JZ ENDING
    CMP CHOICE,1
    JZ OP1
    CMP CHOICE,2
    JZ OP2
OP1: 
    NEWL
    CALL OUTPUTSEQ
    JMP ENDTHIS
OP2: 
    CALL SORT
    NEWL
    SHOWMSG MSG11
ENDTHIS:     
    LOOP OPERATION
        
ENDING:
    NEWL   
    SHOWMSG MSG9
    MOV AH,4CH
    INT 21H

INPROC PROC  
    MOV BL,0  
LOP1: 
    MOV AH,01  
    INT 21H  
    CMP AL,20H ;空格完成输入 
    JZ EXIT  
    CMP AL,0DH ;回车完成输入 
    JZ EXIT
    SUB AL,30H ;调用1号中断后存放在al寄存器的是输入字符的ASCSII,  
               ;必须减去30H或37H(十六进制中ABCDEF等字符)  
    XCHG AL,BL  
    MOV BH,10  
    MUL BH  
    ADD BL,AL  
    JMP LOP1  
EXIT: 
    RET  
INPROC ENDP

OUTPUTBL PROC
    PUSH CX 
    PUSH DX
    PUSH BX
    
    MOV CX,8
GO:
    MOV DL,0
    SHL BL,1
    ADC DL,30H   
    PRINTC DL
    LOOP GO
    POP CX 
    POP DX
    POP BX
    RET
OUTPUTBL ENDP    
    
RAND  PROC
    PUSH CX
    PUSH DX
    PUSH AX
    STI                  ;开中断，允许硬件中断
    MOV AH,0             ;读时钟计数器值
    INT 1AH
    MOV AX,DX            
    ;AND AH,3
    MOV DL,128           ;除128，产生0~128余数
    DIV DL
    MOV BL,AH            ;余数存BX，作随机数
    SUB BL,64
    POP AX
    POP DX
    POP CX
    RET
RAND  ENDP    

OUTPUTSEQ PROC
    PUSH BX  
    PUSH CX
    PUSH DX
    
    LEA SI,ARRAY
    MOV CH,0
    MOV CL,LEN
OUTL:
    PUSH CX
    MOV BL,[SI]
    
    MOV CX,8
INL:    
    SHL BL,1
    MOV DL,0
    ADC DL,30H
    MOV AH,02H
    INT 21H
    LOOP INL
    
    POP CX
    INC SI
    PRINTC 13
    PRINTC 10
    LOOP OUTL
    
    POP BX  
    POP CX
    POP DX
    RET
OUTPUTSEQ ENDP 

SORT PROC
    PUSH CX
    PUSH AX
    
    MOV CH,0
    MOV CL,LEN
OUTS:    
    LEA SI,ARRAY
    PUSH CX
        MOV CH,0    
        MOV CL,LEN;-1
        DEC CL
    INTER:   
        MOV AL,[SI]
        CMP AL,[SI+1]
        JGE HAHA 
        XCHG AL,[SI+1] 
        MOV [SI],AL
    HAHA:        
        INC SI
        LOOP INTER        
    POP CX
    LOOP OUTS
    
    POP CX
    POP AX
    RET
SORT ENDP

CODE ENDS
    END START
