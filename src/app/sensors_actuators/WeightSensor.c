/**
 *
 * \file WeightSensor_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: WeightSensor
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/2/2023 09:13 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_WeightSensor.h"

 /**
  * Runnable: WeightSensor_GetWeight
  *
  * Triggered By:
  *  - OperationInvokedEventImpl.OIE_ppWeightSensor_Opr_GetWeight
  *
  * Description: This function retrieves the weight reading from the weight sensor and provides it as output.
  *              It is triggered by an operation invoked event and updates the 'Arg_Weight' parameter
  *              with the current weight reading. The weight is converted from the native unit (grams)
  *              to the specified 'SensorWeightType' unit.
  *
  * \param Arg_Weight Pointer to a variable where the weight reading will be stored.
  */
void WeightSensor_GetWeight(SensorWeightType* Arg_Weight)
{
    Std_ReturnType status;
    IoWeightSensorReadingType weight;

    /* Server Call Points */
    status = Rte_Call_rpIOGetWeight_Opr_IOGet(&weight);

    if (status != RTE_E_OK)
        return;

    *Arg_Weight = (SensorWeightType)(weight / 100);
}

