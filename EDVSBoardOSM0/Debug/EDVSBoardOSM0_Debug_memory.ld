/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2013
 * (c) NXP Semiconductors 2013-2016
 * Generated linker script file for LPC4337-M0
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.23
 * LPCXpresso v8.1.4 [Build 606] [2016-03-14]  on Jul 9, 2016 10:16:26 PM
 */

MEMORY
{
  /* Define each memory region */
  MFlashA512_256 (rx) : ORIGIN = 0x1a040000, LENGTH = 0x40000 /* 256K bytes (alias Flash) */  
  MFlashA512 (rx) : ORIGIN = 0x1a000000, LENGTH = 0x40000 /* 256K bytes (alias Flash2) */  
  MFlashB512 (rx) : ORIGIN = 0x1b000000, LENGTH = 0x80000 /* 512K bytes (alias Flash3) */  
  M0CodeRam (rwx) : ORIGIN = 0x20008000, LENGTH = 0x400 /* 1K bytes (alias RAM) */  
  RamLoc40 (rwx) : ORIGIN = 0x10086014, LENGTH = 0x3fec /* 16364 bytes (alias RAM2) */  
  RamLoc32 (rwx) : ORIGIN = 0x10002014, LENGTH = 0x5fec /* 24556 bytes (alias RAM3) */  
  EventsBuffer32 (rwx) : ORIGIN = 0x10080000, LENGTH = 0x6010 /* 24592 bytes (alias RAM4) */  
  UartBuffer (rwx) : ORIGIN = 0x10000000, LENGTH = 0x2014 /* 8212 bytes (alias RAM5) */  
  M0Start (rwx) : ORIGIN = 0x10086010, LENGTH = 0x4 /* 4 bytes (alias RAM6) */  
  RamAHB32 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x8000 /* 32K bytes (alias RAM7) */  
  RamAHB16 (rwx) : ORIGIN = 0x20008400, LENGTH = 0x3c00 /* 15K bytes (alias RAM8) */  
  RamAHB_ETB16 (rwx) : ORIGIN = 0x2000c000, LENGTH = 0x4000 /* 16K bytes (alias RAM9) */  
}

  /* Define a symbol for the top of each memory region */
  __base_MFlashA512_256 = 0x1a040000  ; /* MFlashA512_256 */  
  __base_Flash = 0x1a040000 ; /* Flash */  
  __top_MFlashA512_256 = 0x1a040000 + 0x40000 ; /* 256K bytes */  
  __top_Flash = 0x1a040000 + 0x40000 ; /* 256K bytes */  
  __base_MFlashA512 = 0x1a000000  ; /* MFlashA512 */  
  __base_Flash2 = 0x1a000000 ; /* Flash2 */  
  __top_MFlashA512 = 0x1a000000 + 0x40000 ; /* 256K bytes */  
  __top_Flash2 = 0x1a000000 + 0x40000 ; /* 256K bytes */  
  __base_MFlashB512 = 0x1b000000  ; /* MFlashB512 */  
  __base_Flash3 = 0x1b000000 ; /* Flash3 */  
  __top_MFlashB512 = 0x1b000000 + 0x80000 ; /* 512K bytes */  
  __top_Flash3 = 0x1b000000 + 0x80000 ; /* 512K bytes */  
  __base_M0CodeRam = 0x20008000  ; /* M0CodeRam */  
  __base_RAM = 0x20008000 ; /* RAM */  
  __top_M0CodeRam = 0x20008000 + 0x400 ; /* 1K bytes */  
  __top_RAM = 0x20008000 + 0x400 ; /* 1K bytes */  
  __base_RamLoc40 = 0x10086014  ; /* RamLoc40 */  
  __base_RAM2 = 0x10086014 ; /* RAM2 */  
  __top_RamLoc40 = 0x10086014 + 0x3fec ; /* 16364 bytes */  
  __top_RAM2 = 0x10086014 + 0x3fec ; /* 16364 bytes */  
  __base_RamLoc32 = 0x10002014  ; /* RamLoc32 */  
  __base_RAM3 = 0x10002014 ; /* RAM3 */  
  __top_RamLoc32 = 0x10002014 + 0x5fec ; /* 24556 bytes */  
  __top_RAM3 = 0x10002014 + 0x5fec ; /* 24556 bytes */  
  __base_EventsBuffer32 = 0x10080000  ; /* EventsBuffer32 */  
  __base_RAM4 = 0x10080000 ; /* RAM4 */  
  __top_EventsBuffer32 = 0x10080000 + 0x6010 ; /* 24592 bytes */  
  __top_RAM4 = 0x10080000 + 0x6010 ; /* 24592 bytes */  
  __base_UartBuffer = 0x10000000  ; /* UartBuffer */  
  __base_RAM5 = 0x10000000 ; /* RAM5 */  
  __top_UartBuffer = 0x10000000 + 0x2014 ; /* 8212 bytes */  
  __top_RAM5 = 0x10000000 + 0x2014 ; /* 8212 bytes */  
  __base_M0Start = 0x10086010  ; /* M0Start */  
  __base_RAM6 = 0x10086010 ; /* RAM6 */  
  __top_M0Start = 0x10086010 + 0x4 ; /* 4 bytes */  
  __top_RAM6 = 0x10086010 + 0x4 ; /* 4 bytes */  
  __base_RamAHB32 = 0x20000000  ; /* RamAHB32 */  
  __base_RAM7 = 0x20000000 ; /* RAM7 */  
  __top_RamAHB32 = 0x20000000 + 0x8000 ; /* 32K bytes */  
  __top_RAM7 = 0x20000000 + 0x8000 ; /* 32K bytes */  
  __base_RamAHB16 = 0x20008400  ; /* RamAHB16 */  
  __base_RAM8 = 0x20008400 ; /* RAM8 */  
  __top_RamAHB16 = 0x20008400 + 0x3c00 ; /* 15K bytes */  
  __top_RAM8 = 0x20008400 + 0x3c00 ; /* 15K bytes */  
  __base_RamAHB_ETB16 = 0x2000c000  ; /* RamAHB_ETB16 */  
  __base_RAM9 = 0x2000c000 ; /* RAM9 */  
  __top_RamAHB_ETB16 = 0x2000c000 + 0x4000 ; /* 16K bytes */  
  __top_RAM9 = 0x2000c000 + 0x4000 ; /* 16K bytes */  
