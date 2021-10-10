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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 20000000
#define _CAN_BAUDRATE        2

#define RXF0SIDH 0b00000000                                                     //フィルタ設定
#define RXF0SIDL 0b00000000
#define RXF0EID8 0b00100000
//#define RXF0EID8 0b01000000
//#define RXF0EID8 0b01100000
#define RXF0EID0 0b00000000
#define RXM0SIDH 0b00000000                                                     //マスク設定
#define RXM0SIDL 0b00000000
#define RXM0EID8 0b00000000
#define RXM0EID0 0b00000000

//#define TXB1SIDH    0b00000000
//#define TXB1SIDL  

/*Prtotype*/
void CONFIG();

enum MODE{mode_1, mode_2, mode_3, mode_4, mode_5, mode_6, mode_7, mode_8, mode_9, mode_10, mode_11, mode_12, mode_13} Mode;

/*Sub_Aのデータ*/
char data_1[8] = {1, 1, 1, 1, 1, 1, 1, 1};
char data_2[8] = {2, 2, 2, 2, 2, 2, 2, 2};
char data_3[8] = {3, 3, 3, 3, 3, 3, 3, 3};
char data_4[8] = {4, 4, 4, 4, 4, 4, 4, 4};
char data_5[8] = {5, 5, 5, 5, 5, 5, 5, 5};
char data_6[8] = {6, 6, 6, 6, 6, 6, 6, 6};
char data_7[8] = {7, 7, 7, 7, 7, 7, 7, 7};
char data_8[8] = {8, 8, 8, 8, 8, 8, 8, 8};
char data_9[8] = {9, 9, 9, 9, 9, 9, 9, 9};
char data_10[8] = {10, 10, 10, 10, 10, 10, 10, 10};
char data_11[8] = {11, 11, 11, 11, 11, 11, 11, 11};
char data_12[8] = {12, 12, 12, 12, 12, 12, 12, 12};
char data_13[8] = {13, 13, 13, 13, 13, 13, 13, 13};

/*Sub_Bのデータ
char data_1[8] = {21, 21, 21, 21, 21, 21, 21, 21};
char data_2[8] = {22, 22, 22, 22, 22, 22, 22, 22};
char data_3[8] = {23, 23, 23, 23, 23, 23, 23, 23};
char data_4[8] = {24, 24, 24, 24, 24, 24, 24, 24};
char data_5[8] = {25, 25, 25, 25, 25, 25, 25, 25};
char data_6[8] = {26, 26, 26, 26, 26, 26, 26, 26};
char data_7[8] = {27, 27, 27, 27, 27, 27, 27, 27};
char data_8[8] = {28, 28, 28, 28, 28, 28, 28, 28};
char data_9[8] = {29, 29, 29, 29, 29, 29, 29, 29};
char data_10[8] = {30, 30, 30, 30, 30, 30, 30, 30};
char data_11[8] = {31, 31, 31, 31, 31, 31, 31, 31};
char data_12[8] = {32, 32, 32, 32, 32, 32, 32, 32};
char data_13[8] = {33, 33, 33, 33, 33, 33, 33, 33};
*/
/*Sub_Cのデータ
char data_1[8] = {41, 41, 41, 41, 41, 41, 41, 41};
char data_2[8] = {42, 42, 42, 42, 42, 42, 42, 42};
char data_3[8] = {43, 43, 43, 43, 43, 43, 43, 43};
char data_4[8] = {44, 44, 44, 44, 44, 44, 44, 44};
char data_5[8] = {45, 45, 45, 45, 45, 45, 45, 45};
char data_6[8] = {46, 46, 46, 46, 46, 46, 46, 46};
char data_7[8] = {47, 47, 47, 47, 47, 47, 47, 47};
char data_8[8] = {48, 48, 48, 48, 48, 48, 48, 48};
char data_9[8] = {49, 49, 49, 49, 49, 49, 49, 49};
char data_10[8] = {50, 50, 50, 50, 50, 50, 50, 50};
char data_11[8] = {51, 51, 51, 51, 51, 51, 51, 51};
char data_12[8] = {52, 52, 52, 52, 52, 52, 52, 52};
char data_13[8] = {53, 53, 53, 53, 53, 53, 53, 53};
*/
/*Sub_AのID*/
char Sub_1[4] = {0b00000001, 0b00001000, 0b00000000, 0b00000000};               
char Sub_2[4] = {0b00000010, 0b00001000, 0b00000000, 0b00000000};               
char Sub_3[4] = {0b00000011, 0b00001000, 0b00000000, 0b00000000};               
char Sub_4[4] = {0b00000100, 0b00001000, 0b00000000, 0b00000000};               
char Sub_5[4] = {0b00000101, 0b00001000, 0b00000000, 0b00000000};               
char Sub_6[4] = {0b00000110, 0b00001000, 0b00000000, 0b00000000};               
char Sub_7[4] = {0b00000111, 0b00001000, 0b00000000, 0b00000000};               
char Sub_8[4] = {0b00001000, 0b00001000, 0b00000000, 0b00000000};               
char Sub_9[4] = {0b00001001, 0b00001000, 0b00000000, 0b00000000};               
char Sub_10[4] = {0b00001010, 0b00001000, 0b00000000, 0b00000000};               
char Sub_11[4] = {0b00001011, 0b00001000, 0b00000000, 0b00000000};               
char Sub_12[4] = {0b00001100, 0b00001000, 0b00000000, 0b00000000};               
char Sub_13[4] = {0b00001101, 0b00001000, 0b00000000, 0b00000000};               

/*Sub_BのID
char Sub_1[4] = {0b00000001, 0b00101000, 0b00000000, 0b00000000};               
char Sub_2[4] = {0b00000010, 0b00101000, 0b00000000, 0b00000000};               
char Sub_3[4] = {0b00000011, 0b00101000, 0b00000000, 0b00000000};               
char Sub_4[4] = {0b00000100, 0b00101000, 0b00000000, 0b00000000};               
char Sub_5[4] = {0b00000101, 0b00101000, 0b00000000, 0b00000000};               
char Sub_6[4] = {0b00000110, 0b00101000, 0b00000000, 0b00000000};               
char Sub_7[4] = {0b00000111, 0b00101000, 0b00000000, 0b00000000};               
char Sub_8[4] = {0b00001000, 0b00101000, 0b00000000, 0b00000000};               
char Sub_9[4] = {0b00001001, 0b00101000, 0b00000000, 0b00000000};               
char Sub_10[4] = {0b00001010, 0b00101000, 0b00000000, 0b00000000};               
char Sub_11[4] = {0b00001011, 0b00101000, 0b00000000, 0b00000000};               
char Sub_12[4] = {0b00001100, 0b00101000, 0b00000000, 0b00000000};               
char Sub_13[4] = {0b00001101, 0b00101000, 0b00000000, 0b00000000};               
*/
/*Sub_CのID
char Sub_1[4] = {0b00000001, 0b01001000, 0b00000000, 0b00000000};               
char Sub_2[4] = {0b00000010, 0b01001000, 0b00000000, 0b00000000};               
char Sub_3[4] = {0b00000011, 0b01001000, 0b00000000, 0b00000000};               
char Sub_4[4] = {0b00000100, 0b01001000, 0b00000000, 0b00000000};               
char Sub_5[4] = {0b00000101, 0b01001000, 0b00000000, 0b00000000};               
char Sub_6[4] = {0b00000110, 0b01001000, 0b00000000, 0b00000000};               
char Sub_7[4] = {0b00000111, 0b01001000, 0b00000000, 0b00000000};               
char Sub_8[4] = {0b00001000, 0b01001000, 0b00000000, 0b00000000};               
char Sub_9[4] = {0b00001001, 0b01001000, 0b00000000, 0b00000000};               
char Sub_10[4] = {0b00001010, 0b01001000, 0b00000000, 0b00000000};               
char Sub_11[4] = {0b00001011, 0b01001000, 0b00000000, 0b00000000};               
char Sub_12[4] = {0b00001100, 0b01001000, 0b00000000, 0b00000000};               
char Sub_13[4] = {0b00001101, 0b01001000, 0b00000000, 0b00000000};               
*/

int i = 0;
 

void main(void){
    
    CONFIG();
    __delay_ms(100);
    
    while(1){
        
        for(i=0; i<13; i++){
            
            if(i == 0){
                Mode = mode_1;
            }else if( i == 1){
                Mode = mode_2;
            }else if( i == 2){
                Mode = mode_3;
            }else if( i == 3){
                Mode = mode_4;
            }else if( i == 4){
                Mode = mode_5;
            }else if( i == 5){
                Mode = mode_6;
            }else if( i == 6){
                Mode = mode_7;
            }else if( i == 7){
                Mode = mode_8;
            }else if( i == 8){
                Mode = mode_9;
            }else if( i == 9){
                Mode = mode_10;
            }else if( i == 10){
                Mode = mode_11;
            }else if( i == 11){
                Mode = mode_12;
            }else{
                Mode = mode_13;
            }
        
            switch(Mode){

                case mode_1:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_1);                        //ID送信        
                    Load_TX_Data(_F_TXB0D0, 8, data_1);                         //データ送信   
                    break;

                case mode_2:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_2);                                 
                    Load_TX_Data(_F_TXB0D0, 8, data_2);                             
                    break;

                case mode_3:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_3);                                 
                    Load_TX_Data(_F_TXB0D0, 8, data_3);                             
                    break;
                    
                case mode_4:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_4);                                 
                    Load_TX_Data(_F_TXB0D0, 8, data_4);                            
                    break;
                
                case mode_5:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_5);                                
                    Load_TX_Data(_F_TXB0D0, 8, data_5);                             
                    break;
                    
                case mode_6:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_6);                                 
                    Load_TX_Data(_F_TXB0D0, 8, data_6);                             
                    break;
                    
                case mode_7:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_7);                                
                    Load_TX_Data(_F_TXB0D0, 8, data_7);                             
                    break;
                    
                case mode_8:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_8);                                
                    Load_TX_Data(_F_TXB0D0, 8, data_8);                             
                    break;
                
                case mode_9:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_9);                                 
                    Load_TX_Data(_F_TXB0D0, 8, data_9);                             
                    break;
                    
                case mode_10:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_10);                                
                    Load_TX_Data(_F_TXB0D0, 8, data_10);                            
                    break;
                    
                case mode_11:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_11);                                
                    Load_TX_Data(_F_TXB0D0, 8, data_11);                             
                    break;
                    
                case mode_12:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_12);                                
                    Load_TX_Data(_F_TXB0D0, 8, data_12);                             
                    break;
                    
                case mode_13:

                    Load_TX_Data(_F_TXB0SIDH, 4, Sub_13);                                
                    Load_TX_Data(_F_TXB0D0, 8, data_13);                            
            
            }
            RTS0(0);                                                            //送信要求                                      
            
            INTCONbits.T0IF = 0;                                                //TMR0フラグクリア
            TMR0 = 0;                                                           
            while(! INTCONbits.T0IF);                                           //TMR0のタイムアップ待ち
            
            //__delay_ms(5);
        }
        i = 0;
    }
}

void CONFIG()
{
    OSCCON = 0b01101000;
    ANSEL  = 0b00000000;
    ANSELH = 0b00000000;
    TRISC  = 0b00000000;
    PORTC  = 0b00000000;
    
    spi_init();
    __delay_ms(100);
    
    MCP2515_init(_CAN_BAUDRATE);                                                
    Write(_TXB0DLC , 0b00001000);                                                
    Write(_RXF0SIDH , RXF0SIDH);                                                //フィルタ設定
    Write(_RXF0SIDL , RXF0SIDL);
    Write(_RXF0EID8 , RXF0EID8);
    Write(_RXF0EID0 , RXF0EID0);
    Write(_RXM0SIDH , RXM0SIDH);                                                //マスク設定
    Write(_RXM0SIDL , RXM0SIDL);
    Write(_RXM0EID8 , RXM0EID8);
    Write(_RXM0EID0 , RXM0EID0);
    MCP2515_Open(1);                                                            
}
