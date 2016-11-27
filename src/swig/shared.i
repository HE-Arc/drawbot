%module shared

%include "typemaps.i"
%apply float *OUTPUT { float& x }
%apply float *OUTPUT { float& y }

%{
#include <vector>

extern bool _etoile(
    float& x,
    float& y,
    float cx,
    float cy,
    float r,
    float par=-1);

%}

extern bool _etoile(
    float& x,
    float& y,
    float cx,
    float cy,
    float r,
    float par=-1);

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
