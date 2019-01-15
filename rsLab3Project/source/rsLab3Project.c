/****************************************************************************************
* EE344, rsLab3Project
*   Program allows user to use three different counter implementations
*   all of which are incremented by SW2 being pressed. The implementations are
*   software only, hardware interrupts only, and hardware and software combined.
*   The user types s, h, or b, and then hits enter to go into a counter state,
*   and presses q to exit a counter state.
*
* Robert Sanborn, 10/29/2018
*
****************************************************************************************/
#include "MCUType.h"               /* Include project header file                      */
#include "BasicIO.h"
#include "K65TWR_ClkCfg.h"

#define COMMAND_PARSE             'q'
#define SOFTWARE_COUNTER          's'
#define HARDWARE_COUNTER          'h'
#define COMBINATION_COUNTER       'b'

#define ZERO_ADDR 0x00000000
#define HIGH_ADDR 0x001FFFFF
#define USER_IN_LN 2U

#define INVALID_INPUT(x) ((x != SOFTWARE_COUNTER) && (x != HARDWARE_COUNTER) && (x != COMBINATION_COUNTER))
/* For PORTA SW2 interrupt flag*/
#define SW2_BIT          (1U << 4U)
#define SW2_ISF          (PORTA->ISFR & SW2_BIT)
#define SW2_CLR_ISF()    (PORTA->ISFR = SW2_BIT)
#define SW2_INPUT        (GPIOA->PDIR & SW2_BIT)



#define ISF_DISABLE        0U
#define ISF_INT_REDGE      9U     /* Set ISF to falling edge*/
#define MUX_GPIO_ENABLE    1U
#define PIN_4              4U
#define LEADING_ZEROS      1U    /* Leading zeros*/

/**********************************************************************************
* Function Prototypes
**********************************************************************************/

/**********************************************************************************
* PORTA-IRQHandler()
*
* Description:  clears ISF for SW2 immediately then updates
*               global variable Sw_Cnt_Globe so that counter display
*               for hardware counter can be incremented
*
* Return Value: none
*
* Arguments:    none
**********************************************************************************/
void PORTA_IRQHandler(void);


/**********************************************************************************
* GPIOAPeriphIni(INT8U pin_num, INT8U mux, INT8U irq_code)
*
* Description:  Initializes PORTA Peripheral
*
* Return Value: none
*
* Arguments:    INT8U pin_num,   The PCR number of the Peripheral
*               INT8U irq_code,  The interrupt request code
*               INT8U mux,       The Pin Mux Control code
**********************************************************************************/
static void GPIOAPeriphIni(INT8U pin_num, INT8U mux, INT8U irq_code);


/**********************************************************************************
* CalcChkSum() -ascertains checksum for memory block indicated by starting and
*               ending addresses
*
* Description:
*
* Return Value:
*
* Arguments:    startaddr is pointer to the initial address of the memory block
*               endaddr is the pointer to the last address of the memory block
**********************************************************************************/
static INT16U CalcChkSum(INT8U *startaddr, INT8U *endaddr);


/**********************************************************************************
* Private Strings
**********************************************************************************/

static const INT8C InitialMessage[] = {
    "Please enter a command key then press enter. \n\r"
    "Type 's' to demonstrate the software only counter.\n\r"
    "Type 'b' to demonstrate the hardware and software combination counter.\n\r"
    "Type 'h' to demonstrate the hardware only counter.\n\r"
    "To terminate any counter protocol just press 'q'.\n\r"
    };

static const INT8C ErrorMessage[] = {
    "Please type only one letter and then press enter. \n\r"};

static const INT8C ErrorMessage2[] = {
    "Must type s, h, or b for selection.\n\r"};


/**********************************************************************************
* Program
**********************************************************************************/
static INT16U Sw_Cnt_Globe;            /* Global count variable for hardware*/

void main(void){
    INT8C prg_state;
    INT8C userentry[USER_IN_LN];
    INT8U toolong;
    INT32U lastsw;
    INT32U currsw;
    INT16U sw_cnt;

    K65TWR_BootClock();
    BIOOpen(BIO_BIT_RATE_9600);            /* Initialize Serial Port  */

    /* Output Low Address, High Address, and check sum to terminal
     * in the form LLLLLLLL-HHHHHHHH XXXX where, LLLLLLLL
     * is the low address HHHHHHHH is the high address and
     *  XXXX is the check sum */
    BIOPutStrg("CS : ");
    BIOOutHexWord(ZERO_ADDR);
    BIOPutStrg("-");
    BIOOutHexWord(HIGH_ADDR);
    BIOPutStrg(" ");
    BIOOutHexHWord(CalcChkSum( ((void *)ZERO_ADDR),((void *)HIGH_ADDR) ) );
    BIOOutCRLF();

    /* Output user prompt */
    BIOPutStrg(InitialMessage);

    prg_state = COMMAND_PARSE;

    while (1U){
        switch(prg_state){

        case(COMMAND_PARSE):
            BIOOutCRLF();
            toolong = BIOGetStrg(USER_IN_LN, userentry);
            if(toolong){
                BIOPutStrg(ErrorMessage);
            } else {
               /* Check if user entered s, h, or b,
                *  if not stay in Command Parse     */
               if ( INVALID_INPUT(userentry[0U]) ) {
                   /*Stay in Command Parse*/
                   BIOPutStrg(ErrorMessage2);
               } else {
                   prg_state = userentry[0U];
               }
            }
            break;

        case(SOFTWARE_COUNTER):
            sw_cnt = 0;
            /* Begin Outputting Counter */
            BIOOutDecHWord(sw_cnt, LEADING_ZEROS);
            BIOWrite('\r'); //>>> should send \n as well

            /* Initialize SW2 Peripheral, no interrupt enabled  */
            GPIOAPeriphIni(PIN_4, MUX_GPIO_ENABLE, ISF_DISABLE);
            lastsw |= SW2_BIT; /*Preset to 1 b/c GPIOA_PDIR is active low */
            lastsw &= SW2_BIT;
            while (BIORead() != 'q') {
                /* SW2 is active low thus detect rising edge
                 *  for when user stops pressing SW2 */
                currsw = SW2_INPUT;
                if ((currsw == SW2_BIT) && (lastsw == 0x00)) {
                    sw_cnt++;
                    BIOOutDecHWord(sw_cnt, LEADING_ZEROS);
                    BIOWrite('\r');
                } else {}
                lastsw = currsw;
            }
            BIOOutCRLF();
            BIOOutCRLF();

            /* Output user prompt and return to Command Parse */
            BIOPutStrg(InitialMessage);
            prg_state = COMMAND_PARSE;
            break;

        case(HARDWARE_COUNTER):
            sw_cnt = 0;
            Sw_Cnt_Globe = 0;

            /* Begin Outputting Counter */
            BIOOutDecHWord(Sw_Cnt_Globe, LEADING_ZEROS);
            BIOWrite('\r');

            /* Initialize Interrupt for SW2 Rising Edge*/
            SW2_CLR_ISF();
            NVIC_ClearPendingIRQ(PORTA_IRQn);
            NVIC_EnableIRQ(PORTA_IRQn);

            /* SW2 is active low thus detect rising edge
             *  for when user stops pressing SW2 */
            GPIOAPeriphIni(PIN_4, MUX_GPIO_ENABLE, ISF_INT_REDGE);

            /* while user has not entered 'q' continue
             *  to output counter to terminal*/
            while (BIORead() != 'q'){
                if (sw_cnt != Sw_Cnt_Globe){
                    sw_cnt = Sw_Cnt_Globe;
                    BIOOutDecHWord(Sw_Cnt_Globe, LEADING_ZEROS);
                    BIOWrite('\r');
                } else {}
            }
            BIOOutCRLF();
            BIOOutCRLF();
            NVIC_DisableIRQ(PORTA_IRQn);

            /* Output user prompt and return to Command Parse */
            BIOPutStrg(InitialMessage);
            prg_state = COMMAND_PARSE;
            break;

        case(COMBINATION_COUNTER):
            sw_cnt = 0;

            /* SW2 is active low thus detect rising edge
             *  for when user stops pressing SW2 */
            GPIOAPeriphIni(PIN_4, MUX_GPIO_ENABLE, ISF_INT_REDGE);
            SW2_CLR_ISF();

            BIOOutDecHWord(sw_cnt, LEADING_ZEROS);
            BIOWrite('\r');

            while(BIORead() != 'q'){
                /* When Interrupt Flag is set, clear it, & update counter*/
                if (SW2_ISF != 0){
                    SW2_CLR_ISF();
                    sw_cnt++;
                    BIOOutDecHWord(sw_cnt, LEADING_ZEROS);
                    BIOWrite('\r');
                } else {}
            }
            BIOOutCRLF();
            BIOOutCRLF();

            /* Output user prompt and return to Command Parse */
            BIOPutStrg(InitialMessage);
            prg_state = COMMAND_PARSE;
            break;

        /* If somehow the four states are exited completely*/
        default:
            prg_state = COMMAND_PARSE;
            break;
        }
    }
}


/**********************************************************************************
* PORTA-IRQHandler()
*
* Description:  clears ISF for SW2 immediately then updates
*               global variable Sw_Cnt_Globe so that counter display
*               for hardware counter can be incremented
*
* Return Value: none
*
* Arguments:    none
**********************************************************************************/
void PORTA_IRQHandler(void){
    SW2_CLR_ISF();
    Sw_Cnt_Globe++;
}


/**********************************************************************************
* GPIOAPeriphIni()
*
* Description:  Initializes PORTA Peripheral as specified by user
*
* Return Value: none
*
* Arguments:    INT8U pin_num,   The PCR number of the Peripheral
*               INT8U irq_code,  The interrupt request code
*               INT8U mux,       The Pin Mux Control code
**********************************************************************************/
static void GPIOAPeriphIni(INT8U pin_num, INT8U mux_code, INT8U irq_code){
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    PORTA->PCR[pin_num] = PORT_PCR_MUX(mux_code)|PORT_PCR_IRQC(irq_code);
}


/**********************************************************************************
* CalcChkSum() -ascertains checksum for memory block indicated by starting and
*               ending addresses
*
* Description:  Loads every byte from starting address to ending address
*               and takes the first 16 bits of the sum of all said bytes.
*               Note that it if starting address is greater than ending address
*               function will only return byte stored at ending address.
*
* Return Value: c_sum, 16 bit unsigned integer, the first 16 bits of the sum
*               of all bytes between the two addresses
*
* Arguments:    startaddr is pointer to the initial address of the memory block
*               endaddr is the pointer to the last address of the memory block
**********************************************************************************/
static INT16U CalcChkSum(INT8U *startaddr, INT8U *endaddr){
    INT16U c_sum = 0;
    INT8U membyte;
    INT8U *addr = startaddr;

    /*Iterate over all memory locations from start address to address
     * right before ending address and sum up all bytes*/
    while(addr < endaddr){
        membyte = *addr;
        addr++;
        c_sum += (INT16U)membyte;
    }
    c_sum += ( (INT16U)(*endaddr) );

    return c_sum;
}


