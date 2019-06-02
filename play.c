#include <stdio.h>

int main(int ac, char *av[]){
    return
        !av[ac] ? printf("%d\n", main(ac - 1, av)), 0: // looking from tail and first evoke printf
        ac == 0 ? 0 : main(ac - 1, av) + // if looked at zero then return 0 else return sum now and before string
            (*av[ac] == '-' ? -1 * (av[ac][1] - '0') : // if inputed minus number then return minus number
                (*av[ac] == '+' ? av[ac][1] - '0' : // if inputed addition plus number then through
                    (0 <= *av[ac] - '0' && *av[ac] - '0' <= 9 ? *av[ac] - '0' : 0) // last validation
                )
            );
}