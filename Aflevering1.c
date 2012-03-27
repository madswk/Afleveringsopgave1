#include <stdio.h>
#include <stdlib.h>	
#include <string.h>

	/*			*/
	/* OPGAVE 1 */
	/*			*/

// Definerer navne til speciferede tal som bruges senere
#define N 24
#define STUDENTS 15
#define TRUE 1
#define FALSE 0

// En struct, hvori der er oplysninger om eleverne, oprettets. Bruger 'typedef' af praktiske årsager i programmet.
typedef struct 
{
	int nummer;
	char navn[N];
	char efternavn[N];
	char klasse;
	int karakter[10];
	double snit;
}elev_data;

// En struct, hvori der er oplysninger om klasserne, oprettes.
typedef struct 
{
	char klasse;
	double snit;
}klasse_data;

// En enum oprettes af praktiske årsager til senere funktioner, hvor det bliver praktisk at have navne i stedet for tal.
typedef enum 
{
	DATA_NAVN, 
	DATA_NUMMER, 
	DATA_EFTERNAVN, 
	DATA_KLASSE, 
	DATA_KARAKTERER,
	DATA_SNIT
} PRINT_TYPES;

// Prototyper, funktionerne findes efter main().
void read_file(elev_data*,int);
void read_input(char*);
void read_input2(int*);
void read_input3(char*);
void write_file(elev_data*,int,PRINT_TYPES*,int,char*,char*,int);
void snit(elev_data*,int);
void sortOn(elev_data*,int,PRINT_TYPES);
int sort_remove_count(elev_data*,int,PRINT_TYPES,void*);
void sort_remove(elev_data*,int,elev_data*,PRINT_TYPES,void*);
void snit_klasse(elev_data*,int,klasse_data*);
void samlign_klasse_snit(klasse_data*,klasse_data*);
void snit_samlign(elev_data*,int,int*,int*,int*,int);


int main()
{		
	printf("\t#######################################################\n\t\t*** C PROGRAM - AFLEVERINGSPROJEKT 1 ***\n\t#######################################################\n\n");
		
		/*			*/
		/* OPGAVE 2 */
		/*			*/
	
	// Struct af arrays med elevernes data, hvor 'STUDENTS' angiver antallet af elever.	
	elev_data e[STUDENTS];
	char k[2];
	int a_size;
	
	// Funktionen Læser alt data i tekstfilen og gemmer i 'e' og sorterer i tilhørende arrays.
	read_file(e, STUDENTS);
	// Funktionen Sorterer 'e' med hensyn til klasse. 3. parameter bestemmer hvad der sorteres på i 'e'
	sortOn(e, STUDENTS, DATA_KLASSE);
	// Funktionen Læser klassebegnelse fra en fil og sættes i 'k'.
	read_input(k);

	// a_size (array size) variablen bliver sat, idet funktionen kaldes. Den ignorerer alt andet end det der bliver sorteret på.
	// I dette tilfælde bliver sorteret på den klassebetegnelse funktionen ovenover fik, således tælles der hvor mange pladser
	// det nye struct array skal have.
	// sort_remove_count(Det der skal sorteres med, Angiver antallet af elever(størrelsen af arrayet), Angiver hvad der skal sorteres på, Sortering med henssyn til input)
	a_size = sort_remove_count(e, STUDENTS, DATA_KLASSE, k);
	
	// Det nye struct array 'new_e' deklareres.
	elev_data new_e[a_size];
	
	// Funktionen har næsten samme funktion som 'sort_remove_count'. I stedet fjernes den alt det data 
	// der ikke skal bruges. Dataen der bliver sorteret på sættes i det lige før dekarerede 'new_e'.
	sort_remove(e, STUDENTS, new_e ,DATA_KLASSE, k);
	
	// Funktionen sorterer på elevernes navne i 'new_e'
	sortOn(new_e, a_size, DATA_NAVN);
	
	// Her udnyttes den tidligere deklarerede enum. type bestemmer hvilke data jeg gerne vil have fra den enkelte elev. type skal også angive hvor mange data jeg gerne vil have.
	// I dette tilfælde er der 4. stk data: DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN.
	PRINT_TYPES type[4] = {DATA_KLASSE,DATA_NUMMER,DATA_NAVN,DATA_EFTERNAVN};
	
	// Funktionen skriver den data jeg har valgt ovenover 'type' fra 'new_e' til en tekstfil 'OPGAVE2.txt' og udsrkiver derefter den valgte data til consollen 'TRUE'.
	// write_file(Det der skal sorteres med(struct arrayet), Størrelse af det der sorteres med(størrelsen af struct arrayet), Hvilken type af data der skal udskrives, Antallet af forskelligt data, Tekstfilen der skal udskrives til, om der skal udskrives til consollen TRUE = 1 = JA - FALSE = 0 = NEJ)
	write_file(new_e, a_size, type, 4, "OPGAVE2.txt","w", TRUE);
	
		/*			*/
		/* OPGAVE 3	*/  
		/*			*/

	PRINT_TYPES type2[5] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_KARAKTERER};
	write_file(new_e, a_size, type2, 5, "OPGAVE3.txt","w", TRUE);
	
		/*			*/
		/* OPGAVE 4 */
		/*			*/
		
	// Funktionen beregner elevenes snit i 'new_e'
	snit(new_e, a_size);
	
	PRINT_TYPES type3[5] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_SNIT};
	write_file(new_e, a_size, type3, 5, "OPGAVE4.txt","w", TRUE);
	
		/*			*/
		/* OPGAVE 5	*/
		/*			*/
	
	// Funktionen beregner elevenes snit i 'e'
	snit(e, STUDENTS);
	
	PRINT_TYPES type4[5] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_SNIT};
	write_file(e, STUDENTS, type4, 5, "OPGAVE5.txt","w", TRUE);
	
		/*			*/
		/* OPGAVE 6	*/
		/*			*/
	
	// Nyt struct array oprettes, hvor henholdsvis klasse A,B,C bliver tildelt et bogstav som repræsenterer	klassen.
	klasse_data klasser[3];
	klasser[0].klasse = 'A';
	klasser[1].klasse = 'B';
	klasser[2].klasse = 'C';
	FILE *prt = fopen("OPGAVE6.txt","w");
	
	// Funktionen kaldes. Hver enkelt klasses snit beregnes og sættes i struct arrayet klasser.
	snit_klasse(e, STUDENTS, klasser);		
	
	printf("\n[OPGAVE6]\n\n");
	printf("KLASSE A SNIT: %.2lf\nKLASSE B SNIT: %.2lf\nKLASSE C SNIT: %.2lf\n",klasser[0].snit, klasser[1].snit, klasser[2].snit);
	fprintf(prt,"KLASSE A SNIT: %.2lf\nKLASSE B SNIT: %.2lf\nKLASSE C SNIT: %.2lf\n",klasser[0].snit, klasser[1].snit, klasser[2].snit);
	fclose(prt);
	
		/*			*/
		/* OPGAVE 7	*/
		/*			*/
	
	// Struct array klasser2 deklareres.
	klasse_data klasser2[2];
	prt = fopen("OPGAVE7.txt","w");
	
	// Funkionen samligner hvert enkelt klasses gennemsnit og sætter henholdsvis det bedste og dårligste snit i array plads 0 og 1.	
	samlign_klasse_snit(klasser,klasser2);
	
	printf("\n[OPGAVE7]\n\n");
	printf("Klasse med bedste snit: [KLASSE %c] %.2lf\n",klasser2[0].klasse, klasser2[0].snit);
	fprintf(prt,"Klasse med bedste snit: [KLASSE %c] %.2lf\n",klasser2[0].klasse, klasser2[0].snit);
	fclose(prt);
	
		/*			*/
		/* OPGAVE 8	*/
		/*			*/
		
	prt = fopen("OPGAVE8.txt","w");
	printf("\n[OPGAVE8]\n\n");
	printf("Klasse med dårligst snit: [KLASSE %c] %.2lf\n",klasser2[1].klasse, klasser2[1].snit);
	fprintf(prt, "Klasse med dårligst snit: [KLASSE %c] %.2lf\n",klasser2[1].klasse, klasser2[1].snit);
	fclose(prt);
	
		/*			*/
		/* OPGAVE 9	*/
		/*			*/
	
	// Array størrelse bestemmes med henssyn til klasse A
	a_size = sort_remove_count(e,STUDENTS, DATA_KLASSE, "A");
	elev_data new_e2[a_size];
	
	// Alt fjernes på nær eleverne i klasse A
	sort_remove(e, STUDENTS, new_e2 , DATA_KLASSE, "A");
	
	// Der sortes på snit, således det bedste snit ligger på den første plads i new_e2
	sortOn(new_e2, a_size, DATA_SNIT);
	
	// Data om eleven med det bedste snit i A udskrives til fil (ikke til consol)
	PRINT_TYPES type6[5] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_SNIT};
	write_file(&new_e2[0], 1, type6, 5, "OPGAVE9.txt","w", FALSE);
	
	// Samme fremgangsmåde med klasse B (ikke til consol)
	a_size = sort_remove_count(e,STUDENTS, DATA_KLASSE, "B");
	elev_data new_e3[a_size];
	sort_remove(e, STUDENTS, new_e3 ,DATA_KLASSE, "B");
	sortOn(new_e3, a_size, DATA_SNIT);
	
	PRINT_TYPES type7[5] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_SNIT};
	write_file(&new_e3[0], 1, type7, 5, "OPGAVE9.txt","a+", FALSE);
	
	// Samme fremgangsmåde med klasse C. Der udskrives til consol. Der skal først srkives til consol til sidst, da alt dataen til filen OPGAVE9.txt først ligger der her.
	a_size = sort_remove_count(e, STUDENTS, DATA_KLASSE, "C");
	elev_data new_e4[a_size];
	sort_remove(e, STUDENTS, new_e4 ,DATA_KLASSE, "C");
	sortOn(new_e4, a_size, DATA_SNIT);
	
	PRINT_TYPES type8[5] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_SNIT};
	write_file(&new_e4[0], 1, type8, 5, "OPGAVE9.txt","a+", TRUE);
	
		/*				*/
		/*  OPGAVE 10	*/
		/*				*/	
	
	// der sorteres på snit. Det bedste snit ligger på første plads i arrayet.
	sortOn(e, STUDENTS, DATA_SNIT);
	PRINT_TYPES type9[5] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_SNIT};
	write_file(&e[0], 1, type9, 5, "OPGAVE10.txt","w", TRUE);
	
		/*				*/
		/*  OPGAVE 11	*/
		/*				*/	
	
	// der sorteres på snit. Det dårligste snit ligger på sidste plads i arrayet.
	sortOn(e, STUDENTS, DATA_SNIT);
	PRINT_TYPES type33[5] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_SNIT};
	write_file(&e[STUDENTS-1], 1, type33, 5, "OPGAVE11.txt","w", TRUE);
	
		/*				*/
		/*  OPGAVE 12	*/
		/*				*/	
	
	// Variablerne skal bliver sat i funktionen nedenunder.	
	int countA=0,countB=0,countC=0;
	prt = fopen("OPGAVE12.txt","w");
	
	// Funktionen bestemmer hvor mange elever der hvar et snit på 2 og derover i de enkelte klasser hver for sig, når 'flaget' er 1.
	// antallet bliver sat i henholdsvis countA, countB og countC efter hvilken klasse det er.
	snit_samlign(e,STUDENTS,&countA,&countB,&countC,1);

	printf("\n[OPGAVE12]\n\n");
	printf("Snit 2 og derover [Klasse A]: %d\nSnit 2 og derover [Klasse B]: %d\nSnit 2 og derover [Klasse C]: %d\n",countA, countB, countC);
	fprintf(prt,"Snit 2 og derover [Klasse A]: %d\nSnit 2 og derover [Klasse B]: %d\nSnit 2 og derover [Klasse C]: %d\n",countA, countB, countC);
	fclose(prt);
	
		/*				*/
		/*  OPGAVE 13	*/
		/*				*/	
		
	printf("\n[OPGAVE13]\n\n");
	printf("KLASSE - ELEVNR. - NAVN - KARAKTERER - GENNEMSNIT\n");
	
	// Funktionen udskrever de elever der har et snit på 2 og derunder, når flaget er 0.
	snit_samlign(e,STUDENTS,&countA,&countB,&countC,0);

		/*				*/
		/*  OPGAVE 15	*/
		/*				*/
	
	// Funktionen sorterer på nummer	
	sortOn(e, STUDENTS, DATA_NUMMER);
	PRINT_TYPES type11[6] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_KARAKTERER, DATA_SNIT};
	write_file(e, STUDENTS, type11, 6, "OPGAVE15.txt","w", TRUE);
	
		/*				*/
		/*  OPGAVE 16	*/
		/*				*/
	
	// Funktionen sorterer på navn	
	sortOn(e, STUDENTS, DATA_NAVN);
	PRINT_TYPES type12[6] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_KARAKTERER, DATA_SNIT};
	write_file(e, STUDENTS, type12, 6, "OPGAVE16.txt","w", TRUE);
	
		/*				*/
		/*  OPGAVE 17	*/
		/*				*/
	
	// Funktionen sorterer på snit
	sortOn(e, STUDENTS, DATA_SNIT);
	PRINT_TYPES type13[6] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_KARAKTERER, DATA_SNIT};
	write_file(e, STUDENTS, type13, 6, "OPGAVE17.txt","w", TRUE);
	
		/*				*/
		/*  OPGAVE 18	*/
		/*				*/
	
	int k2;
	
	// Læser elevnummer fra en fil og sættes i 'k2'.
	read_input2(&k2);
	
	//Sorterer på elevnummer fra fil og sætter elevens oplysninger i nye structarray
	a_size = sort_remove_count(e,STUDENTS,DATA_NUMMER, &k2);
	elev_data new_e5[a_size];
	sort_remove(e, STUDENTS, new_e5, DATA_NUMMER, &k2);
	
	PRINT_TYPES type14[6] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_KARAKTERER, DATA_SNIT};
	write_file(new_e5, a_size, type14, 6, "OPGAVE18.txt","w", TRUE);
	
		/*				*/
		/*  OPGAVE 19	*/
		/*				*/
		
	char k3[10];
	
	// Læser navn fra en fil og sættes i 'k3'.
	read_input3(k3);
	
	// Sorterer på navn fra fil og sætter elevens oplysninger i nye structarray
	a_size = sort_remove_count(e,STUDENTS,DATA_NAVN,k3);
	elev_data new_e6[a_size];
	sort_remove(e, STUDENTS, new_e6, DATA_NAVN,k3);
	
	PRINT_TYPES type15[6] = {DATA_KLASSE, DATA_NUMMER, DATA_NAVN, DATA_EFTERNAVN, DATA_KARAKTERER, DATA_SNIT};
	write_file(new_e6, a_size, type15, 6, "OPGAVE19.txt","w", TRUE);
	
		/*				*/
		/*  OPGAVE22	*/
		/*				*/
		
	
		
	
return 0;
}

void sortOn(elev_data *elev_array, int size, PRINT_TYPES type)
{
	int current;
	for(current=0;current<size;current++)
	{
		elev_data *temp = &elev_array[current];
		int next;
		for(next=current+1;next<size;next++) 
		{
			if(type==DATA_NAVN) 
			{
				if(strcmp(temp->navn, elev_array[next].navn) > 0)
				{
					elev_data temp2 = elev_array[next];
					elev_array[next] = *temp;
					elev_array[current] = temp2;
				}
			} 
			else if(type==DATA_NUMMER) 
			{
				if(temp->nummer > elev_array[next].nummer)
				{
					elev_data temp2 = elev_array[next];
					elev_array[next] = *temp;
					elev_array[current] = temp2;
				}
			} 
			else if(type==DATA_KLASSE)
			{
				if(temp->klasse > elev_array[next].klasse)
				{
					elev_data temp2 = elev_array[next];
					elev_array[next] = *temp;
					elev_array[current] = temp2;
				}
			}
			else if(type==DATA_SNIT) 
			{
				if(temp->snit < elev_array[next].snit)
				{
					elev_data temp2 = elev_array[next];
					elev_array[next] = *temp;
					elev_array[current] = temp2;
				}			} 
			else if(type==DATA_KARAKTERER) 
			{
				if(temp->karakter > elev_array[next].karakter)
				{
					elev_data temp2 = elev_array[next];
					elev_array[next] = *temp;
					elev_array[current] = temp2;
				}			
			}
		}
	}
}

void read_file(elev_data *e, int size)
{
	FILE *prt = fopen("elev_data.txt","r");
	int i;
	for(i=0;i<size;i++)
	{
		fscanf(prt,"%d %s %s %c %d %d %d %d %d %d %d %d %d %d", &e[i].nummer, e[i].navn,e[i].efternavn, &e[i].klasse,&e[i].karakter[0],
		&e[i].karakter[1],&e[i].karakter[2],&e[i].karakter[3],&e[i].karakter[4],&e[i].karakter[5],&e[i].karakter[6],&e[i].karakter[7],
		&e[i].karakter[8],&e[i].karakter[9]);		
	}						
	fclose(prt);
}

void snit(elev_data *e, int size)
{
	int i;
	int f;
	for(i=0;i<size;i++)
	{
		double sum=0;
		int noexam=0;
		for(f=0;f<10;f++)
		{
			if(e[i].karakter[f]!=-4)
			{
				sum+=e[i].karakter[f];
			}
			else
			{
				noexam++;
				
			}
		}
		e[i].snit = sum/(10-noexam);
	}	
}	

void write_file(elev_data *e, int size, PRINT_TYPES *type, int sizeTypes, char *filename, char *write_type, int print_terminal)
{
	FILE *prt1 = fopen(filename,write_type);
	int f;
	for(f=0;f<sizeTypes;f++)
	{
		if(type[f]==DATA_NAVN) 
		{
			fprintf(prt1, "NAVN - ");
		} 
		else if(type[f]==DATA_NUMMER) 
		{
			fprintf(prt1, "ELEVNR. - ");
		} 
		else if(type[f]==DATA_KLASSE)
		{
			fprintf(prt1, "KLASSE - ");
		}
		else if(type[f]==DATA_SNIT) 
		{
			fprintf(prt1, "GENNEMSNIT - ");
		} 
		else if(type[f]==DATA_KARAKTERER) 
		{
			fprintf(prt1, "KARAKTERER - ");
		}
		
	}
	fprintf(prt1, "\n");

	int i;
	for(i=0;i<size;i++)
	{
		for(f=0;f<sizeTypes;f++) 
		{
			if(type[f]==DATA_NAVN) 
			{
				fprintf(prt1, "\t%.7s ", e[i].navn);
			} 
			else if(type[f]==DATA_EFTERNAVN) 
			{
				fprintf(prt1, "%s     \t", e[i].efternavn);
			}
			else if(type[f]==DATA_KLASSE) 
			{
				fprintf(prt1, "%c ", e[i].klasse);
			} 
			else if(type[f]==DATA_NUMMER)
			{
				fprintf(prt1, "\t%d ", e[i].nummer);
			}
			else if(type[f]==DATA_SNIT) 
			{
				fprintf(prt1, "     \t%.1lf ", e[i].snit);
			} 
			else if(type[f]==DATA_KARAKTERER) 
			{
				fprintf(prt1, "%.02d %.02d %.02d %.02d %.02d %.02d %.02d %.02d %.02d %.02d ", e[i].karakter[0],e[i].karakter[1],e[i].karakter[2],e[i].karakter[3],e[i].karakter[4],
				e[i].karakter[5],e[i].karakter[6],e[i].karakter[7],e[i].karakter[8],e[i].karakter[9]);
			} 
		}
		fprintf(prt1, "\n");		
	}
	fclose(prt1);
	
	prt1 = fopen(filename,"r");
	if(print_terminal == TRUE)
	{
		printf("\n[%s]\n\n", strndup(filename, strcspn(filename, ".")));
		char line[100];
		while(fgets(line, sizeof line, prt1) != NULL)
		{
			printf("%s", line);
		}
	}
	fclose(prt1);
}

void read_input(char *k)
{
	FILE *prt2 = fopen("klasse.txt","r");
	fscanf(prt2,"%s",k);
	fclose(prt2);
}

void read_input2(int *k)
{
	FILE *prt3 = fopen("elevnummer.txt","r");
	fscanf(prt3,"%d",k);
	fclose(prt3);
}

void read_input3(char *k)
{
	FILE *prt4 = fopen("elevnavn.txt","r");
	fscanf(prt4,"%s",k);
	fclose(prt4);
}

int sort_remove_count(elev_data *e, int size, PRINT_TYPES type, void *compare)
{
	int f;
	int count = 0;		
	for(f = 0; f < size; f++) 
	{
		if((type==DATA_NUMMER && e[f].nummer == *((int*)compare)) || (type==DATA_KLASSE && (e[f].klasse == *((char*)compare))) || (type==DATA_NAVN && strcmp(e[f].navn,((char*)compare)) == 0) || e[f].klasse == *((int*)compare)-32 || (type==DATA_SNIT && e[f].snit == *((double*)compare))) 
		{
			count++;
		} 
	}
	return count;
}

void sort_remove(elev_data *e, int size, elev_data *new_e, PRINT_TYPES type, void *compare)
{		
	int c = 0, f;
	for(f = 0; f < size; f++) 
	{
		if((type==DATA_NUMMER && e[f].nummer == *((int*)compare)) || (type==DATA_KLASSE && (e[f].klasse == *((char*)compare))) || (type==DATA_NAVN && strcmp(e[f].navn,((char*)compare)) == 0) || e[f].klasse == *((int*)compare)-32 || (type==DATA_SNIT && e[f].snit == *((double*)compare))) 
		{
			new_e[c] = e[f];
			c++;
		} 
	}	
}

void snit_klasse(elev_data *e, int size, klasse_data *k)
{
	int i, kc;
	double sumklasse = 0;
	int countklasse = 0;
	for(kc=0;kc<3;kc++)
	{
		sumklasse = 0;
		countklasse = 0;
		for(i=0;i<size;i++)
		{
			if(e[i].klasse==k[kc].klasse)
			{
				sumklasse+=e[i].snit;
				countklasse++;
			}
		}
		k[kc].snit = sumklasse/countklasse;
	}
}

void samlign_klasse_snit(klasse_data *k, klasse_data *k2)
{	
	if(k[0].snit>k[1].snit && k[1].snit>k[2].snit)
	{
		k2[0]=k[0];
		k2[1]=k[2];
	}
	else if(k[1].snit>k[0].snit && k[1].snit>k[2].snit)
	{
		k2[0]=k[1];
		k2[1]=k[2];
	}
	else 
	{
		k2[0]=k[2];
		k2[1]=k[1];
	}
}

void snit_samlign(elev_data *e,int size,int *countA,int *countB,int *countC,int over_eller_under)
{
	int i;
	FILE *prt = fopen("OPGAVE13.txt","w");
	for(i=0;i<size;i++)
	{
		if((over_eller_under == 1 && e[i].klasse == 'A' && e[i].snit >= 2.0))
		{
			*(countA)=*(countA)+1;
		}
		else if((over_eller_under == 1 && e[i].klasse == 'B' && e[i].snit >= 2.0))
		{
			*(countB)=*(countB)+1;
		}
		else if((over_eller_under == 1 && e[i].klasse == 'C' && e[i].snit >= 2.0))
		{
			(*countC)=(*countC)+1;
		}
		if(over_eller_under == 0 && e[i].snit <= 2.0)
		{
			printf("%c\t%d\t%s %s     \t%d %d %d %d %d %d %d %d %d %d\t%.2lf\n",e[i].klasse,e[i].nummer,e[i].navn,e[i].efternavn,e[i].karakter[0],e[i].karakter[1],e[i].karakter[2],e[i].karakter[3],
			e[i].karakter[4],e[i].karakter[5],e[i].karakter[6],e[i].karakter[7],e[i].karakter[8],e[i].karakter[9],e[i].snit);
			
			fprintf(prt,"%c\t%d\t%s %s     \t%d %d %d %d %d %d %d %d %d %d\t%.2lf\n",e[i].klasse,e[i].nummer,e[i].navn,e[i].efternavn,e[i].karakter[0],e[i].karakter[1],e[i].karakter[2],e[i].karakter[3],
			e[i].karakter[4],e[i].karakter[5],e[i].karakter[6],e[i].karakter[7],e[i].karakter[8],e[i].karakter[9],e[i].snit);
		}
	}
	fclose(prt);
}
