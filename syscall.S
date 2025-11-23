section .text
    global syscall3          ; Export syscall3
    global syscall6          ; Export syscall6

; syscall3(number, arg1, arg2, arg3)
; Used by basicIO for input/output
syscall3:
    mov rax, rdi             ; syscall number
    mov rdi, rsi             ; arg1
    mov rsi, rdx             ; arg2
    mov rdx, rcx             ; arg3
    syscall
    ret

; syscall6(number, arg1, arg2, arg3, arg4, arg5, arg6)
global syscall6
syscall6:
    mov rax, rdi             ; syscall number
    mov rdi, rsi             ; arg1
    mov rsi, rdx             ; arg2
    mov rdx, rcx             ; arg3
    mov r10, r8              ; arg4
    mov r8, r9               ; arg5
    mov r9, [rsp + 8]        ; arg6 (passed through stack)
    syscall
    ret

; Generic syscall entry
global syscall
syscall:
    jmp syscall6

section .note.GNU-stack noalloc noexec nowrite progbits
