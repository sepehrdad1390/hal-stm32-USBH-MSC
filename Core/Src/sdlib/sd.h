#ifndef _SD_H
#define _SD_H

#ifdef __cplusplus
extern "c" {
#endif

#include "main.h"
#include "stdbool.h" 
#include "fatfs.h"
  
typedef enum 
{
   SD_OK = 0,
   SD_NOT_FOUND,
   SD_NOT_OPEN_FILE,
   SD_NOT_WRITE_FILE,
   SD_NOT_READ_FILE,
   SD_NOT_CLOSE_FILE,
   SD_NOT_UNMOUNT,
   SD_NOT_MOUNT,
   SD_NOT_CREATE_FILE,
   SD_NOT_DELETE_FILE
} SD_Status;
  
#define SD_SDIO hsd
extern SD_HandleTypeDef SD_SDIO;

//#define use_card_detect

#ifdef use_card_detect
#define SD_CD_PORT SDIO_CD_GPIO_Port
#define SD_CD_PIN  SDIO_CD_Pin
#endif

/////////////////////////////////////////////
bool SD_isConnect();
SD_Status SD_init();
SD_Status SD_WriteFILE(const char *name,uint8_t *data,uint32_t size,FSIZE_t start_write);
SD_Status SD_ReadFILE(const char *name,uint8_t *data,UINT size,FSIZE_t start_read);
SD_Status SD_CreateFILE(const char *name);
SD_Status SD_DeleteFILE(const char *name);
SD_Status SD_UN_init();
/////////////////////////////////////////////
#endif