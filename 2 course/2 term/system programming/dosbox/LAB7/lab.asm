; ������ୠ� ࠡ�� �7
; ���襢 �.�. ��5-41 ���. 20
;===============================================================================

prgr SEGMENT
                        ASSUME CS:prgr

     BEGIN:             
                        JMP    MAIN

; ����饭�� � �����
     help_message       DB     '���襢 ����䥩 ��5-41� ���� 20$'
     buffer             DB     256 DUP(0)
     flag_var           DB     0
     input_message      DB     '������ �᫮ (������ ����: ����:����)> $'
     digits             DW     10000,1000,100,10,1
     hex_digits         DB     '0123456789ABCDEF$'

MAIN PROC
                        CALL   CLRSCR
     main_loop:         
                        MOV    AH,09H         ; �뢮� ᮮ�饭�� � ����� �᫠
                        MOV    DX,OFFSET input_message
                        INT    21H

                        call   INPUT          ; ���� �᫠
                        cmp    flag_var,1
                        je     main_exit
                        push   BX

                        mov    dl,'='         ; �뢮� ᨬ���� "="
                        call   PUTCH

                        mov    dx,bx          ; �뢮� �᫠ � ��⭠����筮� ����
                        call   HEX_WRITE

                        mov    dl,' '         ; �뢮� �஡���
                        call   PUTCH

                        pop    BX
                        call   HEX_TO_DECIMAL ; �뢮� �᫠ � �����筮� ����

                        call   CLRF           ; ���室 �� ����� ��ப�
                        MOV    CX,2           ; ��⠢襥�� ������⢮ ���権
                        LOOP   main_loop

     main_exit:         
                        MOV    AH,09H         ; �뢮� ᮮ�饭�� � �����
                        MOV    DX,OFFSET help_message
                        INT    21H
                        CALL   GETCH
                        CALL   CLRSCR
                        CALL   QUIT_PROGRAM
MAIN ENDP

; ��楤�� ����� �᫠
INPUT PROC
                        mov    bp,0           ; ���樠������ ���稪�
                        mov    bx,0           ; ���樠������ १����
     in_loop:           
                        call   GETCH_NON_BLOCKING ; ����祭�� ᨬ����
                        mov    dl,al
                        jmp    check

     shifting:          
                        call   PUTCH         ; �뢮� ᨬ����
                        pop    ax            ; ����祭�� ᨬ���� �� �⥪�
                        mov    ah,0
                        shl    bx, 4         ; ����� १���� �� 4 ��� �����

                        add    bx,ax         ; ���������� ����� ���� � १�����
                        inc    bp            ; ���६��� ���稪�
                        cmp    bp,4          ; �஢�ઠ ������⢠ ��������� ���
                        je     exit          ; �᫨ ������� 4 ����, ��室
                        jmp    in_loop

     check:             
                        cmp    al,'*'        ; �஢�ઠ �� ᨬ��� �����襭�� �����
                        jne    numder        ; �᫨ �� "*", ��ࠡ�⪠ �ᥫ
                        mov    flag_var,1    ; ��⠭���� 䫠�� �����襭�� �����
                        jmp    exit

     numder:            
                        cmp    al,'0'        ; �஢�ઠ �� ����
                        jb     big_case      ; �᫨ ����� "0", ���室 � ��ࠡ�⪥ ������ ᨬ�����

                        cmp    al,'9'        ; �஢�ઠ �� ����
                        ja     big_case      ; �᫨ ����� "9", ���室 � ��ࠡ�⪥ ������ ᨬ�����

                        sub    al,'0'        ; �८�ࠧ������ ᨬ���� � �᫮
                        push   ax            ; ������ �᫠ � �⥪
                        jmp    shifting      ; ���室 � ᤢ���

     big_case:          
                        cmp    al,'A'        ; �஢�ઠ �� ᨬ��� �� "A" �� "F"
                        jb     small_case    ; �᫨ ����� "A", ���室 � ��ࠡ�⪥ �����쪨� ᨬ�����

                        cmp    al,'F'        ; �஢�ઠ �� ᨬ��� �� "A" �� "F"
                        ja     small_case    ; �᫨ ����� "F", ���室 � ��ࠡ�⪥ �����쪨� ᨬ�����

                        sub    al,'A'-10     ; �८�ࠧ������ ᨬ���� � �᫮
                        push   ax            ; ������ �᫠ � �⥪
                        jmp    shifting      ; ���室 � ᤢ���

     small_case:        
                        cmp    al,'a'        ; �஢�ઠ �� ᨬ��� �� "a" �� "f"
                        jb     in_loop       ; �᫨ ����� "a", �த������� �����

                        cmp    al,'f'        ; �஢�ઠ �� ᨬ��� �� "a" �� "f"
                        ja     in_loop       ; �᫨ ����� "f", �த������� �����

                        sub    al,'a'-10     ; �८�ࠧ������ ᨬ���� � �᫮
                        push   ax            ; ������ �᫠ � �⥪
                        jmp    shifting      ; ���室 � ᤢ���

     exit:              
                        ret
INPUT ENDP

; ��楤�� �뢮�� �᫠ � ��⭠����筮� ����
HEX PROC
                        push   ds
                        push   ax
                        push   bx
                        push   cx
                        push   cs
                        pop    ds

                        lea    bx,hex_digits
                  
                        mov    al,dh
                        shr    al, 4
                        xlat
                        push   dx
                        mov    dl,al
                        mov    ah,02h
                        int    21h

                        mov    al,dh
                        and    al,00001111b
                        xlat
                        mov    dl,al
                        mov    ah,02h
                        int    21h

                        pop    dx
                        pop    cx
                        pop    bx
                        pop    ax
                        pop    ds
                        ret
HEX ENDP

; ��楤�� �뢮�� �᫠ � ��⭠����筮� ����, � ��᫥���騬 "h"
HEX_WRITE PROC
                        push   dx
                        call   HEX
                        pop    dx
                        mov    dh,dl
                        call   HEX
                        mov    dl,'h'
                        int    21h
                        ret
HEX_WRITE ENDP

; ��楤�� �८�ࠧ������ ��⭠����筮�� �᫠ � �����筮�
HEX_TO_DECIMAL PROC
                        mov    ax,bx
                        mov    di,0
     hex_loop:          
                        mov    dx,0
                        mov    bx,digits[di]
                        div    bx
                        push   dx
                        add    ax,'0'
                        mov    dl,al
                        call   PUTCH
                        pop    ax
                        inc    di
                        inc    di
                        cmp    di,10
                        jb     hex_loop
                        RET
HEX_TO_DECIMAL ENDP

; ��楤�� �뢮�� ᨬ����
PUTCH PROC
                        mov    ah,2
                        int    21h
                        ret
PUTCH ENDP

; ��楤�� ����祭�� ᨬ����
GETCH PROC
                        mov    ah,1
                        int    21h
                        ret
GETCH ENDP

; ��楤�� ����祭�� ᨬ���� ��� �����஢��
GETCH_NON_BLOCKING PROC
                        mov    ah,8
                        int    21h
                        ret
GETCH_NON_BLOCKING ENDP

; ��楤�� ���室� �� ����� ��ப�
CLRF PROC
                        mov    dl,10
                        call   PUTCH
                        mov    dl,13
                        call   PUTCH
                        ret
CLRF ENDP

; ��楤�� ���⪨ �࠭�
CLRSCR PROC
                        mov    ah,00
                        mov    al,03
                        int    10h
                        RET
CLRSCR ENDP

; ��楤�� �����襭�� �ணࠬ��
QUIT_PROGRAM PROC
                        mov    ah,4ch
                        mov    al,00h
                        int    21h
QUIT_PROGRAM ENDP

prgr ENDS
END BEGIN
