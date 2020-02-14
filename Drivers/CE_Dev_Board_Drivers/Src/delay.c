// file: delay.c
// created by: Grant Wilk
// date created: 12/10/2019
// last modified: 12/10/2019
// description: contains functions for making delays using the systick timer

// STK addresses
#define STK_BASE 0xE000E010
#define STK_CTRL (STK_BASE + 0x00)
#define STK_LOAD (STK_BASE + 0x04)
#define STK_VAL  (STK_BASE + 0x08)

// STK values
#define STK_CTRL_ENABLE (1 << 0)
#define STK_CTRL_COUNTFLAG (1 << 16)
#define STK_RESET 0x0

// time values
# define CYCLES_PER_MS 2000
# define CYCLES_PER_US 2


// delays for some number of milliseconds
// @ param milliseconds - the number of milliseconds to delay for
// @ return void
void delay_ms(int milliseconds){
    int* stk_ctrl = (int*) STK_CTRL;
    int* stk_load = (int*) STK_LOAD;
    int* stk_val = (int*) STK_VAL;

    // reset systick
    *stk_val = STK_RESET;

    // set systick reload value
    *stk_load = milliseconds * CYCLES_PER_MS;

    // start systick
    *stk_ctrl |= STK_CTRL_ENABLE;

    // wait until the count flag goes high
    while (!(*stk_ctrl & STK_CTRL_COUNTFLAG));

    // stop systick
    *stk_ctrl &= ~STK_CTRL_ENABLE;
}


// delays for some number of microseconds
// @ param microseconds - the number of microseconds to delay for
// @ return void
void delay_us(int microseconds){
    int* stk_ctrl = (int*) STK_CTRL;
    int* stk_load = (int*) STK_LOAD;
    int* stk_val = (int*) STK_VAL;

    // reset systick
    *stk_val = STK_RESET;

    // set systick reload value
    *stk_load = microseconds * CYCLES_PER_US;

    // start systick
    *stk_ctrl |= STK_CTRL_ENABLE;

    // wait until the count flag goes high
    while (!(*stk_ctrl & STK_CTRL_COUNTFLAG));

    // stop systick
    *stk_ctrl &= ~STK_CTRL_ENABLE;

}
