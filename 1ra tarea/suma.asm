	BITS 16

start:
	mov ax, 07C0h		; Set up 4K stack space after this bootloader
	add ax, 288		; (4096 + 512) / 16 bytes per paragraph
	mov ss, ax
	mov sp, 4096

	mov ax, 07C0h		; Set data segment to where we're loaded
	mov ds, ax


	;mov si, text_string	; Put string position into SI
	;call print_string	; Call our string-printing routine
	call suma

	jmp $			; Jump here - infinite loop!


	text_string db 'This is my cool new OS!', 0
	msg1     db      'First number: ', 0
	msg2     db      'Second number: ', 0 
	msg3     db      'Total: ', 0
	input1 db ' ', 0
	input2 db ' ', 0
	sum db ' ',0

os_get_cursor_pos:
	pusha

	mov bh, 0
	mov ah, 3
	int 10h				; BIOS interrupt to get cursor position

	mov [.tmp], dx
	popa
	mov dx, [.tmp]
	ret


	.tmp dw 0

reset_cursor:
	call os_get_cursor_pos
	inc dh
	mov dl, 0
	mov bh, 0
	mov ah, 2
	int 10h	
	ret

suma:
	;print Number1
    mov si, msg1
    call print_string

    ;get n1
    mov ah,0h   ;get character from keyboard
	int 16h     ;and store it in AL
	mov [input1], al
	mov si, input1
	call print_string
	;mov ah,0eh  ;Display a character in AL
	;int 10h     ;aka, echo int
    ;mov di, input1
    ;call os_input_string

    ;print Number2
    call reset_cursor
    mov si, msg2
    call print_string

    ;get n2
    mov ah,0h   ;get character from keyboard
	int 16h     ;and store it in AL
	mov [input2], al
	mov si, input2
	call print_string
	;mov ah,0eh  ;Display a character in AL
	;int 10h     ;aka, echo int
	
    ;mov di, input2
    ;call os_input_string

    ;print Sum
    call reset_cursor
    mov si, msg3
    call print_string

    ;sum
    mov ax, [input1]
    sub ax, 48
    mov bx, [input2]
    sub bx, 48
    add ax, bx
    add ax, 48
    mov [sum], ax

    ;print the result
    mov si, sum
    call print_string

    call reset_cursor

    mov ax, [sum]
    cmp ax, 48
    jnz suma

    ret


print_string:			; Routine: output string in SI to screen
	mov ah, 0Eh		; int 10h 'print char' function

.repeat:
	lodsb			; Get character from string
	cmp al, 0
	je .done		; If char is zero, end of string
	int 10h			; Otherwise, print it
	jmp .repeat

.done:
	ret


	times 510-($-$$) db 0	; Pad remainder of boot sector with 0s
	dw 0xAA55		; The standard PC boot signature


	;%include 'input.asm'