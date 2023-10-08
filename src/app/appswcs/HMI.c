/**
 * \file HMI_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: HMI
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/2/2023 09:13 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 */

#include "Rte_HMI.h"

 /**
  * \brief Set the state of a multi-state button based on input data.
  *
  * This function takes button data (DE_btnData) and a pointer to a MultiStateBtnType variable (DE_btnState).
  * Depending on the button data, the function sets the button state accordingly.
  * If DE_btnData is 0, the state is set to MULTI_STATE_BTN_INIT.
  * If DE_btnData is 1, the state is set to MULTI_STATE_BTN_MINUS.
  * If DE_btnData is 2, the state is set to MULTI_STATE_BTN_PLUS.
  *
  * \param DE_btnData Button data input.
  * \param DE_btnState Pointer to the MultiStateBtnType variable representing the button state.
  */
static void HMI_setButtonState(uint8 DE_btnData, MultiStateBtnType* DE_btnState)
{
    switch (DE_btnData)
    {
    case 0:
        *DE_btnState = MULTI_STATE_BTN_INIT;
        break;
    case 1:
        *DE_btnState = MULTI_STATE_BTN_MINUS;
        break;
    case 2:
        *DE_btnState = MULTI_STATE_BTN_PLUS;
        break;
    default:
        break;
    }
}

/**
 * \brief Main entry point for HMI functionality.
 *
 * Runnable HMI_MainFunction
 *
 * Triggered By:
 *  - TimingEventImpl.TE_HMI_MainFunction_100ms
 *
 * It reads seat control data for height, incline, and slide.
 * It then sets the button states using the HMI_setButtonState function and sends the updated button states back to the RTE.
 */
void HMI_MainFunction(void)
{
    Std_ReturnType status;
    MultiStateBtnType DE_HeightBtnState;
    MultiStateBtnType DE_InclineBtnState;
    MultiStateBtnType DE_SlideBtnState;
    uint8 DE_Height;
    uint8 DE_Incline;
    uint8 DE_Slide;
    boolean isUpdated;

    // Check if the Height data has been updated
    isUpdated = Rte_IsUpdated_rpSeatCtrlData_DE_Height();
    // Read Height data
    status = Rte_Read_rpSeatCtrlData_DE_Height(&DE_Height);
    if (status == RTE_E_OK && isUpdated == TRUE)
    {
        // Set button state and write to RTE
        HMI_setButtonState(DE_Height, &DE_HeightBtnState);
        (void)Rte_Write_ppSeatCtrlBtns_DE_HeightBtnState(DE_HeightBtnState);
    }

    // Check if the Incline data has been updated
    isUpdated = Rte_IsUpdated_rpSeatCtrlData_DE_Incline();
    // Read Incline data
    status = Rte_Read_rpSeatCtrlData_DE_Incline(&DE_Incline);
    if (status == RTE_E_OK && isUpdated == TRUE)
    {
        // Set button state and write to RTE
        HMI_setButtonState(DE_Incline, &DE_InclineBtnState);
        (void)Rte_Write_ppSeatCtrlBtns_DE_InclineBtnState(DE_InclineBtnState);
    }

    // Check if the Slide data has been updated
    isUpdated = Rte_IsUpdated_rpSeatCtrlData_DE_Slide();
    // Read Slide data
    status = Rte_Read_rpSeatCtrlData_DE_Slide(&DE_Slide);
    if (status == RTE_E_OK && isUpdated == TRUE)
    {
        // Set button state and write to RTE
        HMI_setButtonState(DE_Slide, &DE_SlideBtnState);
        (void)Rte_Write_ppSeatCtrlBtns_DE_SlideBtnState(DE_SlideBtnState);
    }
}

/**
 * \brief Runnable HMI_SeatModeChanged
 *
 * Triggered By:
 *  - DataReceivedEventImpl.DRE_rpSeatModeBtn_DE_SeatModeBtn
 *
 * This function handles changes in the seat mode button.
 * It reads the button state and switches the seat control mode accordingly.
 */
void HMI_SeatModeChanged(void)
{
    Std_ReturnType status;
    SeatModeBtnType DE_SeatModeBtn;
    uint8 SeatCtrlMode = RTE_MODE_SeatCtrlMode_INIT;

    /* Data Receive Points */
    status = Rte_Read_rpSeatModeBtn_DE_SeatModeBtn(&DE_SeatModeBtn);

    if (status != RTE_E_OK)
        return;

    if (DE_SeatModeBtn == SEAT_MODE_BTN_MANUAL)
    {
        SeatCtrlMode = RTE_MODE_SeatCtrlMode_MANUAL;
    }
    else if (DE_SeatModeBtn == SEAT_MODE_BTN_AUTO)
    {
        SeatCtrlMode = RTE_MODE_SeatCtrlMode_AUTO;
    }
    else
        SeatCtrlMode = RTE_MODE_SeatCtrlMode_INIT;

    /* Mode Switch Points */
    (void)Rte_Switch_ppSeatCtrlMode_SeatCtrlMode(SeatCtrlMode);
}