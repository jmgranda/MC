#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fsm.h"

/* entradas */
int boton = 0;
int timer = 0;
int moneda = 0;

/* salidas */
int vaso = 0;
int cafe = 0;
int leche = 0;
int cobrar = 0;

/* recursos compartidos */
int dinero = 0;
int devolver = 0;

enum estado_t {
  ESPERANDO,
  VASO,
  CAFE,
  LECHE
};

#define T_VASO 1
#define T_CAFE 2
#define T_LECHE 2

void start_timer (int t) { timer = t; }

int boton_pulsado () { return boton && (dinero >= 50); }
int timer_terminado () { return timer == 0; }
int hay_moneda () { return moneda > 0; }
int devolver_pulsado () { return devolver; }

void sacar_vaso () { dinero -= 50; vaso = 1; start_timer(T_VASO); }
void echar_cafe () { vaso = 0; cafe=1; start_timer(T_CAFE); }
void echar_leche () { cafe = 0; leche = 1; start_timer(T_LECHE); }
void terminar_cafe () { leche = 0; devolver = 1; }
void sumar_dinero () { dinero += moneda; moneda = 0; }
void devolver_dinero () { dinero = 0; }

int 
main ()
{
  fsm_trans_t tt_mcafe[] = {
    { ESPERANDO, boton_pulsado, VASO, sacar_vaso },
    { VASO, timer_terminado, CAFE, echar_cafe },
    { CAFE, timer_terminado, LECHE, echar_leche },
    { LECHE, timer_terminado, ESPERANDO, terminar_cafe },
    { -1, 0, -1, 0 }
  };
  fsm_trans_t tt_monedero[] = {
    { ESPERANDO, hay_moneda, ESPERANDO, sumar_dinero },
    { ESPERANDO, devolver_pulsado, ESPERANDO, devolver_dinero },
    { -1, 0, -1, 0 }
  };
  fsm_t *fsm_mcafe = fsm_new (tt_mcafe);
  fsm_t *fsm_monedero = fsm_new (tt_monedero);

  while (scanf("%d %d", &boton, &moneda) == 2) {
    fsm_fire (fsm_mcafe);
    fsm_fire (fsm_monedero);
    printf ("%d %d %d %d\n", vaso, cafe, leche, dinero);
    sleep (1);
    if (timer) timer--;
  }

  return 0;
}
