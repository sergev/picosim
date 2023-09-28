        .section .text
        .global _start
_start:
        movs r7, #1         // syscall exit(status)

        // Condition codes: N=0 Z=0 C=0 V=0
        ldr r0, =0x00000000
        msr APSR_nzcvq, r0
        beq fail1
        bne 1f
fail1:
        svc #0              // fail
1:
        bcs fail1
        bcc 2f
        svc #0              // fail
2:
        bmi fail1
        bpl 3f
        svc #0              // fail
3:
        bvs fail1
        bvc 4f
        svc #0              // fail
4:
        bhi fail1
        bls 5f
        svc #0              // fail
5:
        bge 6f
        svc #0              // fail
6:
        blt fail1
        bgt 7f
        svc #0              // fail
7:
        ble fail1

        // Condition codes: N=0 Z=0 C=0 V=1
        ldr r0, =0x10000000
        msr APSR_nzcvq, r0
        beq fail1
        bne 8f
        svc #0              // fail
8:
        bcs fail1
        bcc 9f
        svc #0              // fail
9:
        bmi fail1
        bpl 10f
        svc #0              // fail
10:
        bvs 11f
        svc #0              // fail
11:
        bvc fail1
        bhi fail1
        bls 12f
        svc #0              // fail
12:
        bge fail1
        blt 13f
        svc #0              // fail
13:
        bgt fail1
        ble 14f
        svc #0              // fail
14:

        // Condition codes: N=0 Z=0 C=1 V=0
        ldr r0, =0x20000000
        msr APSR_nzcvq, r0
        beq fail1
        bne 15f
        svc #0              // fail
15:
        bcs 16f
        svc #0              // fail
16:
        bcc fail1
        bmi fail1
        bpl 17f
        svc #0              // fail
17:
        bvs fail1
        bvc 18f
        svc #0              // fail
18:
        bhi 19f
        svc #0              // fail
19:
        bls fail1
        bge 20f
        svc #0              // fail
20:
        blt fail1
        bgt 21f
        svc #0              // fail
21:
        ble fail1

        // Condition codes: N=0 Z=0 C=1 V=1
        ldr r0, =0x30000000
        msr APSR_nzcvq, r0
        beq fail1
        bne 22f
        svc #0              // fail
22:
        bcs 23f
        svc #0              // fail
23:
        bcc fail1
        bmi fail1
        bpl 24f
        svc #0              // fail
24:
        bvs 25f
        svc #0              // fail
25:
        bvc fail1
        bhi 26f
        svc #0              // fail
26:
        bls fail1
        bge fail1
        blt 27f
        svc #0              // fail
27:
        bgt fail1
        ble 28f
        svc #0              // fail
28:

        // Condition codes: N=0 Z=1 C=0 V=0
        ldr r0, =0x40000000
        msr APSR_nzcvq, r0
        beq 29f
        svc #0              // fail
29:
        bne fail1
        bcs fail1
        bcc 30f
        svc #0              // fail
30:
        bmi fail1
        bpl 31f
        svc #0              // fail
31:
        bvs fail1
        bvc 32f
        svc #0              // fail
32:
        bhi fail1
        bls 33f
        svc #0              // fail
33:
        bge 34f
        svc #0              // fail
34:
        blt fail1
        bgt fail1
        ble 35f
        svc #0              // fail
35:

        // Condition codes: N=0 Z=1 C=0 V=1
        ldr r0, =0x50000000
        msr APSR_nzcvq, r0
        beq 36f
        svc #0              // fail
36:
        bne fail2
        bcs fail2
        bcc 37f
fail2:
        svc #0              // fail
37:
        bmi fail2
        bpl 38f
        svc #0              // fail
38:
        bvs 39f
        svc #0              // fail
39:
        bvc fail2
        bhi fail2
        bls 40f
        svc #0              // fail
40:
        bge fail2
        blt 41f
        svc #0              // fail
41:
        bgt fail2
        ble 42f
        svc #0              // fail
42:

        // Condition codes: N=0 Z=1 C=1 V=0
        ldr r0, =0x60000000
        msr APSR_nzcvq, r0
        beq 43f
        svc #0              // fail
43:
        bne fail2
        bcs 44f
        svc #0              // fail
44:
        bcc fail2
        bmi fail2
        bpl 45f
        svc #0              // fail
45:
        bvs fail2
        bvc 46f
        svc #0              // fail
46:
        bhi fail2
        bls 47f
        svc #0              // fail
47:
        bge 48f
        svc #0              // fail
48:
        blt fail2
        bgt fail2
        ble 49f
        svc #0              // fail
49:

        // Condition codes: N=0 Z=1 C=1 V=1
        ldr r0, =0x70000000
        msr APSR_nzcvq, r0
        beq 50f
        svc #0              // fail
50:
        bne fail2
        bcs 51f
        svc #0              // fail
51:
        bcc fail2
        bmi fail2
        bpl 52f
        svc #0              // fail
52:
        bvs 53f
        svc #0              // fail
53:
        bvc fail2
        bhi fail2
        bls 54f
        svc #0              // fail
54:
        bge fail2
        blt 55f
        svc #0              // fail
55:
        bgt fail2
        ble 56f
        svc #0              // fail
56:

        // Condition codes: N=1 Z=0 C=0 V=0
        ldr r0, =0x80000000
        msr APSR_nzcvq, r0
        beq fail2
        bne 57f
        svc #0              // fail
57:
        bcs fail2
        bcc 58f
        svc #0              // fail
58:
        bmi 59f
        svc #0              // fail
59:
        bpl fail2
        bvs fail2
        bvc 60f
        svc #0              // fail
60:
        bhi fail2
        bls 61f
        svc #0              // fail
61:
        bge fail2
        blt 62f
        svc #0              // fail
62:
        bgt fail2
        ble 63f
        svc #0              // fail
63:

        // Condition codes: N=1 Z=0 C=0 V=1
        ldr r0, =0x90000000
        msr APSR_nzcvq, r0
        beq fail2
        bne 64f
        svc #0              // fail
64:
        bcs fail2
        bcc 65f
        svc #0              // fail
65:
        bmi 66f
        svc #0              // fail
66:
        bpl fail2
        bvs 67f
        svc #0              // fail
67:
        bvc fail2
        bhi fail2
        bls 68f
        svc #0              // fail
68:
        bge 69f
        svc #0              // fail
69:
        blt fail2
        bgt 70f
        svc #0              // fail
70:
        ble fail2

        // Condition codes: N=1 Z=0 C=1 V=0
        ldr r0, =0xa0000000
        msr APSR_nzcvq, r0
        beq fail3
        bne 71f
fail3:
        svc #0              // fail
71:
        bcs 72f
        svc #0              // fail
72:
        bcc fail3
        bmi 73f
        svc #0              // fail
73:
        bpl fail3
        bvs fail3
        bvc 74f
        svc #0              // fail
74:
        bhi 75f
        svc #0              // fail
75:
        bls fail3
        bge fail3
        blt 76f
        svc #0              // fail
76:
        bgt fail3
        ble 77f
        svc #0              // fail
77:

        // Condition codes: N=1 Z=0 C=1 V=1
        ldr r0, =0xb0000000
        msr APSR_nzcvq, r0
        beq fail
        bne 78f
        svc #0              // fail
78:
        bcs 79f
        svc #0              // fail
79:
        bcc fail
        bmi 80f
        svc #0              // fail
80:
        bpl fail
        bvs 81f
        svc #0              // fail
81:
        bvc fail
        bhi 82f
        svc #0              // fail
82:
        bls fail
        bge 83f
        svc #0              // fail
83:
        blt fail
        bgt 84f
        svc #0              // fail
84:
        ble fail

        // Condition codes: N=1 Z=1 C=0 V=0
        ldr r0, =0xc0000000
        msr APSR_nzcvq, r0
        beq 85f
        svc #0              // fail
85:
        bne fail
        bcs fail
        bcc 86f
        svc #0              // fail
86:
        bmi 87f
        svc #0              // fail
87:
        bpl fail
        bvs fail
        bvc 88f
        svc #0              // fail
88:
        bhi fail
        bls 89f
        svc #0              // fail
89:
        bge fail
        blt 90f
        svc #0              // fail
90:
        bgt fail
        ble 91f
        svc #0              // fail
91:

        // Condition codes: N=1 Z=1 C=0 V=1
        ldr r0, =0xd0000000
        msr APSR_nzcvq, r0
        beq 92f
        svc #0              // fail
92:
        bne fail
        bcs fail
        bcc 93f
        svc #0              // fail
93:
        bmi 94f
        svc #0              // fail
94:
        bpl fail
        bvs 95f
        svc #0              // fail
95:
        bvc fail
        bhi fail
        bls 96f
        svc #0              // fail
96:
        bge 97f
        svc #0              // fail
97:
        blt fail
        bgt fail
        ble 98f
        svc #0              // fail
98:

        // Condition codes: N=1 Z=1 C=1 V=0
        ldr r0, =0xe0000000
        msr APSR_nzcvq, r0
        beq 99f
        svc #0              // fail
99:
        bne fail
        bcs 100f
        svc #0              // fail
100:
        bcc fail
        bmi 101f
        svc #0              // fail
101:
        bpl fail
        bvs fail
        bvc 102f
        svc #0              // fail
102:
        bhi fail
        bls 103f
        svc #0              // fail
103:
        bge fail
        blt 104f
        svc #0              // fail
104:
        bgt fail
        ble 105f
        svc #0              // fail
105:

        // Condition codes: N=1 Z=1 C=1 V=1
        ldr r0, =0xf0000000
        msr APSR_nzcvq, r0
        beq 106f
        svc #0              // fail
106:
        bne fail
        bcs 107f
        svc #0              // fail
107:
        bcc fail
        bmi 108f
        svc #0              // fail
108:
        bpl fail
        bvs 109f
        svc #0              // fail
109:
        bvc fail
        bhi fail
        bls 110f
        svc #0              // fail
110:
        bge 111f
        svc #0              // fail
111:
        blt fail
        bgt fail
        ble 112f
        svc #0              // fail
112:
        svc #0              // pass
fail:
        svc #0              // fail
