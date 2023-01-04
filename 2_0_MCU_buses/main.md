
# Algunas consideraciones sobre la arquitectura de la CPU y el sistema en general

``` c
/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief CPU bus, RCC peripheral, NVIC and Interrupts overview
 * @version 0.1
 * @date 2022-12-30
 *
 * @copyright Copyright (c) 2022. All rights reserved.
 *
 * Licensed under the MIT License, see LICENSE for details.
 * SPDX-License-Identifier: MIT
 *
 */

#include <stdlib.h>

static int global_var;    // .bss

static int global_init_var = 5;     // .data
extern int global_extern   = 10;    // .data

// Function -> .text
void function(void) {
    return;
}

int main(void) {

    // Data segments
    // +-------------------------------------------+
    // |Low address                    High address|
    // +------+------------+------+-------+--------+
    // |.text |   .data    | .bss | .heap | .stack |
    // +------+------------+------+-------+--------+
    // |FLASH | FLASH/SRAM | SRAM | SRAM  | SRAM   |
    // +------+------------+------+-------+--------+

    // .text: Contiene el código ejecutable y constantes.

    // .data: Contiene las variables globales y estáticas inicializadas.
    //        Pueden ser read-only o read-write. SRAM y FLASH.
    //        Se almacenarán en FLASH y se copiarán a SRAM en el arranque del programa.

    // .bss: Block Started by Symbol.
    //       Contiene las variables globales y estáticas no inicializadas.
    //       En general se inicializan en 0 en el arranque del programa.
    //       Pueden ser read-write. SRAM.

    // .heap: Memoria dinámica.

    // .stack: Memoria para las variables locales

    char *p           = malloc(10);    // .heap
    const int table[] = {1, 2, 3};     // .text

    return 0;
}
```

## Comentarios sobre la arquitectura del sistema

- La arquitectura utilizada es Von-Neumann
- El bit-encoding es little endian.
- La CPU utiliza 3 "buses" principales. En el "ARM Cortex M3 - TRM" se los menciona como
Advanced High-performance Bus-Lite (AHB-Lite) interfaces: ICode, DCode, and System bus interfaces.
- _Observación: El procesador no puede "fetchear" instrucciones y data al mismo tiempo_

## ICode-BUS

Se utiliza para la transferencia de instrucciones del procesador y la memoria FLASH.
Instruction fetches from Code memory space, 0x00000000 to 0x1FFFFFFF, are performed over this 32-bit AHB-Lite bus.

## DCode-BUS

Se utiliza para la transferencia de datos del procesador y la memoria FLASH a traves del "Bus Matrix"
Data and debug accesses to Code memory space, 0x00000000 to 0x1FFFFFFF, are performed over
this 32-bit AHB-Lite bus. Core data accesses have a higher priority than debug accesses on this
bus. This means that debug accesses are waited until core accesses haveNeuman completed when there
are simultaneous core and debug access to this bus.

## System-BUS

Se utiliza para la conexión del procesador o el DMA con el resto del sistema a traves del bus matrix. El bus matrix se dedica al arbitraje entre el periferico DMA y la CPU para la conexión con el resto del sistema.
Observacion: Este no está conectado a la memoria flash
       Instruction fetches, and data and debug accesses, to address ranges 0x20000000 to 0xDFFFFFFF and
       0xE0100000 to 0xFFFFFFFF are performed over this 32-bit AHB-Lite bus.
       For simultaneous accesses to this bus, the arbitration order in decreasing priority is:
       • data accesses
       • instruction and vector fetches
       • debug.
       The system bus interface contains control logic to handle unaligned accesses, FPB remapped
       accesses, bit-band accesses, and pipelined instruction fetches.

## DMA Bus

Conecta el DMA con la bus matrix

## Bus Matrix

Administra el acceso arbitrando sobre la interacción que tiene la CPU y el DMA sobre el resto del sistema. Utiliza un algoritmo Round Robin.
_Observacion: a este está directamente conectada la SRAM_

## AHB/APB bridges

Conectan el AHB system bus con los perifericos disponibles. Son de comunicación full duplex. Observacion: en este caso puede trabajar hasta 72MHz

