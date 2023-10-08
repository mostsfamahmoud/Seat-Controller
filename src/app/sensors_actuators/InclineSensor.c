/**
 *
 * \file InclineSensor_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: InclineSensor
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/2/2023 09:13 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_InclineSensor.h"

 /**
   * Runnable: InclineSensor_GetPosition
   *
   * Triggered By:
   *  - OperationInvokedEventImpl.OIE_ppInclineSensor_Opr_GetPosition
   *
   * Description: This function retrieves the position of the Incline sensor and provides it as output.
   *              It is triggered by an operation invoked event and updates the 'Arg_Position' parameter
   *              with the current position of the Incline sensor based on the readings obtained from the
   *              'Rte_Call_rpIOGetIncline_Opr_IOGet' server call point.
   *
   * \param Arg_Position Pointer to a variable where the Incline sensor position will be stored.
   */
void InclineSensor_GetPosition(SensorPositionType* Arg_Position)
{
    Std_ReturnType status;
    IoPositionSensorReadingType position;

    /* Server Call Points */
    status = Rte_Call_rpIOGetIncline_Opr_IOGet(&position);

    if (status != RTE_E_OK)
        return;

    if (position == 0)
    {
        *Arg_Position = SENSOR_POSITION_STEP_0;
    }
    else if (position > 0 && position <= 64)
    {
        *Arg_Position = SENSOR_POSITION_STEP_1;
    }
    else if (position > 64 && position <= 192)
    {
        *Arg_Position = SENSOR_POSITION_STEP_2;
    }
    else if (position > 192 && position <= 255)
    {
        *Arg_Position = SENSOR_POSITION_STEP_3;
    }
}

