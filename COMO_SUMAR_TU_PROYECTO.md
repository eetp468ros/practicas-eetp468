# Cómo sumar tu proyecto a la página

> **Alumnos:** la forma más fácil es el formulario. Entrá a
> <https://practicas.eetp468.edu.ar/#sumar> y tocá **«Cargar mi proyecto»**.
> El docente revisa el envío y lo publica.
>
> Esta guía explica cómo cargar un proyecto **a mano** en GitHub (para docentes).

La página de proyectos (`index.html`) lee todos los proyectos de **un solo archivo**: `proyectos.js`.
Para que tu proyecto aparezca, solo tenés que agregar tu ficha ahí.

## 1. Subí el código

Creá una carpeta con un nombre corto, sin espacios ni acentos (por ejemplo `riego_automatico/`),
con tu programa `.ino` y, si podés, un `README.md` que explique las conexiones.

## 2. Agregá las fotos

Guardalas en `proyectos/<id-de-tu-proyecto>/`, por ejemplo:

```
proyectos/riego-automatico/portada.jpg
proyectos/riego-automatico/foto1.jpg
```

- La **portada** se ve mejor horizontal (por ejemplo 1200 × 700 px).
- Achicá las fotos antes de subirlas (menos de 500 KB cada una).
- Si no tenés foto, dejá `imagen: ""` y la página muestra un dibujo según el área.

## 3. Completá tu ficha en `proyectos.js`

Copiá la plantilla que está al final de `proyectos.js` (también se puede copiar desde la página,
en «¿Cómo sumo mi proyecto?») y pegala dentro de la lista, después del último proyecto.

| Campo | Qué poner |
|---|---|
| `id` | Nombre corto sin espacios ni acentos, con guiones: `riego-automatico`. Tiene que ser único. |
| `titulo` | Nombre del proyecto. |
| `resumen` | Una sola oración que diga qué hace. Aparece en la tarjeta. |
| `area` | `Electrónica`, `Robótica`, `Redes`, `Programación`, `Base de datos`, `Automatización`, `Energía` u `Otro`. |
| `curso` / `anio` | Por ejemplo `"6° A"` y `2026`. |
| `estado` | `"En desarrollo"` o `"Terminado"`. |
| `alumnos` | Lista con los nombres del grupo: `["Ana Pérez", "Juan Gómez"]`. |
| `docente` | Nombre del profe a cargo. |
| `horas` | Horas de trabajo del proyecto. **Las completa el docente al evaluarlo**; con `0` no se muestran. |
| `descripcion` | Uno o más párrafos: qué problema resuelve y cómo funciona. |
| `materiales` | Componentes y tecnologías usadas. |
| `etiquetas` | Palabras para buscarlo: `["arduino", "riego", "humedad"]`. |
| `imagen` / `galeria` | Rutas de las fotos del paso 2. |
| `enlaces` | Videos, presentaciones, etc.: `[{ texto: "Video", url: "https://..." }]`. |
| `codigo` | Link a la carpeta del código en GitHub. |

### Errores comunes

- **Falta una coma** entre un proyecto y el siguiente (`},` antes de la nueva `{`).
- **Comillas**: los textos van entre comillas dobles `"..."`. Si tu texto necesita comillas, usá `«...»`.
- **La página quedó en blanco**: casi siempre es una coma o una llave de más o de menos.
  Abrí la página, apretá F12 y mirá la pestaña *Console*: dice en qué línea está el error.

## 4. Revisión

Pedile al profe que revise tus cambios (un *pull request* en GitHub). Cuando se aprueban,
tu proyecto aparece en la página.

## Probar en tu computadora

Abrí `index.html` con doble clic. Para ver un proyecto directamente, agregá al final de la
dirección `#proyecto=` y el `id`, por ejemplo `index.html#proyecto=riego-automatico`.
Ese mismo link sirve para compartir tu proyecto.
