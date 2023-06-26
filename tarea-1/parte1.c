#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main() 
{
    int cantidad_de_juegos = 0;     // Cantidad de juegos, sin contar . y ..
    DIR *carpeta;                   // Carpeta que contiene los juegos
    struct dirent *juego_leido;     // Juego leido actual
    char* orden_por_cantidad[] = {  "Menor_a_40000",
                                    "Entre_40000_y_80000",
                                    "Mayor_a_80000"};

    int numeros[] = {40000, 80000}; // Rango dentro del cual entran las categorias
    char orden[100];

    // Los dos inputs validos al ordenar los juegos
    char opcion_1[] = "cantidad actual\n";
    char opcion_2[] = "mayor cantidad\n";

    printf("De que manera desea ordenar los juegos?\n");
    fgets(orden, sizeof(orden), stdin);

    // Corrobora cual de las dos opciones eligio el 
    // usuario a traves de una comparacion de strings
    int com_1 = strcmp(orden, opcion_1);
    int com_2 = strcmp(orden, opcion_2);

    // Intenta leer la carpeta que contiene los juegos
    // Si falla, sale del programa
    if ((carpeta = opendir("Archivos")) == NULL)
        perror("No se pudo leer la carpeta\n");

    /*
    Si es posible leer la carpeta, recorrera sus contenidos
    y por cada juego que halle creara una carpeta con el 
    nombre de su genero que en su interior contiene los 
    ordenes por cantidad
    */
    else {
        while ((juego_leido = readdir(carpeta)) != NULL) 
        {
            char archivo_carpeta[] = "Archivos/";           // Lee en la carpeta Archivos
            strcat(archivo_carpeta, juego_leido->d_name);   // Le agrega el nombre del juego
            
            char* data = 0;                                 // Donde se guardara el archivo en el buffer
            int largo;                                      // Cantidad de caracteres en el archivo

            FILE *fp = fopen(archivo_carpeta, "r");         // Lee

            if (fp) {                                       // Obtiene el tamano del archivo
                fseek(fp, 0, SEEK_END);
                largo = ftell(fp);
                fseek(fp, 0, SEEK_SET);
                data = malloc(largo);
                if (data) {
                    fread(data, 1, largo, fp);
                }
            }
            rewind(fp);

            fp = fopen(archivo_carpeta, "r");

            // Lee los contenidos del directorio, siempre y cuando no sean . o ..
            // . y .. no son archivos, solo son parte del Path del directorio
            if (strcmp(juego_leido->d_name, ".") != 0 && strcmp(juego_leido->d_name, "..") != 0){
                char* jugadores_actuales    = malloc(largo);
                char* cantidad_jugadores    = malloc(largo);
                char* genero                = malloc(largo);
                char c;

                fscanf(fp, "%s\n%s\n%s", 
                    jugadores_actuales, 
                    cantidad_jugadores, 
                    genero);
                
                cantidad_de_juegos++;

                // Tras leer el archivo, crea una carpeta con el nombre del genero
                mkdir(genero, 0777);

                // Crea una subcarpeta por cada tipo de orden de cantidad
                for (int i = 0; i < 3; i++) {
                    char* path = malloc(strlen(genero) + strlen(orden_por_cantidad[i]) + 2);
                    sprintf(path, "%s/%s", genero, orden_por_cantidad[i]);
                    mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | O_CREAT | O_EXCL);
                    free(path);
                }

                // Transforma las cantidades leidas en enteros
                int n_jugadores_actuales    = atoi(jugadores_actuales);
                int n_cantidad_jugadores    = atoi(cantidad_jugadores);
                
                // Ordena por cantidad actual de jugadores
                if (com_1 == 0)
                {
                    if (n_jugadores_actuales < numeros[0]){
                        char* old_path = malloc(strlen("Archivos") + strlen(juego_leido->d_name) + 2);
                        sprintf(old_path, "%s/%s", "Archivos", juego_leido->d_name);
                        char* new_path = malloc(strlen(genero) + strlen(orden_por_cantidad[0]) + strlen(juego_leido->d_name) + 2);
                        sprintf(new_path, "%s/%s/%s", genero , orden_por_cantidad[0], juego_leido->d_name);
                        rename(old_path, new_path);
                        free(old_path);
                        free(new_path);
                    }
                    else if ((n_jugadores_actuales >= numeros[0]) || (n_jugadores_actuales <= numeros[1])){
                        char* old_path = malloc(strlen("Archivos") + strlen(juego_leido->d_name) + 2);
                        sprintf(old_path, "%s/%s", "Archivos", juego_leido->d_name);
                        char* new_path = malloc(strlen(genero) + strlen(orden_por_cantidad[1]) + strlen(juego_leido->d_name) + 2);
                        sprintf(new_path, "%s/%s/%s", genero , orden_por_cantidad[1], juego_leido->d_name);
                        rename(old_path, new_path);
                        free(old_path);
                        free(new_path);
                    }
                    else if (n_jugadores_actuales > numeros[1]){
                        char* old_path = malloc(strlen("Archivos") + strlen(juego_leido->d_name) + 2);
                        sprintf(old_path, "%s/%s", "Archivos", juego_leido->d_name);
                        char* new_path = malloc(strlen(genero) + strlen(orden_por_cantidad[2]) + strlen(juego_leido->d_name) + 2);
                        sprintf(new_path, "%s/%s/%s", genero , orden_por_cantidad[2], juego_leido->d_name);
                        rename(old_path, new_path);
                        free(old_path);
                        free(new_path);
                    }else{
                        printf("Error al mover los archivos");
                        return 1;
                    }
                }
                
                // Ordena por cantidad maxima de jugadores
                else if (com_2 == 0){
                    if (n_cantidad_jugadores < numeros[0]){
                        char* old_path = malloc(strlen("Archivos") + strlen(juego_leido->d_name) + 2);
                        sprintf(old_path, "%s/%s", "Archivos", juego_leido->d_name);
                        char* new_path = malloc(strlen(genero) + strlen(orden_por_cantidad[0]) + strlen(juego_leido->d_name) + 2);
                        sprintf(new_path, "%s/%s/%s", genero , orden_por_cantidad[0], juego_leido->d_name);
                        rename(old_path, new_path);
                        free(old_path);
                        free(new_path);
                    }
                    else if ((n_cantidad_jugadores >= numeros[0]) || (n_cantidad_jugadores <= numeros[1])){
                        char* old_path = malloc(strlen("Archivos") + strlen(juego_leido->d_name) + 2);
                        sprintf(old_path, "%s/%s", "Archivos", juego_leido->d_name);
                        char* new_path = malloc(strlen(genero) + strlen(orden_por_cantidad[1]) + strlen(juego_leido->d_name) + 2);
                        sprintf(new_path, "%s/%s/%s", genero , orden_por_cantidad[1], juego_leido->d_name);
                        rename(old_path, new_path);
                        free(old_path);
                        free(new_path);
                    }
                    else if (n_cantidad_jugadores > numeros[1]){
                        char* old_path = malloc(strlen("Archivos") + strlen(juego_leido->d_name) + 2);
                        sprintf(old_path, "%s/%s", "Archivos", juego_leido->d_name);
                        char* new_path = malloc(strlen(genero) + strlen(orden_por_cantidad[2]) + strlen(juego_leido->d_name) + 2);
                        sprintf(new_path, "%s/%s/%s", genero , orden_por_cantidad[2], juego_leido->d_name);
                        rename(old_path, new_path);
                        free(old_path);
                        free(new_path);
                    }else{
                        printf("Error al mover los archivos");
                        return 1;
                    }
                }           
            }
            fclose(fp);
        }
    }
    closedir(carpeta);
    rmdir("Archivos");

    return 0;
}