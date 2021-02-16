#ifndef __W25Q128_H
#define __W25Q128_H
#include "common.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* M25P SPI Flash supported commands */  
#define sFLASH_CMD_WRITE          0x02  /* Write to Memory instruction */
#define sFLASH_CMD_WRSR           0x01  /* Write Status Register instruction */
#define sFLASH_CMD_WREN           0x06  /* Write enable instruction */
#define sFLASH_CMD_READ           0x03  /* Read from Memory instruction */
#define sFLASH_CMD_RDSR           0x05  /* Read Status Register instruction  */
#define sFLASH_CMD_RDID           0x9F  /* Read identification */
#define sFLASH_CMD_SE             0x20  /* Sector Erase instruction */
#define sFLASH_CMD_BE_32KB        0x52  /* Block Erase 32Kb instruction */
#define sFLASH_CMD_BE_64KB        0xD8  /* Block Erase 64Kb instruction */
#define sFLASH_CMD_BE_CHIP        0xC7  /* Chip Erase instruction */

#define sFLASH_WIP_FLAG           0x01  /* Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE         0x7F	/* No Effect 0xA5 */
#define sFLASH_SPI_PAGESIZE       0x100

#define sFLASH_W25Q128_ID         0xEF4018
#define sFLASH_M25P64_ID          0x202017
  
/* M25P FLASH SPI Interface pins  */  
#define sFLASH_SPI                           SPI1
#define sFLASH_SPI_CLK                       RCC_APB2Periph_SPI1
#define sFLASH_SPI_CLK_INIT                  RCC_APB2PeriphClockCmd

#define sFLASH_SPI_SCK_PIN                   GPIO_Pin_3
#define sFLASH_SPI_SCK_GPIO_PORT             GPIOB
#define sFLASH_SPI_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define sFLASH_SPI_SCK_SOURCE                GPIO_PinSource3
#define sFLASH_SPI_SCK_AF                    GPIO_AF_SPI1

#define sFLASH_SPI_MISO_PIN                  GPIO_Pin_4
#define sFLASH_SPI_MISO_GPIO_PORT            GPIOB
#define sFLASH_SPI_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define sFLASH_SPI_MISO_SOURCE               GPIO_PinSource4
#define sFLASH_SPI_MISO_AF                   GPIO_AF_SPI1

#define sFLASH_SPI_MOSI_PIN                  GPIO_Pin_5
#define sFLASH_SPI_MOSI_GPIO_PORT            GPIOB
#define sFLASH_SPI_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define sFLASH_SPI_MOSI_SOURCE               GPIO_PinSource5
#define sFLASH_SPI_MOSI_AF                   GPIO_AF_SPI1

#define sFLASH_CS_PIN                        GPIO_Pin_8
#define sFLASH_CS_GPIO_PORT                  GPIOG
#define sFLASH_CS_GPIO_CLK                   RCC_AHB1Periph_GPIOG

/* Exported macro ------------------------------------------------------------*/
/* Select sFLASH: Chip Select pin low */
#define sFLASH_CS_LOW()       GPIO_ResetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)
/* Deselect sFLASH: Chip Select pin high */
#define sFLASH_CS_HIGH()      GPIO_SetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)   

/* Exported functions ------------------------------------------------------- */

/* High layer functions  */
void sFLASH_DeInit(void);
void sFLASH_Init(void);
void sFLASH_EraseSector(uint32_t SectorAddr);
void sFLASH_Erase_32KB_Blk(uint32_t BlkAddr);
void sFLASH_Erase_64KB_Blk(uint32_t BlkAddr);
void sFLASH_EraseChip(void);
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t sFLASH_ReadID(void);
void sFLASH_StartReadSequence(uint32_t ReadAddr);

/* Low layer functions */
uint8_t sFLASH_ReadByte(void);
uint8_t sFLASH_SendByte(uint8_t byte);
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);
void sFLASH_WriteEnable(void);
void sFLASH_WaitForWriteEnd(void);


#endif















