#ifndef __HAL_I2C_DRIVER_H__
#define __HAL_I2C_DRIVER_H__

#include "stm32f446xx.h"

#include <stdint.h>

//I2C cihazlarinin clock'larini etkinlestirmek için

#define _HAL_RCC_I2C1_CLK_ENABLE()	( RCC->APB1ENR |= (1 << 21) )
#define _HAL_RCC_I2C2_CLK_ENABLE()  ( RCC->APB1ENR |= (1 << 22) )
#define _HAL_RCC_I2C3_CLK_ENABLE()  ( RCC->APB2ENR |= (1 << 23) )

/*******************************************I2C için Register bit tanimlari****************************************************************/

																	/*CR1 registeri için bit tanimlari*/
#define I2C_REG_CR1_POS		( (uint32_t) 1 << 11 ) //Bu bit 1'lendiginde ACK shift registerdaki bir sonraki bayt için (N)ACK kontrolü yapar. 

#define I2C_REG_CR1_ACK		( (uint32_t) 1 << 10 ) //Bir bayt alindiktan sonra geri döner.
#define I2C_ACK_ENABLE		1 //1 bayt alindi
#define I2C_ACK_DISABLE		0 //Alinamadi

#define I2C_REG_CR1_STOP_GEN	( (uint32_t) 1 << 9 ) //Master moddayken mevcut bayt trasnfer edildikten sonra yada start kosulu yollandiktan sonra gönderilir.
																										//Slave modda ise mevcut bayt transfer edildikten sonra SCL ve SDA hatlarini serbest birakir.
#define I2C_REG_CR1_START_GEN	( (uint32_t))					//Master moddayken tekrar eden start kosulu.
																										//Slave moddayken ise bus müsait oldugunda start yaratilir.

#define I2C_REG_CR1_NOSTRETCH		( (uint32_t) 1 << 7 )		//Clock stretch'i etkisizlestirir(slave modda kullanilir). Clock stretch slave'in master'i data alisverisini durmaya zorlamasi.
#define I2C_ENABLE_CLK_STRETCH	0		//Nostretch biti varsayilanda 0'dir yani resettten sonra varsayilanda slave'e clock stretch yetkinligi verilir.
#define I2C_DISABLE_CLK_STETCH	1		//Clock stretch etkisizlestirilmistir.

#define I2C_REG_CR1_ENABLE_I2C	( (uint32_t) 1 << 0 )		//I2C peripheral'i etkinlestirmek için.

																	/*CR2 register'i bit tanimlari*/
#define I2C_REG_CR2_BUF_INT_ENABLE       ((uint32_t) ( 1 << 10 ) )	//TxE yada RxNE'nin 1 olmasi Event interrupt yaratir.
#define I2C_REG_CR2_EVT_INT_ENABLE       ((uint32_t) ( 1 << 9 ) )		//Event interrupt özelligi etkinlestirilir.
#define I2C_REG_CR2_ERR_INT_ENABLE       ((uint32_t) ( 1 << 8 ) )		//Error interrupt özelligi etkinlestirilir.

//I2C peripheralinin frekansinin ayarlamak için CR2 registerinda kullanilan bit alanlari.
#define I2C_PERIPHERAL_CLK_FREQ_2MHZ      ((uint32_t)2 )		
#define I2C_PERIPHERAL_CLK_FREQ_3MHZ      ((uint32_t)3 )  
#define I2C_PERIPHERAL_CLK_FREQ_4MHZ     ((uint32_t)4 )  
#define I2C_PERIPHERAL_CLK_FREQ_5MHZ     ((uint32_t)5 )  
#define I2C_PERIPHERAL_CLK_FREQ_6MHZ     ((uint32_t)6 )  
#define I2C_PERIPHERAL_CLK_FREQ_7MHZ     ((uint32_t)7 )  
#define I2C_PERIPHERAL_CLK_FREQ_8MHZ     ((uint32_t)8 ) 
#define I2C_PERIPHERAL_CLK_FREQ_9MHZ     ((uint32_t)9 )  
#define I2C_PERIPHERAL_CLK_FREQ_10MHZ     ((uint32_t)10 )  

/*******************  Bit definition for I2C_OAR1 register  ********************/
#define I2C_REG_OAR1_ADDRMODE        ((uint32_t) 1 << 15 )		//
#define I2C_ADDRMODE_7BIT          0
#define I2C_ADDRMODE_10BI          1

#define I2C_REG_OAR1_14TH_BIT              ((uint32_t) 1 << 14 )
#define I2C_REG_OAR1_7BIT_ADDRESS_POS       1

/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_REG_SR1_TIMEOUT_FLAG              ( (uint32_t) 1 << 14)	//Eger SCL 25 ms den daha uzun süre low kaldiysa yada master kümülatif clok 10ms'den daha çok yada slave kümülatif clok'u 25ms'den daha uzun süreli ise bu bit 1 olur.
																																		//Slave modda 1 oldugunda slave haberlesmeyi resetler ve hat bosa çikar.
																																		//Master modda 1 oldugunda ise donanim tarafindan stop condition yollanir.
																																	
#define I2C_REG_SR1_OVR_FLAG              ( (uint32_t) 1 << 11)			//Alista yeni bir bayt alindiginda DR registeri okunmamissa kayip olur. Iletimde ise DR yazilmadan gönderim yapilmasi gerekiyorsa ayni data 2 defa yollanir.
#define I2C_REG_SR1_AF_FAILURE_FLAG            ( (uint32_t) 1 << 10)	//ACK dönmedigimde donnanim 0 yapar.
#define I2C_REG_SR1_ARLO_FLAG            ( (uint32_t) 1 << 9)					//Eger master bus'in arbitration'inini baska bir master'a kaybettiyse 1 olur.
#define I2C_REG_SR1_BUS_ERROR_FLAG            ( (uint32_t) 1 << 8)		//SDA SCL high iken düser veya yükselirse yani bayt transferi esnasinda gersiz bir yerlesim oluyorsa 1 olur.		
#define I2C_REG_SR1_TXE_FLAG                  ( (uint32_t) 1 << 7)		//Eger iletimde DR bos oldugunda 1 olur.
#define I2C_REG_SR1_RXNE_FLAG                ( (uint32_t) 1 << 6)			//Eger alista DR bos degilse 1 olur.
#define I2C_REG_SR1_STOP_DETECTION_FLAG       ( (uint32_t) 1 << 4) /*  for slave *///Donanim tarafindan slave'de ACK aliniktan sonra stop durum tespti edildiginde set edilir.
#define I2C_REG_SR1_BTF_FLAG                 ( (uint32_t) 1 << 2)					//Data bayt trasnfer i basarili.
#define I2C_REG_SR1_ADDR_FLAG                 ( (uint32_t) 1 << 1)				//Slave modda adres eselsmesinin alindiginin master modda ise iletimin tamamlandiginin bildirimi için.
#define I2C_REG_SR1_ADDR_SENT_FLAG         ( (uint32_t)1 << 1 )   //For master 
#define I2C_REG_SR1_ADDR_MATCHED_FLAG           ( (uint32_t)1 << 1 ) //For SLAVE 	
#define I2C_REG_SR1_SB_FLAG                 ( (uint32_t) 1 << 0)		//Start conditionun olustugunun bildirimi.

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_REG_SR2_BUS_BUSY_FLAG             ( (uint32_t) 1 << 1)	//Haberlesmenin bus'ta devam ettiginin bildirimi için.
#define I2C_BUS_IS_BUSY                       1
#define I2C_BUS_IS_FREE                       0

#define I2C_REG_SR2_MSL_FLAG           ( (uint32_t) 1 << 0)	 //Donanim tarafindan eger cihaz master modda ise 1 yapilir.
#define I2C_MASTER_MODE                1
#define I2C_SLAVE_MODE                 0

#define I2C_REG_SR2_TRA_FLAG          ( (uint32_t) 1 << 2)	//Data baytinin gönderldiginin bildirimi.
#define I2C_RX_MODE                   0
#define I2C_TX_MODE                   1

/*******************  Bit definition for I2C_CCR register  ********************/
#define I2C_REG_CCR_ENABLE_FM             ( (uint32_t) 1 << 15)	//FM modu etkinlestirir.
#define I2C_ENABLE_SM                     0 
#define I2C_ENABLE_FM                     1

#define I2C_REG_CCR_DUTY                   ( (uint32_t) 1 << 14)		//Duty cycle ayari için.
#define I2C_FM_DUTY_16BY9                  1												
#define I2C_FM_DUTY_2                      0

/******************************************************************************/
/*                                                                            */
/*           I2C Driver'i tarafindan kullnilan data veri yapilari             */
/*                                                                            */
/******************************************************************************/

/**
  * @brief  HAL I2C State structure definition
  */
typedef enum
{
  HAL_I2C_STATE_RESET             = 0x00,  /*!< I2C not yet initialized or disabled         */
  HAL_I2C_STATE_READY             = 0x01,  /*!< I2C initialized and ready for use           */
  HAL_I2C_STATE_BUSY              = 0x02,  /*!< I2C internal process is ongoing             */
  HAL_I2C_STATE_BUSY_TX           = 0x12,  /*!< Data Transmission process is ongoing        */
  HAL_I2C_STATE_BUSY_RX           = 0x22,  /*!< Data Reception process is ongoing           */
  HAL_I2C_STATE_MEM_BUSY_TX       = 0x32,  /*!< Memory Data Transmission process is ongoing */
  HAL_I2C_STATE_MEM_BUSY_RX       = 0x42,  /*!< Memory Data Reception process is ongoing    */
  HAL_I2C_STATE_TIMEOUT           = 0x03,  /*!< I2C timeout state                           */
  HAL_I2C_STATE_ERROR             = 0x04   /*!< I2C error state                             */
}hal_i2c_state_t;

/**
  * @brief  I2C Configuration Structure definition
  */
typedef struct
{
	uint32_t ClockSpeed;       /*!< Specifies the clock frequency.
													This parameter must be set to a value lower than 400kHz */

	uint32_t DutyCycle;        /*!< Specifies the I2C fast mode duty cycle.
													This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */

	uint32_t OwnAddress1;      /*!< Specifies the first device own address.
													This parameter can be a 7-bit or 10-bit address. */

	uint32_t AddressingMode;   /*!< Specifies if 7-bit or 10-bit addressing mode is selected.
													This parameter can be a value of @ref I2C_addressing_mode */

	uint32_t DualAddressMode;  /*!< Specifies if dual addressing mode is selected.
													This parameter can be a value of @ref I2C_dual_addressing_mode */

	uint32_t OwnAddress2;      /*!< Specifies the second device own address if dual addressing mode is selected
													This parameter can be a 7-bit address. */

	uint32_t GeneralCallMode;  /*!< Specifies if general call mode is selected.
													This parameter can be a value of @ref I2C_general_call_addressing_mode */

	uint32_t NoStretchMode;    /*!< Specifies if nostretch mode is selected.
													This parameter can be a value of @ref I2C_nostretch_mode */
	uint32_t ack_enable; 

	uint8_t master;
	
}i2c_init_t;


/** 
  * @brief  I2C handle Structure definition
  */

typedef struct
{
	I2C_TypeDef                *Instance;  /*!< I2C registers base address     */

	i2c_init_t                  Init;       /*!< I2C communication parameters   */

	uint8_t                    *pBuffPtr;  /*!< Pointer to I2C transfer buffer */

	uint32_t                   XferSize;   /*!< I2C transfer size              */

	__IO uint32_t              XferCount;  /*!< I2C transfer counter           */

	hal_i2c_state_t            State;      /*!< I2C communication state        */
	uint32_t ErrorCode;     

}i2c_handle_t;

#define  RESET  0 
#define  SET  !RESET

/*
Sm mode or SMBus:
Thigh = CCR * TPCLK1
Tlow = CCR * TPCLK1 
TPCLK1  = 1/FREQR
Thigh = (1/sm_mode_freq ) / 2
so caclulate CCR 
*/ 


/** 
  * @brief  HAL Status structures definition  
  */  
typedef enum 
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;

#define UNUSED(x) ((void)(x))

/******************************************************************************/
/*                                                                            */
/*                      Driver exposed APIs                                   */
/*                                                                            */
/******************************************************************************/


void hal_i2c_init(i2c_handle_t *handle);

void hal_i2c_manage_ack(I2C_TypeDef *i2cx, uint32_t ack_noack);

void hal_i2c_master_tx(i2c_handle_t *handle, uint8_t slave_address, uint8_t *buffer, uint32_t len);
void hal_i2c_master_rx(i2c_handle_t *handle, uint8_t slave_adr, uint8_t *buffer, uint32_t len);

void hal_i2c_slave_tx(i2c_handle_t *handle, uint8_t *buffer, uint32_t len);
void hal_i2c_slave_rx(i2c_handle_t *handle, uint8_t *buffer, uint32_t len);

void HAL_I2C_EV_IRQHandler(i2c_handle_t *hi2c);
void HAL_I2C_ER_IRQHandler(i2c_handle_t *hi2c);

#endif