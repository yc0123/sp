```
1: #include<stdio.h>
2: 
3: int power(int a,int n)
4: {
5:     if(!n)
    ENT  0
    LLA  2
    LI  
    PSH
    IMM  0
    EQ
6:     {
    BZ   0
7:         return 1;
    IMM  1
    LEV
8:     }
9:     else if(n==1)
    JMP  0
    LLA  2
    LI
    PSH
    IMM  1
    EQ
10:     {
    BZ   0
11:         return a;
    LLA  3
    LI
    LEV
12:     }
13:     else
    JMP  0
14:     {
15:         return a*power(a,n=n-1);
    LLA  3
    LI
    PSH
    LLA  3
    LI
    PSH
    LLA  2
    PSH
    LLA  2
    LI
    PSH
    IMM  1
    SUB
    SI
    PSH
    JSR  1349238808
    ADJ  2
    MUL
    LEV
16:     }
17: }
    LEV
18:
19: int main()
20: {
21:     printf("power(5,3)=%d\n",power(5,3));
    ENT  0
    IMM  1348972560
    PSH
    IMM  5
    PSH
    IMM  3
    PSH
    JSR  1349238808
    ADJ  2
    PSH
    PRTF
    ADJ  2
22: }
    LEV
```