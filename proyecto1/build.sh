#!/bin/bash

CC="clang++"
CCFLAGS=""
EXE="main"
SRC="*.cpp"

$CC $CCFLAGS $SRC -o $EXE

#rm clientes.bin productos.bin proveedores.bin
#cp productos.def.bin productos.bin
#cp clientes.def.bin clientes.bin 
#cp proveedores.def.bin proveedores.bin
