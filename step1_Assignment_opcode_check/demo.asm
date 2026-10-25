global main

section .data
    num dd 10
    name db "yash",10,0
    message db "hello",10,0
    grade db 'A'

section .text

main:
    mav eax, ebx
    mov eax, 10
    mov eax, [ebx]
    add eax, ebx
    xyz eax, ebx
