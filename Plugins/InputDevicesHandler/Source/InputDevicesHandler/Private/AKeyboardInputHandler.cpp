#include "AKeyboardInputHandler.h"

AAKeyboardInputHandler::AAKeyboardInputHandler()
{
    CreateInputActions();
}

void AAKeyboardInputHandler::BeginPlay()
{
    Super::BeginPlay();
    MapKeys();
}

void AAKeyboardInputHandler::CreateInputActions()
{
    if (!IA_Keyboard_A_Press)
    {
        IA_Keyboard_A_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_A_Press"));
        IA_Keyboard_A_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_B_Press)
    {
        IA_Keyboard_B_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_B_Press"));
        IA_Keyboard_B_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_C_Press)
    {
        IA_Keyboard_C_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_C_Press"));
        IA_Keyboard_C_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_D_Press)
    {
        IA_Keyboard_D_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_D_Press"));
        IA_Keyboard_D_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_E_Press)
    {
        IA_Keyboard_E_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_E_Press"));
        IA_Keyboard_E_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_F_Press)
    {
        IA_Keyboard_F_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_F_Press"));
        IA_Keyboard_F_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_G_Press)
    {
        IA_Keyboard_G_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_G_Press"));
        IA_Keyboard_G_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_H_Press)
    {
        IA_Keyboard_H_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_H_Press"));
        IA_Keyboard_H_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_I_Press)
    {
        IA_Keyboard_I_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_I_Press"));
        IA_Keyboard_I_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_J_Press)
    {
        IA_Keyboard_J_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_J_Press"));
        IA_Keyboard_J_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_K_Press)
    {
        IA_Keyboard_K_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_K_Press"));
        IA_Keyboard_K_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_L_Press)
    {
        IA_Keyboard_L_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_L_Press"));
        IA_Keyboard_L_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_M_Press)
    {
        IA_Keyboard_M_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_M_Press"));
        IA_Keyboard_M_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_N_Press)
    {
        IA_Keyboard_N_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_N_Press"));
        IA_Keyboard_N_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_O_Press)
    {
        IA_Keyboard_O_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_O_Press"));
        IA_Keyboard_O_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_P_Press)
    {
        IA_Keyboard_P_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_P_Press"));
        IA_Keyboard_P_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_Q_Press)
    {
        IA_Keyboard_Q_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_Q_Press"));
        IA_Keyboard_Q_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_R_Press)
    {
        IA_Keyboard_R_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_R_Press"));
        IA_Keyboard_R_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_S_Press)
    {
        IA_Keyboard_S_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_S_Press"));
        IA_Keyboard_S_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_T_Press)
    {
        IA_Keyboard_T_Press = CreateDefaultSubobject<UInputAction>(TEXT("Keyboard_TPress_Action"));
        IA_Keyboard_T_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_U_Press)
    {
        IA_Keyboard_U_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_T_Press"));
        IA_Keyboard_U_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_V_Press)
    {
        IA_Keyboard_V_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_V_Press"));
        IA_Keyboard_V_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_W_Press)
    {
        IA_Keyboard_W_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_W_Press"));
        IA_Keyboard_W_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_X_Press)
    {
        IA_Keyboard_X_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_X_Press"));
        IA_Keyboard_X_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_Y_Press)
    {
        IA_Keyboard_Y_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_Y_Press"));
        IA_Keyboard_Y_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_Z_Press)
    {
        IA_Keyboard_Z_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_Z_Press"));
        IA_Keyboard_Z_Press->ValueType = EInputActionValueType::Boolean;
    }

    if (!IA_Keyboard_1_Press)
    {
        IA_Keyboard_1_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_1_Press"));
        IA_Keyboard_1_Press->ValueType = EInputActionValueType::Boolean;
    }

    if (!IA_Keyboard_2_Press)
    {
        IA_Keyboard_2_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_2_Press"));
        IA_Keyboard_2_Press->ValueType = EInputActionValueType::Boolean;
    }

    if (!IA_Keyboard_3_Press)
    {
        IA_Keyboard_3_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_3_Press"));
        IA_Keyboard_3_Press->ValueType = EInputActionValueType::Boolean;
    }

    if (!IA_Keyboard_4_Press)
    {
        IA_Keyboard_4_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_4_Press"));
        IA_Keyboard_4_Press->ValueType = EInputActionValueType::Boolean;
    }

    if (!IA_Keyboard_LeftCtrl_Press)
    {
        IA_Keyboard_LeftCtrl_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_LeftCtrl_Press"));
        IA_Keyboard_LeftCtrl_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_RightCtrl_Press)
    {
        IA_Keyboard_RightCtrl_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_RightCtrl_Press"));
        IA_Keyboard_RightCtrl_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_LeftAlt_Press)
    {
        IA_Keyboard_LeftAlt_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_LeftAlt_Press"));
        IA_Keyboard_LeftAlt_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_RightAlt_Press)
    {
        IA_Keyboard_RightAlt_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_RightAlt_Press"));
        IA_Keyboard_RightAlt_Press->ValueType = EInputActionValueType::Boolean;
    }
   
    if (!IA_Keyboard_LeftShift_Press)
    {
        IA_Keyboard_LeftShift_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_LeftShift_Press"));
        IA_Keyboard_LeftShift_Press->ValueType = EInputActionValueType::Boolean;
    }

    if (!IA_Keyboard_RightShift_Press)
    {
        IA_Keyboard_RightShift_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_RightShift_Press"));
        IA_Keyboard_RightShift_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_ArrowKeyUp_Press)
    {
        IA_Keyboard_ArrowKeyUp_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_ArrowKeyUp_Press"));
        IA_Keyboard_ArrowKeyUp_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_ArrowKeyDown_Press)
    {
        IA_Keyboard_ArrowKeyDown_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_ArrowKeyDown_Press"));
        IA_Keyboard_ArrowKeyDown_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_ArrowKeyRight_Press)
    {
        IA_Keyboard_ArrowKeyRight_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_ArrowKeyRight_Press"));
        IA_Keyboard_ArrowKeyRight_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_ArrowKeyLeft_Press)
    {
        IA_Keyboard_ArrowKeyLeft_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_ArrowKeyLeft_Press"));
        IA_Keyboard_ArrowKeyLeft_Press->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_Keyboard_Spacebar_Press)
    {
        IA_Keyboard_Spacebar_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Keyboard_Spacebar_Press"));
        IA_Keyboard_Spacebar_Press->ValueType = EInputActionValueType::Boolean;
    }
}

void AAKeyboardInputHandler::MapKeys()
{
    if (MappingContext)
    {
        MappingContext->MapKey(IA_Keyboard_A_Press, EKeys::A);
        MappingContext->MapKey(IA_Keyboard_B_Press, EKeys::B);
        MappingContext->MapKey(IA_Keyboard_C_Press, EKeys::C);
        MappingContext->MapKey(IA_Keyboard_D_Press, EKeys::D);
        MappingContext->MapKey(IA_Keyboard_E_Press, EKeys::E);
        MappingContext->MapKey(IA_Keyboard_F_Press, EKeys::F);
        MappingContext->MapKey(IA_Keyboard_G_Press, EKeys::G);
        MappingContext->MapKey(IA_Keyboard_H_Press, EKeys::H);
        MappingContext->MapKey(IA_Keyboard_I_Press, EKeys::I);
        MappingContext->MapKey(IA_Keyboard_J_Press, EKeys::J);
        MappingContext->MapKey(IA_Keyboard_K_Press, EKeys::K);
        MappingContext->MapKey(IA_Keyboard_L_Press, EKeys::L);
        MappingContext->MapKey(IA_Keyboard_M_Press, EKeys::M);
        MappingContext->MapKey(IA_Keyboard_N_Press, EKeys::N);
        MappingContext->MapKey(IA_Keyboard_O_Press, EKeys::O);
        MappingContext->MapKey(IA_Keyboard_P_Press, EKeys::P);
        MappingContext->MapKey(IA_Keyboard_Q_Press, EKeys::Q);
        MappingContext->MapKey(IA_Keyboard_R_Press, EKeys::R);
        MappingContext->MapKey(IA_Keyboard_S_Press, EKeys::S);
        MappingContext->MapKey(IA_Keyboard_T_Press, EKeys::T);
        MappingContext->MapKey(IA_Keyboard_U_Press, EKeys::U);
        MappingContext->MapKey(IA_Keyboard_V_Press, EKeys::V);
        MappingContext->MapKey(IA_Keyboard_W_Press, EKeys::W);
        MappingContext->MapKey(IA_Keyboard_X_Press, EKeys::X);
        MappingContext->MapKey(IA_Keyboard_Y_Press, EKeys::Y);
        MappingContext->MapKey(IA_Keyboard_Z_Press, EKeys::Z);
        MappingContext->MapKey(IA_Keyboard_1_Press, EKeys::One);
        MappingContext->MapKey(IA_Keyboard_2_Press, EKeys::Two);
        MappingContext->MapKey(IA_Keyboard_3_Press, EKeys::Three);
        MappingContext->MapKey(IA_Keyboard_4_Press, EKeys::Four);
        MappingContext->MapKey(IA_Keyboard_LeftCtrl_Press, EKeys::LeftControl);
        MappingContext->MapKey(IA_Keyboard_RightCtrl_Press, EKeys::RightControl);
        MappingContext->MapKey(IA_Keyboard_LeftAlt_Press, EKeys::LeftAlt);
        MappingContext->MapKey(IA_Keyboard_RightAlt_Press, EKeys::RightAlt);
        MappingContext->MapKey(IA_Keyboard_LeftShift_Press, EKeys::LeftShift);
        MappingContext->MapKey(IA_Keyboard_RightShift_Press, EKeys::RightShift);
        MappingContext->MapKey(IA_Keyboard_ArrowKeyDown_Press, EKeys::Down);
        MappingContext->MapKey(IA_Keyboard_ArrowKeyUp_Press, EKeys::Up);
        MappingContext->MapKey(IA_Keyboard_ArrowKeyRight_Press, EKeys::Right);
        MappingContext->MapKey(IA_Keyboard_ArrowKeyLeft_Press, EKeys::Left);
        MappingContext->MapKey(IA_Keyboard_Spacebar_Press, EKeys::SpaceBar);
    }
}


