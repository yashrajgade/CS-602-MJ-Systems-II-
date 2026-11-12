


section .text
global main

main:
    mov eax, 3
    mov ebx, 4
    sub eax, ebx
    mov ecx, eax
    mov eax, 5
    mov ebx, 2
    mul ebx
    mov esi, eax
    mov eax, 9
    mov ebx, 10
    add eax, ebx
    mov edi, eax
    mov eax, 15
    mov ebx, 12
    mul ebx
    mov edx, eax
    ret
