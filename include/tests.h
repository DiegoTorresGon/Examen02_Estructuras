#ifndef ED_TESTS_H_
#define ED_TESTS_H_

#include <stdio.h>
#include <stdbool.h>

#define run_test(test)                                   \
    do {                                                 \
        fprintf(stderr, "* Probando " #test "...");      \
        bool ok = test();                                \
        if (!ok) return 1;                               \
        fprintf(stderr, "ok\n");                         \
    } while (0)

#define check(expr, message)                                    \
    if (!(expr)) {                                              \
        fprintf(stderr, "\nError (%s:%d) " message "\n",        \
                __FILE__, __LINE__);                            \
        goto fail;                                              \
    }

#endif  /* ED_TESTS_H_ */
