#ifndef EXT_COMPOSITION_LAYER_OVERLAY_H_
#define EXT_COMPOSITION_LAYER_OVERLAY_H_ 1

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


#ifndef XR_EXT_composition_layer_overlay

#define XR_EXT_composition_layer_overlay 1
#define XR_EXT_composition_layer_overlay_SPEC_VERSION 1
#define XR_EXT_COMPOSITION_LAYER_OVERLAY_EXTENSION_NAME "XR_EXT_composition_layer_overlay"

#define XR_TYPE_COMPOSITION_LAYER_OVERLAY_VARJO ((XrStructureType)1000376001U)


typedef struct XrCompositionLayerOverlayVarjo {
    XrStructureType type;
    const void* XR_MAY_ALIAS next;
    XrCompositionLayerFlags layerFlags;
    XrSpace space;
    uint32_t viewCount;
    const XrCompositionLayerProjectionView* views;
} XrCompositionLayerOverlayVarjo;

#endif /* XR_EXT_composition_layer_overlay */

#ifdef __cplusplus
}
#endif

#endif
