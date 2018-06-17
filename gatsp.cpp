#include <iostream>
#include <conio.h>
#include <algorithm>
//#include <random>
#include <time.h>
using namespace std;

struct element{
	int DNA[5];
	int waga[4];
	int fitness;
};

const int ileMiast = 5;
const int populacja = 10;
const int mutrate = 0.01;

int miasta[][ileMiast]={{0,4,5,2,1}, {5,0,2,4,1}, {3,8,0,8,4},{2,7,4,0,6}, {4,5,6,2,0}};
int droga[ileMiast]={1,2,3,4,5};


void inicjalizacja(int, int*);
void dziedziczenie();
void krzyzowanie();
void mutacja();
void selekcja();
void kociol(int *, int);
void zamiana(int &, int &);
void fitness(element *, int, int);
void najlepszy(element *, int);

int w, czas;


int main(){
	czas = time(NULL);
	srand(time(NULL));
	
	element pop[populacja];
	for(int i=0; i<ileMiast;i++){
	
	cout<<miasta[i][i]<<"\n";
	}
	for(int i=0;i<populacja;i++){
		inicjalizacja(ileMiast, pop[i].DNA);
	}
	
	for(int i=0;i<populacja;i++){
		for(int j=0;j<ileMiast-1;j++){
			pop[i].waga[j]=miasta[pop[i].DNA[j]][pop[i].DNA[j+1]];
		}		
		
	}
	
	for(int i=0; i<populacja;i++){
		for(int j=0;j<ileMiast-1;j++){
		cout<<pop[i].waga[j];
		}
		cout<<"\n";
	}
	
	
	cout<<"\n\n\n";
	for(int i=0; i<populacja;i++){
		for(int j=0; j<ileMiast;j++){
		cout<<pop[i].DNA[j];
		}
		cout<<"\n";
	}
	fitness(pop,ileMiast-1, populacja);
	najlepszy(pop, populacja);
	
	
	//system("CLS");
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

void fitness(struct element ar[], int ileMiast, int populacja){
	int w;
	for(int i=0; i<populacja;i++){
		w=0;
		for(int j=0;j<ileMiast;j++){
		
		w+=ar[i].waga[j];
	}
	ar[i].fitness=w;
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

void najlepszy(struct element arr[], int populacja){
	int j=arr[0].fitness,k=1;
	for(int i=0;i<populacja;i++){
		if(arr[i].fitness<j){
			j=arr[i].fitness;
			k=i+1;
		}
	}
	cout<<"\nNajlepszy element: "<<k<<" o wartosci: "<<j;
}
