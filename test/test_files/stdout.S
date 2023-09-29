        .section .text
        .global _start
_start:
        mov r0, #1
        adr r1, msg
        mov r2, #len
        svc #4          // syscall write(fd, buf, count)

        mov r0, #0
        svc #1          // syscall exit(status)

msg:
        .ascii "Hello!\n"
len = . - msg
