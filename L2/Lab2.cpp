/***************************
******* Vivek Pal **********
******* 17MA20048 **********
****************************
You are given a system of equations and
The Problem statement is to find
set non-basic variables equal to zero and solve the remaining
 basic variables. Find all basic solutions for the
following set of equations.
for Row Reducing Guass-Jorden Method is being used.
*******************************/
#include<bits/stdc++.h>
using namespace std;
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
void printD(vector<vector<double> > A){
	int N=A.size();
	int M=A[0].size();
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			printf("%lf ", A[i][j]);
		}
		printf("\n");
	}
	return;
}
void print1D(vector<int> A){
	int N=A.size();
	for(int i=0;i<N;i++)
		printf("%d ", A[i]);
	printf("\n");
}
void print1DDouble(vector<double> A){
	int N=A.size();
	for(int i=0;i<N;i++)
		printf("%lf ", A[i]);
	printf("\n");
}
vector<int> grosper(int k, int N){
	int set=(1<<k)-1;
	int lim=(1<<N);
	vector<int> ans;
	while(set<lim){
		ans.push_back(set);
		int c=set & -set;
		int r=set+c;
		set=(((r^set)>>2)/c)|r;
	}
	return ans;
}
vector<int> binar(int k, int N){
	vector<int> ans;
	while(N>0){
		ans.push_back(N%2);
		N=N/2;
		k--;
	}
	while(k--) ans.push_back(0);
	return ans;
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
void valueEqDouble(vector<vector<double> >& A, int x){
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
			double t=A[x][i];
			A[x][i]=A[index][i];
			A[index][i]=t;
		}
	}
	double sun=A[x][x];
	for(int i=x+1;i<N;i++){
		double moon=A[i][x];
		for(int j=x;j<M;j++){
			A[i][j]=sun*A[i][j]-moon*A[x][j];
		}
	}
	valueEqDouble(A, x+1);
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
int rankt(vector<vector<int> > A){
	value(A, 0);
	int sun=0;
	int N=A.size();
	int M=A[0].size();
	for(int i=0;i<N;i++){
		int moon=0;
		for(int j=0;j<M;j++){
			if(A[i][j]==0) moon++;
		}
		if(moon==M) sun++;
	}
	return N-sun;
}
int eqnConst(vector<vector<int> > A){
	int N=A.size();
	int M=A[0].size();
	valueEq(A, 0);
	for(int i=0;i<N;i++){
		int j=0;
		while(j<M && A[i][j]==0) j+=1;
		if(j==M-1) return 0;
	}
	return 1;
}
vector<double> backSub(vector<vector<double> >A) 
{ 
	int N=A.size();
	vector<double> ans(N);
	for (int i = N-1; i >= 0; i--) 
	{ 
		ans[i] = A[i][N];
		for (int j=i+1; j<N; j++)
			ans[i] -= A[i][j]*ans[j];
		ans[i] = ans[i]/A[i][i]; 
	} 
	return ans;
} 
void solve(){
	printf("Please enter no. of distinct variables and no. of equations :- ");
	int N, M; cin>>M>>N;
	printf("Please Enter the Augumented Matrix :- \n");
	M+=1;
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
	
	vector< vector<int> > B;
	for(int i=0;i<N;i++){
		vector<int> a;
		B.push_back(a);
		for(int j=0;j<M-1;j++)
			B[i].push_back(A[i][j]);
	}
	
	int flag=eqnConst(A);
	if(flag==0){
		printf("Given System of Equations is Inconsistent\n");
		return;
	}
	int R=rankt(A);
	valueEq(A, 0);
	int kk=R, nn=M-1;
	//print(A);
	
	vector<int> gg=grosper(kk, nn);
	//print1D(gg);
	for(int k=0;k<gg.size();k++){
		vector<int> bb=binar(M-1, gg[k]);
		//print1D(bb);
		vector<vector<double> > soln;
		for(int ii=0;ii<R;ii++){
			vector<double> a;
			soln.push_back(a);
		}
		for(int ii=0;ii<R;ii++){
			for(int jj=0;jj<M-1;jj++){
				if(bb[jj]==1){
					soln[ii].push_back((double)A[ii][jj]);
				}
			}
			soln[ii].push_back((double)A[ii][M-1]);
		}
		//printD(soln);
		valueEqDouble(soln, 0);
		//printf(" --- \n");
		//printD(soln);
		vector<double> ans=backSub(soln);
		//printf(" ---------- \n");
		//print1DDouble(ans);
		//printf("-------------------\n");
		printf("Taking ");
		for(int ii=0;ii<M-1;ii++)
			if(bb[ii]==0) printf("%d ", ii+1);
		printf("as Non-Basic Variable, we Have solution ");
		int xx=0;
		for(int jj=0;jj<M-1;jj++){
			if(bb[jj]==0) printf("0 ");
			else printf("%lf ", ans[xx++]);
		}
		int ff=0;
		for(int ii=0;ii<ans.size();ii++)
			if(ans[ii]<0) ff=1;
		if(ff) printf("  ----  But this not a basic feasible solution");
		
		printf("\n");
		//printf("--------------------\n");
	}
}
int main(){
	
	solve();
	return 0;
}
