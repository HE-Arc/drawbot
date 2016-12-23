%module(directors="1") Dessin;

%include "typemaps.i"
%apply float *OUTPUT { float& x }
%apply float *OUTPUT { float& y }

%{
#include "src/declarations.h"
#include "src/callback.h"
#include "src/caller.h"
#include "../programme/dessins.h"

#define LOG

extern Caller* caller;
%}

%feature("director") Callback;

%include "src/caller.h"
%include "src/callback.h"

extern void etoile(float cx, float cy, float r);
extern void fleur(float cx, float cy, float rTotal, float k);
extern void coeur(float cx, float cy, float r);
extern void cercle(float cx, float cy, float r);
extern void spirale(float cx, float cy, float cr, float pas);
extern void droite(float x1, float y1, float x2, float y2);
extern void rectangle(float x1, float y1, float x2, float y2);
extern void maison(float x, float y, float h);

extern void moveServos();
extern void toAngle(float x, float y);

extern Caller* caller;

%pragma(java) jniclasscode=%{
    static {
        java.io.File path = new java.io.File(".");
        try {
            path = new java.io.File(Dessin.class.getProtectionDomain().getCodeSource().getLocation().toURI().getPath());
        } catch(java.net.URISyntaxException use) {
            System.err.println(use.getMessage());
        }
        System.load(path.getParent() + "/Dessin.so");
    }
%}
