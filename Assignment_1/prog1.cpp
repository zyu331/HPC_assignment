#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include<string.h>
#include<unistd.h>


void srand48(long);
double drand48(void);	



int CalLocalSum(int count, int rank, int seed) {
	srand48(seed+rank);
	double sum=0;
	for(int i=1;i <= count;i++){
		sum=sum+drand48();
	
	}
	return sum;
}


int main(int argc, char *argv[]){

	/* initial */
	MPI_Init(&argc, &argv);
        int rank, size;
        MPI_Comm comm = MPI_COMM_WORLD;
        MPI_Comm_size(comm, &size);
        MPI_Comm_rank(comm, &rank);
	int seed;
	int N;
	if(rank==0) {
		N=atoi(argv[1]);
        	seed=atoi(argv[2]);
	}
	MPI_Bcast(&seed, 1, MPI_INT, 0, comm);
	MPI_Bcast(&N, 1, MPI_INT, 0, comm);
	double t0=MPI_Wtime();
	
	/* localSum */
	double localSum;
	localSum=CalLocalSum(int(N/size),rank,seed);
	double totalSum = localSum;
	totalSum=localSum;
	printf("N=%d,seed=%d,size=%d,",N,seed,size);
	printf("rank:%d localsum:%lf totalSum:%lf \n",rank, localSum, totalSum);
	MPI_Barrier(comm);
	
	/*globalSum */
	int d,j;
	d=ceil(log2(size));
	
	for (j = 0; j <= d-1; j++) {
		int rank_compl = (rank ^ int(pow(2,j)));
		if ((rank&1<<j) != 0) {
			MPI_Send(&totalSum, 1, MPI_DOUBLE, rank_compl, 111, comm);
			MPI_Finalize();
			exit(0);
			}
		else {
			MPI_Status stat;
                        MPI_Request req;
			double temp;
			MPI_Irecv(&temp, 1, MPI_DOUBLE, rank_compl, 111, comm, &req);
			MPI_Wait(&req, &stat);
			totalSum = totalSum + temp;
			}
	}
		
	if (rank == 0){
		printf("N = %d, P = %d, C = %d, S = %lf\n",N,size,seed,totalSum);
		double t1=MPI_Wtime();
		printf("Time = %lf\n",t1-t0);
	}
 	 

	return MPI_Finalize();

}
