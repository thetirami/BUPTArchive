;��0200H��Ԫ��ʼ��100��������һ����������Щ�����������ֲ��䣬������ȡ�����ͻ�
DATA SEGMENT
    ORG 0200H               ;��0200H��ʼ
    STRING DB 100 DUP (?)
DATA ENDS 

STACK SEGMENT STACK
STACK ENDS 

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,ES:DATA,SS:STACK
BEGIN:
    MOV AX,DATA
    MOV DS,AX

    MOV CX,100
    LEA SI,STRING
AGAIN:  
    MOV AL,[SI]
    CMP AL,0
    JGE OVER    ;AL��0��0������OVER
    NEG AL	    ;AL��0����AL��
OVER:   
    MOV [SI],AL
    INC SI
    LOOP AGAIN

    MOV AH,4CH
    INT 21H
CODE ENDS
    END BEGIN