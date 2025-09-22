#include "sd.h"

static bool sdconnected = true;

bool SD_isConnect()
{
#ifdef use_card_detect
  if(HAL_GPIO_ReadPin(SD_CD_PORT,SD_CD_PIN) == GPIO_PIN_RESET)
  {
      sdconnected = true;
      return true;
  }
  else
  {
    sdconnected = false;
     return false;
  }
#else 
  if(f_mount(&SDFatFS,SDPath,1) == FR_OK)
  {
    sdconnected = true;
     return true;
  } 
  else 
  {
    sdconnected = false;
     return false;
  }
#endif
}

SD_Status SD_init()
{
   //if(SD_isConnect() == false) return SD_NOT_FOUND;
   //f_mount(&SDFatFS,0,1);
   if(f_mount(&SDFatFS,SDPath,1) != FR_OK) return SD_NOT_MOUNT;
   return SD_OK;
}

SD_Status SD_WriteFILE(const char *name,uint8_t *data,UINT size,FSIZE_t start_write)
{
     UINT count = 0;
    if(sdconnected == false) return SD_NOT_FOUND;
    if(f_open(&SDFile,name,FA_WRITE) != FR_OK) return SD_NOT_OPEN_FILE;
    if(f_lseek(&SDFile,start_write) != FR_OK) return SD_NOT_WRITE_FILE;
    if(f_write(&SDFile,data,size,&count) != FR_OK || count != size) return SD_NOT_WRITE_FILE;
    if(f_close(&SDFile) != FR_OK) return SD_NOT_CLOSE_FILE;
    return SD_OK;
}

SD_Status SD_ReadFILE(const char *name,uint8_t *data,UINT size,FSIZE_t start_read)
{
     UINT count = 0;
    if(sdconnected == false) return SD_NOT_FOUND;
    if(f_open(&SDFile,name,FA_WRITE) != FR_OK) return SD_NOT_OPEN_FILE;
    if(f_lseek(&SDFile,start_read) != FR_OK) return SD_NOT_READ_FILE;
    if(f_read(&SDFile,data,size,&count) != FR_OK || count != size) return SD_NOT_WRITE_FILE;
    if(f_close(&SDFile) != FR_OK) return SD_NOT_CLOSE_FILE;
    return SD_OK;
}

SD_Status SD_CreateFILE(const char *name)
{
      if(sdconnected == false) return SD_NOT_FOUND;
      if(f_open(&SDFile,name,FA_CREATE_ALWAYS | FA_CREATE_NEW) != FR_OK) return SD_NOT_CREATE_FILE;
      if(f_close(&SDFile) != FR_OK) return SD_NOT_CLOSE_FILE;
      return SD_OK;
}

SD_Status SD_DeleteFILE(const char *name)
{
      if(sdconnected == false) return SD_NOT_FOUND;
      if(f_unlink(name) != FR_OK) return SD_NOT_DELETE_FILE;
      if(f_close(&SDFile) != FR_OK) return SD_NOT_CLOSE_FILE;
      return SD_OK;
}

SD_Status SD_UN_init()
{
      if(sdconnected == false) return SD_NOT_FOUND;
      if(f_mount(&SDFatFS,0,1) != FR_OK) return SD_NOT_UNMOUNT;
}