#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <windows.h>

using namespace std;

const int mile=6;
const int osobniki=50;
const int potomkowie=25;
const int ilemutacji=5;
const int ilegeneracji=1000;


int populacja[osobniki+potomkowie][mile];
int fitness[osobniki+potomkowie];
unsigned int bestfit=1000;
double bestdna[mile];
double bestgen;

int przystanki;
int generacja;


int koordy(int, int, int);
void import(vector<int>&, int &);
void init(int [][mile],int, int);
void zamiana(int &, int &);
void nfitness(int *, int [][mile],vector <int> , int, int);
void cross(int [][mile], int*, int, int, int);
void bubblesort(int [][mile], int *, int, int);
void mutacja(int [][mile], int, int,int);
void najlepszy(int [][mile], int *, int,unsigned int&,double *,double &, int, int);


int main(){
	srand(time(NULL));
	//vector <int> miasta;
	vector <int> odleglosci;
	int g=0;
	
	import(odleglosci, przystanki);
	init(populacja,przystanki,osobniki+potomkowie);
	
	for(int i=0;i<osobniki;i++){
		for(int j=0;j<przystanki;j++){
		cout<<" "<<populacja[i][j];
	}
		cout<<"\n";
	}
	cout<<"\n";
	for(int i=0;i<odleglosci.size();i++){
	cout<<" "<<odleglosci[i];
	
	}
	
	cout<<"\nprzystanki: "<<przystanki;
	
//GA
	nfitness(fitness,populacja,odleglosci,mile,osobniki+potomkowie);

	
	//bubblesort(populacja, fitness,osobniki+potomkowie,mile);
	cout<<"\nfitness: ";
	for(int i=0;i<osobniki;i++){
	cout<<" "<<fitness[i];
	}
	while(g<ilegeneracji){
    system("CLS");
	generacja++;
	mutacja(populacja,mile,ilemutacji,osobniki+potomkowie);	
	cross(populacja,fitness,osobniki,potomkowie,mile);
	nfitness(fitness,populacja,odleglosci,mile,osobniki+potomkowie);
    bubblesort(populacja, fitness,osobniki+potomkowie,mile);
    najlepszy(populacja, fitness, generacja, bestfit, bestdna, bestgen, mile, osobniki);
    
	cout<<"\nfitness2: ";
	for(int i=0;i<osobniki;i++){
	cout<<" "<<fitness[i];
	}
//	for(int i=0;i<mile;i++){
//		cout<<" "<<populacja[0][i];
//	}

    Sleep(50);
    g++;
    //system("PAUSE");
	}
	
	ofstream wyjscie("wynik.txt");
	wyjscie<<bestfit;
	wyjscie<<"\n";
	for(int i=0; i<mile;i++){
		wyjscie<<bestdna[i]<<" ";
	}
	wyjscie.close();
	

	
	cout<<"\n\n\n";
	system("PAUSE");
	return 0;
}

int koordy(int a, int b, int przystanki){
	int c=0;
	c=((a-1)*przystanki)+b-1;
	return c;
}

void import(vector <int>&o, int &przystanki){
	ifstream dane("num.txt");
	dane>>przystanki;
	
	while (true)			
	{
		int x;		
		dane >>x;	 
		
		o.push_back(x); 
		if (dane.eof())break;
	}

	
}

void init(int populacja[][mile], int przystanki, int osobniki){
	for(int j=0;j<=osobniki;j++){
	
	for(int i=0;i<przystanki;i++){
		populacja[j][i]=(i+1);
		
	}
		for(int i=0;i<przystanki;i++){
			int k=rand()%przystanki;
			zamiana(populacja[j][i],populacja[j][k]);
		}
	}
	
}

void zamiana(int & a, int & b){
	int z = a;
	a = b;
	b = z;
}

void nfitness(int fitness[], int populacja[][mile],vector <int> odleglosci, int mile, int osobniki){
		//double w=0;
		for(int i=0;i<osobniki;i++){
			fitness[i]=0;
		for(int j=0;j<=mile;j++){
			if(j<mile){
			fitness[i]+=odleglosci[koordy(populacja[i][j],populacja[i][j+1],mile)];
			//cout<<"\ni, j: "<<i<<","<<j<<"\nfit:: "<<fitness[i]<<" koor:"<<koordy(populacja[i][j],populacja[i][j+1],mile);
			}else if(j==mile){
			fitness[i]+=odleglosci[koordy(populacja[i][j],populacja[i][0], mile)];
			//cout<<"\ni, j: "<<i<<","<<j<<"\nfit:: "<<fitness[i]<<" koor:"<<koordy(populacja[i][j],populacja[i][0],mile);
			//cout<<"\ntest: "<<odleglosci[koordy((populacja[i][j]),(populacja[i][0]),mile)]<<" j: "<<j;
			}
			
			//w+=fitness[i];
		}
				
		//cout<<"\nfitness12: "<<fitness[i];	
	}

//	for(int i=0; i<osobniki;i++){
//		fitness[i]=(1/fitness[i]);
//	}
	//w=0;
	 
}

void cross(int populacja[][mile], int fitness[], int osobniki, int potomkowie, int mile){
	
	for(int c=0;c<potomkowie;c++){
		int p=mile/2+1, g=0;
		int x=rand()%osobniki;
		int z=rand()%osobniki;
//		cout<<"\nlos: "<<x<<" "<<z;
		for(int b=0;b<mile;b++){
		populacja[osobniki+c][b]=populacja[z][b];
		}
//			cout<<"\ncross: ";
//			for(int a=0;a<mile;a++){
//				cout<<populacja[osobniki+c][a];
//			}cout<<"\np:"<<p;
		for(int j=0;j<mile;j++){
			for(int i=p; i<mile;i++){
				if(populacja[x][j]==populacja[z][i] ){
					swap(populacja[osobniki+c][p],populacja[osobniki+c][i]);
					p++;
//					cout<<"\nDZIALA!!! "<<p;
				}
				
				}
			
		}
//cout<<"\ntest nowego: ";
//			for(int q=0;q<mile;q++){
//				cout<<populacja[osobniki+c][q];
//			}cout<<"\ntest starego: ";
//			for(int q=0;q<mile;q++){
//				cout<<populacja[z][q];
//			}		
//cout<<"\n";
}	
	
	
}


void bubblesort(int populacja[][mile], int fitness[], int osobniki, int mile){
		double temp;
		int temp2;
		for(int i=0;i<osobniki-1;i++){
			for(int j=0;j<osobniki-1;j++){
				if (fitness[j] > fitness[j+1]){
					temp = fitness[j];
					fitness[j] = fitness[j+1];
					fitness[j+1]=temp;
					
					for(int k=0;k<mile;k++){
					
					temp2 = populacja[j][k];
					populacja[j][k] = populacja[j+1][k];
					populacja[j+1][k]=temp2;
					}
				}
			}
		}
	
}
void mutacja(int populacja[][mile], int mile, int ilemutacji, int osobniki){
	for(int i=0;i<=ilemutacji;i++){
		int y=rand()%osobniki;
		int x=rand()%mile;
		int z=rand()%mile;
		swap(populacja[y][x],populacja[y][z]);
	}

}

void najlepszy(int populacja[][mile],int fitness[],int generacja, unsigned int &bestfit, double bestdna[], double &bestgen, int mile, int osobniki){
	double j=fitness[0],k=1;
	for(int i=0;i<osobniki;i++){
		if(fitness[i]<j){
			j=fitness[i];
		}
		if(fitness[i] < bestfit){
			bestfit=fitness[i];
			bestgen=generacja;
			for(int u=0;u<mile;u++){
				bestdna[u]=populacja[0][u];
			}
		}
	}
	cout<<"\n DNA: ";
	for(int i=0;i<mile;i++){
		cout<<bestdna[i]<<" ";
	}
	cout<<"\nPokolenie: "<<generacja<<"\nNajlepszy element: "<<j<<"\nFitness: "<<bestfit;
}

