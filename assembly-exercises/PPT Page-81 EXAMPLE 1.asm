;(V-(X*Y��Z-540))/X
DATA SEGMENT
    X DW 0010H		
    Y DW 0123H
    Z DW 7890H
    V DW 3456H
    QR DW ?         ;�����
    REMAINDER DW ?  ;�������
DATA ENDS 

STACK SEGMENT STACK
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,SS:STACK
START:
    MOV AX,DATA
    MOV DS,AX 	        ;��ʼ��DS
    
    MOV AX,X 	        ;AX��X
    IMUL Y		        ;DX��AX��X*Y
    MOV CX,AX		
    MOV BX,DX	        ;�ݴ���BX��CX��,�˼ҵĽ���DX:AX
    MOV AX,Z		
    CWD	                ;Z��չ ��Ĭ��dx��ax�ĸ�λ
    ADD CX,AX
    ADC BX,DX	        ;BX��CX��X*Y��Z ��Щ���������Ĵ�����ʾһ�����ļӷ�       
    SUB CX,540
    SBB BX,0	        ;�����н�λ
    MOV AX,V		
    CWD		            ;��չV
    SUB AX,CX
    SBB DX,BX
    IDIV X
    MOV QR,AX 		    ;������
    MOV REMAINDER,DX	;��������      
    
    MOV AH,4CH
    INT 21H	            ;������������ص�DOS
CODE ENDS               ;��ν���
    END START	        ;������ָ࣬��������ڵ�ַ                           
