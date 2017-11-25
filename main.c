#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_MAX 500
#define SIZE_LINE_MATRIX 4
#define SIZE_COLUMNS_MATRIX 8

char *one_dimension_char(char *, int);
int *one_dimension_int(int *, int);
int **two_dimension_int(char **, int, int);
int *convert_binary(char *, int *, int);
char *binary_to_hexa(int *, char *, int);
char *change_hexa(char *, int *, int);
int *hexa_to_binary(int *, int *, int);
int deleteSpace(char *);

int main(int argc, char ** argv){


    char *text_array = NULL;
    char *container = NULL;
    int *array_bits = NULL;
    char *hexa = NULL;
    int *change = NULL;
    int *array_bits_hexa = NULL;
    char *array_file = NULL;
    int key[SIZE_LINE_MATRIX][SIZE_COLUMNS_MATRIX];
    int size_array = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int cnt = 0;
    int choice = 0;

    //OUVERTURES DE FICHIERS
    FILE *text = NULL;
    text = fopen("text.txt", "r+t");


    if(text != NULL){
        text_array = one_dimension_char(text_array, SIZE_MAX);
        container = one_dimension_char(container, SIZE_MAX);

        while(fgets(container, SIZE_MAX, text) != NULL){ //fgets PREND EN COMPTE QUE D'UNE LIGNE
            strcat(text_array,container); //CONCATENASION DE LA SUITE DE LA CHAINE DE CARACTERES DE text_array

        }
        printf("   MESSAGE:\n");
        while(text_array[i] != '\0'){
            fread(&text_array, sizeof(char), i, text);
            printf("%c", text_array[i]);
            i++;
            cnt++;

        }

        size_array = cnt;
        printf("\n   TAILLE DU FICHIER: %d\n", size_array);

        while(choice != 1 || choice != 2 || choice != 3){

            printf("\n1- CRYPTER LE MESSAGE\n");
            printf("2- DECRYPTER LE MESSAGE\n");
            printf("3- QUITTER LE PROGRAMME\n");
            printf("   VOTRE CHOIX: ");

            scanf("%d", &choice);
            switch(choice){

                case 1:
                    printf("\n   VOUS AVEZ CHOISI LE CRYPTAGE DU MESSAGE\n");

                    array_bits = one_dimension_int(array_bits, size_array * 8);

                    i = 0;
                    printf("%s", text_array);
                    while(text_array[i] != '\0'){
                        printf("%d ", text_array[i]);
                        i++;
                    }
                    //INITIALISATION DU TABLEAU A 0
                    for(i = 0; i < size_array * 8; i++){
                        array_bits[i] = 0;
                    }
                    //CONVERSION BINAIRE DE LA CHAINE
                    array_bits = convert_binary(text_array, array_bits, size_array);

                    printf("\n   LE MESSAGE EN BINAIRE:\n\n   ");
                    cnt = 0;
                    j = 0;
                    for(i = 0; i < size_array * 8; i++){
                        printf("%d", array_bits[i]);
                        cnt++;
                        j++;
                        if(j == 4){
                            printf(" ");
                            j = 0;
                        }
                        if(cnt == 8){
                            printf("\n   ");
                            cnt = 0;
                        }
                    }
                    //CONVERSION BINAIRE EN HEXA
                    hexa = one_dimension_char(hexa, (size_array * 2));
                    hexa = binary_to_hexa(array_bits, hexa, size_array);

                    printf("\n");
                    FILE *matrix = NULL;
                    matrix = fopen("key.txt", "rt");
                    char matrix_array[50];
                    if(matrix != NULL){
                        fgets(matrix_array, 50, matrix);
                        cnt = 0;
                        i = 0;
                        cnt = strlen(matrix_array);
                        array_file = one_dimension_char(array_file, cnt);


                        for(i = 5; i < cnt-1; i++){
                            array_file[j] = matrix_array[i];
                            j++;

                        }
                        i = 0;
                        //SUPPRESSION DES ESPACES
                        for(i = 0; i < cnt; i++){
                            deleteSpace(array_file);
                        }
                        cnt = 0;
                        //MATRICE G4,8: TABLEAU A DEUX DIMENSIONS
                        printf("\n   MATRICE G4:\n\n   ");
                        for(i = 0; i < 4; i++){
                            for(j = 0; j < 8; j++){
                                key[i][j] = array_file[k] - 48;
                                k++;
                                printf("%d", key[i][j]);
                                cnt++;
                                if(cnt == 8){
                                    printf("\n   ");
                                    cnt = 0;
                                }
                            }
                        }
                        /*//PERMUTATION DES COLONNES 1 ET 4
                        printf("\n   ");
                        cnt = 0;
                        i = 0;
                        int permut[SIZE_LINE_MATRIX][SIZE_COLUMNS_MATRIX];
                        for(i = 0; i < SIZE_LINE_MATRIX; i++){
                            permut[i][0] = key[i][4];
                        }
                        for(i = 0; i < SIZE_LINE_MATRIX; i++){
                            key[i][4] = key[i][0];
                        }
                        for(i = 0; i < SIZE_LINE_MATRIX; i++){
                            key[i][0] = permut[i][0];
                        }
                        for(i = 0; i < SIZE_LINE_MATRIX; i++){
                            for(j = 0; j < SIZE_COLUMNS_MATRIX; j++){
                                printf("%d", key[i][j]);
                                cnt++;
                                if(cnt == 8){
                                    printf("\n   ");
                                    cnt = 0;
                                }
                            }
                        }*/






                    }else{
                        printf("\n\nECHEC DU CHARGEMENT DU FICHIER...");
                    }



                    break;
                case 2:
                    break;
                case 3:
                    free(array_file);
                    free(array_bits_hexa);
                    free(change);
                    free(hexa);
                    free(array_bits);
                    free(text_array);
                    free(container);
                    fclose(text);
                    exit(0);
                    break;
                default:
                    printf("\nERREUR");
                    break;
            }


        }
    }else{
        printf("\n\nECHEC DU CHARGEMENT DU FICHIER...");
    }

    return 0;
}


char *one_dimension_char(char *name, int size){

    char *string = malloc(sizeof(char) * size);

    string[0] = '\0';

    name = string;

    return name;
}
int *one_dimension_int(int *array, int size){
    array = malloc(sizeof(int) * size);
    return array;
}
int **two_dimension_int(int **array, int lines, int columns){
    int i = 0;
    array = (int*)malloc(sizeof(int*) * lines);
    for(i = 0; i < lines; i++){
        array = malloc(sizeof(int) * columns);
    }
    return array;
}
int *convert_binary(char *array, int *bits, int size){
    int i = 0;
    int j = 0;
    int cnt = 0;
    int rest = 0;
    int result = 0;
    for(i = 0; i < size; i++){
        if(i > 0){
            cnt += 8;
        }

        result = array[i];
        for(j = 7; j >= 0; j--){
            rest = result % 2;
            result /= 2;

            if(rest == 0){
                bits[j + cnt] = 0;

            }else{
                bits[j + cnt] = 1;

            }
        }
    }

    return bits;
}
char *binary_to_hexa(int *bits, char *hexa, int size){

    int i = 0;
    int j = 0;
    int k = 0;
    int result = 0;
    int cnt = 0;
    int cnt2 = 0;
    int bits_array[4] = {8, 4, 2, 1};

    printf("\n   LE MESSAGE EN HEXA:\n\n   ");

    for(i = 0; i < (size * 8) / 4; i++){
        if(i > 0){
            cnt += 4;
        }
        for(j = 0; j < 4; j++){
            result += bits_array[j] * bits[j + cnt];
                if(j == 3){
                    if(result >= 0 && result <= 9){ //0 à 9
                        result = result + 48;
                        hexa[k] = result;
                        printf("%c", hexa[k]);
                        k++;
                        result = 0;
                        cnt2++;
                        if(cnt2 == 2){
                            printf(" ");
                            cnt2 = 0;
                        }
                    }else if(result >= 10 && result <= 15){ //a à f
                        result = result + 55;

                        hexa[k] = result;
                        printf("%c", hexa[k]);
                        k++;
                        result = 0;
                        cnt2++;
                        if(cnt2 == 2){
                            printf(" ");
                            cnt2 = 0;
                        }
                    }
                }
        }

    }

    return hexa;

}

int deleteSpace(char * str){
    char * ptr = str;
    while((ptr = strchr(ptr, ' ')) != NULL){
        strcpy(ptr, ptr + 1);
    }
    return ptr;
}
int sub_messages(int ){

}
