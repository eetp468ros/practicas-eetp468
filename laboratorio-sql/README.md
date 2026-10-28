# Laboratorio SQL

Página para practicar comandos SQL desde el celular o la compu, sin instalar nada.
Publicada en <https://sql.eetp468.edu.ar> (Netlify).

## Cómo funciona

- Todo corre **en el navegador**: usa SQLite compilado para la web
  ([sql.js](https://github.com/sql-js/sql.js) 1.8.0, que se descarga desde cdnjs).
  No hay servidor ni base de datos externa.
- Trae cargada una tabla `alumnos` de ejemplo (datos inventados para practicar).
- Acepta la sintaxis de MySQL del material de clase (`INT PRIMARY KEY AUTO_INCREMENT`)
  y la adapta a SQLite.
- Las tablas de cada alumno quedan guardadas **en su propio dispositivo**
  (almacenamiento del navegador). **Reiniciar** las vuelve al estado inicial.

Todo está en un solo archivo: `index.html`.

- Los **ejemplos** están en la lista `EJEMPLOS`.
- Los **datos iniciales**, en `DATOS_INICIALES`.
- Los **botones de atajos**, en `TECLAS`.

## Publicar automáticamente desde GitHub (Netlify)

Para que cada cambio que se una a `main` se publique solo en `sql.eetp468.edu.ar`:

1. En Netlify, entrá al sitio → **Site configuration → Build & deploy → Continuous deployment**
   → **Link repository** y elegí `eetp468ros/practicas-eetp468`.
2. Configurá:
   - **Branch to deploy:** `main`
   - **Base directory:** `laboratorio-sql`
   - **Build command:** dejarlo vacío
   - **Publish directory:** `laboratorio-sql`
3. Guardá. El dominio `sql.eetp468.edu.ar` sigue igual.
