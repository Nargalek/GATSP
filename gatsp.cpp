#include <iostream>
#include <conio.h>
#include <algorithm>
#include <windows.h>
#include <time.h>

using namespace std;
const int ileMiast = 5;
const int populacja = 20;
const int mutrate = 0.01;

int miasta[ileMiast][ileMiast]={{0,4,5,2,1}, {5,0,2,4,1}, {3,8,0,8,4},{2,7,4,0,6}, {4,5,6,2,0}};
int droga[ileMiast]={1,2,3,4,5};
int ileGen=0;


struct element{
	int DNA[ileMiast];
	int waga[ileMiast-1];
	double fitness=0;
	int pok=0;
};

void inicjalizacja(int, int*);
void kociol(int *, int);
void zamiana(int &, int &);
void bubblesort(element *, int);
void wdroga(element *, int, int);
void fitness(element *, int , int);
void najlepszy(element *, int , element *, int);
void nowaGeneracja( element *, int, int);

element pop[populacja];
element everBest[1];

int main(){
	srand(time(NULL));

	
	for(int i=0;i<populacja;i++){
		inicjalizacja(ileMiast, pop[i].DNA);
		for(int j=0;j<ileMiast;j++){
		
		cout<<pop[i].DNA[j];
		}
		cout<<"\n";
	}
	everBest[0].fitness=1000;
	
	
	while(1){
	system("CLS");
	ileGen++;
	wdroga(pop, populacja, ileMiast);
	fitness(pop,ileMiast-1, populacja);
	bubblesort(pop, populacja);
	for(int i=0;i<populacja;i++){
		cout<<"\nfit: "<<pop[i].fitness;
	//	cout<<"\nnfit: "<<pop[i].nFitness;
	}
	
	nowaGeneracja(pop, populacja, ileMiast);
	najlepszy(pop, populacja, everBest, ileGen);
	cout<<"\n\nNajlepsze rozwiazanie: "<<"\nfitness:"<<everBest[0].fitness<<"\nKolejnosc miast: ";
	for(int i=0;i<ileMiast;i++){
		cout<<everBest[0].DNA[i]<<" ";
	}
	cout<<"\nWaga: ";
	for(int i=0;i<ileMiast-1;i++){
		cout<<everBest[0].waga[i]<<" ";
	}
	cout<<"\nPokolenie: "<<everBest[0].pok;
	cout<<"\nmiasto test: "<<miasta[everBest[0].DNA[0]-1][everBest[0].DNA[1]-1];
	Sleep(500);
	
	}
	
	
	
	
	
	
	cout<<"\n\n";
	system("PAUSE");
	return 0;	
}


void inicjalizacja(int ileMiast, int ar[]){

	int droga[5]={1,2,3,4,5};
		for(int i=0;i<ileMiast;i++){
			ar[i]=droga[i];			
		}
	kociol(ar, ileMiast);
}

void nowaGeneracja(struct element ar[], int populacja, int ileMiast){
	element nPop[populacja];
	for(int i=0;i<populacja;i++){
		nPop[i]=ar[i];
	}
	for(int i=0;i<populacja;i+=2){
		for(int j=0;j<ileMiast/2;j++){
			element temp;
			int k=rand()%ileMiast;
			temp.DNA[j] = nPop[i].DNA[k];
			nPop[i].DNA[k] = nPop[i].DNA[j];
			nPop[i].DNA[j]=temp.DNA[j];
		}
	}
	for(int i=0;i<populacja;i++){
		ar[i]=nPop[i];
	}
	
}
void kociol(int ar[], int ileMiast){
	int j=0;
	for(int i=0;i<ileMiast;i++){ 
		j=rand()%ileMiast;
		zamiana(ar[i],ar[j]);
	}
}

void zamiana(int & a, int & b){
	int z = a;
	a = b;
	b = z;
}
void bubblesort(struct element ar[], int a){
		element temp;
		for(int i;i<a;i++){
			for(int i=0;i<a-1;i++){
				if (ar[i].fitness > ar[i+1].fitness){
					temp = ar[i];
					ar[i] = ar[i+1];
					ar[i+1]=temp;
				}
			}
		}
	
}

void wdroga(struct element ar[], int populacja, int ileMiast){
		for(int i=0;i<populacja;i++){
		for(int j=0;j<ileMiast-1;j++){
			ar[i].waga[j]=miasta[((ar[i].DNA[j])-1)][((ar[i].DNA[j+1])-1)];
		}		
		
	}
}

void fitness(struct element ar[], int ileMiast, int populacja){
	double w=0.0;
	for(int i=0; i<populacja;i++){
		
		for(int j=0;j<ileMiast;j++){
		
		w+=ar[i].waga[j];
	}
	ar[i].fitness=w;
	//cout<<"\ndouble w: "<<1/(w+1);
	w=0;
	}
	 
}

void najlepszy(struct element arr[], int populacja, struct element everBest[], int ileGen){
	float j=arr[0].fitness,k=1;
	for(int i=0;i<populacja;i++){
		if(arr[i].fitness<j){
			j=arr[i].fitness;
		}
		if(arr[i].fitness < everBest[0].fitness){
			everBest[0]=arr[i];
			everBest[0].pok=ileGen;
		}
	}
	cout<<"\n1: "<<(everBest[0].DNA[0]-1)<<"\n2: "<<(everBest[0].DNA[1])-1;
	cout<<"\nPokolenie: "<<ileGen<<"\nNajlepszy element: "<<j;
}
