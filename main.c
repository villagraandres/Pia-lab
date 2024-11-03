#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void actualizarRegistro(FILE *);
struct Paciente {
    int edad, genero, servicio, consultorio, id, meses, dias;
    char nombre[100];
    char descripcion[200];
    char direccion[100];
};

int main(void) {
    int opcion = 0, opcion2 = 1, id;
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
                    struct Paciente datosPaciente = {0};
                    printf("Ingrese el nombre: ");
                    while (getchar() != '\n');
                    fgets(datosPaciente.nombre, sizeof(datosPaciente.nombre), stdin);
                    datosPaciente.nombre[strcspn(datosPaciente.nombre, "\n")] = '\0';

                    printf("Ingrese el tipo de servicio (1. Consulta Externa 2. Emergencias): ");
                    scanf("%d", &datosPaciente.servicio);

                    printf("Ingrese su direccion: ");
                    while (getchar() != '\n');
                    fgets(datosPaciente.direccion, sizeof(datosPaciente.direccion), stdin);
                    datosPaciente.direccion[strcspn(datosPaciente.direccion, "\n")] = '\0';

                    do {
                        printf("Ingrese su edad: ");
                        scanf("%d", &datosPaciente.edad);
                        if (datosPaciente.edad < 0) {
                            printf("Edad incorrecta\n");
                        }
                    } while (datosPaciente.edad < 0);

                    if (datosPaciente.edad == 0) {
                        do {
                            printf("Ingrese los meses: ");
                            scanf("%d", &datosPaciente.meses);
                            if (datosPaciente.meses < 0) {
                                printf("Dato incorrecto\n");
                            }
                        } while (datosPaciente.meses < 0);
                    }

                    if (datosPaciente.meses == 0 && datosPaciente.edad==0) {
                        do {
                            printf("Ingrese los dias de nacido: ");
                            scanf("%d", &datosPaciente.dias);
                            if (datosPaciente.dias < 0) {
                                printf("Dato incorrecto\n");
                            }
                        } while (datosPaciente.dias < 0);
                    }

                    printf("Ingrese su genero (1. Hombre 2. Mujer): ");
                    scanf("%d", &datosPaciente.genero);

                    printf("Ingrese la descripcion de sus sintomas: ");
                    while (getchar() != '\n');
                    fgets(datosPaciente.descripcion, sizeof(datosPaciente.descripcion), stdin);
                    datosPaciente.descripcion[strcspn(datosPaciente.descripcion, "\n")] = '\0';

                    printf("Ingrese el numero del consultorio del doctor que le atendera: ");
                    scanf("%d", &datosPaciente.consultorio);

                    fprintf(archivo, "%d|%s|%d|%s|%d|%d|%d|%d|%s|%d\n", id, datosPaciente.nombre, datosPaciente.servicio, datosPaciente.direccion,
                            datosPaciente.edad, datosPaciente.meses, datosPaciente.dias, datosPaciente.genero, datosPaciente.descripcion, datosPaciente.consultorio);

                    printf("\nSu numero de folio es: %d\n", id);
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
                struct Paciente datosPaciente;
                while (fgets(linea, sizeof(linea), archivo) != NULL) {
                    int idActual;
                    sscanf(linea, "%d|", &idActual);

                    if (idActual == id) {
                        encontrado = 1;
                        sscanf(linea, "%d|%99[^|]|%d|%99[^|]|%d|%d|%d|%d|%199[^|]|%d",
                               &datosPaciente.id, datosPaciente.nombre, &datosPaciente.servicio, datosPaciente.direccion, &datosPaciente.edad,
                               &datosPaciente.meses, &datosPaciente.dias, &datosPaciente.genero, datosPaciente.descripcion, &datosPaciente.consultorio);

                        printf("ID: %d\n", datosPaciente.id);
                        printf("Nombre: %s\n", datosPaciente.nombre);
                        printf("Servicio: %d\n", datosPaciente.servicio);
                        printf("Dirección: %s\n", datosPaciente.direccion);
                        if (datosPaciente.edad > 0) {
                            printf("Edad: %d\n", datosPaciente.edad);
                        } else {
                            printf("Meses: %d\n", datosPaciente.meses);
                            printf("Días: %d\n", datosPaciente.dias);
                        }
                        printf("Género: %d\n", datosPaciente.genero);
                        printf("Descripción: %s\n", datosPaciente.descripcion);
                        printf("Consultorio: %d\n", datosPaciente.consultorio);
                        printf("-----------------------\n");
                        break;
                    }
                }
                printf("Desea actualizar el registro? S: Si, N: No: ");
                char actualizar;
                scanf(" %c", &actualizar);
                if (actualizar == 'S' || actualizar == 's') {
                    // Lógica para actualizar el registro
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