#pragma once

#define RAYGUI_IMPLEMENTATION
#include "raygui_custom.h"
#include "TypeDef.h"

namespace RayFlux {

    struct LazyGui {
        U16 x = 0;
        U16 y = 0;
        U16 size = 20;


        U16 spacing = 10;
        void Write(const char* text, Color color = LIGHTGRAY) {
            DrawText(text, x, y,size, color);
            y += size + spacing;
        }

        int CheckBox( const char *text, bool *checked) {
            int result = GuiCheckBox(Rectangle((F32) x,(F32)y, (F32)size, (F32)size), text, checked);
            y += size + spacing;
            return result;
        }
        int ComboBox( F32 width, const char *text, int *active) {
            int result = GuiComboBox(Rectangle((F32) x,(F32)y, width, (F32)size), text, active);
            y += size + spacing;
            return result;
        }

        int Button( F32 width, const char *text) {
            int result = GuiButton(Rectangle((F32) x,(F32)y, width, (F32)size), text);
            y += size + spacing;
            return result;
        }

    };



}
