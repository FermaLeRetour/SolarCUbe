/*
 * traffic_manager.c
 *
 *  Created on: Sep 19, 2021
 *      Author: virgocoachman
 */

#include <stdio.h>
#include <stdlib.h>
#include "traffic_manager.h"
#include "diag/trace.h"
#include "led.h"

/**
 * Permet de comparer et de renvoyer la plus grande valeur entre deux nombres entiers
 * Elle nous servira à comparer les files de voies pour savoir laquelle est la plus longue, et attribuer la priorité en conséquence
 */
uint8_t great_between(uint8_t a, uint8_t b){
	if(a >= b)
		return a;
	return b;
}

/**
 * Fonction permettant de changer la priorité de voie: la voie pr
 * @paramètres
 * priority : est un tableau contenant les valeurs de priorités des deux voies du carrefour
 * 			 priority[0]: L'état de la priorité (0 ou 1) de la voie_1
 * 			 priority[1]: L'état de la priorité (0 ou 1) de la voie_2
 * 			 Si l'état de la priorité d'une voie est à 1, alors le feu vert s'allume sur cette voie alors
 * 			 sur l'autre voie qui a la priorité à 0 a un feu rouge allumé
 * index : indique la voie qui doit recevoir la priorité 1. Si index = 0, alors priority[0] sera égal à 1 et priority[1] à 0
 * 			si index = 1, alors priority[1] sera égal à 1 et priority[0] à 0
 */
void switching_priority(uint8_t *priority, uint8_t index){
	priority[index] = 1;
	switch(index){
	case 0:
		priority[1] = 0;
		break;
	case 1:
		priority[0] = 0;
		break;
	default:
		puts("\nValeur d'index incorrecte, deux valeurs seulement sont possibles : 0 ou 1\n\n");
	}
}

/**
 * Permet de comparer la longueur des toutes les 4 files et de faire basculer la priorité en cas de besoin
 * 		et commande l'allumage de feux selon la priorité des voies
 * Retourne la file la plus longue
 * @paramètres:
 * a, b, c ,d : les pointeurs sur les compteurs respectivement de la file_a, file_b, file_c et file_d
 */
uint8_t analyse_queues_situation(uint8_t *a, uint8_t *b, uint8_t *c, uint8_t *d, uint8_t *priority){
	uint8_t length = 0;
	// queue_1 = la file (a ou b) la plus longue sur la voie_1
	uint8_t queue_1 = great_between(*a, *b);
	// queue_1 = la file (a ou b) la plus longue sur la voie_2
	uint8_t queue_2 = great_between(*c, *d);
	if(queue_1 == great_between(queue_1, queue_2)){
		switching_priority(priority, 0);
		length = *a + *b;
	} else{
		switching_priority(priority, 1);
		length = *c + *d;
		length = queue_1;
	}

	display_queues(a, b, c, d);
	uint8_t i = get_queue_big_priority(priority);
	blink_led_on(i);

	return length;
}

void display_queues(uint8_t *a, uint8_t *b, uint8_t *c, uint8_t *d){
	trace_printf("Voie_a : %u et voie_b : %u\nVoie_c : %u et voie_d : %u\n"
			"====================================================\n", *a, *b, *c, *d);
}

/**
 * Retourne l'index de la voie la plus prioritaire
 */
uint8_t get_queue_big_priority(uint8_t *priority)
{
	trace_printf("Voie_1 : %u et voie_2 : %u\n", priority[0], priority[1]);
	if(priority[0]>= priority[1])
		return 0;
	return 1;
}


