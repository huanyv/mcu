ORG 00H

START:
    MOV A,#0FFH ;A�����ۼ���ACC?? ? ���������ȫϨ��1111 1111
	CLR C      ;C�����λ����״̬���б�־λCY?? ??? ?��C����? CY = 0
	MOV R1 ,#8

LEFT:
	RLC  A    ;����λCY��ACC(8λ/��9λ����8Ϊ����ѭ��)������
	MOV  P2,A
	CALL DELAY
	DJNZ R1,LEFT
	MOV  R2,#7

RIGHT:
	RRC  A    ;����λCY��ACC(8λ/��9λ)������
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
	DJNZ R5,$ ;R5��1����Ϊ0����ִ�б���
	DJNZ R4,D2;R4��1����Ϊ0������ת��D2��ŵĳ���ʼ��
	DJNZ R3,D1;R3��1����Ϊ0������ת��D1��ŵĳ���ʼ��
	RET
	END