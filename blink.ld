ENTRY(main)

MEMORY {
  flash (rx) : ORIGIN = 0x08000000, LENGTH = 0x20000
  sram  (rwx): ORIGIN = 0x20000000, LENGTH = 0x5000
}

SECTIONS {
  .isr_vector : {
    . = ALIGN(4);

    KEEP(*(.isr_vector))
  } >flash

  .text : {
    . = ALIGN(4);

    *(.text)
    *(.rodata)

    . = ALIGN(4);
    _etext = .;
  } >flash

  .data : {
    . = ALIGN(4);
    _sdata = .;

    *(.data)

    . = ALIGN(4);
    _edata = .;
  } >sram AT>flash

  .bss : {
    . = ALIGN(4);
    _sbss = .;

    *(.bss)

    . = ALIGN(4);
    _ebss = .;
  } >sram
}
