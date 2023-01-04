/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief MCO with different clock sources example
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023. All rights reserved.
 *
 * Licensed under the MIT License, see LICENSE for details.
 * SPDX-License-Identifier: MIT
 *
 */

#include <stm32f1xx.h>

typedef enum {
    NO_CLK      = 0b000,
    SYSCLK      = 0b100,
    HSI         = 0b101,
    HSE         = 0b110,
    PLLCLK_DIV2 = 0b111,
} MCO_Source_t;

void MCO_enable(MCO_Source_t source) {

    // Habilito el CLK del GPIOA (GPIOA esta conectado en el bus APB2
    RCC->APB2ENR |= (0b1 << 2);

    /**
     * NOTE - Si bien es una AFIO para este caso no es necesario
     * utilizar el bit AFIO_EN del registro RCC_APB2ENR
     *
     * Este es utilizado en casos de remaping de algunos perifericos,
     * en las EXTI (External interrupt/event GPIO mapping) del registro AFIO_EXTICRx
     * y triggers/events en el registro AFIO_EVCR.
     *
     * Nota extraida del datasheet:
     *      To read/write the AFIO_EVCR, AFIO_MAPR and AFIO_EXTICRX registers, the AFIO clock
     *      should first be enabled. Refer to Section 7.3.7: APB2 peripheral clock enable register
     *      (RCC_APB2ENR).
     */

    // Configuro el pin PA8 del GPIOA en modo AFIO Push Pull
    GPIOA->CRH &= ~(0b1111 << 0);    // Reseteo los bits 8:11
    GPIOA->CRH |= (0b10 << 2);       // Alternate Function Output Push-Pull (10: AFIO Push-pull)

    // Configuro el pin PA8 del GPIOA en modo High Speed
    GPIOA->CRH |= (0b11 << 0);    // Output mode, max speed 50 MHz (11: High speed mode)

    // Configuro el MCO en el pin PA8
    RCC->CFGR &= ~(0b111 << 24);    // Reseteo los bits 24:26
    RCC->CFGR |= (source << 24);    // Configuro el MCO en el pin PA8
}

int main(void) {

    // NOTE
    // A diferencia del ejemplo anterior voy a hacer la configuracion
    // de los registros mediante macros de CMSIS. Esto nos permite
    // hacerlo de una forma "mas legible", estandarizada y portable.
    // Para mas informacion sobre CMSIS, ver:

    /**
     * Objetivo:
     *
     * Para habilitar el MCO del MCU hay que configurar el registro RCC_CFGR
     *
     * A su vez se necesita configurar el pin correspondiente con el MCO
     *
     * Nota extraida del datasheet:
     *      The microcontroller clock output (MCO) capability allows the clock to be output onto the
     *      external MCO pin. The configuration registers of the corresponding GPIO port must be
     *      programmed in alternate function mode. One of 4 clock signals can be selected as the MCO
     *      clock.
     *
     * Para este MCU el pin que hay que configurar es el PA8 en modo
     * -AFIO
     * -High Speed Mode (no es necesario pero para poder hacer un upscaling optimo conviene)
     */

    // NOTE - Si quiero ir barriendo los diferentes CLK_SRC del MCO
    // deberia configurar en el caso del HSE el BYPASS para el external crystal

    // while (1) {
    //     Habilito el CLK del MCO conmutando en las diferentes CLK_SRC
    //     for (MCO_Source_t src = SYSCLK; src <= PLLCLK_DIV2; src++) {
    //         MCO_enable(src);
    //         for (volatile uint32_t i = 0; i < 1000000; i++)
    //             ;
    //     }
    // }

    while (1) MCO_enable(HSI);    // Por default el HSI esta habilitado como fuente de CLk del sistema
                                  // Configuro el MCO con el HSI como CLK_SRC

    // TODO - Configurar el HSE y setearlo como CLK_SRC del MCO
    // Habilito el CLK del HSE
    // RCC->CR |= (0b1 << 16);    // HSEON

    // Espero a que el HSE este listo
    // while (!(RCC->CR & (0b1 << 17)));    // HSERDY

    // while (1) MCO_enable(HSE);    // Configuro el MCO con el HSE como CLK_SRC

    return 0;
}
