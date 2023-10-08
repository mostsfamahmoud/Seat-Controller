/**
 *
 * \file SeatManager_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: SeatManager
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/2/2023 09:13 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_SeatManager.h"

 /**
   * \brief Determines whether motor adjustment is needed based on sensor data.
   *
   * This function evaluates the seat position and weight to determine if motor adjustment
   * is required for optimal seat positioning. It calculates the appropriate motor adjustment
   * step and returns true if adjustment is needed.
   *
   * \param position The position of the seat as a sensor value.
   * \param weight The weight on the seat as a sensor value.
   * \param step A pointer to a variable where the motor adjustment step will be stored.
   *
   * \return Returns true if motor adjustment is needed, false otherwise.
   *
   * \note The provided step pointer will be updated with the required motor step if adjustment is needed.
   */
static boolean SeatManager_IsMotorAdjustNeeded(SensorPositionType position, SensorWeightType weight, StepMotorStepType* step)
{
	boolean adjustMotor = FALSE;

	switch (position)
	{
	case SENSOR_POSITION_STEP_0:
		if (weight > 60)
		{
			*step = MOTOR_STEP_PLUS;
			adjustMotor = TRUE;
		}
		break;

	case SENSOR_POSITION_STEP_1:
		if (weight > 80)
		{
			*step = MOTOR_STEP_PLUS;
			adjustMotor = TRUE;
		}
		else if (weight < 60)
		{
			*step = MOTOR_STEP_MINUS;
			adjustMotor = TRUE;
		}
		break;

	case SENSOR_POSITION_STEP_2:
		if (weight > 100)
		{
			*step = MOTOR_STEP_PLUS;
			adjustMotor = TRUE;
		}
		else if (weight < 80)
		{
			*step = MOTOR_STEP_MINUS;
			adjustMotor = TRUE;
		}
		break;

	case SENSOR_POSITION_STEP_3:
		if (weight < 100)
		{
			*step = MOTOR_STEP_MINUS;
			adjustMotor = TRUE;
		}
		break;

	default:
		break;
	}

	return adjustMotor;
}


/**
 * Runnable: SeatManager_AutoHeight
 *
 * Triggered By:
 *  - TimingEventImpl.TE_SeatManager_AutoHeight_200ms
 *
 * Description: This function is triggered periodically to adjust the seat height automatically based on sensor data.
 */
void SeatManager_AutoHeight(void)
{
	Std_ReturnType pStatus, wStatus;
	StepMotorStepType Arg_Step;
	SensorPositionType Arg_Position;
	SensorWeightType Arg_Weight;
	boolean adjustMotor;

	/* Server Call Points */
	pStatus = Rte_Call_rpHeightSensor_Opr_GetPosition(&Arg_Position);
	wStatus = Rte_Call_rpWeightSensor_Opr_GetWeight(&Arg_Weight);

	if (pStatus == RTE_E_OK && wStatus == RTE_E_OK)
	{
		adjustMotor = SeatManager_IsMotorAdjustNeeded(Arg_Position, Arg_Weight, &Arg_Step);

		if (adjustMotor)
			(void)Rte_Call_rpHeightMotor_Opr_Move(Arg_Step);
	}
}

/**
 * Runnable: SeatManager_AutoIncline
 *
 * Triggered By:
 *  - TimingEventImpl.TE_SeatManager_AutoIncline_200ms
 *
 * Description: This function is triggered periodically to adjust the seat incline automatically based on sensor data.
 */
void SeatManager_AutoIncline(void)
{
	Std_ReturnType pStatus, wStatus;
	StepMotorStepType Arg_Step;
	SensorPositionType Arg_Position;
	SensorWeightType Arg_Weight;
	boolean adjustMotor;

	/* Server Call Points */
	pStatus = Rte_Call_rpInclineSensor_Opr_GetPosition(&Arg_Position);
	wStatus = Rte_Call_rpWeightSensor_Opr_GetWeight(&Arg_Weight);

	if (pStatus == RTE_E_OK && wStatus == RTE_E_OK)
	{
		adjustMotor = SeatManager_IsMotorAdjustNeeded(Arg_Position, Arg_Weight, &Arg_Step);

		if (adjustMotor)
			(void)Rte_Call_rpInclineMotor_Opr_Move(Arg_Step);
	}
}

/**
 * Runnable: SeatManager_AutoSlide
 *
 * Triggered By:
 *  - TimingEventImpl.TE_SeatManager_AutoSlide_200ms
 *
 * Description: This function is triggered periodically to adjust the seat slide position automatically based on sensor data.
 */
void SeatManager_AutoSlide(void)
{
	Std_ReturnType pStatus, wStatus;
	StepMotorStepType Arg_Step;
	SensorPositionType Arg_Position;
	SensorWeightType Arg_Weight;
	boolean adjustMotor;

	/* Server Call Points */
	pStatus = Rte_Call_rpSlideSensor_Opr_GetPosition(&Arg_Position);
	wStatus = Rte_Call_rpWeightSensor_Opr_GetWeight(&Arg_Weight);

	if (pStatus == RTE_E_OK && wStatus == RTE_E_OK)
	{
		adjustMotor = SeatManager_IsMotorAdjustNeeded(Arg_Position, Arg_Weight, &Arg_Step);

		if (adjustMotor)
			(void)Rte_Call_rpSlideMotor_Opr_Move(Arg_Step);
	}
}

/**
 *
 * Runnable SeatManager_SetHeight
 *
 * Triggered By:
 *  - DataReceivedEventImpl.DRE_rpSeatCtrlBtns_DE_HeightBtnState
 *
 * Function to manage seat height adjustment based on button state
 */
void SeatManager_SetHeight(void)
{
	Std_ReturnType status;
	MultiStateBtnType DE_HeightBtnState;
	StepMotorStepType Arg_Step;

	/* Data Receive Points */

	// Read the state of the height button from the RTE
	status = Rte_Read_rpSeatCtrlBtns_DE_HeightBtnState(&DE_HeightBtnState);

	/* Software Logic */

	// Check if the height button state is MULTI_STATE_BTN_MINUS and RTE status is OK
	if (DE_HeightBtnState == MULTI_STATE_BTN_MINUS && status == RTE_E_OK)
	{
		Arg_Step = MOTOR_STEP_MINUS;
	}
	// Check if the height button state is MULTI_STATE_BTN_PLUS and RTE status is OK
	else if (DE_HeightBtnState == MULTI_STATE_BTN_PLUS && status == RTE_E_OK)
	{
		Arg_Step = MOTOR_STEP_PLUS;
	}
	else
	{
		// No matching state found, no action needed
		return;
	}

	/* Server Call Point
	 * Call the RTE to move the seat height motor in the specified direction
	 */
	(void)Rte_Call_rpHeightMotor_Opr_Move(Arg_Step);
}

/**
 *
 * Runnable SeatManager_SetIncline
 *
 * Triggered By:
 *  - DataReceivedEventImpl.DRE_rpSeatCtrlBtns_DE_InclineBtnState
 *
 * Function to manage seat incline adjustment based on button state
 */
void SeatManager_SetIncline(void)
{
	Std_ReturnType status;
	MultiStateBtnType DE_InclineBtnState;
	StepMotorStepType Arg_Step;

	/* Data Receive Points */

	// Read the state of the incline button from the RTE
	status = Rte_Read_rpSeatCtrlBtns_DE_InclineBtnState(&DE_InclineBtnState);

	/* Software Logic */

	// Check if the incline button state is MULTI_STATE_BTN_MINUS and RTE status is OK
	if (DE_InclineBtnState == MULTI_STATE_BTN_MINUS && status == RTE_E_OK)
	{
		Arg_Step = MOTOR_STEP_MINUS;
	}
	// Check if the incline button state is MULTI_STATE_BTN_PLUS and RTE status is OK
	else if (DE_InclineBtnState == MULTI_STATE_BTN_PLUS && status == RTE_E_OK)
	{
		Arg_Step = MOTOR_STEP_PLUS;
	}
	else
	{
		// No matching state found, no action needed
		return;
	}

	/* Server Call Point
	 * Call the RTE to move the seat incline motor in the specified direction
	 */
	(void)Rte_Call_rpInclineMotor_Opr_Move(Arg_Step);
}

/**
 *
 * Runnable SeatManager_SetSlide
 *
 * Triggered By:
 *  - DataReceivedEventImpl.DRE_rpSeatCtrlBtns_DE_SlideBtnState
 *
 * Function to manage seat slide adjustment based on button state
 */
void SeatManager_SetSlide(void)
{
	Std_ReturnType status;
	MultiStateBtnType DE_SlideBtnState;
	StepMotorStepType Arg_Step;

	/* Data Receive Points */

	// Read the state of the slide button from the RTE
	status = Rte_Read_rpSeatCtrlBtns_DE_SlideBtnState(&DE_SlideBtnState);

	/* Software Logic */

	// Check if the slide button state is MULTI_STATE_BTN_MINUS and RTE status is OK
	if (DE_SlideBtnState == MULTI_STATE_BTN_MINUS && status == RTE_E_OK)
	{
		Arg_Step = MOTOR_STEP_MINUS;
	}
	// Check if the slide button state is MULTI_STATE_BTN_PLUS and RTE status is OK
	else if (DE_SlideBtnState == MULTI_STATE_BTN_PLUS && status == RTE_E_OK)
	{
		Arg_Step = MOTOR_STEP_PLUS;
	}
	else
	{
		// No matching state found, no action needed
		return;
	}

	/* Server Call Point
	 * Call the RTE to move the seat Slide motor in the specified direction
	 */
	(void)Rte_Call_rpSlideMotor_Opr_Move(Arg_Step);
}