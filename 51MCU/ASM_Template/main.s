ORG 00H

START:
    MOV A,#0FFH ;A代表累加器ACC?? ? 发光二极管全熄灭1111 1111
	CLR C      ;C代表进位程序状态字中标志位CY?? ??? ?将C清零? CY = 0
	MOV R1 ,#8

LEFT:
	RLC  A    ;带进位CY在ACC(8位/共9位，以8为周期循环)中左移
	MOV  P2,A
	CALL DELAY
	DJNZ R1,LEFT
	MOV  R2,#7

RIGHT:
	RRC  A    ;带进位CY在ACC(8位/共9位)中右移
	MOV  P2,A
	CALL DELAY
	DJNZ R2,RIGHT
	JMP  START

DELAY:
	MOV R3,#200
D1:
	MOV R4,#30
D2:
	MOV  R5,#20
	DJNZ R5,$ ;R5减1，不为0，则执行本行
	DJNZ R4,D2;R4减1，不为0，则跳转到D2标号的程序开始处
	DJNZ R3,D1;R3减1，不为0，则跳转到D1标号的程序开始处
	RET
	END