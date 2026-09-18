# Contribuir al Proyecto RISK


Este archivo define cómo organizar el trabajo del equipo durante el desarrollo completo del proyecto, incluyendo código, documentación, pruebas, ramas, commits y entregas.

El objetivo es mantener una implementación coherente, organizada y fácil de entender y sustentar por todos los integrantes.

---

## 1. Alcance del proyecto

El proyecto implementa en C++ una versión por consola del juego **RISK**.

El desarrollo es incremental y está dividido en tres componentes principales:

- **Componente 1:** configuración y desarrollo del juego mediante estructuras lineales.
- **Componente 2:** almacenamiento y recuperación de partidas mediante estructuras jerárquicas y codificación de Huffman.
- **Componente 3:** estrategias de juego mediante estructuras no lineales, específicamente grafos.

Cada nueva entrega debe conservar, corregir y completar las funcionalidades desarrolladas anteriormente.

Por esta razón, el código, la documentación, los diagramas y las pruebas deben representar siempre el estado actual completo del proyecto.

---

## 2. Componentes del proyecto

### Componente 1: configuración del juego

Incluye las funcionalidades relacionadas con el desarrollo normal de una partida:

- inicializar una partida desde un archivo;
- administrar jugadores;
- administrar turnos;
- consultar y actualizar el tablero;
- obtener y ubicar unidades;
- realizar ataques;
- fortificar territorios;
- mostrar el estado actual de la partida;
- detectar la condición de victoria;
- finalizar correctamente la ejecución.

Comandos principales:

```text
inicializar
obtener_unidades
atacar
fortificar
estado_juego
salir
```

### Componente 2: almacenamiento de partidas

Permite almacenar y recuperar el estado de una partida.

Debe utilizar estructuras jerárquicas y el algoritmo de codificación de **Huffman**.

Comandos principales:

```text
guardar
guardar_comprimido
inicializar
```

El comando `inicializar` debe poder trabajar tanto con partidas almacenadas normalmente como con archivos comprimidos cuando esta funcionalidad haya sido implementada.

### Componente 3: estrategias de juego

Utiliza **grafos** para ayudar al jugador a tomar decisiones relacionadas con la conquista de territorios.

Comandos principales:

```text
costo_conquista
conquista_mas_barata
```

---

## 3. Módulos y TAD principales

El proyecto se divide en TAD relacionados entre sí.

### `Territorio`

Representa un territorio del tablero.

Administra la información necesaria para:

- identificar el territorio;
- conocer su propietario;
- almacenar la cantidad de unidades;
- consultar sus relaciones con otros territorios cuando corresponda.

### `Continente`

Agrupa los territorios pertenecientes a un mismo continente.

La estructura acordada es:

```text
Continente
    └── secuencia de Territorio
```

### `Tablero`

Representa el tablero completo de RISK.

La estructura acordada es:

```text
Tablero
    └── secuencia de Continente
            └── secuencia de Territorio
```

No se debe mantener otra secuencia independiente de territorios dentro de `Tablero`, porque esto podría generar dos fuentes de información diferentes sobre el mismo territorio.

Cuando se implemente el Componente 3, las relaciones entre territorios también serán utilizadas para representar y consultar el grafo del tablero.

### `Jugador`

Representa a un jugador de la partida.

Administra principalmente:

- nombre;
- color;
- cartas obtenidas durante la partida;
- información necesaria para conocer su estado dentro del juego.

### `Partida`

Coordina el funcionamiento general del juego.

Relaciona principalmente:

- jugadores;
- tablero;
- turno;
- ataque;
- mazo;
- estado de inicialización;
- estado de finalización;
- ganador.

Las operaciones principales del sistema deben coordinarse desde este TAD cuando corresponda.

### `Turno`

Controla:

- qué jugador tiene el turno actual;
- qué etapa del turno se está ejecutando.

Las etapas deben respetar el flujo definido para:

```text
obtener unidades
→ atacar
→ fortificar
→ siguiente jugador
```

### `Dados`

Se encarga de los dados utilizados durante un ataque.

Permite:

- lanzar una cantidad de dados;
- almacenar los resultados;
- ordenarlos;
- consultar los resultados;
- obtener los valores necesarios para realizar las comparaciones;
- limpiar el lanzamiento anterior.

### `Ataque`

Coordina la lógica de un ataque entre dos territorios.

Depende principalmente de:

- `Jugador`;
- `Tablero`;
- `Territorio`;
- `Dados`.

Las reglas implementadas deben corresponder al enunciado o a aclaraciones directas del profesor.

### `Carta` y `Mazo`

Administran las cartas utilizadas dentro del juego.

Su funcionamiento debe mantenerse coherente con las reglas de obtención e intercambio de cartas que correspondan al estado actual del proyecto.

### Estructuras de Huffman

Para el Componente 2 se deberán utilizar las estructuras necesarias para:

- calcular frecuencias;
- construir el árbol de Huffman;
- generar códigos;
- codificar información;
- decodificar información;
- guardar y recuperar archivos comprimidos.

Los TAD concretos utilizados deben corresponder al diseño implementado por el grupo.

### Grafo

Para el Componente 3 se utilizará una representación de grafo que permita analizar los territorios y sus conexiones.

Debe permitir implementar las operaciones necesarias para:

```text
costo_conquista
conquista_mas_barata
```

La estructura definitiva debe corresponder al diseño realizado por el equipo y a los conceptos vistos en clase.

---

## 4. Organización del trabajo

Antes de modificar un módulo:

1. Revisar su archivo `.h`.
2. Revisar los TAD de los que depende.
3. Revisar el enunciado correspondiente.
4. Confirmar que la operación pertenece al alcance actual.
5. Revisar si existe alguna aclaración del profesor relacionada con esa funcionalidad.
6. Mantener coherencia entre código, documentación, diagramas y pruebas.

No se debe modificar la interfaz de otro TAD únicamente para hacer funcionar una implementación incorrecta.

Si una función necesita una operación que todavía no existe, primero se debe revisar si esa operación realmente pertenece al diseño del TAD correspondiente.

---

## 5. Organización del repositorio

La organización general debe mantenerse aproximadamente así:

```text
Proyecto Estructuras/
│
├── .github/
│   └── CONTRIBUTING.md
│
├── documentacion/
│   ├── entrega2/
│   └── entrega3/
│
├── pruebas/
│   ├── entrega1/
│   ├── entrega2/
│   └── entrega3/
│
├── entregas/
│
├── scripts/
│   └── generar_entrega.sh
│
├── .gitignore
├── main.cpp
├── *.cpp
├── *.h
└── archivos necesarios para ejecutar el programa
```

### Archivos especiales

`.gitignore` debe permanecer en la raíz del repositorio.

Los scripts auxiliares deben almacenarse en:

```text
scripts/
```

La carpeta `.github/` se utiliza para archivos relacionados con la organización del repositorio en GitHub.

---

## 6. Convenciones de código

El proyecto utiliza **C++17**.

Se debe mantener:

```cpp
using namespace std;
```

Se prefieren soluciones sencillas, explícitas y fáciles de explicar durante la sustentación.

Cuando sea posible, utilizar:

- ciclos `for`;
- ciclos `while`;
- condiciones claras;
- `vector`;
- estructuras vistas en clase;
- operaciones básicas de STL conocidas por el equipo.

No se deben agregar construcciones, librerías o técnicas nuevas sin entender primero:

- qué hacen;
- por qué son necesarias;
- qué problema solucionan;
- por qué son apropiadas para este proyecto.

Evitar introducir sin justificación:

- `auto`;
- lambdas;
- algoritmos avanzados de STL;
- conversiones innecesariamente complejas;
- estructuras adicionales que no correspondan al diseño;
- librerías incluidas únicamente por comodidad.

Todo integrante debe poder explicar el código que entrega.

---

## 7. Encabezados e implementación

Cada TAD debe mantener separadas su interfaz y su implementación:

```text
NombreTAD.h
NombreTAD.cpp
```

El archivo `.h` contiene principalmente:

- estado del TAD;
- prototipos de las operaciones.

El archivo `.cpp` contiene:

- implementación de las operaciones declaradas en el encabezado.

Las firmas del `.cpp` deben coincidir exactamente con las declaradas en el `.h`.

No se deben crear operaciones públicas nuevas sin revisar primero si corresponden al diseño del TAD.

---

## 8. Comentarios

Los comentarios deben explicar decisiones importantes y partes que no sean evidentes.

Usar comentarios naturales y concretos.

Ejemplo:

```cpp
// Ordena los resultados de mayor a menor porque primero se comparan los dados mas altos.
```

Otro ejemplo:

```cpp
// Se recibe por referencia para evitar copiar toda la carta y const evita modificarla.
```

Evitar comentarios artificiales o innecesariamente formales.

También se debe evitar comentar instrucciones evidentes como:

- cada `return`;
- cada asignación;
- cada llave;
- operaciones cuyo propósito ya es claro por el nombre de la función.

---

## 9. Reglas del juego

Las reglas implementadas deben provenir de:

1. aclaraciones directas del profesor;
2. enunciado oficial;
3. material trabajado en clase.

Entre las reglas actualmente utilizadas se encuentran:

- después de una fortificación debe quedar mínimo una unidad en el territorio de origen;
- después de conquistar un territorio se deben trasladar unidades al territorio conquistado;
- el territorio atacante no puede quedar vacío;
- un jugador puede ganar al controlar los 42 territorios según la modalidad implementada;
- en un empate de dados gana el defensor;
- únicamente se pueden atacar territorios vecinos;
- la fortificación se realiza entre territorios propios permitidos por las reglas.

No se deben inventar reglas cuando exista una duda.

Cuando una condición todavía no haya sido confirmada, debe mantenerse como **pendiente** hasta obtener una respuesta del profesor.

---

## 10. Flujo de ramas

La rama principal del proyecto es:

```text
main
```

`main` representa la versión estable del proyecto y se encuentra protegida.

No se debe trabajar directamente sobre `main`.

Todo cambio debe realizarse primero en una rama separada y luego integrarse mediante Pull Request.

### Nombre de las ramas

Todas las ramas deben indicar:

1. el tipo de trabajo;
2. la persona responsable;
3. la tarea o módulo.

Formato:

```text
tipo/nombre-tarea
```

Los nombres utilizados por el equipo son:

```text
isabella
saul
alejandro
```

### Nuevas funcionalidades

Formato:

```text
feature/nombre-tarea
```

Ejemplos:

```text
feature/isabella-huffman
feature/saul-guardar-comprimido
feature/alejandro-inicializar-binario
```

### Correcciones

Formato:

```text
fix/nombre-tarea
```

Ejemplos:

```text
fix/isabella-ataque
fix/saul-tablero
fix/alejandro-turno
```

### Documentación

Formato:

```text
docs/nombre-tarea
```

Ejemplos:

```text
docs/isabella-diseno-entrega2
docs/saul-plan-pruebas
docs/alejandro-diagrama-tads
```

### Organización y mantenimiento

Formato:

```text
chore/nombre-tarea
```

Ejemplos:

```text
chore/isabella-preparar-entrega3
chore/saul-organizar-pruebas
```

### Reglas para las ramas

- Usar siempre `isabella`, `saul` o `alejandro` como responsable.
- Escribir todo en minúsculas.
- No utilizar espacios.
- No utilizar tildes.
- Separar palabras mediante guiones.
- Una rama debe corresponder a una tarea concreta.
- No mezclar cambios diferentes dentro de una misma rama.
- No trabajar directamente sobre `main`.

Antes de empezar una tarea nueva:

```bash
git switch main
git pull origin main
git switch -c feature/isabella-nombre-tarea
```

Cambiar `feature` por `fix`, `docs` o `chore` cuando corresponda.

---

## 11. Commits

Cada commit debe representar un cambio claro y relacionado.

Formato:

```text
tipo(modulo): descripcion breve
```

### Tipos de commit

| Tipo | Uso |
|---|---|
| `feat` | Nueva funcionalidad |
| `fix` | Corrección de un error |
| `docs` | Cambios únicamente de documentación |
| `test` | Creación o modificación de pruebas |
| `refactor` | Reorganización de código sin cambiar su comportamiento |
| `chore` | Organización o mantenimiento del repositorio |

### Módulo o alcance

Ejemplos:

```text
jugador
partida
territorio
continente
tablero
turno
dados
ataque
carta
mazo
huffman
grafo
main
docs
repo
```

### Ejemplos

```text
feat(tablero): implementar busqueda de territorios
```

```text
feat(territorio): implementar manejo de unidades
```

```text
fix(partida): corregir busqueda de jugadores
```

```text
feat(dados): implementar lanzamiento y manejo de resultados
```

```text
fix(ataque): corregir traslado de unidades al conquistar
```

```text
feat(huffman): implementar calculo de frecuencias
```

```text
feat(huffman): construir arbol de codificacion
```

```text
feat(grafo): implementar representacion del tablero
```

```text
test(ataque): agregar casos de configuracion invalida
```

```text
test(huffman): agregar pruebas de guardar comprimido
```

```text
docs(tads): actualizar descripcion de estructuras
```

```text
docs(repo): actualizar guia de contribucion
```

```text
chore(repo): preparar estructura para entrega 3
```

### Reglas para commits

- Usar el tipo en minúscula.
- Indicar el módulo entre paréntesis.
- Escribir después de `:` una descripción corta.
- Indicar qué cambió.
- No utilizar mensajes genéricos.
- Mantener cambios relacionados en el mismo commit.
- Separar cambios diferentes en commits distintos.

Evitar mensajes como:

```text
cambios
```

```text
update
```

```text
arreglos finales
```

```text
ahora si
```

Antes de realizar el commit:

```bash
git status
```

y comprobar qué archivos se incluirán.

---

## 12. Pull Requests

Todo cambio destinado a la versión estable debe integrarse a `main` mediante Pull Request.

El flujo esperado es:

```text
rama de trabajo
        ↓
Pull Request
        ↓
main
```

Antes de crear un Pull Request:

- comprobar que la tarea esté terminada;
- revisar los archivos modificados;
- comprobar que el proyecto compile;
- ejecutar las pruebas correspondientes;
- verificar que no se incluyan archivos innecesarios;
- comprobar que código y documentación sean coherentes.

El Pull Request debe explicar brevemente:

- qué se modificó;
- qué problema resuelve;
- qué archivos principales cambiaron;
- si existen dependencias;
- qué queda pendiente.

Cuando sea posible, otro integrante debe revisar los cambios antes de integrarlos.

---

## 13. Compilación

El proyecto debe comprobarse utilizando C++17.

Compilación general:

```bash
g++ -std=c++17 *.cpp
```

Para una revisión más estricta se puede utilizar:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp
```

Luego ejecutar:

```bash
./a.out
```

No se debe considerar terminado un módulo únicamente porque su archivo `.cpp` compile de forma aislada.

También debe comprobarse que el proyecto completo compile y enlace correctamente.

---

## 14. Pruebas

Las pruebas deben comprobar casos válidos e inválidos.

No se deben inventar resultados.

El procedimiento recomendado es:

1. definir el caso;
2. definir el resultado esperado;
3. ejecutar el programa;
4. registrar el resultado obtenido;
5. comparar ambos resultados.

### Entrega 1

El plan de pruebas se concentra principalmente en:

```text
atacar
```

### Entrega 2

El plan de pruebas debe incluir:

```text
guardar_comprimido
```

### Entrega 3

El plan de pruebas debe incluir:

```text
costo_conquista
```

Las pruebas utilizadas en cada entrega deben almacenarse en su carpeta correspondiente:

```text
pruebas/entrega1/
pruebas/entrega2/
pruebas/entrega3/
```

---

## 15. Documentación

La documentación debe mantenerse sincronizada con la implementación.

El documento de diseño es **incremental**.

Esto significa que una nueva entrega no documenta únicamente lo nuevo, sino el estado completo del proyecto hasta ese momento.

Cada TAD documentado debe seguir el formato solicitado en clase.

Según corresponda, debe incluir:

- descripción;
- estado;
- condiciones de las variables;
- interfaz;
- precondiciones;
- poscondiciones.

También se deben incluir los diagramas o esquemáticos solicitados para explicar el funcionamiento de las operaciones principales.

La documentación correspondiente a cada entrega debe almacenarse en:

```text
documentacion/entrega2/
documentacion/entrega3/
```

---

## 16. Diagrama de relación entre TAD

El diagrama de relación entre TAD utilizado en el proyecto **no es un diagrama UML de clases**.

No se deben agregar elementos propios de UML que no hayan sido solicitados, como:

- `public`;
- `private`;
- signos `+` y `-`;
- rombos de composición;
- punteros;
- referencias;
- firmas completas de C++.

Utilizar notación abstracta.

Ejemplos:

```text
string      -> cadena de caracteres
int         -> numerico entero
bool        -> booleano
void        -> vacio
vector<T>   -> secuencia de T
```

El diagrama debe mostrar los TAD utilizados realmente por la implementación y sus relaciones.

---

## 17. Dependencias entre módulos

Antes de modificar un módulo se deben revisar sus dependencias.

La relación general actual incluye:

```text
Partida
├── Jugador
├── Tablero
│   └── Continente
│       └── Territorio
├── Turno
├── Ataque
│   └── Dados
└── Mazo
    └── Carta
```

`Ataque` también consulta y modifica información relacionada con `Tablero` y `Territorio`.

El Componente 2 agregará las estructuras necesarias para Huffman.

El Componente 3 utilizará las relaciones entre territorios para trabajar con el grafo del tablero.

Cuando cambie la implementación, esta sección también debe actualizarse.

---

## 18. Organización de las entregas

Las entregas anteriores deben conservarse como evidencia de lo que realmente fue entregado.

No se deben modificar posteriormente los ZIP correspondientes a entregas ya realizadas.

Los archivos finales se almacenan en:

```text
entregas/
```

Ejemplo:

```text
entregas/
├── Entrega_1_Risk.zip
├── Entrega_2_Risk.zip
└── Entrega_3_Risk.zip
```

La documentación correspondiente a cada entrega debe mantenerse organizada en:

```text
documentacion/
├── entrega2/
└── entrega3/
```

Las pruebas deben almacenarse en:

```text
pruebas/
├── entrega1/
├── entrega2/
└── entrega3/
```

Los scripts auxiliares se almacenan en:

```text
scripts/
```

Actualmente se utiliza:

```text
scripts/generar_entrega.sh
```

Este script permite generar de forma automática el archivo ZIP correspondiente a una entrega.

### Uso del script de entrega

Antes de utilizar el script por primera vez, se debe comprobar que tenga permiso de ejecución:

```bash
chmod +x scripts/generar_entrega.sh
```

Este permiso normalmente queda registrado en Git después de realizar el commit correspondiente, pero puede volver a aplicarse si fuera necesario.

Para generar la Entrega 2:

```bash
./scripts/generar_entrega.sh 2
```

Para generar la Entrega 3:

```bash
./scripts/generar_entrega.sh 3
```

El script genera automáticamente el archivo correspondiente dentro de:

```text
entregas/
```

Por ejemplo:

```text
entregas/Entrega_2_Risk.zip
```

o:

```text
entregas/Entrega_3_Risk.zip
```

El ZIP debe contener únicamente los archivos necesarios para la entrega según las instrucciones vigentes del profesor.

Actualmente el script incluye los archivos:

```text
*.cpp
*.h
*.txt
```

ubicados en la raíz del proyecto.

No se deben incluir archivos compilados o temporales como:

```text
*.o
*.exe
a.out
```

Tampoco se deben incluir dentro del ZIP carpetas internas como:

```text
.git/
.github/
documentacion/
pruebas/
scripts/
```

La documentación final debe entregarse de la forma indicada por el profesor para la entrega correspondiente.

Si existe una diferencia entre el enunciado escrito y una instrucción posterior dada directamente por el profesor, se debe seguir la instrucción más reciente confirmada.

Antes de entregar se debe revisar manualmente el contenido del ZIP generado para comprobar que no falte ningún archivo necesario y que no se haya incluido información adicional por error.

No se debe modificar manualmente un ZIP correspondiente a una entrega anterior.

## 19. Uso de inteligencia artificial

El uso de herramientas de inteligencia artificial debe seguir las instrucciones establecidas para el proyecto.

Cuando una parte del código o de la documentación sea desarrollada con apoyo de IA, se debe identificar de manera honesta según lo solicitado por el profesor.

Cuando corresponda, debe registrarse:

- qué parte recibió apoyo de IA;
- qué herramienta fue utilizada;
- el prompt utilizado;
- si el resultado fue modificado posteriormente por el equipo.

El contenido generado con apoyo de IA no debe superar el límite definido por el enunciado de la asignatura.

La IA puede utilizarse como apoyo para:

- explicar conceptos;
- revisar lógica;
- detectar errores;
- revisar redacción;
- sugerir alternativas;
- entender código existente.

Las sugerencias deben ser revisadas, comprendidas y adaptadas antes de incorporarse.

Todo integrante debe ser capaz de explicar durante la sustentación el código que presenta.

---

## 20. Antes de considerar una tarea terminada

Comprobar:

- [ ] Estoy trabajando en una rama diferente de `main`.
- [ ] La rama contiene mi nombre.
- [ ] El cambio pertenece al alcance actual.
- [ ] Revisé el enunciado o la aclaración correspondiente.
- [ ] El `.h` y el `.cpp` coinciden.
- [ ] No inventé reglas.
- [ ] No agregué librerías innecesarias.
- [ ] Entiendo cualquier construcción nueva utilizada.
- [ ] El código puede explicarse durante la sustentación.
- [ ] Los comentarios son claros y naturales.
- [ ] El proyecto compila con C++17.
- [ ] Probé los casos relacionados con mi cambio.
- [ ] Revisé la documentación correspondiente.
- [ ] `git status` contiene únicamente los archivos relacionados.
- [ ] El commit tiene un mensaje claro.
- [ ] El Pull Request tiene como destino `main`.

---

## 21. Prioridad ante dudas

Cuando exista una contradicción, utilizar este orden:

1. Respuesta directa y reciente del profesor.
2. Enunciado oficial del proyecto.
3. Diapositivas y material trabajado en clase.
4. Diseño y decisiones confirmadas por el equipo.
5. Reglas oficiales de RISK cuando el profesor indique aplicarlas.
6. Sugerencias externas o herramientas de inteligencia artificial.

Si todavía falta información, la decisión debe permanecer como **pendiente** hasta ser confirmada.