;----------------------------------------------------------------------------
; ����������ֵ˵��
; ����:
;       DA_  : Descriptor Attribute
;       D    : ���ݶ�
;       C    : �����
;       S    : ϵͳ��
;       R    : ֻ��
;       RW   : ��д
;       A    : �ѷ���
;       ���� : �ɰ���������˼����
;G D 0 AVL 0 0 0 0 P DPL(2λ) DT TYPE(4λ)
;----------------------------------------------------------------------------
DA_32		EQU	4000h	; 32 λ�� 0100 0000 0000 0000

DA_DPL0		EQU	  00h	; DPL = 0 0000 0000
DA_DPL1		EQU	  20h	; DPL = 1 0010 0000
DA_DPL2		EQU	  40h	; DPL = 2 0100 0000
DA_DPL3		EQU	  60h	; DPL = 3 0110 0000
;----------------------------------------------------------------------------
; �洢������������ֵ˵��
;----------------------------------------------------------------------------
DA_DR		EQU	90h	; ���ڵ�ֻ�����ݶ�����ֵ  1001 0000
DA_DRW		EQU	92h	; ���ڵĿɶ�д���ݶ�����ֵ 1001 0010
DA_DRWA		EQU	93h	; ���ڵ��ѷ��ʿɶ�д���ݶ�����ֵ 1001 0011
DA_C		EQU	98h	; ���ڵ�ִֻ�д��������ֵ 1001 1000
DA_CR		EQU	9Ah	; ���ڵĿ�ִ�пɶ����������ֵ 1001 1010
DA_CCO		EQU	9Ch	; ���ڵ�ִֻ��һ�´��������ֵ 1001 1100
DA_CCOR		EQU	9Eh	; ���ڵĿ�ִ�пɶ�һ�´��������ֵ 1001 1110
;----------------------------------------------------------------------------
; ϵͳ������������ֵ˵��
;----------------------------------------------------------------------------
DA_LDT		EQU	  82h	; �ֲ���������������ֵ 1000 0010
DA_TaskGate	EQU	  85h	; ����������ֵ 1000 0101
DA_386TSS	EQU	  89h	; ���� 386 ����״̬������ֵ 1000 1001
DA_386CGate	EQU	  8Ch	; 386 ����������ֵ 1000 1100
DA_386IGate	EQU	  8Eh	; 386 �ж�������ֵ 1000 1110
DA_386TGate	EQU	  8Fh	; 386 ����������ֵ 1000 1111
;----------------------------------------------------------------------------


;----------------------------------------------------------------------------
; ѡ��������ֵ˵��
; ����:
;       SA_  : Selector Attribute


SA_RPL0		EQU	0	; ��00
SA_RPL1		EQU	1	; �� RPL01
SA_RPL2		EQU	2	; ��10
SA_RPL3		EQU	3	; ��11


SA_TIG		EQU	0	; ��TI 0000
SA_TIL		EQU	4	; ��  0100
;----------------------------------------------------------------------------


; �� ------------------------------------------------------------------------------------------------------
;
; ������
; usage: Descriptor Base, Limit, Attr
;        Base:  dd
;        Limit: dd (low 20 bits available)�Ͷ�ʮλ����
;        Attr:  dw (lower 4 bits of higher byte are always 0)���ֽڵĵ���λʼ��Ϊ0
%macro Descriptor 3 ;�ν���Ϊ�͵�ַ 1����Base 2����Limit 3�������� 
	dw	%2 & 0FFFFh				; �ν��� 1				(2 �ֽ�)
	dw	%1 & 0FFFFh				; ���׵�ַ 1				(2 �ֽ�)
	db	(%1 >> 16) & 0FFh			; ���׵�ַ 2				(1 �ֽ�)
	dw	((%2 >> 8) & 0F00h) | (%3 & 0F0FFh)	; ���� 1 + �ν��� 2 + ���� 2		(2 �ֽ�)
	db	(%1 >> 24) & 0FFh			; ���׵�ַ 3				(1 �ֽ�)
%endmacro ; �� 8 �ֽ�
;
; ��
; usage: Gate Selector, Offset, DCount, Attr
;        Selector:  dw
;        Offset:    dd
;        DCount:    db
;        Attr:      db
%macro Gate 4 ;1����Selector 2����Offset 3����DCount 4����Attr
	dw	(%2 & 0FFFFh)				; ƫ�� 1				(2 �ֽ�)
	dw	%1					; ѡ����				(2 �ֽ�)
	dw	(%3 & 1Fh) | ((%4 << 8) & 0FF00h)	; ����					(2 �ֽ�)
	dw	((%2 >> 16) & 0FFFFh)			; ƫ�� 2				(2 �ֽ�)
%endmacro ; �� 8 �ֽ�