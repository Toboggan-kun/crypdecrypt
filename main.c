#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 9
int deleteSpace(char*);
int main(int argc, char ** argv){

    char text_array[SIZE] = "Passages";
    int choice = 0;
    int size = 0;
    int tab_value[size*8];
    int tab_bits[SIZE*8] = {0};
    char tab_hexa[SIZE*2];
    char change_hexa;
    char tab_hexa_change[SIZE];
    int bits[4] = {8, 4, 2, 1};
    int tab_bits_hexa[SIZE*8];
    char tab_file[35];
    int key[4][8];
    int convert_array[(SIZE*4)/2][8];
    int all_submessages[((SIZE*4)/2)*8];
    int i = 0;
    int j = 0;
    int k = 0;
    int cnt = 0;
    int cnt2 = 0;
    int rest = 0;
    int result = 0;
    printf("\n   MESSAGE: %s", text_array);
    printf("\n");

    while(choice != 1 || choice != 2 || choice != 3){
        printf("\n1- CRYPTER LE MESSAGE\n");
        printf("2- DECRYPTER LE MESSAGE\n");
        printf("3- QUITTER LE PROGRAMME\n");
        printf("   VOTRE CHOIX: ");

        scanf("%d", &choice);
        switch(choice){

        case 1:
            printf("\n   VOUS AVEZ CHOISI LE CRYPTAGE DU MESSAGE\n");


            //CONVERSION DU TABLEAU EN BINAIRE
            cnt = 0;
            while(i < SIZE){
                //printf("%d", text_array[i]);
                i++;
                //cnt++;
                //if(cnt = 2){
                    //printf(" ");
                    //cnt = 0;
                //}
            }

            //CONVERSION DU MESSAGE EN BINAIRE
            for(i = 0; i < SIZE; i++){
                if(i > 0)
                    cnt += 8;


                result = text_array[i];
                //j = 0;
                for(j = 7; j >= 0; j--){
                    rest = result % 2; //On récupère le reste
                    //printf("\nrest = %d", rest);

                    result /= 2; //On divise la valeur par 2 (division successive)
                    //printf("\nresult = %d", result);
                    if(rest == 0){
                        tab_bits[j + cnt] = 0;
                        tab_value[i] = result; //On récupère la valeur divisée pour la récupérer ensuite
                    }else{
                        tab_bits[j + cnt] = 1;
                        tab_value[i] = result; //On récupère la valeur divisée pour la récupérer ensuite

                    }

                }


            }
            printf("\n   LE MESSAGE EN BINAIRE:\n\n   ");
            cnt = 0;
            j = 0;
            for(i = 0; i < SIZE * 8; i++){
                printf("%d", tab_bits[i]);
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

            //CONVERSION BINAIRE EN HEXADECIMAL
            k = 0;
            result = 0;
            cnt = 0;
            size = 0;
            printf("\n   LE MESSAGE EN HEXA:\n\n   ");

            for(i = 0; i < (SIZE * 8) / 4; i++){
                if(i > 0){
                    cnt += 4;
                }
                for(j = 0; j < 4; j++){
                    result += bits[j] * tab_bits[j + cnt];


                    if(j == 3){
                        if(result >= 0 && result <= 9){ //0 à 9
                            result = result + 48;
                            //printf("result = %d", result);
                            tab_hexa[k] = result;
                            printf("%c", tab_hexa[k]);
                            k++;
                            result = 0;
                            size++;
                            if(size == 2){
                                printf(" ");
                                size = 0;
                            }
                        }else if(result >= 10 && result <= 15){ //a à f
                            result = result + 55;
                            //printf("result = %d", result);
                            tab_hexa[k] = result;
                            printf("%c", tab_hexa[k]);
                            k++;
                            result = 0;
                            size++;
                            if(size == 2){
                                printf(" ");
                                size = 0;
                            }
                        }
                    }
                }

            }
            printf("\n");
            //CONVERSION BINAIRE DES CARACTERES
            for(i = 0; i < (SIZE * 8) / 4; i++){
                if(tab_hexa[i] >= 'A' && tab_hexa[i] <= 'F'){ //A à F
                change_hexa = tab_hexa[i] - 55;
                tab_hexa_change[i] = change_hexa; //Stockage de la saisie dans un tableau
                }else if(tab_hexa[i] >= 'a' && tab_hexa[i] <= 'f'){ //a à f
                    change_hexa = tab_hexa[i] - 87;
                    tab_hexa_change[i] = change_hexa;
                }else if(tab_hexa[i] >= '0' && tab_hexa[i] <= '9'){ //0 à 9

                    change_hexa = tab_hexa[i] - 48;
                    tab_hexa_change[i] = change_hexa;
                }
            }

            //CONVERSION BINAIRE EN HEXADECIMAL
            printf("\n");
            printf("   CONVERSION BINAIRE DE LA CHAINE HEXA\n\n   ");

            k = 0; //Parcours de 4 en 4
            rest = 0; //Stockage du reste
            result = 0; //Stockage de la valeur divisée
            cnt = 0; //Parcours du tableau +4

            for(i = 0; i < (SIZE * 8) / 4; i++){

                if(i > 0)
                    cnt += 4; //Si i > 0, cnt va permettre de se déplacer à tab_bits[k + 4]

                    for(k = 3; k >= 0; k--){ //Commencer à partir de tab_bits[4]
                        rest = tab_hexa_change[i] % 2; //Récupère le reste
                        result = tab_hexa_change[i];
                        result /= 2; //On divise la valeur par 2
                            if(rest == 0){
                                tab_bits_hexa[k + cnt] = 0;
                                tab_hexa_change[i] = result; //Initialisation de la valeur divisée par 2 dans le tableau

                            }else{
                                tab_bits_hexa[k + cnt] = 1;
                                tab_hexa_change[i] = result; //Initialisation de la valeur divisée par 2 dans le tableau

                            }

                    }
            }

            cnt = 0;
            printf("T = ");
            for(i = 0; i < SIZE*8; i++){
                printf("%d", tab_bits_hexa[i]); //Affichage du tableau binaire
                cnt++;
                if(cnt == 4){
                    printf(" ");
                    cnt = 0;
                }
            }
            printf("\n\n");

            FILE *matrix = NULL;
            matrix = fopen("key.txt", "r+");
            char matrix_array[50];
            if(matrix != NULL){

                fgets(matrix_array, 50, matrix);
                printf("   %s", matrix_array);
                size = 0;
                size = strlen(matrix_array);
                printf("\n   *TAILLE DE LA MATRICE: %d", size);

                j = 0;
                for(i = 5; i < size-1; i++){
                    tab_file[j] = matrix_array[i];
                    j++;

                }
                printf("\n");
                //SUPPRESSION DES ESPACES
                for(j = 0; j < 35; j++){
                    deleteSpace(tab_file);
                    //printf("%c", tab_file[j]);
                }

                //MATRICE G4,8: TABLEAU A DEUX DIMENSIONS
                k = 0;
                cnt = 0;
                printf("\n   MATRICE G4:\n\n   ");
                for(i = 0; i < 4; i++){
                    for(j = 0; j < 8; j++){
                        key[i][j] = tab_file[k] - 48;
                        k++;
                        printf("%d", key[i][j]);
                        cnt++;
                        if(cnt == 8){
                            printf("\n   ");
                            cnt = 0;
                        }
                    }
                }
                //CALCUL DES SOUS MESSAGES
                 printf("\n   CALCUL DES SOUS-MESSAGES X:\n\n   ");
                //CALCUL DU PRODUIT+SOMME MATRICIEL
                cnt = 0; //Garde en mémoire
                int lines = 0;
                int columns = 0;
                int product = 0;

                for(i = 0; i < (SIZE*4)/2; i++){ //(12 * 4) / 3

                    for(columns = 0; columns < 8; columns++){

                        product = 0;
                        for(lines = 0; lines < 4; lines++){
                            product += tab_bits_hexa[cnt + lines] * key[lines][columns];
                        }
                        if(product % 2 == 0){
                            convert_array[i][columns] = 0; //Attribue 0

                        }else{
                            convert_array[i][columns] = 1; //Attribue 1

                        }
                    }
                    cnt += 4; //Permet d'avancer de +3
                }
                cnt = 0;
                k = 0;
                result = 0;
                for(i = 0; i < (SIZE*4)/2; i++){
                    k++;
                    printf("X%d = ", k);
                    for(j = 0; j < 8; j++){
                        printf("%d", convert_array[i][j]);
                        all_submessages[result] = convert_array[i][j];
                        cnt++;
                        result++;
                        if(cnt == 8){
                            printf("\n   ");
                            cnt = 0;
                        }
                    }
                }
                printf("\n\n");
                printf("   CONVERSION DES SOUS-MESSAGES:\n   ");
                cnt = 0;
                printf("X = ");
                for(i = 0; i < ((SIZE*4)/2)*8; i++){
                    printf("%d", all_submessages[i]); //Affichage du tableau binaire
                    cnt++;
                    if(cnt == 4){
                        printf(" "); //Affichage d'un espace tous les 3 chiffres
                        cnt = 0;
                    }
                }
                printf("\n\n   MESSAGE FINAL:\n   ");
                printf("X = (");
                result = 0;
                cnt = 0;
                cnt2 = 0;
                k = 0;
                for(i = 0; i < SIZE*4; i ++){

                    for(j = 0; j < 4; j++){
                        result += bits[j] * all_submessages[cnt];
                        cnt++;

                        if(j == 3){
                            if(result >= 0 && result <= 9){ //0 à 9
                                result = result + 48;
                                //printf("result = %d", result);
                                all_submessages[k] = result;
                                printf("%c", all_submessages[cnt2]);
                                cnt2++;
                                k++;
                                result = 0;
                            }else if(result >= 10 && result <= 15){ //a à f
                                result = result + 55;
                                //printf("result = %d", result);
                                all_submessages[k] = result;
                                printf("%c", all_submessages[cnt2]);
                                cnt2++;
                                k++;
                                result = 0;
                            }
                        }
                    }
                }
                printf(")h");
                FILE * crypted_file = NULL;
                crypted_file = fopen("crypted_file.txt", "a+");

                fclose(matrix);

            }else{
                printf("\n   ERREUR DE CHARGEMENT DE FICHIER...\n\n   ");
            }


            break;
        case 2:
            break;
        case 3:
            break;
        default:
            printf("\nERREUR");
            break;



        }
    }
    return 0;
}
int deleteSpace(char * str){
    char * ptr = str;
    while((ptr = strchr(ptr, ' ')) != NULL){
        strcpy(ptr, ptr + 1);
    }
}
