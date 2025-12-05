#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADevicesHandler.h"
#include "AKeyboardInputHandler.generated.h"
UCLASS()
class INPUTDEVICESHANDLER_API AAKeyboardInputHandler : public AADevicesHandler
{
	GENERATED_BODY()
public:
    AAKeyboardInputHandler();
    virtual void BeginPlay() override;
    virtual void CreateInputActions() override;
    virtual void MapKeys() override;
    
    UPROPERTY()
    UInputAction* IA_Keyboard_A_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_B_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_C_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_D_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_E_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_F_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_G_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_H_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_I_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_J_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_K_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_L_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_M_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_N_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_O_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_P_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_Q_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_R_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_S_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_T_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_U_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_V_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_W_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_X_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_Y_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_Z_Press;   

    UPROPERTY()
    UInputAction* IA_Keyboard_1_Press;

    UPROPERTY()
    UInputAction* IA_Keyboard_2_Press;

    UPROPERTY()
    UInputAction* IA_Keyboard_3_Press;

    UPROPERTY()
    UInputAction* IA_Keyboard_4_Press;

    UPROPERTY()
    UInputAction* IA_Keyboard_Spacebar_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_LeftCtrl_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_RightCtrl_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_LeftAlt_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_RightAlt_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_LeftShift_Press; 
    UPROPERTY()
    UInputAction* IA_Keyboard_RightShift_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_ArrowKeyUp_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_ArrowKeyDown_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_ArrowKeyRight_Press;
    UPROPERTY()
    UInputAction* IA_Keyboard_ArrowKeyLeft_Press;
};
