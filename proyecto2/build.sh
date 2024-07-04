#!/bin/bash

CC="clang++"
CCFLAGS="-std=c++11"
EXE="main"
SRC="*.cpp"

$CC $CCFLAGS $SRC -o $EXE

rm clientes1.bin clientes2.bin clientes1.dat clientes2.dat clientes.bin log.txt
cp clientes.def.dat clientes.dat
cp productos.def.dat productos.dat
#cp clientes.def.bin clientes.bin 
#cp proveedores.def.bin proveedores.bin
