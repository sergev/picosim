Result:

    Setup interrupt handler.
    SP    = 20041ff8
    SP[0] = 10000264   <--- SP before interrupt
    SP[1] = 10000223
    Force interrupt.
    Got interrupt.
    SP    = 20041fd0
    SP[0] = 10000264   <--- SP in callback
    SP[1] = fffffff9        exc_return to Thread mode with main stack
    SP[2] = 00000007        r0 <--- SP after interrupt
    SP[3] = 00000000        r1
    SP[4] = e000e200        r2
    SP[5] = 00000080        r3
    SP[6] = 20000149        r12
    SP[7] = 100003d1        lr
    SP[8] = (unpredictable) return address
    SP[9] = 01000000        xpsr (bit 9 is 0)
    SP[10] = 10000264  <--- SP before interrupt
    SP[11] = 10000223
