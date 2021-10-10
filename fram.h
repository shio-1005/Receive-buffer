/**********************************************************************
 * File         :fram.h                       
 * Date         :2020/11/6
 * Summary      :Use for fram
 * CPU type     :PIC16F886
 * Compiler     :XC8
 * Author       :Akaru Oishi
* ***********************************************************************/



#ifndef __FRAM_H
#define __FRAM_H

#define _FRAM_STRAGE_SIZE                   16                                  //�f�[�^�i�[�p�z��̃T�C�Y�iBytes)


/*--Prototype--*/
void Wren(void);
void WRDI(void);
char RDSR(void);
char *READ(char address_h , char address_l , char bytes);
void WRITE(char address_h , char address_l , char *p , char bytes);
char *RDID(void);

#endif