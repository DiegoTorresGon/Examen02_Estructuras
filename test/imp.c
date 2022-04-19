#include <tests.h>
#include <imp.h>
#include <mem.h>

bool a_make_num() {
    aexp_t *a = aexp_make_num(666);
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_is_num(a), "Esperaba expresión numérica");
    check(aexp_num(a) == 666, "Valor numérico no esperado");
    aexp_free(a);
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_make_add() {
    aexp_t *a = aexp_make_add(aexp_make_num(42),
                              aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_is_add(a), "Experaba que expresión fuera suma");
    check(aexp_left(a) != NULL, "Esperaba hijo izquierdo");
    check(aexp_right(a) != NULL, "Esperaba hijo derecho");
    check(aexp_is_num(aexp_left(a)), "Esperaba hijo izquierdo numérico");
    check(aexp_is_num(aexp_right(a)), "Esperaba hijo derecho numérico");
    check(aexp_num(aexp_left(a)) == 42, "Esperaba hijo izquierdo = 42");
    check(aexp_num(aexp_right(a)) == 666, "Esperaba hijo derecho = 666");

    aexp_free(a);
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_make_sub() {
    aexp_t *a = aexp_make_sub(aexp_make_num(42),
                              aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_is_sub(a), "Experaba que expresión fuera resta");
    check(aexp_left(a) != NULL, "Esperaba hijo izquierdo");
    check(aexp_right(a) != NULL, "Esperaba hijo derecho");
    check(aexp_is_num(aexp_left(a)), "Esperaba hijo izquierdo numérico");
    check(aexp_is_num(aexp_right(a)), "Esperaba hijo derecho numérico");
    check(aexp_num(aexp_left(a)) == 42, "Esperaba hijo izquierdo = 42");
    check(aexp_num(aexp_right(a)) == 666, "Esperaba hijo derecho = 666");

    aexp_free(a);
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_make_mul() {
    aexp_t *a = aexp_make_mul(aexp_make_num(42),
                              aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_is_mul(a), "Experaba que expresión fuera multiplicación");
    check(aexp_left(a) != NULL, "Esperaba hijo izquierdo");
    check(aexp_right(a) != NULL, "Esperaba hijo derecho");
    check(aexp_is_num(aexp_left(a)), "Esperaba hijo izquierdo numérico");
    check(aexp_is_num(aexp_right(a)), "Esperaba hijo derecho numérico");
    check(aexp_num(aexp_left(a)) == 42, "Esperaba hijo izquierdo = 42");
    check(aexp_num(aexp_right(a)) == 666, "Esperaba hijo derecho = 666");

    aexp_free(a);
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_eval_num() {
    aexp_t *a;

    a = aexp_make_num(0);
    check(aexp_eval(a) == 0, "Esperaba que 0 = 0");
    aexp_free(a);

    a = aexp_make_num(666);
    check(aexp_eval(a) == 666, "Esperaba que 666 = 666");
    aexp_free(a);

    a = aexp_make_num(42);
    check(aexp_eval(a) == 42, "Esperaba que 42 = 42");
    aexp_free(a);
    
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_eval_add() {
    aexp_t *a;

    a = aexp_make_add(aexp_make_num(0),
                      aexp_make_num(0));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 0 + 0 = 0");
    aexp_free(a);

    a = aexp_make_add(aexp_make_num(0),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 666, "Esperaba que 0 + 666 = 666");
    aexp_free(a);

    a = aexp_make_add(aexp_make_num(42),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 708, "Esperaba que 42 + 666 = 708");
    aexp_free(a);

    a = aexp_make_add(aexp_make_num(666),
                      aexp_make_num(42));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 708, "Esperaba que 666 + 42 = 708");
    aexp_free(a);
    
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_eval_sub() {
    aexp_t *a;

    a = aexp_make_sub(aexp_make_num(0),
                      aexp_make_num(0));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 0 - 0 = 0");
    aexp_free(a);

    a = aexp_make_sub(aexp_make_num(0),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 0 - 666 = 0");
    aexp_free(a);

    a = aexp_make_sub(aexp_make_num(42),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 42 - 666 = 0");
    aexp_free(a);

    a = aexp_make_sub(aexp_make_num(666),
                      aexp_make_num(42));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 624, "Esperaba que 666 - 42 = 624");
    aexp_free(a);
    
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_eval_mul() {
    aexp_t *a;

    a = aexp_make_mul(aexp_make_num(0),
                      aexp_make_num(0));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 0 * 0 = 0");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(0),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 0 * 666 = 0");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(1),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 666, "Esperaba que 1 * 666 = 666");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(42),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 27972, "Esperaba que 42 * 666 = 27972");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(666),
                      aexp_make_num(42));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 27972, "Esperaba que 666 * 42 = 27972");
    aexp_free(a);
    
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool b_make_truefalse() {
    bexp_t *bt = bexp_make_true();
    bexp_t *bf = bexp_make_false();
    check(bt != NULL, "Documentar...");
    check(bf != NULL, "Documentar...");
    check(bt != bf, "Esperaba que true != false");

    bexp_free(bt);
    bexp_free(bf);
    return true;

 fail:
    bexp_free(bt);
    bexp_free(bf);
    return false;
}

bool b_make_equal() {
    bexp_t *b = bexp_make_equal(aexp_make_num(2),
                                aexp_make_num(3));
    check(b != NULL, "Esperaba suficiente memoria :C");
    check(bexp_is_equal(b), "¿Qué esperabas?");
    check(bexp_aleft(b) != NULL, "¿Qué esperabas?");
    check(bexp_aright(b) != NULL, "¿Qué esperabas?");
    check(aexp_is_num(bexp_aleft(b)), "¿Qué esperabas?");
    check(aexp_is_num(bexp_aright(b)), "¿Qué esperabas?");
    check(aexp_num(bexp_aleft(b)) == 2, "¿Qué esperabas?");
    check(aexp_num(bexp_aright(b)) == 3, "¿Qué esperabas?");

    bexp_free(b);
    return true;

 fail:
    bexp_free(b);
    return false;
}

bool b_make_less() {
    bexp_t *b = bexp_make_less(aexp_make_num(2),
                               aexp_make_num(3));
    check(b != NULL, "¿Qué esperabas?");
    check(bexp_is_less(b), "¿Qué esperabas?");
    /* Terminar prueba */

    bexp_free(b);
    return true;

 fail:
    return false;
}

bool b_eval_truefalse() {
    bexp_t* fal = bexp_make_false();
    bexp_t* tru = bexp_make_true();

    check(!bexp_eval(fal), "Esparaba valor falso");
    check(bexp_eval(tru), "Esperaba valor verdadero");

    bexp_free(fal);
    bexp_free(tru);
    return true;

 fail:
    bexp_free(fal);
    bexp_free(tru);
    return false;
}

bool b_make_and() {
    bexp_t* fal = bexp_make_false();

    bexp_t* a = bexp_make_and(fal, fal);

    check(bexp_is_and(a), "Esperaba que fuera una expresión tipo AND.");

    bexp_free(fal);
    bexp_free(a);
    return true;
 fail:
    bexp_free(fal);
    bexp_free(a);
    return false;
}

bool b_make_or() {
    bexp_t* tru = bexp_make_true();

    bexp_t* a = bexp_make_or(tru, tru);

    check(bexp_is_or(a), "Esperaba que fuera una expresión tipo OR.");

    bexp_free(a);
    bexp_free(tru);
    return true;
 fail:
    bexp_free(a);
    bexp_free(tru);
    return false;
}

bool b_make_neg() {
    bexp_t* tru = bexp_make_true();

    bexp_t* a = bexp_make_neg(tru);

    check(bexp_is_neg(a), "Esperaba que fuera una expresión tipo NOT.");
    
    bexp_free(a);
    bexp_free(tru);
    return true;
 fail:
    bexp_free(a);
    bexp_free(tru);
    return false;
}

bool b_eval_equal() {
    bexp_t* fal = bexp_make_equal(aexp_make_num(0), aexp_make_num(1));
    bexp_t* tru = bexp_make_equal(aexp_make_num(1), aexp_make_num(1));


    check(!bexp_eval(fal), "Experaba valor falso");
    check(bexp_eval(tru), "Esperaba valor verdadero");
    
    bexp_free(fal);
    bexp_free(tru);
    return true;
 fail:
    bexp_free(fal);
    bexp_free(tru);
    return false;
}

bool b_eval_less() {
    bexp_t* less = bexp_make_less(aexp_make_num(0), aexp_make_num(1));
    bexp_t* equal = bexp_make_less(aexp_make_num(1), aexp_make_num(1));
    bexp_t* greater = bexp_make_less(aexp_make_num(2), aexp_make_num(1));


    check(bexp_eval(less), "Experaba valor verdadero");
    check(!bexp_eval(equal), "Esperaba valor falso");
    check(!bexp_eval(greater), "Esperaba valor falso");
    
    bexp_free(less);
    bexp_free(equal);
    bexp_free(greater);
    return true;
 fail:
    bexp_free(less);
    bexp_free(equal);
    bexp_free(greater);
    return false;
}

bool b_eval_and() {
    bexp_t* fal = bexp_make_false();
    bexp_t* tru = bexp_make_true();

    bexp_t* a = bexp_make_and(tru, tru);

    check(bexp_eval(a), "Esperaba valor verdadero");
    
    bexp_free(a);
    a = bexp_make_and(tru, fal);
    check(!bexp_eval(a), "Esperaba valor falso");
    
    bexp_free(a);
    a = bexp_make_and(fal, tru);
    check(!bexp_eval(a), "Esperaba valor falso");

    bexp_free(a);
    a = bexp_make_and(fal, fal);
    check(!bexp_eval(a), "Esperaba valor falso");

    bexp_free(a);
    bexp_free(fal);
    bexp_free(tru);
    return true;
 fail:
    bexp_free(a);
    bexp_free(fal);
    bexp_free(tru);
    return false;
}

bool b_eval_or() {
    bexp_t* fal = bexp_make_false();
    bexp_t* tru = bexp_make_true();

    bexp_t* a = bexp_make_or(tru, tru);

    check(bexp_eval(a), "Esperaba valor verdadero");
    
    bexp_free(a);
    a = bexp_make_or(tru, fal);
    check(bexp_eval(a), "Esperaba valor verdadero");
    
    bexp_free(a);
    a = bexp_make_or(fal, tru);
    check(bexp_eval(a), "Esperaba valor verdadero");

    bexp_free(a);
    a = bexp_make_or(fal, fal);
    check(!bexp_eval(a), "Esperaba valor falso");

    bexp_free(a);
    bexp_free(fal);
    bexp_free(tru);
    return true;
 fail:
    bexp_free(a);
    bexp_free(fal);
    bexp_free(tru);
    return false;
}

bool b_eval_neg() {
    bexp_t* fal = bexp_make_false();
    bexp_t* tru = bexp_make_true();

    bexp_t* a = bexp_make_neg(tru);

    check(!bexp_eval(a), "Esperaba valor falso");
    
    bexp_free(a);
    a = bexp_make_neg(fal);
    check(bexp_eval(a), "Esperaba valor verdadero");

    bexp_free(a);
    bexp_free(fal);
    bexp_free(tru);
    return true;
 fail:
    bexp_free(a);
    bexp_free(fal);
    bexp_free(tru);
    return false;
}


///  PROBANDO MEMORIA
bool test_mem_assign_and_eval() {
    mem_t* m = mem_make();

    uint64_t n = 100;
    for(uint64_t i = 1; i < n; i += 2) {
        aexp_t* value = aexp_make_num(i);
        mem_assign(m, value, value);
        aexp_free(value);
    }

    for(uint64_t i = 0; i < n; i += 2) {
        aexp_t* value = aexp_make_num(i);
        mem_assign(m, value, value);
        aexp_free(value);
    }

    //This part is for testing if memory locations are being placed in order.
    //This is because the mem_eval function starts searching in the first value stored
    //and stops if it finds an element with a bigger index than the one that it's looking for.
    for(uint64_t i = 0; i < n; ++i) {
        aexp_t* value = aexp_make_num(i);
        bool test = i == mem_eval(m, value);
        aexp_free(value);
        check(test, "Expected equal values.");
    }

    //This next part tests when we update already existing positions on memory.
    for(uint64_t i = 0; i < n; ++i) {
        aexp_t* value = aexp_make_num(2 * i);
        aexp_t* index = aexp_make_num(i);
        mem_assign(m, index, value);
        aexp_free(value);
        aexp_free(index);
    }

    for(uint64_t i = 0; i < n; ++i) {
        aexp_t* value = aexp_make_num(i);
        bool test = 2 * i == mem_eval(m, value);
        aexp_free(value);
        check(test, "Expected equal values.");
    }
    
    for(uint64_t i = n; i < 2 * n; ++i) {
        aexp_t* value = aexp_make_num(i);
        bool test = 0 == mem_eval(m, value);
        aexp_free(value);
        check(test, "Expected value 0 on uninitialized position.");
    }

    mem_free(m);
    return true;
fail:
    mem_free(m);
    return false;
}

int main() {
    fprintf(stderr, "- Probando expresiones aritméticas\n");
    run_test(a_make_num);
    run_test(a_make_add);
    run_test(a_make_sub);
    run_test(a_make_mul);
    run_test(a_eval_num);
    run_test(a_eval_add);
    run_test(a_eval_sub);
    run_test(a_eval_mul);
    fprintf(stderr, "- Probando expresiones booleanas\n");
    run_test(b_make_truefalse);
    run_test(b_make_equal);
    run_test(b_make_less);
    run_test(b_eval_truefalse);
    run_test(b_make_and);
    run_test(b_make_or);
    run_test(b_make_neg);
    run_test(b_eval_equal);
    run_test(b_eval_less);
    run_test(b_eval_and);
    run_test(b_eval_or);
    run_test(b_eval_neg);
    fprintf(stderr, "- Probando memoria\n");
    run_test(test_mem_assign_and_eval);

    //This is a test
    
}
