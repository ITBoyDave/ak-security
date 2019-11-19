#/usr/bin/env bash

#gcc base64.c base64.h -o base64.so
gcc -I $JAVA_HOME/include/ -I $JAVA_HOME/include/linux -I . -fPIC -shared aksecurity.c -L .  -o libak_security.so base64.c
