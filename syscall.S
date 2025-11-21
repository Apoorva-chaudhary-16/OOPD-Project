section .text
    global syscall3  ; Export syscall3 function
    global syscall6  ; Export syscall6 function
    
    ; We have removed the _start section.
    ; The C++ standard library will provide the program's entry point.

syscall3:
    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx
    syscall
    ret

global syscall6

syscall6:
    mov rax, rdi      ; syscall number
    mov rdi, rsi      ; arg1
    mov rsi, rdx      ; arg2
    mov rdx, rcx      ; arg3
    mov r10, r8       ; arg4
    mov r8, r9        ; arg5
    mov r9, [rsp+8]   ; arg6 (from stack)
    syscall
    ret


global syscall
syscall:
    jmp syscall6


section .note.GNU-stack noalloc noexec nowrite progbits