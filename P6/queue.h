#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX 15

/*Cua de uint8_t*/
typedef  struct{
  uint8_t cua[MAX];
  int tail;
  int head;
  int count;
}queue_t;

/*Inicialitza la cua q a l'estat buit*/
void queue_empty(queue_t *const q);

/*Retorna true si q es buida*/
bool queue_is_empty(const queue_t *const q);

/*Retorna true si q es plena*/
bool queue_is_full(const queue_t *const q);

/*Encua l'element v a la cua q. Si la cua es plena no fa res*/
void queue_enqueue(queue_t *const q, uint8_t v);

/*Desencua l'element del davant de la cua q. Si la cua es buida no fa
  res*/
void queue_dequeue(queue_t *const q);

/*Retorna l'element del davant de la cua q. Si la cua es buida retorna
  un valor arbitrari*/
uint8_t queue_front(const queue_t *const q);


#endif
