// ════════════════════════════════════════════════════════════════
//  FORMULARIO DE PROYECTOS — practicas.eetp468.edu.ar
//
//  Los alumnos cargan su proyecto en un formulario de Google.
//  Con cada envío, este script arma en Drive una carpeta lista para
//  subir a GitHub (proyectos/<id>/ con las fotos y el código) y la
//  ficha para pegar en proyectos.js, y avisa por mail.
//
//  Instalación (una sola vez): ver las instrucciones que acompañan
//  este archivo. Resumen: ejecutar crearFormulario().
// ════════════════════════════════════════════════════════════════

const CONFIG = {
  tituloFormulario: "Cargá tu proyecto — Prácticas EETP N° 468",
  carpetaBase:      "Proyectos web (formulario)",   // carpeta de Drive donde queda todo
  mailAviso:        "",                             // a quién avisar ("" = a la cuenta que instala)
  confirmarAlAlumno: true,                          // mandar al alumno un mail de «recibimos tu proyecto»
  repo:             "https://github.com/eetp468ros/practicas-eetp468",
  ladoMaximoFoto:   1600,                           // las fotos se achican a este tamaño (px)

  // Opciones de los desplegables y casillas (se pueden editar)
  areas: ["Electrónica", "Robótica", "Redes", "Programación", "Base de datos",
          "Automatización", "Energía", "Otro"],
  estados: ["En desarrollo", "Terminado"],
  materiales: ["Arduino Uno", "Arduino Nano", "ESP32", "Raspberry Pi", "Sensores",
               "Motores / servos", "Pantalla LCD / OLED", "LEDs y resistencias", "Buzzer",
               "Impresión 3D", "HTML / CSS / JavaScript", "Python", "SQL / base de datos"],
  etiquetas: ["arduino", "robótica", "sensores", "automatización", "domótica",
              "seguridad", "energía", "redes", "web", "base de datos", "accesibilidad",
              "reciclaje", "IoT"]
};

// Títulos de las preguntas. Las 4 de archivos se agregan a mano en el
// formulario y tienen que llamarse EXACTAMENTE así.
const P = {
  titulo:         "Nombre del proyecto",
  resumen:        "Resumen",
  area:           "Área",
  curso:          "Curso",
  anio:           "Año",
  estado:         "Estado",
  alumnos:        "Integrantes",
  docente:        "Docente",
  problema:       "¿Qué problema resuelve?",
  funcionamiento: "¿Cómo funciona?",
  materiales:     "Materiales",
  etiquetas:      "Etiquetas",
  video:          "Video",
  autorizacion:   "Consentimiento",
  portada:        "Foto de portada",
  equipo:         "Foto de los integrantes",
  proceso:        "Fotos del proceso de trabajo",
  codigo:         "Código del proyecto"
};


// ──────────────────────────────────────────
//  INSTALACIÓN: crea el formulario, la planilla, la carpeta y el activador
// ──────────────────────────────────────────
function crearFormulario() {
  const props = PropertiesService.getScriptProperties();
  if (props.getProperty("FORM_ID")) {
    const f = FormApp.openById(props.getProperty("FORM_ID"));
    Logger.log("El formulario ya existe. Editalo acá: " + f.getEditUrl());
    return;
  }

  const form = FormApp.create(CONFIG.tituloFormulario)
    .setDescription("Completá los datos de tu proyecto. Con esto se arma su página en " +
                    "practicas.eetp468.edu.ar. El docente la revisa antes de publicarla.")
    .setCollectEmail(true);

  const corto = (titulo, ayuda, obligatoria) =>
    form.addTextItem().setTitle(titulo).setHelpText(ayuda).setRequired(obligatoria);
  const largo = (titulo, ayuda, obligatoria) =>
    form.addParagraphTextItem().setTitle(titulo).setHelpText(ayuda).setRequired(obligatoria);
  const lista = (titulo, opciones) =>
    form.addListItem().setTitle(titulo).setChoiceValues(opciones).setRequired(true);
  const hasta3 = (titulo, opciones, ayuda) =>
    form.addCheckboxItem().setTitle(titulo).setHelpText(ayuda).setChoiceValues(opciones)
      .showOtherOption(true).setRequired(true)
      .setValidation(FormApp.createCheckboxValidation()
        .setHelpText("Elegí hasta 3.").requireSelectAtMost(3).build());

  corto(P.titulo, "Ej.: Riego automático", true);
  corto(P.resumen, "Una oración que explique qué hace (máximo 160 letras).", true)
    .setValidation(FormApp.createTextValidation()
      .setHelpText("Máximo 160 letras.").requireTextLengthLessThanOrEqualTo(160).build());
  lista(P.area, CONFIG.areas);
  corto(P.curso, "Ej.: 6° A", true);
  corto(P.anio, "Ej.: " + new Date().getFullYear(), true)
    .setValidation(FormApp.createTextValidation()
      .setHelpText("Escribí el año con números, ej.: 2026.").requireNumberBetween(2020, 2100).build());
  lista(P.estado, CONFIG.estados);
  largo(P.alumnos, "Un nombre por línea: Nombre Apellido", true);
  corto(P.docente, "Nombre del profe a cargo", true);
  largo(P.problema, "Primer párrafo: qué problema resuelve el proyecto.", true);
  largo(P.funcionamiento, "Segundo párrafo: cómo funciona.", true);
  hasta3(P.materiales, CONFIG.materiales, "Elegí hasta 3. Si falta alguno, usá «Otro».");
  hasta3(P.etiquetas, CONFIG.etiquetas, "Palabras para encontrar el proyecto. Elegí hasta 3.");
  corto(P.video, "Link al video (YouTube, Drive…). Opcional.", false)
    .setValidation(FormApp.createTextValidation()
      .setHelpText("Pegá un link completo, que empiece con https://").requireTextIsUrl().build());
  form.addCheckboxItem().setTitle(P.autorizacion)
    .setHelpText("Las fotos y los nombres se publican en una página web abierta.")
    .setChoiceValues(["Todos los integrantes estamos de acuerdo en que se publiquen nuestros nombres y las fotos " +
                      "del proyecto (incluida la foto del grupo) en practicas.eetp468.edu.ar."])
    .setRequired(true);
  form.addPageBreakItem().setTitle("Fotos y código")
    .setHelpText("Subí las fotos (mejor horizontales) y los archivos del código.");
  // Las preguntas para subir archivos no se pueden crear por código:
  // se agregan a mano en esta sección (ver instrucciones).

  // Planilla de respuestas, carpeta y registro
  const ss = SpreadsheetApp.create(CONFIG.tituloFormulario + " (respuestas)");
  form.setDestination(FormApp.DestinationType.SPREADSHEET, ss.getId());
  const registro = ss.insertSheet("Procesados");
  registro.appendRow(["Fecha", "ID", "Proyecto", "Mail del alumno", "Carpeta para subir", "Ficha para proyectos.js", "Avisos"]);
  registro.setFrozenRows(1);
  registro.getRange("1:1").setFontWeight("bold");

  const carpeta = DriveApp.createFolder(CONFIG.carpetaBase);
  DriveApp.getFileById(form.getId()).moveTo(carpeta);
  DriveApp.getFileById(ss.getId()).moveTo(carpeta);

  props.setProperties({ FORM_ID: form.getId(), PLANILLA_ID: ss.getId(), CARPETA_ID: carpeta.getId() });
  ScriptApp.newTrigger("procesarEnvio").forForm(form).onFormSubmit().create();

  Logger.log("✅ Formulario creado. Editalo acá para agregar las preguntas de archivos:\n" +
             form.getEditUrl() + "\n\nLink para los alumnos:\n" + form.getPublishedUrl());
}


// ──────────────────────────────────────────
//  CON CADA ENVÍO DEL FORMULARIO
// ──────────────────────────────────────────
function procesarEnvio(e) {
  const props    = PropertiesService.getScriptProperties();
  const base     = DriveApp.getFolderById(props.getProperty("CARPETA_ID"));
  const registro = SpreadsheetApp.openById(props.getProperty("PLANILLA_ID")).getSheetByName("Procesados");
  const r        = respuestas(e.response);
  const titulo   = String(r[P.titulo] || "").trim();
  const mailAlumno = String(e.response.getRespondentEmail() || "").trim();

  try {
    const id      = idUnico(aId(titulo), base);
    const raiz    = base.createFolder(id);           // se sube completa a la carpeta proyectos/ del repo
    const ruta    = `proyectos/${id}`;
    const avisos  = [];

    // Fotos con nombres fijos
    let imagen = "";
    const portada = archivos(r[P.portada]);
    if (portada.length) imagen = `${ruta}/` + guardarImagen(portada[0], raiz, "portada", avisos);
    else avisos.push("No subieron foto de portada: la página va a mostrar el dibujo del área.");

    const galeria = [];
    archivos(r[P.equipo]).slice(0, 1)
      .forEach(f => galeria.push(`${ruta}/` + guardarImagen(f, raiz, "equipo", avisos)));
    archivos(r[P.proceso])
      .forEach((f, i) => galeria.push(`${ruta}/` + guardarImagen(f, raiz, `proceso-${i + 1}`, avisos)));

    // Código en la subcarpeta codigo/
    let codigo = "";
    const archivosCodigo = archivos(r[P.codigo]);
    if (archivosCodigo.length) {
      const carpetaCodigo = raiz.createFolder("codigo");
      archivosCodigo.forEach(fid => {
        const original = DriveApp.getFileById(fid);
        original.makeCopy(nombreSinAutor(original.getName()), carpetaCodigo);
      });
      codigo = `${CONFIG.repo}/tree/HEAD/${ruta}/codigo`;
    }

    const video = String(r[P.video] || "").trim();
    const ficha = armarFicha({
      id,
      titulo,
      resumen:     String(r[P.resumen] || "").trim(),
      area:        String(r[P.area] || "Otro"),
      curso:       String(r[P.curso] || "").trim(),
      anio:        Number(r[P.anio]) || new Date().getFullYear(),
      estado:      String(r[P.estado] || "En desarrollo"),
      alumnos:     String(r[P.alumnos] || "").split(/\r?\n|,/).map(s => s.trim()).filter(Boolean),
      docente:     String(r[P.docente] || "").trim(),
      descripcion: [r[P.problema], r[P.funcionamiento]].map(s => String(s || "").trim()).filter(Boolean),
      materiales:  lista(r[P.materiales]),
      etiquetas:   lista(r[P.etiquetas]),
      imagen,
      galeria,
      enlaces:     video ? [{ texto: "Video", url: video }] : [],
      codigo
    });

    base.createFile(`${id} - ficha para proyectos.js.txt`, ficha);
    registro.appendRow([new Date(), id, titulo, mailAlumno, raiz.getUrl(), ficha, avisos.join("\n")]);
    avisarPorMail(`📥 Nuevo proyecto: ${titulo} (${id})`,
      `Llegó un proyecto nuevo desde el formulario${mailAlumno ? ", enviado por " + mailAlumno : ""}.\n\n` +
      `Carpeta lista para subir a GitHub (dentro de «proyectos/»):\n${raiz.getUrl()}\n\n` +
      (avisos.length ? `⚠️ Para revisar:\n- ${avisos.join("\n- ")}\n\n` : "") +
      `Ficha para pegar en proyectos.js (después del último proyecto):\n\n${ficha}\n`);

    if (CONFIG.confirmarAlAlumno && mailAlumno) {
      MailApp.sendEmail(mailAlumno, `Recibimos tu proyecto: ${titulo}`,
        `¡Hola!\n\nRecibimos el proyecto «${titulo}». El docente lo va a revisar y, cuando esté ` +
        `aprobado, va a aparecer en https://practicas.eetp468.edu.ar\n\n` +
        `Si necesitás corregir algo, avisale a tu docente.\n\nPrácticas EETP N° 468`);
    }
  } catch (err) {
    registro.appendRow([new Date(), "ERROR", titulo, mailAlumno, "", "", err.message]);
    avisarPorMail(`⚠️ Error al procesar el proyecto «${titulo}»`,
      `No se pudo procesar el envío del formulario${mailAlumno ? " de " + mailAlumno : ""}.\n\nDetalle: ${err.message}\n\n` +
      `Las respuestas están en la planilla del formulario.`);
  }
}


// ──────────────────────────────────────────
//  FUNCIONES DE AYUDA
// ──────────────────────────────────────────

// Respuestas del formulario por título de pregunta
function respuestas(response) {
  const r = {};
  response.getItemResponses().forEach(ir => { r[ir.getItem().getTitle()] = ir.getResponse(); });
  return r;
}

function archivos(valor) {
  if (!valor) return [];
  return (Array.isArray(valor) ? valor : [valor]).filter(Boolean);
}

function lista(valor) {
  return archivos(valor).map(v => String(v).trim()).filter(Boolean);
}

// «Riego Automático!» → «riego-automatico»
function aId(titulo) {
  const id = String(titulo).normalize("NFD").replace(/[̀-ͯ]/g, "")
    .toLowerCase().replace(/[^a-z0-9]+/g, "-").replace(/^-+|-+$/g, "").slice(0, 40).replace(/-+$/, "");
  return id || "proyecto";
}

// Si ya existe una carpeta con ese id, agrega -2, -3…
function idUnico(id, carpeta) {
  let candidato = id, n = 2;
  while (carpeta.getFoldersByName(candidato).hasNext()) candidato = `${id}-${n++}`;
  return candidato;
}

// Google Forms agrega « - Nombre de quien subió» al archivo: se lo saca
function nombreSinAutor(nombre) {
  const limpio = String(nombre).replace(/ - [^.]*?(\.[^.]+)?$/, "$1");
  return limpio.replace(/\s+/g, "_");
}

// Copia la foto achicada (en JPG) o, si no se puede, la original
function guardarImagen(fileId, carpeta, nombre, avisos) {
  const original = DriveApp.getFileById(fileId);
  const chica = fotoAchicada(fileId);
  if (chica) {
    carpeta.createFile(chica.setName(`${nombre}.jpg`));
    return `${nombre}.jpg`;
  }
  const ext = (String(original.getName()).match(/\.([a-z0-9]+)$/i) || [, "jpg"])[1].toLowerCase();
  if (!["jpg", "jpeg", "png", "webp", "gif"].includes(ext)) {
    avisos.push(`La foto «${nombre}» está en formato .${ext}, que la web no muestra: convertila a JPG.`);
  } else if (original.getSize() > 1024 * 1024) {
    avisos.push(`La foto «${nombre}» pesa ${(original.getSize() / 1048576).toFixed(1)} MB: conviene achicarla.`);
  }
  original.makeCopy(`${nombre}.${ext}`, carpeta);
  return `${nombre}.${ext}`;
}

// Usa la miniatura de Drive en tamaño grande (requiere el servicio avanzado «Drive API»)
function fotoAchicada(fileId) {
  try {
    if (typeof Drive === "undefined") return null;
    const link = Drive.Files.get(fileId, { fields: "thumbnailLink" }).thumbnailLink;
    if (!link) return null;
    const resp = UrlFetchApp.fetch(link.replace(/=s\d+$/, "=s" + CONFIG.ladoMaximoFoto), {
      headers: { Authorization: "Bearer " + ScriptApp.getOAuthToken() },
      muteHttpExceptions: true
    });
    if (resp.getResponseCode() !== 200) return null;
    return resp.getBlob().getAs("image/jpeg");
  } catch (err) {
    return null;
  }
}

// Ficha con el mismo formato que usa proyectos.js
function armarFicha(p) {
  const s     = v => JSON.stringify(v);
  const lista = a => "[" + a.map(s).join(", ") + "]";
  return [
    "  {",
    `    id: ${s(p.id)},`,
    `    titulo: ${s(p.titulo)},`,
    `    resumen: ${s(p.resumen)},`,
    `    area: ${s(p.area)},`,
    `    curso: ${s(p.curso)},`,
    `    anio: ${p.anio},`,
    `    estado: ${s(p.estado)},`,
    `    alumnos: ${lista(p.alumnos)},`,
    `    docente: ${s(p.docente)},`,
    "    descripcion: [",
    p.descripcion.map(d => "      " + s(d)).join(",\n"),
    "    ],",
    `    materiales: ${lista(p.materiales)},`,
    `    etiquetas: ${lista(p.etiquetas)},`,
    `    imagen: ${s(p.imagen)},`,
    `    galeria: ${lista(p.galeria)},`,
    `    enlaces: [${p.enlaces.map(e => `{ texto: ${s(e.texto)}, url: ${s(e.url)} }`).join(", ")}],`,
    `    codigo: ${s(p.codigo)}`,
    "  },"
  ].join("\n");
}

function avisarPorMail(asunto, cuerpo) {
  const destino = CONFIG.mailAviso || Session.getEffectiveUser().getEmail();
  if (destino) MailApp.sendEmail(destino, asunto, cuerpo);
}
