/****************************************************************************************
 * K65TWR_ClkCfg
 *
 * This a standalone clock configuration module based on the old KDS clock configuration
 * system_MK65F18.c and .h. Using this allows you to not have to link in a bunch of SDK
 * modules that are not normally needed.
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 *
 * 09/06/2018 Todd Morton
 *
 ***************************************************************************************/
#ifndef K65TWR_CLKCFG_H_
#define K65TWR_CLKCFG_H_                        /**< Symbol preventing repeated inclusion */

//#include <stdint.h>

/* MCG mode constants */

#define MCG_MODE_FEI                   0U
#define MCG_MODE_FBI                   1U
#define MCG_MODE_BLPI                  2U
#define MCG_MODE_FEE                   3U
#define MCG_MODE_FBE                   4U
#define MCG_MODE_BLPE                  5U
#define MCG_MODE_PBE                   6U
#define MCG_MODE_PEE                   7U

/* Predefined clock setups
   0 ... Default  part configuration
         Multipurpose Clock Generator (MCG) in FEI mode.
         Reference clock source for MCG module: Slow internal reference clock
         Core clock = 20.97152MHz
         Bus clock  = 20.97152MHz
   1 ... Maximal speed configuration
         Multipurpose Clock Generator (MCG) in PEE mode.
         Reference clock source for MCG module: System oscillator 0 reference clock
         Core clock = 180MHz
         Bus clock  = 60MHz
   2 ... Chip internally clocked, ready for Very Low Power Run mode.
         Multipurpose Clock Generator (MCG) in BLPI mode.
         Reference clock source for MCG module: Fast internal reference clock
         Core clock = 4MHz
         Bus clock  = 4MHz
   3 ... Chip externally clocked, ready for Very Low Power Run mode.
         Multipurpose Clock Generator (MCG) in BLPE mode.
         Reference clock source for MCG module: System oscillator 0 reference clock
         Core clock = 4MHz
         Bus clock  = 4MHz
   4 ... USB clock setup
         Multipurpose Clock Generator (MCG) in PEE mode.
         Reference clock source for MCG module: System oscillator 0 reference clock
         Core clock = 120MHz
         Bus clock  = 60MHz
   5 ... Maximum achievable clock frequency configuration in RUN mode
         Multipurpose Clock Generator (MCG) in PEE mode.
         Reference clock source for MCG module: System oscillator 0 reference clock
         Core clock = 120MHz
         Bus clock  = 60MHz
*/
#define CLOCK_SETUP 1

/* Define clock source values */

#define CPU_XTAL_CLK_HZ                16000000U           /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
#define CPU_XTAL32k_CLK_HZ             32768U              /* Value of the external 32k crystal or oscillator clock frequency of the RTC in Hz */
#define CPU_INT_SLOW_CLK_HZ            32768U              /* Value of the slow internal oscillator clock frequency in Hz */
#define CPU_INT_FAST_CLK_HZ            4000000U            /* Value of the fast internal oscillator clock frequency in Hz */
#define CPU_INT_IRC_CLK_HZ             48000000U           /* Value of the 48M internal oscillator clock frequency in Hz */

/* RTC oscillator setting */
/* RTC_CR: SC2P=0,SC4P=0,SC8P=0,SC16P=0,CLKO=1,OSCE=1,WPS=0,UM=0,SUP=0,WPE=0,SWR=0 */
#define SYSTEM_RTC_CR_VALUE            0x0300U             /* RTC_CR */

/* Low power mode enable */
/* SMC_PMPROT: AHSRUN=1,AVLP=1,ALLS=1,AVLLS=1 */
#define SYSTEM_SMC_PMPROT_VALUE        0xAAU               /* SMC_PMPROT */

/* Internal reference clock trim */
/* #undef SLOW_TRIM_ADDRESS */                             /* Slow oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef SLOW_FINE_TRIM_ADDRESS */                        /* Slow oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef FAST_TRIM_ADDRESS */                             /* Fast oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef FAST_FINE_TRIM_ADDRESS */                        /* Fast oscillator not trimmed. Commented out for MISRA compliance. */

#ifdef CLOCK_SETUP
#if (CLOCK_SETUP == 0)
  #define DEFAULT_SYSTEM_CLOCK         20971520U           /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_FEI /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x06U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0x24U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN=0,PLLSTEN=0,PRDIV=0 */
  #define SYSTEM_MCG_C5_VALUE          0x00U               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV=0 */
  #define SYSTEM_MCG_C6_VALUE          0x00U               /* MCG_C6 */
  /* MCG_C7: OSCSEL=0 */
  #define SYSTEM_MCG_C7_VALUE          0x00U               /* MCG_C7 */
  /* MCG_C9: PLL_CME=0,PLL_LOCRE=0,EXT_PLL_LOCS=0 */
  #define SYSTEM_MCG_C9_VALUE          0x00U               /* MCG_C9 */
  /* MCG_C11: PLLCS=0 */
  #define SYSTEM_MCG_C11_VALUE         0x00U               /* MCG_C11 */
  /* OSC_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x80U               /* OSC_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV3=1,OUTDIV4=1 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x00110000U         /* SIM_CLKDIV1 */
  /* SIM_CLKDIV2: USBDIV=1,USBFRAC=0 */
  #define SYSTEM_SIM_CLKDIV2_VALUE     0x02U               /* SIM_CLKDIV2 */
  /* SIM_CLKDIV3: PLLFLLDIV=0,PLLFLLFRAC=0 */
  #define SYSTEM_SIM_CLKDIV3_VALUE     0x00U               /* SIM_CLKDIV3 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: SDHCSRC=0,LPUARTSRC=0,TPMSRC=1,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=0,TRACECLKSEL=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0,USBREGEN=0,USBSLSRC=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x01000000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 1)
//  #define DEFAULT_SYSTEM_CLOCK         180000000U          /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_PEE /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=4,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x22U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0x24U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN=0,PLLSTEN=0,PRDIV=1 */
  #define SYSTEM_MCG_C5_VALUE          0x01U               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV=0x1D */
  #define SYSTEM_MCG_C6_VALUE          0x5DU               /* MCG_C6 */
  /* MCG_C7: OSCSEL=0 */
  #define SYSTEM_MCG_C7_VALUE          0x00U               /* MCG_C7 */
  /* MCG_C9: PLL_CME=1,PLL_LOCRE=0,EXT_PLL_LOCS=0 */
  #define SYSTEM_MCG_C9_VALUE          0x20U               /* MCG_C9 */
  /* MCG_C11: PLLCS=0 */
  #define SYSTEM_MCG_C11_VALUE         0x00U               /* MCG_C11 */
  /* OSC_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x80U               /* OSC_CR */
  /* SMC_PMCTRL: RUNM=3,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x60U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=2,OUTDIV3=2,OUTDIV4=6 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x02260000U         /* SIM_CLKDIV1 */
  /* SIM_CLKDIV2: USBDIV=6,USBFRAC=0 */
  #define SYSTEM_SIM_CLKDIV2_VALUE     0x0CU               /* SIM_CLKDIV2 */
  /* SIM_CLKDIV3: PLLFLLDIV=0,PLLFLLFRAC=0 */
  #define SYSTEM_SIM_CLKDIV3_VALUE     0x00U               /* SIM_CLKDIV3 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: SDHCSRC=0,LPUARTSRC=0,TPMSRC=1,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=1,TRACECLKSEL=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0,USBREGEN=0,USBSLSRC=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x01010000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 2)
  #define DEFAULT_SYSTEM_CLOCK         4000000U            /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_BLPI /* Clock generator mode */
  /* MCG_C1: CLKS=1,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x46U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=1,LP=1,IRCS=1 */
  #define SYSTEM_MCG_C2_VALUE          0x27U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN=0,PLLSTEN=0,PRDIV=0 */
  #define SYSTEM_MCG_C5_VALUE          0x00U               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV=0 */
  #define SYSTEM_MCG_C6_VALUE          0x00U               /* MCG_C6 */
  /* MCG_C7: OSCSEL=0 */
  #define SYSTEM_MCG_C7_VALUE          0x00U               /* MCG_C7 */
  /* MCG_C9: PLL_CME=0,PLL_LOCRE=0,EXT_PLL_LOCS=0 */
  #define SYSTEM_MCG_C9_VALUE          0x00U               /* MCG_C9 */
  /* MCG_C11: PLLCS=0 */
  #define SYSTEM_MCG_C11_VALUE         0x00U               /* MCG_C11 */
  /* OSC_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x80U               /* OSC_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV3=0,OUTDIV4=4 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x00040000U         /* SIM_CLKDIV1 */
  /* SIM_CLKDIV2: USBDIV=0,USBFRAC=0 */
  #define SYSTEM_SIM_CLKDIV2_VALUE     0x00U               /* SIM_CLKDIV2 */
  /* SIM_CLKDIV3: PLLFLLDIV=0,PLLFLLFRAC=0 */
  #define SYSTEM_SIM_CLKDIV3_VALUE     0x00U               /* SIM_CLKDIV3 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: SDHCSRC=0,LPUARTSRC=0,TPMSRC=1,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=3,TRACECLKSEL=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0,USBREGEN=0,USBSLSRC=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x01030000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 3)
  #define DEFAULT_SYSTEM_CLOCK         4000000U            /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_BLPE /* Clock generator mode */
  /* MCG_C1: CLKS=2,FRDIV=4,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0xA2U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=1,LP=1,IRCS=1 */
  #define SYSTEM_MCG_C2_VALUE          0x27U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=1,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x02U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN=0,PLLSTEN=0,PRDIV=0 */
  #define SYSTEM_MCG_C5_VALUE          0x00U               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV=0 */
  #define SYSTEM_MCG_C6_VALUE          0x00U               /* MCG_C6 */
  /* MCG_C7: OSCSEL=0 */
  #define SYSTEM_MCG_C7_VALUE          0x00U               /* MCG_C7 */
  /* MCG_C9: PLL_CME=0,PLL_LOCRE=0,EXT_PLL_LOCS=0 */
  #define SYSTEM_MCG_C9_VALUE          0x00U               /* MCG_C9 */
  /* MCG_C11: PLLCS=0 */
  #define SYSTEM_MCG_C11_VALUE         0x00U               /* MCG_C11 */
  /* OSC_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x80U               /* OSC_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=3,OUTDIV2=3,OUTDIV3=3,OUTDIV4=0x0F */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x333F0000U         /* SIM_CLKDIV1 */
  /* SIM_CLKDIV2: USBDIV=0,USBFRAC=0 */
  #define SYSTEM_SIM_CLKDIV2_VALUE     0x00U               /* SIM_CLKDIV2 */
  /* SIM_CLKDIV3: PLLFLLDIV=0,PLLFLLFRAC=0 */
  #define SYSTEM_SIM_CLKDIV3_VALUE     0x00U               /* SIM_CLKDIV3 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: SDHCSRC=0,LPUARTSRC=0,TPMSRC=1,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=3,TRACECLKSEL=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0,USBREGEN=0,USBSLSRC=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x01030000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 4)
  #define DEFAULT_SYSTEM_CLOCK         120000000U          /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_PEE /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=4,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x22U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0x24U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN=0,PLLSTEN=0,PRDIV=1 */
  #define SYSTEM_MCG_C5_VALUE          0x01U               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV=0x0E */
  #define SYSTEM_MCG_C6_VALUE          0x4EU               /* MCG_C6 */
  /* MCG_C7: OSCSEL=0 */
  #define SYSTEM_MCG_C7_VALUE          0x00U               /* MCG_C7 */
  /* MCG_C9: PLL_CME=0,PLL_LOCRE=0,EXT_PLL_LOCS=0 */
  #define SYSTEM_MCG_C9_VALUE          0x00U               /* MCG_C9 */
  /* MCG_C11: PLLCS=0 */
  #define SYSTEM_MCG_C11_VALUE         0x00U               /* MCG_C11 */
  /* OSC_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x80U               /* OSC_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=1,OUTDIV3=1,OUTDIV4=4 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x01140000U         /* SIM_CLKDIV1 */
  /* SIM_CLKDIV2: USBDIV=1,USBFRAC=0 */
  #define SYSTEM_SIM_CLKDIV2_VALUE     0x12U               /* SIM_CLKDIV2 */
  /* SIM_CLKDIV3: PLLFLLDIV=0,PLLFLLFRAC=0 */
  #define SYSTEM_SIM_CLKDIV3_VALUE     0x00U               /* SIM_CLKDIV3 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: SDHCSRC=0,LPUARTSRC=0,TPMSRC=1,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=1,TRACECLKSEL=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0,USBREGEN=0,USBSLSRC=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x01010000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 5)
  #define DEFAULT_SYSTEM_CLOCK         120000000U          /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_PEE /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=4,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x22U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0x24U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN=0,PLLSTEN=0,PRDIV=1 */
  #define SYSTEM_MCG_C5_VALUE          0x01U               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV=0x0E */
  #define SYSTEM_MCG_C6_VALUE          0x4EU               /* MCG_C6 */
  /* MCG_C7: OSCSEL=0 */
  #define SYSTEM_MCG_C7_VALUE          0x00U               /* MCG_C7 */
  /* MCG_C9: PLL_CME=0,PLL_LOCRE=0,EXT_PLL_LOCS=0 */
  #define SYSTEM_MCG_C9_VALUE          0x00U               /* MCG_C9 */
  /* MCG_C11: PLLCS=0 */
  #define SYSTEM_MCG_C11_VALUE         0x00U               /* MCG_C11 */
  /* OSC_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x80U               /* OSC_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=1,OUTDIV3=1,OUTDIV4=4 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x01140000U         /* SIM_CLKDIV1 */
  /* SIM_CLKDIV2: USBDIV=1,USBFRAC=0 */
  #define SYSTEM_SIM_CLKDIV2_VALUE     0x12U               /* SIM_CLKDIV2 */
  /* SIM_CLKDIV3: PLLFLLDIV=0,PLLFLLFRAC=0 */
  #define SYSTEM_SIM_CLKDIV3_VALUE     0x00U               /* SIM_CLKDIV3 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: SDHCSRC=0,LPUARTSRC=0,TPMSRC=1,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=1,TRACECLKSEL=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0,USBREGEN=0,USBSLSRC=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x01010000U         /* SIM_SOPT2 */
#endif
#else
  #define DEFAULT_SYSTEM_CLOCK         20971520u
#endif


/****************************************************************************************
 * Function to configure the system clock to high-speed, 180MHz
 ***************************************************************************************/
void K65TWR_BootClock(void);

#endif  /* #if !defined(K65TWR_CLKCFG_H_) */
