/*
 * WS2812S.s
 *
 *  Created on: 3 mai 2016
 *      Author: Samuel Poiraud
 *  Cette fonction est rédigée en assembleur pour respecter scrupuleusement les délais de production des signaux pour les leds de la matrice.
 */

 .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

  .data

  	//Les durées des boucles sont obtenues et réglées par la mesure à l'oscilloscopes
  	//Les durées ci dessous ont été obtenues pour une fréquence d'horloge SYSCLK à 64MHz, sur oscillateur interne.
	.set T0H, 18		//objectif : 350ns +/- 150ns
	.set T0L, 40		//objectif : 800ns +/- 150ns
	.set T1H, 40		//objectif : 700ns +/- 150ns
	.set T1L, 30		//objectif : 600ns +/- 150ns

  .section  .text.User_section

  .global WS2812_send_pixel_asm
  WS2812_send_pixel_asm:
  //R0 : pixel
  	STMDB SP! ,{R4-R7}
  //R1 : GPIO_PIN_X	: c'est la valeur à inscrire dans le registre BSRR pour mettre à 1 le port demandé
  //R2 : Adresse du registre BSRR du GPIO concerné

	LSL R5, R1, #16	//R5 est la valeur à inscrire dans le registre BSRR pour mettre à 0 le port demandé
	MOV R3, #23
	loop:

		LSR R4, R0, R3
		ANDS R4, R4, #1
		BEQ write0
		write1:
			STR R1, [R2]
			MOV R7, #T1H
			loop1h:
				SUBS R7, #1
				BNE loop1h
			STR R5, [R2]
			MOV R7, #T1L
			loop1l:
				SUBS R7, #1
				BNE loop1l
			B end_loop
		write0:
			STR R1, [R2]
			MOV R7, #T0H
			loop0h:
				SUBS R7, #1
				BNE loop0h
			STR R5, [R2]
			MOV R7, #T0L
			loop0l:
				SUBS R7, #1
				BNE loop0l
			B end_loop
		end_loop:
		SUB R3, #1
		CMP R3, #-1
	BNE loop

	LDMIA SP! ,{R4-R7}
	BX LR






