#include "tp1.h"
#include <stdio.h>
#include <string.h>

void pingHote_Exo1()
{

    char adr_ip[30], command[50];
    printf("Entrez l'adresse ip/hote que vous souhaitez ping : ");
    scanf("%s", adr_ip);
    command[0] = '\0';
    strcat(command, "ping -c 5 ");
    strcat(command, " ");
    strcat(command, adr_ip);
    system(command);
}

void calculPourcentagePacket_Exo2()
{
    FILE *fp;
    char buffer[20];
    char packet_receiv[10], packet_transm[10], packet_loss[10];
    char time_delai[20], adr_ip[30], command[50], temp[20];

    printf("Entrez l'adresse ip/hote que vous souhaitez ping : ");
    scanf("%s", adr_ip);
    command[0] = '\0';
    strcat(command, "ping -c 5 ");
    strcat(command, " ");
    strcat(command, adr_ip);
    strcat(command, "|grep packets");

    fp = popen(command, "r");

    if (fp == NULL)
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s", buffer) != EOF)
    {
        if (strcmp(buffer, "packets") == 0)
        {
            strcpy(packet_transm, temp);
        }
        if (strcmp(buffer, "received,") == 0)
        {
            strcpy(packet_receiv, temp);
        }
        if (strcmp(buffer, "packet") == 0)
        {
            strcpy(packet_loss, temp);
        }
        strcpy(temp, buffer);
        printf("%s\t", buffer);
    }

    strcpy(time_delai, temp);

    printf("\n==========================================================\n");
    printf("Le packet tansmit (Transmitted) est : %s\n", packet_transm);
    printf("Le packet reçu (received) est : %s\n", packet_receiv);
    printf("Le packet perdu (loss) est : %s\n", packet_loss);
    printf("Le temps aller - retour (delai) : %s\n", time_delai);
    printf("\n==========================================================\n");
    pclose(fp);
}

void lectureFichierIp_Exo3()
{
    FILE *fichier;
    fichier = fopen("test", "r");

    // Vérifier si le fichier est ouvert avec succès
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        doPing(ligne);
    }
    fclose(fichier);
}

static void doPing(char *addr_ip)
{
    char buffer[50], received[30], command[50], temp[20];
    FILE *fp;
    command[0] = '\0';
    strcat(command, "ping -c 3 ");
    strcat(command, " ");
    addr_ip[strlen(addr_ip) - 1] = '\0';
    strcat(command, addr_ip);
    strcat(command, "|grep packets");
    // printf("Commande : %s\n", command);
    // return;
    fp = popen(command, "r");

    if (fp == NULL)
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s", buffer) != EOF)
    {

        if (strcmp(buffer, "received,") == 0)
        {
            printf("%s  ==> %s,\t", addr_ip, temp);
        }
        strcpy(temp, buffer);
    }
    printf("%s\n", temp);
}