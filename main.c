#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int opcion = 0, opcion2 = 1, edad, genero, servicio, consultorio, id,meses=-1,dias=-1;
    char nombre[100];
    char descripcion[200];
    char direccion[100];
    char linea[400];

    FILE *archivoId = fopen("cuentaId.txt", "r");
    if (archivoId == NULL) {
        archivoId = fopen("cuentaId.txt", "w");
        if (archivoId == NULL) {
            printf("Error al abrir el archivo de Id\n");
            return 1;
        }
        fprintf(archivoId, "%d", 1);
        fclose(archivoId);
    }

    while (opcion != 5) {
        do {
            printf("Ingrese una opcion\n");
            printf("1. Alta de paciente\n");
            printf("2. Busqueda o edicion de paciente\n");
            printf("3. Listado de pacientes\n");
            printf("4. Baja de Paciente\n");
            printf("5. Salir\n");
            scanf("%d", &opcion);
        } while (opcion > 5 || opcion < 1);

        switch (opcion) {
            case 1:
                archivoId = fopen("cuentaId.txt", "r+");
                if (archivoId == NULL) {
                    printf("Error al abrir el archivo de Id\n");
                    return 1;
                }
                fscanf(archivoId, "%d", &id);

                FILE *archivo = fopen("pacientes.txt", "a+");
                if (archivo == NULL) {
                    printf("Error al abrir el archivo de pacientes\n");
                    fclose(archivoId);
                    return 1;
                }

                while (opcion2 != 2) {
                    printf("Ingrese el nombre: ");
                    while (getchar() != '\n');
                    fgets(nombre, sizeof(nombre), stdin);
                    nombre[strcspn(nombre, "\n")] = '\0';

                    printf("Ingrese el tipo de servicio (1. Consulta Externa 2. Emergencias): ");
                    scanf("%d", &servicio);

                    printf("Ingrese su direccion: ");
                    while (getchar() != '\n');
                    fgets(direccion, sizeof(direccion), stdin);
                    direccion[strcspn(direccion, "\n")] = '\0';

                    do {
                        printf("Ingrese su edad: ");
                        scanf("%d", &edad);
                        if(edad<0) {
                            printf("Edad incorrecta");
                        }
                    }while(edad<0);

                    if(edad==0) {
                        do {
                            printf("Ingrese los meses");
                            scanf("%d",&meses);

                            if(meses<0) {
                                printf("Dato incorrecto");
                            }

                        }while(meses<0);
                    }

                    if(meses==0) {
                        do {
                            printf("Ingrese los dias de nacido");
                            scanf("%d",&dias);
                        }while(dias<0);

                    }




                    printf("Ingrese su genero (1. Hombre 2. Mujer): ");
                    scanf("%d", &genero);

                    printf("Ingrese la descripcion de sus sintomas: ");
                    while (getchar() != '\n');
                    fgets(descripcion, sizeof(descripcion), stdin);
                    descripcion[strcspn(descripcion, "\n")] = '\0';

                    printf("Ingrese el numero del consultorio del doctor que le atendera: ");
                    scanf("%d", &consultorio);

                    fprintf(archivo, "%d|%s|%d|%s|%d|%d|%d|%d|%s|%d\n", id, nombre, servicio, direccion, edad,meses,dias, genero, descripcion, consultorio);


                    printf("\nSu numero de folio es: %d",id);
                    printf("Quiere agregar otro registro? (1: SI 2: NO): ");
                    scanf("%d", &opcion2);
                    id++;
                }

                fseek(archivoId, 0, SEEK_SET);
                fprintf(archivoId, "%d", id);

                fclose(archivo);
                fclose(archivoId);
                break;

            case 2:
                printf("Ingrese el ID del paciente a buscar: ");
            scanf("%d", &id);

            archivo = fopen("pacientes.txt", "r");
            if (archivo == NULL) {
                printf("Error al abrir el archivo de pacientes\n");
                break;
            }

            int encontrado = 0;
            while (fgets(linea, sizeof(linea), archivo) != NULL) {
                int idActual;
                sscanf(linea, "%d|", &idActual);

                if (idActual == id) {
                    encontrado = 1;
                    sscanf(linea, "%d|%99[^|]|%d|%99[^|]|%d|%d|%d|%d|%199[^|]|%d",
                           &id, nombre, &servicio, direccion, &edad, &meses, &dias, &genero, descripcion, &consultorio);

                    printf("ID: %d\n", id);
                    printf("Nombre: %s\n", nombre);
                    printf("Servicio: %d\n", servicio);
                    printf("Dirección: %s\n", direccion);
                    if(meses==-1 || dias==-1) {
                        printf("Edad: %d\n", edad);
                    }else {
                        printf("Meses: %d Dias: %d",meses,dias);
                    }
                    printf("Meses: %d\n", meses);
                    printf("Días: %d\n", dias);
                    printf("Género: %d\n", genero);
                    printf("Descripción: %s\n", descripcion);
                    printf("Consultorio: %d\n", consultorio);
                    printf("-----------------------\n");
                    break;
                }
            }
            printf("Desea actualizar el registro? S: Si, N: No");
            scanf("%d",&opcion);
            if(opcion=='S'|| opcion=='s') {

            }

            if (!encontrado) {
                printf("Paciente con ID %d no encontrado.\n", id);
            }

            fclose(archivo);
            break;

            case 5:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion no valida\n");
                break;
        }
    }

    return 0;
}