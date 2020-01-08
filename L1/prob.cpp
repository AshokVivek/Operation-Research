/***************************
******* Vivek Pal **********
******* 17MA20048 **********
****************************

You are given a system of equations and
The Problem statement is to find
1). Row Reduce Echelon form of Matrix.
2). Rank of the Matrix.
3). if Equation is Consistent or Not?
4). No. of solutions of the System of Equations.
for Row Reducing Guass-Jorden Method is being used.
And you have to write a menu driven program to ask for the operation.
*******************************/
//Used Libraries at header
#include<stdio.h>
#include<bits/stdc++.h>
#include<vector>
using namespace std;
//
// This print function is used to print a 2D
// vector in nice display for upto 3 digit elements.
void print(vector<vector<int> > A){
	int N=A.size();
	int M=A[0].size();
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			printf("%3d ", A[i][j]);
		}
		printf("\n");
	}
	return;
}
void valueEq(vector<vector<int> >& A, int x){
	int N=A.size();
	int M=A[0].size();
	if(x>=min(N,M-1)) return;
	int mint=M+1, index=0;
	for(int i=x;i<N;i++){
		int j=x;
		while(j<M && A[i][j]==0) j++;
		if(mint>j){
			mint =j;
			index=i;
		}
	}
	if(index!=x){
		for(int i=x;i<M;i++){
			int t=A[x][i];
			A[x][i]=A[index][i];
			A[index][i]=t;
		}
	}
	int sun=A[x][x];
	for(int i=x+1;i<N;i++){
		int moon=A[i][x];
		for(int j=x;j<M;j++){
			A[i][j]=sun*A[i][j]-moon*A[x][j];
		}
	}
	valueEq(A, x+1);
}
void value(vector<vector<int> >& A, int x){
	int N=A.size();
	int M=A[0].size();
	if(x>=min(N,M)) return;
	int mint=M+1, index=0;
	for(int i=x;i<N;i++){
		int j=x;
		while(j<M && A[i][j]==0) j++;
		if(mint>j){
			mint =j;
			index=i;
		}
	}
	if(index!=x){
		for(int i=x;i<M;i++){
			int t=A[x][i];
			A[x][i]=A[index][i];
			A[index][i]=t;
		}
	}
	int sun=A[x][x];
	for(int i=x+1;i<N;i++){
		int moon=A[i][x];
		for(int j=x;j<M;j++){
			A[i][j]=sun*A[i][j]-moon*A[x][j];
		}
	}
	value(A, x+1);
}
void rref(){
	printf("Please enter:- \n1). for your own made-up Matrix \n2). for given question input\n");
	int sun;
	do{cin>>sun;}while(sun<1 || sun>2);
	if(sun==2){
		int N=4, M=4;
		vector< vector<int> > A;
		int x;
		for(int i=0;i<N;i++){
			vector<int> a;
			A.push_back(a);
		}
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				A[i].push_back(i+j+3);
			}
		}
		value(A, 0);
		printf("The Row Reduced Echelon Form is :- \n");
		print(A);
		return;
	}
	printf("Please enter the size of matrix in 2D form  :-  ");
	int N, M; cin>>N>>M;
	printf("Please enter the matrix :-\n");
	vector< vector<int> > A;
	int x;
	for(int i=0;i<N;i++){
		vector<int> a;
		A.push_back(a);
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>x;
			A[i].push_back(x);
		}
	}
	value(A, 0);
	printf("The Row Reduced Echelon Form is :- \n");
	print(A);
}
void rank(){
	printf("Please enter:- \n1). for your own made-up Matrix \n2). for given question input\n");
	int sun;
	do{cin>>sun;}while(sun<1 || sun>2);
	if(sun==2){
		int N=10, M=10;
		vector< vector<int> > A;
		int x;
		for(int i=0;i<N;i++){
			vector<int> a;
			A.push_back(a);
		}
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				A[i].push_back(i+j+3);
			}
		}
		value(A, 0);
		sun=0;
		for(int i=0;i<N;i++){
			int moon=0;
			for(int j=0;j<M;j++){
				if(A[i][j]==0) moon++;
			}
			if(moon==M) sun++;
		}
		printf("The Rank of the given Matrix is  %d.\n", N-sun);
		return;
	}
	printf("Please enter the size of matrix in 2D form  :-  ");
	int N, M; cin>>N>>M;
	printf("Please enter the matrix :-\n");
	vector< vector<int> > A;
	int x;
	for(int i=0;i<N;i++){
		vector<int> a;
		A.push_back(a);
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>x;
			A[i].push_back(x);
		}
	}
	value(A, 0);
	sun=0;
	for(int i=0;i<N;i++){
		int moon=0;
		for(int j=0;j<M;j++){
			if(A[i][j]==0) moon++;
		}
		if(moon==M) sun++;
	}
	printf("The Rank of the given Matrix is  %d.\n", N-sun);
}
void eqnConst(){
	printf("Please enter No. of Variable and No. of equations respectively :- ");
	int N, M; cin>>M>>N;
	printf("Please enter Augumented Matrix of the given equations :-\n");
	M=M+1; // Since No. of columns will be one more than No.of Variables
	vector< vector<int> > A;
	int x;
	for(int i=0;i<N;i++){
		vector<int> a;
		A.push_back(a);
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>x;
			A[i].push_back(x);
		}
	}
	valueEq(A, 0);
	for(int i=0;i<N;i++){
		int j=0;
		while(j<M && A[i][j]==0) j+=1;
		if(j==M-1){
			printf("System of Equations is Inconsistent.\n");
			return;
		}
	}
	printf("System of Equations is Consistent.\n");
}
void eqnSoln(){
	printf("Please enter No. of Variable and No. of equations respectively :- ");
	int N, M; cin>>M>>N;
	printf("Please enter Augumented Matrix of the given equations\n");
	M+=1; // Since No. of columns will be one more than No.of Variables
	vector< vector<int> > A;
	int x;
	for(int i=0;i<N;i++){
		vector<int> a;
		A.push_back(a);
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>x;
			A[i].push_back(x);
		}
	}
	valueEq(A, 0);
	for(int i=0;i<N;i++){
		int j=0;
		while(j<M && A[i][j]==0) j+=1;
		if(j==M-1){
			printf("No Solution Exists.\n");
			return;
		}
	}
	int zz=0;
	for(int i=0;i<N;i++){
		if(A[i][M-1]==0) zz+=1;
	}
	for(int i=0;i<N;i++){
		A[i].pop_back();
	}
	M-=1;
	value(A, 0);
	int sun=0;
	for(int i=0;i<N;i++){
		int moon=0;
		for(int j=0;j<M;j++){
			if(A[i][j]==0) moon++;
		}
		if(moon==M) sun++;
	}
	if(zz==N){
		printf("Trivial Solution Exists and");
		if(N-sun==M) printf(" which is unique solution.\n");
		else printf(" other infinitely many solutions exists.\n");
	}else{
		if(N-sun==M) printf("A Unique Solution exists.\n");
		else printf("Infinitely Many Solutions exists.\n");
	}
}
int main(){

	printf("Please Enter for finding :- \n");
	printf("1). Row Reduce Echelon form of Matrix.\n");
	printf("2). Rank of the Matrix.\n");
	printf("3). if Equation is Consistent or Not?\n");
	printf("4). No. of solutions of the System of Equations\n");
	printf("0). for Exit from the Process.\n");
	do{
		printf("\n---------------------------------------------------------\n");
		printf("Please enter choice according to Process to execute :- ");
		int sun; cin>>sun;
		if(sun==0) break;
		if(sun==1) rref();
		if(sun==2) rank();
		if(sun==3) eqnConst();
		if(sun==4) eqnSoln();
	}while(true);
	return 0;
}
