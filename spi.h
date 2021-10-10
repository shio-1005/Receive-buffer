/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SPI_H
#define	SPI_H

/* Define */
#define _SSPSTAT_CONFIG 0b01000000      //CKE(bit6)��1�i�����オ��ő��M�j
#define _SSPCON_CONFIG  0b00100000      //SPI�}�X�^�[���[�h�C�N���b�N��Fosc/4�C�N���b�N��Low�ŃA�C�h��
#define _XTAL_FREQ      20000000

/* prototype */
void spi_init(void);
char spi_putc(char c);

#endif
