
#include "reseau.h"


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
//Vérifie si l'IP est correcte (typo)
//testé et approuvé !
int VerifValeursIP(char *cAddrIP)
{
int nIP[4];

//Récup des 'ip séparées'
sscanf(cAddrIP, "%d.%d.%d.%d", &nIP[0], &nIP[1], &nIP[2], &nIP[3]);

if(nIP[0]<=255 && nIP[0]>=0
   && nIP[1]<=255 && nIP[1]>=0
   && nIP[2]<=255 && nIP[2]>=0
   && nIP[3]<=255 && nIP[3]>=0)
	{
	return 1;
	}
return 0;
}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
//Vérifie si le port est correct (entre 5000 et 6000)
//testé et approuvé !
int VerifValeursPort(int *nPort)
{
if(*nPort<=6000 && *nPort>=5000)
	{
	return 1;
	}
return 0;
}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
//Menu pour changer les parametres du config.cfg
//testé et approuvé !
int MenuChangerConfig()
{
int bBypass = 0;
char cIP[20];
int nPortRecev, nPortSend;

char cOldIP[20];
int nOldPortRecev, nOldPortSend;


GetConfig(cOldIP, &nOldPortRecev, &nOldPortSend);


printf("|\n");
printf("O======== Changer la configuration ===========================================O");

while(!bBypass)
	{
	printf("\n| Entrez l'adresse IP [%s] : ", cOldIP);
	scanf(" %s", cIP);

	if(VerifValeursIP(cIP))
		{break;}
	else
		{
		printf("| ->(?) L'adresse IP doit être de la forme 'x.x.x.x' avec 0 <= x <= 255");
		}
	}
printf("|");
while(!bBypass)
	{
	printf("\n| Entrez le port d'emmission [%d] : ", nOldPortRecev);
	scanf(" %d", &nPortSend);

	if(VerifValeursPort(&nPortSend))
		{break;}
	else
		{
		printf("| ->(?) Les ports doivent être compris entre 5000 et 6000 inclus");
		}
	}
printf("|");
while(!bBypass)
	{
	printf("\n| Entrez le port de reception [%d] : ", nOldPortSend);
	scanf(" %d", &nPortRecev);

	if(VerifValeursPort(&nPortRecev))
		{break;}
	else
		{
		printf("| ->(?) Les ports doivent être compris entre 5000 et 6000 inclus");
		}
	}

return SetConfig(cIP, nPortSend, nPortRecev);
}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
//Change le fichier de config pour y mettre de nouvelles valeures
//Vérifie les valeurs avant de les appliquer
//retourne 1 quand set réussi, sinon 0 et affichage d'un message d'erreur
//testé et approuvé !
int SetConfig(char *cAddrIP, int nPortSend, int nPortRecev)
{
FILE *FConfig;

if(!VerifValeursIP(cAddrIP)
   && !VerifValeursPort(&nPortSend)
   && !VerifValeursPort(&nPortRecev))
	{
	return 0;
	}

//Ouverture pour réécriture du config.cfg
FConfig = fopen("config.cfg", "w+");

fprintf(FConfig, "adresse=%s\n", cAddrIP);
fprintf(FConfig, "portsend=%d\n", nPortSend);
fprintf(FConfig, "portrecev=%d\n", nPortRecev);

fclose(FConfig);
return 1;
}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
//Change le fichier de config pour y mettre de nouvelles valeures
//Vérifie les valeurs avant de les appliquer
//retourne 1 quand set réussi, sinon 0 et affichage d'un message d'erreur
//testé et approuvé !
int GetConfig(char *cAddrIP, int *nPortSend, int *nPortRecev)
{
FILE *FConfig;
char cAddrIPTemp[20];
int nPortSendTemp, nPortRecevTemp;
int i;

FConfig = fopen("config.cfg", "r");
if(FConfig == NULL)
	{
	printf("=====> Erreur GetConfig : 404 file not found :oP\n");
	return 0;
	}

//Recup des valeurs
fscanf(FConfig, "adresse=%s\n", cAddrIPTemp);
fscanf(FConfig, "portsend=%d\n", &nPortSendTemp);
fscanf(FConfig, "portrecev=%d\n", &nPortRecevTemp);


fclose(FConfig);


//Assignations aux arguments de la fonction
for(i=0 ; i<20 ; i++)
	{
	cAddrIP[i] = cAddrIPTemp[i];
	}
*nPortSend = nPortSendTemp;
*nPortRecev = nPortRecevTemp;

return 1;
}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
// Initialisation de la socket
// dediee a la reception
// parametre d'entree:
//    port_recv: port de reception
// valeur de retour: 1 si reussi
//                   0 si echec
int init_socket_recv(int port_recv)
{
    if ((sock_recv=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        printf("Error : socket");

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port_recv);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock_recv, (struct sockaddr *) &si_me, (int) sizeof(si_me))==-1)
    {
        printf("Error : bind");
        return 0;
    }
    return 1;
}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
// Initialisation de la socket
// dediee a l'envoi
// parametre d'entree:
//    port_send: port d'envoi
//    addr_ip: adresse ip de l'adversaire
// valeur de retour: 1 si reussi
//                   0 si echec
int init_socket_send(int port_send, const char* addr_ip)
{
    if ((sock_send=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        printf("Error : socket");

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(port_send);
    if (inet_aton(addr_ip, (struct in_addr *) &si_other.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
        return 0;
    }
	return 1;
}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
// Reception de la position i,j
int receive_position(int* i, int* j)
{
	char* commaPos;
	int iCommaPos;
    char buf[BUFLEN];
	printf(".");
    if (recv(sock_recv, buf, BUFLEN, 0)==-1)
        printf("Error : recvfrom()");
    *i = atoi(buf);
	commaPos = strchr(buf,',');
	iCommaPos = commaPos - buf + 1;
	*j = atoi(buf+iCommaPos);
	return 1;
}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
// Envoi de la position i,j
int send_position(int i, int j)
{
    char buf[BUFLEN];
    int slen=sizeof(si_other);
    sprintf(buf, "%d,%d", i,j);
    if (sendto(sock_send, buf, BUFLEN, 0, (struct sockaddr *) &si_other, slen)==-1)
        printf("Error : sendto()");
	return 1;
}
