/* =====================================================================
   PROYECTOS DE PRÁCTICAS — EETP N° 468 «Ing. Luis B. Laporte»

   Este es el ÚNICO archivo que hay que editar para sumar un proyecto.
   Copiá la PLANTILLA (al final), pegala dentro de la lista PROYECTOS
   y completá los datos. Guía completa: COMO_SUMAR_TU_PROYECTO.md

   Reglas rápidas:
   - Cada proyecto va entre llaves { } y termina con una coma.
   - Los textos van entre comillas "así".
   - Las listas van entre corchetes [ ], separadas por comas.
   - Las fotos van en la carpeta proyectos/<id-del-proyecto>/
   ===================================================================== */

window.PROYECTOS = [

  {
    id: "datacenter-escolar",
    titulo: "Mi Datacenter Escolar",
    resumen: "Simulador web para armar racks, conectar equipos y calcular la energía de un datacenter.",
    area: "Redes",
    curso: "6°A",
    anio: 2026,
    estado: "Terminado",
    alumnos: [],
    docente: "",
    descripcion: [
      "Página web interactiva para aprender cómo se arma un datacenter: se agregan racks, se colocan equipos (patch panel, switch core, switches ToR, router, servidores, NAS y UPS) y se conectan con cables UTP, fibra óptica o eléctricos.",
      "La versión avanzada suma el consumo de cada equipo y la capacidad de cada UPS: muestra la carga, la autonomía de la batería y qué pasa cuando hay una sobrecarga."
    ],
    materiales: ["HTML, CSS y JavaScript", "Funciona sin internet en cualquier navegador"],
    etiquetas: ["datacenter", "racks", "cableado", "energía", "web"],
    imagen: "proyectos/rack_escuela/portada.jpg",
    galeria: [],
    enlaces: [
      { texto: "Abrir simulador", url: "rack_escuela/index.html" },
      { texto: "Versión avanzada (energía)", url: "rack_escuela/avanzado.html" }
    ],
    codigo: "https://github.com/eetp468ros/practicas-eetp468/tree/HEAD/rack_escuela"
  },

  {
    id: "baston-inteligente",
    titulo: "Bastón inteligente",
    resumen: "Bastón para personas con discapacidad visual que avisa de obstáculos con sonido y vibración.",
    area: "Electrónica",
    curso: "6°A",
    anio: 2026,
    estado: "En desarrollo",
    alumnos: [],
    docente: "",
    descripcion: [
      "Mide la distancia a los obstáculos con un sensor ultrasónico HC-SR04 y avisa de dos maneras: un buzzer que pita más seguido y más agudo cuanto más cerca está el obstáculo, y un micro motor de vibración que vibra más fuerte.",
      "El motor se maneja con un transistor, porque el pin del Arduino no puede darle toda la corriente que necesita."
    ],
    materiales: ["Arduino Nano o Uno", "Sensor ultrasónico HC-SR04", "Buzzer pasivo", "Micro motor de vibración", "Transistor y resistencia de 470 Ω"],
    etiquetas: ["arduino", "ultrasonido", "accesibilidad"],
    imagen: "",
    galeria: [],
    enlaces: [],
    codigo: "https://github.com/eetp468ros/practicas-eetp468/tree/HEAD/baston_inteligente"
  },

  {
    id: "robot-minisumo",
    titulo: "Robot Minisumo",
    resumen: "Robot autónomo que busca al rival con un sensor de distancia y lo empuja fuera del dohyo sin salirse de la línea.",
    area: "Robótica",
    curso: "6°A",
    anio: 2026,
    estado: "En desarrollo",
    alumnos: [],
    docente: "",
    descripcion: [
      "El robot gira buscando al oponente con un sensor ultrasónico y, cuando lo detecta, ataca a máxima velocidad. Dos sensores de línea en la parte de abajo detectan el borde blanco del dohyo para no caerse.",
      "Las velocidades de búsqueda, ataque y giro, y la distancia de detección, se pueden ajustar al principio del programa."
    ],
    materiales: ["Placa Arduino", "Driver de motores", "2 motores con reductora", "Sensor ultrasónico", "2 sensores de línea"],
    etiquetas: ["arduino", "robot", "competencia", "motores"],
    imagen: "",
    galeria: [],
    enlaces: [],
    codigo: "https://github.com/eetp468ros/practicas-eetp468/blob/HEAD/MINISUMO%20v101026"
  },

  {
    id: "sensor-gas-mq5",
    titulo: "Detector de gas MQ-5",
    resumen: "Alarma que detecta pérdidas de gas con un sensor MQ-5 y avisa con luz y sonido.",
    area: "Electrónica",
    curso: "6°A",
    anio: 2026,
    estado: "En desarrollo",
    alumnos: ["Grupo Milena"],
    docente: "",
    descripcion: [
      "Lee el sensor de gas MQ-5 y, si la concentración supera un límite, enciende la alarma con un buzzer y un LED.",
      "Al arrancar hace un pitido corto para comprobar que el buzzer funciona y deja un LED encendido mientras la placa está funcionando."
    ],
    materiales: ["Arduino Uno", "Sensor de gas MQ-5", "Buzzer", "LEDs y resistencias"],
    etiquetas: ["arduino", "seguridad", "gas", "alarma"],
    imagen: "",
    galeria: [],
    enlaces: [],
    codigo: "https://github.com/eetp468ros/practicas-eetp468/tree/HEAD/sensor_gas_mq5"
  },

  {
    id: "sensor-presencia",
    titulo: "Sensor de presencia con radar",
    resumen: "Detecta si hay una persona en movimiento o quieta con un radar LD2420 y lo indica con LEDs y un «sonar».",
    area: "Electrónica",
    curso: "6°A",
    anio: 2026,
    estado: "En desarrollo",
    alumnos: ["Milena Gomez", "Morena Paz"],
    docente: "Martin Luraschi",
    descripcion: [
      "Usa un sensor de radar LD2420 que detecta personas aunque estén quietas. Un LED verde indica que no hay nadie, otro LED indica movimiento y otro indica que la persona está quieta.",
      "Un buzzer funciona como un sonar: pita más rápido y más agudo cuanto más cerca está la persona."
    ],
    materiales: ["Arduino", "Radar de presencia LD2420", "Buzzer pasivo", "3 LEDs y resistencias"],
    etiquetas: ["arduino", "radar", "presencia"],
    imagen: "proyectos/sensor_presencia/portada.jpg",
    galeria: ["proyectos/sensor_presencia/mov.jpg"],
    enlaces: [ { texto: "Video en YouTube", url: "https://youtu.be/iYiTc67nozs?si=CVs59qp4b1SAwq-1" }],
    codigo: "https://github.com/eetp468ros/practicas-eetp468/tree/HEAD/sensor_presencia"
  },

   {
    id: "laboratorio-sql",
    titulo: "Laboratorio SQL",
    resumen: "Mini laboratorio para probar comandos SQL",
    area: "Base de datos",
    curso: "6°A",
    anio: 2026,
    estado: "En desarrollo",
    alumnos: [],
    docente: "Martin Luraschi",
    descripcion: [
      "Mini servidor de bases de datos de la EETP N°468, destinado a las prácticas de los alumnos de la especialidad. Permite crear,  consultar y administrar bases de datos mediante el lenguaje SQL, como apoyo a los espacios de programación y desarrollo de software.",
      "Funciona directamente en el navegador, en el celular o en la compu, sin instalar nada: trae una tabla de alumnos cargada, ejemplos de CREATE TABLE, INSERT, SELECT, UPDATE y DELETE para tocar y probar, y explica los errores en castellano. Las tablas de cada alumno quedan guardadas en su dispositivo."
    ],
    materiales: ["HTML", "CSS", "JavaScript", "SQLite en el navegador (sql.js)"],
    etiquetas: ["SQL", "base de datos", "tablas"],
    imagen: "proyectos/laboratorio-sql/portada.jpg",
    galeria: [],
    enlaces: [{ texto: "Abrir el laboratorio", url: "https://sql.eetp468.edu.ar" }],
    codigo: "https://github.com/eetp468ros/practicas-eetp468/tree/HEAD/laboratorio-sql"
  },

  {
    id: "pruebas-buzzers",
    titulo: "Laboratorio de buzzers",
    resumen: "Programas de prueba para comparar buzzers y encontrar la frecuencia en la que cada uno suena más fuerte.",
    area: "Electrónica",
    curso: "6°A",
    anio: 2026,
    estado: "Terminado",
    alumnos: [],
    docente: "",
    descripcion: [
      "Tres programas cortos para probar buzzers antes de usarlos en un proyecto: una prueba aislada del buzzer pasivo, una prueba de dos módulos MH-FMD (que suenan con nivel BAJO) y un barrido de frecuencias.",
      "Con el barrido y el Monitor Serie se anota en qué frecuencia suena más fuerte cada buzzer."
    ],
    materiales: ["Arduino", "Buzzer pasivo", "Módulos buzzer MH-FMD"],
    etiquetas: ["arduino", "sonido", "pruebas"],
    imagen: "",
    galeria: [],
    enlaces: [],
    codigo: "https://github.com/eetp468ros/practicas-eetp468/tree/HEAD/barrido_buzzers"
  },

   {
     id: "prueba",
     titulo: "Prueba",
     resumen: "Prueba de la prueba",
     area: "Robótica",
     curso: "6°A",
     anio: 2026,
     estado: "En desarrollo",
     alumnos: ["Juan Perez", "Roberto Sanchez", "Lino Rojos", "Pedro Casio", "Rodolfo Nesh"],
     docente: "Martin Luraschi",
     descripcion: [
       "Permite determinar la calidad del proyecto antes de publicarlo en la WEB.",
       "Es un formulario que genera una serie de validaciones."
     ],
     materiales: ["Arduino Uno", "ESP32", "Impresión 3D"],
     etiquetas: ["arduino", "sensores", "domótica"],
     imagen: "proyectos/prueba/portada.jpg",
     galeria: 
["proyectos/prueba/equipo.jpg", "proyectos/prueba/proceso-1.jpg", "proyectos/prueba/proceso-2.jpg"],
     enlaces: [],

codigo: "https://github.com/eetp468ros/practicas-eetp468/tree/HEAD/proyectos/prueba/codigo"
   },

   {
    id: "riego-automatico",
    titulo: "Riego automatico",
    resumen: "Prueba de riego automatico",
    area: "Robótica",
    curso: "6°A",
    anio: 2026,
    estado: "Terminado",
    alumnos: ["Juan Cruz", "Pedro Lima"],
    docente: "MLuraschi",
    descripcion: [
      "Riego en horarios sin gente",
      "Usa un Arduino nano para controlar el riego."
    ],
    materiales: ["Arduino Nano", "Buzzer"],
    etiquetas: ["arduino", "robótica"],
    imagen: "proyectos/riego/portada.jpg",
    galeria: ["proyectos/riego/equipo.jpg", "proyectos/riego/proceso-1.jpg"],
    enlaces: [],
    codigo: ""
  },

     {
    id: "totem-informacion",
    titulo: "Totem Información",
    resumen: "Sistema de información con  pantalla touch.",
    area: "Electrónica",
    curso: "6°A",
    anio: 2026,
    estado: "En desarrollo",
    alumnos: ["Mateo Flores"],
    docente: "Martin Luraschi",
    descripcion: [
      "Suministra información a la gente que concurre a la escuela.",
      "Utiliza una pantalla touch reciclada con un sistema linux optimizado."
    ],
    materiales: ["Pantalla LCD / OLED", "HTML / CSS / JavaScript", "PC"],
    etiquetas: ["Informatica"],
    imagen: "proyectos/totem-informacion/portada.jpg",
    galeria: ["proyectos/totem-informacion/equipo.jpg", "proyectos/totem-informacion/proceso-1.jpg"],
    enlaces: [{ texto: "Abrir la página", url: "https://practicas.eetp468.edu.ar/" }],
    codigo: "https://github.com/eetp468ros/practicas-eetp468/tree/HEAD/proyectos/totem-informacion/codigo"
  },

   {
    id: "fuente-variable",
    titulo: "Fuente variable",
    resumen: "Fuente variable de prueba",
    area: "Electrónica",
    curso: "6°A",
    anio: 2026,
    estado: "En desarrollo",
    alumnos: ["Aldo Puchot", "Santiago Martin"],
    docente: "Martin Luraschi",
    descripcion: [
      "Se utiliza para realizar pruebas con diferentes tensiones.",
      "Utilizamos una fuente ATX reciclada."
    ],
    materiales: ["Fuente ATX"],
    etiquetas: ["energía", "reciclaje"],
    imagen: "proyectos/fuente-variable/portada.jpg",
    galeria: ["proyectos/fuente-variable/equipo.jpg", "proyectos/fuente-variable/proceso-1.jpg"],
    enlaces: [{ texto: "Abrir la página", url: "https://www.atx.com.ar" }],
    codigo: ""
  },

   {
    id: "ticket-soporte-tecnico",
    titulo: "TICKET SOPORTE TECNICO",
    resumen: "Sistema para el seguimento de reparaciones.",
    area: "Otro",
    curso: "6°A",
    anio: 2026,
    estado: "En desarrollo",
    alumnos: ["Santiago Martin"],
    docente: "Martin Luraschi",
    horas: 10,                         // horas de trabajo: las completa el docente al evaluar
    descripcion: [
      "Nos permite controlar las tareas realizadas por los alumnos.",
      "Utiliza una planilla de Google Sheet con scripts."
    ],
    materiales: ["HTML / CSS / JavaScript"],
    etiquetas: ["redes", "base de datos"],
    imagen: "proyectos/ticket-soporte-tecnico/portada.jpg",
    galeria: ["proyectos/ticket-soporte-tecnico/equipo.jpg", "proyectos/ticket-soporte-tecnico/proceso-1.jpg"],
    enlaces: [{ texto: "Abrir la página", url: "https://ticket.eetp468edu.ar" }],
    codigo: ""
  },


  /* ---------- PLANTILLA: copiá desde la { hasta la }, pegala arriba
     (después de la } del último proyecto, poniendo una coma antes) ----------

  {
    id: "nombre-corto-sin-espacios",
    titulo: "Nombre del proyecto",
    resumen: "Una oración que explique qué hace.",
    area: "Electrónica",              // Electrónica, Robótica, Redes, Programación, Base de datos, Automatización, Energía u Otro
    curso: "6° A",
    anio: 2026,
    estado: "En desarrollo",          // "En desarrollo" o "Terminado"
    alumnos: ["Nombre Apellido", "Nombre Apellido"],
    docente: "Nombre del profe",
    horas: 0,                         // horas de trabajo: las completa el docente al evaluar (0 = no se muestra)
    descripcion: [
      "Primer párrafo: qué problema resuelve.",
      "Segundo párrafo: cómo funciona."
    ],
    materiales: ["Arduino Uno", "Sensor ...", "..."],
    etiquetas: ["arduino", "..."],
    imagen: "proyectos/nombre-corto-sin-espacios/portada.jpg",
    galeria: ["proyectos/nombre-corto-sin-espacios/foto1.jpg"],
    enlaces: [
      { texto: "Video en YouTube", url: "https://..." }
    ],
    codigo: "https://github.com/eetp468ros/practicas-eetp468/tree/HEAD/carpeta_del_proyecto"
  }

  ------------------------------------------------------------------------- */

];
