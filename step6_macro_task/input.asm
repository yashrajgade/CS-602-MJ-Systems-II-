%macro mysub 3
    mov eax, %1
    mov ebx, %2
    sub eax, ebx
    mov %3, eax
%endmacro

%macro mymul 3
    mov eax, %1
    mov ebx, %2
    mul ebx
    mov %3, eax
%endmacro

%macro myadd 3
    mov eax, %1
    mov ebx, %2
    add eax, ebx
    mov %3, eax
%endmacro

section .text
global main

main:
    mysub 3,4,ecx
    mymul 5,2,esi
    myadd 9,10,edi
    mymul 15,12,edx
    ret
