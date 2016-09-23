/* 
    startup.o sdk-ameba-rtl8710af-v3.5a_without_NDA_GCC_V1.0.0
	pvvx 2016
*/

//#include <defs.h>
#include "rtl8195a.h"
#include "diag.h"
#include "hal_spi_flash.h"
#include "hal_api.h"
#include "hal_platform.h"
#include "diag.h"
#include "hal_diag.h"
#include "rtl8195a_uart.h"
#include "rtl8195a/rtl8195a_peri_on.h"
#include "hal_peri_on.h"

#define VREG32(addr) ((u32)(*((volatile u32*)(addr))))

#define __fastcall
#define _DWORD u32
#define _WORD u16

#define unk_0 ((u8 *)(0))
//-------------------------------------------------------------------------
// Function declarations

//void HalNMIHandler_Patch(void); // idb
u32 __fastcall StartupHalLogUartInit(int a1);
//void StartupHalInitPlatformLogUart(void); // idb
//void RtlBootToSram(void); // idb
//void __fastcall SYSCpuClkConfig(int ChipID, int SysCpuClk);
//int32_t IsForceLoadDefaultImg2(void); // idb
int __fastcall GetChipId(int a1, u32 a2);
void __fastcall StartupHalSpicInit(int InitBaudRate);
void __fastcall PreProcessForVendor(unsigned int a1, u32 a2, int a3);
void __fastcall HalHardFaultHandler_user_define(u32 HardDefaultArg); // idb
void __fastcall HalHardFaultHandler_Patch_c(u32 HardDefaultArg); // idb
void __fastcall VectorTableOverrideRtl8195A(u32 StackP); // idb
//void SYSPlatformInit(void); // idb
//void InfraStart(void); // idb
//void SDIO_Device_Off(void); // idb
//void _HalReInitPlatformLogUart(void); // idb
//void ReloadImg_user_define(void); // idb
//void ReloadImg(void); // idb
//void CPUResetHandler(void); // idb
//void __fastcall CPUReset(int a1);
// int DiagPrintf(const char *, ...); weak
 extern int HalWdgIntrHandle(void); //weak
// int HalGetCpuClk(void); weak
// int __fastcall SpicNVMCalLoadAll(_DWORD); weak
// int __fastcall SpicFlashInitRtl8195A(_DWORD); weak
// void *memset(void *s, int c, size_t n);
// int __fastcall HalPinCtrlRtl8195A(_DWORD, _DWORD, _DWORD); weak
// int __fastcall VectorTableInitRtl8195A(_DWORD); weak
// int __fastcall VectorIrqRegisterRtl8195A(_DWORD); weak
// int __fastcall HalTimerInitRtl8195a(_DWORD); weak
// int __fastcall SpicInitRtl8195A(_DWORD, _DWORD); weak
// int strcmp(const char *s1, const char *s2);
// int __fastcall RtlConsolRom(_DWORD); weak
// int __fastcall SpicWaitWipRtl8195A(_DWORD); weak
// int __fastcall SpicOneBitCalibrationRtl8195A(_DWORD); weak
// int __fastcall HalCpuClkConfig(_DWORD); weak
// int __fastcall HalDelayUs(_DWORD); weak
// int __fastcall HAL_GPIO_GetIPPinName_8195a(_DWORD); weak
// int __fastcall HAL_GPIO_Init_8195a(_DWORD); weak
// int __fastcall HAL_GPIO_ReadPin_8195a(_DWORD); weak
// int __fastcall HAL_GPIO_DeInit_8195a(_DWORD); weak
// int __fastcall HalHardFaultHandler(_DWORD); weak
// int __fastcall HALEFUSEOneByteReadROM(_DWORD, _DWORD, _DWORD, _DWORD); weak
// int __fastcall SpicReadIDRtl8195A(_DWORD); weak
// int __fastcall SdrControllerInit(_DWORD); weak
// int __fastcall SdrCtrlInit(_DWORD); weak
// int __fastcall SpicUserReadFourByteRtl8195A(_DWORD, _DWORD, _DWORD, _DWORD); weak
// int __fastcall SpicUserReadRtl8195A(_DWORD, _DWORD, _DWORD, _DWORD); weak
// void *memcpy(void *dest, const void *src, size_t n);
// int HalCommonInit(void); weak
// int __fastcall ShowRamBuildInfo(_DWORD); weak
// int __fastcall SystemCoreClockUpdate(_DWORD); weak
// int En32KCalibration(void); weak
// int __fastcall InitSoCPM(_DWORD); weak
// int __fastcall SpicDisableRtl8195A(_DWORD); weak
// int __fastcall AppStart(_DWORD); weak
// int __fastcall VectorTableInitForOSRtl8195A(_DWORD, _DWORD, _DWORD); weak
// int __fastcall HalLogUartInit(_DWORD); weak
// int __fastcall HalTimerOpInit_Patch(_DWORD); weak
// int __cdecl wifi_off(_DWORD); weak

//-------------------------------------------------------------------------
// Data declarations

PRAM_FUNCTION_START_TABLE pRamStartFun = (PRAM_FUNCTION_START_TABLE)0x10000BC8; // idb
/* hal_gpio.h
typedef struct _HAL_GPIO_ADAPTER_ {
    IRQ_HANDLE IrqHandle;   // GPIO HAL IRQ Handle
    GPIO_USER_IRQ_FUN UserIrqHandler;   // GPIO IRQ Handler
    GPIO_IRQ_FUN PortA_IrqHandler[32]; // The interrupt handler triggered by Port A[x]
    VOID *PortA_IrqData[32];
    VOID (*EnterCritical)(void);
    VOID (*ExitCritical)(void);
    u32 Local_Gpio_Dir[3];  // to record direction setting: 0- IN, 1- Out
    u8 Gpio_Func_En;    // Is GPIO HW function enabled ?
    u8 Locked;
}HAL_GPIO_ADAPTER, *PHAL_GPIO_ADAPTER;
*/
/* hal_irqn.h
typedef enum _IRQn_Type_ {
    SYSTEM_ON_IRQ                   =  0,
    ....
} IRQn_Type, *PIRQn_Type;
*/  
HAL_GPIO_ADAPTER gBoot_Gpio_Adapter =
{
  { NULL, SYSTEM_ON_IRQ, 0u, 0u },
  NULL,
  {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
  },
  {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
  },
  NULL,
  NULL,
  { 0u, 0u, 0u },
  0u,
  0u
}; // idb
// extern int ConfigDebugErr; weak
// extern _UNKNOWN _rom_bss_start__; weak
// extern _UNKNOWN _rom_bss_end__; weak
// extern int ConfigDebugWarn; weak
// extern int ConfigDebugInfo; weak
// extern _UNKNOWN UartLogIrqHandle; weak
// extern int (__fastcall *_image2_entry_func__)(_DWORD); idb
// extern _UNKNOWN _image2_validate_code__; weak
// extern int pHAL_Gpio_Adapter; weak
// extern _UNKNOWN NewVectorTable; weak
// extern _UNKNOWN _image1_bss_start__; weak
// extern _UNKNOWN _image1_bss_end__; weak
// extern _UNKNOWN _bss_start__; weak
// extern _UNKNOWN _bss_end__; weak
// extern _UNKNOWN vPortSVCHandler; weak
// extern _UNKNOWN xPortPendSVHandler; weak
// extern _UNKNOWN xPortSysTickHandler; weak
// extern _UNKNOWN HalTimerOp; weak
//----- (00000004) --------------------------------------------------------
void __fastcall HalNMIHandler_Patch(void)
{
  if ( ConfigDebugErr & (_DBG_MISC_ | _DBG_SDR_) )
    DiagPrintf("\rRTL8195A[HAL]: %s:NMI Error!!!!\n", "HalNMIHandler_Patch");
  if ( VREG32(VENDOR_REG_BASE) < 0 ) HalWdgIntrHandle(); //
}
// 1070: using guessed type int ConfigDebugErr;
// 1074: using guessed type int DiagPrintf(const char *, ...);
// 1078: using guessed type int HalWdgIntrHandle(void);
#define DEFAULT_BAUDRATE 38400
//----- (00000044) --------------------------------------------------------
u32 StartupHalLogUartInit(int a1)
{
/*  int v1; // r4@1
  unsigned int v2; // r0@1
  unsigned int v3; // r3@1

  v40003004 = 0; 	// HAL_UART_WRITE32(UART_DLH_OFF, 0)
  v4000300C = 128;  // HAL_UART_WRITE32(UART_LINE_CTL_REG_OFF
  v1 = a1;
  v2 = (unsigned int)HalGetCpuClk() >> 2;
  v3 = v2 / 0x96000;
  if ( 10 * v2 / 0x96000 - 10 * (v2 / 0x96000) > 4 )   LOBYTE(v3) = v3 + 1;
  v40003000 = (unsigned __int8)v3; // HAL_UART_WRITE32(UART_DLL_OFF, Divisor & 0xff);
  v4000300C = 3;
  v40003008 = 193; // 0xC1
  v40003004 = v1; // HAL_UART_WRITE32(UART_DLH_OFF, (Divisor & 0xff00) >> 8)

  if ( v1 )
  {
    v4000280C = 0x1000000; // VENDOR_REG_BASE +
    vE000ED0C = (unsigned __int16)(vE000ED0C & 0xF8FF) | 0x5FA0300;
    vE000E413 = 0xFFFFFFE0;
    vE000E100 = 0x80000;
  } */

  	HAL_UART_WRITE32(UART_DLH_OFF,0);

	u32 SysClock = (HalGetCpuClk() >> 2);
	u32 SampleRate = (16 * DEFAULT_BAUDRATE);
	u32 Divisor = SysClock / SampleRate;
	u32 Remaind = ((SysClock * 10) / SampleRate) - (Divisor * 10);
	if (Remaind > 4) Divisor++;
	// set DLAB bit to 1

	//	HAL_UART_WRITE32(UART_LINE_CTL_REG_OFF, RUART_LINE_CTL_REG_DLAB_ENABLE);

	HAL_UART_WRITE32(UART_DLL_OFF, Divisor & 0xff);
	// set DLAB bit to 1 ?
	HAL_UART_WRITE32(UART_LINE_CTL_REG_OFF, 3);
	HAL_UART_WRITE32(UART_DLH_OFF, a1);
	if(a1) {
		// Enable Peripheral_IRQ Setting for Log_Uart
		HAL_WRITE32(VENDOR_REG_BASE, PERIPHERAL_IRQ_EN, 0x1000000);
		// Cortex-M3 SCB->AIRCR
		HAL_WRITE32(0xE000ED00, 0x0C, (HAL_READ32(0xE000ED00, 0x0C) & 0xF8FF) | 0x5FA0300);
		HAL_WRITE8(0xE000E100,0x313,0xE0);
		HAL_WRITE32(0xE000E100,0,0x80000);  // NVIC enable external interrupt[?] ?
	}
  return 0;
}
// 107C: using guessed type int HalGetCpuClk(void);
//----- (000000E0) --------------------------------------------------------
void StartupHalInitPlatformLogUart(void)
{
	HAL_WRITE32(PERI_ON_BASE, SOC_FUNC_EN, HAL_READ32(PERI_ON_BASE, SOC_FUNC_EN) & (~(PERI_ON_SOC_FUNC_EN_LOG_UART))); //   v40000210 &= 0xFFFFEFFF; // ~(1<<12)
	HAL_WRITE32(PERI_ON_BASE, SOC_FUNC_EN, HAL_READ32(PERI_ON_BASE, SOC_FUNC_EN) | PERI_ON_SOC_FUNC_EN_LOG_UART); // v40000210 |= 0x1000u;
	HAL_WRITE32(PERI_ON_BASE, PESOC_CLK_CTRL, HAL_READ32(PERI_ON_BASE, PESOC_CLK_CTRL) | PERI_ON_CLK_CTRL_ACTCK_LOG_UART_EN); // v40000230 |= 0x1000u;
	StartupHalLogUartInit(5);
}
extern u8 _image2_validate_code__, _image2_entry_func__;
extern u8 _rom_bss_start__, _rom_bss_end__;
extern void UartLogIrqHandle(void);
//----- (0000010C) --------------------------------------------------------
void RtlBootToSram(void)
{
  int v0; // r0@1
  int v1; // r0@5
  PTIMER_ADAPTER ptim_adapter; // [sp+0h] [bp-38h]@1
  //int v3; // [sp+4h] [bp-34h]@1
  //int v4; // [sp+8h] [bp-30h]@1
  //int v5; // [sp+Ch] [bp-2Ch]@1
  //char v6; // [sp+1Ch] [bp-1Ch]@1
  //char v7; // [sp+1Dh] [bp-1Bh]@1

  memset(&_rom_bss_start__, 0, &_rom_bss_end__ - &_rom_bss_start__);

  VREG32(0x40000230) |= 0x40u;
  VREG32(0x40000230) |= 0x80u;
  HalPinCtrlRtl8195A(216, 0, 1);
  VREG32(0x40000320) = 2047;
  VREG32(0x400002C0) |= 1u;
  VREG32(0x400002C0) |= 0x100000u;
  VectorTableInitRtl8195A(536870908);
  VREG32(0x40000210) |= 0x10u;
  VREG32(0x40000230) |= 0x100u;
  VREG32(0x40000230) |= 0x200u;
  v0 = HalPinCtrlRtl8195A(196, 0, 1);
  SpicNVMCalLoadAll(v0);
  VREG32(0x40000014) &= 0x8Fu;
  ConfigDebugErr = -1;
  ConfigDebugWarn = 0;
  ConfigDebugInfo = 0;
  VREG32(0x40000210) &= 0xFFFFEFFF;
  VREG32(0x40000210) |= 0x1000u;
  VREG32(0x40000230) |= 0x1000u;
  v3 = 88;
  v4 = 0;
  ptim_adapter.v2 = (int)&UartLogIrqHandle;
  v5 = 5;
  StartupHalLogUartInit(0);
  VectorIrqRegisterRtl8195A(ptim_adapter);
  StartupHalLogUartInit(5);
  VREG32(0x40000204) = 3;
  VREG32(0x40000270) |= 1u;
  VREG32(0x40000210) |= 0x10000u;
  VREG32(0x40000230) |= 0x4000u;
  VREG32(0x40000230) |= 0x8000u;
  v7 = 1;
  v6 = 1;
  v3 = 0;
  v2 = 0;
  v4 = 0;
  HalTimerInitRtl8195a((PTIMER_ADAPTER)&v2);
  SpicInitRtl8195A(1, 1);
  SpicFlashInitRtl8195A(1);
  if ( ConfigDebugErr & _DBG_MISC_ ) {
	  DiagPrintf("\r===== Enter Image 1.5 ====\n");
	  DiagPrintf("\rImg2 Sign: %s, InfaStart @ 0x%08x\n", &_image2_validate_code__, _image2_entry_func__);
  v1 = strcmp((const char *)&_image2_validate_code__, "RTKWin");
  if ( v1 )
  {
    if ( ConfigDebugErr & _DBG_MISC_ )
      DiagPrintf("\rInvalid Image2 Signature\n");
    v1 = RtlConsolRom(1000);
  }
  _image2_entry_func__(v1);
}
// 1070: using guessed type int ConfigDebugErr;
// 1074: using guessed type int DiagPrintf(const char *, ...);
// 1080: using guessed type int __fastcall SpicNVMCalLoadAll(_DWORD);
// 1084: using guessed type int __fastcall SpicFlashInitRtl8195A(_DWORD);
// 1094: using guessed type int __fastcall HalPinCtrlRtl8195A(_DWORD, _DWORD, _DWORD);
// 1098: using guessed type int __fastcall VectorTableInitRtl8195A(_DWORD);
// 109C: using guessed type int ConfigDebugWarn;
// 10A0: using guessed type int ConfigDebugInfo;
// 10A8: using guessed type int __fastcall VectorIrqRegisterRtl8195A(_DWORD);
// 10AC: using guessed type int __fastcall HalTimerInitRtl8195a(_DWORD);
// 10B0: using guessed type int __fastcall SpicInitRtl8195A(_DWORD, _DWORD);
// 10B4: using guessed type int (__fastcall *_image2_entry_func__)(_DWORD);
// 10C0: using guessed type int __fastcall RtlConsolRom(_DWORD);

//----- (000002E4) --------------------------------------------------------
void __fastcall SYSCpuClkConfig(int ChipID, int SysCpuClk)
{
  int v2; // r6@1
  signed int v3; // r4@1
  int v4; // r5@3

  v2 = ChipID;
  v3 = SysCpuClk;
  if ( ConfigDebugInfo & _DBG_SPI_FLASH_ )
    ChipID = DiagPrintf("\r[SPIF Inf]%s(0x%x)\n", "SYSCpuClkConfig", SysCpuClk);
  v4 = VREG32(0x40000210) & 0x10;
  if (VREG32(0x40000210) & 0x10 )
  {
    SpicWaitWipRtl8195A(ChipID);
    v4 = 1;
  }
  if ( v2 == 0xFC && (!v3) )  v3 = 1;
  HalCpuClkConfig(v3);
  HalDelayUs(1000);
  StartupHalInitPlatformLogUart();
  if ( v4 ) SpicOneBitCalibrationRtl8195A(v3);
}
// 1074: using guessed type int DiagPrintf(const char *, ...);
// 10A0: using guessed type int ConfigDebugInfo;
// 10C4: using guessed type int __fastcall SpicWaitWipRtl8195A(_DWORD);
// 10C8: using guessed type int __fastcall SpicOneBitCalibrationRtl8195A(_DWORD);
// 10CC: using guessed type int __fastcall HalCpuClkConfig(_DWORD);
// 10D0: using guessed type int __fastcall HalDelayUs(_DWORD);
extern PHAL_GPIO_ADAPTER pHAL_Gpio_Adapter;
//----- (00000354) --------------------------------------------------------
int32_t IsForceLoadDefaultImg2(void)
{
  int v0; // r4@1
  int v1; // r6@1
  int v2; // r5@2
  signed int v3; // r6@4
  int v4; // r0@6
  int32_t result; // r0@8
  uint8_t gpio_pin[4]; // [sp+4h] [bp-24h]@1
  HAL_GPIO_PIN GPIO_Pin; // [sp+8h] [bp-20h]@3

  VREG32(gpio_pin) = VREG32(0x98009008);
//  gpio_pin[1] = VREG32(0x98009009);
  v0 = 0;
  pHAL_Gpio_Adapter = (int)&gBoot_Gpio_Adapter;
  v1 = 0;
  do
  {
    v2 = gpio_pin[v0];
    if ( v2 != 0xff )
    {
      GPIO_Pin.pin_name = HAL_GPIO_GetIPPinName_8195a(v2 & 0x7F);
      if ( v2 & 0x80 )
      {
        v3 = 1;
        GPIO_Pin.pin_mode = 1;
      }
      else
      {
        GPIO_Pin.pin_mode = 2;
        v3 = 0;
      }
      HAL_GPIO_Init_8195a(&GPIO_Pin);
      v4 = HAL_GPIO_ReadPin_8195a(&GPIO_Pin);
      v1 = v4 - v3 + ((unsigned int)(v4 - v3) <= 0) - (v4 - v3);
      HAL_GPIO_DeInit_8195a(&GPIO_Pin);
    }
    ++v0;
  }
  while ( v0 != 2 );
  result = v1;
  pHAL_Gpio_Adapter = 0;
  return result;
}
// 10D4: using guessed type int pHAL_Gpio_Adapter;
// 10D8: using guessed type int __fastcall HAL_GPIO_GetIPPinName_8195a(_DWORD);
// 10DC: using guessed type int __fastcall HAL_GPIO_Init_8195a(_DWORD);
// 10E0: using guessed type int __fastcall HAL_GPIO_ReadPin_8195a(_DWORD);
// 10E4: using guessed type int __fastcall HAL_GPIO_DeInit_8195a(_DWORD);

//----- (000003D8) --------------------------------------------------------
int __fastcall GetChipId(int a1, u32 a2)
{
  u32 chip_id; // [sp+4h] [bp-Ch]@1

  chip_id = a2;
  if ( HALEFUSEOneByteReadROM(VREG(SYSTEM_CTRL_BASE+REG_SYS_EFUSE_CTRL), 248, &chip_id, 7) != 1 && (ConfigDebugErr & _DBG_MISC_) ) //  0x400000E8?
    DiagPrintf("\rGet Chip ID Failed\r");
  return (u8)chip_id;
}
// 1070: using guessed type int ConfigDebugErr;
// 1074: using guessed type int DiagPrintf(const char *, ...);
// 10F0: using guessed type int __fastcall HALEFUSEOneByteReadROM(_DWORD, _DWORD, _DWORD, _DWORD);

//----- (00000418) --------------------------------------------------------
void __fastcall StartupHalSpicInit(int InitBaudRate)
{
  int v1; // r4@1

  VREG32(0x40000210) |= 0x10u;
  v1 = InitBaudRate;
  VREG32(0x40000230) |= 0x100u;
  VREG32(0x40000230) |= 0x200u;
  HalPinCtrlRtl8195A(196, (VREG32(0x400001F4) & 0xF0000000) - 0x30000000 <= 0, 1);
  SpicInitRtl8195A(v1, 0);
}
// 1094: using guessed type int __fastcall HalPinCtrlRtl8195A(_DWORD, _DWORD, _DWORD);
// 10B0: using guessed type int __fastcall SpicInitRtl8195A(_DWORD, _DWORD);
extern u8 _image1_bss_start__, _image1_bss_end__;
//----- (00000464) --------------------------------------------------------
void __fastcall PreProcessForVendor(unsigned int a1, u32 a2, int a3)
{
  int v3; // r0@1
  u32 v4; // r1@1
  int v5; // r8@3
  int v6; // r4@3
  u32 v7; // r5@4
  signed int v8; // r7@6
  char v9[4]; // r1@10
  int v10; // r0@13
  signed int v11; // r9@14
  int v12; // r0@17
  int v13; // r3@24
  int v14; // r1@26
  int v15; // r2@26
  signed int v16; // r4@28
  signed int v17; // r7@29
  signed int v18; // r8@34
  signed int v19; // r5@43
  const char *v20; // r0@51
  int v21; // r4@55
  int v22; // r1@57
  int v23; // r5@57
  int v24; // r7@57
  int v25; // r2@68
  int v26; // r3@68
  int v27; // r0@79
  unsigned int v28; // [sp+0h] [bp-28h]@1
  u32 Image2Addr; // [sp+4h] [bp-24h]@1
  int v30; // [sp+8h] [bp-20h]@1

  v28 = a1;
  Image2Addr = a2;
  v30 = a3;
  v3 = HALEFUSEOneByteReadROM(VREG32(0x400000E8), 211, (char *)&v28 + 3, 7);
  v4 = BYTE3(v28) << 31;
  if ( BYTE3(v28) & 1 )
    v3 = HalPinCtrlRtl8195A(216, 0, 1);
  v5 = GetChipId(v3, v4);
  v6 = VREG32(0x40000210) & 0x10;
  if ( VREG32(0x40000210) & 0x10 )
  {
    v7 = (u32)&_image2_entry_func__;
    v6 = 1;
    goto LABEL_6;
  }
  memcpy(&Image2Addr, (const void *)0x1006FFFC, 4u);
  v7 = Image2Addr;
  if ( v5 != 251 )
  {
    StartupHalSpicInit(1);
LABEL_6:
    v8 = 1;
    goto LABEL_9;
  }
  v8 = 0;
LABEL_9:
  if ( ConfigDebugErr & _DBG_MISC_ )
  {
    *(u32 *)v9 = "NO";
    if ( v6 )
      *(u32 *)v9 = "YES";
    DiagPrintf("\rBOOT from Flash:%s\r\n", *(u32 *)v9, 2 * ConfigDebugErr);
  }
  memset(&_image1_bss_start__, 0, &_image1_bss_end__ - &_image1_bss_start__);
  v10 = HalDelayUs(1000);
  if ( (u8)(v5 + 5) > 2u )
  {
    v10 = SdrCtrlInit(v10);
    v11 = 1;
  }
  else
  {
    v11 = 0;
  }
  ConfigDebugErr = -1;
  ConfigDebugWarn = 0;
  ConfigDebugInfo = 0;
  if ( v8 )     SpicNVMCalLoadAll(v10);
  SYSCpuClkConfig(v5, 0);
  StartupHalInitPlatformLogUart();
  if ( ConfigDebugErr & _DBG_MISC_ )
    v12 = DiagPrintf("\r===== Enter Image 1 ====\r\n");
  if ( v8 )
  {
    SpicReadIDRtl8195A(v12);
    v12 = SpicFlashInitRtl8195A(1);
  }
  if ( v11 )    SdrControllerInit(v12);
  if ( v6 )
  {
    v13 = VREG(0x98000018) << 10;
    if ( !VREG(0x98000018) )
      v13 = VREG(0x98000010) + 32;
    v14 = *(u32 *)(v13 - 0x67FFFFF8);
    v15 = *(u32 *)(v13 - 0x67FFFFF4);
    if ( v14 == 0x35393138 )
    {
      if ( v15 == 0x31313738 )
      {
        v16 = v13;
LABEL_29:
        v17 = -1;
        goto LABEL_34;
      }
    }
    else if ( v14 == 0x35393130 && v15 == 0x31313738 )
    {
      v17 = v13;
      v16 = -1;
LABEL_34:
      v18 = VREG(0x98009000);
      if ( VREG(0x98009000) != -1 )
      {
        if ( VREG(0x98009000) >= (unsigned int)(v13 + *(_DWORD *)(v13 - 0x68000000)) && !(VREG(0x98009000) & 0xFFF) )
        {
          v25 = *(u32 *)(VREG(0x98009000) - 0x67FFFFF8);
          v26 = *(u32 *)(VREG(0x98009000) - 0x67FFFFF4);
          if ( v25 == 0x35393138 )
          {
            if ( v26 == 0x31313738 )
              v16 = VREG(0x98009000);
          }
          else if ( v25 == 0x35393130 && v26 == 0x31313738 )
          {
            v17 = VREG(0x98009000);
          }
LABEL_41:
          if ( IsForceLoadDefaultImg2() )
          {
            if ( v17 != -1 )
            {
              v19 = v17;
              goto LABEL_50;
            }
            v19 = v16;
          }
          else
          {
            if ( v16 != -1 )
            {
              v19 = v16;
              goto LABEL_50;
            }
            v19 = v17;
          }
          if ( v19 == -1 )
          {
            DiagPrintf("\n\rFatal:no fw\n\r");
            while ( 1 ) RtlConsolRom(1000);
          }
LABEL_50:
          if ( v19 == v17 )
          {
            v20 = "\n\rload OLD fw %d\n\r";
          }
          else
          {
            if ( v19 != v16 )
            {
LABEL_55:
              v21 = *(u32 *)(v19 - 0x68000000);
              Image2Addr = *(u32 *)(v19 - 0x67FFFFFC);
              if ( ConfigDebugErr & _DBG_MISC_ )
                DiagPrintf("\rFlash Image2:Addr 0x%x, Len %d, Load to SRAM 0x%x\n", v19, v21);
              v22 = v19 + 16;
              v23 = v19 + v21;
              SpicUserReadFourByteRtl8195A(v21, v22, Image2Addr, 1);
              v24 = *(u32 *)(v23 - 0x67FFFFF0);
              if ( (unsigned int)(v24 - 1) <= 0xFFFFFFFD && *(u32 *)(v23 - 0x67FFFFEC) == 0x30000000 )
              {
                if ( !v11 )
                {
                  if ( ConfigDebugErr & _DBG_MISC_ )
                    DiagPrintf("\r\n\rFW/HW conflict. No DRAM on board.\n\r");
                  while ( 1 )
                    ;
                }
                if ( ConfigDebugErr & _DBG_MISC_ )
                  DiagPrintf("\rImage3 length: 0x%x, Image3 Addr: 0x%x\n", *(_DWORD *)(v23 - 0x67FFFFF0));
                SpicUserReadRtl8195A(v24, v23 + 32, 0x30000000, 1);
              }
              else if ( ConfigDebugErr & _DBG_MISC_ )
              {
                DiagPrintf("\rNo Image3\n\r");
              }
              v7 = Image2Addr;
              if ( ConfigDebugErr & _DBG_MISC_ )
                DiagPrintf("\rImg2 Sign: %s, InfaStart @ 0x%08x \n", Image2Addr + 4, *(_DWORD *)Image2Addr);
              v27 = strcmp((const char *)(Image2Addr + 4), "RTKWin");
              if ( v27 )
              {
                while ( 1 )
                {
                  if ( ConfigDebugErr & _DBG_MISC_ )
                    DiagPrintf("\rInvalid Image2 Signature\n");
                  RtlConsolRom(1000);
                }
              }
              goto LABEL_84;
            }
            v20 = "\n\rload NEW fw %d\n\r";
          }
          DiagPrintf(v20, v19 - v18 + ((unsigned int)(v19 - v18) <= 0) - (v19 - v18));
          goto LABEL_55;
        }
        if ( ConfigDebugErr & _DBG_MISC_ )   DiagPrintf("\rOTA addr 0x%x INVALID\n", VREG(0x98009000));
      }
      v18 = -1;
      goto LABEL_41;
    }
    v16 = -1;
    goto LABEL_29;
  }
  v27 = strcmp((const char *)(Image2Addr + 4), "RTKWin");
  if ( v27 )
  {
    while ( 1 )
    {
      if ( ConfigDebugErr & _DBG_MISC_ )
        DiagPrintf("\rInvalid Image2 Signature\n", 2 * ConfigDebugErr);
      RtlConsolRom(1000);
    }
  }

LABEL_84:
	{
		(*(void (__cdecl **)(int))v7)(v27);
	}
}
// 1070: using guessed type int ConfigDebugErr;
// 1074: using guessed type int DiagPrintf(const char *, ...);
// 1080: using guessed type int __fastcall SpicNVMCalLoadAll(_DWORD);
// 1084: using guessed type int __fastcall SpicFlashInitRtl8195A(_DWORD);
// 1094: using guessed type int __fastcall HalPinCtrlRtl8195A(_DWORD, _DWORD, _DWORD);
// 109C: using guessed type int ConfigDebugWarn;
// 10A0: using guessed type int ConfigDebugInfo;
// 10C0: using guessed type int __fastcall RtlConsolRom(_DWORD);
// 10D0: using guessed type int __fastcall HalDelayUs(_DWORD);
// 10F0: using guessed type int __fastcall HALEFUSEOneByteReadROM(_DWORD, _DWORD, _DWORD, _DWORD);
// 10F4: using guessed type int __fastcall SpicReadIDRtl8195A(_DWORD);
// 10F8: using guessed type int __fastcall SdrControllerInit(_DWORD);
// 10FC: using guessed type int __fastcall SdrCtrlInit(_DWORD);
// 1100: using guessed type int __fastcall SpicUserReadFourByteRtl8195A(_DWORD, _DWORD, _DWORD, _DWORD);
// 1104: using guessed type int __fastcall SpicUserReadRtl8195A(_DWORD, _DWORD, _DWORD, _DWORD);

//----- (000007B4) --------------------------------------------------------
void __fastcall HalHardFaultHandler_Patch_c(u32 HardDefaultArg)
{
  u32 v1; // r4@1
  int v2; // r3@5
  int v3; // r3@6

  v1 = HardDefaultArg;
  if ( (VREG(0xE000ED28) & 0x82) && (unsigned int)(VREG(0xE000ED38) - 0x40080000) < 0x40000 )
  {
    if ( ConfigDebugErr & _DBG_MISC_ )
      DiagPrintf("\r.");
    v2 = *(_DWORD *)(v1 + 24);
    if ( (*(_WORD *)v2 & 0xF800) <= 0xE000 )
      v3 = v2 + 2;
    else
      v3 = v2 + 4;
    *(_DWORD *)(v1 + 24) = v3;
  }
  else
  {
    HalHardFaultHandler_user_define(HardDefaultArg);
    HalHardFaultHandler(v1);
  }
}
// 1070: using guessed type int ConfigDebugErr;
// 1074: using guessed type int DiagPrintf(const char *, ...);
// 10E8: using guessed type int __fastcall HalHardFaultHandler(_DWORD);
extern void * NewVectorTable;
//----- (00000828) --------------------------------------------------------
void __fastcall VectorTableOverrideRtl8195A(u32 StackP)
{
  *((_DWORD *)&NewVectorTable + 2) = HalNMIHandler_Patch;
}

//----- (00000838) --------------------------------------------------------
void SYSPlatformInit(void)
{
  VREG(0x40000020) = (VREG(0x40000020) & 0xF0FFFFFF) | 0x6000000;
  VREG(0x40000064) = (VREG(0x40000064) & 0xFFFFFFE7) | 8;
}
extern void * NewVectorTable;
extern u8 _bss_start__, _bss_end__;
extern void xPortPendSVHandler( void );
extern void xPortSysTickHandler( void );
extern void vPortSVCHandler( void );
//----- (00000858) --------------------------------------------------------
void InfraStart(void)
{
  unsigned int v0; // r4@1
  int v1; // r0@1
  int v2; // r4@1
  void *v3; // r0@6
  int v4; // r0@7
  int v5; // r0@8
  int v6; // r0@8

  *((_DWORD *)&NewVectorTable + 2) = HalNMIHandler_Patch;
  v0 = VREG(0x40000210);
  v1 = HalCommonInit();
  v2 = (v0 >> 4) & 1;
  if ( v1 && (ConfigDebugErr & _DBG_MISC_) )    v1 = DiagPrintf("\rHal Common Init Failed.\n");
  if ( ConfigDebugErr & _DBG_MISC_ )    v1 = DiagPrintf("\r===== Enter Image 2 ====\n");
  ShowRamBuildInfo(v1);
  v3 = memset(&_bss_start__, 0, &_bss_end__ - &_bss_start__);
  if ( v2 )
  {
    v4 = SpicNVMCalLoadAll(v3);
    v3 = (void *)SpicReadIDRtl8195A(v4);
  }
  SystemCoreClockUpdate(v3);
  SYSPlatformInit();
  v5 = En32KCalibration();
  InitSoCPM(v5);
  SDIO_Device_Off();
  v6 = VectorTableInitForOSRtl8195A(&vPortSVCHandler, &xPortPendSVHandler, &xPortSysTickHandler);
  if ( v2 )   v6 = SpicDisableRtl8195A(v6);
  AppStart(v6);
}
// 1070: using guessed type int ConfigDebugErr;
// 1074: using guessed type int DiagPrintf(const char *, ...);
// 1080: using guessed type int __fastcall SpicNVMCalLoadAll(_DWORD);
// 10F4: using guessed type int __fastcall SpicReadIDRtl8195A(_DWORD);
// 1114: using guessed type int HalCommonInit(void);
// 1118: using guessed type int __fastcall ShowRamBuildInfo(_DWORD);
// 111C: using guessed type int __fastcall SystemCoreClockUpdate(_DWORD);
// 1120: using guessed type int En32KCalibration(void);
// 1124: using guessed type int __fastcall InitSoCPM(_DWORD);
// 1128: using guessed type int __fastcall SpicDisableRtl8195A(_DWORD);
// 112C: using guessed type int __fastcall AppStart(_DWORD);
// 1144: using guessed type int __fastcall VectorTableInitForOSRtl8195A(_DWORD, _DWORD, _DWORD);

//----- (00000908) --------------------------------------------------------
void SDIO_Device_Off(void)
{
	VREG(0x40000240) &= 0xFFFFFFFE;
	VREG(0x40000214) &= 0xFFFFFFFE;
	VREG(0x40000214) &= 0xFFFFFFFD;
	VREG(0x400002A0) &= 0xFFFFFFFE;
}

//----- (00000944) --------------------------------------------------------
void _HalReInitPlatformLogUart(void)
{
  HalLogUartInit(38400);
}
// 1148: using guessed type int __fastcall HalLogUartInit(_DWORD);

//----- (0000097C) --------------------------------------------------------
void ReloadImg(void)
{
  int v0; // r4@1
  int v1; // r5@1
  unsigned int i; // r3@3
  int v3; // r3@6
  int v4; // r1@8
  int v5; // r2@8
  signed int v6; // r4@10
  signed int v7; // r5@11
  signed int v8; // r1@16
  int v9; // r2@16
  const char *v10; // r0@29
  int v11; // r3@30
  int v12; // r1@37
  int v13; // r0@37
  int j; // r3@37
  int v15; // r5@38
  int v16; // r4@40
  int k; // r3@46

  v0 = VREG(0x98000010);
  v1 = VREG(0x98000014);
  if ( ConfigDebugErr & _DBG_MISC_ )
    DiagPrintf("\r\rImage1 length: 0x%x, Image Addr: 0x%x\n\r", VREG(0x98000010), VREG(0x98000014));
  for ( i = 32; i < v0 + 32; i += 4 )
    *(_DWORD *)(v1 - 32 + i) = *(_DWORD *)(i - 0x68000000);
  v3 = VREG(0x98000018) << 10;
  if ( !(VREG(0x98000018)) )    v3 = VREG(0x98000010 + 32);
  v4 = *(_DWORD *)(v3 - 0x67FFFFF8);
  v5 = *(_DWORD *)(v3 - 0x67FFFFF4);
  if ( v4 == 0x35393138 )
  {
    if ( v5 == 0x31313738 )
    {
      v6 = v3;
LABEL_11:
      v7 = -1;
      goto LABEL_16;
    }
LABEL_14:
    v6 = -1;
    goto LABEL_11;
  }
  if ( v4 != 0x35393130 || v5 != 0x31313738 )
    goto LABEL_14;
  v7 = v3;
  v6 = -1;
LABEL_16:
  v8 = VREG(0x98009000);
  v9 = VREG(0x98009000) + 1;
  if ( VREG(0x98009000) == -1 )
  {
LABEL_21:
    v8 = -1;
    goto LABEL_22;
  }
  if ( VREG(0x98009000) < (unsigned int)(v3 + *(_DWORD *)(v3 - 0x68000000)) || (VREG(0x98009000) & 0xFFF) )
  {
    if ( ConfigDebugErr & _DBG_MISC_ )
      DiagPrintf("\r\rOTA addr 0x%x INVALID\n\r");
    goto LABEL_21;
  }
  v9 = *(_DWORD *)(VREG(0x98009000) - 0x67FFFFF8);
  v11 = *(_DWORD *)(VREG(0x98009000) - 0x67FFFFF4);
  if ( v9 == 0x35393138 )
  {
    v9 = 0x31313738;
    if ( v11 == 0x31313738 )
    {
      v6 = VREG(0x98009000);
      goto LABEL_33;
    }
    goto LABEL_22;
  }
  if ( v9 != 892940592 || (v9 = 825308984, v11 != 825308984) )
  {
LABEL_22:
    if ( v6 == -1 )
    {
      if ( v7 == -1 )
      {
        if ( ConfigDebugErr & _DBG_MISC_ )
          DiagPrintf("\r\rFatal:no fw\n\r", v8, 2 * ConfigDebugErr);
        while ( 1 )
          RtlConsolRom(1000);
      }
      v6 = v7;
LABEL_28:
      if ( ConfigDebugErr & _DBG_MISC_ )
      {
        v10 = "\r\rload OLD fw %d\n\r";
LABEL_36:
        DiagPrintf(v10, v6 - v8 + ((unsigned int)(v6 - v8) <= 0) - (v6 - v8), v9);
        goto IMG2_LOAD_START;
      }
      goto IMG2_LOAD_START;
    }
    goto LABEL_33;
  }
  if ( v6 == -1 )
  {
    v6 = VREG(0x98009000);
    goto LABEL_28;
  }
  v7 = VREG(0x98009000);
LABEL_33:
  if ( v6 == v7 )
    goto LABEL_28;
  if ( ConfigDebugErr & _DBG_MISC_ )
  {
    v10 = "\r\rload NEW fw %d\n\r";
    goto LABEL_36;
  }
IMG2_LOAD_START:
  v12 = *(_DWORD *)(v6 - 0x68000000);
  v13 = *(_DWORD *)(v6 - 0x67FFFFFC);
  for ( j = v6 + 16; ; j += 4 )
  {
    v15 = v12 + v6;
    if ( j >= (unsigned int)(v12 + v6 + 16) )
      break;
    *(_DWORD *)(-16 - v6 + v13 + j) = *(_DWORD *)(j - 1744830464);
  }
  v16 = *(_DWORD *)(v15 - 0x68000000);
  if ( (unsigned int)(v16 - 1) <= 0xFFFFFFFD && *(_DWORD *)(v15 - 0x67FFFFEC) == 0x30000000 )
  {
    if ( ConfigDebugErr & _DBG_MISC_ )
      DiagPrintf("\r\rImage3 length: 0x%x, Image3 Addr: 0x%x\n\r", *(_DWORD *)(v15 - 0x67FFFFF0));
    for ( k = v15 + 32; k < (unsigned int)(v16 + v15 + 32); k += 4 )
      *(_DWORD *)(0x2FFFFFE0 - v15 + k) = *(_DWORD *)(k - 0x68000000);
  }
  else if ( ConfigDebugErr & _DBG_MISC_ )
  {
    DiagPrintf("\r\rNo Image3\n\r");
  }
  ReloadImg_user_define();
}
// 1070: using guessed type int ConfigDebugErr;
// 1074: using guessed type int DiagPrintf(const char *, ...);
// 10C0: using guessed type int __fastcall RtlConsolRom(_DWORD);

//----- (00000B44) --------------------------------------------------------
void CPUResetHandler(void)
{
  memset(&_rom_bss_start__, 0, &_rom_bss_end__ - &_rom_bss_start__);
  ConfigDebugErr = -1;
  HalCpuClkConfig(0);
  VectorTableInitRtl8195A(0x1FFFFFFC);
  VREG(0x40000210) &= 0xF7FFFFFF;
  VREG(0x40000210) |= 0x10u;
  VREG(0x40000230) |= 0x100u;
  VREG(0x40000230) |= 0x200u;
  HalPinCtrlRtl8195A(196, 0, 1);
  HalTimerOpInit_Patch(&HalTimerOp);
  HalDelayUs(1000);
  _HalReInitPlatformLogUart();
  ReloadImg();
  InfraStart();
}
// 1070: using guessed type int ConfigDebugErr;
// 1094: using guessed type int __fastcall HalPinCtrlRtl8195A(_DWORD, _DWORD, _DWORD);
// 1098: using guessed type int __fastcall VectorTableInitRtl8195A(_DWORD);
// 10CC: using guessed type int __fastcall HalCpuClkConfig(_DWORD);
// 10D0: using guessed type int __fastcall HalDelayUs(_DWORD);
// 114C: using guessed type int __fastcall HalTimerOpInit_Patch(_DWORD);
extern int wifi_off(void);
//----- (00000BDC) --------------------------------------------------------
void __fastcall  CPUReset(int a1) // __noreturn
{
  wifi_off(a1);
  pRamStartFun->RamPatchFun1 = CPUResetHandler;
  VREG(0x40000210) |= 0x8000000u; // REG_SOC_FUNC_EN 1<<27
  VREG(0xE000ED0C) = 0x5FA0003;  //
  while(1);
}
// 1154: using guessed type int __cdecl wifi_off(_DWORD);

// ALL OK, 18 function(s) have been successfully decompiled

