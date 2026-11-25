#!/usr/bin/env bash
set -Eeuo pipefail

# Preparar exclusivamente el ZIP oficial de la Entrega 3 de RISK
# No incluye imagenes, datos de prueba, scripts, historicos ni archivos .git
# Debe ejecutarse desde la raiz del repositorio: bash /ruta/generar_entrega3.sh

if [[ ! -f "Partida.cpp" || ! -f "Grafo.h" || ! -d "pruebas/entrega3" ]]; then
  echo 'ERROR: entra primero a la raiz del repositorio Proyecto Estructuras.' >&2
  exit 1
fi

PDF='documentacion/entrega3/Documento_Entrega_3_Risk.pdf'
ZIP='entregas/Entrega_3_Risk.zip'

if [[ ! -s "$PDF" ]]; then
  echo "ERROR: falta $PDF" >&2
  echo 'Descarga el PDF final de Overleaf y guardalo en esa ubicacion, con ese nombre.' >&2
  exit 1
fi
if [[ "$(head -c 4 "$PDF")" != '%PDF' ]]; then
  echo "ERROR: $PDF no parece un documento PDF valido." >&2
  exit 1
fi

for cmd in git g++ zip unzip mktemp; do
  if ! command -v "$cmd" >/dev/null; then
    echo "ERROR: no esta instalado el comando $cmd" >&2
    exit 1
  fi
done

if [[ "$(git branch --show-current)" != 'main' ]]; then
  echo 'ERROR: cambia a main antes de generar la entrega.' >&2
  exit 1
fi
if [[ "$(git rev-parse HEAD)" != "$(git rev-parse origin/main)" ]]; then
  echo 'ERROR: tu main local y origin/main no coinciden. Revisa el estado Git.' >&2
  exit 1
fi
if ! git diff --quiet HEAD -- '*.cpp' '*.cxx' '*.h' '*.hxx'; then
  echo 'ERROR: hay cambios locales sin registrar en archivos fuente.' >&2
  exit 1
fi

shopt -s nullglob
FUENTES=( ./*.cpp ./*.cxx ./*.h ./*.hxx )
CPP=( ./*.cpp ./*.cxx )
SIN_MAIN=()
for archivo in "${CPP[@]}"; do
  [[ "$archivo" == './main.cpp' ]] || SIN_MAIN+=("$archivo")
done

if (( ${#CPP[@]} == 0 || ${#FUENTES[@]} == 0 )) || [[ ! -f './main.cpp' ]]; then
  echo 'ERROR: faltan los archivos fuente de RISK.' >&2
  exit 1
fi

TEMP="$(mktemp -d)"
trap 'rm -rf "$TEMP"' EXIT

echo '=== 1. Compilacion del programa completo ==='
g++ -std=c++17 "${CPP[@]}" -o "$TEMP/risk"
echo 'COMPILACION_PRINCIPAL_OK'

echo '=== 2. Pruebas automatizadas del Componente 3 ==='
if [[ ! -f pruebas/entrega3/test_grafo.cpp ]]; then
  echo 'ERROR: falta test_grafo.cpp' >&2
  exit 1
fi
g++ -std=c++17 -I. pruebas/entrega3/test_grafo.cpp Grafo.cpp -o "$TEMP/test_grafo"
"$TEMP/test_grafo"

for nombre in test_costo_conquista test_conquista_mas_barata; do
  if [[ ! -f "pruebas/entrega3/${nombre}.cpp" ]]; then
    echo "ERROR: falta pruebas/entrega3/${nombre}.cpp" >&2
    exit 1
  fi
  g++ -std=c++17 -I. "pruebas/entrega3/${nombre}.cpp" "${SIN_MAIN[@]}" -o "$TEMP/$nombre"
  "$TEMP/$nombre"
done
echo 'PRUEBAS_E3_OK'

echo '=== 3. ZIP oficial sin carpetas internas ==='
mkdir -p entregas
if [[ -e "$ZIP" ]]; then
  echo "ERROR: ya existe $ZIP; no se sobrescribira automaticamente." >&2
  echo 'Si es una version anterior, renombrala manualmente y vuelve a ejecutar.' >&2
  exit 1
fi
zip -q -X -j "$TEMP/Entrega_3_Risk.zip" "$PDF" "${FUENTES[@]}"
unzip -t "$TEMP/Entrega_3_Risk.zip" | tail -n 1

# Acepta exclusivamente el PDF final y los archivos fuente en la raiz del ZIP.
while IFS= read -r nombre; do
  case "$nombre" in
    */*) echo "ERROR: el ZIP contiene una ruta interna: $nombre" >&2; exit 1 ;;
    Documento_Entrega_3_Risk.pdf|*.h|*.hxx|*.cpp|*.cxx) ;;
    *) echo "ERROR: hay un archivo no permitido: $nombre" >&2; exit 1 ;;
  esac
done < <(unzip -Z1 "$TEMP/Entrega_3_Risk.zip")

# Prueba de independencia del repositorio: extraer el ZIP en otra carpeta
# y compilar sus fuentes sin utilizar archivos de otras rutas.
mkdir -p "$TEMP/extraido"
(
  cd "$TEMP/extraido"
  unzip -q ../Entrega_3_Risk.zip
  EXTRACCION_CPP=( ./*.cpp ./*.cxx )
  g++ -std=c++17 "${EXTRACCION_CPP[@]}" -o ../risk_extraido
)
echo 'COMPILACION_DESDE_ZIP_OK'

mv "$TEMP/Entrega_3_Risk.zip" "$ZIP"
echo
printf 'ZIP_FINAL: %s\n' "$ZIP"
printf 'COMMIT_VERIFICADO: %s\n' "$(git rev-parse --short HEAD)"
echo 'Contenido del ZIP:'
unzip -Z1 "$ZIP"
echo
printf 'ENTREGA_3_LISTA_PARA_REVISION\n'
