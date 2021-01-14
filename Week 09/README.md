# Power Management

## Reducing power consumption in hardware

![Hardware1](https://user-images.githubusercontent.com/56385955/104615692-71566c00-56c4-11eb-9500-e090663d2bdd.PNG)

![Hardware2](https://user-images.githubusercontent.com/56385955/104615699-72879900-56c4-11eb-8f7b-30681a24dc21.PNG)

## Reducing power consumption in software

![Software1](https://user-images.githubusercontent.com/56385955/104615708-73b8c600-56c4-11eb-8948-e00f732c7809.PNG)

**Sleeping**
Two-step Procedure for sleeping (power-down mode)

1. Set SMCR = 0101 (Mode = power-down and sleep enabled = true)
2. Call the “sleep” instruction. The sleep instruction is one of the 131 instructions in the RISC instruction set of ATmega328p.  </br>
Assembly commands can be invoked through inline assembler in C.

**Sleeping with BOD disabled**

A brown out is a short dip in power supply.
ATmega328p has an on-chip Brown-out detection circuit that resets the microcontroller when the power supply falls below a specific level.  </br>
Brown-out detector can be disabled during sleep to conserve power.
