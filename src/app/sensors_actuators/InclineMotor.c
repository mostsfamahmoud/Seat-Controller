/**
 *
 * \file InclineMotor_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: InclineMotor
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/2/2023 09:13 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_InclineMotor.h"

 /**
  * Runnable: InclineMotor_Move
  *
  * Triggered By:
  *  - OperationInvokedEventImpl.OIE_ppInclineMotor_Opr_Move
  *
  * Description: This function is responsible for moving the Incline motor in the specified direction.
  *              It is triggered by an operation invoked event and takes a step type argument to determine
  *              whether to move the motor forward (MOTOR_STEP_PLUS) or reverse (MOTOR_STEP_MINUS).
  */
void InclineMotor_Move(StepMotorStepType Arg_Step)
{
    if (Arg_Step == MOTOR_STEP_PLUS)
    {
        /* Server Call Point
         * Call the RTE to set the Incline motor in the forward direction.
         */
        (void)Rte_Call_rpIOSetIncline_Opr_IOSetForward();
    }
    else if (Arg_Step == MOTOR_STEP_MINUS)
    {
        /* Server Call Point
         * Call the RTE to set the Incline motor in the reverse direction.
         */
        (void)Rte_Call_rpIOSetIncline_Opr_IOSetReverse();
    }
}
