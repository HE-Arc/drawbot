%module(directors="1") shared;

%include "typemaps.i"
%apply float *OUTPUT { float& x }
%apply float *OUTPUT { float& y }

%{
#include "src/declarations.h"
#include "src/callback.h"
#include "src/caller.h"
#include "../programme/shared.h"

#define LOG

extern Caller* caller;
%}

%feature("director") Callback;

%include "src/caller.h"
%include "src/callback.h"

extern void etoile(float cx, float cy, float r, float par=-1);

extern void moveServos();
extern void toAngle(float x, float y);

extern Caller* caller;

%pragma(java) jniclasscode=%{
    static {
        java.io.File path = new java.io.File(".");
        try {
            path = new java.io.File(shared.class.getProtectionDomain().getCodeSource().getLocation().toURI().getPath());
        } catch(java.net.URISyntaxException use) {
            System.err.println(use.getMessage());
        }
        System.load(path.getParent() + "/shared.so");
    }
%}
