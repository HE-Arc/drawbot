#!/bin/sh
# TODO: write a proper Makefile

set -xe

NAME=shared

swig -java -c++ \
    -outdir swig/src/ \
    "swig/${NAME}.i"

g++ -c -fpic -fno-strict-aliasing \
    "programme/${NAME}.cpp"

g++ -c -fpic -fno-strict-aliasing \
    "swig/${NAME}_wrap.cxx" \
    -I/usr/lib/jvm/java-8-openjdk/include \
    -I/usr/lib/jvm/java-8-openjdk/include/linux
rm -r "swig/${NAME}_wrap.cxx"

g++ -shared \
    "${NAME}.o" \
    "${NAME}_wrap.o" \
    -o "swig/${NAME}.so"
rm -f "${NAME}.o" "${NAME}_wrap.o"

mkdir -p swig/build
javac -d swig/build \
    -cp /usr/share/processing/core/library/core.jar \
    swig/src/*.java
rm -f \
    "swig/src/${NAME}.java" \
    "swig/src/${NAME}JNI.java" \
    swig/src/*_double.java

jar cvfm \
    "swig/${NAME}.jar" \
    swig/src/MANIFEST.MF \
    -C swig/build \
    .
rm -rf swig/build

mv "swig/${NAME}.jar" "swig/${NAME}.so" simulateur/code

java \
    -cp /usr/share/processing/core/library/core.jar:simulateur/code/shared.jar \
    Dessin
