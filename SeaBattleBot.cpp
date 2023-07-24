#include <iostream>
#include <array>
#include <stdlib.h>

using namespace std;

int ship1, ship2, ship3, ship4;
int **BB, **BBB;
int my_score = 0, comp_score = 0;

void OutTable(int **B, int n, int m){
    for(int i=0; i<n; i++){
        for(int k=0; k<m; k++){
            if(B[i][k]==0) cout << '-' << ' ';
            else if(B[i][k]==1) cout << 'x' << ' ';
            else cout << 'o' << ' '; 
        }
        cout << endl;
    }
}

int** CreateTable(int n, int m){
    int **B = new int*[n];
    for(int i=0; i<n; i++){
        B[i] = new int[m];
        for (int k=0; k<m; k++){
            B[i][k]=0;
        }
    }
    return B;
}

int num; int **ik_num;
int** DeleteTable(int i_, int k_){
    num--;
    int **ik_num2 = new int*[num];
    int w = 0;
    for(int u = 0; u < num; u++)
        {
            if (ik_num[w][0]==i_ && ik_num[w][1]==k_) w++;
            ik_num2[u]=ik_num[w];
            w++;
        }
    return ik_num2;
}

int Random(int x){
    if (x>1) return 0 + rand() % (x-1); else return 0;
}

int** OneTable(int n, int m, int **L)
{
    int **M = L;
    for(int ii = 0; ii < n; ii++){
            for(int kk = 0; kk < m; kk++){
                if(M[ii][kk]==0){
                if(ii>0){if(M[ii-1][kk]==2) M[ii][kk]=1;}
                if(ii<n-1){if(M[ii+1][kk]==2) M[ii][kk]=1;} 
                if(kk>0){if(M[ii][kk-1]==2) M[ii][kk]=1;}
                if(kk<m-1){if(M[ii][kk+1]==2) M[ii][kk]=1;}

                if(ii<n-1 && kk<m-1){if(M[ii+1][kk+1]==2) M[ii][kk]=1;}
                if(ii<n-1 && kk>0){if(M[ii+1][kk-1]==2) M[ii][kk]=1;}
                if(ii>0 && kk<m-1){if(M[ii-1][kk+1]==2) M[ii][kk]=1;}
                if(ii>0 && kk>0){if(M[ii-1][kk-1]==2) M[ii][kk]=1;}
                }
            }
        }
    return M;
}

int i_changed, k_changed, dir_changed;
void AskTable(int n, int m, int **B, int **BB, int **BBB)
{
    int i_, k_;
    cout << "Enter the coordinates of the field cell: ";
    cin >> i_ >> k_;
    i_--; k_--;
    while (i_ > n-1 || i_ < 0 || k_ > m-1 || k_ < 0)
    {
        cout << "Error! Enter the coordinates of the field cell again: ";
        cin >> i_ >> k_;
        i_--; k_--;
    }
    if(BB[i_][k_]==2){
        BBB[i_][k_]=2;
            if(i_>0 && BB[i_-1][k_]==2 && BBB[i_-1][k_]!=2) {cout << "Hit!" << endl; goto AskTable_;}
            if(i_<n-1 && BB[i_+1][k_]==2 && BBB[i_+1][k_]!=2) {cout << "Hit!"<< endl; goto AskTable_;}
            if(k_>0 && BB[i_][k_-1]==2 && BBB[i_][k_-1]!=2) {cout << "Hit!"<< endl; goto AskTable_;}
            if(k_<m-1 && BB[i_][k_+1]==2 && BBB[i_][k_+1]!=2) {cout << "Hit!"<< endl; goto AskTable_;}

            if(i_>0 && BB[i_-1][k_]==2)
            {
                int iii = i_;
                while(i_>0 && BB[iii-1][k_]==2){
                    iii--;
                    if(BBB[iii][k_]!=2) {cout << "Hit!"<< endl; goto AskTable_;}
                }
            }
            if(i_<n-1 && BB[i_+1][k_]==2)
            {
                int iii = i_;
                while(i_<n-1 && BB[iii+1][k_]==2){
                    iii++;
                    if(BBB[iii][k_]!=2) {cout << "Hit!"<< endl; goto AskTable_;}
                }
            }
            if(k_>0 && BB[i_][k_-1]==2)
            {
                int kkk = k_;
                while(k_>0 && BB[i_][kkk-1]==2){
                    kkk--;
                    if(BBB[i_][kkk]!=2) {cout << "Hit!"<< endl; goto AskTable_;}
                }
            }
            if(k_<m-1 && BB[i_][k_+1]==2)
            {
                int kkk = k_;
                while(k_<m-1 && BB[i_][kkk+1]==2){
                    kkk++;
                    if(BBB[i_][kkk]!=2) {cout << "Hit!"<< endl; goto AskTable_;}
                }
            }

        cout << "The ship is dead!" << endl;
        OneTable(n, m, BBB);
        my_score++; if(my_score == ship1+ship2+ship3+ship4) { cout << "You have won!" << endl; return; }
        goto AskTable_;
        AskTable_:
            OutTable(BBB, n, m);
            AskTable(n, m, B, BB, BBB);
    }
    else{
        BBB[i_][k_]=1;
        cout << "Missed!" << endl;
        OutTable(BBB, n, m);
        int r = Random(num);
    }
}


int i_first; int k_first;
void CheckTable(int i, int k, int n, int m, int **B, int dir, bool dead)
{
    char answer;
    answer='n';
    if(dead){
        cout << "Is the ship dead? ";
        cin >> answer;
    }
    if(answer=='n'){
    cout << "[" << i+1 << "," << k+1 << "]? ";
            cin >> answer;
            if (answer == 'y'){
                B[i][k]=2;
                ik_num = DeleteTable(i, k);
                OutTable(B, n, m);
                if(dir==0){
                    i_first=i; k_first=k;
                    if(i>0 && B[i-1][k]==0) { i--; dir = 1; }
                    else if(i<n-1 && B[i+1][k]==0) { i++; dir = 2; }
                    else if(k>0 && B[i][k-1]==0) { k--; dir = 3; }
                    else if(k<m-1 && B[i][k+1]==0) { k++; dir = 4; }
                }
                else{
                    if(dir==1) {if(i>0 && i_first<n-1 && B[i-1][k]==0) i--; else {dir=2; i=i_first+1; k=k_first;}}
                    else if(dir==2) {if(i<n-1 && i_first>0 && B[i+1][k]==0) i++; else {dir=1; i=i_first-1; k=k_first;}}
                    else if(dir==3) {if(k>0 && k_first<n-1 && B[i][k-1]==0) k--; else {dir=4; i=i_first; k=k_first+1;}}
                    else if(dir==4) {if(k<m-1 && k_first>0 && B[i][k+1]==0) k++; else {dir=3; i=i_first; k=k_first-1;}}
                }
                CheckTable(i, k, n, m, B, dir, true);
            }
            else
            {
            B[i][k]=1;
            ik_num = DeleteTable(i, k);
            OutTable(B, n, m);
            if(dir==0){
               int r = Random(num);
               i = ik_num[r][0];
               k = ik_num[r][1];
            }
            else
            {
                    if(i_first<n-1 && B[i_first+1][k_first]==0) {dir=2; i=i_first+1; k=k_first;}
                    else if(i_first>0 && B[i_first-1][k_first]==0) {dir=1; i=i_first-1; k=k_first;}
                    else if(k_first<n-1 && B[i_first][k_first+1]==0) {dir=4; i=i_first; k=k_first+1;}
                    else if(k_first>0 && B[i_first][k_first-1]==0) {dir=3; i=i_first; k=k_first-1;}
                    else dir=0;
            }
            i_changed=i; k_changed = k; dir_changed=dir;
            AskTable(n, m, B, BB, BBB);
            }
    }
    else {
        for(int ii = 0; ii < n; ii++){
            for(int kk = 0; kk < m; kk++){
                if(B[ii][kk]==0){
                if(ii>0){if(B[ii-1][kk]==2) B[ii][kk]=1;}
                if(ii<n-1){if(B[ii+1][kk]==2) B[ii][kk]=1;} 
                if(kk>0){if(B[ii][kk-1]==2) B[ii][kk]=1;}
                if(kk<m-1){if(B[ii][kk+1]==2) B[ii][kk]=1;}

                if(ii<n-1 && kk<m-1){if(B[ii+1][kk+1]==2) B[ii][kk]=1;}
                if(ii<n-1 && kk>0){if(B[ii+1][kk-1]==2) B[ii][kk]=1;}
                if(ii>0 && kk<m-1){if(B[ii-1][kk+1]==2) B[ii][kk]=1;}
                if(ii>0 && kk>0){if(B[ii-1][kk-1]==2) B[ii][kk]=1;}

                if(B[ii][kk]==1) ik_num = DeleteTable(ii, kk);
                }
            }
        }
        OutTable(B, n, m);
        comp_score++; if(comp_score == ship1+ship2+ship3+ship4) { cout << "You lose!" << endl; return; }
        int r = Random(num);
        CheckTable(ik_num[r][0], ik_num[r][1], n, m, B, 0, false);
    }
}


int main()
{
    srand(time(0));
    int n, m, i, k; int dir = 0;
    cout << "Enter the field spacing: ";
    cin >> n >> m;
    num = n*m;
    cout << "Enter the number of 1-deck, 2-deck, 3-deck, 4-deck ships: ";
    cin >> ship1 >> ship2 >> ship3 >> ship4;
    
    ik_num = new int*[n*m];
    for(int u = 0; u < n; u++)
        for(int w = 0; w < m; w++)
            ik_num[u*m+w]=new int[2]{u, w};

    int **B = CreateTable(n, m);
    int r = Random(num);
    //CheckTable(ik_num[r][0], ik_num[r][1], n, m, B, 0, false);

    BB = CreateTable(n, m);
    BBB = CreateTable(n, m);
    int ri, rk, rdest;
    int t = 0;
    while(t < ship4){
            ri = Random(n);
            rk = Random(m);
            rdest = Random(4);

            switch(rdest){
               case 0: 
               if(ri<3) ri=3; 
               if(BB[ri][rk]==0 && BB[ri-1][rk]==0 && BB[ri-2][rk]==0 && BB[ri-3][rk]==0) { 
                   BB[ri][rk]=2; BB[ri-1][rk]=2; BB[ri-2][rk]=2; BB[ri-3][rk]=2; OneTable(n, m, BB); t++; break;
               } rdest=1;
               
               case 1: 
               if(ri>((n-1)-3)) ri=(n-1)-3;
               if(BB[ri][rk]==0 && BB[ri+1][rk]==0 && BB[ri+2][rk]==0 && BB[ri+3][rk]==0) { 
                   BB[ri][rk]=2; BB[ri+1][rk]=2; BB[ri+2][rk]=2; BB[ri+3][rk]=2; OneTable(n, m, BB); t++; break;
               } rdest=2;
               
               case 2: 
               if(rk>((m-1)-3)) rk=(m-1)-3;
               if(BB[ri][rk]==0 && BB[ri][rk+1]==0 && BB[ri][rk+2]==0 && BB[ri][rk+3]==0) { 
                   BB[ri][rk]=2; BB[ri][rk+1]=2; BB[ri][rk+2]=2; BB[ri][rk+3]=2; OneTable(n, m, BB); t++; break;
               } rdest=3;
               
               case 3: 
               if(rk<3) rk=3;
               if(BB[ri][rk]==0 && BB[ri][rk-1]==0 && BB[ri][rk-2]==0 && BB[ri][rk-3]==0) { 
                   BB[ri][rk]=2; BB[ri][rk-1]=2; BB[ri][rk-2]=2; BB[ri][rk-3]=2; OneTable(n, m, BB); t++; break;
               } rdest=0;
            }

    }
    t = 0;
    while(t < ship3){
            ri = Random(n);
            rk = Random(m);
            rdest = Random(4);

            switch(rdest){
               case 0: 
               if(ri<2) ri=2; 
               if(BB[ri][rk]==0 && BB[ri-1][rk]==0 && BB[ri-2][rk]==0) { 
                   BB[ri][rk]=2; BB[ri-1][rk]=2; BB[ri-2][rk]=2; OneTable(n, m, BB); t++; break;
               } rdest=1;
               
               case 1: 
               if(ri>((n-1)-2)) ri=(n-1)-2;
               if(BB[ri][rk]==0 && BB[ri+1][rk]==0 && BB[ri+2][rk]==0) { 
                   BB[ri][rk]=2; BB[ri+1][rk]=2; BB[ri+2][rk]=2; OneTable(n, m, BB); t++; break;
               } rdest=2;
               
               case 2: 
               if(rk>((m-1)-2)) rk=(m-1)-2;
               if(BB[ri][rk]==0 && BB[ri][rk+1]==0 && BB[ri][rk+2]==0) { 
                   BB[ri][rk]=2; BB[ri][rk+1]=2; BB[ri][rk+2]=2; OneTable(n, m, BB); t++; break;
               } rdest=3;
               
               case 3: 
               if(rk<2) rk=2;
               if(BB[ri][rk]==0 && BB[ri][rk-1]==0 && BB[ri][rk-2]==0) { 
                   BB[ri][rk]=2; BB[ri][rk-1]=2; BB[ri][rk-2]=2; OneTable(n, m, BB); t++; break;
               } rdest=0;
            }

    }
    t = 0;
    while(t < ship2){
            ri = Random(n);
            rk = Random(m);
            rdest = Random(4);

            switch(rdest){
               case 0: 
               if(ri<1) ri=1; 
               if(BB[ri][rk]==0 && BB[ri-1][rk]==0) { 
                   BB[ri][rk]=2; BB[ri-1][rk]=2; OneTable(n, m, BB); t++; break;
               } rdest=1;
               
               case 1: 
               if(ri>((n-1)-1)) ri=(n-1)-1;
               if(BB[ri][rk]==0 && BB[ri+1][rk]==0) { 
                   BB[ri][rk]=2; BB[ri+1][rk]=2; OneTable(n, m, BB); t++; break;
               } rdest=2;
               
               case 2: 
               if(rk>((m-1)-1)) rk=(m-1)-1;
               if(BB[ri][rk]==0 && BB[ri][rk+1]==0) { 
                   BB[ri][rk]=2; BB[ri][rk+1]=2; OneTable(n, m, BB); t++; break;
               } rdest=3;
               
               case 3: 
               if(rk<1) rk=1;
               if(BB[ri][rk]==0 && BB[ri][rk-1]==0) { 
                   BB[ri][rk]=2; BB[ri][rk-1]=2; OneTable(n, m, BB); t++; break;
               } rdest=0;
            }

    }
    t = 0;
    while(t < ship1){
            ri = Random(n);
            rk = Random(m);
            rdest = Random(4);

            switch(rdest){
               case 0: 
               if(BB[ri][rk]==0) { 
                   BB[ri][rk]=2; OneTable(n, m, BB); t++; break;
               } rdest=1;
               
               case 1: 
               if(BB[ri][rk]==0) { 
                   BB[ri][rk]=2; OneTable(n, m, BB); t++; break;
               } rdest=2;
               
               case 2: 
               if(BB[ri][rk]==0) { 
                   BB[ri][rk]=2; OneTable(n, m, BB); t++; break;
               } rdest=3;
               
               case 3: 
               if(BB[ri][rk]==0) { 
                   BB[ri][rk]=2; OneTable(n, m, BB); t++; break;
               } rdest=0;
            }

    }
    OutTable(BB, n, m); //delete this string later
    cout << "The computer is ready! And you? ";
    char answer;
    cin >> answer;
    CheckTable(ik_num[r][0], ik_num[r][1], n, m, B, 0, false);
    while(my_score < ship1+ship2+ship3+ship4 && comp_score < ship1+ship2+ship3+ship4){
        CheckTable(i_changed, k_changed, n, m, B, dir_changed, false);
    }
}

