#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void busqueda(const char *name, int indent)
{

    //Se crean las estructuras que serviran para
    //leer los directorios.
    DIR *carpeta_genero;
    struct dirent *subcarpeta;

    //Se crean las variables que almacenaran 
    //los datos respecto a los jugadores
    int menor_total = 0;
    int entre_total = 0;
    int mayor_total = 0;
    int menor = 0;
    int entre = 0;
    int mayor = 0;

    //Se abre el directorio actual y se 
    //verifica que se lee correctamente
    if (!(carpeta_genero = opendir(name)))
        return;

    //Mientras carpeta_genero no sea NULL
    //(Se tiene abierto un directorio)
    while ((subcarpeta = readdir(carpeta_genero)) != NULL)
    {
        //Se verifica si la subcarpeta leida es un directorio
        if (subcarpeta->d_type == DT_DIR) 
        {
            char path[1024];
            //Se verifica que la subcarpeta no sea ni la carpeta actual
            //ni la carpeta anterior
            if (strcmp(subcarpeta->d_name, ".") == 0 || strcmp(subcarpeta->d_name, "..") == 0)
                continue;
            //Se almacena la direccion de la subcarpeta
            //y se imprime lo referente al genero que es 
            //la subcarpeta    
            snprintf(path, sizeof(path), "%s/%s", name, subcarpeta->d_name);
            printf("Cantidad de juegos de %s:\n", subcarpeta->d_name);

            DIR *carpeta_ventas;
            struct dirent *ventas;

            //Se verifica que carpeta_ventas se haya leido
            // correctamente
            if (!(carpeta_ventas = opendir(path)))
                return;
            
            //Mientras exista un directorio para abrir se mantiene el bucle
            while ((ventas = readdir(carpeta_ventas)) != NULL) {    
                //Se verifica que el directorio abierto no sea ni el actual
                //ni el anterior (padre)
                if (!strcmp(ventas->d_name, ".") == 0 && !strcmp(ventas->d_name, "..") == 0)
                {
                    //Se generan arreglos que serviran para el path y los contadores
                    char carpeta_menor[1024];
                    char carpeta_entre[1024];
                    char carpeta_mayor[1024];                    
                    menor = 0;
                    entre = 0;
                    mayor = 0;
                    //Se copia el path anterior (que indica el genero)
                    //en cada arreglo
                    strcpy(carpeta_menor, path);
                    strcpy(carpeta_entre, path);
                    strcpy(carpeta_mayor, path);
                    
                    //Se le concatena la ultima direccion
                    //para poder abrir las carpetas que contienen los juegos
                    strcat(carpeta_menor, "/Menor_a_40000");
                    strcat(carpeta_entre, "/Entre_40000_y_80000");
                    strcat(carpeta_mayor, "/Mayor_a_80000");

                    DIR *carpeta_menor_dir;
                    DIR *carpeta_entre_dir;
                    DIR *carpeta_mayor_dir;
                    struct dirent *juego;

                    //Se verifica que se haya abierto la carpeta menor
                    if (!(carpeta_menor_dir = opendir(carpeta_menor)))
                        continue;
                    else {
                        //Se ejecuta el bucle que cuenta los juegos con menores jugadores
                        while ((juego = readdir(carpeta_menor_dir)) != NULL) {
                            if (strcmp(juego->d_name, ".") == 0 || strcmp(juego->d_name, "..") == 0)
                                continue;    
                            menor++;
                        } closedir(carpeta_menor_dir);
                    } free(juego);
                    
                    //Se verifica que se haya abierto la carpeta entre
                    if (!(carpeta_entre_dir = opendir(carpeta_entre)))
                        continue;
                    else {
                        //Se ejecuta el bucle que cuenta los juegos con jugadores entre 40000 y 80000
                        while ((juego = readdir(carpeta_entre_dir)) != NULL) {
                            if (strcmp(juego->d_name, ".") == 0 || strcmp(juego->d_name, "..") == 0)
                                continue;   
                            entre++;
                        } closedir(carpeta_entre_dir);
                    } free(juego);
                    
                    //Se verifica que se haya abierto la carpeta mayor
                    if (!(carpeta_mayor_dir = opendir(carpeta_mayor)))
                        continue;
                    else {
                        //Se ejecuta el bucle que cuenta los juegos con mas jugadores
                        while ((juego = readdir(carpeta_mayor_dir)) != NULL) {
                            if (strcmp(juego->d_name, ".") == 0 || strcmp(juego->d_name, "..") == 0)
                                continue;    
                            mayor++;
                        } closedir(carpeta_mayor_dir);
                    } free(juego);

                    //Se muestran los resultados obtenidos por genero
                    if (strcmp(ventas->d_name, "Menor_a_40000") == 0) {
                        printf("    Juegos con una cantidad de jugadores menor a 40000: %d\n", menor);
                    }
                    if (strcmp(ventas->d_name, "Entre_40000_y_80000") == 0) {
                        printf("    Juegos con una cantidad de jugadores entre 40000 y 80000: %d\n", entre);
                    }
                    if (strcmp(ventas->d_name, "Mayor_a_80000") == 0) {
                        printf("    Juegos con una cantidad de jugadores mayor a 80000: %d\n", mayor);
                    }
                }
            }
            //Se aumenta el contador de cada cantidad de jugadores.
            menor_total += menor;
            mayor_total += mayor;
            entre_total += entre;
            closedir(carpeta_ventas);
        }
    }
    //Se cierra la carpeta principal
    closedir(carpeta_genero);

    //Se muestran los totales obtenidos anteriormente.
    printf("Del total de juegos:\n");
    printf("    Existen %d con una mayor cantidad de jugadores menor a 40000\n", menor_total);
    printf("    Existen %d con una mayor cantidad de jugadores entre 40000 y 80000\n", entre_total);
    printf("    Existen %d con una mayor cantidad de jugadores mayor a 80000\n", mayor_total);
}

int main(void) {
    busqueda(".", 0);
    return 0;
}