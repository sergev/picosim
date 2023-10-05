Result:

    Setup interrupt handler.
    SP    = 20041ff4
    SP[0] = 100003b9   <--- SP before interrupt
    SP[1] = 10000264
    Force interrupt.
    Got interrupt.
    SP    = 20041fc8
    SP[0] = 10000264   <--- SP in callback
    SP[1] = fffffff9        exc_return to Thread mode with main stack
    SP[2] = 00000007        r0 <--- SP after interrupt
    SP[3] = 00000000        r1
    SP[4] = e000e200        r2
    SP[5] = 00000080        r3
    SP[6] = 20000149        r12
    SP[7] = 100003d3        lr
    SP[8] = (unpredictable) return address
    SP[9] = 01000200        xpsr (bit 9 is 1)
    SP[10] = 100003cd       (skip for alignment)
    SP[11] = 100003b9  <--- SP before interrupt
    SP[12] = 10000264
