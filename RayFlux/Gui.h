#pragma once

#define RAYGUI_IMPLEMENTATION
#include "raygui_custom.h"

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
            int result = GuiCheckBox(Rectangle((float) x,(float)y, (float)size, (float)size), text, checked);
            y += size + spacing;
            return result;
        }
        int ComboBox( float width, const char *text, int *active) {
            int result = GuiComboBox(Rectangle((float) x,(float)y, width, (float)size), text, active);
            y += size + spacing;
            return result;
        }

    };



}
