
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <spi.h>
#include <MCP2515.h>
#include <fram.h>

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT   = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//#pragma interrupt _Receive

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 20000000
#define _CAN_BAUDRATE        2

//#define TXB1SIDH    0b00000000
//#define TXB1SIDL  
#define _RXB0D0 0b01100110

/*Prtotype*/
void CONFIG();
void interrupt isr();

char CSS[4] = {0b00000000, 0b00001000, 0b00000000, 0b00000000};                 //{SIDH, SIDL, EID8, EID0}

int i = 0;                                                                      //Write Point
int j = 0;                                                                      //Read Point

/*受信バッファ*/
char rx_sidh[10];
char rx_sidl[10];
char rx_eid8[10];
char rx_eid0[10];
char data_0[8], data_1[8], data_2[8], data_3[8], data_4[8], data_5[8], data_6[8], data_7[8], data_8[8], data_9[8];



void main(void){
    
    CONFIG();
    __delay_ms(100);
    
    while(1){
        
        RC6 = 0;                                                                //LED OFF
        RC1 = 0;                                                                
        RC7 = 0;                                                                
        
        if(j <= i){
            
            for(j; j == i; j++){

                RC6 = 0;
                RC1 = 0; 
                RC7 = 0; 

                CSS[2] = rx_sidh[j];
                CSS[3] = rx_sidl[j];
                Load_TX_Data(_F_TXB0SIDH, 4, CSS);                              //ID送信
                
                if(j == 0){
                    Load_TX_Data(_F_TXB0D0, 8, data_0);                         //データ送信
                }else if(j == 1){
                    Load_TX_Data(_F_TXB0D0, 8, data_1);
                }else if(j == 2){
                    Load_TX_Data(_F_TXB0D0, 8, data_2);
                }else if(j == 3){
                    Load_TX_Data(_F_TXB0D0, 8, data_3);
                }else if(j == 4){
                    Load_TX_Data(_F_TXB0D0, 8, data_4);
                }else if(j == 5){
                    Load_TX_Data(_F_TXB0D0, 8, data_5);
                }else if(j == 6){
                    Load_TX_Data(_F_TXB0D0, 8, data_6);
                }else if(j == 7){
                    Load_TX_Data(_F_TXB0D0, 8, data_7);
                }else if(j == 8){
                    Load_TX_Data(_F_TXB0D0, 8, data_8);
                }else if(j == 9){
                    Load_TX_Data(_F_TXB0D0, 8, data_9);
                }
                
                RTS0_CSS(0);                                                    //送信要求
                
            }
            
        }else{
            
            for(j; j < 10 ; j++){

                RC6 = 0;
                RC1 = 0; 
                RC7 = 0; 

                CSS[2] = rx_sidh[j];
                CSS[3] = rx_sidl[j];
                Load_TX_Data(_F_TXB0SIDH, 4, CSS);                              //ID送信
                
                if(j == 0){
                    Load_TX_Data(_F_TXB0D0, 8, data_0);                         //データ送信
                }else if(j == 1){
                    Load_TX_Data(_F_TXB0D0, 8, data_1);
                }else if(j == 2){
                    Load_TX_Data(_F_TXB0D0, 8, data_2);
                }else if(j == 3){
                    Load_TX_Data(_F_TXB0D0, 8, data_3);
                }else if(j == 4){
                    Load_TX_Data(_F_TXB0D0, 8, data_4);
                }else if(j == 5){
                    Load_TX_Data(_F_TXB0D0, 8, data_5);
                }else if(j == 6){
                    Load_TX_Data(_F_TXB0D0, 8, data_6);
                }else if(j == 7){
                    Load_TX_Data(_F_TXB0D0, 8, data_7);
                }else if(j == 8){
                    Load_TX_Data(_F_TXB0D0, 8, data_8);
                }else if(j == 9){
                    Load_TX_Data(_F_TXB0D0, 8, data_9);
                }
                
                RTS0_CSS(0);                                                    //送信要求
                
            }
            
            for(j = 0; j == i; j++){
                
                RC6 = 0;
                RC1 = 0; 
                RC7 = 0; 

                CSS[2] = rx_sidh[j];
                CSS[3] = rx_sidl[j];
                Load_TX_Data(_F_TXB0SIDH, 4, CSS);                              //ID送信
                
                if(j == 0){
                    Load_TX_Data(_F_TXB0D0, 8, data_0);                         //データ送信
                }else if(j == 1){
                    Load_TX_Data(_F_TXB0D0, 8, data_1);
                }else if(j == 2){
                    Load_TX_Data(_F_TXB0D0, 8, data_2);
                }else if(j == 3){
                    Load_TX_Data(_F_TXB0D0, 8, data_3);
                }else if(j == 4){
                    Load_TX_Data(_F_TXB0D0, 8, data_4);
                }else if(j == 5){
                    Load_TX_Data(_F_TXB0D0, 8, data_5);
                }else if(j == 6){
                    Load_TX_Data(_F_TXB0D0, 8, data_6);
                }else if(j == 7){
                    Load_TX_Data(_F_TXB0D0, 8, data_7);
                }else if(j == 8){
                    Load_TX_Data(_F_TXB0D0, 8, data_8);
                }else if(j == 9){
                    Load_TX_Data(_F_TXB0D0, 8, data_9);
                }
                
                RTS0_CSS(0);                                                    //送信要求
                
            }
            
        }
              
    }  
}

void CONFIG(){
    
    OSCCON = 0b01101000;
    ANSEL  = 0b00000000;
    ANSELH = 0b00000000;
    TRISC  = 0b00000000;
    PORTC  = 0b00000000;
    
    spi_init();
    __delay_ms(100);
    
    MCP2515_init(_CAN_BAUDRATE);                                                
    Write(_TXB0DLC , 0b00001000);                                                
    MCP2515_Open(1);                                                            //0:通常モード，1:割り込み，タイマー
}

void interrupt isr(){
    
    rx_sidh[i] = Read(_RXB0SIDH);
    rx_sidl[i] = Read(_RXB0SIDL);
    rx_eid8[i] = Read(_RXB0EID8);
    rx_eid0[i] = Read(_RXB0EID0);
    
    if(i == 0){
        RC6 = 1;                                                                //LED ON
        data_0[0] = Read(_RXB0D0);
    }else if(i == 1){
        RC1 = 1; 
        data_1[0] = Read(_RXB0D0);
    }else if(i == 2){
        RC7 = 1; 
        data_2[0] = Read(_RXB0D0);
    }else if(i == 3){
        data_3[0] = Read(_RXB0D0);
    }else if(i == 4){
        data_4[0] = Read(_RXB0D0);
    }else if(i == 5){
        data_5[0] = Read(_RXB0D0);
    }else if(i == 6){
        data_6[0] = Read(_RXB0D0);
    }else if(i == 7){
        data_7[0] = Read(_RXB0D0);
    }else if(i == 8){
        data_8[0] = Read(_RXB0D0);
    }else if(i == 9){
        data_9[0] = Read(_RXB0D0);
    }
    
    if(i == 9){
        i = 0;
    }else{
        i++;
    }
    
    Write(_CANINTF, 0b00000000);                                                //受信フラグクリア
    INTCONbits.INTF = 0;                                                        //割り込みフラグクリア
}             
