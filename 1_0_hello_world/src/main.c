/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief  STM32 Hello World (SWO and ITM)
 * @version 0.1
 * @date 2022-12-29
 *
 * @copyright Copyright (c) 2022. All rights reserved.
 *
 * Licensed under the MIT License, see LICENSE for details.
 * SPDX-License-Identifier: MIT
 *
 */

#include <stdio.h>
#include <stm32f1xx.h>

int main(void) {
    printf("HOLA MUNDO\n");
    return 0;
}

// NOTE: Para que funcione el printf hay que agregar la
// opción de semihosting para poder usar el
// ITM (Instrumentation Trace Macrocell) del MCU
//
// ====== Usar como template task ======
// {
//     "version": "2.0.0",
//     "tasks": [
//         {
//             "type": "shell",
//             "command": "cd ~/.platformio/packages/tool-openocd && bin/openocd -f scripts/interface/stlink.cfg -c 'set CPUTAPID 0' -f target/stm32f1x.cfg", // Change target MCU from stm32f1x.cfg to any supported MCU, The command "-c 'set CPUTAPID 0'" allows STM32 Clones to be debugged.
//             "args": [
//             ],
//             "problemMatcher": [
//                 "$platformio"
//             ],
//             "label": "OpenOCD (Allow semihosting output)"
//         }
//     ]
// }
// =====================================
//
// Ademas hay que modificar el .ini y agregar un script para
//  agregar en las variables de entorno los flags correspondientes
//
// ====== script.py ======
// Import("env")
//
// # Semihosting
// env.Append(
//     LINKFLAGS=["--specs=rdimon.specs"],
//     LIBS=["rdimon"]
// )
// =======================

