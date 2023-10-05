Result:

    Setup interrupt handler.
    SP    = 20041ff8
    SP[0] = 10000264
    SP[1] = 10000223
    Force interrupt.
    Got interrupt.
    SP    = 20041fd0
    SP[0] = 10000264
    SP[1] = fffffff9
    SP[2] = 00000007
    SP[3] = 00000000
    SP[4] = e000e200
    SP[5] = 00000080
    SP[6] = 2000015d
    SP[7] = 10000381
    SP[8] = 10000380
    SP[9] = 01000000
    SP[10] = 10000264
    SP[11] = 10000223

20041ffc: 10000223
20041ff8: 10000264 <--- SP before interrupt
20041ff4: 01000000      xpsr (bit 9 is 0)
20041ff0: 10000380      return address
20041fec: 10000381      lr
20041fe8: 2000015d      r12
20041fe4: 00000080      r3
20041fe0: e000e200      r2
20041fdc: 00000000      r1
20041fd8: 00000007      r0 <--- SP after interrupt
20041fd4: fffffff9      exc_return to Thread mode with main stack
20041fd0: 10000264 <--- SP in callback
