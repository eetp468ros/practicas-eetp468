# Publicar la página en practicas.eetp468.edu.ar

La página se publica gratis con **GitHub Pages**. Son tres partes: unir los cambios,
activar Pages en GitHub y pedir un registro DNS a quien administra el dominio de la escuela.

## 1. Unir los cambios en la rama principal

Todo tiene que estar en la rama principal del repositorio: `main`.
Ver la explicación sobre ramas y *pull requests* que acompaña este cambio.

## 2. Activar GitHub Pages

1. Entrá a <https://github.com/eetp468ros/practicas-eetp468> → **Settings** → **Pages**.
2. En **Build and deployment** → **Source**, elegí **Deploy from a branch**.
3. En **Branch**, elegí la rama principal y la carpeta **/ (root)**. Guardá con **Save**.
4. En **Custom domain** tiene que aparecer `practicas.eetp468.edu.ar`
   (lo toma del archivo `CNAME`). Si no aparece, escribilo y guardá.

> Con una cuenta gratuita de GitHub, el repositorio tiene que ser **público** para usar Pages.

## 3. Registro DNS (lo hace quien administra eetp468.edu.ar)

Hay que agregar en la zona DNS de `eetp468.edu.ar` este registro:

| Tipo  | Nombre     | Valor                  | TTL      |
|-------|------------|------------------------|----------|
| CNAME | `practicas` | `eetp468ros.github.io.` | 3600 (o el que venga por defecto) |

- No hay que tocar ningún otro registro: el sitio actual de la escuela sigue igual.
- El cambio puede tardar desde unos minutos hasta 24 horas en verse.

## 4. Activar HTTPS

Cuando el DNS ya funciona, volvé a **Settings → Pages**: GitHub muestra
«DNS check successful». Marcá **Enforce HTTPS** (puede tardar un rato en habilitarse).

Listo: la página queda en <https://practicas.eetp468.edu.ar> y se actualiza sola
cada vez que se suma un proyecto a la rama principal.

## Archivos que no hay que borrar

- `CNAME`: le dice a GitHub qué dirección usar.
- `.nojekyll`: hace que GitHub publique los archivos tal cual, sin procesarlos.
- `index.html`, `proyectos.js` y la carpeta `assets/`: la página en sí.
