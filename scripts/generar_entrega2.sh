
#!/usr/bin/env bash
set -euo pipefail

# Este script prepara solamente la Entrega 2
# El ZIP oficial no incluye archivos de pruebas ni carpetas internas

PROYECTO="$(cd "$(dirname "$0")/.." && pwd)"
cd "$PROYECTO"

PDF="documentacion/entrega2/Documento_Entrega_2_Risk.pdf"
ZIP_FINAL="entregas/Entrega_2_Risk.zip"
RESPALDO="entregas/Respaldo_Pruebas_Entrega_2_Risk.zip"

# Verificamos que el documento definitivo ya esté guardado
if [ ! -s "$PDF" ]; then
    echo "ERROR: falta el PDF final en $PDF"
    exit 1
fi

# Incluimos todos los tipos de archivo fuente permitidos
shopt -s nullglob
FUENTES=( *.cpp *.cxx *.h *.hxx )

if [ "${#FUENTES[@]}" -eq 0 ]; then
    echo "ERROR: no se encontraron archivos fuente"
    exit 1
fi

mkdir -p entregas

TEMP="$(mktemp -d)"
trap 'rm -rf "$TEMP"' EXIT

# Comprobamos la compilación antes de empaquetar
echo "Verificando compilación..."
g++ -std=c++17 -Wall -Wextra -pedantic \
    ./*.cpp -o "$TEMP/risk"

# Creamos el ZIP oficial sin rutas ni carpetas internas
# Incluimos el archivo de partida y las pruebas de la segunda entrega
PRUEBAS=( pruebas/entrega2/archivos_generados/*.txt
          pruebas/entrega2/archivos_generados/*.bin )

zip -q -j "$TEMP/Entrega_2_Risk.zip" \
    "$PDF" "${FUENTES[@]}" partida.txt "${PRUEBAS[@]}"

mv "$TEMP/Entrega_2_Risk.zip" "$ZIP_FINAL"

# Guardamos las pruebas en otro ZIP separado
zip -q -r "$TEMP/Respaldo.zip" \
    pruebas/entrega1 \
    pruebas/entrega2 \
    partida.txt \
    scripts/generar_entrega2.sh

mv "$TEMP/Respaldo.zip" "$RESPALDO"

echo
echo "===== ENTREGA OFICIAL ====="
unzip -l "$ZIP_FINAL"

echo
echo "===== RESPALDO DE PRUEBAS ====="
unzip -l "$RESPALDO"

echo
echo "ZIP oficial: $ZIP_FINAL"
echo "Respaldo: $RESPALDO"
