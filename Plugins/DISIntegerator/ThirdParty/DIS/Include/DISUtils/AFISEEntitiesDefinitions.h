#pragma once
//*****************************************************************************************************************************************************//
//                                                               AFISE Entities' Definitions                                                             
//  Ameesha
//  10/07/2025 3:18:34 pm
//  Added Oscar Drone
//*****************************************************************************************************************************************************//

#define DEFAULT_SIMULATION_OBJECT                         0                   //Default Simulation Object                         0x0
#define DEFAULT_PLATFORM                                  1                   //Default Platform                                  0x1
#define DEFAULT_PLATFORM_LAND                             2                   //Default Platform Land                             0x2
#define DEFAULT_PLATFORM_AIR                              3                   //Default Platform Air                              0x3
#define DEFAULT_PLATFORM_SURFACE                          4                   //Default Platform Surface                          0x4
#define DEFAULT_PLATFORM_SUBSURFACE                       5                   //Default Platform Subsurface                       0x5
#define DEFAULT_PLATFORM_SPACE                            6                   //Default Platform Space                            0x6
#define DEFAULT_MUNITION                                  7                   //Default Munition                                  0x7
#define DEFAULT_MUNITION_ANTI_AIR                         8                   //Default Munition Anti-Air                         0x8
#define DEFAULT_MUNITION_ANTI_ARMOUR                      9                   //Default Munition Anti-Armour                      0x9
#define DEFAULT_MUNITION_ANTI_GUIDED_WEAPON               10                  //Default Munition Anti-Guided Weapon               0xA
#define DEFAULT_MUNITION_ANTI_RADAR                       11                  //Default Munition Anti-Radar                       0xB
#define DEFAULT_MUNITION_ANTI_SATELLITE                   12                  //Default Munition Anti-Satellite                   0xC
#define DEFAULT_MUNITION_ANTI_SHIP                        13                  //Default Munition Anti-Ship                        0xD
#define DEFAULT_MUNITION_ANTI_SUBMARINE                   14                  //Default Munition Anti-Submarine                   0xE
#define DEFAULT_MUNITION_ANTI_PERSONNEL                   15                  //Default Munition Anti-Personnel                   0xF
#define DEFAULT_MUNITION_BATTLEFIELD_SUPPORT              16                  //Default Munition Battlefield Support              0x10
#define DEFAULT_MUNITION_STRATEGIC                        17                  //Default Munition Strategic                        0x11
#define DEFAULT_MUNITION_TACTICAL                         18                  //Default Munition Tactical                         0x12
#define DEFAULT_MUNITION_DIRECTED_ENERGY_WEAPON           19                  //Default Munition Directed Energy Weapon           0x13
#define DEFAULT_LIFE_FORM_LAND                            20                  //Default Life Form Land                            0x14
#define DEFAULT_LIFE_FORM_AIR                             21                  //Default Life Form Air                             0x15
#define DEFAULT_LIFE_FORM_SURFACE                         22                  //Default Life Form Surface                         0x16
#define DEFAULT_LIFE_FORM_SUBSURFACE                      23                  //Default Life Form Subsurface                      0x17
#define DEFAULT_LIFE_FORM_SPACE                           24                  //Default Life Form Space                           0x18
#define DEFAULT_ENVIRONMENTAL                             25                  //Default Environmental                             0x19
#define DEFAULT_CULTURAL_FEATURE_LAND                     26                  //Default Cultural Feature Land                     0x1A
#define DEFAULT_CULTURAL_FEATURE_AIR                      27                  //Default Cultural Feature Air                      0x1B
#define DEFAULT_CULTURAL_FEATURE_SURFACE                  28                  //Default Cultural Feature Surface                  0x1C
#define DEFAULT_CULTURAL_FEATURE_SUBSURFACE               29                  //Default Cultural Feature Subsurface               0x1D
#define DEFAULT_CULTURAL_FEATURE_SPACE                    30                  //Default Cultural Feature Space                    0x1E
#define DEFAULT_SUPPLY                                    31                  //Default Supply                                    0x1F
#define DEFAULT_RADIO                                     32                  //Default Radio                                     0x20
#define DEFAULT_EXPENDABLE_LAND                           33                  //Default Expendable Land                           0x21
#define DEFAULT_EXPENDABLE_AIR                            34                  //Default Expendable Air                            0x22
#define DEFAULT_EXPENDABLE_SURFACE                        35                  //Default Expendable Surface                        0x23
#define DEFAULT_EXPENDABLE_SUBSURFACE                     36                  //Default Expendable Subsurface                     0x24
#define DEFAULT_EXPENDABLE_SPACE                          37                  //Default Expendable Space                          0x25
#define DEFAULT_SENSOR_EMITTER                            38                  //Default Sensor/Emitter                            0x26
#define DEFAULT_SENSOR_EMITTER_LAND                       39                  //Default Sensor/Emitter land                       0x27
#define DEFAULT_SENSOR_EMITTER_AIR                        40                  //Default Sensor/Emitter Air                        0x28
#define DEFAULT_SENSOR_EMITTER_SURFACE                    41                  //Default Sensor/Emitter Surface                    0x29
#define DEFAULT_SENSOR_EMITTER_SUBSURFACE                 42                  //Default Sensor/Emitter Subsurface                 0x2A
#define DEFAULT_SENSOR_EMITTER_SPACE                      43                  //Default Sensor/Emitter Space                      0x2B

#define DEFAULT_EXPENDABLE                                900                 //Default Expendable                                0x384
#define EXPENDABLE_CHAFF                                  901                 //Chaff                                             0x385
#define EXPENDABLE_FLARE                                  902                 //Flare                                             0x386
#define EXPENDABLE_COMBINED_CHAFF_AND_FLARE               903                 //Combined chaff and flare                          0x387
#define EXPENDABLE_ACTIVE_EMITTER                         904                 //Active emitter                                    0x388
#define EXPENDABLE_PASSIVE_DECOY                          905                 //Passive decoy                                     0x389
#define EXPENDABLE_WINGED_DECOY                           906                 //Winged decoy                                      0x38A
#define EXPENDABLE_SIGNAL_ILLUMINATION_FLARE              907                 //Signal/Illumination Flare                         0x38B
#define EXPENDABLE_SMOKE_GENERATOR                        908                 //Smoke Generator                                   0x38C
#define EXPENDABLE_SAR_NIGHT_LIGHT                        909                 //SAR Night Light (SRNL)                            0x38D

#define DEFAULT_MISSILE                                   1000                //Default Missile                                   0x3E8
#define MISSILE_AIM_120_C5                                1001                //AMRAAM AIM-120 C-5                                0x3E9
#define MISSILE_AIM_9L                                    1002                //SRAAM AIM-9 L Sidewinder                          0x3EA
#define MISSILE_ASPIDE_2000                               1003                //ASPIDE 2000                                       0x3EB
#define MISSILE_HQ_9P                                     1004                //HQ-9P                                             0x3EC
#define MISSILE_LY_80                                     1005                //HQ-16 SAM LY-80                                   0x3ED
#define MISSILE_CROTALE                                   1006                //Crotale SAM                                       0x3EE
#define MISSILE_MISTRAL                                   1007                //Mistral SAM                                       0x3EF
#define MISSILE_FN_16                                     1008                //FN-16 SAM                                         0x3F0
#define MISSILE_FN_6                                      1009                //FN-6 SAM                                          0x3F1
#define MISSILE_QW_18                                     1010                //QW-18 SAM                                         0x3F2
#define MISSILE_S400                                      1011                //SA-21 Growler S-400                               0x3F3
#define MISSILE_SA_3_GOA                                  1012                //SA-3 Goa / S-125                                  0x3F4
#define MISSILE_MAGIC_R_550                               1013                //Magic R 550                                       0x3F5
#define MISSILE_PL15                                      1014                //Missile PL15                                      0x3F6
#define MISSILE_PL5_IR                                    1015                //Missile PL5 IR                                    0x3F7
#define MISSILE_PL10_IIR_HOBS                             1016                //Missile PL10 IIR HOBS                             0x3F8
#define MISSILE_AIM_9M                                    1017                //AIM 9L                                            0x3F9
#define MISSILE_AIM_120_D                                 1018                //AIM 120 D                                         0x3FA
#define MISSILE_AIM_120_C7                                1019                //AIM 120 C7                                        0x3FB
#define MISSILE_SD_10A                                    1020                //Missile SD10A                                     0x3FC
#define MISSILE_METEOR                                    1021                //Meteor                                            0x3FD
#define MISSILE_ASTRA                                     1022                //Astra                                             0x3FE
#define MISSILE_AA_12                                     1023                //AA-12                                             0x3FF
#define MISSILE_AA_11                                     1024                //AA-11                                             0x400
#define MISSILE_Mica_RF                                   1025                //Mica RF                                           0x401
#define MISSILE_Mica_IIR                                  1026                //Mica IIR                                          0x402
#define MISSILE_ASRAAM                                    1027                //ASRAAM AIM-132                                    0x403
#define MISSILE_PYTHON5                                   1028                //Python 5                                          0x404
#define MISSILE_AIM_9X_HOBS                               1029                //AIM 9X HOBS                                       0x405
#define MISSILE_HQ_9B                                     1030                //HQ-9B                                             0x406
#define MISSILE_LY_80_EV                                  1031                //HQ-16 SAM LY-80-EV                                0x407
#define MISSILE_AA_10C                                    1032                //AA-10C                                            0x408
#define MISSILE_BARAK                                     1033                //Barak 8                                           0x409
#define MISSILE_BRAHMOS                                   1034                //Brahmos                                           0x40A
#define MISSILE_SPICE_2000                                1035                //Spice 2000                                        0x40B
#define MISSILE_AGM_65_MAVERICK                           1036                //AGM-65                                            0x40C
#define MISSILE_CBU_105                                   1037                //CBU-105                                           0x40D
#define MISSILE_GBU_31A_JDAM                              1038                //GBU-31A                                           0x40E
#define MISSILE_EXOCET_SM39                               1039                //Exocet                                            0x40F
#define MISSILE_AGM_88                                    1040                //AGM-88 HARM                                       0x410
#define MISSILE_MAR_1                                     1041                //MAR-1                                             0x411
#define MISSILE_CM_400_AKG                                1042                //CM-400AKG                                         0x412
#define MISSILE_C802_AK                                   1043                //C-802AK                                           0x413
#define MISSILE_AG_300_M                                  1044                //AG-300/M                                          0x414
#define MISSILE_AS_30                                     1045                //AS-30                                             0x415
#define MISSILE_AA_13_C                                   1046                //AA-13C                                            0x416
#define MISSILE_SWORD_X                                   1047                //Sword-X                                           0x417
#define MISSILE_SWORD_1                                   1048                //Sword-1                                           0x418
#define MISSILE_SWORD_2                                   1049                //Sword-2                                           0x419
#define MISSILE_SWORD_3                                   1050                //Sword-3                                           0x41A
#define MISSILE_SWORD_4                                   1051                //Sword-4                                           0x41B
#define MISSILE_SWORD_5                                   1052                //Sword-5                                           0x41C
#define MISSILE_DERBY                                     1053                //DERBY                                             0x41D
#define MISSILE_SA_6_GAINFUL                              1054                //Missile SA-6                                      0x41E
#define MISSILE_SA_8_GECKO                                1055                //Missile SA-8                                      0x41F
#define MISSILE_SA_17_GRIZZLY                             1056                //Missile SA-17                                     0x420
#define MISSILE_SPICE_250                                 1057                //Missile Spice-250                                 0x421
#define MISSILE_HAMMER                                    1058                //Missile Hammer                                    0x422
#define MISSILE_AS_14                                     1059                //Missile AS-14                                     0x423
#define MISSILE_AS_18                                     1060                //Missile AS-18                                     0x424
#define MISSILE_AS_20                                     1061                //Missile AS-20                                     0x425
#define MISSILE_PAF_AGM_84_L_HARPOON                      1062                //Missile AGM-84L Harpoon PAF                       0x426
#define MISSILE_AS_17                                     1063                //Missile AS-17                                     0x427
#define MISSILE_POPEYE_2                                  1064                //Missile Popeye 2                                  0x428
#define MISSILE_IAF_AGM_84_L_HARPOON                      1065                //Missile AGM-84L Harpoon IAF                       0x429
#define MISSILE_FATAH_I                                   1066                //Missile Fatah-I                                   0x42A
#define MISSILE_ALARM                                     1067                //Missile ALARM                                     0x42B
#define MISSILE_FATAH_II                                  1068                //Missile Fatah-II                                  0x42C
#define MISSILE_PINAKA                                    1069                //Missile Pinaka                                    0x42D
#define MISSILE_AIM7_SPARROW                              1070                //AIM-7 Sparrow                                     0x42E
#define MISSILE_BLAZE_1                                   1071                //Blaze 1                                           0x42F
#define MISSILE_BLAZE_2                                   1072                //Blaze 2                                           0x430
#define MISSILE_PULSE_1                                   1073                //Pulse 1                                           0x431
#define MISSILE_PULSE_2                                   1074                //Pulse 2                                           0x432
#define MISSILE_HQ_22                                     1075                //HQ-22                                             0x433
#define MISSILE_PL_9                                      1076                //Missile PL-9                                      0x434
#define MISSILE_PL_10_PLAAF                               1077                //Missile PL-10                                     0x435
#define MISSILE_PL_12                                     1078                //Missile PL-12                                     0x436
#define MISSILE_PL_15_PLAAF                               1079                //Missile PL-15                                     0x437
#define MISSILE_PL_17                                     1080                //Missile PL-17                                     0x438
#define MISSILE_YJ_83K                                    1081                //Missile YJ-83K                                    0x439
#define MISSILE_KD_88                                     1082                //Missile KD-88                                     0x43A
#define MISSILE_RUDRAM_1                                  1083                //Missile Rudram 1                                  0x43B
#define MISSILE_RUDRAM_2                                  1084                //Missile Rudram 2                                  0x43C
#define MISSILE_RUDRAM_3                                  1085                //Missile Rudram 3                                  0x43D
#define MISSILE_BRAHMOS_SLCM                              1086                //BrahMos-SLCM                                      0x43E
#define MISSILE_HARPY                                     1087                //Harpy                                             0x43F
#define MISSILE_SCALP                                     1088                //SCALP                                             0x440
#define MISSILE_BRAHMOS_ALCM                              1089                //BrahMos-ALCM                                      0x441

#define DEFAULT_BOMB                                      1500                //Default Bomb                                      0x5DC
#define BOMB_GBU_31                                       1501                //GBU 31                                            0x5DD
#define BOMB_GBU_32                                       1502                //GBU 32                                            0x5DE
#define BOMB_GBU_38                                       1503                //GBU 38                                            0x5DF
#define BOMB_REK                                          1504                //REK                                               0x5E0
#define BOMB_MAM_L                                        1505                //MAM-L                                             0x5E1
#define BOMB_H_2_SOW                                      1506                //H-2                                               0x5E2
#define BOMB_H_4_SOW                                      1507                //H-4                                               0x5E3
#define BOMB_SLAMMER_1                                    1508                //Slammer 1                                         0x5E4
#define BOMB_SLAMMER_2                                    1509                //Slammer 2                                         0x5E5
#define BOMB_SLAMMER_3                                    1510                //Slammer 3                                         0x5E6
#define BOMB_SLAMMER_4                                    1511                //Slammer 4                                         0x5E7
#define BOMB_LS_500J                                      1512                //LS-500J                                           0x5E8

#define DEFAULT_SHELL                                     1800                //Default Shell                                     0x708
#define SHELL_120MM                                       1801                //120mm Shell                                       0x709
#define SHELL_125MM                                       1802                //125mm Shell                                       0x70A
#define SHELL_155MM                                       1803                //155mm Shell                                       0x70B
#define SHELL_203MM                                       1804                //203mm Shell                                       0x70C

#define DEFAULT_LIFE_FORM                                 2000                //Default Life Form (Human  animal birds etc.)      0x7D0
#define LIFE_FORM_TOWER_CONTROLLER                        2001                //ATC Tower Controller                              0x7D1
#define LIFE_FORM_MAN                                     2002                //Man                                               0x7D2
#define LIFE_FORM_WOMAN                                   2003                //Woman                                             0x7D3
#define LIFE_FORM_SOLDIER                                 2004                //Soldier                                           0x7D4
#define LIFE_FORM_BIRD_SHOOTER                            2005                //Bird Shooter                                      0x7D5
#define LIFE_FORM_PILOT                                   2006                //Pilot                                             0x7D6
#define LIFE_FORM_TECHNICIAN                              2007                //Technician                                        0x7D7
#define LIFE_FORM_CAT                                     2008                //Cat                                               0x7D8
#define LIFE_FORM_DOG                                     2009                //Dog                                               0x7D9
#define LIFE_FORM_JTAC                                    2010                //JTAC                                              0x7DA
#define LIFE_FORM_DEFAULT_PAKISTAN_ARMY_SOLDIER           2011                //Pakistan Army Default Soldier                     0x7DB
#define LIFE_FORM_DEFAULT_MANPADS                         2012                //Pakistan Army Default MANPADS                     0x7DC
#define LIFE_FORM_MANPADS_MISTRAL                         2013                //Pakistan Army Mistral MANPAD Missile Launcher     0x7DD
#define LIFE_FORM_MANPADS_FN_16                           2014                //Pakistan Army FN-16 MANPADS Missile Launcher      0x7DE
#define LIFE_FORM_MANPADS_FN_6                            2015                //Pakistan Army FN-6 MANPADS Missile Launcher       0x7DF
#define LIFE_FORM_MANPADS_QW_18                           2016                //Pakistan Army QW-18 MANPADS Missile Launcher      0x7E0
#define LIFE_FORM_MANPADS_IGLA_S                          2017                //IGLA-S                                            0x7E1
#define LIFE_FORM_MANPADS_FIM_92_STINGER                  2018                //FIM-92 STINGER                                    0x7E2

#define DEFAULT_CULTURAL_FEATURE                          3000                //Default Cultural Feature                          0xBB8
#define STATIC_OBJECT_OBSERVATION_TOWER                   3001                //Observation Tower                                 0xBB9
#define STATIC_OBJECT_TRENCH                              3002                //Ditch                                             0xBBA
#define STATIC_OBJECT_BUILDING                            3003                //PAK Building                                      0xBBB
#define STATIC_OBJECT_FENCE                               3004                //Chain Link Fence                                  0xBBC
#define STATIC_OBJECT_HANGER                              3005                //Hanger                                            0xBBD
#define STATIC_OBJECT_BUILDING_LARGE                      3006                //Building-Large                                    0xBBE
#define STATIC_OBJECT_BARRACKS                            3007                //Barracks                                          0xBBF

#define DEFAULT_VEHICLE                                   4000                //Default Vehicle                                   0xFA0
#define VEHICLE_AMBULANCE                                 4001                //Ambulance                                         0xFA1
#define VEHICLE_WATER_BOUZER                              4002                //Water Bouzer                                      0xFA2
#define VEHICLE_RUNWAY_AUTO_SWEEPER                       4003                //Runway Auto Sweeper                               0xFA3
#define VEHICLE_CRASH_TENDER                              4004                //Crash Tender                                      0xFA4
#define VEHICLE_SINGLE_CABIN                              4005                //Single Cabin                                      0xFA5
#define VEHICLE_DOUBLE_CABIN                              4006                //Double Cabin                                      0xFA6
#define VEHICLE_DRAG_PARACHUTE_VAN                        4007                //Drag Parachute Van                                0xFA7
#define VEHICLE_RUNWAY_INSPECTION                         4008                //Runway Inspection Vehicle                         0xFA8
#define VEHICLE_MOBILE_OFFICER                            4009                //Mobile Officer Vehicle                            0xFA9
#define VEHICLE_FRICTION_TEST                             4010                //Friction Test Vehicle                             0xFAA
#define VEHICLE_BASE_COMMANDER_CAR                        4011                //Base Commander Car                                0xFAB
#define VEHICLE_OC_FLYING_CAR                             4012                //OC Flying Car                                     0xFAC
#define VEHICLE_TOYOTA_ALTIS                              4013                //Toyota Corolla Altis                              0xFAD
#define VEHICLE_TOYOTA_GLI                                4014                //Toyota Corolla GLI                                0xFAE
#define VEHICLE_TOYOTA_XLI                                4015                //Toyota Corolla XLI                                0xFAF
#define VEHICLE_TOYOTA_SURF                               4016                //Toyota Surf                                       0xFB0
#define VEHICLE_TOYOTA_HIACE                              4017                //Toyota Hiace                                      0xFB1
#define VEHICLE_TOYOTA_COASTER                            4018                //Toyota Coaster                                    0xFB2
#define VEHICLE_TOYOTA_LANDCRUISER_3_DOOR                 4019                //Toyota Land Cruiser 3 Door                        0xFB3
#define VEHICLE_TOYOTA_LANDCRUISER_PRADO                  4020                //Toyota Land Cruiser Prado                         0xFB4
#define VEHICLE_TOYOTA_LANDCRUISER_5_DOOR                 4021                //Toyota Land Cruiser 5 Door                        0xFB5
#define VEHICLE_TOYOTA_Revo                               4022                //Toyota Revo                                       0xFB6
#define VEHICLE_HONDA_CIVIC                               4023                //Honda Civic                                       0xFB7
#define VEHICLE_HONDA_CITY                                4024                //Honda City                                        0xFB8
#define VEHICLE_SUZUKI_LIANA                              4025                //Suzuki Liana                                      0xFB9
#define VEHICLE_SUZUKI_BALENO                             4026                //Suzuki Baleno                                     0xFBA
#define VEHICLE_SUZUKI_SWIFT                              4027                //Suzuki Swift                                      0xFBB
#define VEHICLE_SUZUKI_CULTUS                             4028                //Suzuki Cultus                                     0xFBC
#define VEHICLE_SUZUKI_WAGON_R                            4029                //Suzuki Wagon R                                    0xFBD
#define VEHICLE_SUZUKI_ALTO                               4030                //Suzuki Alto                                       0xFBE
#define VEHICLE_SUZUKI_MEHRAN                             4031                //Suzuki Mehran                                     0xFBF
#define VEHICLE_SUZUKI_POTOHAR                            4032                //Suzuki Potohar                                    0xFC0
#define VEHICLE_HONDA_CD_70                               4033                //Honda CD 70                                       0xFC1
#define VEHICLE_HONDA_CG_125                              4034                //Honda CG 125                                      0xFC2
#define VEHICLE_BICYCLE                                   4035                //Bicycle                                           0xFC3
#define VEHICLE_PRIVATE_BUS                               4036                //Private Bus                                       0xFC4
#define VEHICLE_AIRPORT_TRANSPORT_BUS                     4037                //Airport Transport Bus                             0xFC5
#define VEHICLE_TRUCK                                     4038                //Truck                                             0xFC6
#define VEHICLE_OIL_TANKER                                4039                //Oil Tanker                                        0xFC7
#define VEHICLE_JEEP                                      4040                //Jeep                                              0xFC8
#define VEHICLE_PUSH_BACK                                 4041                //Push Back Vehicle                                 0xFC9
#define VEHICLE_FOLLOW_ME                                 4042                //Follow Me Vehicle                                 0xFCA
#define VEHICLE_STAIRS_CABIN                              4043                //Stairs Cabin Vehicle                              0xFCB
#define VEHICLE_STAIRS_TRUCK                              4044                //Stairs Truck                                      0xFCC
#define VEHICLE_SUPPLY_VAN                                4045                //Supply Van                                        0xFCD
#define VEHICLE_HONDA_ACCORD                              4046                //Honda Accord                                      0xFCE
#define VEHICLE_BMW_7_SERIES                              4047                //BMW 7 Series                                      0xFCF
#define VEHICLE_BMW_X5                                    4048                //BMW X5                                            0xFD0

#define DEFAULT_RADAR                                     5000                //Default Radar System                              0x1388
#define MPDR_45_RADAR                                     5001                //MPDR 45                                           0x1389
#define MPDR_60_RADAR                                     5002                //MPDR 60                                           0x138A
#define MPDR_90_RADAR                                     5003                //MPDR 90                                           0x138B
#define TPS_43G_RADAR                                     5004                //TPS 43G                                           0x138C
#define TPS_77_RADAR                                      5005                //TPS 77                                            0x138D
#define YLC_II_RADAR                                      5006                //YLC II                                            0x138E
#define YLC_6_RADAR                                       5007                //YLC 6                                             0x138F
#define ATCR_RADAR                                        5008                //ATCR                                              0x1390
#define TPS_77_MRR_RADAR                                  5009                //TPS-77 MRR (Multi-role Radar)                     0x1391
#define ROHINI_RADAR                                      5010                //Rohini Radar                                      0x1392
#define GS_100_RADAR                                      5011                //GS-100 Radar                                      0x1393
#define MASTER_T_RADAR                                    5012                //Master T Radar                                    0x1394
#define ARUDHRA_RADAR                                     5013                //Arudhra MPR Radar                                 0x1395
#define BARAK_RADAR                                       5014                //Barak Radar                                       0x1396
#define VERA_RADAR                                        5015                //VERA                                              0x1397
#define YLC_2A_RADAR                                      5016                //YLC 2A                                            0x1398
#define YLC_18A_RADAR                                     5017                //YLC 18A                                           0x1399
#define YLC_8E_RADAR                                      5018                //YLC 8E                                            0x139A
#define JY_27A_RADAR                                      5019                //JY 27A                                            0x139B
#define INDRA_RADAR                                       5020                //INDRA                                             0x139C
#define MPDR_REBORN_RADAR                                 5021                //MPDR REBORN                                       0x139D

#define DEFAULT_COMMAND_AND_CONTROL_CENTER                5400                //Default Command And Control                       0x1518
#define HQ_9_COMMAND_AND_CONTROL_CENTER                   5401                //HQ-9 Control Center Vehicle                       0x1519
#define HQ_16_COMMAND_AND_CONTROL_CENTER                  5402                //HQ-16 Control Center Vehicle                      0x151A
#define SA_21_COMMAND_AND_CONTROL_CENTER                  5403                //SA-21 Command Post (S-400)                        0x151B
#define SA_3_COMMAND_AND_CONTROL_CENTER                   5404                //SA-3 Goa Battery C3 Van                           0x151C
#define SPYDER_SR_COMMAND_AND_CONTROL_CENTER              5405                //SPYDER-SR-Command and Control                     0x151D
#define SPYDER_MR_COMMAND_AND_CONTROL_CENTER              5406                //SPYDER-MR-Command and Control                     0x151E
#define BARAK_COMMAND_AND_CONTROL_CENTER                  5407                //BARAK Control Center Vehicle                      0x151F
#define SA_6_COMMAND_AND_CONTROL_CENTER                   5408                //SA-6 Battery C3 Vehicle                           0x1520
#define SA_17_COMMAND_AND_CONTROL_CENTER                  5409                //SA-17 Command Post Vehicle                        0x1521

#define DEFAULT_DETECTION_CENTER                          5500                //Default Detection Center                          0x157C
#define SPADA_DETECTION_CENTER                            5501                //SPADA Detection Center                            0x157D
#define HQ_9P_DETECTION_CENTER                            5502                //HQ-9P Search Radar Vehicle                        0x157E
#define HQ_16_DETECTION_CENTER                            5503                //HQ-16 Search Radar Vehicle                        0x157F
#define SA_21_GROWLER_DETECTION_CENTER                    5504                //SA-21 Acquisition Radar (S-400)                   0x1580
#define CROTALE_DETECTION_CENTER                          5505                //Crotale Radar System                              0x1581
#define SA_3_DETECTION_CENTER                             5506                //SA-3 Detection Center                             0x1582
#define HQ_9B_DETECTION_CENTER                            5507                //HQ-9B Search Radar Vehicle                        0x1583
#define LY_80_DETECTION_CENTER                            5508                //LY-80 Search Radar Vehicle                        0x1584
#define LY_80_EV_DETECTION_CENTER                         5509                //LY-80-EV Search Radar Vehicle                     0x1585
#define HQ_22_DETECTION_CENTER                            5510                //HQ-22 Detection Center                            0x1586

#define DEFAULT_FIRE_CONTROL_CENTER                       5600                //Default Fire Control Center                       0x15E0
#define SPADA_FIRE_CONTROL_CENTER                         5601                //SPADA Fire Control Center                         0x15E1
#define HQ_9P_FIRE_CONTROL_CENTER                         5602                //HQ-9P Fire Control Radar                          0x15E2
#define HQ_16_FIRE_CONTROL_CENTER                         5603                //HQ-16 Fire Control Radar                          0x15E3
#define SA_21_GROWLER_FIRE_CONTROL_CENTER                 5604                //SA-21 Grave Stone Engagement Radar (S-400)        0x15E4
#define LY_80_EV_FIRE_CONTROL_CENTER                      5605                //LY-80-EV Fire Control Vehicle                     0x15E5
#define HQ_9B_FIRE_CONTROL_CENTER                         5606                //HQ-9B Fire Control Radar                          0x15E6
#define LY_80_FIRE_CONTROL_CENTER                         5607                //LY-80 Fire Control Vehicle                        0x15E7
#define SA_6_FIRE_CONTROL_CENTER                          5608                //Straight Flush Engagement Radar                   0x15E8
#define SA_17_FIRE_CONTROL_CENTER                         5609                //Chair Back Engagement Radar                       0x15E9
#define HQ_22_FIRE_CONTROL_CENTER                         5610                //HQ-22 Fire Control Center                         0x15EA

#define DEFAULT_MUNITION_LAUNCHER                         5700                //Default Munition Laucher                          0x1644
#define SPADA_MUNITION_LAUNCHER                           5701                //SPADA Munition Launcher                           0x1645
#define HQ_9P_MUNITION_LAUNCHER                           5702                //HQ-9P Transporter Erector Launcher                0x1646
#define HQ_16_MUNITION_LAUNCHER                           5703                //HQ-16 Transporter Erector Launcher                0x1647
#define SA_21_MUNITION_LAUNCHER                           5704                //SA-21 Self-propelled TEL                          0x1648
#define CROTALE_MUNITION_LAUNCHER                         5705                //Crotale P4R Missile Firing System                 0x1649
#define SA_3_MUNITION_LAUNCHER                            5706                //SA-3 Missile Launcher (S-125)                     0x164A
#define HQ_9B_MUNITION_LAUNCHER                           5707                //HQ-9B Transporter Erector Launcher                0x164B
#define LY_80_MUNITION_LAUNCHER                           5708                //LY-80 Transporter Erector Launcher                0x164C
#define LY_80_EV_MUNITION_LAUNCHER                        5709                //LY-80-EV Transporter Erector Launcher             0x164D
#define SPYDER_SR_MUNITION_LAUNCHER                       5710                //SPYDER-SR Munition Launcher                       0x164E
#define SPYDER_MR_MUNITION_LAUNCHER                       5711                //SPYDER-MR Munition Launcher                       0x164F
#define BARAK_MUNITION_LAUNCHER                           5712                //Barak Munition Launcher                           0x1650
#define SA_6_MUNITION_LAUNCHER                            5713                //SA-6 TEL                                          0x1651
#define SA_8_MUNITION_LAUNCHER                            5714                //SA-8 TLAR                                         0x1652
#define SA_17_MUNITION_LAUNCHER                           5715                //SA-17 Launcher/Loader Vehicle (TEL)               0x1653
#define BRAHMOS_MUNITION_LAUNCHER                         5716                //Brahmos Munition Launcher                         0x1654
#define HQ_22_MUNITION_LAUNCHER                           5717                //HQ-22 Munition Launcher                           0x1655

#define DEFAULT_C3I_SYSTEM                                5900                //Default C3I System                                0x170C
#define GMCC_C3I_SYSTEM                                   5901                //GMCC C3I System                                   0x170D
#define SMCC_C3I_SYSTEM                                   5902                //SMCC C3I System                                   0x170E

#define DEFAULT_TANK                                      6000                //Default Tank                                      0x1770
#define TANK_ALKHALID                                     6001                //AlKhalid Tank                                     0x1771
#define TANK_AL_ZARAR                                     6002                //AlZarar Tank                                      0x1772
#define TANK_ARJUN                                        6003                //Arjun Tank                                        0x1773

#define DEFAULT_APC                                       6200                //Default Armoured Personnel Carrier                0x1838
#define APC_TALHA                                         6201                //Talha APC                                         0x1839
#define APC_BMP_1                                         6202                //BMP-1                                             0x183A
#define APC_BMP_2                                         6203                //BMP-2                                             0x183B

#define DEFAULT_ARTILLERY                                 6400                //Default Artillery                                 0x1900
#define ARTILLERY_M110A2                                  6401                //M110A2 Artillery Launcher                         0x1901
#define ARTILLERY_K9_VAJRA                                6402                //K9 Vajra Self-propelled Artillery                 0x1902
#define ARTILLERY_SH_15                                   6403                //SH-15 Self-Propelled Artillery                    0x1903
#define ARTILLERY_FATAH_I                                 6404                //Fatah-I Self-Propelled Artillery                  0x1904
#define ARTILLERY_SMERCH_PINAKA                           6405                //Smerch Pinaka Self-Propelled Artillery            0x1905
#define ARTILLERY_FATAH_II                                6406                //Fatah-II Self-Propelled Artillery                 0x1906

#define DEFAULT_FIGHTER                                   7000                //Default Fighter Aircraft                          0x1B58
#define JF17_B1                                           7001                //JF-17 Block-I Thunder                             0x1B59
#define J10C                                              7002                //J-10C Vigorous Dragon                             0x1B5A
#define F7P                                               7003                //Chengdu F-7 P                                     0x1B5B
#define F7PG                                              7004                //Chengdu F-7 PG                                    0x1B5C
#define MirageIII                                         7005                //Dassault Mirage-III                               0x1B5D
#define MirageIIIRose                                     7006                //Dassault Mirage-III ROSE                          0x1B5E
#define MirageV                                           7007                //Dassault Mirage-V                                 0x1B5F
#define F16                                               7008                //F-16 Fighting Falcon                              0x1B60
#define F16A                                              7009                //F-16 Fighting Falcon A                            0x1B61
#define F16C                                              7010                //F-16 Fighting Falcon C                            0x1B62
#define Mig21                                             7011                //Mikoyan MIG-21 Fishbed                            0x1B63
#define Mig23                                             7012                //Mikoyan MIG-23 Flogger                            0x1B64
#define Mig25                                             7013                //Mikoyan MIG-25 Foxbat                             0x1B65
#define Mig27                                             7014                //Mikoyan MIG-27 Flogger                            0x1B66
#define Mig29                                             7015                //Mikoyan MIG-29 Fulcrum                            0x1B67
#define Su30MKI                                           7016                //Sukhoi Su-30 MKI                                  0x1B68
#define Jaguar                                            7017                //Jaguar Jet                                        0x1B69
#define Harrier                                           7018                //Harrier Jet                                       0x1B6A
#define Mirage2000                                        7019                //Dassault Mirage-2000                              0x1B6B
#define Rafale                                            7020                //Dassault Rafale                                   0x1B6C
#define JF17_B3                                           7021                //JF-17 Block-III                                   0x1B6D
#define HAL_Tejas                                         7022                //HAL Tejas                                         0x1B6E
#define JF17_B2                                           7023                //JF-17 Block-2                                     0x1B6F
#define JF17_B2B                                          7024                //JF-17 Block-2B                                    0x1B70
#define F15_EAGLE                                         7025                //F-15 Eagle                                        0x1B71
#define Su35                                              7026                //Su-35                                             0x1B72
#define F16CS                                             7027                //F-16-CS                                           0x1B73
#define Tornado_ADV                                       7028                //Tornado ADV                                       0x1B74
#define J_16                                              7029                //J-16                                              0x1B75

#define DEFAULT_UAV                                       7500                //Default UAV                                       0x1D4C
#define IAIHeron                                          7501                //IAI Heron UAV                                     0x1D4D
#define IAISearcher                                       7502                //IAI Searcher                                      0x1D4E
#define FalcoUAV                                          7503                //Falco UAV                                         0x1D4F
#define Tornado_UAV                                       7504                //Tornado UAV                                       0x1D50
#define UqabUAV                                           7505                //Uqab UAV                                          0x1D51
#define DrdoAura                                          7506                //DRDO Aura UAV                                     0x1D52
#define DrdoRustom                                        7507                //DRDO Rustom UAV                                   0x1D53
#define VectorUAV                                         7508                //Vector UAV                                        0x1D54
#define RoverUAV                                          7509                //Rover UAV                                         0x1D55
#define ShadowMKI                                         7510                //Shadow MKI UAV                                    0x1D56
#define AAIRQ7Shadow                                      7511                //AAIRQ Shadow UAV                                  0x1D57
#define RQ170Sentinel                                     7512                //RQ 170 Sentinel UAV                               0x1D58
#define BuraqUAV                                          7513                //Buraq UAV                                         0x1D59
#define ShahperUAV                                        7514                //Shahper UAV                                       0x1D5A
#define WING_LOONG_II                                     7515                //Wing Loong II                                     0x1D5B
#define BAYRAKTAR_TB2                                     7516                //Bayraktar TB2                                     0x1D5C
#define BAYRAKTAR_AKINCI                                  7517                //Bayraktar Akinci                                  0x1D5D
#define YIHA_UAV                                          7518                //YIHA UAV                                          0x1D5E
#define QUADCOPTER_PAK                                    7519                //Quadcopter PAK                                    0x1D5F
#define QUADCOPTER_IND                                    7520                //Quadcopter IND                                    0x1D60
#define QUADCOPTER_PAK_KILLER_DRONE                       7521                //Quadcopter PAK Killer Drone                       0x1D61
#define QUADCOPTER_IND_KILLER_DRONE                       7522                //Quadcopter IND Killer Drone                       0x1D62
#define HAROP                                             7523                //IAI Harop (LM)                                    0x1D63
#define HARPY                                             7524                //IAI Harpy                                         0x1D64
#define OSCAR_DRONE                                       7525                //Oscar Drone                                       0x1D65

#define DEFAULT_HELICOPTER                                8000                //Default Helicopter                                0x1F40
#define AllouteIII                                        8001                //Alloute III Helicopter                            0x1F41
#define MI17                                              8002                //MI-17 Helicopter                                  0x1F42
#define MI35HindE                                         8003                //Mi-35 Hind E                                      0x1F43
#define Bell1ZViper                                       8004                //Bell 1Z Viper                                     0x1F44
#define BellAH1FCobra                                     8005                //Bell AH 1F Cobra                                  0x1F45
#define AgustaAW139                                       8006                //Agusta Westland 139                               0x1F46
#define MI24_HIND_A                                       8007                //Mi-24 Hind A                                      0x1F47
#define BELL_412_HUEY                                     8008                //Bell 412 Huey                                     0x1F48
#define AH_64E_Apache                                     8009                //AH-64E Apache                                     0x1F49

#define DEFAULT_TRAINER                                   8200                //Default Trainer                                   0x2008
#define SuperMushak                                       8201                //Super Mushak                                      0x2009
#define K8                                                8202                //Karakoram 8                                       0x200A
#define T37                                               8203                //T-37 Jet Trainer                                  0x200B

#define DEFAULT_MILITARY_AEW                              8400                //Default Military AEW                              0x20D0
#define KE03                                              8401                //Karakoram Eagle 03                                0x20D1
#define SSS                                               8402                //Saab 2000 AEW&C                                   0x20D2
#define Falcon20                                          8403                //Falcon Eagle 20                                   0x20D3
#define P3C_ORION_ASW                                     8404                //P3C Orion Anti-submarine Warfare                  0x20D4
#define PHALCON_AWACS                                     8405                //Phalcon Airbone Warning & Control System          0x20D5
#define EMBRAER                                           8406                //Embraer AWACS                                     0x20D6
#define HS_748                                            8407                //Hawker Siddeley HS 748                            0x20D7
#define KJ_500                                            8408                //KJ-500                                            0x20D8
#define YTG_9                                             8409                //YTG-9                                             0x20D9

#define DEFAULT_MILITARY_CARGO_TANKER                     8600                //Default Military Cargo Tanker                     0x2198
#define IL78                                              8601                //Illyushin IL-78                                   0x2199
#define C130                                              8602                //C-130 Hercules                                    0x219A
#define CASA_CN235                                        8603                //CASA CN 235-220                                   0x219B
#define Boeing_KC_777                                     8604                //Boeing 777 (Air to Air Refueller)                 0x219C
#define IL76                                              8605                //illyushin 76                                      0x219D
#define C17                                               8606                //C-17 Globemaster                                  0x219E
#define YY_20A                                            8607                //YY-20A                                            0x219F

#define DEFAULT_AIRLINER                                  9000                //Default Airliner                                  0x2328
#define ATR42                                             9001                //ATR-42                                            0x2329
#define ATR72                                             9002                //ATR-72                                            0x232A
#define Boeing737                                         9003                //Boeing 737                                        0x232B
#define Boeing747                                         9004                //Boeing 747                                        0x232C
#define Boeing777                                         9005                //Boeing 777                                        0x232D
#define AirbusA300                                        9006                //Airbus A300                                       0x232E
#define AirbusA310                                        9007                //Airbus A310                                       0x232F
#define AirbusA320                                        9008                //Airbus A-320                                      0x2330
#define AirbusA330                                        9009                //Airbus A330                                       0x2331
#define AirbusA340                                        9010                //Airbus A340                                       0x2332
#define AirbusA380                                        9011                //Airbus A380                                       0x2333
#define Challenger605                                     9012                //Bombardier Challenger 605                         0x2334
#define BeechcraftModel1300                               9013                //Beechcraft Model 1300 Airliner                    0x2335

#define DEFAULT_SURFACE_TANKER                            10000               //Default Surface Tanker                            0x2710
#define SURFACE_OIL_TANKER                                10001               //Generic Oil Tanker (Water)                        0x2711

#define DEFAULT_SURFACE_CARRIER                           10200               //Default Surface Carrier                           0x27D8
#define SURFACE_CARRIER_KUZNETSOV_CLASS                   10201               //Kuznetsov Class Aircraft Carrier                  0x27D9
#define SURFACE_CARRIER_VIKRAMADITYA_CLASS                10202               //Vikramaditya Class Aircraft Carrier               0x27DA

#define DEFAULT_SURFACE_GUIDED_MISSILE_DESTROYER          10400               //Default Guided Missile Destroyer DDG              0x28A0
#define SURFACE_DDG_DELHI                                 10401               //Delhi class Destroyer                             0x28A1
#define SURFACE_DDG_KOLKATA                               10402               //Kolkata class Destroyer D63 Kolkata               0x28A2

#define DEFAULT_SURFACE_GUIDED_MISSILE_FRIGATE            10600               //Default Guided MIssile Frigate FFG                0x2968
#define SURFACE_FFG_ZULFIQUAR_CLASS                       10601               //F-22P Zulfiquar Class Frigate                     0x2969

#define DEFAULT_EW_SYSTEM                                 11000               //Default EW System                                 0x2AF8
#define VERA_E                                            11001               //VERA E                                            0x2AF9
#define PENTACLE                                          11002               //Pentacle                                          0x2AFA
#define SAMYUKTA_CC_SHELTER                               11003               //Samyukta CC Shelter                               0x2AFB
#define SAMYUKTA_DF_SHELTER                               11004               //Samyukta DF Shelter                               0x2AFC
#define SAMYUKTA_ECM_SYSTEM                               11005               //Samyukta ECM System                               0x2AFD
#define EADS_CC_SHELTER                                   11006               //EADS CC Shelter                                   0x2AFE
#define EADS_DF_SHELTER                                   11007               //EADS DF Shelter                                   0x2AFF
#define EADS_ECM_SYSTEM                                   11008               //EADS ECM System                                   0x2B00
//*****************************************************************************************************************************************************//
