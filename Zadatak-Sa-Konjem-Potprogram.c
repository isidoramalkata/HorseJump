#include <stdio.h>
#include <stdlib.h>
#define MAXBR 10

typedef struct point {
    int i,j;
    struct point *a,*b,*c,*d,*e,*f,*g,*h;
} node;

void promeni(node **tren,node **novi,int (*matrica)[MAXBR][MAXBR], int *brojac, node *(*stek)[MAXBR*MAXBR],int p,int q, node **pok ,int *x)
{
    *novi=(node*)malloc(sizeof(node));
    (*brojac)++;
    (*novi)->i=p;								
    (*novi)->j=q;
    (*matrica)[(*novi)->i-1][(*novi)->j-1]=1;
    if ((*stek)[(*brojac)-1]!=NULL) free((*stek)[(*brojac)-1]);
    (*stek)[(*brojac)-1]=*novi;
	*pok=*novi;
    *tren=*novi;
	*x=0;
}

int main(){
    int v,k,x,y,m[MAXBR][MAXBR],i,j,br=1;
    node *novi,*prvi,*tren,*stack[MAXBR*MAXBR];	//stek za cuvanje odluka, pre skoka na novo polje, staro se sacuva na steku
	
    printf("Unesite Dimenzije Table:\n");
    scanf("%d %d", &v, &k );
	if (v<1 || v>MAXBR ||k<1 ||k>MAXBR) exit(-1);
	printf("Unesite Polozaj Konja\n");
    scanf("%d %d",&x,&y);
	if (x<1 || x>v || y<1 || y>k) exit(-1);
	// Inicijalizacija Matrice i steka
    for (i=0; i<v; i++) 				
        for (j=0; j<k; j++)
            m[i][j]=0;
    m[x-1][y-1]=1;

	for (i=0;i<MAXBR*MAXBR;stack[i]=NULL,i++);
	prvi=(node*)malloc(sizeof(node));
    stack[0]=prvi;
    prvi->i=x; prvi->j=y; x=0; novi=prvi;	
	// Formiranje Stabla i popunjavanje steka sa predjenim potezima

	// izlazi ukoliko je brojac jednak dimenzijama matrice, jer je tada presao sva polja(pun stek), ili kad je jednak 0, jer je tada prosao sve mogucnosti(prazan stek)
    while ((br<v*k) && (br!=0)) {
	//postavljanje novih elemenata na nill, x sluzi kao flag da li je u prethodnij interaciji napravljen novi struct, ili skinut stari sa steka
	if (x==0) {novi->e=NULL;novi->g=NULL;novi->c=NULL;novi->f=NULL;novi->a=NULL;novi->b=NULL;novi->h=NULL;novi->d=NULL;tren=novi;}

	//gore desno ?
    if ((0<tren->i-2) && (tren->i-2<=v) && (tren->j+1<=k) && (tren->j+1>0) && (m[tren->i-3][tren->j]==0) && (tren->a==NULL)){
		promeni(&tren,&novi,&m, &br,&stack,tren->i-2,tren->j+1,&(tren->a),&x);

        }	//gore levo ?
        else if ((0<tren->i-2) && (tren->i-2<=v) && (tren->j-1<=k) && (tren->j-1>0) && (m[tren->i-3][tren->j-2]==0) && (tren->b==NULL)){
				promeni(&tren,&novi,&m, &br,&stack,tren->i-2,tren->j-1,&(tren->b),&x);

			}	//desno gore ?
			else if ((0<tren->i-1) && (tren->i-1<=v) && (tren->j+2<=k) && (tren->j+2>0) && (m[tren->i-2][tren->j+1]==0) && (tren->c==NULL)){
					promeni(&tren,&novi,&m, &br,&stack,tren->i-1,tren->j+2,&(tren->c),&x);

				}	//levo gore ?
				else if ((0<tren->i-1) && (tren->i-1<=v) && (tren->j-2<=k) && (tren->j-2>0) && (m[tren->i-2][tren->j-3]==0) && (tren->d==NULL)){
					promeni(&tren,&novi,&m, &br,&stack,tren->i-1,tren->j-2,&(tren->d),&x);

					}	//dole desno ?
					else if ((0<tren->i+2) && (tren->i+2<=v) && (tren->j+1<=k) && (tren->j+1>0) && (m[tren->i+1][tren->j]==0) && (tren->e==NULL)){
							promeni(&tren,&novi,&m, &br,&stack,tren->i+2,tren->j+1,&(tren->e),&x);

						}	//dole levo ?
						else if ((0<tren->i+2) && (tren->i+2<=v) && (tren->j-1<=k) && (tren->j-1>0) && (m[tren->i+1][tren->j-2]==0) && (tren->f==NULL)){
								promeni(&tren,&novi,&m, &br,&stack,tren->i+2,tren->j-1,&(tren->f),&x);

							}	//desno dole ?
							else if ((0<tren->i+1) && (tren->i+1<=v) && (tren->j+2<=k) && (tren->j+2>0) && (m[tren->i][tren->j+1]==0) && (tren->g==NULL)){
									promeni(&tren,&novi,&m, &br,&stack,tren->i+1,tren->j+2,&(tren->g),&x);

								}	//levo dole ?
								else if ((0<tren->i+1) && (tren->i+1<=v) && (tren->j-2<=k) && (tren->j-2>0) && (m[tren->i][tren->j-3]==0) && (tren->h==NULL)){
										promeni(&tren,&novi,&m, &br,&stack,tren->i+1,tren->j-2,&(tren->h),&x);
										
									}	//nema gde ?
									else if (br>0){x=1; m[tren->i-1][tren->j-1]=0;
											if (stack[br]!=NULL) {free(stack[br]); stack[br]=0;}
											tren=stack[(--br)-1];
									}
		}
    if (br==0) printf("ne \n");
    if (br==v*k) {printf("da \n");	

	for (i=1;i<=v;i++) for(j=1;j<=k;j++) m[i][j]=0;		//Postavljanje svih elemenata matrice na 0
	for (i=0;i<br;i++)									//ispisivanje pozicija konja
	{
		printf("korak %d : \n",i+1);
		m[stack[i]->i][stack[i]->j]=1;
		for (x=1;x<=v;x++){
			for (y=1;y<=k;y++)
				printf("%d ",m[x][y]);
			printf("\n");}
	}
	for (i=0;i<br;i++){free(stack[br]);}}
}