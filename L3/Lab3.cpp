#include<bits/stdc++.h>
using namespace std;
void printIST(vector< vector<double> > A, vector<double> Z, vector<int> NBV, vector<int> BV){
	int N=A.size();
	int M=A[0].size();
	for(int j=0;j<M-1;j++){
		if(j==0) printf("         -X%d", NBV[j]);
		else printf("          -X%d", NBV[j]);
	}
	printf("\n");
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(A[i][j]>=0) cout<<' ';
			int x=(A[i][j]>0)?A[i][j]:(-1)*A[i][j];
			int sun=0;
			while(x>0){ x/=10; sun+=1;}
			if(A[i][j]>-1 && A[i][j]<1) sun+=1;
			for(int kk=0;kk<4-sun;kk++) printf(" ");
			printf("%lf ", A[i][j]);
		}
		printf("  = X%d\n", BV[i]);
	}
	for(int i=0;i<M;i++){
		if(Z[i]>=0) printf(" ");
		int x=(Z[i]>0)?Z[i]:(-1)*Z[i];
		int sun=0;
		while(x>0){ x/=10; sun+=1;}
		if(Z[i]>-1 && Z[i]<1) sun+=1;
		for(int kk=0;kk<4-sun;kk++) printf(" ");
		printf("%lf ", Z[i]);
	}
	printf("  = Z\n");
}
int simpleIteration(vector< vector<double> >& A, vector<double>& Z, vector<int>& NBV, vector<int>& BV, int k){
	int N=A.size();
	int M=A[0].size();
	double mint=0.00;
	int v=-1;
	for(int i=0;i<M;i++){
		if((double)Z[i]<mint){
			mint=Z[i];
			v=i;
		}
	}
	//cout<<N<<' '<<M<<' '<<mint<<' '<<v<<'\n';
	if(v<0){
		printf("Basic Solution and Basic Feasible Solution at iteration %d is  :-  ( ", k);
		for(int j=0;j<NBV.size();j++){
			printf("X%d = 0, ", NBV[j]);
		}
		for(int j=0;j<BV.size()-1;j++){
			printf("X%d = %lf, ", BV[j], A[j][M-1]);
		}
		printf("X%d = %lf )\n", BV[N-1], A[N-1][M-1]);
		printf("\nValue of Objective function is  %lf   at this BFS.\n", Z[M-1]);
		return k;
	}
	printf("Basic Solution at iteration %d is  :-  ( ", k);
	for(int j=0;j<NBV.size();j++){
		printf("X%d = 0, ", NBV[j]);
	}
	for(int j=0;j<BV.size()-1;j++){
		printf("X%d = %lf, ", BV[j], A[j][M-1]);
	}
	printf("X%d = %lf )\n", BV[N-1], A[N-1][M-1]);
	mint=(double)999999999.99;
	int u=-1;
	for(int i=0;i<N;i++){
		if(A[i][v]>0){
			double dum=(double)A[i][M-1]/(double)A[i][v];
			//printf("in for u %d %d -- %lf\n", i, v, dum);
			if(mint > dum){
				mint=dum;
				u=i;
			}
		}
	}
	/*
	printf("In iteration %d Basic Variables are :- ", k+1);
	for(int i=0;i<BV.size();i++)
		cout<<BV[i]<<' ';
	printf("  and min ratio is :- %lf\n", mint);
	*/
	int t=BV[u];
	BV[u]=NBV[v];
	NBV[v]=t;
	// Simplex method
	/*
	printf("Current Simplex Mat :-\n");
	printIST(A, Z, NBV, BV);
	printf("Pivot Point is -- intdex %d %d,  with value %lf\n", u, v, A[u][v]);
	*/
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(i!=u && j!=v){
				A[i][j]=A[i][j]-((double)A[i][v]*(double)A[u][j])/(double)A[u][v];
			}
		}
	}
	for(int i=0;i<M;i++){
		if(i!=v) Z[i]=Z[i]-((double)Z[v]*(double)A[u][i])/(double)A[u][v];
	}

	double sun=A[u][v];
	Z[v]/=(-1)*sun;
	for(int i=0;i<N;i++)
		if(i!=u) A[i][v]/=(-1)*sun;
	for(int i=0;i<M;i++)
		A[u][i]/=sun;
	A[u][v]/=sun;

	//printf("The Simplex Tableau is \n");
	//printIST(A, Z, NBV, BV);
	return simpleIteration(A, Z, NBV, BV, k+1);
}
void BSBFS(vector< vector<double> > A, vector<double> Z, vector<int> NBV, vector<int> BV){
	simpleIteration(A, Z, NBV, BV, 0);
}
void printItr(vector< vector<double> > A, vector<double> Z, vector<int> NBV, vector<int> BV, int k){
	if(k<=0){
		printIST(A, Z, NBV, BV);
		return;
	}
	int N=A.size();
	int M=A[0].size();
	double mint=0.00;
	int v=-1;
	for(int i=0;i<M;i++){
		if((double)Z[i]<mint){
			mint=Z[i];
			v=i;
		}
	}
	if(v<0){
		printf("This iteration No. doesn't exist\n");
		return;
	}
	mint=(double)999999999.99;
	int u=-1;
	for(int i=0;i<N;i++){
		if(A[i][v]>0){
			double dum=(double)A[i][M-1]/(double)A[i][v];
			if(mint > dum){
				mint=dum;
				u=i;
			}
		}
	}
	int t=BV[u];
	BV[u]=NBV[v];
	NBV[v]=t;
	// Simplex method
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(i!=u && j!=v){
				A[i][j]=A[i][j]-((double)A[i][v]*(double)A[u][j])/(double)A[u][v];
			}
		}
	}
	for(int i=0;i<M;i++){
		if(i!=v) Z[i]=Z[i]-((double)Z[v]*(double)A[u][i])/(double)A[u][v];
	}

	double sun=A[u][v];
	Z[v]/=(-1)*sun;
	for(int i=0;i<N;i++)
		if(i!=u) A[i][v]/=(-1)*sun;
	for(int i=0;i<M;i++)
		A[u][i]/=sun;
	A[u][v]/=sun;

	printItr(A, Z, NBV, BV, k-1);
}
int iteration(vector< vector<double> > A, vector<double> Z, vector<int> NBV, vector<int> BV, int k){
	int N=A.size();
	int M=A[0].size();
	double mint=0.00;
	int v=-1;
	for(int i=0;i<M;i++){
		if((double)Z[i]<mint){
			mint=Z[i];
			v=i;
		}
	}
	//cout<<N<<' '<<M<<' '<<mint<<' '<<v<<'\n';
	if(v<0) return k;
	mint=(double)999999999.99;
	int u=-1;
	for(int i=0;i<N;i++){
		if(A[i][v]>0){
			double dum=(double)A[i][M-1]/(double)A[i][v];
			//printf("in for u %d %d -- %lf\n", i, v, dum);
			if(mint > dum){
				mint=dum;
				u=i;
			}
		}
	}
	/*
	printf("In iteration %d Basic Variables are :- ", k+1);
	for(int i=0;i<BV.size();i++)
		cout<<BV[i]<<' ';
	printf("  and min ratio is :- %lf\n", mint);
	*/
	int t=BV[u];
	BV[u]=NBV[v];
	NBV[v]=t;
	// Simplex method
	/*
	printf("Current Simplex Mat :-\n");
	printIST(A, Z, NBV, BV);
	printf("Pivot Point is -- intdex %d %d,  with value %lf\n", u, v, A[u][v]);
	*/
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(i!=u && j!=v){
				A[i][j]=A[i][j]-((double)A[i][v]*(double)A[u][j])/(double)A[u][v];
			}
		}
	}
	for(int i=0;i<M;i++){
		if(i!=v) Z[i]=Z[i]-((double)Z[v]*(double)A[u][i])/(double)A[u][v];
	}

	double sun=A[u][v];
	Z[v]/=(-1)*sun;
	for(int i=0;i<N;i++)
		if(i!=u) A[i][v]/=(-1)*sun;
	for(int i=0;i<M;i++)
		A[u][i]/=sun;
	A[u][v]/=sun;

	//printf("The Simplex Tableau is \n");
	//printIST(A, Z, NBV, BV);
	return iteration(A, Z, NBV, BV, k+1);
}
int NofItr(vector< vector<double> > A, vector<double> Z, vector<int> NBV, vector<int> BV){
	int N=A.size();
	int M=A[0].size();
	//printf("No. of Iterations are :- ");
	int x=iteration(A, Z, NBV, BV, 0);
	return x;
}
void ithSimplex(vector< vector<double> > A, vector<double> Z, vector<int> NBV, vector<int> BV){
	int N=A.size();
	int M=A[0].size();
	printf("Please, enter the iteration no. :- ");
	int k; cin>>k;
	printItr(A, Z, NBV, BV, k);
}
void allNBV(vector<int> NBV){
	printf("All Non-Basic variables in the initial table are :- ");
	for(int i=0;i<NBV.size();i++){
		printf("X%d ", NBV[i]);
	}
	printf("\n");
}
void allBVm(vector< vector<double> > A, vector<double> Z, vector<int> NBV, vector<int> BV){
	int N=A.size();
	int M=A[0].size();
	double mint=0.00;
	int v=-1;
	for(int i=0;i<M;i++){
		if((double)Z[i]<mint){
			mint=Z[i];
			v=i;
		}
	}
	mint=(double)999999999.99;
	int u=-1;
	for(int i=0;i<N;i++){
		if(A[i][v]>0){
			double dum=(double)A[i][M-1]/(double)A[i][v];
			//printf("in for u %d %d -- %lf\n", i, v, dum);
			if(mint > dum){
				mint=dum;
				u=i;
			}
		}
	}
	printf("In iteration 1 Basic Variables are :- ");
	for(int i=0;i<BV.size();i++)
		printf("X%d ", BV[i]);
	printf("  and min ratio is :- %lf\n", mint);
}
int main(){

	printf("Please enter no. of distinct variables and no. of equations in the System of Eqns :- ");
	int N, M; cin>>M>>N;
	printf("Please Enter the Augumented Matrix :- \n");
	M+=1; // Since in Augumented matrix No. of columns would be 1 more than no. of distincts variable
	vector< vector<double> > A; // This is to represent Augumented Matrix
	double x;
	for(int i=0;i<N;i++){
		vector<double> a;
		A.push_back(a);
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>x;
			A[i].push_back(x);
		}
	}
	// The Optimization function is like =>
	// Z = a1.x1 + a2.x2 + ... + an.xn + d
	printf("Please enter the coeff. of optimization fn with d at last :- ");
	vector<double> Z;
	for(int i=0;i<M;i++){
		cin>>x;
		if(i<M-1) x*=(-1);
		Z.push_back(x);
	}

	// NBV represent the collection of Non-Basic Variable
	// and BV represent the collection of Basic Variable.
	// Initially x1, x2, ... , xm would represent Non-Basic Variable
	// and remaining N would represent basic variable.
	vector<int> NBV, BV;
	for(int i=1;i<M;i++)
		NBV.push_back(i);
	for(int i=1;i<=N;i++)
		BV.push_back(M-1+i);

	printf("Please Enter for :- \n");
	printf("1). List of all BS and BFSs.\n");
	printf("2). Print the initial simplex table.\n");
	printf("3). List of all Non-basic variables in the initial table\n");
	printf("4). List of Basic variables along with min ratios in the first iteration\n");
	printf("5). number of iterations.\n");
	printf("6). simplex table of the ith iteration.\n");
	printf("0). for Exit from the Process.\n");
	do{
		printf("\n---------------------------------------------------------\n");
		printf("Please enter choice according to Process to execute :- ");
		int sun; cin>>sun;
		if(sun==0) break;
		else if(sun==1) BSBFS(A, Z, NBV, BV);
		else if(sun==2) printIST(A, Z, NBV, BV);
		else if(sun==3) allNBV(NBV);
		else if(sun==4) allBVm(A, Z, NBV, BV);
		else if(sun==5) printf("No. of Iterations are :-  %d\n", NofItr(A, Z, NBV, BV));
		else if(sun==6) ithSimplex(A, Z, NBV, BV);
		else printf("Sorry!, Please Select choice accordingly.\n");
	}while(true);
	printf("Thank you !\n");
	return 0;
}
