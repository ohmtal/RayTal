//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// RayFlux Gui
//-----------------------------------------------------------------------------
#pragma once

#include "raylib.h"
#include "TypeDef.h"

namespace RayFlux {

    struct LazyGui {
        U16 x = 0;
        U16 y = 0;
        U16 size = 20;


        U16 spacing = 10;
        void Write(const char* text, Color color = LIGHTGRAY);
        int CheckBox( const char *text, bool *checked);
        int ComboBox( F32 width, const char *text, int *active);
        int Button( F32 width, const char *text);


    };



}
