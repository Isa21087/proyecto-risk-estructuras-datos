#!/bin/bash

NOMBRE_ZIP="entregas/Entrega_2_Risk.zip"

echo "Generando entrega..."

rm -f "$NOMBRE_ZIP"

zip "$NOMBRE_ZIP" *.cpp *.h *.txt

echo
echo "Archivos incluidos:"
unzip -l "$NOMBRE_ZIP"

echo
echo "Entrega creada correctamente en:"
echo "$NOMBRE_ZIP"
