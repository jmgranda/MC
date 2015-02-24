#include <stdio.h>
#include <stdlib.h>

/* entradas */
int boton = 0;
int dinero = 0;
int timer = 0;

/* salidas */
int vaso = 0;
int cafe = 0;
int leche = 0;
int cobrar = 0;
int devolver = 0;

struct fsm_trans_t {
  int orig;
  int (*inputs) (void);
  int dest;
  void (*outputs) (void);
};
typedef struct fsm_trans_t fsm_trans_t;

struct fsm_t {
  fsm_trans_t* tt;
  int current;
};
typedef struct fsm_t fsm_t;

void
fsm_init (fsm_t* this, fsm_trans_t* tt)
{
  this->tt = tt;
  this->current = tt[0].orig;
}

fsm_t*
fsm_new (fsm_trans_t* tt)
{
  fsm_t* this = (fsm_t*) malloc (sizeof (fsm_t));
  fsm_init (this, tt);
  return this;
}

void
fsm_fire (fsm_t* this)
{
}

enum estado_t {
  ESPERANDO,
  SERVIRCAFE
};

int
boton_pulsado () 
{
  return boton && (dinero >= 50);
}

void
esperando_to_servircafe (void)
{
  boton = 0;
  cafe = 1;
  cobrar = 1;
}

int 
main ()
{
  fsm_trans_t tt[] = {
    { ESPERANDO, boton_pulsado, SERVIRCAFE, esperando_to_servircafe },
    { -1, 0, -1, 0 }
  };
  fsm_t *fsm = fsm_new (tt);

  while (scanf("%d %d %d", &boton, &dinero, &timer) == 3) {
    fsm_fire (fsm);
    printf ("%d %d %d %d %d\n", vaso, cafe, leche, cobrar, devolver);
  }

  return 0;
}
