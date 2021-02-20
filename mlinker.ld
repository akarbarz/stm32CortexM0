/* (8KB SRAM on the STM32F031R8 line, 48192 = 0x2000) */
/* (8kB RAM starts at address 0x20000000) */

/* Label for programs entry point */
ENTRY(reset_handler)

/* Define the end of RAM and start of stack memory */
_estack = 0x20002000;

/* Set minimum size for stack and dynamic memory */
/* linker will gen error if less than this much RAM left over */
/* 1 KB */
_Min_Leftover_RAM = 0x400;

MEMORY
{
    FLASH ( rx )      : ORIGIN = 0x08000000, LENGTH = 64K
    RAM ( rxw )       : ORIGIN = 0x20000000, LENGTH = 8K
}

SECTIONS
{
  /* Vector table will be at start of flash */
  .vector_table :
  {
  . = ALIGN(4);
  KEEP(*(.vector_table))
  . = ALIGN(4);
  } >FLASH

  /* main program code. */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    . = ALIGN(4);
  } >FLASH

  /* read-only data,
   * constants, strings, information that won't change. */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* Lil bit of RAM for
   * things like variables, which can change. */
  _sidata = .;
  .data : AT(_sidata)
  {
    . = ALIGN(4);
    /* Mark start/end locations for the 'data' section. */
    _sdata = .;
    *(.data)
    *(.data*)
    _edata = .;
    . = ALIGN(4);
  } >RAM

  /* Similar to the 'data' section,
   * but its space is initialized to all 0s at the
   * start of the program. */
  .bss :
  {
    . = ALIGN(4);
    /* Also mark the start/end of the BSS section. */
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM

  /* Space set aside for the application's heap/stack. */
  .dynamic_allocations :
  {
    . = ALIGN(4);
    _ssystem_ram = .;
    . = . + _Min_Leftover_RAM;
    . = ALIGN(4);
    _esystem_ram = .;
  } >RAM

}
