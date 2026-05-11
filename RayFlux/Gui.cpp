#include "Gui.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui_custom.h"

namespace RayFlux {


    void LazyGui::Write(const char* text, Color color){
        DrawText(text, x, y,size, color);
        y += size + spacing;
    }

    int LazyGui::CheckBox(const char* text, bool* checked){
        int result = GuiCheckBox(Rectangle((F32) x,(F32)y, (F32)size, (F32)size), text, checked);
        y += size + spacing;
        return result;
    }

    int LazyGui::ComboBox(F32 width, const char* text, int* active){
        int result = GuiComboBox(Rectangle((F32) x,(F32)y, width, (F32)size), text, active);
        y += size + spacing;
        return result;
    }

    int LazyGui::Button(F32 width, const char* text){
        int result = GuiButton(Rectangle((F32) x,(F32)y, width, (F32)size), text);
        y += size + spacing;
        return result;
    }
}
