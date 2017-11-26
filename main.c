#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_MAX 500
#define SIZE_LINE_MATRIX 4
#define SIZE_COLUMNS_MATRIX 8

char *one_dimension_char(char *, int);
int *one_dimension_int(int *, int);
int **two_dimension_int(int **, int, int);
int *convert_binary(char *, int *, int);
char *binary_to_hexa(int *, char *, int);
char *change_hexa(char *, int *, int);
int *hexa_to_binary(int *, int *, int);
int *sub_messages(int **, int *, int , int , int , int *);
int *final_message(int *, int);
int deleteSpace(char *);

int main(int argc, char ** argv){


    char *text_array = NULL;
    char *container = NULL;
    int *array_bits = NULL;
    char *hexa = NULL;
    int *change = NULL;
    int *array_bits_hexa = NULL;
    char *array_file = NULL;
    int **key = NULL;
    int *result = NULL;
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

        if(fgets(container, SIZE_MAX, text) != NULL){ //fgets PREND EN COMPTE QUE D'UNE LIGNE
            strcat(text_array,container); //CONCATENASION DE LA SUITE DE LA CHAINE DE CARACTERES DE text_array


        }
        printf("   MESSAGE:\n");
        while(text_array[i] != NULL){
            fread(&text_array, sizeof(char), 1, text);
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


                        key = two_dimension_int(key, SIZE_LINE_MATRIX, SIZE_COLUMNS_MATRIX);

                        //MATRICE G4,8: TABLEAU A DEUX DIMENSIONS
                        i = 0;
                        j = 0;
                        k = 0;
                        cnt = 0;
                        printf("\n   MATRICE G4:\n\n   ");
                        for(i = 0; i < SIZE_LINE_MATRIX; i++){
                            for(j = 0; j < SIZE_COLUMNS_MATRIX; j++){
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
                        //CALCUL MATRICIEL
                        result = one_dimension_int(result,(size_array * 8) * 2); //STOCKAGE DU RESULTAT
                        result = sub_messages(key, array_bits, SIZE_LINE_MATRIX, SIZE_COLUMNS_MATRIX, size_array, result);
                        //AFFICHAGE DU RESULTAT
                        result = final_message(result, size_array);

                        //CREATION DU FICHIER AVEC MESSAGE CRYPTE
                        FILE * crypted_file = NULL;
                        crypted_file = fopen("crypted_file.txtc", "w+t");
                        if(crypted_file != NULL){

                            strcat(crypted_file, result);

                        }else{
                            printf("\n\nECHEC DU CHARGEMENT DU FICHIER...");
                        }




                    }else{
                        printf("\n\nECHEC DU CHARGEMENT DU FICHIER...");
                    }
                    free(result);
                    for(i = 0; i < SIZE_COLUMNS_MATRIX; i++){
                        free(key[i]);
                    }
                    free(key);

                    free(array_file);
                    free(array_bits_hexa);
                    free(change);
                    free(hexa);
                    free(array_bits);
                    free(text_array);
                    free(container);
                    break;
                case 2:
                    break;
                case 3:


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
        array[i] = malloc(sizeof(int) * columns);
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
int *sub_messages(int **key, int *bits, int lines, int columns, int size, int *result_message){
    printf("\n   CALCUL DES SOUS-MESSAGES X:\n\n   ");
    //CALCUL DU PRODUIT+SOMME MATRICIEL
    int i = 0;
    int j = 0;
    int k = 0;
    int one = 0;
    int two = 0;
    int cnt = 0; //Garde en mémoire
    int product = 0;
    int **convert_array = NULL;
    int result = 0;

    convert_array = two_dimension_int(convert_array, size*2, columns);
    for(i = 0; i < (size*4)/2; i++){ //(12 * 4) / 3

        for(one = 0; one < columns; one++){

            product = 0;
            for(two = 0; two < lines; two++){
                product += bits[cnt + two] * key[two][one];
            }
            if(product % 2 == 0){
                convert_array[i][one] = 0; //Attribue 0

            }else{
                convert_array[i][one] = 1; //Attribue 1

            }
        }
        cnt += 4; //Permet d'avancer de +3
    }
    cnt = 0;
    result = 0;
    for(i = 0; i < size*2; i++){
        k++;
        printf("X%d = ", k);
        for(j = 0; j < 8; j++){
            printf("%d", convert_array[i][j]);
            result_message[result] = convert_array[i][j];
            cnt++;
            result++;
            if(cnt == 8){
                printf("\n   ");
                cnt = 0;
            }
        }
    }
    return result_message;
}
int *final_message(int *result_message, int size){
    printf("\n\n   MESSAGE FINAL:\n   ");
    printf("X = (");
    int result;
    char letter;
    int cnt = 0;
    int cnt2 = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int bits_array[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    //result = one_dimension_char(result, size*2);
    for(i = 0; i < size*2; i ++){

        for(j = 0; j < 8; j++){
            result += bits_array[j] * result_message[cnt];
            //printf("result = %d\n", result);
            cnt++;

            if(j == 7){
                letter = result;
                printf("%c", letter);
                result = 0;
                letter = 0;
            }
        }
    }
    printf(")h");
    return result;

}
