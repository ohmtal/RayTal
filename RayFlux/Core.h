/*
 * Copy and Paste Template:

    class TEMPLATE: public RayFlux::Core {
    public:
        //----------------------------------------------------------------------
        bool Init() override {

            return true;
        }
        //----------------------------------------------------------------------
        void ShutDown() override {

        }
        //----------------------------------------------------------------------
        void Update(F32 dt) override {

        }
        //----------------------------------------------------------------------
        void Render() override {

        }

    }; //class...
*/

#pragma once

#include "TypeDef.h"

namespace RayFlux {

    // ---------------- Core Class
    class Core  {

    public:
        virtual bool Init() { return true; }
        virtual void Update(F32 dt) {}
        virtual void Render() {}
        virtual void ShutDown() {}
    }; //class

} ; //namespace
