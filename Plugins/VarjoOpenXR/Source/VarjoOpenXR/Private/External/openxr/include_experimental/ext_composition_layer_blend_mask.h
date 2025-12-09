#ifndef EXT_COMPOSITION_LAYER_BLEND_MASK_H_
#define EXT_COMPOSITION_LAYER_BLEND_MASK_H_ 1

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


#ifndef XR_EXT_composition_layer_blend_mask

#define XR_EXT_composition_layer_blend_mask 1
#define XR_EXT_composition_layer_blend_mask_SPEC_VERSION 1
#define XR_EXT_COMPOSITION_LAYER_BLEND_MASK_EXTENSION_NAME "XR_EXT_composition_layer_blend_mask"

#define XR_TYPE_COMPOSITION_LAYER_BLEND_MASK_VARJO ((XrStructureType)1000376000U)

// TODO: These modes directly map to varjo_BlendControlMaskingMode modes!
typedef XrFlags64 XrMaskingMode;
static const XrMaskingMode XR_MASKING_MODE_OFF = 0;
static const XrMaskingMode XR_MASKING_MODE_RESTRICTED = 1;  // Use chroma keying in masked area (or plain VST if not active), elsewhere show VR content.
static const XrMaskingMode XR_MASKING_MODE_EXTENDED = 2;    // Show VR content in masked area, elsewhere use chroma keying (or plain VST if not active).
static const XrMaskingMode XR_MASKING_MODE_REDUCED = 3;     // Show VST content in masked area, elsewhere use chroma keying (or plain VST if not active).
static const XrMaskingMode XR_MASKING_MODE_DEPTH_TEST_OR_ALWAYS_FAIL = 4;  // Do VST depth test in masked area, elsewhere always fail depth test (show VST).
static const XrMaskingMode XR_MASKING_MODE_DEPTH_TEST_OR_ALWAYS_PASS = 5;  // Do VST depth test in masked area, elsewhere always pass depth test (show VR).

// TODO: These modes directly map to varjo_BlendControlDebugMode modes!
typedef XrFlags64 XrMaskingDebugMode;
static const XrMaskingDebugMode XR_MASKING_DEBUG_MODE_OFF = 0;          // No debug visualization
static const XrMaskingDebugMode XR_MASKING_DEBUG_MODE_SHOW_MASK = 1;    // Visualize mask alpha value.
static const XrMaskingDebugMode XR_MASKING_DEBUG_MODE_SHOW_COLORS = 2;  // Visualize mask rgb values (meaningful only with RGBA texture format).


typedef struct XrCompositionLayerBlendMaskVarjo {
    XrStructureType type;
    const void* XR_MAY_ALIAS next;
    XrCompositionLayerFlags layerFlags;
    XrSpace space;
    uint32_t viewCount;
    const XrCompositionLayerProjectionView* views;
    bool forceGlobalViewOffset;
    XrMaskingMode maskingMode;
    XrMaskingDebugMode debugMode;

} XrCompositionLayerBlendMaskVarjo;

#endif /* XR_EXT_composition_layer_blend_mask */

#ifdef __cplusplus
}
#endif

#endif
