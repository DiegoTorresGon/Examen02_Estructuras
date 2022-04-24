#ifndef ED_IMP_H_
#define ED_IMP_H_

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

/***************************/
/* EXPRESIONES ARITMÉTICAS */
/***************************/

#ifndef MEM_TYPE
#define MEM_TYPE

struct mem_t;
typedef struct mem_t mem_t;

#endif

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
bool aexp_is_mem(aexp_t *a);

/*
  El valor de un natural se puede obtener con el selector `aexp_num',
  mientras que los operandos izquierdo y derecho de una suma, resta o
  multiplicación se pueden obtener con los selectores `aexp_left' y
  `aexp_right' respectivamente.
 */
uint64_t aexp_num(aexp_t *a);
aexp_t *aexp_left(aexp_t *a);
aexp_t *aexp_right(aexp_t *a);
aexp_t *aexp_index(aexp_t *a);

/*
  Los siguientes constructores permiten crear un natural a partir de
  un valor de tipo `uint64_t', o bien, una expresión aritmética
  compuesta por otras expresiones aritméticas más simples.
 */
aexp_t *aexp_make_num(uint64_t num);
aexp_t *aexp_make_add(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_sub(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_mul(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_mem(aexp_t *index);

/*
  Para liberar el espacio en memoria que ocupa una expresión
  aritmética se utiliza el siguiente destructor.
 */
void aexp_free(aexp_t *a);

/*
  Evaluador de expresiones aritméticas.
 */
uint64_t aexp_eval(aexp_t *a, mem_t* m);

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
  Los siguientes métodos son selectores para acceder a los miembros internos
  de una expresión booleanas. 

  bexp_aleft y bexp_aright corresponden a expresiones de tipo igualdad y menor que.

  bexp_bleft y bexp_bright corresponden a expresiones de tipo AND y OR.

  bexp_nchild corresponde a una expresión de negación.
 */
aexp_t *bexp_aleft(bexp_t *b);
aexp_t *bexp_aright(bexp_t *b);
bexp_t *bexp_bleft(bexp_t *b);
bexp_t *bexp_bright(bexp_t *b);
bexp_t *bexp_nchild(bexp_t *b);

/*
  De acuerdo a los posibles tipos de expresiones booleanas:

  B -> true | false | (A = A) | (A < A) | (B and B) | (B or B) | not B .

  Se encuentran los constructores para generar expresiones booleanas
  de cada tipo.
 */
bexp_t *bexp_make_true();
bexp_t *bexp_make_false();
bexp_t *bexp_make_equal(aexp_t *left, aexp_t *right);
bexp_t *bexp_make_less(aexp_t *left, aexp_t *right);
bexp_t *bexp_make_and(bexp_t *left, bexp_t *right);
bexp_t *bexp_make_or(bexp_t *left, bexp_t *right);
bexp_t *bexp_make_neg(bexp_t *child);

/**
 * @brief Libera la memoria que utiliza una expresión booleana
 *        incluyendo a cualquiera de sus hijos.
 * 
 * @param b Expresión booleanas por liberar.
 */
void bexp_free(bexp_t *b);

/**
 * @brief Evalua el valor de verdad de una expresión booleana.
 * 
 * @param b Expresión booleana por evaluar.
 * @return bool Valor de verdad de la expresión. 
 */
bool bexp_eval(bexp_t *b, mem_t* m);


/***************************/
/* EXPRESIONES DE PROGRAMA */
/***************************/

struct pexp_t;
typedef struct pexp_t pexp_t;

/*
  P -> skip | x[A]:=A | (P;P) | (while B do P) | if (B then P else P)

  Una expresión de Programa puede ser skip (una instruccion que no hace algo), 
  x[A]:=A (asignacion a la memoria), (P;P) (una secuencia de programas),
  (while B do P) (repeticion) y if (B then P else P) (condicional). 

  Los siguientes predicados determinan qué tipo de expresión es P.
  Toda expresión de programa satisface únicamente uno de estos
  predicados.
 */
bool pexp_is_skip(pexp_t *p);
bool pexp_is_assign(pexp_t *p);
bool pexp_is_sequence(pexp_t *p) ;
bool pexp_is_while(pexp_t *p);
bool pexp_is_conditional(pexp_t *p);

/*
  Los siguientes constructores permiten crear una expresion de Programa a partir de
  expresiones Aritmeticas o Booleanas, asi como expresiones de Programa.
 */
pexp_t *pexp_make_skip();
pexp_t *pexp_make_assign(aexp_t *index, aexp_t *rvalue);
pexp_t *pexp_make_sequence(pexp_t *pfirst, pexp_t *psecond);
pexp_t *pexp_make_while(bexp_t *condition, pexp_t *ptrue);
pexp_t *pexp_make_conditional(bexp_t *condition, pexp_t *ptrue, pexp_t *pfalse);


/*
  Los siguientes métodos son selectores para acceder a los miembros internos
  de una expresión de programa. 

  pexp_pfirst y pexp_psecond corresponden a expresiones de tipo secuencia.

  pexp_aindex y pexp_arvalue corresponden a expresiones de tipo asignación.

  pexp_bcondition, pexp_ptrue y pexp_pfalse corresponden a un programa tipo ciclo
  y las primeras dos a un programa tipo condicional.
 */
aexp_t *pexp_aindex(pexp_t *p);
aexp_t *pexp_arvalue(pexp_t *p);
pexp_t *pexp_psecond(pexp_t *p);
pexp_t *pexp_pfirst(pexp_t *p);
bexp_t *pexp_bcondition(pexp_t *p);
pexp_t *pexp_ptrue(pexp_t *p);
pexp_t *pexp_pfalse(pexp_t *p);

//Evaluador
pexp_t *pexp_t_eval(pexp_t *p, mem_t* m);

#endif  /* ED_IMP_H_ */
