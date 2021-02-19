/* Define the end of RAM and limit of stack memory */
/* (8KB SRAM on the STM32F031R8 line, 48192 = 0x2000) */
/* (8kB RAM starts at address 0x20000000) */
_estack = 0x20002000;

MEMORY
{
    FLASH ( rx )      : ORIGIN = 0x08000000, LENGTH = 64K
    RAM ( rxw )       : ORIGIN = 0x20000000, LENGTH = 8K
}
