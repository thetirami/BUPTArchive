DATA SEGMENT
    ASCII DB 30h,31h,32h,33h,34h,35h,36h,37h,38h,39H,41h,42h,43h,44h,45h,46h	            
    hex	db 24h,6bh                                  ;������������
DATA ENDS

STACK SEGMENT STACK
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,ES:EDATA,SS:STACK
    
START: 
    MOV AX,DATA
    MOV DS,AX
    MOV BX, offset ASCII    ;����һ��졣������������һ����
    ;LEA BX,ASCII           ;BXָ��ASCII���
    
    MOV AL,hex              ;ALȡ��һλ16��������
                            ;ǡ�þ���ASCII����е�λ��
    AND AL,0Fh              ;ֻ�е�4λ����Ч�ģ���4λ��0
    XLAT                    ;���룺AL��DS:[BX��AL] 
    MOV DL,AL               ;��ڲ�����DL��AL
    MOV AH,2	            ;02��DOS���ܵ���
    INT 21H	                ;��ʾһ��ASCII���ַ�
    
    MOV AL,hex+1	        ;ת������ʾ��һ������
    AND AL,0Fh
    XLAT
    MOV DL,AL
    MOV AH,2
    INT 21H  
    
    MOV AH,4CH
    INT 21H

CODE ENDS
    ENDS START
