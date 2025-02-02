/**
 ******************************************************************************
 * @file    ISM330DLCSensor.h
 * @author  SRA
 * @version V1.0.0
 * @date    13-January-2020
 * @brief   Abstract Class of an ISM330DLC Inertial Measurement Unit (IMU) 6 axes
 *          sensor.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2020 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Prevent recursive inclusion -----------------------------------------------*/

#ifndef __ISM330DLCSensor_H__
#define __ISM330DLCSensor_H__


/* Includes ------------------------------------------------------------------*/

#include "Wire.h"
#include "SPI.h"
#include "ISM330DLC_ACC_GYRO_Driver.h"

/* Defines -------------------------------------------------------------------*/

#define ISM330DLC_ACC_SENSITIVITY_FOR_FS_2G   0.061  /**< Sensitivity value for 2 g full scale [mg/LSB] */
#define ISM330DLC_ACC_SENSITIVITY_FOR_FS_4G   0.122  /**< Sensitivity value for 4 g full scale [mg/LSB] */
#define ISM330DLC_ACC_SENSITIVITY_FOR_FS_8G   0.244  /**< Sensitivity value for 8 g full scale [mg/LSB] */
#define ISM330DLC_ACC_SENSITIVITY_FOR_FS_16G  0.488  /**< Sensitivity value for 16 g full scale [mg/LSB] */

#define ISM330DLC_GYRO_SENSITIVITY_FOR_FS_125DPS   04.375  /**< Sensitivity value for 125 dps full scale [mdps/LSB] */
#define ISM330DLC_GYRO_SENSITIVITY_FOR_FS_245DPS   08.750  /**< Sensitivity value for 245 dps full scale [mdps/LSB] */
#define ISM330DLC_GYRO_SENSITIVITY_FOR_FS_500DPS   17.500  /**< Sensitivity value for 500 dps full scale [mdps/LSB] */
#define ISM330DLC_GYRO_SENSITIVITY_FOR_FS_1000DPS  35.000  /**< Sensitivity value for 1000 dps full scale [mdps/LSB] */
#define ISM330DLC_GYRO_SENSITIVITY_FOR_FS_2000DPS  70.000  /**< Sensitivity value for 2000 dps full scale [mdps/LSB] */

#define ISM330DLC_WAKE_UP_THRESHOLD_LOW       0x01  /**< Lowest  value of wake up threshold */
#define ISM330DLC_WAKE_UP_THRESHOLD_MID_LOW   0x0F
#define ISM330DLC_WAKE_UP_THRESHOLD_MID       0x1F
#define ISM330DLC_WAKE_UP_THRESHOLD_MID_HIGH  0x2F
#define ISM330DLC_WAKE_UP_THRESHOLD_HIGH      0x3F  /**< Highest value of wake up threshold */

#define ISM330DLC_TAP_THRESHOLD_LOW       0x01  /**< Lowest  value of wake up threshold */
#define ISM330DLC_TAP_THRESHOLD_MID_LOW   0x08
#define ISM330DLC_TAP_THRESHOLD_MID       0x10
#define ISM330DLC_TAP_THRESHOLD_MID_HIGH  0x18
#define ISM330DLC_TAP_THRESHOLD_HIGH      0x1F  /**< Highest value of wake up threshold */

#define ISM330DLC_TAP_SHOCK_TIME_LOW       0x00  /**< Lowest  value of wake up threshold */
#define ISM330DLC_TAP_SHOCK_TIME_MID_LOW   0x01
#define ISM330DLC_TAP_SHOCK_TIME_MID_HIGH  0x02
#define ISM330DLC_TAP_SHOCK_TIME_HIGH      0x03  /**< Highest value of wake up threshold */

#define ISM330DLC_TAP_QUIET_TIME_LOW       0x00  /**< Lowest  value of wake up threshold */
#define ISM330DLC_TAP_QUIET_TIME_MID_LOW   0x01
#define ISM330DLC_TAP_QUIET_TIME_MID_HIGH  0x02
#define ISM330DLC_TAP_QUIET_TIME_HIGH      0x03  /**< Highest value of wake up threshold */

#define ISM330DLC_TAP_DURATION_TIME_LOW       0x00  /**< Lowest  value of wake up threshold */
#define ISM330DLC_TAP_DURATION_TIME_MID_LOW   0x04
#define ISM330DLC_TAP_DURATION_TIME_MID       0x08
#define ISM330DLC_TAP_DURATION_TIME_MID_HIGH  0x0C
#define ISM330DLC_TAP_DURATION_TIME_HIGH      0x0F  /**< Highest value of wake up threshold */

/* Typedefs ------------------------------------------------------------------*/
typedef enum
{
  ISM330DLC_STATUS_OK = 0,
  ISM330DLC_STATUS_ERROR,
  ISM330DLC_STATUS_TIMEOUT,
  ISM330DLC_STATUS_NOT_IMPLEMENTED
} ISM330DLCStatusTypeDef;

typedef enum
{
  ISM330DLC_INT1_PIN,
  ISM330DLC_INT2_PIN
} ISM330DLC_Interrupt_Pin_t;

typedef struct
{
  unsigned int FreeFallStatus : 1;
  unsigned int TapStatus : 1;
  unsigned int DoubleTapStatus : 1;
  unsigned int WakeUpStatus : 1;
  unsigned int TiltStatus : 1;
  unsigned int D6DOrientationStatus : 1;
} ISM330DLC_Event_Status_t;

/* Class Declaration ---------------------------------------------------------*/

/**
 * Abstract class of an ISM330DLC Inertial Measurement Unit (IMU) 6 axes
 * sensor.
 */
class ISM330DLCSensor
{
  public:
    ISM330DLCSensor                                     (TwoWire *i2c, uint8_t address=ISM330DLC_ACC_GYRO_I2C_ADDRESS_HIGH);
    ISM330DLCSensor                                     (SPIClass *spi, int cs_pin, uint32_t spi_speed=2000000);
    ISM330DLCStatusTypeDef begin                        (void);
    ISM330DLCStatusTypeDef end                          (void);
    ISM330DLCStatusTypeDef Enable_X                     (void);
    ISM330DLCStatusTypeDef Enable_G                     (void);
    ISM330DLCStatusTypeDef Disable_X                    (void);
    ISM330DLCStatusTypeDef Disable_G                    (void);
    ISM330DLCStatusTypeDef ReadID                       (uint8_t *p_id);
    ISM330DLCStatusTypeDef Get_X_Axes                   (int32_t *pData);
    ISM330DLCStatusTypeDef Get_G_Axes                   (int32_t *pData);
    ISM330DLCStatusTypeDef Get_X_Sensitivity            (float *pfData);
    ISM330DLCStatusTypeDef Get_G_Sensitivity            (float *pfData);
    ISM330DLCStatusTypeDef Get_X_AxesRaw                (int16_t *pData);
    ISM330DLCStatusTypeDef Get_G_AxesRaw                (int16_t *pData);
    ISM330DLCStatusTypeDef Get_X_ODR                    (float *odr);
    ISM330DLCStatusTypeDef Get_G_ODR                    (float *odr);
    ISM330DLCStatusTypeDef Set_X_ODR                    (float odr);
    ISM330DLCStatusTypeDef Set_G_ODR                    (float odr);
    ISM330DLCStatusTypeDef Get_X_FS                     (float *fullScale);
    ISM330DLCStatusTypeDef Get_G_FS                     (float *fullScale);
    ISM330DLCStatusTypeDef Set_X_FS                     (float fullScale);
    ISM330DLCStatusTypeDef Set_G_FS                     (float fullScale);
    ISM330DLCStatusTypeDef Enable_Free_Fall_Detection   (void);
    ISM330DLCStatusTypeDef Enable_Free_Fall_Detection   (ISM330DLC_Interrupt_Pin_t int_pin);
    ISM330DLCStatusTypeDef Disable_Free_Fall_Detection  (void);
    ISM330DLCStatusTypeDef Set_Free_Fall_Threshold      (uint8_t thr);
    ISM330DLCStatusTypeDef Enable_Tilt_Detection        (void);
    ISM330DLCStatusTypeDef Enable_Tilt_Detection        (ISM330DLC_Interrupt_Pin_t int_pin);
    ISM330DLCStatusTypeDef Disable_Tilt_Detection       (void);
    ISM330DLCStatusTypeDef Enable_Wake_Up_Detection     (void);
    ISM330DLCStatusTypeDef Enable_Wake_Up_Detection     (ISM330DLC_Interrupt_Pin_t int_pin);
    ISM330DLCStatusTypeDef Disable_Wake_Up_Detection    (void);
    ISM330DLCStatusTypeDef Set_Wake_Up_Threshold        (uint8_t thr);
    ISM330DLCStatusTypeDef Enable_Single_Tap_Detection  (void);
    ISM330DLCStatusTypeDef Enable_Single_Tap_Detection  (ISM330DLC_Interrupt_Pin_t int_pin);
    ISM330DLCStatusTypeDef Disable_Single_Tap_Detection (void);
    ISM330DLCStatusTypeDef Enable_Double_Tap_Detection  (void);
    ISM330DLCStatusTypeDef Enable_Double_Tap_Detection  (ISM330DLC_Interrupt_Pin_t int_pin);
    ISM330DLCStatusTypeDef Disable_Double_Tap_Detection (void);
    ISM330DLCStatusTypeDef Set_Tap_Threshold            (uint8_t thr);
    ISM330DLCStatusTypeDef Set_Tap_Shock_Time           (uint8_t time);
    ISM330DLCStatusTypeDef Set_Tap_Quiet_Time           (uint8_t time);
    ISM330DLCStatusTypeDef Set_Tap_Duration_Time        (uint8_t time);
    ISM330DLCStatusTypeDef Enable_6D_Orientation        (void);
    ISM330DLCStatusTypeDef Enable_6D_Orientation        (ISM330DLC_Interrupt_Pin_t int_pin);
    ISM330DLCStatusTypeDef Disable_6D_Orientation       (void);
    ISM330DLCStatusTypeDef Get_6D_Orientation_XL        (uint8_t *xl);
    ISM330DLCStatusTypeDef Get_6D_Orientation_XH        (uint8_t *xh);
    ISM330DLCStatusTypeDef Get_6D_Orientation_YL        (uint8_t *yl);
    ISM330DLCStatusTypeDef Get_6D_Orientation_YH        (uint8_t *yh);
    ISM330DLCStatusTypeDef Get_6D_Orientation_ZL        (uint8_t *zl);
    ISM330DLCStatusTypeDef Get_6D_Orientation_ZH        (uint8_t *zh);
	ISM330DLCStatusTypeDef Get_Event_Status             (ISM330DLC_Event_Status_t *status);
    ISM330DLCStatusTypeDef ReadReg                      (uint8_t reg, uint8_t *data);
    ISM330DLCStatusTypeDef WriteReg                     (uint8_t reg, uint8_t data);
	
	/**
     * @brief Utility function to read data.
     * @param  pBuffer: pointer to data to be read.
     * @param  RegisterAddr: specifies internal address register to be read.
     * @param  NumByteToRead: number of bytes to be read.
     * @retval 0 if ok, an error code otherwise.
     */
    uint8_t IO_Read(uint8_t* pBuffer, uint8_t RegisterAddr, uint16_t NumByteToRead)
    {
      if (dev_spi) {
        dev_spi->beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));

        digitalWrite(cs_pin, LOW);

        /* Write Reg Address */
        dev_spi->transfer(RegisterAddr | 0x80);
        /* Read the data */
        for (uint16_t i=0; i<NumByteToRead; i++) {
          *(pBuffer+i) = dev_spi->transfer(0x00);
        }
         
        digitalWrite(cs_pin, HIGH);

        dev_spi->endTransaction();

        return 0;
      }
		
      if (dev_i2c) {
        dev_i2c->beginTransmission(((uint8_t)(((address) >> 1) & 0x7F)));
        dev_i2c->write(RegisterAddr);
        dev_i2c->endTransmission(false);

        dev_i2c->requestFrom(((uint8_t)(((address) >> 1) & 0x7F)), (uint8_t) NumByteToRead);

        int i=0;
        while (dev_i2c->available()) {
          pBuffer[i] = dev_i2c->read();
          i++;
        }

        return 0;
      }

      return 1;
    }
    
    /**
     * @brief Utility function to write data.
     * @param  pBuffer: pointer to data to be written.
     * @param  RegisterAddr: specifies internal address register to be written.
     * @param  NumByteToWrite: number of bytes to write.
     * @retval 0 if ok, an error code otherwise.
     */
    uint8_t IO_Write(uint8_t* pBuffer, uint8_t RegisterAddr, uint16_t NumByteToWrite)
    {
      if (dev_spi) {
        dev_spi->beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));

        digitalWrite(cs_pin, LOW);

        /* Write Reg Address */
        dev_spi->transfer(RegisterAddr);
        /* Write the data */
        for (uint16_t i=0; i<NumByteToWrite; i++) {
          dev_spi->transfer(pBuffer[i]);
        }

        digitalWrite(cs_pin, HIGH);

        dev_spi->endTransaction();

        return 0;                    
      }
  
      if (dev_i2c) {
        dev_i2c->beginTransmission(((uint8_t)(((address) >> 1) & 0x7F)));

        dev_i2c->write(RegisterAddr);
        for (uint16_t i = 0 ; i < NumByteToWrite ; i++) {
          dev_i2c->write(pBuffer[i]);
        }

        dev_i2c->endTransmission(true);

        return 0;
      }

      return 1;
    }

  private:
    ISM330DLCStatusTypeDef Set_X_ODR_When_Enabled(float odr);
    ISM330DLCStatusTypeDef Set_G_ODR_When_Enabled(float odr);
    ISM330DLCStatusTypeDef Set_X_ODR_When_Disabled(float odr);
    ISM330DLCStatusTypeDef Set_G_ODR_When_Disabled(float odr);

    /* Helper classes. */
    TwoWire *dev_i2c;
    SPIClass *dev_spi;
    
    /* Configuration */
    uint8_t address;
    int cs_pin;
    uint32_t spi_speed;

    uint8_t X_isEnabled;
    float X_Last_ODR;
    uint8_t G_isEnabled;
    float G_Last_ODR;
};

#ifdef __cplusplus
extern "C" {
#endif
uint8_t ISM330DLC_IO_Write( void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite );
uint8_t ISM330DLC_IO_Read( void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead );
#ifdef __cplusplus
}
#endif

#endif