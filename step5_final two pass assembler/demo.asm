global main

section .data
    Arr dd 60,11,56
    a dd 20,28,55
    num dd 10
    name db "yash",10,0
    message db "hello",10,0
    grade db 'A'

section .text

main:
    mov eax, ebx
    mov eax, 10
    mov eax, [ebx]
    add eax, ebx
    sub eax, ebx
