#include <imp.h>
#include <mem.h>
#include <tests.h>

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

bool a_make_mem() {
    aexp_t *a = aexp_make_mem(aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_is_mem(a), "Esperaba expresión de memoria");
    check(aexp_eval(aexp_index(a), NULL) == 666, "Valor numérico no esperado");
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
    check(aexp_eval(a, NULL) == 0, "Esperaba que 0 = 0");
    aexp_free(a);

    a = aexp_make_num(666);
    check(aexp_eval(a, NULL) == 666, "Esperaba que 666 = 666");
    aexp_free(a);

    a = aexp_make_num(42);
    check(aexp_eval(a, NULL) == 42, "Esperaba que 42 = 42");
    aexp_free(a);
    
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_eval_mem() {
    aexp_t *a;
    mem_t* m = mem_make();
    if(m == NULL) goto fail;

    a = aexp_make_mem(aexp_make_num(0));
    check(aexp_eval(a, m) == 0, "Esperaba que x[0] == 0");
    
    aexp_t* val = aexp_make_num(10);
    mem_assign(m, aexp_index(a), val); 
    check(aexp_eval(a, m) == 10, "Esperaba que x[0] == 10");

    aexp_free(a);
    a = aexp_make_mem(aexp_make_num(15));
    check(aexp_eval(a, m) == 0, "Esperaba que x[15] == 0");

    aexp_free(val);
    aexp_free(a);
    mem_free(m);
    return true;

 fail:
    aexp_free(a);
    aexp_free(val);
    mem_free(m);
    return false;
}

bool a_eval_add() {
    aexp_t *a;

    a = aexp_make_add(aexp_make_num(0),
                      aexp_make_num(0));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 0, "Esperaba que 0 + 0 = 0");
    aexp_free(a);

    a = aexp_make_add(aexp_make_num(0),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 666, "Esperaba que 0 + 666 = 666");
    aexp_free(a);

    a = aexp_make_add(aexp_make_num(42),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 708, "Esperaba que 42 + 666 = 708");
    aexp_free(a);

    a = aexp_make_add(aexp_make_num(666),
                      aexp_make_num(42));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 708, "Esperaba que 666 + 42 = 708");
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
    check(aexp_eval(a, NULL) == 0, "Esperaba que 0 - 0 = 0");
    aexp_free(a);

    a = aexp_make_sub(aexp_make_num(0),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 0, "Esperaba que 0 - 666 = 0");
    aexp_free(a);

    a = aexp_make_sub(aexp_make_num(42),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 0, "Esperaba que 42 - 666 = 0");
    aexp_free(a);

    a = aexp_make_sub(aexp_make_num(666),
                      aexp_make_num(42));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 624, "Esperaba que 666 - 42 = 624");
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
    check(aexp_eval(a, NULL) == 0, "Esperaba que 0 * 0 = 0");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(0),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 0, "Esperaba que 0 * 666 = 0");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(1),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 666, "Esperaba que 1 * 666 = 666");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(42),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 27972, "Esperaba que 42 * 666 = 27972");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(666),
                      aexp_make_num(42));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a, NULL) == 27972, "Esperaba que 666 * 42 = 27972");
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

    check(!bexp_eval(fal, NULL), "Esparaba valor falso");
    check(bexp_eval(tru, NULL), "Esperaba valor verdadero");

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


    check(!bexp_eval(fal, NULL), "Experaba valor falso");
    check(bexp_eval(tru, NULL), "Esperaba valor verdadero");
    
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


    check(bexp_eval(less, NULL), "Experaba valor verdadero");
    check(!bexp_eval(equal, NULL), "Esperaba valor falso");
    check(!bexp_eval(greater, NULL), "Esperaba valor falso");
    
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

    check(bexp_eval(a, NULL), "Esperaba valor verdadero");
    
    bexp_free(a);
    a = bexp_make_and(tru, fal);
    check(!bexp_eval(a, NULL), "Esperaba valor falso");
    
    bexp_free(a);
    a = bexp_make_and(fal, tru);
    check(!bexp_eval(a, NULL), "Esperaba valor falso");

    bexp_free(a);
    a = bexp_make_and(fal, fal);
    check(!bexp_eval(a, NULL), "Esperaba valor falso");

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

    check(bexp_eval(a, NULL), "Esperaba valor verdadero");
    
    bexp_free(a);
    a = bexp_make_or(tru, fal);
    check(bexp_eval(a, NULL), "Esperaba valor verdadero");
    
    bexp_free(a);
    a = bexp_make_or(fal, tru);
    check(bexp_eval(a, NULL), "Esperaba valor verdadero");

    bexp_free(a);
    a = bexp_make_or(fal, fal);
    check(!bexp_eval(a, NULL), "Esperaba valor falso");

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

    check(!bexp_eval(a, NULL), "Esperaba valor falso");
    
    bexp_free(a);
    a = bexp_make_neg(fal);
    check(bexp_eval(a, NULL), "Esperaba valor verdadero");

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

/// PROBANDO CONSTRUCTORES DE P
bool p_make_skip(){
    pexp_t *p=pexp_make_skip();
    check(p!=NULL, "Expected enough memory");
    check(pexp_is_skip(p), "Expected skip type");
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
    return false;
}

bool p_make_assign(){
    pexp_t *p=pexp_make_assign(aexp_make_num(2),
                                aexp_make_num(3));
    check(p!=NULL, "Expected enough memory");
    check(pexp_is_assign(p), "Expected skip type"); 
    check(pexp_aindex(p)!=NULL, "Expected enough memory + assignation on left pointer");
    check(pexp_arvalue(p)!=NULL, "Expected enough memory + assignation on right pointer");
    check(aexp_is_num(pexp_aindex(p)), "Expected numeric type on left");
    check(aexp_is_num(pexp_arvalue(p)), "Expected numeric type on right");
    check(aexp_num(pexp_aindex(p)) == 2, "Expected 2");
    check(aexp_num(pexp_arvalue(p)) == 3, "Expected 3");
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
    return false;
}
bool p_make_sequence(){
    pexp_t *p=pexp_make_sequence(pexp_make_skip(),
                                pexp_make_skip());
    check(p!=NULL, "Expected enough memory");
    check(pexp_is_sequence(p), "Expected sequence type"); 
    check(pexp_pfirst(p)!=NULL, "Expected enough memory + assignation on left pointer");
    check(pexp_psecond(p)!=NULL, "Expected enough memory + assignation on right pointer");
    check(pexp_is_skip(pexp_pfirst(p)), "Expected skip type on left");
    check(pexp_is_skip(pexp_psecond(p)), "Expected skip type on right");
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
    return false;
}
bool p_make_while(){
    bexp_t* tru = bexp_make_true();
    bexp_t* or = bexp_make_or(tru, tru);
    pexp_t *p=pexp_make_cicle(or,
                                pexp_make_skip());
    check(p!=NULL, "Expected enough memory");
    check(pexp_is_while(p), "Expected while type"); 
    check(pexp_bcondition(p)!=NULL, "Expected enough memory + assignation on left pointer");
    check(pexp_ptrue(p)!=NULL, "Expected enough memory + assignation on right pointer");
    check(bexp_is_or(pexp_bcondition(p)), "Expected or type on left");
    check(pexp_is_skip(pexp_ptrue(p)), "Expected skip type on right");
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
    return false;
}
bool p_make_conditional(){
    bexp_t* tru = bexp_make_true();
    bexp_t* or = bexp_make_or(tru, tru);
    pexp_t *p = pexp_make_conditional(or,
                                        pexp_make_skip(), pexp_make_skip());
    check(p!=NULL, "Expected enough memory");
    check(pexp_is_conditional(p), "Expected skip type"); 
    check(pexp_bcondition(p)!=NULL, "Expected enough memory + assignation on left pointer");
    check(pexp_ptrue(p)!=NULL, "Expected enough memory + assignation on mid pointer")
    check(pexp_pfalse(p)!=NULL, "Expected enough memory + assignation on right pointer");
    check(bexp_is_or(pexp_bcondition(p)), "Expected or type on left");
    check(pexp_is_skip(pexp_ptrue(p)), "Expected skip type on right");
    check(pexp_is_skip(pexp_pfalse(p)), "Expected skip type on mid");
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
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
    run_test(a_make_mem);
    run_test(a_make_add);
    run_test(a_make_sub);
    run_test(a_make_mul);
    run_test(a_eval_num);
    run_test(a_eval_mem);
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
    fprintf(stderr, "- Probando expresiones de P\n");
    run_test(p_make_skip);
    run_test(p_make_assign);
    run_test(p_make_sequence);
    run_test(p_make_while);
    run_test(p_make_conditional);
    //This is a test
    
}
