#ifndef EXT_EYE_FOVEATION_H_
#define EXT_EYE_FOVEATION_H_ 1

/*
** Copyright 2017-2023 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/


#ifdef __cplusplus
extern "C" {
#endif


#ifndef XR_EXT_eye_foveation

#define XR_EXT_eye_foveation 1
#define XR_EXT_eye_foveation_SPEC_VERSION 1
#define XR_EXT_EYE_FOVEATION_EXTENSION_NAME "XR_EXT_eye_foveation"
#define XR_TYPE_SYSTEM_EYE_FOVEATION_PROPERTIES_EXT ((XrStructureType)1000370000U)
#define XR_TYPE_VIEW_FOVEA_MAPPING_INFO_EXT ((XrStructureType)1000370001U)

typedef XrFlags64 XrFoveaMappingStateFlagsEXT;
static const XrFoveaMappingStateFlagsEXT XR_FOVEA_MAPPING_STATE_TRACKED_BIT_EXT = 0x00000001;

typedef struct XrSystemEyeFoveationPropertiesEXT {
    XrStructureType type;
    void* XR_MAY_ALIAS next;
    XrBool32 supportsEyeFoveation;
} XrSystemEyeFoveationPropertiesEXT;

typedef struct XrViewFoveaMappingInfoEXT {
    XrStructureType type;
    const void* XR_MAY_ALIAS next;
    XrTime sampleTime;
    XrVector2f foveaMapping;
    XrFoveaMappingStateFlagsEXT flags;
} XrViewFoveaMappingInfoEXT;

#endif /* XR_EXT_eye_foveation */

#ifdef __cplusplus
}
#endif

#endif
