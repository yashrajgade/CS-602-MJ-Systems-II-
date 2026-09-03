global main

section .data
    num dd 10

section .text

main:
    mav eax, ebx
    mov eax, 10
    mov eax, [ebx]
    add eax, ebx
    xyz eax, ebx
