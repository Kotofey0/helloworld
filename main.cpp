//
//  main.cpp
//  NORKA-13MC
//

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <strings.h>
#include <math.h>

typedef struct {
    int ** Matr; //сама матрица
    int m,n; //ее размер
} Matrix;

Matrix *A = new Matrix[5];
char prog[20][5][40];

bool exitcode;
char * dirstr;
char * arg1, * arg2, * arg3;


void Reset_m(int i){
    A[i].Matr=NULL;
    A[i].m=0;
    A[i].n=0;
}

void Arr(){
    printf("--> ");
}

void ArrP(){
    printf("->");
}

void NewMatr(int M){
    int i;
    A[M].Matr = new int*[A[M].m];
    for(i=0;i<A[M].m;i++) A[M].Matr[i]=new int[A[M].n];
}

int DirCode(char inp[4]);

void TransLocal(int M){
    
    Matrix buf;
    int b;
    
    buf = A[M];
    
    b = A[M].m;
    A[M].m = A[M].n;
    A[M].n = b;
    
    NewMatr(M);
    
    for(int i=0;i<A[M].m;i++)
        for(int j = 0;j<A[M].n;j++)
            A[M].Matr[i][j]=buf.Matr[j][i];
    
    
    
}

bool SizeMatch(int M1, int M2){
    return ((A[M1].m==A[M2].m)&&(A[M1].n==A[M2].n));
}

bool SizeMLP(int M1, int M2){
    return (A[M1].n==A[M2].m);
}

bool CorrectName(int M){
    return (M < 5);
}

bool InizMatr(int M){
    return ((A[M].m!=0)&&(A[M].n!=0)&&(A[M].Matr!=NULL)&&CorrectName(M));
}


bool SqareMatr(int M){
    return (A[M].m==A[M].n);
}

bool BigEqs(int M){
    bool outs = false;
    for(int i = 0; i < A[M].m; i++)
        for(int j = 0; j < A[M].n; j++)
            outs += (A[M].Matr[i][j] > 99)||(A[M].Matr[i][j] < -9);
    return outs;
}

void PHelp(){
    printf("A, B, C, D, E                       - записать матрицу в память\n");
    printf("M (matrix) [i,j]                    - изменить ij элемент матрицы\n");
    printf("EM (matrix) [m,n]                   - записать еденичную матрицу размером MxN\n");
    printf("O (matrix) [m,n]                    - записать нулевую матрицу размером MxN\n");
    printf("DET (matrix)                        - вычислить определитель матрицы\n");
    printf("RANK (matrix)                       - вычислить ранг матрицы\n");
    printf("TRS (matrix1) [matrix2]             - транспонировать матрицу 1 (и записать в матрицу 2)\n");
    printf("RE (matrix1) [matrix2]              - записать транспонированную матрицу из алгебраических дополнений матрицы 1 (в матрицу 2)\n");
    printf("MLP (matrix1,const) [matrix2]       - умножить матрицу 1 на число (и записать в матрицу 2)\n");
    printf("ADD (matrix1,matrix2) [matrix3]     - сложить матрицы 1 и 2 (и записать в матрицу 3)\n");
    printf("MMLP (matrix1,matrix2) [matrix3]    - умножить матрицу 1 на матрицу 2 и записать результат в матрицу 3\n");
    printf("SUB (matrix1,matrix2) [matrix3]     - вычесть из матрицы 1 матрицу 2 (и записать в матрицу 3)\n");
    printf("EXIT or QUIT                        - выйти\n");
    printf("HELP [command]                      - эта страница\n");
    printf("MEM [matrix]                        - показать все матрицы или программу (или только одну матрицу)\n");
    printf("RSA                                 - очистить всю память\n");
    printf("PROG (program)                      - записать в память алгоритм из стандартных функций\n");
    printf("P1, P2, P3, P4, P5                  - пользовательские алгоритмы\n");
    printf("DISK (matrix, name of file(.mtr))   - сохранить матрицу в файл [.mtr]\n");
    printf("RFD (matrix, name of file(.mtr))    - загрузить матрицу из файла [.mtr]\n");
    printf("S (matrix)                          - привести матрицу к ступенчатаму виду\n");
    printf("VECT ROW (matrix)                   - записать вектор строку\n");
    printf("VECT COL (matrix)                   - записать вектор столбец\n");
    printf("DIAG (matrix)                       - записать диагональную матрицу\n");
    int a = 4;
    a++;
    
    
}



void ErrDir(char dirs[4]){
    printf("Неизвестная команда - \"%s\"\nНапишите \"HELP\" \n",dirs);
}

void ErrC(int ErrCode){
    switch (ErrCode) {
        case 1:printf("Argument expected\n");break;
        case 2:printf("Matrix doesn't exist\n");break;
        case 3:printf("Size mismatch\n");break;
        case 4:printf("File not found: \"%s\"\n",arg2);break;
        case 5:printf("Matrix has no rewar matrix\n");
            
            
        default:
            break;
    }
};

int DirCode(char inp[4]){
    if(!(strcmp(inp, "A")))     return 1;
    if(!(strcmp(inp, "B")))     return 2;
    if(!(strcmp(inp, "C")))     return 3;
    if(!(strcmp(inp, "D")))     return 4;
    if(!(strcmp(inp, "E")))     return 5;
    if(!(strcmp(inp, "M")))     return 6;
    if(!(strcmp(inp, "EM")))    return 7;
    if(!(strcmp(inp, "O")))     return 8;
    if(!(strcmp(inp, "DET")))   return 9;
    if(!(strcmp(inp, "RANK")))  return 10;
    if(!(strcmp(inp, "TRS")))   return 11;
    if(!(strcmp(inp, "RE")))    return 12;
    if(!(strcmp(inp, "MLP")))   return 13;
    if(!(strcmp(inp, "ADD")))   return 14;
    if(!(strcmp(inp, "MMLP")))  return 15;
    if(!(strcmp(inp, "SUB")))   return 16;
    if(!(strcmp(inp, "EXIT")))  return 17;
    if(!(strcmp(inp, "HELP")))  return 18;
    if(!(strcmp(inp, "MEM")))   return 19;
    if(!(strcmp(inp, "RSA")))   return 20;
    if(!(strcmp(inp, "P1")))    return 21;
    if(!(strcmp(inp, "P2")))    return 22;
    if(!(strcmp(inp, "P3")))    return 23;
    if(!(strcmp(inp, "P4")))    return 24;
    if(!(strcmp(inp, "P5")))    return 25;
    if(!(strcmp(inp, "PROG")))  return 26;
    if(!(strcmp(inp, "DISK")))  return 27;
    if(!(strcmp(inp, "RFD")))   return 28;
    if(!(strcmp(inp, "S")))     return 29;
    if(!(strcmp(inp, "VECT")))  return 30;
    if(!(strcmp(inp, "ROW")))   return 31;
    if(!(strcmp(inp, "COL")))   return 32;
    if(!(strcmp(inp, "DIAG")))  return 33;
    
    return 0;
    
    
}

int ** Minor(int i0, int j0, int n, int ** matr){
    
    int ** minor;
    int ci,cj,i,j;
    ci = -1;
    
    minor = new int* [n-1];
    for(i=0;i<n;i++) minor[i] = new int[n-1];
    for(i = 0; i < n; i++){
        if(i!=i0) {
            ci++;
            cj = -1;
            for(j = 0; j < n; j++){
                if(j!=j0){
                    cj++;
                    minor[ci][cj] = matr[i][j];
                }
            }
        }
    }
    
    return minor;
}

void loop(int n){
    
}
int det(int n,int **matr);

int Aij(int i0, int j0, int n, int ** matr){
    return pow(-1,((i0+1)+(j0+1)))*det(n-1, Minor(i0, j0, n, matr));
}

int det(int n, int ** matr){
    if (n == 1){
        return matr[0][0];
    }
    if (n == 2){
        return (matr[0][0]*matr[1][1]-matr[0][1]*matr[1][0]);
    }
    int ii,jj,ci;
    int **minor;
    int determinant=0;
    for(int i = 0;i < n; i++){//разложение по первой строке
        
        minor = new int* [n-1];
        for(int x = 0; x < (n-1); x++) minor[x] = new int [n-1];
        
        ci=-1;
        for(ii = 0; ii < n; ii++){
            if(ii != i) ci++;
            for(jj = 1; jj < n; jj++){
                
                if(ii != i) {
                    
                    minor[ci][jj-1] = matr[ii][jj];
                    
                }
            }
        }
        determinant += pow(-1,(i))*matr[i][0]*det(n-1,minor);
        
    }
    return determinant;
}

void Modify(int x){
    int buf[10][10],i,j,m,n; char str[30], * word, *ptrptr;
    int M = x - 1;
    j=0;
    gets(str);
    i=0;
    word = strtok_r(str, " " ,&ptrptr);
    sscanf(word, "%d" ,&(buf[i][j]));
    while((word!=NULL)&&(word[0]!='.')){
        
        word = strtok_r(NULL, " ",&ptrptr);
        i++;
        if((word!=NULL)&&(word[0]!='.')){
            
            sscanf(word, "%d" ,(buf[i]+j));
        }
    }
    m=i;
    if((word!=NULL)&&(word[0]=='.')) n = 1; else{
        j++;
        do {
            gets(str);
            i=0;
            word = strtok_r(str, " " ,&ptrptr);
            sscanf(word, "%d" ,&(buf[i][j]));
            while(word!=NULL){
                i++;
                word = strtok_r(NULL, " ",&ptrptr);
                if((word!=NULL)&&(word[1]!='.'))
                    sscanf(word, "%d" ,(buf[i]+j));
                
            }
            j++;
        } while (i==m);
        n=j;
    };;;
    A[M].m=m;
    A[M].n=n;
    A[M].Matr=new int* [m];
    for(i=0;i<m;i++) A[M].Matr[i] = new int[n];
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            A[M].Matr[i][j]=buf[i][j];
    TransLocal(M);
    
    
    
    
    
}

void Mdf_ij(){
    int i,j,x;
    if((arg1==NULL)||(arg2==NULL)||(arg3==NULL)){
        ErrC(1);
        return;
    }
    x=DirCode(arg1)-1;
    if (!(InizMatr(x))){
        ErrC(2);
        return;
    }
    sscanf(arg2, "%d",&i);
    sscanf(arg3, "%d",&j);
    scanf("%d",&(A[x].Matr[j-1][i-1]));
    
    
}

void EMatr(){
    
    int m,n,i,j,M;
    if(arg1==NULL){
        ErrC(1);
        return;
    }
    if(arg2==NULL) m = 1;
    else sscanf(arg2,"%d",&m);
    if(arg3==NULL) n = 1;
    else sscanf(arg3,"%d",&n);
    
    M=DirCode(arg1)-1;
    A[M].m=m;
    A[M].n=n;
    NewMatr(M);
    
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            if(i==j)A[M].Matr[i][j]=1;else A[M].Matr[i][j] = 0;
    
    
    
    
}

void Help(){
    if(arg1!=NULL){
        PHelp();
        return;
    }
    int ind = DirCode(arg1)-1;
    
    switch (ind) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            printf("A, B, C, D, E.\n-=USING=-");
            printf("Use for manual input matrix to memory.\n");
            printf("You can input matrix with size from 1x1 to 10x10.\n");
            printf("-=SINTAX=-\n");
            printf("You must write matrix's elemets with spaces between them (min - 1 space)\n");
            printf("and with [Enter] between the strings.\n");
            printf("In end of input you must put a point \".\" on tse same string with one or more spaces");
            printf("-=EXAMPLE=-");
            printf("--> A\n3 4 5\n5 4 7\n3 8 0 .\n");
            break;
        case 6: ;break;
        case 7: ;break;
        case 8: ;break;
        case 9: ;break;
        case 10: ;break;
        case 11: ;break;
        case 12: ;break;
        case 13: ;break;
        case 14: ;break;
        case 15: ;break;
        case 0: printf("Unknown command \"%s\"...",arg1) ;break;
            
    }
    
}

void ZeroM(){
    
    
    int m,n,i,j,M;
    if(arg1==NULL){
        ErrC(1);
        return;
    }
    if(arg2==NULL) m = 1;
    else sscanf(arg2,"%d",&m);
    if(arg3==NULL) n = 1;
    else sscanf(arg3,"%d",&n);
    
    if((M=DirCode(arg1)-1)>=5)
        return;
    A[M].m=m;
    A[M].n=n;
    NewMatr(M);
    
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            A[M].Matr[i][j]=0;
    
    
}

void Deter(){
    
    if (arg1==NULL){
        ErrC(1);
        return ;
    }
    int M = DirCode(arg1)-1;
    if (!(InizMatr(M))){
        ErrC(2);
        return ;
    }
    if (!(SqareMatr(M))){
        ErrC(3);
        return ;
    }
    // int razm = A[M].m;
    
    /* long int l,d,sum11=1,sum12=0, sum21=1, sum22=0;
     // находим детерминант
     for (int i=0;i<razm;i++)
     {
     sum11=1; l=2*razm-1-i;sum21=1;
     for (int j=0;j<razm;j++)
     {
     sum21*=A[M].Matr[j][l%razm];
     l--;
     sum11*=A[M].Matr[j][(j+i)%(razm)];
     }
     sum22+=sum21;
     sum12+=sum11;
     }
     d=sum12-sum22;*/
    
    int d = det(A[M].m,A[M].Matr);
    printf("=%d\n",d);
    
}

void Stairs(){
    
    if(arg1==NULL){
        ErrC(1);
        return;
    }
    
    int M = DirCode(arg1)-1;
    
    float ** buf = new float * [A[M].m];
    for(int i = 0; i < A[M].m; i++) buf[i] = new float [A[M].n];
    for(int i = 0; i < A[M].m; i++)
        for(int j = 0; j < A[M].n; j++)
            buf[i][j] = A[M].Matr[i][j];
    
    float cons;
    for(int i = 1; i < A[M].m; i++){
        for(int ii = i; ii < A[M].m; ii++){
            
            if((buf[i-1][i-1]!=0)&&(buf[ii][i-1]!=0)){
                
                cons = buf[ii][i-1]/buf[i-1][i-1];
                for(int j = 0; j < A[M].n; j++){
                    buf[ii][j] -= cons*buf[i-1][j];
                }
                
            }
            else {
                
                for(int j = 0; j < A[M].n; j++){
                    int b = buf[ii][j];
                    buf[ii][j] = buf[i-1][j];
                    buf[i-1][j] = b;
                }
            }
            
        }
        
    }
    
    for(int i = 0; i <A[M].m; i++){
        for(int j = 0; j < A[M].n; j++) printf("%7.4f  ",buf[i][j]);
        printf("\n\n");
    }
    
}

void Ranks(){
    
    if(arg1==NULL){
        ErrC(1);
        return;
    }
    
    int M = DirCode(arg1)-1;
    
    float ** buf = new float * [A[M].m];
    for(int i = 0; i < A[M].m; i++) buf[i] = new float [A[M].n];
    for(int i = 0; i < A[M].m; i++)
        for(int j = 0; j < A[M].n; j++)
            buf[i][j] = A[M].Matr[i][j];
    
    float cons;
    for(int i = 1; i < A[M].m; i++){
        for(int ii = i; ii < A[M].m; ii++){
            
            if((buf[i-1][i-1]!=0)&&(buf[ii][i-1]!=0)){
                
                cons = buf[ii][i-1]/buf[i-1][i-1];
                for(int j = 0; j < A[M].n; j++){
                    buf[ii][j] -= cons*buf[i-1][j];
                }
                
            }
            else {
                
                for(int j = 0; j < A[M].n; j++){
                    int b = buf[ii][j];
                    buf[ii][j] = buf[i-1][j];
                    buf[i-1][j] = b;
                }
            }
            
        }
        
    }
    
    for(int i = 0; i < A[M].m; i++)
        for(int j = 0; j <A[M].n; j++)
            if(A[M].Matr[i][j]<0.00000001) A[M].Matr[i][j] = 0;
    float sum = 0;int rank;
    if(A[M].m < A[M].n)rank = A[M].m; else rank = A[M].m;
    for(int i = 0; i < A[M].n; i++){
        sum = 0;
        for(int j = 0; j < A[M].m; j++) sum += buf[i][j]*buf[i][j];
        if (sum==0.00001) rank--;
    }
    
    /* for(int i = 0; i < A[M].m; i++){
     for(int j = 0; j < A[M].n; j++)
     printf("%5.2f ",buf[i][j]);
     printf("\n");
     } */
    //
    //
    printf("=%d\n",rank);
}

void Programming(){
    
    if(arg1==NULL){
        ErrC(1);
        return;
    }
    int P=DirCode(arg1)-21;
    int i=0;
    char OP[40];
    
    
    while(strcmp(OP, "END")!=0){
        printf("P%d:%d",P+1,i);
        ArrP();
        gets(OP);
        strcpy(prog[i++][P],OP);
    }
}

bool NORKA();

void UserC(){
    int P = DirCode(dirstr)-21;
    char OP[40], *context;
    int i = 0;
    
    strcpy(OP,prog[i++][P]);
    while(strcmp(OP, "END")!=0){
        dirstr = strtok_r(OP, " ,",&context);
        arg1   = strtok_r(NULL, " ,",&context);
        arg2   = strtok_r(NULL, " ,",&context);
        arg3   = strtok_r(NULL, " ,",&context);
        
        if(!NORKA())
            printf("-----------\n");
        strcpy(OP,prog[i++][P]);
    }
    printf("END\n");
}

void Trans(){
    
    int M;
    if(arg1==NULL){
        ErrC(1);
        return ;
    }
    M = DirCode(arg1)-1;
    TransLocal(M);
}

void Rewar(){
    
    if(arg1 == NULL){
        ErrC(1);
        return;
    }
    if(!SqareMatr(DirCode(arg1)-1)){
        ErrC(3);
        return;
    }
    if(!InizMatr(DirCode(arg1)-1)){
        ErrC(2);
        return;
    }
    if(det(A[DirCode(arg1)-1].m,A[DirCode(arg1)-1].Matr)==0){
        ErrC(5);
        return;
    }
    Matrix buffer; int M = DirCode(arg1)-1;
    int n = buffer.m = buffer.n = A[M].m;
    buffer.Matr = new int * [n];
    
    for(int i = 0; i < n; i++) buffer.Matr[i] = new int [n];
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            buffer.Matr[i][j] = Aij(i, j, n, A[M].Matr);
    
    if(arg2 != NULL){
        A[DirCode(arg2)-1] = buffer;
        TransLocal(DirCode(arg2)-1);
    }
    else{
        A[M] = buffer;
        TransLocal(M);
    }
    
    
}

void Mltpl(int code){
    int  i,i1,j,j1;
    
    if(code == 2){
        if((arg1==NULL)||(arg1==NULL)||(arg3==NULL)){ErrC(1);return;}
        
        int M1=(DirCode(arg1))-1,M2=(DirCode(arg2))-1,M3=(DirCode(arg3))-1;
        if(!SizeMLP(M1, M2)){
            ErrC(3);
            return;
        }
        if (!(InizMatr(M1))){
            ErrC(2);
            return ;
        }
        if (!(InizMatr(M2))){   // m - rows
            ErrC(2);            // n - cols
            return ;
        }
        
        A[M3].m=A[M1].m;
        A[M3].n=A[M2].n;
        NewMatr(M3);
        
        for(i=0;i<A[M3].m;i++)
            
            for(j=0;j<A[M3].n;j++){
                
                j1=0;
                
                for(i1=0;i1<A[M1].n;i1++){
                    
                    j1+=A[M1].Matr[i][i1]*A[M2].Matr[i1][j];
                    
                }
                
                A[M3].Matr[i][j]=j1;
            }
    }
    else{
        if((arg1==NULL)||(arg2==NULL)){
            ErrC(1);
            return;
        }
        int Cons ;
        sscanf(arg2, "%d",&Cons);
        int M1 = DirCode(arg1)-1;
        if(arg3!=NULL){
            int M2=DirCode(arg3)-1;
            A[M2].m=A[M1].m;
            A[M2].n=A[M1].n;
            NewMatr(M2);
            for(i=0;i<A[M1].m;i++)
                for(j=0;j<A[M1].n;j++)
                    A[M2].Matr[i][j]=Cons*A[M1].Matr[i][j];
            
        }
        else for(i=0;i<A[M1].m;i++)
            for(j=0;j<A[M1].n;j++)
                A[M1].Matr[i][j]=Cons*A[M1].Matr[i][j];
        
        
    }
}

void Vect(){
    if(arg1 == NULL){
        ErrC(1);
        return;
    }
    if(arg2 == NULL){
        ErrC(1);
        return;
    }
    int vector[10];
    char vectstr[50];
    char *buf, *context;
    
    int i;
    
    gets(vectstr);
    buf = strtok_r(vectstr, " ", &context);
    sscanf(buf, "%d", vector);
    for(i = 1;context != NULL;i++){
        buf = strtok_r(NULL, " ", &context);
        sscanf(buf, "%d", vector+i);
    }
    
    int M = DirCode(arg2)-1;
    
    A[M].m = i;
    A[M].n = 1;
    
    NewMatr(M);
    
    for(int ii = 0; ii < i; ii++)
        A[M].Matr[ii][0] = vector[ii];
    
    if(DirCode(arg1)==32)
        return;
    if(DirCode(arg1)==31) {
        
        TransLocal(M);
        return;
    }
    
    
    
    
    
}

void Diag(){
    
    if(arg1 == NULL){
        ErrC(1);
        return;
    }
    
    int vector[10];
    char vectstr[50];
    char *buf, *context;
    
    int i;
    gets(vectstr);
    buf = strtok_r(vectstr, " ", &context);
    sscanf(buf, "%d", vector);
    for(i = 1;context != NULL;i++){
        buf = strtok_r(NULL, " ", &context);
        sscanf(buf, "%d", vector+i);
    }
    
    int M = DirCode(arg1)-1;
    
    A[M].m=A[M].n=i;
    NewMatr(M);
    
    for(int ii = 0; ii < i; ii++)
        for(int jj = 0; jj < i; jj++){
            
            if(ii==jj) A[M].Matr[ii][jj] = vector[ii]; //vector[jj];
            else A[M].Matr[ii][jj] = 0;
            
        }
    
}

void Addit(int code){
    Matrix buf;
    int i,j,M1,M2,M3=-1,k=1;
    
    switch(code){
        case 1:k=1;break;
        case 2:k=-1;break;
    }
    
    if((arg1==NULL)||(arg2==NULL)){
        ErrC(1);
        return;
    }
    M1=DirCode(arg1)-1;
    M2=DirCode(arg2)-1;
    if(!(SizeMatch(M1, M2))){
        ErrC(3);
        return;
    }
    if (!(InizMatr(M1))){
        ErrC(2);
        return ;
    }
    if (!(InizMatr(M2))){
        ErrC(2);
        return ;
    }
    
    
    if(arg3!=NULL) M3=DirCode(arg3)-1;
    buf = A[M1];
    buf.Matr = new int*[A[M1].m];
    for(i=0;i<A[M1].m;i++) buf.Matr[i] = new int [A[M2].n];
    for(i=0;i<A[M1].m;i++)
        for(j=0;j<A[M1].n;j++)
            buf.Matr[i][j]=A[M1].Matr[i][j];
    
    for (i=0; i<A[M1].m; i++)
        for(j=0;j<A[M1].n;j++)
            buf.Matr[i][j]+=k*(A[M2].Matr[i][j]);
    if(M3>-1)A[M3]=buf; else A[M1]=buf;
    
}


void Memor(){
    char names[6]="ABCDE";
    printf("\n");
    if((arg1!=NULL)&&(DirCode(arg1)>=1)&&(DirCode(arg1)<=5)){
        int a = DirCode(arg1) - 1;
        printf("Матрица %c:\n",names[a]);
        if(!(InizMatr(a))) printf("-NO DATA-\n"); else
            if(BigEqs(a)){
                for(int i = 0;i<A[a].m;i++){
                    printf("|");
                    for(int j = 0;j<A[a].n;j++) printf("%5d ",A[a].Matr[i][j]);
                    printf("|\n");
                    if (i < A[a].m-1) {
                        printf("|");
                        for(int j = 0;j<A[a].n;j++) printf("      ");
                        printf("|\n");
                    }
                    
                }
            }
            else{
                for(int i = 0;i<A[a].m;i++){
                    printf("|");
                    for(int j = 0;j<A[a].n;j++) printf("%2d ",A[a].Matr[i][j]);
                    printf("|\n");
                }
            }
    }
    
    else if((arg1!=NULL)&&(DirCode(arg1)>=21)&&(DirCode(arg1)<=25)){
        int P = DirCode(arg1)-21;
        printf("Program P%d\n",P+1);
        int i = 0;
        while(strcmp(prog[i][P],"END")!=0) printf("%s\n",prog[i++][P]);
        printf(".\n");
        
    }
    else for(int a=0;a<5;a++){
        printf("Матрица %c:\n",names[a]);
        if(!(InizMatr(a))) printf("-NO DATA-\n");
        else if(BigEqs(a)){
            for(int i = 0;i<A[a].m;i++){
                printf("|");
                for(int j = 0;j<A[a].n;j++) printf("%5d ",A[a].Matr[i][j]);
                printf("|\n");
                if (i < A[a].m-1) {
                    printf("|");
                    for(int j = 0;j<A[a].n;j++) printf("      ");
                    printf("|\n");
                }
                
            }
        }
        else{
            for(int i = 0;i<A[a].m;i++){
                printf("|");
                for(int j = 0;j<A[a].n;j++) printf("%2d ",A[a].Matr[i][j]);
                printf("|\n");
            }
        }
    }
}


void ResetAll(){
    
    for(int i =0;i<5;i++){
        Reset_m(i);
    }
    
    for(int i = 0; i < 5; i++){
        strcpy(prog[0][i],"END");
        
    }
    
    
    
    
    
}
void CopyM(){
    if((arg1==NULL)||(arg2==NULL)){ ErrC(1); return;}
    int i,j,M1=DirCode(arg1)-1,M2 = DirCode(arg2)-1;
    A[M2]=A[M1];
    NewMatr(DirCode(arg2)-1);
    for(i=0;i<A[M1].m;i++)
        for(j=0;j<A[M1].n;j++)
            A[M2].Matr[i][j]=A[M1].Matr[i][j];
}

void disk(){
    
    if((arg1==NULL)||(arg2==NULL)){
        ErrC(1);
        return;
    }
    
    
    FILE *f; int M = DirCode(arg1)-1;
    
    if(DirCode(arg1)<6){
        f = fopen(arg2, "wb");
        
        
        fwrite(&(A[M].m),sizeof(int),1,f);
        fwrite(&(A[M].n),sizeof(int),1,f);
        
        for(int i = 0; i < A[M].m; i++)
            for (int j = 0; j < A[M].n; j++) {
                fwrite(&(A[M].Matr[i][j]),sizeof(int),1,f);
            }
        
        
        
        fclose(f);
    }
    else if ((DirCode(arg1)>20)&&(DirCode(arg1)<26)){
        f = fopen(arg2,"wt");
        int i = 0;
        int p = DirCode(arg1)-21;
        fprintf(f,"%s\n",prog[i][p]);
        while(strcmp(prog[i++][p],"END")){
            fprintf(f,"%s\n",prog[i][p]);
            
            
        }
        fclose(f);
    }
    
    return;
}


void ReadFromFile(){
    
    if((arg1==NULL)||(arg2==NULL)){ ErrC(1); return;}
    
    FILE * f; int m,n,M = DirCode(arg1)-1;
    
    if(DirCode(arg1)<6){
        Reset_m(DirCode(arg1)-1);
        f = fopen(arg2,"rb");
        if (f == NULL){
            ErrC(4);
            return;
        }
        
        fread(&m,sizeof(int),1,f);
        fread(&n,sizeof(int),1,f);
        
        A[M].m = m;
        A[M].n = n;
        
        NewMatr(M);
        
        for(int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                fread(&(A[M].Matr[i][j]), sizeof(int), 1, f);
            }
        
        
        fclose(f);
    }else if((DirCode(arg1)>20)&&(DirCode(arg1)<26)){
        if((f=fopen(arg2, "rt"))==NULL){
            ErrC(4);
            //fclose(f);
            return;
        }
        int i = 0,p = DirCode(arg1) - 21;
        char bufs[20], *context;
        while(!feof(f)){
            fgets(bufs,20,f);
            sprintf(prog[i++][p],"%s",strtok_r(bufs, ";\n", &context));
            
        }
        fclose(f);
    }
}

bool VarInit(){
    return false;
}


bool NORKA(){
    bool outs = true;
    
    switch (DirCode(dirstr)) {
        case  1:
        case  2:
        case  3:
        case  4:
        case  5:Modify(DirCode(dirstr)); outs = false;break;//OK
        case  6:Mdf_ij();break;//OK
        case  7:EMatr();break;//OK
        case  8:ZeroM();break;//OK
        case  9:Deter();break;//OK
        case 10:Ranks();break;//OK
        case 11:Trans();break;//OK
        case 12:Rewar();break;//OK
        case 13:Mltpl(1);break;//OK
        case 14:Addit(1);break;//OK
        case 15:Mltpl(2);break;//OK
        case 16:Addit(2);break;//OK
        case 17:exitcode = true;break;//OK
        case 18:PHelp();break;//OK
        case 19:Memor();break;//OK
        case 20:ResetAll();break;//OK
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:UserC();break;//OK
        case 26:Programming();break;//OK
        case 27:disk();break;//OK
        case 28:ReadFromFile();break;//OK
        case 29:Stairs();break;//OK
        case 30:Vect();break;//OK
        case 33:Diag();break;//OK
            
        case 0:if ( !VarInit() ) ErrDir(dirstr);//OK
    }
 //   dirstr=arg1=arg2=arg3=NULL;
    return outs;
}

int main(){
    char command[4+1+4+1+4+1+4], * context;
    printf("NORKA-13MC");
    ResetAll();
    while (!exitcode) {
        Arr();
        gets(command);
        if(strcmp(command, "\0")!=0){
            dirstr = strtok_r(command, " ,",&context);
            arg1   = strtok_r(NULL, " ,",&context);
            arg2   = strtok_r(NULL, " ,",&context);
            arg3   = strtok_r(NULL, " ,",&context);
            
            NORKA();
            dirstr=arg1=arg2=arg3=NULL;

        }
    }
    return 0;
}
