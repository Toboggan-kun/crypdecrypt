/*
PROJET SECURITE
Groupe:
    - TANG SONG Caroline
    - ABDELMALKI Noha

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_MAX 500
#define SIZE_LINE_MATRIX 4
#define SIZE_COLUMNS_MATRIX 8

//PROTOTYPES DE FONCTIONS
char *one_dimension_char(char *, int);
int *one_dimension_int(int *, int);
int **two_dimension_int(int **, int, int);
int *convert_binary(char *, int *, int);
char *binary_to_hexa(int *, char *, int);
char *change_hexa(char *, int *, int);
int *hexa_to_binary(int *, int *, int);
int *sub_messages(int **, int *, int , int , int , int *);
char *final_message(int *, int, char*);
char *message_decrypted(int *, int *, char *, int);
int deleteSpace(char *);

int main(int argc, char ** argv){

    //DECLARATION DES VARIABLES
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
    char *letter = NULL;
    int i = 0;
    int j = 0;
    int k = 0;
    int cnt = 0;
    int choice = 0;

        //MENU
        printf("\n   BIENVENUE SUR CODEC - L'APPLICATION PRECAIRE POUR CRYPTER/DECRYPTER VOTRE MESSAGE!\n\n");
        while(choice != 1 || choice != 2 || choice != 3){

            printf("\n   1- CRYPTER LE MESSAGE\n\n");
            printf("   2- DECRYPTER LE MESSAGE\n\n");
            printf("   3- QUITTER LE PROGRAMME...\n\n");
            printf("   VOTRE CHOIX: ");

            scanf("%d", &choice);
            switch(choice){

                case 1:
                    printf("\n   VOUS AVEZ CHOISI LE CRYPTAGE DU MESSAGE\n\n");
                    //OUVERTURES DE FICHIERS
                    FILE *text = NULL;
                    text = fopen("text.txt", "r+t");

                    //LECTURE DU FICHIER A CRYPTER
                    if(text != NULL){
                        text_array = one_dimension_char(text_array, SIZE_MAX);
                        container = one_dimension_char(container, SIZE_MAX);

                        while(fgets(container, SIZE_MAX, text) != NULL){ //fgets PREND EN COMPTE QUE D'UNE LIGNE
                            strcat(text_array,container); //CONCATENASION DE LA SUITE DE LA CHAINE DE CARACTERES DE text_array

                        }
                    //AFFICHAGE DU MESSAGE
                    printf("   LE MESSAGE A CRTPTER:\n\n");
                    size_array = ftell(text); //TAILLE DU FICHIER
                    printf("%s", text_array);
                    printf("\n\n   TAILLE DU FICHIER: %d\n", size_array);
                    array_bits = one_dimension_int(array_bits, size_array * 8);

                    //AFFICHAGE DU MESSAGE EN DECIMAL
                    i = 0;
                    printf("\n   LE MESSAGE EN DECIMAL:\n\n");
                    for(i = 0; i < size_array; i++){
                        printf("%c : %d", text_array[i], text_array[i]);
                        printf("\n");

                    }
                    printf("\n");
                    i = 0;

                    //CONVERSION BINAIRE DE LA CHAINE
                    array_bits = convert_binary(text_array, array_bits, size_array);


                    //CONVERSION BINAIRE EN HEXADECIMAL
                    hexa = one_dimension_char(hexa, (size_array * 2));
                    hexa = binary_to_hexa(array_bits, hexa, size_array);

                    printf("\n");
                    //OUVERTURE DU FICHIER MATRICE G4,8
                    FILE *matrix = NULL;
                    matrix = fopen("key.txt", "rt");
                    char matrix_array[50];
                    if(matrix != NULL){
                        fgets(matrix_array, 50, matrix);
                        cnt = 0;
                        i = 0;
                        cnt = strlen(matrix_array); //TAILLE DE LA MATRICE
                        array_file = one_dimension_char(array_file, cnt);

                        //RECUPERATION DES DONNEES SOUHAITEES DANS LE FICHIER

                        for(i = 5; i < cnt-1; i++){
                            if(matrix_array[i] == '0' || matrix_array[i] == '1' || matrix_array[i] == ' '){ //SI LE FORMAT DE LA CLE EST BONNE

                                array_file[j] = matrix_array[i];
                                j++;

                            }else{ //SINON QUITTE LE PROGRAMME POUR CHANGER DE CLE
                                printf("\n   VOTRE CLE NE CORRESPOND PAS...\n   VEUILLEZ SAISIR UNE AUTRE CLE...\n");
                                exit(0);
                            }
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
                        printf("\n   LA MATRICE G4,8:\n\n   ");
                        for(i = 0; i < SIZE_LINE_MATRIX; i++){
                            for(j = 0; j < SIZE_COLUMNS_MATRIX; j++){
                                key[i][j] = array_file[k] - 48; //CONVERSION ASCII
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
                        letter = one_dimension_char(letter, size_array*2+1);
                        letter[size_array*2] = '\0';
                        letter = final_message(result, size_array, letter);

                        //CREATION DU FICHIER AVEC MESSAGE CRYPTE
                        FILE * crypted_file = NULL;

                        crypted_file = fopen("crypted_file.txtc", "w+t");
                        if(crypted_file != NULL){

                            fwrite(letter, sizeof(char), size_array*2, crypted_file);

                            fclose(crypted_file);

                        }else{
                            printf("\n\n   ECHEC DU CHARGEMENT DU FICHIER...\n");
                        }


                    }else{
                        printf("\n\n   ECHEC DU CHARGEMENT DU FICHIER...\n");
                    }

                    //LIBERATION DES TABLEAUX ALLOUES ET FERMETURE DES FICHIERS
                    free(letter);
                    free(result);
                    for(i = 0; i < SIZE_COLUMNS_MATRIX; i++){
                        free(key[i]);
                    }
                    free(key);
                    fclose(matrix);
                    free(array_file);
                    free(array_bits_hexa);
                    free(change);
                    free(hexa);
                    free(array_bits);
                    free(text_array);
                    free(container);
                    }else{
                        printf("\n\n   ECHEC DU CHARGEMENT DU FICHIER...\n");
                    }
                    printf("\n\n");
                    break;
                case 2:
                    printf("\n   VOUS AVEZ CHOISI LE DECRYPTAGE DU MESSAGE\n\n   ");
                    FILE * message = NULL;
                    message = fopen("crypted_file.txtc", "r+t");


                    if(message != NULL){

                        text_array = one_dimension_char(text_array, SIZE_MAX);
                        container = one_dimension_char(container, SIZE_MAX);

                        while(fgets(container, SIZE_MAX, message) != NULL){ //fgets PREND EN COMPTE QUE D'UNE LIGNE
                            strcat(text_array,container); //CONCATENASION DE LA SUITE DE LA CHAINE DE CARACTERES DE text_array

                        }
                        printf("LE MESSAGE CRYPTE:\n   ");
                        printf("%s", text_array);

                        size_array = ftell(message); //TAILLE DU FICHIER
                        printf("\n   TAILLE DU FICHIER: %d\n", size_array);

                        //CONVERSION DU MESSAGE EN BINAIRE
                        array_bits = one_dimension_int(array_bits, size_array * 8);
                        array_bits = convert_binary(text_array, array_bits, size_array);

                        /*//MATRICE G4,8
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
                            j = 0;

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
                            result = one_dimension_int(result, (size_array * 8) * 2);
                            result = sub_messages(key, array_bits, SIZE_LINE_MATRIX, SIZE_COLUMNS_MATRIX, size_array, result);*/
                            letter = one_dimension_char(letter, size_array/2);
                            result = one_dimension_int(result, size_array*4);
                            letter = message_decrypted(array_bits, result, letter, size_array);

                            //CREATION DU FICHIER DECRYPTE
                            FILE *decrypted_file = NULL;
                            decrypted_file = fopen("decrypted_file.txtcd", "w+t");

                            if(decrypted_file != NULL){
                                fwrite(letter, sizeof(char), size_array/2, decrypted_file);
                                fclose(decrypted_file);

                            }else{
                                printf("\n\n   ECHEC DU CHARGEMENT DU FICHIER...\n");
                            }

                            //LIBERATION DES TABLEAUX ALLOUES ET FERMETURE DES FICHIERS
                            free(letter);
                            free(result);
                            /*for(i = 0; i < SIZE_COLUMNS_MATRIX; i++){
                                free(key[i]);
                            }
                            free(key);*/
                            //fclose(matrix);
                            free(array_bits);
                            free(container);
                            free(text_array);
                            fclose(message);
                        /*}else{
                            printf("\n\nECHEC DU CHARGEMENT DU FICHIER...");
                        }*/
                    }else{
                        printf("\n\n   ECHEC DU CHARGEMENT DU FICHIER...\n\n");
                    }

                    break;
                case 3:
                    printf("\n   VOUS QUITTEZ LE PROGRAMME...\n");
                    exit(0);
                    break;
                default:
                    printf("\n   VEUILLEZ SAISIR LE NUMERO CORRESPONDANT...\n");
                    break;
        }

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
    int i = 0;
    array = malloc(sizeof(int) * size);
    //INITIALISATION DU TABLEAU A 0
    for(i = 0; i < size; i++){
        array[i] = 0;
    }
    return array;
}
int **two_dimension_int(int **array, int lines, int columns){
    int i = 0;
    int j = 0;
    array = (int*)malloc(sizeof(int*) * lines);
    for(i = 0; i < lines; i++){
        array[i] = malloc(sizeof(int) * columns);
    }
    //INITIALISATION DU TABLEAU A 0
    for(i = 0; i < lines; i++){
        for(j = 0; j < columns; j++){
           array[i][j] = 0;
        }
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
        if(array[i] < 0){
            result += 256;
        }
        if(array[i] == 48){
            result = 0;
        }

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
    printf("\n   LE MESSAGE CONVERTI EN BINAIRE:\n\n   ");
    cnt = 0;
    i = 0;
    j = 0;

    for(i = 0; i < size * 8; i++){

        printf("%d", bits[i]);
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
char *final_message(int *result_message, int size, char *letter){
    printf("\n\n   LE MESSAGE FINAL:\n   ");
    printf("M = ");
    int result = 0;
    int cnt = 0;
    int i = 0;
    int j = 0;

    int bits_array[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    //result = one_dimension_char(result, size*2);
    for(i = 0; i < size*2; i ++){

        for(j = 0; j < 8; j++){
            result += bits_array[j] * result_message[cnt];
            cnt++;

            if(j == 7){
                if(result == 0){
                    letter[i] = 48;
                    printf("%c", letter[i]);
                    result = 0;
                }else{
                    letter[i] = result;
                    printf("%c", letter[i]);
                    result = 0;
                }

            }
        }
    }

    return letter;

}
char *message_decrypted(int *bits, int *result, char *message, int size){
    int i = 0;
    int j = 0;
    int k = 0;
    int cnt = 0;
    int decimal = 0;
    int bits_array[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    printf("\n   ON RECUPERE LES 4 PREMIERS BITS CORRESPONDANT A LA MATRICE IDENTITE:\n\n   ");
    while(bits[i] < size*8 && j != (size*8) / 2){
        if(i >= 4 && i % 4 == 0){
            cnt += 4;
        }

        result[j] = bits[i + cnt];
        printf("%d", result[j]);

        i++;
        j++;
        k++;
        if(k == 4){
            printf(" ");
            k = 0;
        }
    }

    //CONVERSION BINAIRE EN DECIMAL
    i = 0;
    j = 0;
    cnt = 0;
    printf("\n\n   LE MESSAGE DECRYPTE:\n\n");
    for(i = 0; i < size / 2; i++){
        for(j = 0; j < 8; j++){

            decimal += bits_array[j] * result[cnt];
            cnt++;
            if(j == 7){
                if(decimal == 131 || decimal == 67 || decimal == 35 || decimal == 19 || decimal == 11){
                    decimal = decimal - 3;
                    message[i] = decimal;
                    printf("%c", message[i]);
                    decimal = 0;
                }else{
                    message[i] = decimal;
                    printf("%c", message[i]);
                    decimal = 0;
                }

            }
        }
    }
    printf("\n\n");

    return message;
}
