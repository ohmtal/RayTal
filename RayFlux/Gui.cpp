#include "Gui.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui_custom.h"

namespace RayFlux {


    void LazyGui::Write(const char* text, Color color){
        DrawText(text, (S32)x, (S32)y, (S32)size, color);
        y += size + spacing;
    }

    void LazyGui::Label(const char* text){
        GuiLabel(Rectangle( x,y, size, size),  text);
        y += size + spacing;
    }

    int LazyGui::CheckBox(const char* text, bool* checked){
        int result = GuiCheckBox(Rectangle( x,y, size, size), text, checked);
        y += size + spacing;
        return result;
    }

    int LazyGui::ComboBox(F32 width, const char* text, int* active){
        int result = GuiComboBox(Rectangle( x,y, width, size), text, active);
        y += size + spacing;
        return result;
    }

    int LazyGui::Button(F32 width, const char* text){
        int result = GuiButton(Rectangle( x,y, width, size), text);
        y += size + spacing;
        return result;
    }

    void LazyGui::Separator (F32 width, Color color ) {
        DrawLine(x, y,  x + width, y, color);
        y += spacing;
    }
}
