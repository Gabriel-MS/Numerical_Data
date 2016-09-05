#include <iostream>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include <fstream>

#define EIGEN_NO_DEBUG
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include <unsupported/Eigen/KroneckerProduct>

using namespace std;
using namespace Eigen;

int main()
{
    //=================================================================
    int n, i, j, row;

    double data[510][3]; //Matrix to hold all raw data
    double rho[500], P[500], u[500];
    VectorXd rho_vec(500), P_vec(500), u_vec(500), one(500);
    MatrixXd P_matrix(500,500), u_matrix(500,500);
    MatrixXd P_diff(500,500), u_diff(500,500), diff(500,500);

cout << "ok" << endl;
    ifstream file("data.csv");

    for(int row = 0; row < 502; ++row)
    {
        string line;
        getline(file, line);
        if ( !file.good() )
            break;
        stringstream iss(line);

        for (int col = 0; col < 3; ++col)
        {
            string val;
            getline(iss, val, ';');
            if ( !iss )
                break;
            stringstream convertor(val);
            convertor >> data[row][col];
        }
    }
cout << "ok" << endl;
    //========================================================================

//Transferring values from 'prop' matrix to vectors
for(n=0; n<500; n++)
{
    row = n+1;
    rho[n] = data[row][0];
    u[n] = data[row][1];
    P[n] = data[row][2];
}

//Reading C++ vectors into Eigen type vectors
for(n=0; n<500; n++)
{
    rho_vec[n] = rho[n];
    u_vec[n] = u[n];
    P_vec[n] = P[n];
}

for(n=0; n<500; n++)
{
    one[n] = 1;
}
cout << "ok" << endl;
    //=========================================================================
    P_matrix = one*P_vec.transpose();
    u_matrix = one*u_vec.transpose();

    //Creating Matrix with minus operations
    u_diff = (u_matrix - u_matrix.transpose()).array().abs();
    P_diff = (P_matrix - P_matrix.transpose()).array().abs();

    for(i=0; i<500; i++)
    {
        for(j=0; j<500; j++)
        {
            if(u_diff(i,j) <= 1e-10) u_diff(i,j)=1;
            if(P_diff(i,j) <= 1e-10) P_diff(i,j)=1;
        }
    }

    int x;
    x = 42; // X IS THE ANSWER

for(i=0; i<491; i++)
    {

            u_diff.block<10,10>(i,i) << x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x;


            P_diff.block<10,10>(i,i) << x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x,
                                        x,x,x,x,x,x,x,x,x,x;

/*
            P_diff(i,i) = x;
            u_diff(i,i) = x;

            int k;

            for(j=0; j<21; j++)
            {
                k = i+j;
                P_diff(i,k) = x;
                P_diff(k,i) = x;
                u_diff(k,i) = x;
                u_diff(i,k) = x;
            }
*/



    }


    diff = u_diff + P_diff;

MatrixXd::Index minU1, minU2, minP1, minP2, min1, min2;
    double min_u = u_diff.minCoeff(&minU1, &minU2);
    double min_P = P_diff.minCoeff(&minP1, &minP2);
    double min0 = diff.minCoeff(&min1, &min2);


    cout << "minimum u = " << min_u << "| at = " << minU1 << "," << minU2 << endl;
    cout << "minimum P = " << min_P << "| at = " << minP1 << "," << minP2 << endl;
    cout << "minimum = " << min0 << "| at = " << min1 << "," << min2 << endl;
    cout << u_vec[minU1] << endl;
    cout << u_vec[minU2] << endl;
    cout << P_vec[minP1] << endl;
    cout << P_vec[minP2] << endl;

    cout << rho_vec[minU1] << endl;
    cout << rho_vec[minU2] << endl;
    cout << rho_vec[minP1] << endl;
    cout << rho_vec[minP2] << endl << endl;

    cout << rho_vec[min1] << endl;
    cout << rho_vec[min2] << endl;

    return 0;
}
