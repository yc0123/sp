set -x
gcc -w c4_power.c -o c4
./c4
# ./c4 -s hello.c
# ./c4 c4.c hello.c
# ./c4 c4.c c4.c hello.c