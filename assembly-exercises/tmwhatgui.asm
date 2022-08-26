DATA SEGMENT
    ASCII DB 30h,31h,32h,33h,34h,35h,36h,37h,38h,39H,41h,42h,43h,44h,45h,46h	            
    hex	db 24h,6bh                                  ;假设两个数据
DATA ENDS

STACK SEGMENT STACK
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,ES:EDATA,SS:STACK
    
START: 
    MOV AX,DATA
    MOV DS,AX
    MOV BX, offset ASCII    ;比下一句快。。。。功能是一样的
    ;LEA BX,ASCII           ;BX指向ASCII码表
    
    MOV AL,hex              ;AL取得一位16进制数，
                            ;恰好就是ASCII码表中的位移
    AND AL,0Fh              ;只有低4位是有效的，高4位清0
    XLAT                    ;换码：AL←DS:[BX＋AL] 
    MOV DL,AL               ;入口参数：DL←AL
    MOV AH,2	            ;02号DOS功能调用
    INT 21H	                ;显示一个ASCII码字符
    
    MOV AL,hex+1	        ;转换并显示下一个数据
    AND AL,0Fh
    XLAT
    MOV DL,AL
    MOV AH,2
    INT 21H  
    
    MOV AH,4CH
    INT 21H

CODE ENDS
    ENDS START
