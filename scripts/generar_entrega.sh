#!/bin/bash

if [ -z "$1" ]; then
    echo "Uso: ./scripts/generar_entrega.sh numero_entrega"
    echo "Ejemplo: ./scripts/generar_entrega.sh 2"
    exit 1
fi

ENTREGA="$1"

# Ubicarse siempre en la raíz del proyecto,
# sin importar desde dónde se ejecute el script.
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROYECTO_DIR="$(dirname "$SCRIPT_DIR")"

cd "$PROYECTO_DIR" || exit 1

ZIP="entregas/Entrega_${ENTREGA}_Risk.zip"

echo "Generando Entrega $ENTREGA..."

rm -f "$ZIP"

zip "$ZIP" *.cpp *.h *.txt

echo
echo "Archivos incluidos:"
unzip -l "$ZIP"

echo
echo "Entrega creada correctamente:"
echo "$ZIP"