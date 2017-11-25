#include <stdio.h>
#include <stdlib.h>
#define SIZE_MAX 500

char *one_dimension_char(char *, int);
int *one_dimension_int(int *, int);
int *convert_binary(char *, int *, int);
char *binary_to_hexa(int *, char *, int);
char *change_hexa(char *, char *, int);
int *hexa_to_binary(char *, int *, int);
int main(int argc, char ** argv){


    char *text_array = NULL;
    char *container = NULL;
    int *array_bits = NULL;
    char *hexa = NULL;
    char *change = NULL;
    int *array_bits_hexa = NULL;
    int size_array = 0;
    int i = 0;
    int j = 0;
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
        printf("\n   TAILLE DU FICHIER: %d\n\n", size_array);

        while(choice != 1 || choice != 2 || choice != 3){

            printf("\n1- CRYPTER LE MESSAGE\n");
            printf("2- DECRYPTER LE MESSAGE\n");
            printf("3- QUITTER LE PROGRAMME\n");
            printf("   VOTRE CHOIX: ");

            scanf("%d", &choice);
            switch(choice){

                case 1:
                    printf("\n   VOUS AVEZ CHOISI LE CRYPTAGE DU MESSAGE\n");
                    free(text_array);
                    text_array = one_dimension_char(text_array, size_array);
                    array_bits = one_dimension_int(array_bits, size_array * 8);

                    //INITIALISATION DU TABLEAU A 0
                    for(i = 0; i < size_array * 8; i++){
                        array_bits[i] = 0;
                    }
                    cnt = 0;
                    i = 0;
                    while(i < size_array){
                        printf("%d", text_array[i]);
                        i++;
                        cnt++;
                        if(cnt == 2){
                            printf(" ");
                            cnt = 0;
                        }
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
                    hexa = one_dimension_char(hexa, size_array * 2);
                    //CONVERSION BINAIRE EN HEXA
                    hexa = binary_to_hexa(array_bits, hexa, size_array);

                    //CONVERSION ASCII
                    change = one_dimension_char(change, size_array);
                    change = change_hexa(hexa, change, size_array);

                    //CONVERSION HEXA EN BINAIRE
                    array_bits_hexa = one_dimension_int(array_bits_hexa, size_array * 8);
                    array_bits = hexa_to_binary(change, array_bits_hexa, size_array);


                    break;
                case 2:
                    break;
                case 3:

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
char *change_hexa(char *hexa, char *change, int size){
    int change_ascii = 0;
    int i = 0;
    for(i = 0; i < (size * 8) / 4; i++){
        if(hexa[i] >= 'A' && hexa[i] <= 'F'){ //A à F
            change_ascii = hexa[i] - 55;
            change[i] = change_ascii; //Stockage de la saisie dans un tableau
        }else if(hexa[i] >= 'a' && hexa[i] <= 'f'){ //a à f
            change_ascii = hexa[i] - 87;
            change[i] = change_ascii;
        }else if(hexa[i] >= '0' && hexa[i] <= '9'){ //0 à 9

            change_ascii = hexa[i] - 48;
            change[i] = change_ascii;
        }
    }
    return change;
}
int *hexa_to_binary(char *hexa, int *binary, int size){
    int i = 0;
    int k = 0; //Parcours de 4 en 4
    int rest = 0; //Stockage du reste
    int result = 0; //Stockage de la valeur divisée
    int cnt = 0; //Parcours du tableau +4
    printf("\n   CONVERSION BINAIRE DE LA CHAINE HEXA\n\n   ");

    for(i = 0; i < (size * 8) / 4; i++){

        if(i > 0){
            cnt += 4; //Si i > 0, cnt va permettre de se déplacer à tab_bits[k + 4]
        }
        for(k = 3; k >= 0; k--){ //Commencer à partir de l'indice 3
            rest = hexa[i] % 2; //Récupère le reste
            result = hexa[i];
            result /= 2; //On divise la valeur par 2
            if(rest == 0){
                binary[k + cnt] = 0;
                hexa[i] = result; //Initialisation de la valeur divisée par 2 dans le tableau

            }else{
                binary[k + cnt] = 1;
                hexa[i] = result; //Initialisation de la valeur divisée par 2 dans le tableau
            }

        }
    }
    //AFFICHAGE
    cnt = 0;
    result = 0;
    printf("T = ");
    for(i = 0; i < size*8; i++){
        printf("%d", binary[i]); //Affichage du tableau binaire
        cnt++;
        if(cnt == 4){
            printf(" ");
            cnt = 0;
        }
        result++;
    }
    printf("\ntaille = %d", result);
    return binary;
}
