/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief ADC clk configuration example
 * @version 0.1
 * @date 2022-12-31
 *
 * @copyright Copyright (c) 2022. All rights reserved.
 *
 * Licensed under the MIT License, see LICENSE for details.
 * SPDX-License-Identifier: MIT
 *
 */

#include <stm32f1xx.h>

// Para configurar un periferico necesito la base_address.
// Se encuentra en la sección memory map del datasheet
// En este caso el ADC va 0x4001 2400 - 0x4001 27FF
// 0x40000000 (PERIPH_BASE) + 0x10000 (APB2_BUS_BASE) + 0x2400 (ADC1_BASE)
#define ADC_BASE_ADDR 0x40012400

// Luego dependiendo del registro que quiera configurar necesito
// darle el offset correspondiente
#define ADC_REG_CR1_OFFSET 0x04

// La direccion del registro finalmente sera la base mas el offset
// A su vez, necesitamos habilitar el clock del periferico para poder configurarlo
#define ADC_CR1_REG (uint32_t *)(ADC_BASE_ADDR + ADC_REG_CR1_OFFSET)

// Procedemos de la misma manera con el RCC para habilitar el clock
#define RCC_BASE_ADDR          0x40021000
#define RCC_APB2ENR_REG_OFFSET 0x18
#define RCC_APB2ENR_REG        (uint32_t *)(RCC_BASE_ADDR + RCC_APB2ENR_REG_OFFSET)

int main(void) {

    // Habilito el clock del ADC (bit 9 del registro RCC_APB2ENR)
    *RCC_APB2ENR_REG |= (1 << 9);

    // Configuro el ADC en modo SCAN (bit 8 del registro ADC_CR1)
    *ADC_CR1_REG |= (1 << 8);

    return 0;
}
