// Copyright 2023 Varjo Technologies Oy. All rights reserved.
#ifndef VARJO_OPENXR_EXPERIMENTAL_H
#define VARJO_OPENXR_EXPERIMENTAL_H

#include "ext_eye_foveation.h"
#include "ext_composition_layer_blend_mask.h"
#include "ext_composition_layer_overlay.h"

// TODO: These flags are normally in openxr.h from conan package.
static const XrCompositionLayerFlags XR_COMPOSITION_LAYER_PREVENT_MASKING_BIT = 0x00000008;
static const XrCompositionLayerFlags XR_COMPOSITION_LAYER_PREVENT_FORCED_DEPTH_TESTING_BIT = 0x00000010;

#endif  // VARJO_OPENXR_EXPERIMENTAL_H