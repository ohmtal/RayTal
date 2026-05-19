//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// RayFlux Gui
//
// Struct Gui handle gui elements in a way we can get the last states like
// mIsClicked. Every Widget return a boolean usually mIsClicked.
// I only have a few Widgets so far. A bit inspired by ImGui.
// I had started with LazyGui which nearly does the same but to use SameLine
// all Widgets needs to be ported to get the size of each.
// for full control it's possible to combine it with the raygui functions.
//
// Example:
// init:
//      RayFlux::Gui gui(100 , 100);
// render:
//      gui.Begin(); // reset cursor and mLastBounds
//      gui.Write("Hello World");
//      //Combine example:
//        gui.setStates(SliderSize); // set the size of the element
//        static float sliderVal = 1.f; //GetMusicVolume(mainMusic);
//        // mLastBounds is set by setStates
//        if (GuiSlider(gui.mLastBounds, nullptr, "Vol.", &sliderVal, 0.f, 1.f)) {
//            SetMusicVolume(*mainMusic,  sliderVal);
//        }
//
//      gui.End(); // OPTIONAL at the moment - does nothing but looks good ;)
//-----------------------------------------------------------------------------
#pragma once

#include "raylib.h"
#include "TypeDef.h"


namespace RayFlux {

   struct Gui {
        F32 mLeft = 0.f;
        F32 mTop  = 0.f;
        Vector2 mCursor = {0.f, 0.f};
        Vector2 mSpacing = { 10.f, 10.f };
        Vector2 mDefaultSize = { 20.f, 20.f };

        bool mSameLine  = false;

        // last states
        bool mIsFocused = false;
        bool mIsPressed = false;
        bool mIsClicked = false;
        Rectangle mLastBounds = {0.f, 0.f, 0.f, 0.f};
        S32 mLastState  = 0;


        Gui(F32 x, F32 y) {
            mLeft = x;
            mTop  = y;
            mCursor = Vector2(x,y);
        }
        void Begin() {
            mCursor = Vector2(mLeft, mTop);
            mLastBounds = {0.f, 0.f, 0.f, 0.f};

        }
        void End() {

        }

        void SameLine( F32 relativeX=0.f ) {
            mSameLine = true;
            if (relativeX > 0.f) mCursor.x =  mLeft + relativeX ;
        }

        F32 getX() { return mCursor.x; };
        F32 getY() { return mCursor.y; };
        F32 incX(F32 value) { mCursor.x += value;  return mCursor.x; };
        F32 incY(F32 value) { mCursor.y += value; return mCursor.y; };
        void setX(F32 value) { mCursor.x = value; }
        void setY(F32 value) { mCursor.y = value; }
        // ---------------------------------------------------------------------
        // Button control, returns true when clicked
        bool Button(const Vector2 size, const char *text);
        bool Button(const F32 width, const char *text) { return Button({width, mDefaultSize.y}, text);}
        // Check Box control, returns 1 when state changed
        bool CheckBox(const Vector2 size, const char *text, bool *checked);
        bool CheckBox(const char* text, bool* checked) { return CheckBox(mDefaultSize, text, checked);}
        // Default write
        bool Write(const char *text, int fontSize, Color color = LIGHTGRAY);
        bool Write(const char *text,  Color color = LIGHTGRAY) { return Write(text, mDefaultSize.y, color); }
        // Label
        bool Label(const char *text);

        bool Separator(const Vector2 size, Color color = LIGHTGRAY);
        bool Separator(const F32 width, Color color = LIGHTGRAY) { return Separator( { width, 0.f }, color); }

    // private: not --- for full control !
        void resetStates();
        void setStates(const Vector2 size);

        void enhanceCursor();
    }; // GUI

    // =========================================================================
    // old version keep for compat - will be removed in future
    struct LazyGui {
        F32 x = 0.0f;
        F32 y = 0.0f;
        F32 size = 20.0f;

        LazyGui(F32 lx, F32 ly, F32 lsize = 20.f ) : x(lx), y(ly), size(lsize) {}

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
