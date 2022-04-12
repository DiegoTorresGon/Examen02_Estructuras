#ifndef ED_IMP_H_
#define ED_IMP_H_

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

/***************************/
/* EXPRESIONES ARITMÉTICAS */
/***************************/

/*
  Una estructura de tipo `aexp_t' representa una expresión aritmética.
 */
struct aexp_t;
typedef struct aexp_t aexp_t;

/*
  A -> N | (A + A) | (A - A) | (A * A)
  
  Una expresión aritmética A puede ser un natural, una suma, una resta
  o una multiplicación.

  Los siguientes predicados determinan qué tipo de expresión es A.
  Toda expresión aritmética satisface únicamente uno de estos
  predicados.
 */
bool aexp_is_num(aexp_t *a);
bool aexp_is_add(aexp_t *a);
bool aexp_is_sub(aexp_t *a);
bool aexp_is_mul(aexp_t *a);

/*
  El valor de un natural se puede obtener con el selector `aexp_num',
  mientras que los operandos izquierdo y derecho de una suma, resta o
  multiplicación se pueden obtener con los selectores `aexp_left' y
  `aexp_right' respectivamente.
 */
uint64_t aexp_num(aexp_t *a);
aexp_t *aexp_left(aexp_t *a);
aexp_t *aexp_right(aexp_t *a);

/*
  Los siguientes constructores permiten crear un natural a partir de
  un valor de tipo `uint64_t', o bien, una expresión aritmética
  compuesta por otras expresiones aritméticas más simples.
 */
aexp_t *aexp_make_num(uint64_t num);
aexp_t *aexp_make_add(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_sub(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_mul(aexp_t *left, aexp_t *right);

/*
  Para liberar el espacio en memoria que ocupa una expresión
  aritmética se utiliza el siguiente destructor.
 */
void aexp_free(aexp_t *a);

/*
  Evaluador de expresiones aritméticas.
 */
uint64_t aexp_eval(aexp_t *a);

/*************************/
/* EXPRESIONES BOOLEANAS */
/*************************/

struct bexp_t;
typedef struct bexp_t bexp_t;

/*
  B -> true | false | (A = A) | (A < A) | (B and B) | (B or B) | not B

  Una expresión Booleana B puede ser verdadero, falso, la comparación
  de igualdad y menor qué entre dos expresiones ariméticas, la
  conjunción, disyunción y negación de expresiones Booleanas.

  Los siguientes predicados determinan qué tipo de expresión es B.
  Toda expresión booleana satisface únicamente uno de estos
  predicados.
 */
bool bexp_is_true(bexp_t *b);
bool bexp_is_false(bexp_t *b);
bool bexp_is_equal(bexp_t *b);
bool bexp_is_less(bexp_t *b);
bool bexp_is_and(bexp_t *b);
bool bexp_is_or(bexp_t *b);
bool bexp_is_neg(bexp_t *b);

/*
  Pendiente: documentar...
 */
aexp_t *bexp_aleft(bexp_t *b);
aexp_t *bexp_aright(bexp_t *b);
bexp_t *bexp_bleft(bexp_t *b);
bexp_t *bexp_bright(bexp_t *b);
bexp_t *bexp_nchild(bexp_t *b);

/*
  Pendiente: documentar...
 */
bexp_t *bexp_make_true();
bexp_t *bexp_make_false();
bexp_t *bexp_make_equal(aexp_t *left, aexp_t *right);
bexp_t *bexp_make_less(aexp_t *left, aexp_t *right);
bexp_t *bexp_make_and(bexp_t *left, bexp_t *right);
bexp_t *bexp_make_or(bexp_t *left, bexp_t *right);
bexp_t *bexp_make_neg(bexp_t *child);

/*
  Pendiente: documentar...
 */
void bexp_free(bexp_t *b);

/*
  Pendiente: documentar...
 */
bool bexp_eval(bexp_t *b);

#endif  /* ED_IMP_H_ */
