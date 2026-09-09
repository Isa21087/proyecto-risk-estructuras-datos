# Guía de trabajo en equipo con GitHub, WSL y VS Code

## Proyecto

**Sistema de apoyo para el juego Risk — Entrega 0**

Integrantes:

- Saúl Leonardo Cruz Romero
- Isabella Hermosa Losada
- Alejandro Macias Barrios

Esta guía explica el procedimiento desde cero. El repositorio central del equipo es:

`https://github.com/Isa21087/proyecto-risk-estructuras-datos`

## 1. Idea general

Cada integrante tiene una copia del proyecto en su computador. GitHub conserva la versión central.

- `main`: versión oficial del proyecto.
- Rama: espacio separado para desarrollar una tarea sin alterar `main`.
- Commit: punto de guardado con una descripción del cambio.
- Push: subir los commits a GitHub.
- Pull: descargar cambios desde GitHub.
- Pull request: solicitud para unir una rama con `main`.
- Merge: aceptar el pull request e incorporar el cambio a `main`.

**Regla principal:** nadie programa directamente en `main`. Cada tarea se realiza en una rama.

---

## 2. Configuración inicial de cada colaborador

Esta sección se realiza una sola vez en cada computador. Isabella ya completó esta configuración.

### 2.1. Aceptar la invitación

El colaborador debe iniciar sesión en su propia cuenta de GitHub y aceptar la invitación al repositorio privado.

### 2.2. Comprobar Git en WSL

Abrir Ubuntu/WSL y ejecutar:

```bash
git --version
```

### 2.3. Configurar la identidad

Cada persona escribe su propio nombre y el correo asociado a su cuenta de GitHub:

```bash
git config --global user.name "NOMBRE COMPLETO"
git config --global user.email "CORREO_DE_GITHUB"
git config --global init.defaultBranch main
```

### 2.4. Instalar e iniciar sesión en GitHub CLI

```bash
sudo apt update
sudo apt install gh
gh auth login
```

Elegir:

```text
GitHub.com
HTTPS
Yes
Login with a web browser
```

Autorizar la cuenta propia en el navegador y después ejecutar:

```bash
gh auth setup-git
```

### 2.5. Clonar el repositorio

Si ya existe una carpeta final vacía, entrar en ella y clonar usando el punto final:

```bash
cd "RUTA_DE_LA_CARPETA_VACIA"
git clone https://github.com/Isa21087/proyecto-risk-estructuras-datos.git .
```

El punto significa “descargar dentro de la carpeta actual”.

Ejemplo de Saúl:

```bash
cd "/mnt/c/Users/Conej/Desktop/Estrucutras/ProyectoEstructuras"
git clone https://github.com/Isa21087/proyecto-risk-estructuras-datos.git .
```

Comprobar:

```bash
git status
```

Debe indicar que está en `main` y actualizado con `origin/main`.

---

## 3. Rutina al encender el computador

No se repiten `git init`, `git clone` ni `gh auth login` cada día.

### Isabella

```bash
cd "/mnt/c/Users/Usuario/Desktop/Proyecto Estructuras"
code .
```

### Saúl

```bash
cd "/mnt/c/Users/Conej/Desktop/Estrucutras/ProyectoEstructuras"
code .
```

Cada integrante usa la ruta de su propia copia.

En la terminal de VS Code, revisar:

```bash
git status
git branch
```

El asterisco de `git branch` muestra la rama actual.

---

## 4. Comenzar una tarea nueva

Primero actualizar `main`:

```bash
git switch main
git pull origin main
```

Crear una rama con un nombre relacionado con la tarea:

```bash
git switch -c nombre-de-la-rama
```

Ejemplos:

```bash
git switch -c interfaz-consola
git switch -c comando-ayuda
git switch -c validacion-parametros
```

Los nombres de las ramas se escriben sin espacios ni tildes.

---

## 5. Guardar y subir cambios

Después de modificar y guardar los archivos en VS Code:

```bash
git status
git add .
git commit -m "Descripción clara del cambio"
git push -u origin nombre-de-la-rama
```

Ejemplo:

```bash
git status
git add .
git commit -m "Agregar ayuda general de comandos"
git push -u origin comando-ayuda
```

La opción `-u` solo es necesaria la primera vez que se sube una rama. Para los siguientes avances en esa misma rama:

```bash
git add .
git commit -m "Descripción del nuevo avance"
git push
```

---

## 6. Continuar una tarea otro día

Abrir WSL, entrar en la carpeta y abrir VS Code. Después:

```bash
git branch
git switch nombre-de-la-rama
git pull
```

No se crea otra rama si se continuará la misma tarea.

Al terminar el nuevo avance:

```bash
git add .
git commit -m "Descripción del avance"
git push
```

---

## 7. Unir el trabajo con `main`

Cuando una tarea esté completa:

1. Subir todos los cambios de la rama.
2. Abrir el repositorio en GitHub.
3. Presionar **Compare & pull request**.
4. Comprobar que aparezca `base: main` y `compare: nombre-de-la-rama`.
5. Explicar brevemente qué se modificó.
6. Crear el pull request.
7. Otro integrante revisa la pestaña **Files changed**.
8. Si todo funciona, se presiona **Merge pull request**.

Después del merge, todos actualizan su copia:

```bash
git switch main
git pull origin main
```

La persona que creó la rama puede eliminarla localmente:

```bash
git branch -d nombre-de-la-rama
```

---

## 8. Integrar dos trabajos antes del pull request

Supongamos que el trabajo de Isabella ya se unió a `main` y Saúl sigue trabajando en su rama.

Saúl incorpora el `main` actualizado en su rama:

```bash
git switch main
git pull origin main
git switch nombre-de-la-rama-de-saul
git merge main
```

Después debe compilar y probar el programa combinado. Si funciona:

```bash
git push
```

Entonces crea su pull request.

---

## 9. Si aparece un conflicto

Un conflicto ocurre cuando dos personas modifican las mismas líneas.

1. No hacer `push` inmediatamente.
2. Abrir el archivo marcado por Git en VS Code.
3. Revisar cuidadosamente ambos cambios.
4. Conservar la combinación correcta; no elegir **Accept Both** sin verificar.
5. Guardar el archivo.
6. Compilar y probar.
7. Finalizar con:

```bash
git add .
git commit -m "Resolver conflicto al integrar cambios"
git push
```

Si no entienden qué parte conservar, deben detenerse y revisarlo en equipo antes de continuar.

---

## 10. Rutina antes de cerrar o irse a dormir

Guardar los archivos con `Ctrl + S` y ejecutar:

```bash
git status
git add .
git commit -m "Avance: descripción de lo realizado"
git push
```

Si la tarea todavía no está terminada, el avance puede permanecer en su rama. No es obligatorio crear el pull request ese día.

---

## 11. Comandos que no deben repetirse diariamente

Estos comandos son de configuración inicial:

```text
git init
git clone
git remote add origin
git config --global...
gh auth login
```

No deben ejecutarse nuevamente al comenzar cada sesión.

Tampoco se debe utilizar:

```bash
git push origin main
```

para subir trabajo cotidiano. Los cambios se suben desde una rama y se integran mediante un pull request.

---

## 12. Resumen rápido

### Tarea nueva

```bash
git switch main
git pull origin main
git switch -c nombre-de-la-rama
```

### Guardar avance

```bash
git add .
git commit -m "Descripción del cambio"
git push
```

En el primer `push` de la rama:

```bash
git push -u origin nombre-de-la-rama
```

### Después de un merge

```bash
git switch main
git pull origin main
```

### Regla final

`main` es la versión oficial; cada tarea se desarrolla en una rama y llega a `main` mediante un pull request revisado.
