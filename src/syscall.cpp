#include "processor.h"
#include "bus_controller.h"

//
// Interpret Linux syscalls.
//
void Processor::linux_syscall(int op)
{
    switch (op) {
    case 1: // exit
        app_finished = true;
        return;

    case 3: // read
        break;

    case 4: { // write
        unsigned fd = get_reg(0);
        unsigned addr = get_reg(1);
        unsigned len = get_reg(2);
        const unsigned sram_base = 0x00008000;
        const unsigned sram_end  = 0x00080000;

        // Make sure arguments are reasonable.
        if (fd == 1 && len > 0 && len <= 10000 && addr >= sram_base && (addr+len) <= sram_end) {
            write_stdout(addr, len);
            set_reg(0, len);
        } else {
            set_reg(0, -1);
        }
        return;
    }
    case 5: // open
        break;

    case 6: // close
        break;

    case 9: // link
        break;

    case 10: // unlink
        break;

    case 11: // execve
        break;

    case 12: // chdir
        break;

    case 14: // mknod
        break;

    case 15: // chmod
        break;

    case 16: // lchown
        break;

    case 19: // lseek
        break;

    case 20: // getpid
        break;

    case 23: // setuid
        break;

    case 24: // getuid
        break;

    case 25: // stime
        break;

    case 27: // alarm
        break;

    case 29: // pause
        break;

    case 30: // utime
        break;

    case 36: // sync
        break;

    case 37: // kill
        break;

    case 39: // mkdir
        break;

    case 40: // rmdir
        break;

    case 41: // dup
        break;

    case 42: // pipe
        break;

    case 43: // times
        break;

    case 45: // brk
        break;

    case 46: // setgid
        break;

    case 47: // getgid
        break;

    case 49: // geteuid
        break;

    case 50: // getegid
        break;

    case 54: // ioctl
        break;

    case 55: // fcntl
        break;

    case 57: // setpgid
        break;

    case 60: // umask
        break;

    case 63: // dup2
        break;

    case 65: // getpgrp
        break;

    case 66: // setsid
        break;

    case 78: // gettimeofday
        break;

    case 80: // getgroups
        break;

    case 82: // select
        break;

    case 83: // symlink
        break;

    case 85: // readlink
        break;

    case 88: // reboot
        break;

    case 92: // truncate
        break;

    case 93: // ftruncate
        break;

    case 102: // socketcall
        break;

    case 106: // stat
        break;

    case 107: // lstat
        break;

    case 108: // fstat
        break;

    case 114: // wait4
        break;

    case 116: // sysinfo
        break;

    case 122: // uname
        break;

    case 126: // sigprocmask
        break;

    case 132: // getpgid
        break;

    case 141: // getdents
        break;

    case 162: // nanosleep
        break;

    case 182: // chown
        break;

    case 190: // vfork
        break;

    default:
        terminate_simulation("Unsupported syscall");
    }

    // Return -1 by default.
    set_reg(0, -1);
}

//
// Write data from memory to stdout.
//
void Processor::write_stdout(unsigned addr, unsigned nbytes)
{
    if (addr & 1) {
        write8_stdout(addr, nbytes);
    }
    if ((addr & 2) && nbytes >= 2) {
        write16_stdout(addr, nbytes);
        if (nbytes == 0)
            return;
    }
    while (nbytes >= 4) {
        write32_stdout(addr, nbytes);
        if (nbytes == 0)
            return;
    }
    if (nbytes >= 2) {
        write16_stdout(addr, nbytes);
        if (nbytes == 0)
            return;
    }
    if (nbytes >= 1) {
        write8_stdout(addr, nbytes);
    }
}

//
// Write one byte to stdout.
//
void Processor::write8_stdout(unsigned &addr, unsigned &nbytes)
{
    char c = data_read8(addr);
    addr += 1;
    nbytes -= 1;
    put_char(c);
}

//
// Write two bytes to stdout.
//
void Processor::write16_stdout(unsigned &addr, unsigned &nbytes)
{
    unsigned h = data_read16(addr);
    addr += 2;
    nbytes -= 2;
    put_char(h);
    put_char(h >> 8);
}

//
// Write four bytes to stdout.
//
void Processor::write32_stdout(unsigned &addr, unsigned &nbytes)
{
    unsigned w = data_read32(addr);
    addr += 4;
    nbytes -= 4;
    put_char(w);
    put_char(w >> 8);
    put_char(w >> 16);
    put_char(w >> 24);
}

//
// Write one byte to stdout.
//
void Processor::put_char(char ch)
{
    if (ch == '\n' || ch == '\r' || ch == '\t' || ch == '\b') {
        // Legal control character.
    } else if (ch >= 0 && ch < ' ') {
        std::cout << '^';
        if (capture_stdout_flag)
            stdout_buf << '^';
        ch += '@';
    } else if (ch > '~') {
        std::cout << '^';
        if (capture_stdout_flag)
            stdout_buf << '^';
        ch = '?';
    }
    std::cout << ch << std::flush;
    if (capture_stdout_flag)
        stdout_buf << ch;
}
