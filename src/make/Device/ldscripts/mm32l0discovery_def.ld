/*
Linker subscript for MM32L073 definitions with 32K Flash and 4K RAM
Copyright ICWiser 2018
Eric Qiu <jmqiu@icwiser.com>
*/

/* Memory Spaces Definitions */

ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 32K
  RAM  (xrw) : ORIGIN = 0x20000000, LENGTH = 4K
}

/* highest address of the user mode stack */
_estack = 0x20001000;
