#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int CalLocalSum(){
	srand48(argv[2]+rank);
	count=argv[1]/size;
	int sum=0;
	int randNum;
	for( int i=1; i<=count;i++){
		randNum_=drand();
		sum=sum+randNum_;
	}
	return sum;
}


int main(int argc, char *argv[]){

/* initial */

	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;	
	int rank, size;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

/* broadcast */
	MPI_Bcast(&argv, 2, MPI_INT, 0, comm);

/* localSum */
	int localSum;
	localSum=CalLocalSum(argv[1]/size);

/*globalSum */
	int d;
	d=ceil(log2(size));
	int totalSum = 0;
	double t0=MPI_Wtime();

	for j = 0 to d-1 {
		if ((rank AND 2^j)!= 0) {
			MPI_Send(&localSum, 1, MPI_INT, (rank XOR 2^j), 111, MPI_COMM_WORLD);
			exit;
		}
		else {
			MPI_Recv(&localSum, 1, MPI_INT,(rank XOR 2^j), 111, MPI_COMM_WORLD, &stat);
			totalSum = totalSum + localSum;
			}
		}

	if (rank == 0)
		print totalSum;

	double t1=MPI_Wtime();
	double runTime=t1-t0;
	print totalSum;

	MPI_Finalize();
	return 0;

}
