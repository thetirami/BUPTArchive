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
    cmp byte ptr [di],'$'       ;外循环，先判断后循环
	jz done	                    ;为$结束
	cmp byte ptr [si],' '       ;检测是否是空格
	jnz next	                ;不是空格继续循环         
    mov di,si	                ;是空格，进入剔除空格分支
inlp: 
    inc di
	mov al,[di]	                ;前移一个位置
	mov [di-1],al
	cmp byte ptr [di],'$'       ;内循环，先循环后判断
	jnz inlp
	jmp outlp
next:    
    inc si	                    ;继续对后续字符进行处理
	jmp outlp
done:    
    MOV AH,4CH
    INT 21H
CODE ENDS
    END START
