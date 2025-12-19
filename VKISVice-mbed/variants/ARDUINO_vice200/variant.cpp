#include "Arduino.h"
#include "pinDefinitions.h"


////////////////// for vice-200

PinDescription g_APinDescription[] = {
  // D0 - D7  
  { P0_11,  NULL, NULL, NULL },     // D0   / TX1      becas
  { P0_12, NULL, NULL, NULL },     // D1   / RX1            
  { NC, NULL, NULL, NULL },     // D2       NOT CONNECTED 
  { P0_19, NULL, NULL, NULL },     // D3   / RX2    
  { P0_21, NULL, NULL, NULL },     // D4             
  { P0_17, NULL, NULL, NULL },     // D5        IMU/MAGNOMETER SDA
  { P0_15, NULL, NULL, NULL },     // D6        IMU/MAGNOMETER SCL
  { NC, NULL, NULL, NULL },     // D7        NOT CONNECTED

  // D8 - D13
  { P0_27, NULL, NULL, NULL },     // D8        /SS        
  { NC, NULL, NULL, NULL },     // D9                NOT CONNECTED        
  { P0_5,  NULL, NULL, NULL },     // D10            
  { P0_4,  NULL, NULL, NULL },     // D11              
  { P0_26,  NULL, NULL, NULL },     // D12   / MOSI      
  { P1_9,  NULL, NULL, NULL },     // D13   (LED)            

  // D14 - D19 
  { P0_7, NULL, NULL, NULL },     // D14   / SCK         
  { P0_16,  NULL, NULL, NULL },     // D15   / TX2            
  { P0_20,  NULL, NULL, NULL },     // D16                                      
  { P0_14,  NULL, NULL, NULL },     // D17   / SCL           
  { P0_13, NULL, NULL, NULL },     // D18   / SDA                 
  { P0_6, NULL, NULL, NULL },     // D19   / MISO             
};


extern "C" {
  unsigned int PINCOUNT_fn() {
    return (sizeof(g_APinDescription) / sizeof(g_APinDescription[0]));
  }
}

#include "nrf_rtc.h"
#include "nrf_uarte.h"
#include "nrf_uart.h"

void initVariant() {
  // If you don't use SWO, this is safe and prevents trace routing weirdness.
  NRF_CLOCK->TRACECONFIG = 0;

  // Some bootloaders leave RTC1 COMPARE0 IRQ enabled; disable to avoid lockups.
  nrf_rtc_event_disable(NRF_RTC1, NRF_RTC_INT_COMPARE0_MASK);
  nrf_rtc_int_disable(NRF_RTC1, NRF_RTC_INT_COMPARE0_MASK);

  // Disable UARTE0 which may be enabled by bootloader
  nrf_uarte_task_trigger(NRF_UARTE0, NRF_UARTE_TASK_STOPRX);
  while (!nrf_uarte_event_check(NRF_UARTE0, NRF_UARTE_EVENT_RXTO)) { }
  NRF_UARTE0->ENABLE = 0;
  NRF_UART0->ENABLE = 0;

  // Disable PWMs / unmap outputs to avoid stray pin drive
  NRF_PWM_Type* PWM[] = {
    NRF_PWM0, NRF_PWM1, NRF_PWM2
  #ifdef NRF_PWM3
    ,NRF_PWM3
  #endif
  };

  for (unsigned int i = 0; i < (sizeof(PWM)/sizeof(PWM[0])); i++) {
    PWM[i]->ENABLE = 0;
    PWM[i]->PSEL.OUT[0] = 0xFFFFFFFFUL;
  }
}


#ifdef SERIAL_CDC

static void utox8(uint32_t val, uint8_t* s) {
  for (int i = 0; i < 16; i=i+2) {
    int d = val & 0XF;
    val = (val >> 4);

    s[15 - i -1] = d > 9 ? 'A' + d - 10 : '0' + d;
    s[15 - i] = '\0';
  }
}

uint8_t getUniqueSerialNumber(uint8_t* name) {
  #define SERIAL_NUMBER_WORD_0  NRF_FICR->DEVICEADDR[1]
  #define SERIAL_NUMBER_WORD_1  NRF_FICR->DEVICEADDR[0]

  utox8(SERIAL_NUMBER_WORD_0, &name[0]);
  utox8(SERIAL_NUMBER_WORD_1, &name[16]);

  return 32;
}

void _ontouch1200bps_() {
  __disable_irq();
  NRF_POWER->GPREGRET = DFU_MAGIC_SERIAL_ONLY_RESET;
  NVIC_SystemReset();
}

#endif
