#include "tp1.h"
#include <stdio.h>
#include <string.h>

void pingHote_Exo1(){

    char adr_ip[30],command[50] ;  
    printf("Entrez l'adresse ip/hote que vous souhaitez ping : ");
    scanf("%s",adr_ip);
    command[0] = '\0'; 
    strcat(command,"ping -c 5 ");
    strcat(command," ");
    strcat(command,adr_ip);
    system(command);

}

void test(){
    FILE *fp;
    char buffer[20];
    char packet_receiv[10] ,packet_transm[10] ,packet_loss[10] ;
    char time_delai[20],adr_ip[30], command[50], temp[20] ;

    printf("Entrez l'adresse ip/hote que vous souhaitez ping : ");
    scanf("%s",adr_ip);
    command[0] = '\0'; 
    strcat(command,"ping -c 5 ");
    strcat(command," ");
    strcat(command,adr_ip);
    strcat(command,"|grep packets");

    fp = popen(command, "r"); 

    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s", buffer) != EOF) {
        if(strcmp(buffer,"packets") == 0){
            strcpy(packet_transm,temp);
        }
        if(strcmp(buffer,"received,") == 0){
            strcpy(packet_receiv,temp);
        }
        if(strcmp(buffer,"packet") == 0){
            strcpy(packet_loss,temp);
        }
        strcpy(temp, buffer);
        printf("%s\t", buffer);
    }

    strcpy(time_delai,temp);

    printf("\nLe packet tansmit (Transmitted) est : %s\n",packet_transm);
    printf("Le packet reçu (received) est : %s\n",packet_receiv);
    printf("Le packet perdu (loss) est : %s\n",packet_loss);
    printf("Le temps aller - retour (delai) : %s\n",time_delai);
    pclose(fp);

}

