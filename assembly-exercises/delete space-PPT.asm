;delete space key
DATA SEGMENT
    STRING DB 'Let us have a try !','$'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA
start:
    MOV AX,DATA
    MOV DS,AX
	
	mov si,offset string
outlp:	
    cmp byte ptr [di],'$'       ;��ѭ�������жϺ�ѭ��
	jz done	                    ;Ϊ$����
	cmp byte ptr [si],' '       ;����Ƿ��ǿո�
	jnz next	                ;���ǿո����ѭ��         
    mov di,si	                ;�ǿո񣬽����޳��ո��֧
inlp: 
    inc di
	mov al,[di]	                ;ǰ��һ��λ��
	mov [di-1],al
	cmp byte ptr [di],'$'       ;��ѭ������ѭ�����ж�
	jnz inlp
	jmp outlp
next:    
    inc si	                    ;�����Ժ����ַ����д���
	jmp outlp
done:    
    MOV AH,4CH
    INT 21H
CODE ENDS
    END START
