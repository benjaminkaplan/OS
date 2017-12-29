.section .text
    .global main
main:
    mov $100000,%eax
    mov $1,%ebx
    mov $message,%ecx
    mov msglength,%edx
    int  $0x80

    ;mov $1, %eax
    ;mov $50, %ebx
    ;int $0x80
.section .data
    message: .ascii "Hello world!"
    msglength: .word 12
