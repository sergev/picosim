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

        // Make sure arguments are reasonable.
        if (fd == 1 && len > 0 && len <= 10000 &&
            addr >= ADDR_SRAM_START && (addr+len) <= ADDR_SRAM_LAST) {
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
