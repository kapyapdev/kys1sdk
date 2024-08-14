#include "sys/hardware.h"

int main()
{
        int a = 5;
        int b = 8;

        int a1 = 14;
        int b1 = 1;

        FILE* f = fopen("runtime.asm", "w");

        init(f);
        add(a, b);
        int bonzi = add(a1, b1);
        sub(bonzi, 5);

        return 0;
}
