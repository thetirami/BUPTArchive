;��̰�4λ���BCD��ת��Ϊ����������

; (ǧλ����10����λ��)��10��ʮλ��)��10����λ��
;=ǧλ����1000����λ����100��ʮλ����10����λ��

;��10�����ӳ������(��ڲ��������ڲ�����ΪAX)

;ǧλ������λ����ʮλ������λ�����ȡ�ã�

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
    
    MOV AX,BCDNUM	    ;ȡBCD��
    MOV BX,AX
    MOV DX,AX	        ;�ݴ���BX��DX��
    AND AX,0F000H
    MOV CL,12
    SHR AX,CL	        ;ȡǧλ��
    CALL MUL10	        ;ǧλ����10 ? AX
    AND BX,0F00H
    MOV CL,8
    SHR BX,CL	        ;ȡ��λ��
    ADD AX,BX	        ;ǧλ����10 ����λ��? AX
    CALL MUL10          ;��ǧλ����10 ����λ������10 ? A
    MOV BX,DX
    AND BX,00F0H
    MOV CL,4
    SHR BX,CL		    ;ȡʮλ��
    ADD AX,BX           ;��ǧλ����10 ����λ������10��ʮλ�� ? AX
    CALL MUL10
    MOV BX,DX
    AND BX,000FH	    ;ȡ��λ��
    ADD AX,BX
    MOV BINNUM, AX
    
    MOV AH,4CH
    INT 21H

MUL10 PROC               ;��λ3��=8����������λ1��=2�������ڳ�10
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