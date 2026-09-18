# Contribuir al Proyecto RISK

Gracias por contribuir al proyecto **RISK** de la asignatura **Estructuras de Datos**.

Este archivo define cómo organizar los cambios del equipo para que el código, la documentación y las ramas se mantengan coherentes durante la Entrega 1.

---

## 1. Alcance del proyecto

El proyecto implementa en C++ una versión por consola del juego **RISK**.

En la Entrega 1, el trabajo se concentra en el **Componente 1**, encargado de:

- inicializar una partida desde un archivo;
- administrar jugadores y turnos;
- consultar y actualizar el tablero;
- obtener y ubicar unidades;
- realizar ataques entre territorios vecinos;
- fortificar territorios propios;
- mostrar el estado actual de la partida;
- detectar cuándo un jugador controla los 42 territorios;
- finalizar correctamente la ejecución del programa.

Las misiones no hacen parte del alcance actual.

Las cartas y el mazo corresponden a una funcionalidad adicional y solo deben desarrollarse si el equipo decide implementar esa bonificación.

---

## 2. Módulos principales

El proyecto se divide en TAD relacionados entre sí.

### `Territorio`

Representa un territorio del tablero.

Debe almacenar la información necesaria para identificarlo, conocer su propietario, administrar sus unidades y representar sus relaciones con otros territorios cuando corresponda.

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

### `Jugador`

Representa a un jugador de la partida.

Actualmente administra:

- nombre;
- color;
- cartas obtenidas durante la partida.

### `Partida`

Coordina el funcionamiento general del juego.

Relaciona:

- jugadores;
- tablero;
- turno;
- ataque;
- mazo;
- estado de inicialización;
- estado de finalización;
- ganador.

Las operaciones principales del Componente 1 se coordinan desde este TAD.

### `Turno`

Controla qué jugador tiene el turno actual y la etapa correspondiente.

La forma definitiva de seleccionar el primer jugador al inicializar desde archivo debe mantenerse pendiente hasta que exista una confirmación del profesor.

### `Dados`

Se encarga de los dados utilizados durante un ataque.

Actualmente permite:

- lanzar una cantidad de dados;
- guardar los resultados;
- ordenarlos de mayor a menor;
- consultar todos los resultados;
- obtener los resultados mayores;
- limpiar el lanzamiento anterior.

### `Ataque`

Coordina la lógica de un ataque entre dos territorios.

Depende principalmente de:

- `Jugador`;
- `Tablero`;
- `Territorio`;
- `Dados`.

No se deben agregar reglas de ataque que no estén confirmadas por el enunciado o por el profesor.

### `Carta` y `Mazo`

Pertenecen a la funcionalidad adicional de cartas.

No deben condicionar el funcionamiento obligatorio del Componente 1.

---

## 3. Organización del trabajo

Antes de modificar un módulo:

1. Revisar su archivo `.h`.
2. Revisar los TAD de los que depende.
3. Confirmar que la operación esté dentro del alcance de la entrega.
4. Verificar si existe alguna regla pendiente de respuesta del profesor.
5. Mantener coherencia entre código, documentación, diagramas y pruebas.

No se debe modificar la interfaz de otro TAD únicamente para hacer funcionar una implementación incorrecta.

Si una función necesita una operación que todavía no existe, primero se debe revisar si esa operación pertenece realmente al diseño del TAD.

---

## 4. Convenciones de código

El proyecto utiliza **C++17**.

### Estilo general

Se debe mantener:

```cpp
using namespace std;
```

No se deben agregar librerías, construcciones de C++ o técnicas nuevas sin explicar primero:

- qué hacen;
- por qué son necesarias;
- por qué no basta con lo que ya usa el proyecto.

Se prefieren soluciones sencillas, explícitas y fáciles de defender durante la sustentación.

Cuando sea posible, utilizar:

- ciclos `for`;
- ciclos `while`;
- condiciones claras;
- `vector`;
- operaciones básicas de STL vistas en clase.

Evitar introducir sin justificación:

- `auto`;
- lambdas;
- algoritmos de STL para reemplazar lógica que el grupo debe implementar;
- conversiones avanzadas;
- estructuras adicionales que no hagan parte del diseño;
- librerías incluidas únicamente por comodidad.

---

## 5. Encabezados e implementación

Cada TAD debe mantener separadas su interfaz y su implementación:

```text
NombreTAD.h
NombreTAD.cpp
```

El archivo `.h` contiene:

- estado del TAD;
- prototipos de sus operaciones.

El archivo `.cpp` contiene:

- implementación de las operaciones declaradas en el encabezado.

Las firmas del `.cpp` deben coincidir exactamente con las declaradas en el `.h`.

No se deben crear funciones nuevas en el `.cpp` sin revisar primero si pertenecen al diseño.

---

## 6. Comentarios

Los comentarios deben explicar decisiones importantes y partes que no sean obvias.

Usar comentarios con:

```cpp
//
```

Ejemplo recomendado:

```cpp
// Ordena los resultados de mayor a menor porque primero se comparan los dados mas altos.
```

Otro ejemplo:

```cpp
// Se recibe por referencia para evitar copiar toda la carta y const evita modificarla.
```

Evitar comentarios demasiado formales o artificiales, por ejemplo:

```cpp
// Esto es necesario debido a que el sistema requiere efectuar la posterior comparacion de los valores obtenidos.
```

También se debe evitar comentar instrucciones evidentes como cada `return`, llave o asignación simple.

---

## 7. Reglas del juego que no se deben cambiar

Hasta que exista una nueva aclaración del profesor:

- después de una fortificación debe quedar mínimo una unidad en el territorio de origen;
- después de conquistar un territorio se debe mover al menos una unidad al territorio conquistado;
- el territorio de origen tampoco puede quedar vacío;
- un jugador gana cuando controla los 42 territorios;
- en un empate de dados gana el defensor;
- el ataque utiliza hasta tres dados del atacante y hasta dos del defensor según la lógica que finalmente sea confirmada;
- no se debe inventar una cantidad mínima definitiva de unidades para iniciar o continuar un ataque mientras esa regla siga pendiente de confirmación.

Cuando una regla no esté confirmada, se debe marcar como **pendiente** y no implementarla como decisión final.

---

## 8. Flujo de ramas

Las ramas principales son:

- `main`: versión principal protegida;
- `develop`: rama de integración protegida.

El trabajo nuevo debe realizarse en ramas separadas.

Ejemplos:

```text
feature/nombre-funcionalidad
fix/nombre-correccion
docs/nombre-documentacion
```

Ejemplos aplicados al proyecto:

```text
feature/isabella-jugador-partida
feature/saul-modelo-mapa
fix/isabella-dados-ataque
```

No se debe trabajar directamente sobre `main` ni mezclar cambios no relacionados dentro de una misma rama.

---

## 9. Commits

Cada commit debe representar un cambio claro y relacionado.

Para mantener los mensajes organizados, se usará el siguiente formato:

```text
tipo(modulo): descripcion breve
```

### Tipos de commit

| Tipo | Cuándo usarlo |
|---|---|
| `feat` | Cuando se agrega una funcionalidad nueva. |
| `fix` | Cuando se corrige un error o comportamiento incorrecto. |
| `docs` | Cuando solamente cambia documentación. |
| `test` | Cuando se agregan o modifican pruebas. |
| `refactor` | Cuando se reorganiza código sin cambiar su comportamiento esperado. |
| `chore` | Para tareas de mantenimiento del repositorio que no cambian la lógica del programa. |

### Módulo o alcance

Dentro de los paréntesis se indica la parte del proyecto que cambia.

Ejemplos de módulos:

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
main
docs
repo
```

Si un commit afecta principalmente un solo TAD, se debe utilizar ese TAD como módulo.

### Ejemplos para este proyecto

Nueva funcionalidad en `Tablero`:

```text
feat(tablero): implementar busqueda de territorios
```

Implementación de relaciones del mapa:

```text
feat(tablero): agregar consulta de vecindad entre territorios
```

Nueva operación de `Territorio`:

```text
feat(territorio): implementar manejo de unidades
```

Nueva funcionalidad en `Jugador`:

```text
feat(jugador): implementar operaciones basicas del jugador
```

Nueva funcionalidad en `Partida`:

```text
feat(partida): implementar estado basico de la partida
```

Corrección de la búsqueda de jugadores:

```text
fix(partida): corregir busqueda de jugadores
```

Implementación de dados:

```text
feat(dados): implementar lanzamiento y manejo de resultados
```

Corrección de dados:

```text
fix(dados): corregir ordenamiento de resultados
```

Implementación de ataque:

```text
feat(ataque): implementar validaciones basicas del ataque
```

Corrección relacionada con conquista:

```text
fix(ataque): corregir traslado de unidades al conquistar
```

Pruebas del comando atacar:

```text
test(ataque): agregar casos de prueba de configuracion invalida
```

Documentación de TAD:

```text
docs(tads): documentar jugador partida y dados
```

Actualización del diagrama:

```text
docs(diagrama): actualizar relaciones entre tads
```

Cambio interno que no modifica el comportamiento:

```text
refactor(partida): simplificar busqueda de jugadores
```

Limpieza de archivos duplicados del repositorio:

```text
chore(repo): eliminar archivos duplicados
```

Actualización del archivo de contribución:

```text
docs(repo): actualizar guia de contribucion
```

### Reglas para escribir los mensajes

- Usar el tipo en minúscula: `feat`, `fix`, `docs`, etc.
- Escribir el módulo entre paréntesis.
- Después de los dos puntos, escribir una descripción corta y concreta.
- El mensaje debe decir qué cambió, no frases genéricas como `cambios`, `arreglos` o `update`.
- Un commit debe contener cambios relacionados entre sí.
- Si se están modificando módulos diferentes por razones diferentes, es preferible separarlos en commits distintos.

Ejemplo recomendado:

```text
feat(tablero): implementar busqueda de territorios
```

Evitar:

```text
cambios
```

```text
fix: cosas del tablero
```

```text
update final ahora si
```

Antes de crear un commit se debe comprobar que solamente estén incluidos los archivos relacionados con ese cambio.

## 10. Pull Requests

Los cambios deben integrarse a `develop` mediante Pull Request.

Antes de solicitar la integración:

- comprobar que la rama esté actualizada;
- revisar los archivos modificados;
- compilar los `.cpp` afectados;
- comprobar que no existan errores ni advertencias relevantes;
- verificar que no se hayan incluido archivos ajenos al cambio;
- revisar que código y documentación sean coherentes.

El Pull Request debe indicar brevemente:

- qué módulo se modificó;
- qué problema resuelve;
- qué archivos fueron cambiados;
- qué dependencias tiene;
- qué queda pendiente.

Los cambios deben ser revisados por otro integrante antes de integrarse.

---

## 11. Compilación

Los archivos modificados deben comprobarse con C++17.

La compilación debe realizarse con advertencias activadas:

```text
-std=c++17 -Wall -Wextra -pedantic
```

No se debe considerar terminado un módulo únicamente porque su archivo compila de forma aislada.

Cuando las dependencias estén disponibles, también se debe comprobar que el proyecto completo compile y enlace correctamente.

---

## 12. Pruebas

Las pruebas deben comprobar tanto casos válidos como inválidos.

Para el comando `atacar` se deben considerar, entre otros:

- territorio de origen inexistente;
- territorio de destino inexistente;
- territorio de origen que no pertenece al jugador;
- territorio de destino propio;
- territorios que no son vecinos;
- unidades insuficientes;
- pérdida de unidades del atacante;
- pérdida de unidades del defensor;
- empate de dados;
- conquista de territorio;
- traslado de unidades después de conquistar;
- condición de victoria.

No se deben inventar resultados obtenidos.

Primero se define el resultado esperado, luego se ejecuta el programa y finalmente se registra el resultado real.

---

## 13. Documentación y diagrama de TAD

La documentación del proyecto debe mantenerse sincronizada con el código.

Cada TAD documentado en el informe debe incluir:

- descripción;
- estado;
- condiciones de las variables;
- interfaz;
- precondiciones;
- poscondiciones.

El diagrama de relación entre TAD de `draw.io` **no es un diagrama UML de clases**.

Por lo tanto, no se deben agregar:

- `public`;
- `private`;
- signos `+` o `-`;
- rombos de composición;
- punteros;
- referencias;
- firmas completas de C++.

En el diagrama se utiliza notación abstracta, por ejemplo:

```text
string        -> cadena de caracteres
int           -> numerico entero
bool          -> booleano
void          -> vacio
vector<T>     -> secuencia de T
```

---

## 14. Uso de inteligencia artificial

Si una parte del código o de la documentación fue desarrollada con apoyo de una herramienta de IA, debe registrarse de manera honesta según las instrucciones de la entrega.

La IA puede utilizarse como apoyo para:

- explicar conceptos de C++;
- revisar lógica propuesta por el grupo;
- detectar errores;
- revisar redacción;
- sugerir correcciones sobre código existente.

Las sugerencias deben revisarse antes de incorporarlas.

No se debe presentar como trabajo completamente propio una solución generada directamente por una herramienta externa.

Cuando se consulte una construcción de C++ nueva, también debe quedar claro qué se investigó y por qué fue necesario utilizarla.

---

## 15. Dependencias entre módulos

Antes de trabajar en un módulo, revisar sus dependencias.

Actualmente, la relación principal es:

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
```

`Ataque` también necesita consultar y modificar información del `Tablero` y de los `Territorio`.

Por esta razón, los cambios en `Territorio`, `Continente` o `Tablero` deben revisarse antes de cerrar definitivamente la implementación de `Ataque`.

---

## 16. Antes de considerar un cambio terminado

Comprobar:

- [ ] El cambio pertenece al alcance actual.
- [ ] El `.h` y el `.cpp` coinciden.
- [ ] No se inventaron reglas.
- [ ] No se agregaron librerías innecesarias.
- [ ] Las construcciones nuevas fueron entendidas y justificadas.
- [ ] Se mantiene `using namespace std;`.
- [ ] El código puede explicarse durante la sustentación.
- [ ] Los comentarios son claros y naturales.
- [ ] El archivo compila con C++17.
- [ ] Se probaron los casos relacionados con el cambio.
- [ ] La documentación correspondiente fue revisada.
- [ ] El commit contiene únicamente archivos relacionados.
- [ ] El Pull Request tiene como destino `develop`.

---

## 17. Prioridad ante dudas

Cuando exista una contradicción, utilizar este orden:

1. Respuesta directa del profesor.
2. Enunciado oficial del proyecto.
3. Diapositivas y formato trabajado en clase.
4. Diseño y decisiones confirmadas por el equipo.
5. Reglas oficiales de RISK cuando el profesor indique aplicarlas.
6. Sugerencias externas o de herramientas de IA.

Si todavía falta información, la decisión debe permanecer pendiente hasta ser confirmada.
