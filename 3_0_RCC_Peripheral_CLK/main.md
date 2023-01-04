# Perifericos

## RCC (Reset and Clock Control)

Mirar la documentacion del periferico en la seccion "Clock tree"
Es el periferico encargado de administrar los relojes del sistema. Se puede configurar el reloj de la CPU, los relojes de los perifericos, etc.
En aplicaciones de bajo consumo es vital poder administrar los relojes de los perifericos para poder ahorrar energia.
Donde se necesita de un RTC (Real Time Clock) se puede usar el periferico propio del microcontrolador
La base de tiempo puede ser conseguida a partir de 3 fuentes de reloj:

- HSI (High Speed Internal) (RC Oscillator) (En este caso 8MHz)
- HSE (High Speed External) (Crystal Oscillator) (En este caso 8MHz)
- PLL_CLK (Phase Locked Loop)

Luego de un reset el microcontrolador arranca con el HSI como reloj de la CPU. Luego conmuta al HSE o al PLL_CLK si se configura.

Mediante los prescalers se puede tunear la frecuencia clock de los perifericos.

Por default todos peripheral clocks estan deshabilitados para ahorrar energia. En los MCU modernos lo comun es inicializar el clock del periferico antes de usarlo de lo contrario no funcionara ni podrá ser configurado.

El RCC puede ser considerado como un periferico más que permite la configurarion y tunning de la base de tiempo de los elementos del sistema.
