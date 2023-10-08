/**
 *
 * \file IoHwAbs_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: IoHwAbs
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/2/2023 09:13 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_IoHwAbs.h"

 /* For reading from Position Sensors */
#include "Adc.h"

/* For reading from Weight Sensor */
#include "Spi.h"

/* For driving Motors (height, slide, incline) */
#include "Dio.h"

/* Shall be replaced with Inter Runnable Variable */
/* Internal variables to read Position sensors in one Adc Group */
static Adc_ValueGroupType IoHwAb_PositionSensorsReadings[ADC_GR0_NUM_CHANNELS] =
{
    /* Height */
    0,
    /* Incline */
    0,
    /* Slide */
    0
};

/**
 * Runnable: IoHwAbs_ECUGet_Height
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppIOGetHeight_Opr_IOGet
 *
 * Description: This function retrieves the height sensor reading and provides it as output.
 *              It is triggered by an operation invoked event and updates the 'position' parameter
 *              with the current height sensor reading.
 *
 * \param position Pointer to a variable where the height sensor reading will be stored.
 */
void IoHwAbs_ECUGet_Height(IoPositionSensorReadingType* position)
{
    Std_ReturnType status;

    status = Adc_ReadGroup(AdcConf_AdcGroup_PositionsSensorsGrp, IoHwAb_PositionSensorsReadings);

    if (status == E_OK)
    {
        /* IoPositionSensorReadingType has to be adjusted in arxml file */
        /* as per Adc resolution "Adc_ValueGroupType can be uint8 or uint16" */
        *position = (IoPositionSensorReadingType)IoHwAb_PositionSensorsReadings[0];
    }
    else
    {
        /* Operation shall be updated to return a failure error code */
    }
}

/**
 * Runnable: IoHwAbs_ECUGet_Incline
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppIOGetIncline_Opr_IOGet
 *
 * Description: This function retrieves the incline sensor reading and provides it as output.
 *              It is triggered by an operation invoked event and updates the 'position' parameter
 *              with the current incline sensor reading.
 *
 * \param position Pointer to a variable where the incline sensor reading will be stored.
 */
void IoHwAbs_ECUGet_Incline(IoPositionSensorReadingType* position)
{
    Std_ReturnType status;

    status = Adc_ReadGroup(AdcConf_AdcGroup_PositionsSensorsGrp, IoHwAb_PositionSensorsReadings);

    if (status == E_OK)
    {
        *position = (IoPositionSensorReadingType)IoHwAb_PositionSensorsReadings[1];
    }
    else
    {
        /* Operation shall be updated to return a failure error code */
    }
}

/**
 * Runnable: IoHwAbs_ECUGet_Slide
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppIOGetSlide_Opr_IOGet
 *
 * Description: This function retrieves the slide sensor reading and provides it as output.
 *              It is triggered by an operation invoked event and updates the 'position' parameter
 *              with the current slide sensor reading.
 *
 * \param position Pointer to a variable where the slide sensor reading will be stored.
 */
void IoHwAbs_ECUGet_Slide(IoPositionSensorReadingType* position)
{
    Std_ReturnType status;

    status = Adc_ReadGroup(AdcConf_AdcGroup_PositionsSensorsGrp, IoHwAb_PositionSensorsReadings);

    if (status == E_OK)
    {
        *position = (IoPositionSensorReadingType)IoHwAb_PositionSensorsReadings[2];
    }
    else
    {
        /* Operation shall be updated to return a failure error code */
    }
}

/**
 * Runnable: IoHwAbs_ECUGet_Weight
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppIOGetWeight_Opr_IOGet
 *
 * Description: This function retrieves the weight sensor reading and provides it as output.
 *              It is triggered by an operation invoked event and updates the 'weight' parameter
 *              with the current weight sensor reading.
 *
 * \param weight Pointer to a variable where the weight sensor reading will be stored.
 */
void IoHwAbs_ECUGet_Weight(IoWeightSensorReadingType* weight)
{
    Std_ReturnType status;
    Spi_DataType spiData;

    status = Spi_ReadIB(SpiConf_SpiChannel_WeightSensor, &spiData);

    if (status == E_OK)
    {
        /* IoWeightSensorReadingType has to be adjusted in arxml file */
        /* as per Spi_DataType "can be uint8 or uint16" */
        *weight = (IoWeightSensorReadingType)spiData;
    }
    else
    {
        /* Operation shall be updated to return a failure error code */
    }
}

/**
 * Runnable: IoHwAbs_ECUSetForward_Height
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppIOSetHeight_Opr_IOSetForward
 *
 * Description: This function sets the height motor to move forward.
 *              It is triggered by an operation invoked event.
 */
void IoHwAbs_ECUSetForward_Height(void)
{
    /* Write HIGH to move forward */
    Dio_WriteChannel(DioConfg_DioChannel_HeightMotorCh, STD_HIGH);
}

/**
 * Runnable: IoHwAbs_ECUSetForward_Incline
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppIOSetIncline_Opr_IOSetForward
 *
 * Description: This function sets the incline motor to move forward.
 *              It is triggered by an operation invoked event.
 */
void IoHwAbs_ECUSetForward_Incline(void)
{
    /* Write HIGH to move forward */
    Dio_WriteChannel(DioConfg_DioChannel_InclineMotorCh, STD_HIGH);
}

/**
 * Runnable: IoHwAbs_ECUSetForward_Slide
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppIOSetSlide_Opr_IOSetForward
 *
 * Description: This function sets the slide motor to move forward.
 *              It is triggered by an operation invoked event.
 */
void IoHwAbs_ECUSetForward_Slide(void)
{
    /* Write HIGH to move forward */
    Dio_WriteChannel(DioConfg_DioChannel_SlideMotorCh, STD_HIGH);
}

/**
 * Runnable: IoHwAbs_ECUSetReverse_Height
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppIOSetHeight_Opr_IOSetReverse
 *
 * Description: This function sets the height motor to move in reverse.
 *              It is triggered by an operation invoked event.
 */
void IoHwAbs_ECUSetReverse_Height(void)
{
    /* Write LOW to move in reverse */
    Dio_WriteChannel(DioConfg_DioChannel_HeightMotorCh, STD_LOW);
}

/**
 * Runnable: IoHwAbs_ECUSetReverse_Incline
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppIOSetIncline_Opr_IOSetReverse
 *
 * Description: This function sets the incline motor to move in reverse.
 *              It is triggered by an operation invoked event.
 */
void IoHwAbs_ECUSetReverse_Incline(void)
{
    /* Write LOW to move in reverse */
    Dio_WriteChannel(DioConfg_DioChannel_InclineMotorCh, STD_LOW);
}

/**
 * Runnable: IoHwAbs_ECUSetReverse_Slide
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppIOSetSlide_Opr_IOSetReverse
 *
 * Description: This function sets the slide motor to move in reverse.
 *              It is triggered by an operation invoked event.
 */
void IoHwAbs_ECUSetReverse_Slide(void)
{
    /* Write LOW to move in reverse */
    Dio_WriteChannel(DioConfg_DioChannel_SlideMotorCh, STD_LOW);
}