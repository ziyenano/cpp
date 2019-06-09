#include <iostream>
#include <stdio.h>
#include "mpi.h"
#include "math.h"

using namespace std;

double fn(double x);
double calc_area(double a, double b, double h, int per_sz);

int main(int argc, char *argv[]) {
    int my_rank, comm_sz;  
    int npart = 1024;
    double a = 0.;
    double b = 5.;
    
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    double h = (b - a) / npart;
    int per_sz = npart / comm_sz;
    double per_a = a + my_rank * per_sz * h; 
    double per_b = per_a + per_sz * h; 
    double per_area = calc_area(per_a, per_b, h, per_sz);

    if (my_rank != 0) {
        //除节点0外, 其他节点将计算好的per_area发送给节点0
        MPI_Send(&per_area, 1, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD);
    } else {
        double ttl_area = per_area;
        //节点0, 将其他节点传过来的area累加起来
        for (int src = 1; src < comm_sz; ++src) {
            MPI_Recv(&per_area, 1, MPI_DOUBLE, src, 99, MPI_COMM_WORLD, &status);
            ttl_area += per_area;
        }
        printf("ttl size[%d], ttl area[%lf]", comm_sz, ttl_area);
    }
    //以上代码所有节点(rank)都会运行

    MPI_Finalize();
    return 0;
}


double fn(double x) {
    return -1 * pow(x-1, 2) + 5;
}

double calc_area(double a, double b, double h, int per_sz) {
    double area = 0.; 
    for (int i = 0; i < per_sz; ++i) {
        area += 0.5 * h * (fn(a + i * h) + fn(a + (i+1) * h));
    }
    return area;
}
