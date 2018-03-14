
 _______  _______  ______   _______    ______   _______ _________ _______ _________ _______  _______  _______ 
(  ____ \(  ___  )(  __  \ (  ____ \  (  __  \ (  ____ )\__   __/(  ____ \\__   __/(  ____ \(  ____ )(  ____ \
| (    \/| (   ) || (  \  )| (    \/  | (  \  )| (    )|   ) (   | (    \/   ) (   | (    \/| (    )|| (    \/
| |      | |   | || |   ) || (__      | |   ) || (____)|   | |   | (__       | |   | (__    | (____)|| (_____ 
| |      | |   | || |   | ||  __)     | |   | ||     __)   | |   |  __)      | |   |  __)   |     __)(_____  )
| |      | |   | || |   ) || (        | |   ) || (\ (      | |   | (         | |   | (      | (\ (         ) |
| (____/\| (___) || (__/  )| (____/\  | (__/  )| ) \ \_____) (___| )         | |   | (____/\| ) \ \__/\____) |
(_______/(_______)(______/ (_______/  (______/ |/   \__/\_______/|/          )_(   (_______/|/   \__/\_______)




Al añadir un proyecto nuevo recuerda añadir la página de propiedades ProyectosSDL.props al nuevo proyecto:
Menú VER -> administrador de propiedades -> Agregar hoja de propiedades existente -> ProyectosSDL.props > Guardar

Las librerias que se utilizan en esta solución (en el directorio bin) son las librerias de los directorios lib\x86 de SDL-2.0.4 y SDL_image-2.0.1.
Si quieres usar las librerias de lib\x64 copialas de SDL-2.0.4 y SDL_image-2.0.1 al directorio bin de la solución.
Abre el archivo ProyectosSDL.props y modifica la línea correspondiente a LibraryPath.

Si quieres añadir una nueva libreria, copia su directorio en la solución y los bin de la libreria en el directorio bin de la solución.
Y añade los nuevos elementos al archivo ProyectosSDL.props en las lineas: IncludePath, LibraryPath y AdditionalDependencies.
También puedes crear otras páginas de propiedades.
