#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#define MAX 1000 


struct administrator{
	int id;
	char fjalekalimi[15];
};

struct sekretaria {
	char emer[20];
	char mbiemer[20];
	int emerp;
	char fjalekalimi[15];
};

struct lenda{
	int id;
	char emer[20];
	int numri_studenteve;
	int id_s[MAX];
	int id_k[MAX];
};


struct klasa{
	char id[5];
	char *emer[3];
	int viti;
	char grupi;	
};

struct nota{
	int id;
	int nota;
};


struct student {
	int  id;
	char emer[20];
	char mbiemer[20];
	char fjalekalimi[15];
	int mosha;
	struct klasa klasa;
	struct nota nota[MAX];
};

struct administrator admin[1];
struct sekretaria sekretari[MAX];
struct student student[MAX];
struct lenda lende[MAX];

int Nr_sekretari = 1; // Numri i sekretareve qe jane te ruajtura ne skedare
int Nr_studenti = 1; // Numri i studenteve qe jane te ruajtura ne skedare
int Nr_klasa = 1; // Numri i klasave qe jane te ruajtura ne skedare
int Nr_lenda = 1; // Numri i klasave qe jane te ruajtura ne skedare
int nr_klasa[MAX]; // Vektor per te ruajtur numrin e klasave te nje lende
int Nr_nota[MAX]; // Vektor per te ruajtur numrin e norave te nje studenti

int ID = 1; // Id e sekretarise
int ID_S = 1; // Id e studentit
int ID_L = 1; // Id e studentit
int flag=0; // TE drejtat e perdoruesit
int login=0; // id e personit qe eshte i kycur

void Menuja_Kryesore();
void Menuja_Admin(int k,struct administrator admin[]);
void Menuja_Sekretaria(struct sekretaria sekretari[]);
void Menuja_Studenti(int k,struct student student[]);
void Login_Admin();
void Login_Sekretari();
void Login_Student();
void Shto_Sekretari(struct sekretaria sekretari[]);
void Fshi_Sekretari(struct sekretaria sekretari[]);
void Shfaq_Sekretari(struct sekretaria sekretari[]);
void Ndrysho_Fjalekalimin_Sekretari(struct sekretaria sekretari[]);
void Shto_Student(struct student student[]);
void Fshi_Student(struct student student[]);
void Shfaq_Student(struct student student[]);
void Ndrysho_Fjalekalimin_Student();
void Ndrysho_Student(struct student student[]);
void Ndrysho_Student_Menu(int k,struct student student[]);
void Ndrysho_Student_Emer(int k,struct student student[]);
void Ndrysho_Student_Fjalekalimin(int k,struct student student[]);
void Ndrysho_Student_Klasa(int k,struct student student[]);
void Ndrysho_Student_Nota(int k,struct student student[]);
void Ndrysho_Student_Mosha(int k,struct student student[]);
void Shto_Lenda(struct lenda lenda[]);
void Ndrysho_Lenda(struct lenda lende[]);
void Ndrysho_Lenda_Menu(int k,struct lenda lende[]);
void Ndrysho_Lenda_Emer(int k,struct lenda lende[]);
void Ndrysho_Lenda_Dege(int k,struct lenda lende[]);
void Shto_Note(struct student studenti[]);
void Gjenero_Flete_Notash_Student(struct student studenti[]);
int Note_Lende(int id, int nid);
void Gjenero_Flete_Notash_Lende(struct student studenti[]);
void Flete_Provimi(struct lenda lende[]);
void Flete_Note(struct lenda lende[]);
void Ndrysho_Fjalekalimin_Student(int k,struct student student[]);
void Regjistrohu_Lende(int k,struct student student[]);
void Shfaq_Listen_Lende(int k,struct student student[]);
void Shfaq_Listen_Nota(int k,struct student student[]);
void Raporte();

int main(int argc, char *argv[])
{
	int i,j;
	FILE *r1,*r2,*r3;
	if ((r1 = fopen("sekretaria.txt", "r")) == NULL)
	{
		printf("\nFile-I i kerkuar nuk mund te hapet.\n");
		exit(EXIT_FAILURE);
	}
	
	for (i = 1; i < MAX; i++)
	{

		fscanf(r1, "%d " , &sekretari[i].emerp);
		fscanf(r1, "%s " , &sekretari[i].fjalekalimi);
		fscanf(r1, "%s " , &sekretari[i].emer);
		fscanf(r1, "%s " , &sekretari[i].mbiemer);
		fscanf(r1, "\n");
		if(sekretari[i].emerp==0){
			Nr_sekretari=i;
			ID = sekretari[i-1].emerp+1;
			i=MAX;
		} 

	}
	fclose(r1);
	
	if ((r2 = fopen("student.txt", "r")) == NULL)
	{
		printf("\nFile-I i kerkuar nuk mund te hapet.\n");
		exit(EXIT_FAILURE);
	}
	
	for (i = 1; i < MAX; i++)
	{
		
		fscanf(r2, "%d" , &student[i].id);
		fscanf(r2, "%s" , &student[i].fjalekalimi);
		fscanf(r2, "%s" , &student[i].emer);
		fscanf(r2, "%s" , &student[i].mbiemer);
		fscanf(r2, "%d" , &student[i].mosha);
		fscanf(r2, "%s" , &student[i].klasa.emer);
		fscanf(r2, "%d" , &student[i].klasa.viti);
		fscanf(r2, "%s" , &student[i].klasa.grupi);
		fscanf(r2, "%s" , &student[i].klasa.id);
		fscanf(r2, "%d " , &Nr_nota[i]);
		//printf("Numri i notave %d\n",Nr_nota[i]);
		if(Nr_nota[i]!=0){
			for(j=0;j<Nr_nota[i];j++){
				//printf("Lexo nota %d\n",j);
				fscanf(r2, "%d " , &student[i].nota[j].id);
				fscanf(r2, "%d " , &student[i].nota[j].nota);
			}
		}
		if(student[i].id==0){
			Nr_studenti=i;
			ID_S=student[i-1].id+1;
			i=MAX;
		}
	}
   	
	fclose(r2);
	
	
	if ((r3 = fopen("lenda.txt", "r")) == NULL)
	{
		printf("\nFile-I i kerkuar nuk mund te hapet.\n");
		exit(EXIT_FAILURE);
	}
	
	for (i = 1; i < MAX; i++)
	{
		fscanf(r3, "%d " , &lende[i].id);
		fscanf(r3, "%s " , &lende[i].emer);
		fscanf(r3, "%d " , &lende[i].numri_studenteve);
		if(lende[i].numri_studenteve!=0){
			for(j = 0; j<lende[i].numri_studenteve;j++){
				fscanf(r3, "%d " , &lende[i].id_s[j]);
			}
		}
		fscanf(r3, "%d " , &nr_klasa[i]);
		if(nr_klasa[i]!=0){
			for(j = 0; j<nr_klasa[i];j++){
				fscanf(r3, "%d " , &lende[i].id_k[j]);
			}
		}
		fscanf(r3, " \n");
		if(lende[i].id==0){
			Nr_lenda=i;
			ID_L = lende[i-1].id+1;
			i=MAX;
		} 

	}

	fclose(r3);
	
	
	Menuja_Kryesore();

	printf("Saving ...\n");
	
	FILE *f1,*f2,*f3;
	if ((f2 = fopen("sekretaria.txt", "w")) == NULL)
	{
		printf("\nFile-I i kerkuar nuk mund te hapet.\n");
		exit(EXIT_FAILURE);
	}
	
   	
   	for (i = 1; i < Nr_sekretari; i++)
	{
		
		fprintf(f2, "%d " , sekretari[i].emerp);
		fprintf(f2, "%s " , &sekretari[i].fjalekalimi);
		fprintf(f2, "%s " , &sekretari[i].emer);
		fprintf(f2, "%s\n" , &sekretari[i].mbiemer);
	}
	
	fclose(f2);
	
	if ((f1 = fopen("student.txt", "w")) == NULL)
	{
		printf("\nFile-I i kerkuar nuk mund te hapet.\n");
		exit(EXIT_FAILURE);
	}

   	for (i = 1; i < Nr_studenti; i++)
	{
		
		fprintf(f1, "%d " , student[i].id);
		fprintf(f1, "%s " , &student[i].fjalekalimi);
		fprintf(f1, "%s " , &student[i].emer);
		fprintf(f1, "%s " , &student[i].mbiemer);
		fprintf(f1, "%d " , student[i].mosha);
		fprintf(f1, "%s " , &student[i].klasa.emer);
		fprintf(f1, "%d " , student[i].klasa.viti);
		fprintf(f1, "%s " , &student[i].klasa.grupi);
		fprintf(f1, "%s " , &student[i].klasa.id);
		fprintf(f1, "%d " , Nr_nota[i]);
		//printf("Nr note %d\n",Nr_nota[i]);
		if(Nr_nota[i]!=0){
			for(j=0;j<Nr_nota[i];j++){
				fprintf(f1, "%d " , student[i].nota[j].id);
				fprintf(f1, "%d " , student[i].nota[j].nota);
			}
		}
		fprintf(f1, "\n");
	}
	
	fclose(f1);
	
	if ((f3 = fopen("lenda.txt", "w")) == NULL)
	{
		printf("\nFile-I i kerkuar nuk mund te hapet.\n");
		exit(EXIT_FAILURE);
	}
	for (i = 1; i < Nr_lenda; i++)
	{
		fprintf(f3, "%d " , lende[i].id);
		fprintf(f3, "%s " , &lende[i].emer);
		fprintf(f3, "%d " , lende[i].numri_studenteve);
		if(lende[i].numri_studenteve>0){
			for(j = 0; j<lende[i].numri_studenteve;j++){
				fprintf(f3, "%d " , lende[i].id_s[j]);
			}
		}
		if(nr_klasa[i]>0){
			fprintf(f3, "%d " , nr_klasa[i]);
			for(j = 0; j<nr_klasa[i];j++){
				fprintf(f3, "%d " , lende[i].id_k[j]);
			}
		}else{
			fprintf(f3, "0 ");
		}
		fprintf(f3, "\n");
	}
	fclose(f3);
	
	printf("Done");
	return 1;
}

void Menuja_Kryesore(){
	char n;
	while(1){
		system("cls");
		printf("-------------------------------------------\n");
		printf("\n|       Hyr ne sistem me te drejta:       |\n\n");
		printf("-------------------------------------------\n");
		printf("\n1\tAdministrator\n");
		printf("2\tSekretari\n");
		printf("3\tStudent\n");
		printf("d\tDil nga programi\n");
		printf("\nZgjidhni nje opsion:");
		n = getche();
		switch(n){
			case '1':Login_Admin();break;
			case '2':Login_Sekretari();break;
			case '3':Login_Student();break;
			case 'd':printf("\n--------------------------------\n\nJu dolet nga programi\n");return;break;
			default:printf("\nKomande e panjohur\n");sleep(1); break;
			
		}
		system("cls");
	}
}


void Menuja_Admin(int k,struct administrator admin[]){
	char n;
	while (1)
	{
		system("cls");
		printf("---------------------------------------------------\n");
		printf("\n|    Mire se vini ne menune e Administratorit     |\n\n");
		printf("---------------------------------------------------\n");
		printf("\n1\tShtim i nje llogarie te re per sekretarine\n");
		printf("2\tFshi nje llogari ekzistuese te sekretarise\n");
		printf("3\tRivendos fjalekalimin per nje llogari sekretarie\n");
		printf("4\tGjenero listen emer mbiemer te llogarive te sekretarise mesimore\n");
		printf("d\tDil nga menuja\n\n");
		printf("\nZgjidhni nje opsion:");
		n = getche();
		switch (n)
		{
			case '1':Shto_Sekretari(sekretari); break;
			case '2':Fshi_Sekretari(sekretari); break;
			case '3':Ndrysho_Fjalekalimin_Sekretari(sekretari); break;
			case '4':Shfaq_Sekretari(sekretari);break;
			case 'd':printf("\n--------------------------------\n\nJu dolet nga menuja\n--------------------------------\n\n");sleep(1);return;break;
			default:printf("\nKomande e panjohur");sleep(1); break;
		}
		system("cls");
	}
}


void Menuja_Sekretaria(struct sekretaria sekretari[]){
	char n;
	while (1)
	{
		system("cls");
		printf("---------------------------------------------------\n");
		printf("\n|      Mire se vini ne menune e Sekretarise       |\n\n");
		printf("---------------------------------------------------\n");
		printf("\n1\tShto student\n");
		printf("2\tNdrysho student\n");
		printf("3\tFshi student\n");
		printf("4\tShto lende\n");
		printf("5\tNdrysho lende\n");
		printf("6\tShto note\n");
		printf("7\tGjenero Flete notash per student\n");
		printf("8\tGjenero Flete notash per lende\n");
		printf("9\tRaporte\n");
		printf("d\tDil nga menuja\n\n");
		printf("\nZgjidhni nje opsion:");
		n = getche();
		switch (n)
		{
			case '1':Shto_Student(student);break;
			case '2':Ndrysho_Student(student);break;
			case '3':Fshi_Student(student);break;
			case '4':Shto_Lenda(lende);break;
			case '5':Ndrysho_Lenda(lende);break;
			case '6':Shto_Note(student);break;
			case '7':Gjenero_Flete_Notash_Student(student);break;
			case '8':Gjenero_Flete_Notash_Lende(student);break;
			case '9':Raporte();break;
			case 'd':printf("\n--------------------------------\n\nJu dolet nga menuja\n--------------------------------\n\n");sleep(1);return;break;
			default:printf("\nKomande e panjohur");sleep(1);break;
		}
		system("cls");
	}
}


void Menuja_Student(int k,struct student student[]){
	char n;
	while (1)
	{
		system("cls");
		printf("---------------------------------------------------\n");
		printf("\n|        Mire se vini ne menune e Studentit       |\n\n");
		printf("---------------------------------------------------\n");
		printf("\n1\tNdrysho fjalekalimin\n");
		printf("2\tRegjistrohu ne nje lende\n");
		printf("3\tShfaq listen e lendeve\n");
		printf("4\tShfaq listen e notave\n");
		printf("d\tDil nga menuja\n\n");
		printf("\nZgjidhni nje opsion:");
		n = getche();
		switch (n)
		{
			case '1':Ndrysho_Fjalekalimin_Student(k,student);break;
			case '2':Regjistrohu_Lende(k,student);break;
			case '3':Shfaq_Listen_Lende(k,student);break;
			case '4':Shfaq_Listen_Nota(k,student);break;
			case 'd':printf("\n--------------------------------\n\nJu dolet nga menuja\n--------------------------------\n\n");sleep(1);return;break;
			default:printf("\nKomande e panjohur"); sleep(1);break;
		}
		system("cls");
	}
}


void Login_Admin(){
	char pass[15];
	int i=0, id, n=0, k=0;
	FILE *f1;
	if ((f1 = fopen("admin.txt", "r")) == NULL)
	{
		printf("\nFile-I i kerkuar nuk mund te hapet.\n");
		exit(EXIT_FAILURE);
	}
	
	fscanf(f1, "%d", &admin[0].id);
	fscanf(f1, "%s", &admin[0].fjalekalimi);
   	
	//printf("%d, %s",admin[0].id,&admin[0].fjalekalimi);
	fclose(f1);
	
	while (1)
	{
		system("cls");
		printf("--------------------------------------\n");
		printf("\n|      Login per administratorin     |\n\n");
		printf("--------------------------------------\n");
		printf("\n1\tIdentifikohu\n");
		printf("d\tDil\n");
		printf("\nZgjidhni nje opsion:");
		n = getche();
		switch(n){
			case 'd':printf("\n--------------------------------\n\nJu dolet nga menuja\n--------------------------------\n\n");sleep(1);return;break;
			case '1':printf("\n\nID: ");
			scanf("%d", &id);
			if (id == admin[0].id)
			{
				printf("Fjalekalimi: ");
				scanf("%s", pass);
				if (strcmp(pass, admin[0].fjalekalimi) == 0)
				{
					flag=1;
					Menuja_Admin(k,admin);
					continue;
				}
				else
				{
					printf("\nFjalekalimi jo i sakte!\n");
					sleep(1);
					continue;
				}
			}else{
					printf("\nKjo ID nuk ekziston\n");sleep(1);break;
				}
			default:printf("\nKomande e panjohur"); sleep(1);break;
		}

	}
}


void Login_Sekretari(){
	char pass[15];
	int i=0, id, n=0, k=0;
	

	while (1)
	{
		system("cls");
		printf("----------------------------------\n");
		printf("\n|      Login per sekretarine     |\n\n");
		printf("----------------------------------\n");
		printf("\n1\tIdentifikohu\n");
		printf("d\tDil\n");
		printf("\nZgjidhni nje opsion:");
		n = getche();
		switch(n){
			case 'd':printf("\n--------------------------------\n\nJu dolet nga menuja\n--------------------------------\n\n");sleep(1);return;break;
			default:printf("\nKomande e panjohur"); sleep(1);break;
			case '1':printf("\n\nID: ");
			scanf("%d", &id);
			for (i = 1; i < Nr_sekretari; i++)
			{
				if (sekretari[i].emerp == id)
				{
					k = i;
					flag = 2;
					break;
				}
			}
			if(k==0){
				printf("\nId nuk ekziston"); sleep(1);
			}
			else if (id == sekretari[k].emerp)
			{
				printf("Fjalekalimi: ");
				scanf("%s", pass);
				if (strcmp(pass, sekretari[k].fjalekalimi) == 0)
				{
					Menuja_Sekretaria(sekretari);
					continue;
				}
				else
				{
					printf("\nFjalekalimi jo i sakte!\n");
					sleep(1);
					continue;
				}
			}
			
		}

	}
}


void Login_Student(){
	char pass[15];
	int i=0, id, n=0, k=0;

	while (1)
	{
		system("cls");
		printf("----------------------------------\n");
		printf("\n|        Login per studentin     |\n\n");
		printf("----------------------------------\n");
		printf("\n1\tIdentifikohu\n");
		printf("d\tDil\n");
		printf("\nZgjidhni nje opsion:");
		n = getche();
		switch(n){
			case 'd':printf("\n--------------------------------\n\nJu dolet nga menuja\n--------------------------------\n\n");sleep(1);return;break;
			case '1':printf("\n\nID: ");
			scanf("%d", &id);
			for (i = 1; i <= Nr_studenti; i++)
			{
				if (student[i].id == id)
				{
					k = i;
					flag = 3;
					break;
				}
			}
			if(k==0){
				printf("\nId nuk ekziston"); sleep(1);
			}
			if (id == student[i].id)
			{
				printf("Fjalekalimi: ");
				scanf("%s", pass);
				
				if (strcmp(pass, student[k].fjalekalimi) == 0)
				{
					Menuja_Student(k,student);
					continue;
				}
				else
				{
					printf("\nFjalekalimi jo i sakte!\n");
					sleep(1);
					continue;
				}
			}
			default:printf("\nKomande e panjohur"); sleep(1);break;
		}

	}
}


void Shto_Sekretari(struct sekretaria sekretari[])
{
	int i;
	char z;
	while (1)
	{
		if (Nr_sekretari + 1 == MAX)
		{
			printf("\nNuk mund te shtoni me sekretare\n");
			return;
		}
		else
		{
			sekretari[Nr_sekretari].emerp = ID;
			strcpy(sekretari[Nr_sekretari].fjalekalimi, "12345678");
			printf("\nJepni emrin e sekretarit te ri: ");
			scanf("%s", &sekretari[Nr_sekretari].emer);
			printf("Jepni mbiemrin e sekretari te ri: ");
			scanf("%s", &sekretari[Nr_sekretari].mbiemer);
			Nr_sekretari++;
			ID++;
		}
		printf("\nDeshironi te shtoni sekretar tjeter?(y/n)");
		z = getche();
		if (z == 'y')
			continue;
		if (z == 'n')
		{
			printf("\nShtimi u krye me sukses!\n");
			return;		break;
		}
		else
			printf("\nKomande e panjohur.\n");sleep(1);break;
	}
}

void Fshi_Sekretari(struct sekretaria sekretari[])
{
	int i, k=0, id;
	char z;
	Shfaq_Sekretari(sekretari);
	printf("\nJepni ID e sekretarit qe doni te fshini: ");
	scanf("%d", &id);
	for (i = 1; i <= Nr_sekretari; i++)
	{
		if (sekretari[i].emerp == id)
		{
			k = i;
			break;
		}
	}
	if(k==0){
		printf("\nId nuk ekziston"); sleep(1);
	}
	else if (flag == 1)
	{
		printf("\nDeshironi qe te fshini sekretarin me id %d(y/n):",id);
		z = getche();
		if (z == 'y'){
			for (i = k; i < Nr_sekretari; i++)
			{
				
				strcpy(sekretari[i].emer, sekretari[i + 1].emer);
				strcpy(sekretari[i].mbiemer, sekretari[i + 1].mbiemer);
				strcpy(sekretari[i].fjalekalimi, sekretari[i + 1].fjalekalimi);
				sekretari[i].emerp= sekretari[i + 1].emerp;
				printf("\nSekretari u fshi me sukses.\n");sleep(1);
			}
			Nr_sekretari--;
		}

		else if (z == 'n')
		{
			return;
		}
		else
			printf("\nKomande e panjohur.\n");sleep(1);return;
		
		
	}else{
		printf("\nJu nuk keni te drejte per te kryer kete veprim."); sleep(1);
		}
	
}

void Shfaq_Sekretari(struct sekretaria sekretari[])
{
	int i;
	system("cls");
	printf("\n\n----- Lista e Sekretareve ------\n\n");
	printf("--------------------------------");
	printf("\nID\tEmri\tMbiemri\t \n");
	printf("--------------------------------\n");
	for (i = 1; i < Nr_sekretari; i++)
	{
		printf("\n%d\t%s\t",sekretari[i].emerp , sekretari[i].emer);
		printf("%s\n", sekretari[i].mbiemer);
	}
	printf("\n--------------------------------\n");
	printf("\nKliko per te vazhduar...\n");
	getch();
}

void Ndrysho_Fjalekalimin_Sekretari( struct sekretaria sekretari[])
{
	char emer[20],mbiemer[20];
	char pass[15];
	int i,k=0;
	
	if(flag==1){
		system("cls");
		Shfaq_Sekretari(sekretari);
		printf("\nJepni emrin e sekretarit qe doni te ndryshoni fjalekalimin: ");
		scanf("%s", emer);
		printf("Jepni mbiemrin e sekretarit qe doni te ndryshoni fjalekalimin: ");
		scanf("%s", mbiemer);

		for (i = 1; i < Nr_sekretari; i++){
			if(strcmp(emer, sekretari[i].emer) == 0 && strcmp(mbiemer, sekretari[i].mbiemer) == 0 ){
				printf("\nJepni passwordin e ri: ");
				scanf("%s", pass);
				strcpy(sekretari[i].fjalekalimi, pass);
				printf("\nFjalekalimi i ri u ruajt me sukses.");sleep(1);return;
			}
		}
		if(k==0)
			printf("\nSekretari nuk u gjend.\n");sleep(1);Ndrysho_Fjalekalimin_Sekretari(sekretari);
	}else{
		printf("\nJu nuk keni te drejte per te kryer kete veprim."); sleep(1);return;
	}
	
}


void Shto_Student(struct student student[]){
	char z;
	while (1)
	{
		if (Nr_studenti + 1 == MAX)
		{
			printf("\nNuk mund te shtoni me studente\n");
			return;
		}
		else
		{
			student[Nr_studenti].id = ID_S;
			strcpy(student[Nr_studenti].fjalekalimi, "12345678");
			printf("\nJepni emrin e studentit te ri: ");
			scanf("%s", &student[Nr_studenti].emer);
			printf("Jepni mbiemrin e studentit te ri: ");
			scanf("%s", &student[Nr_studenti].mbiemer);
			printf("Jepni moshen e studentit te ri: ");
			scanf("%d", &student[Nr_studenti].mosha);
			printf("Jepni emrin e deges te studentit te ri: ");
			scanf("%s", &student[Nr_studenti].klasa.emer);
			printf("Jepni vitin e studentit te ri: ");
			scanf("%d", &student[Nr_studenti].klasa.viti);
			printf("Jepni grupin e studentit te ri: ");
			scanf("%s", &student[Nr_studenti].klasa.grupi);
			

			sprintf(student[Nr_studenti].klasa.id,"%s%d%s",&student[Nr_studenti].klasa.emer,student[Nr_studenti].klasa.viti,&student[Nr_studenti].klasa.grupi);
			
			Nr_studenti++;
			ID_S++;
		}
		printf("\nDeshironi te shtoni student tjeter?(y/n)");
		z = getche();
		if (z == 'y')
			continue;
		if (z == 'n')
		{
			printf("\nShtimi u krye me sukses!\n");
			return;		break;
		}
		else
			printf("\nKomande e panjohur.\n");sleep(1);break;
	}
}


void Ndrysho_Student(struct student student[]){
	int id,i,k=0;
	if(flag==2){
	
		system("cls");
		printf("----------------------------------\n");
		printf("\n|         Ndrysho Student        |\n\n");
		printf("----------------------------------\n");
		
		printf("\n\nID e Studentit: ");
		scanf("%d",&id);
		
		for (i = 1; i < Nr_studenti; i++){
				if(student[i].id == id ){
					k=i;
					break;
				}
			}
		if(k==0){
			printf("\nID e gabuar.\n");sleep(1);Menuja_Sekretaria(sekretari);
		}
		else{
			Ndrysho_Student_Menu(k,student);
		}
	}else{
		printf("\nJu nuk keni te drejte per te kryer kete veprim."); sleep(1);return;
	}
}


void Ndrysho_Student_Menu(int k,struct student student[]){
	char n;
	while (1)
	{
		system("cls");
		printf("\n1\tShtyp 1 per te ndryshuar emrin dhe mbiemrin\n");
		printf("2\tShtyp 2 per te resetuar fjalekalimin\n");
		printf("3\tShtyp 3 per te ndryshuar moshen\n");
		printf("4\tShtyp 4 per te ndryshuar klasen\n");
		printf("5\tShtyp 5 per te ndryshuar noten\n");
		printf("d\tDil nga menuja\n\n");
		printf("\nZgjidhni nje opsion:");
		n = getche();
		switch (n)
		{
			case '1':Ndrysho_Student_Emer(k,student);break;
			case '2':Ndrysho_Student_Fjalekalimin(k,student);break;
			case '3':Ndrysho_Student_Mosha(k,student);break;
			case '4':Ndrysho_Student_Klasa(k,student);break;
			case '5':Ndrysho_Student_Nota(k,student);break;
			case 'd':printf("\n--------------------------------\n\nJu dolet nga menuja\n--------------------------------\n\n");sleep(1);return;
			default:printf("\nKomande e panjohur");sleep(1);break;
		}
		system("cls");
	}
}


void Fshi_Student(struct student student[]){
	int i, k=0, id;
	if(flag==2){
		printf("\nJepni ID e studentit qe doni te fshini: ");
		scanf("%d", &id);
		for (i = 1; i <= Nr_studenti; i++)
		{
			if (student[i].id == id)
			{
				k = i;
				break;
			}
		}
		if(k==0){
			printf("\nID e gabuar"); sleep(1);return;
		}

		for (i = k; i < Nr_sekretari; i++)
		{
			
			strcpy(student[i].emer, student[i + 1].emer);
			strcpy(student[i].mbiemer, student[i + 1].mbiemer);
			strcpy(sekretari[i].fjalekalimi, student[i + 1].fjalekalimi);
			student[i].id= student[i + 1].id;
			int j;
			for(j=0; j<3; j++)
				student[i].klasa.emer[i] = student[i+1].klasa.emer[j];
			student[i].klasa.viti = student[i+1].klasa.viti;
			student[i].klasa.grupi = student[i+1].klasa.grupi;
			for(j=0; j<5; j++)
				student[i].klasa.id[j] = student[i+1].klasa.id[j];
			//for(i=1; i < Nr_klasa; i++){
				
			//}
		}
		Nr_studenti--;
		printf("\nFshirja u realizua me sukses.\n");sleep(1);
	}else{
		printf("\nJu nuk keni te drejte per te kryer kete veprim."); sleep(1);
		}
	
}

void Ndrysho_Student_Emer(int k,struct student student[]){
	printf("\nJepni emrin e ri te studentit: ");
	scanf("%s", &student[k].emer);
	printf("Jepni mbiemrin e ri te studentit: ");
	scanf("%s", &student[k].mbiemer);
	printf("\nStudenti u ndryshua me sukses.\n");
	sleep(1);
}

void Ndrysho_Student_Fjalekalimin(int k,struct student student[]){
	printf("\nFjalekalimi po resetohet...\n");
	strcpy(student[k].fjalekalimi,"12345678");
	printf("\nFjalekalimi i studentit u resetua me sukses.\n");
	sleep(1);
}

void Ndrysho_Student_Klasa(int k,struct student student[]){
	printf("\nJepni emrin e deges se studentit: ");
	scanf("%s", &student[k].klasa.emer);
	printf("Jepni grupin e studentit: ");
	scanf("%s", &student[k].klasa.grupi);
	printf("Jepni vitin e studentit: ");
	scanf("%d", &student[k].klasa.viti);
	printf("\nStudenti u ndryshua me sukses.\n");
	sleep(1);
}

void Ndrysho_Student_Nota(int k,struct student student[]){
	printf("\nJepni ID e lendes se studentit: ");
	scanf("%d", &student[k].nota[0].id);
	printf("Jepni noten e studentit: ");
	scanf("%d", &student[k].nota[0].nota);
	printf("\nStudenti u ndryshua me sukses.\n");
	sleep(1);
}

void Ndrysho_Student_Mosha(int k,struct student student[]){
	printf("\nJepni moshen e studentit: ");
	scanf("%d", &student[k].mosha);
	printf("\nStudenti u ndryshua me sukses.\n");
	sleep(1);
}

void Shto_Lenda(struct lenda lenda[]){
	char z;
	while (1)
	{
		if (Nr_lenda + 1 == MAX)
		{
			printf("\nNuk mund te shtoni me lende\n");
			return;
		}
		else
		{
			lenda[Nr_lenda].id = ID_L;
			//strcpy(student[Nr_studenti].fjalekalimi, "12345678");
			printf("\nJepni emrin e lendes se re: ");
			scanf("%s", &lenda[Nr_lenda].emer);
			lenda[Nr_lenda].numri_studenteve=0;
			nr_klasa[Nr_lenda]=0;

			Nr_lenda++;
			ID_L++;
		}
		printf("\nDeshironi te shtoni lende tjeter?(y/n)");
		z = getche();
		if (z == 'y')
			continue;
		if (z == 'n')
		{
			printf("\nShtimi u krye me sukses!\n");
			return;		break;
		}
		else
			printf("\nKomande e panjohur.\n");sleep(1);break;
	}
}

void Ndrysho_Lenda(struct lenda lende[]){
	int id,i,k=0;
	if(flag==2){
	
		system("cls");
		printf("----------------------------------\n");
		printf("\n|         Ndrysho Lende        |\n\n");
		printf("----------------------------------\n");
		
		printf("\n\nJep ID e lendes per t'u ndryshuar: ");
		scanf("%d",&id);
		
		for (i = 1; i < Nr_lenda; i++){
				if(lende[i].id == id ){
					k=i;
					break;
				}
			}
		if(k==0){
			printf("\nID e gabuar.\n");sleep(1);Menuja_Sekretaria(sekretari);
		}
		else{
			Ndrysho_Lenda_Menu(k,lende);
		}
	}else{
		printf("\nJu nuk keni te drejte per te kryer kete veprim."); sleep(1);return;
	}
}

void Ndrysho_Lenda_Menu(int k,struct lenda lende[]){
	char n;
	while (1)
	{
		system("cls");
		printf("\n1\tShtyp 1 per te ndryshuar emrin e lendes\n");
		printf("2\tShtyp 2 per te ndryshuar degen ku jepet lenda\n");
		printf("d\tDil nga menuja\n\n");
		printf("\nZgjidhni nje opsion:");
		n = getche();
		switch (n)
		{
			case '1':Ndrysho_Lenda_Emer(k,lende);Menuja_Sekretaria(sekretari);break;
			case '2':Ndrysho_Lenda_Dege(k,lende);Menuja_Sekretaria(sekretari);break;
			case 'd':printf("\n--------------------------------\n\nJu dolet nga menuja\n--------------------------------\n\n");sleep(1);return;
			default:printf("\nKomande e panjohur");sleep(1);break;
		}
		system("cls");
	}
}

void Ndrysho_Lenda_Dege(int k,struct lenda lende[]){
	printf("\nJepni id e deges ku jepet lenda: ");
	scanf("%d", &lende[k].id_k[0]);
	printf("\nLenda u ndryshua me sukses.\n");
	sleep(1);
}

void Ndrysho_Lenda_Emer(int k,struct lenda lende[]){
	printf("\nJepni emrin e ri te lendes: ");
	scanf("%s", &lende[k].emer);
	printf("\nLenda u ndryshua me sukses.\n");
	sleep(1);
}

void Shto_Note(struct student studenti[]){
	int id,i,k=0;
	char z;
	system("cls");
	if(flag==2){
		//lenda[Nr_lenda].id = ID_L;
		//strcpy(student[Nr_studenti].fjalekalimi, "12345678");
		printf("\nJepni id e studentit: ");
		scanf("%d", &id);
		
		for (i = 1; i < Nr_studenti; i++){
				if(student[i].id == id ){
					k=i;
					break;
				}
			}
		if(k==0){
			printf("\nStudenti nuk u gjet.\n");sleep(1);return;
		}
		else{
			printf("\nJepni id e lendes: ");
			scanf("%d", &student[k].nota[Nr_nota[k]].id);
			printf("\nJepni noten: ");
			scanf("%d", &student[k].nota[Nr_nota[k]].nota);
			
			Nr_nota[k]++;

			printf("\nDeshironi te shtoni lende tjeter?(y/n)");
			z = getche();
			if (z == 'y')
				Shto_Note(studenti);
			if (z == 'n')
			{
				printf("\nShtimi u krye me sukses!\n");
				return;		return;
			}
			else
				printf("\nKomande e panjohur.\n");sleep(1);return;
		}
	}else{
		printf("\nJu nuk keni te drejte per te kryer kete veprim."); sleep(1);return;
	}
}

void Gjenero_Flete_Notash_Student(struct student studenti[]){
	int id,i,k=0;
	char z;
	system("cls");
	if(flag==2){
		printf("\nJepni id e studentit: ");
		scanf("%d", &id);
		
		for (i = 1; i < Nr_studenti; i++){
				if(student[i].id == id ){
					k=i;
					break;
				}
			}
		if(k==0){
			printf("\nStudenti nuk u gjet.\n");sleep(1);return;
		}
		else{
			sleep(1);
			system("cls");
			char filename[20];
			//strcpy(filename,"nota/1");
			sprintf(filename, "nota/%d.txt",studenti[k].id ); 
			//strcpy(filename,studenti[k].id+'0');
			FILE *f1;
			if ((f1 = fopen(filename, "w")) == NULL)
			{
				printf("\nFile-I i kerkuar nuk mund te hapet.\n");
				exit(EXIT_FAILURE);
			}
			printf("\nStudenti\t\t%s\n",&studenti[k].emer);
			printf("------------------------------------\n");
			printf("\n\t Lista e notave \t\n");
			printf("\n------------------------------------\n");
			printf("\nLenda\t\t\tNota\n");
			fprintf(f1,"\nStudenti\t\t%s\n",&studenti[k].emer);
			fprintf(f1,"------------------------------------\n");
			fprintf(f1,"\n\t Lista e notave \t\n");
			fprintf(f1,"\n------------------------------------\n");
			fprintf(f1,"\nLenda\t\t\tNota\n");
			


			for(i=0;i<Nr_nota[k];i++){
				//printf("\n%s\t\t%d",&lende[student[k].nota[i].id].emer,student[k].nota[i].nota);
					printf("\n%s\t\t",&lende[student[k].nota[i].id].emer);
				fprintf(f1,"\n%s\t\t",&lende[student[k].nota[i].id].emer);
				if(strlen(lende[student[k].nota[i].id].emer)<8){
					printf("\t");
					fprintf(f1,"\t");
				}
				printf("%d",Note_Lende(k,student[k].nota[i].id));
				fprintf(f1,"%d",Note_Lende(k,student[k].nota[i].id));

				
				
			}
			fprintf(f1, "\n");
			
			fclose(f1);
			printf("\n\n\nKliko per te vazhduar...");
			z = getche();
		}
	}else{
		printf("\nJu nuk keni te drejte per te kryer kete veprim."); sleep(1);return;
	}
}

void Gjenero_Flete_Notash_Lende(struct student studenti[]){
	int id,i,k=0;
	char z;
	system("cls");
	if(flag==2){
		printf("----------------------------------\n");
		printf("\n| Gjenero flete notashe per lende |\n\n");
		printf("----------------------------------\n");
		printf("\n1\t Flete provimi\n");
		printf("\n2\t Flete note\n");
		z = getche();
		switch (z)
		{
			case '1':Flete_Provimi(lende);break;
			case '2':Flete_Note(lende);break;
			case 'd':printf("\n--------------------------------\n\nJu dolet nga menuja\n--------------------------------\n\n");sleep(1);return;break;
			default:printf("\nKomande e panjohur");sleep(1);break;
		}
		
	}else{
		printf("\nJu nuk keni te drejte per te kryer kete veprim."); sleep(1);return;
	}
}


int Note_Lende(int id, int nid){
	int i,cnota=0,cnr=0;
	for(i=1;i<Nr_nota[id];i++){
		if(student[id].nota[i].id==nid){
			cnr++;
			if(student[id].nota[i].nota<0){
				student[id].nota[i].nota=0;
			}
			cnota+=student[id].nota[i].nota;
		}
	}
	float num = ((float) cnota/ (float) cnr);
	int result = (int)(num < 0 ? (num - 0.5) : (num + 0.5));
	return result;
}

void Raporte(){
	char n;
	while (1)
	{
		system("cls");
		printf("----------------------------\n");
		printf("\n|          Raporte        |\n\n");
		printf("----------------------------\n");
		printf("\n1\tShfaq listen e lendeve\n");
		printf("\tShfaq listen e studenteve per\n");
		printf("\ta\tNje vit te kerkuar\n");
		printf("\tb\tNje dege dhe nje vit te kerkuar\n");
		printf("\tc\tNje klase te bazuar ne ID-ne e klases\n");
		printf("2\tShfaq listen e studenteve me mesatare 10\n");
		printf("3\tShfaq listen e studenteve te renditur sipas mesatares ne rend zbrites\n");
		printf("4\tShfaq perqindjen e numrit te studenteve sipas fashave te mesatareve\n");
		printf("5\tShfaq listen e studenteve qe nuk jane futur asnjehere ne provimin e nje lende te kerkuar\n");
		printf("6\tShfaq listen e studenteve kalues ne provimin e nje lende te kerkuar\n");
		printf("7\tPerqindja e ngelshmerise per cdo lende\n");
		printf("8\tShfaq lenden qe ka kalueshmeri me te larte\n");
		printf("d\tDil nga menuja\n\n");
		printf("\nZgjidhni nje opsion:");
		n = getche();
		switch (n)
		{
			case '1':break;
			case 'a':break;
			case 'b':break;
			case 'c':break;
			case '2':break;
			case '3':break;
			case '4':break;
			case '5':break;
			case '6':break;
			case '7':break;
			case '8':break;
			case 'd':printf("\n--------------------------------\n\nJu dolet nga menuja\n--------------------------------\n\n");sleep(1);return;break;
			default:printf("\nKomande e panjohur");sleep(1); break;
		}
		system("cls");
	}
}


void Flete_Provimi(struct lenda lende[]){
	int id,i,k=0;
	char z;
	printf("\nJepni id e lendes: ");
	scanf("%d", &id);
	
	for (i = 1; i < Nr_lenda; i++){
			if(lende[i].id == id ){
				k=i;
				break;
			}
		}
	if(k==0){
		printf("\nLenda nuk u gjet.\n");sleep(1);return;
	}
	else{
		sleep(1);
		system("cls");
		char filename[20];
		sprintf(filename, "lende/fp%d.txt",lende[k].id ); 
		//strcpy(filename,studenti[k].id+'0');
		FILE *f1;
		if ((f1 = fopen(filename, "w")) == NULL)
		{
			printf("\nFile-I i kerkuar nuk mund te hapet.\n");
			exit(EXIT_FAILURE);
		}
		printf("\nLenda\t\t%s\n",&lende[k].emer);
		printf("------------------------------------\n");
		printf("\n\t Flete Provimi\t\n");
		printf("\n------------------------------------\n");
		printf("\nEmri_Student\t\tNota\n");
		fprintf(f1,"\nLenda\t\t%s\n",&lende[k].emer);
		fprintf(f1,"------------------------------------\n");
		fprintf(f1,"\n\t Flete Provimi\t\n");
		fprintf(f1,"\n------------------------------------\n");
		fprintf(f1,"\nEmri_Student\t\tNota\n");
		


		for(i=0;i<Nr_studenti;i++){
			//printf("\n%s\t\t%d",&lende[student[k].nota[i].id].emer,student[k].nota[i].nota);
			if(Note_Lende(student[i].id,lende[k].id)<0 || Note_Lende(student[i].id,lende[k].id)==4){
				printf("\n%s\t\t",&student[i].emer);
				fprintf(f1,"\n%s\t\t",&student[i].emer);
				if(strlen(student[i].emer)<8){
					printf("\t");
					fprintf(f1,"\t");
				}
				printf("%d",Note_Lende(student[i].id,lende[k].id));
				fprintf(f1,"%d",Note_Lende(student[i].id,lende[k].id));
			}
			
		}
		fprintf(f1, "\n");
		
		fclose(f1);
		printf("\n\n\nKliko per te vazhduar...");
		z = getche();
	}
}

void Flete_Note(struct lenda lende[]){
	int id,i,k=0;
	char z;
	printf("\nJepni id e lendes: ");
	scanf("%d", &id);
	
	for (i = 1; i < Nr_lenda; i++){
			if(lende[i].id == id ){
				k=i;
				break;
			}
		}
	if(k==0){
		printf("\nLenda nuk u gjet.\n");sleep(1);Flete_Note(lende);
	}
	else{
		sleep(1);
		system("cls");
		char filename[20];
		sprintf(filename, "lende/fn%d.txt",lende[k].id ); 
		//strcpy(filename,studenti[k].id+'0');
		FILE *f1;
		if ((f1 = fopen(filename, "w")) == NULL)
		{
			printf("\nFile-I i kerkuar nuk mund te hapet.\n");
			exit(EXIT_FAILURE);
		}
		printf("\nLenda\t\t%s\n",&lende[k].emer);
		printf("------------------------------------\n");
		printf("\n\t Flete Provimi\t\n");
		printf("\n------------------------------------\n");
		printf("\nEmri_Student\t\tNota\n");
		fprintf(f1,"\nLenda\t\t%s\n",&lende[k].emer);
		fprintf(f1,"------------------------------------\n");
		fprintf(f1,"\n\t Flete Note\t\n");
		fprintf(f1,"\n------------------------------------\n");
		fprintf(f1,"\nEmri_Student\t\tNota\n");
		


		for(i=0;i<Nr_studenti;i++){
			
			if(Note_Lende(student[i].id,lende[k].id)>=5){
				printf("\n%s\t\t",&student[i].emer);
				fprintf(f1,"\n%s\t\t",&student[i].emer);
				if(strlen(student[i].emer)<8){
					printf("\t");
					fprintf(f1,"\t");
				}
				printf("%d",Note_Lende(student[i].id,lende[k].id));
				fprintf(f1,"%d",Note_Lende(student[i].id,lende[k].id));
			
			}
		}
		fprintf(f1, "\n");
		
		fclose(f1);
		printf("\n\n\nKliko per te vazhduar...");
		z = getche();
	}
}

void Ndrysho_Fjalekalimin_Student(int k,struct student student[]){
	char pass[20];
	printf("\n\nJepni fjalekalimin e ri:\n");
	scanf("%s",&pass);
	strcpy(student[k].fjalekalimi,pass);
	printf("\n\nFjalekalimi u ndryshua me sukses.\n");
	sleep(1);
}

void Regjistrohu_Lende(int k,struct student student[]){
	int id,i,j,tmp=0;
	printf("\n\nJepni id e lendes:\n");
	scanf("%d",&id);
	for(i=0; i <Nr_lenda; i++){
		if(tmp==1)
			break;
		if(lende[i].id==id){

				lende[i].id_s[lende[i].numri_studenteve]=k;
				lende[i].numri_studenteve++;
				tmp=1;
				break;
		}
	}
	printf("\n\nJu u rregjistruat me sukses.\n");
	sleep(1);
}

void Shfaq_Listen_Lende(int k,struct student student[]){
	int j,i;
	char z;
	system("cls");
	printf("--------------------------------------\n");
	printf("\n|  Lendet ku mund te regjistrohesh  |\n\n");
	printf("--------------------------------------\n");
	for(i=1; i <Nr_lenda; i++){
		if(lende[i].numri_studenteve==0)
			printf("\n%d\t%s\n",lende[i].id,lende[i].emer);
		for(j=0; j<lende[i].numri_studenteve; j++){
			if(lende[i].id_s[j]!=k){
				printf("\n%d\t%s\n",lende[i].id,lende[i].emer);
				break;
			}
		}
	}
	printf("\n\n\nKliko per te vazhduar...");
	z = getche();
}

void Shfaq_Listen_Nota(int k,struct student student[]){
	char filename[20];
	FILE *r1;
	sprintf(filename, "nota/%d.txt",student[k].id);
	if ((r1 = fopen(filename, "r")) == NULL)
	{
		printf("\n\nSekretaria nuk e ka gjeneruar ende fleten tende te notave.\n");
		sleep(2);
		return;
	}
	int c;
	system("cls");
	while ((c = getc(r1)) != EOF)
        putchar(c);
	fclose(r1);
	sleep(10);
}
