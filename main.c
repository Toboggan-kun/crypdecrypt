#include <stdio.h>
#include <stdlib.h>
#define SIZE_MAX 500

char *one_dimension_char(char *, int);
int main(int argc, char ** argv){


    char *text_array = NULL;
    char *container = NULL;
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
        printf("MESSAGE: ");
        while(text_array[i] != '\0'){
            fread(&text_array, sizeof(char), 1, text);
            printf("%c", text_array[i]);
            i++;
            cnt++;

        }

        printf("%s", container);
        printf("%s", text_array);
        size_array = cnt;

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


                    free(text_array);


                    break;
                case 2:
                    break;
                case 3:

                    break;
                default:
                    printf("\nERREUR");
                    break;
            }
        free(container);
        free(text_array);
        fclose(text);
        }
    }else{
        printf("\n\nECHEC DU CHARGEMENT DU FICHIER...");
    }

    return 0;
}


char *one_dimension_char( char *name, int size ){

    char *string = malloc(sizeof(char) * size);

    string[0] = '\0';

    name = string;

    return name;
}
