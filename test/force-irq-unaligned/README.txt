Result:

    Setup interrupt handler.
    SP    = 20041ff4
    SP[0] = 10000375
    SP[1] = 10000264
    Force interrupt.
    Got interrupt.
    SP    = 20041fc8
    SP[0] = 10000264
    SP[1] = fffffff9
    SP[2] = 00000007
    SP[3] = 00000000
    SP[4] = e000e200
    SP[5] = 00000080
    SP[6] = 20000149
    SP[7] = 1000038b
    SP[8] = 1000038a
    SP[9] = 01000200
    SP[10] = 10000385
    SP[11] = 10000375
    SP[12] = 10000264

20041ff8: 10000264
20041ff4: 10000375 <--- SP before interrupt
20041ff0: 10000385      (skip)
20041fec: 01000200      xpsr (bit 9 is 1)
20041fe8: 1000038a      return address
20041fe4: 1000038b      lr
20041fe0: 20000149      r12
20041fdc: 00000080      r3
20041fd8: e000e200      r2
20041fd4: 00000000      r1
20041fd0: 00000007      r0 <--- SP after interrupt
20041fcc: fffffff9      exc_return to Thread mode with main stack
20041fc8: 10000264 <--- SP in callback
