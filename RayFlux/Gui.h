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
        F32 x = 0.0f;
        F32 y = 0.0f;
        F32 size = 20.0f;

        LazyGui(F32 lx, F32 ly) : x(lx), y(ly) {}

        F32 spacing = 10.0f;



        // ------------------------------------------------
        void Write(const char* text, Color color = LIGHTGRAY);
        void Label(const char* );
        int CheckBox( const char *text, bool *checked);
        int ComboBox( F32 width, const char *text, int *active);
        int Button( F32 width, const char *text);
        void Separator (F32 width, Color color = LIGHTGRAY);

    private:
        bool sameLine = false;
        void inc(F32 valueY = 0.f) {
            if (valueY > 0.f) y += valueY;
            else y += size + spacing;
        }
    };



}
