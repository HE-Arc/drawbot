#!/bin/sh
# TODO: write a proper Makefile

set -xe

NAME=shared

mkdir -p swig/build \
    swig/gen

swig -java -c++ \
    -outdir swig/gen \
    "swig/${NAME}.i"

g++ -c -fpic -fno-strict-aliasing \
    "swig/src/declarations.cpp"

g++ -c -fpic -fno-strict-aliasing \
    "swig/${NAME}_wrap.cxx" \
    -I/usr/lib/jvm/java-8-openjdk/include \
    -I/usr/lib/jvm/java-8-openjdk/include/linux
rm -r "swig/${NAME}_wrap.cxx" "swig/${NAME}_wrap.h"

g++ -shared \
    "${NAME}_wrap.o" \
    "declarations.o" \
    -o "swig/${NAME}.so"
rm -f "${NAME}.o" "${NAME}_wrap.o" "declarations.o"

mkdir -p swig/build
javac -d swig/build \
    -cp /usr/share/processing/core/library/core.jar \
    swig/src/*.java \
    swig/gen/*.java
rm -rf "swig/gen"

jar cvfm \
    "swig/${NAME}.jar" \
    "swig/src/MANIFEST.MF" \
    -C "swig/build" \
    .
rm -rf "swig/build"

mv "swig/${NAME}.jar" "swig/${NAME}.so" simulateur/code

java \
    -cp /usr/share/processing/core/library/core.jar:simulateur/code/shared.jar \
    Dessin
