        .section .text
        .global _start
_start:
        mov r0, #1
        adr r1, msg
        mov r2, #len
        mov r7, #4      // syscall write(fd, buf, count)
        svc #0

        mov r0, #0
        mov r7, #1      // syscall exit(status)
        svc #0

msg:
        .ascii "Hello!\n"
len = . - msg
