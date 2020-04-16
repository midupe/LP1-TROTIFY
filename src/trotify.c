#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mainmenu(void){
	printf("***********\n");
	printf("* Trotify *\n");
	printf("***********\n");
	printf("1.\n");
	printf("\ta. user read_file <path>\n");
	printf("\tb. user read_file\n");
	printf("2.\n");
	printf("\ta. maint read_file <path>\n");
	printf("\tb. maint read_file\n");
	printf("3.\n");
	printf("\ta. save_current_data <path>\n");
	printf("\tb. save_current_data\n");
	printf("4. user insert <name> <user_id> <card_number> <number_of_trip> <number_of_km>\n");
	printf("5. user find_nearest_vehicle <user_position_x> <user_position_y>\n");
	printf("6. maint insert <vehicle_id> <position_x> <position_y> <charge> <km_until_maintenance>\n");
	printf("7. maint need_to_charge\n");
	printf("8. maint need_maintenance\n");
	printf("9. user delete <user_id>\n");
	printf("10. maint delete <vehicle_id>\n");
	printf("11. user make_trip <user_id> <vehicle_id> <end_position_x> <end_position_y>\n");
    printf("12. maint charge_vehicle <vehicle_id>\n");
    printf("13. maint charge_all_vehicles\n");
    printf("14. maint make_maintenance <vehicle_id>\n");
    printf("15. maint make_maintenance_all_vehicles\n");
	printf("16. h\n");
	printf("17. q\n");
}

/* Estrutura Users */
typedef struct sUsers
{
    char nome[62+1];
    char apelido[62+1];
    char userID[15+1];
    char creditCard[24+1];
    int numViagens;
    int km;
    struct sUsers *prox;
} USERS;
typedef USERS* ULINK;

/* Estrutura Trotinetes */
typedef struct sTrot
{
    char trotID[31+1];
    int xpos;
    int ypos;
    int carga;
    int manKM;
    struct sTrot *prox;
} TROT;
typedef TROT *TLINK;

/* Iniciar lista Users */
void inic_u(ULINK* ulink)
{
    *ulink = NULL;
}

/* Iniciar lista Trotinetes */
void inic_t(TLINK*tlink)
{
    *tlink = NULL;
}

/* Inserir User */
void inserir_u(ULINK * ulink, char* nome, char* apelido, char* userID, char* creditCard, int numViagens, int km)
{
    if(*ulink == NULL)
    {
        *ulink = (ULINK) malloc(sizeof(USERS));
        if (*ulink==NULL)
            return;
        strcpy((*ulink)-> nome, nome);
        strcpy((*ulink)-> apelido, apelido);
        strcpy((*ulink)-> userID, userID);
        strcpy((*ulink) -> creditCard, creditCard);
        (*ulink) -> numViagens = numViagens;
        (*ulink) -> km = km;
        (**ulink).prox=NULL;
    }
    else
        inserir_u(&(**ulink).prox, nome, apelido, userID, creditCard, numViagens, km);
}

/* Inserir Trotinete */
void inserir_t(TLINK * tlink, char* trotID, int xpos, int ypos, int carga, int manKM)
{
    if(*tlink == NULL)
    {
        *tlink = (TLINK) malloc(sizeof(TROT));
        if (*tlink==NULL)
            return;
        strcpy((*tlink) -> trotID, trotID);
        (*tlink) -> xpos = xpos;
        (*tlink) -> ypos = ypos;
        (*tlink) -> carga = carga;
        (*tlink) -> manKM = manKM;
        (**tlink).prox=NULL;
    }
    else
        inserir_t(&(**tlink).prox, trotID, xpos, ypos, carga, manKM);
}

/* Listar Users */
void listar_u(ULINK ulink)
{
    if(ulink==NULL)
        return;
    printf("%s %s %s %s %d %d\n", ulink->nome, ulink->apelido, ulink->userID, ulink->creditCard, ulink->numViagens, ulink->km);
    listar_u(ulink->prox);
}

/* Listar Trotinetes */
void listar_t(TLINK tlink)
{
    if(tlink==NULL)
        return;
    printf("%s %d %d %d %d\n", tlink->trotID, tlink->xpos, tlink->ypos, tlink->carga, tlink->manKM);
    listar_t(tlink->prox);
}

/* Procurar Users */
int search_u (USERS*ulink, char*userID)
{
    int count=-1;
    while (ulink!=NULL)
    {
        count++;
        if (strcmp(ulink->userID, userID)==0)
        {
            return count;
        } else ulink = ulink->prox; 
    }
    return -1;
}

/* Procurar Trotinetes */
int search_t (TROT *tlink, char*trotID)
{
    int count=-1;
    while (tlink!=NULL)
    {
        count++;
        if (strcmp(tlink->trotID, trotID)==0)
        {
            return count;
        } else tlink = tlink->prox; 
    }
    return -1;
}

/* Adicionar Users */
void user_insert(ULINK* ulink)
{
	char Nome[127];
	char Apelido[127];
	char ID[127];
    char CreditCard[127];
    int NumViagens;
    int KM;
	int dados=0;
	scanf("%s %s %s %s %d %d", Nome, Apelido ,ID, CreditCard, &NumViagens, &KM);
			if(search_u(*ulink, ID)==-1)
            {
				dados=1;
            } else printf("User ID already exists\n");
            if (strlen(CreditCard)!=24 || strlen(ID)!=15)
            {
				printf("Bad arguments\n");
                dados=0;
            }
			if (dados==1) inserir_u(ulink, Nome, Apelido, ID, CreditCard, NumViagens, KM);
}

/* Adicionar Trotinetes */
void maint_insert(TLINK* tlink)
{
	char trotID[127];
    int xpos;
    int ypos;
    int carga;
    int manKM;
	int dados=0;
	scanf("%s %d %d %d %d", trotID, &xpos, &ypos, &carga, &manKM);
			if(search_t(*tlink, trotID)==-1)
            {
				dados=1;
            } else printf("Vehicle ID already exists\n");
            if (strlen(trotID)!=31 || carga<0 || carga>100)
            {
				printf("Bad arguments\n");
                dados=0;
            }
			if (dados==1) inserir_t(tlink, trotID, xpos, ypos, carga, manKM);
} 

/* Remover Users */
void apagar_u(USERS **ulink, int position)
{
    USERS *tmp=*ulink;
    USERS *prox = tmp->prox; 
    int i;
    if (*ulink==NULL)
        return;
    if (position==0)
    {
        *ulink=tmp->prox;
        free(tmp);
        return;
    }
    for (i=0; tmp!=NULL && i<position-1; i++) 
        tmp = tmp->prox; 
    if (tmp == NULL || tmp->prox == NULL) 
        return; 
    prox = tmp->prox->prox;
    free(tmp->prox); 
    tmp->prox = prox;
}
void user_delete(ULINK* ulink)
{
    char ID[127];
    scanf("%s", ID);
    if(search_u(*ulink, ID)!=-1)
    {
		apagar_u(ulink, search_u(*ulink, ID));
        printf("User %s removed\n",ID);
    } else
        printf("User ID does not exist\n");
}

/* Remover Trotinetes */
void apagar_t(TROT **tlink, int position)
{
    TROT *tmp=*tlink;
    TROT *prox = tmp->prox; 
    int i;
    if (*tlink==NULL)
        return;
    if (position==0)
    {
        *tlink=tmp->prox;
        free(tmp);
        return;
    }
    for (i=0; tmp!=NULL && i<position-1; i++) 
        tmp = tmp->prox; 
    if (tmp == NULL || tmp->prox == NULL) 
        return; 
    prox = tmp->prox->prox;
    free(tmp->prox); 
    tmp->prox = prox;
}
void maint_delete(TLINK* tlink)
{
    char ID[127];
    scanf("%s", ID);
    if(search_t(*tlink, ID)!=-1)
    {
		apagar_t(tlink, search_t(*tlink, ID));
        printf("Vehicle %s removed\n",ID);
    } else 
        printf("Vehicle ID does not exist\n");
}

/* Viagem Users */
int trip_startPosX (TROT*tlink, char*ID)
{
    while (tlink!=NULL)
    {
        if (strcmp(tlink->trotID, ID)==0)
        {
            return tlink->xpos;
        } else tlink = tlink->prox; 
    }
    return -1;
}
int trip_startPosY (TROT*tlink, char*ID)
{
    while (tlink!=NULL)
    {
        if (strcmp(tlink->trotID, ID)==0)
        {
            return tlink->ypos;
        } else tlink = tlink->prox; 
    }
    return -1;
}
int trip_carga (TROT*tlink, char*ID)
{
    while (tlink!=NULL)
    {
        if (strcmp(tlink->trotID, ID)==0)
        {
            return tlink->carga;
        } else tlink = tlink->prox; 
    }
    return -1;
}
int trip_manKm (TROT*tlink, char*ID)
{
    while (tlink!=NULL)
    {
        if (strcmp(tlink->trotID, ID)==0)
        {
            return tlink->manKM;
        } else tlink = tlink->prox; 
    }
    return -1;
}
void trip_saveUser(USERS*ulink, char*ID, int d)
{
    while (ulink!=NULL)
    {
        if (strcmp(ulink->userID, ID)==0)
        {
            ulink->numViagens++;
            ulink->km+=d;
            return;
        } else ulink = ulink->prox; 
    }
}
void trip_saveTrot(TROT*tlink, char*ID, int endPosX, int endPosY, int cargafinal, int kmuntilm)
{
    while (tlink!=NULL)
    {
        if (strcmp(tlink->trotID, ID)==0)
        {
            tlink->xpos = endPosX;
            tlink->ypos = endPosY;
            tlink->carga = cargafinal;
            tlink->manKM = kmuntilm;
            return;
        } else tlink = tlink->prox; 
    }
}
void user_maketrip(ULINK *ulink, TLINK *tlink)
{
    char userID[127];
    char trotID[127];
    int endPosX;
    int endPosY;
    int startPosX = -1;
    int startPosY = -1;
    int cargainicial = -1;
    int d;
    float fracao;
    int cargafinal;
    float dv;
    float preco;
    int kmuntilm=0;
    scanf("%s %s %d %d", userID, trotID, &endPosX, &endPosY);
    if (search_u(*ulink,userID)!=-1 && search_t(*tlink,trotID)!=-1)
    {
        startPosX = trip_startPosX(*tlink, trotID);
        startPosY = trip_startPosY(*tlink, trotID);
        cargainicial = trip_carga(*tlink, trotID);
        kmuntilm = trip_manKm(*tlink, trotID);
        dv = ((startPosX-endPosX)*(startPosX-endPosX)+(startPosY-endPosY)*(startPosY-endPosY));
        dv=sqrt(dv);
        d=ceil(dv);
        fracao=(d/30.00);
        cargafinal = (cargainicial-100*fracao);
        preco=(0.25*d+0.5);
        kmuntilm-=d;
        if (cargafinal<0)
        {
            printf("Not possible to make such a long trip with this vehicle's charge\n");
            return;
        }
        trip_saveUser(*ulink, userID, d);
        trip_saveTrot(*tlink, trotID, endPosX, endPosY, cargafinal, kmuntilm);
        printf("%d %05.2f %d %d\n", d, preco, kmuntilm, cargafinal);
    } else printf("Bad arguments\n");
}

/* Enontrar Trotinete mais próximo de User */
int calcdistancia(int x1,int x2,int y1,int y2)
{
    float d;
    int dv;
    d=((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    d=sqrt(d);
    dv=ceil(d);
    return dv;
}
void user_find_nearest_vehicle(TLINK tlink)
{
    int userPosX;
    int userPosY;
    char trotinete[32];
    int trotPosX;
    int trotPosY;
    int calc;
    int distancia=2147483647;
    int count=0;
    scanf("%d %d", &userPosX, &userPosY);
    while (tlink!=NULL)
    {
        if ((tlink->carga)>20 && (tlink->manKM)>3)
        {
            trotPosX=((tlink)->xpos);
            trotPosY=((tlink)->ypos);
            calc=calcdistancia(userPosX,trotPosX,userPosY,trotPosY);
            if (calc<distancia)
            {
                distancia=calc;
                strcpy(trotinete, tlink->trotID);
                count++;
            }
        }
        tlink = tlink->prox; 
    }
    if (count!=0)
    {
        printf("%s\n",trotinete);
    } else printf("No vehicle in memory\n");
        
}

/* Trotinetes com baixa carga */
void need_to_charge(TLINK tlink)
{
    int count=0;
    while(tlink!=NULL)
    {
        if(tlink->carga<20)
        {
            count++;
            printf("%s\n", tlink->trotID);
        }
        tlink=tlink->prox;
    }
    if(count==0)
        printf("No vehicle needs to charge\n");
}

/* Trotinetes que precisam manutenção */
void need_maintenance(TLINK tlink)
{
    int count=0;
    while (tlink!=NULL)
    {
        if(tlink->manKM<3 || tlink->carga<20)
        {
            count++;
            printf("%s\n", tlink->trotID);
        }
        tlink=tlink->prox;
    }
    if (count==0)
        printf("No vehicle needs maintenance\n");
}

/* Ler ficheiro utilizadores */
void user_read_file(int argc, char*argv[], char fichiroIntrod[512], ULINK *ulink)
{
    char fname[512], temp[512];
    int i=1;
    char nome[62+1];
    char apelido[62+1];
    char userID[15+1];
    char creditCard[24+1];
    int numViagens;
    int km;
    int dados=0;
    FILE *fp;
    strcpy(temp, fichiroIntrod);
    if (argc==2)
    {
        strcpy(fname, argv[1]);
        strcat(fname, ".users");
    } else
    {
        if (temp[0]=='\0'){
            printf("No path to file defined\n");
            return;
        }
        strcpy(fname,temp);
        strcat(fname, ".users");
        strcpy(temp, fname);
        while(temp[i-1]!='\0')
        {
            fname[i-1]=temp[i];
            i++;
        }
    }
    fp = fopen(fname,"r");
    if(fp==NULL)
    {
        return;
    }
    while(fscanf(fp,"%s %s %s %s %d %d", userID, nome, apelido, creditCard, &numViagens, &km)!=EOF)
    {
        if (search_u(*ulink, userID)!=-1)
            dados=1;
        if (strlen(creditCard)!=24 || strlen(userID)!=15)
            dados=1; 
        if (dados==0)
            inserir_u(ulink, nome, apelido, userID, creditCard, numViagens, km);
    }
    fclose(fp);
}

/* Ler ficheiro trotinetes */
void maint_read_file(int argc, char*argv[], char fichiroIntrod[512], TLINK *tlink)
{
    char fname[512], temp[512];
    int i=1;
    char trotID[31+1];
    int xpos;
    int ypos;
    int carga;
    int manKM;
    int dados=0;
    FILE *fp;
    strcpy(temp, fichiroIntrod);
    if (argc==2)
    {
        strcpy(fname, argv[1]);
        strcat(fname, ".trotinetes");
    } else
    {
        if (temp[0]=='\0'){
            printf("No path to file defined\n");
            return;
        }
        strcpy(fname,temp);
        strcat(fname, ".trotinetes");
        strcpy(temp, fname);
        while(temp[i-1]!='\0')
        {
            fname[i-1]=temp[i];
            i++;
        }
    }
    fp = fopen(fname,"r");
    if(fp==NULL)
    {
        return;
    }
    while(fscanf(fp,"%s %d %d %d %d", trotID, &xpos, &ypos, &carga, &manKM)!=EOF)
    {
        if (search_t(*tlink, trotID)!=-1)
            dados=1;
        if (strlen(trotID)!=31 || carga<0 || carga>100)
            dados=1; 
        if (dados==0)
            inserir_t(tlink, trotID, xpos, ypos, carga, manKM);
    }
    fclose(fp);
}

/* Salvar dados */
void save_current_data(int argc, char*argv[], char fichiroIntrod[512], ULINK ulink, TLINK tlink)
{
    char fname[512], temp[512], fuser[512], ftrot[512];
    int i=1;
    FILE *fpu, *fpt;
    strcpy(temp, fichiroIntrod);
    if (argc==2)
    {
        strcpy(fname, argv[1]);
    } else
    {
        if (temp[0]=='\0'){
            printf("No path to file defined\n");
            return;
        }
        strcpy(fname,temp);
        strcpy(temp, fname);
        while(temp[i-1]!='\0')
        {
            fname[i-1]=temp[i];
            i++;
        }
    }
    strcpy(fuser, fname);
    strcpy(ftrot, fname);
    strcat(fuser, ".userout");
    strcat(ftrot, ".trotinetesout");
    fpu = fopen(fuser,"w");
    if(fpu==NULL)
    {
        return;
    }
     while (ulink!=NULL)
    {
        fprintf(fpu, "%s ", ulink->userID);
        fprintf(fpu, "%s ", ulink->nome);
        fprintf(fpu, "%s ", ulink->apelido);
        fprintf(fpu, "%s ", ulink->creditCard);
        fprintf(fpu, "%d ", ulink->numViagens);
        fprintf(fpu, "%d\n", ulink->km);
        ulink=ulink->prox;        
    }
    fclose(fpu);
    fpt = fopen(ftrot,"w");
    if(fpt==NULL)
    {
        return;
    }
    while (tlink!=NULL)
    {
        fprintf(fpt, "%s ", tlink->trotID);
        fprintf(fpt, "%d ", tlink->xpos);
        fprintf(fpt, "%d ", tlink->ypos);
        fprintf(fpt, "%d ", tlink->carga);
        fprintf(fpt, "%d\n", tlink->manKM);
        tlink=tlink->prox;
    }
    fclose(fpt);
}

/* Carregar Trotinete */
void chargeVehicle(TLINK tlink)
{
    char id[512];
    scanf("%s",id);
    if (strlen(id)!=31)
    {
        printf("Bad arguments\n");
        return;
    }
    if (search_t(tlink, id)==-1)
    {
        printf("Vehicle ID does not exist\n");
        return;
    }
    tlink -> carga = 100;
}

/* Carregar Todas as Trotinetes */
void chargeAllVehicles(TLINK tlink)
{
    while (tlink!=NULL){
        if (tlink->carga<20)
            tlink -> carga = 100;
        tlink = tlink->prox;
    }
}

/* Fazer Manutenção Trotinetes */
void makeMaintenance(TLINK tlink)
{
    char id[512];
    scanf("%s",id);
    if (strlen(id)!=31)
    {
        printf("Bad arguments\n");
        return;
    }
    if (search_t(tlink, id)==-1)
    {
        printf("Vehicle ID does not exist\n");
        return;
    }
    tlink -> manKM = 50;
}

/* Fazer Manutenção a Todas Trotinetes */
void makeAllMaintenance(TLINK tlink)
{
    while (tlink!=NULL){
        if (tlink->manKM<3)
            tlink -> manKM = 50;
        tlink = tlink->prox;
    }
}

int main(int argc, char*argv[])
{
    ULINK ulink;
    TLINK tlink;
	char tipo[18], comando[21], string[512];
	int dados=2;
    inic_u(&ulink);
    inic_t(&tlink);
	mainmenu();
	while(dados!=1){
	    scanf("%s", tipo);
        if (strcmp(tipo, "user")==0 || strcmp(tipo, "maint")==0 || strcmp(tipo, "h")==0 || strcmp(tipo, "q")==0 || strcmp(tipo, "save_current_data")==0)
        {
            if (strcmp(tipo, "user")==0)
            {
		        scanf("%s", comando);
                if (strcmp(comando, "read_file")==0 || strcmp(comando, "insert")==0 || strcmp(comando, "delete")==0 || strcmp(comando, "make_trip")==0 || strcmp(comando, "find_nearest_vehicle")==0)
                {
                    if (strcmp(comando, "read_file")==0) 
                    {
                        scanf("%[^\n]", string);
                        user_read_file(argc, argv, string, &ulink);
                    }
		            if (strcmp(comando, "insert")==0) user_insert(&ulink);
                    if (strcmp(comando, "delete")==0) user_delete(&ulink);
                    if (strcmp(comando, "make_trip")==0) user_maketrip(&ulink,&tlink);
		            if (strcmp(comando, "find_nearest_vehicle")==0) user_find_nearest_vehicle(tlink);
                } else dados=0;
	        }
	        if (strcmp(tipo, "maint")==0)
            {
	    	    scanf("%s", comando);
                if (strcmp(comando, "make_maintenance_all_vehicles")==0 || strcmp(comando, "make_maintenance")==0 || strcmp(comando, "charge_all_vehicles")==0 || strcmp(comando, "charge_vehicle")==0 || strcmp(comando, "read_file")==0 || strcmp(comando, "insert")==0 || strcmp(comando, "delete")==0 || strcmp(comando, "need_to_charge")==0 || strcmp(comando,"need_maintenance")==0)
                {
	    	        if (strcmp(comando, "read_file")==0)
                    {
                        scanf("%[^\n]", string);
                        maint_read_file(argc, argv, string, &tlink);
                    }
	    	        if (strcmp(comando, "insert")==0) maint_insert(&tlink);
                    if (strcmp(comando, "delete")==0) maint_delete(&tlink);
	    	        if (strcmp(comando, "need_to_charge")==0) need_to_charge(tlink);
	    	        if (strcmp(comando, "need_maintenance")==0) need_maintenance(tlink);
                    if (strcmp(comando ,"charge_vehicle")==0) chargeVehicle(tlink);
                    if (strcmp(comando ,"charge_all_vehicles")==0) chargeAllVehicles(tlink);
                    if (strcmp(comando ,"make_maintenance")==0) makeMaintenance(tlink);
                    if (strcmp(comando ,"make_maintenance_all_vehicles")==0) makeAllMaintenance(tlink);
                } else dados=0;
	        }
	        if (strcmp(tipo, "save_current_data")==0)
            {
                scanf("%[^\n]", string);
                save_current_data(argc, argv, string, ulink, tlink);
            }
	        if (strcmp(tipo, "h")==0){
                mainmenu();
                dados=2;
            }
	        if (strcmp(tipo, "q")==0)
            {
                exit(0);
                dados=1;
            }
        } else dados=0;
        if(dados==0)
        {
            dados=2;
            scanf("%[^\n]", string);
            printf("Bad arguments\n");
        }
	}
	return (0);
}
