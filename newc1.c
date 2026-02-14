#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int deter(int a[3][3]);
int minor (int a[3][3],int element);
int vec (int a[3][3],double root1,double root2, double root3);

void print(int x[3][3]);
void chara (int a[3][3],int* s1,int* s2,int* s3);
void cubic (int a[3][3] , int *s1,int *s2,int *s3);

void input(int x[3][3]){
    printf("\nEnter matrix : \n");
    for(int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            printf ("Enter element [%d][%d] : ",i,j);
            scanf ("%d",&x[i][j]);
        }
    }
}

int main(){
    int a[3][3];
    int s1=0,s2=0,s3=0;
    
    input (a);
    print (a);
    chara (a, &s1, &s2, &s3);

    return 0;
}

void chara (int a[3][3], int *s1,int *s2,int *s3){
    *s1 = a[0][0] + a[1][1] + a[2][2];
    
    *s2 = ((a[1][1]*a[2][2]) - (a[2][1]*a[1][2]))
        + ((a[0][0]*a[2][2]) - (a[2][0]*a[0][2]))
        + ((a[0][0]*a[1][1]) - (a[1][0]*a[0][1]));

    *s3 = deter(a);

    printf ("\nThe characteristic equation : \n\n");
    printf ("A^3 - (%d)A^2 + (%d)A - (%d)",*s1,*s2,*s3);
    printf("\n\n");

    cubic (a,&*s1,&*s2,&*s3);
}

void print (int x[3][3]){

    printf("\n");
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            printf("\t%d",x[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int deter (int a[3][3]){
    int det = (a[0][0]*minor(a,1))
    - (a[0][1]*minor(a,2))
    + (a[0][2]*minor(a,3));
    
    return det;
}

int minor (int a[3][3],int x){
    int min;
    
    if (x==1) {
        min = ((a[1][1]*a[2][2]) - (a[2][1]*a[1][2]));
    }

    else if (x == 2){
        min = ((a[1][0]*a[2][2]) - (a[2][0]*a[1][2]));
    }

    else if (x == 3){
        min = ((a[1][0]*a[2][1]) - (a[2][0]*a[1][1]));
    }

    return (min);
}

void cubic (int a[3][3],int *s1,int *s2,int *s3){
    int j=1;
    double i;
    int root_count = 0;

    double roots[3] = {0,0,0};
    double first = 1;
    double prev = 0;

    int v1 = pow(j,3) , v2 = (pow(j,2)*(*s1)); 
    int v3 = (*s2)*pow(j,1);

    printf("First term= %d\nSecond term = %d\nThird term = %d\nFourth term = %d\n",v1,v2,v3,*s3);
    int sum = v1-v2+v3-*s3;
    
    for (i = -40.0; i <= 40.0; i += 0.01) {
        double v1 = pow(i, 3);
        double v2 = (pow(i, 2) * (*s1)); 
        double v3 = (*s2) * i;

        double sum = v1 - v2 + v3 - (*s3);

        if (!first && (prev * sum <= 0)) {

            roots[root_count] = i;

            printf("Root found!! The Root is : %.2f\n", i);
            root_count++;
        }

        prev = sum;
        first = 0;

       if (root_count == 3) {break;} 
        
    }

    vec (a,roots[0],roots[1],roots[2]);
}

int vec (int a[3][3],double r1,double r2,double r3){

    double roots[3] = {r1, r2, r3};

    for (int k = 0; k < 3; k++) {
        double r = roots[k];
        double m[3][3];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = (i == j) ? (a[i][j] - r) : a[i][j];
            }
        }

        double v[3];
        v[0] = m[0][1] * m[1][2] - m[1][1] * m[0][2];
        v[1] = m[0][2] * m[1][0] - m[1][2] * m[0][0];
        v[2] = m[0][0] * m[1][1] - m[1][0] * m[0][1];

        if (v[0] == 0 && v[1] == 0 && v[2] == 0) {
            v[0] = m[1][1] * m[2][2] - m[2][1] * m[1][2];
            v[1] = m[1][2] * m[2][0] - m[2][2] * m[1][0];
            v[2] = m[1][0] * m[2][1] - m[2][0] * m[1][1];
        }

        double norm = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
        if (norm != 0) {
            v[0] /= norm;
            v[1] /= norm;
            v[2] /= norm;
        }

        printf("\nEigenvector for root %.2f:\n", r);
        printf("\t[ %.2f\t,%.2f\t,%.2f ]\n", v[0], v[1], v[2]);
    }

    // made by ~ Sanskar,Atharva,Sarang,Srusti,shri,Namrata
} 