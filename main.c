#include <stdio.h>
#include <stdlib.h>

// Global
char cek[50],pcek[50],bantuan;
int i=0,N,tes=0,extra;
//
void buatakun(int *N){
    FILE *fp,*fj;

    printf("Berapa jumlah akun baru? ");
    scanf("%d",&extra);
    fflush(stdin);
    *N=extra+*N;

    char username[*N][50],password[*N][50];

    if(tes==1){
    fp=fopen("data.txt","r");
    for(i=0;i<*N-extra;i++)fscanf(fp,"%s %s",&username[i],&password[i]);
    fclose(fp);
    }
    fj=fopen("data.txt", "a");

    for(i=*N-extra;i<*N; i++){
    printf("input username : ");
    fgets(username[i],50,stdin);
    strtok(username[i],"\n");
        for(int j=0; j<i; j++){
                if((strcmp(username[i],username[j]))==0){
                printf("Username sudah digunakan %s %d\n",username[i],i);
                printf("Username : ");
                fgets(username[i],50,stdin);
                strtok(username[i],"\n");
            }
        }
    printf("input password : ");
    fgets(password[i],50,stdin);
    strtok(password[i],"\n");
        for(int j=0; j<i; j++){
            if((strcmp(password[i],password[j]))==0){
                printf("Password sudah digunakan\n");
                printf("Password : ");
                fgets(password[i],50,stdin);
                strtok(password[i],"\n");
            }
        }
    }
    for(i=*N-extra; i<*N; i++)fprintf(fj,"%s %s\n",username[i],password[i]);
    fclose(fj);
}
void login(int *N){
    FILE *fp;
    fp=fopen("data.txt","r");
    char username[50][*N],password[50][*N],logout,tambahakun;

    printf("\n>>>Log In<<<\n");
    printf("Username : ");
    fgets(cek,50,stdin);
    strtok(cek,"\n");
    fflush(stdin);
    printf("Password : ");
    fgets(pcek,50,stdin);
    strtok(pcek,"\n");
    fflush(stdin);
    for(i=0;i<*N+1;i++){
        fscanf(fp,"%s %s",&username[i],&password[i]);
        if((strcmp(cek,username[i]))==0 && (strcmp(pcek,password[i]))==0){
            printf("\nLogin Berhasil\n");
            tes=1;
            printf("Apa anda ingin menambahkan akun? (y/n)");
            scanf("%c",&tambahakun);
            fflush(stdin);
            printf("\n");
            if(tambahakun=='y'){
                tes=1;
                buatakun(&*N);
            }
            menu();
            break;
        }
    }
    if(tes==0){
        printf("\nLogin Gagal\n");
        printf("Butuh bantuan? (y/n) ");
        scanf("%c",&bantuan);
        fflush(stdin);
        if(bantuan=='y')help();
        printf("\nApa anda ingin keluar? (y/n) ");
        scanf("%c",&logout);
        fflush(stdin);
        printf("\n");
        if(logout=='y')exit(0);
        else login(&*N);
    }
}
void tambahbarang(int *N){
    FILE *fb,*fd;
    fb=fopen("barang.txt","r");
    int s=0,tem,a=0;
    char temp[50];

    printf("Berapa barang baru? ");
    scanf("%d",&extra);
    fflush(stdin);
    *N=extra+*N;

    struct barang{
        char nama[50],jenis[50];
        int jumlah,harga,kode;
    }b[*N];

    printf("Data Barang: \n");
    printf("---     Nama        Jenis        Harga       Jumlah ---\n");
    for(i=0;i<*N-extra;i++){
        fscanf(fb,"%s %s %d %d\n",&b[i].nama,&b[i].jenis,&b[i].harga,&b[i].jumlah);
        printf("%12s %12s %12d %12d\n",b[i].nama,b[i].jenis,b[i].harga,b[i].jumlah);
    }
    fclose(fb);

    printf("\nPeringatan!! Sensitif terhadap spasi!! (Gunakan _)\n");
    for(i=*N-extra;i<*N; i++){
            printf("input nama barang : ");
            fgets(b[i].nama,50,stdin);
            strtok(b[i].nama,"\n");
            printf("input jenis barang : ");
            fgets(b[i].jenis,50,stdin);
            strtok(b[i].jenis,"\n");
            fflush(stdin);
            printf("input harga barang : ");
            scanf("%d",&b[i].harga);
            for(int j=0; j<i; j++){
                if(strcmp(b[i].nama,b[j].nama)==0 && strcmp(b[i].jenis,b[j].jenis)==0 && b[i].harga==b[j].harga){
                    s=b[j].jumlah;
                    printf("input jumlah barang : ");
                    scanf("%d",&b[i].jumlah);
                    fflush(stdin);
                    b[j].jumlah=b[i].jumlah+s;
                    i=i-1;
                    *N=*N-1;
                    a=1;
                }
            }
            if(a==0){
                printf("input jumlah barang : ");
                scanf("%d",&b[i].jumlah);
                fflush(stdin);
            }
            if(b[i].jumlah==0)*N=*N-1;
    }
    for(int j=0;j<*N;j++){
        for(i=0;i<*N-1;i++){
            if(strcmp(b[i].nama,b[i+1].nama)>0){
                strcpy(temp,b[i].nama);
                strcpy(b[i].nama,b[i+1].nama);
                strcpy(b[i+1].nama,temp);
                tem=b[i].harga;
                b[i].harga=b[i+1].harga;
                b[i+1].harga=tem;
                strcpy(temp,b[i].jenis);
                strcpy(b[i].jenis,b[i+1].jenis);
                strcpy(b[i+1].jenis,temp);
                tem=b[i].jumlah;
                b[i].jumlah=b[i+1].jumlah;
                b[i+1].jumlah=tem;
            }
        }
    }
    fd=fopen("barang.txt","w");
    for(i=0; i<*N; i++)fprintf(fd,"%s %s %d %d \n",b[i].nama,b[i].jenis,b[i].harga,b[i].jumlah);
    fclose(fd);
}
void caribarang(int *N){
    FILE *fa;
    fa=fopen("barang.txt","r");
    int t=0;
    char Cari[50];
    struct brg{
        char nama[50],jenis[50];
        int jumlah,harga;
    }b[*N];

    for(i=0;i<*N;i++)fscanf(fa,"%s %s %d %d\n",&b[i].nama,&b[i].jenis,&b[i].harga,&b[i].jumlah);
    fclose(fa);

    printf("\nJenis yang ada\n");
    for(i=0;i<*N;i++){
        for(int j=0;j<i;j++){
            if(strcmp(b[i].jenis,b[j].jenis)==0)t=1;
        }
        if(t==0)printf("%s ",b[i].jenis);
        t=0;
    }
    printf("\n");
    printf ("Input jenis barang : ");
    fgets(Cari,50,stdin);
    strtok(Cari,"\n");
    fflush(stdin);
    printf("---         Nama        Jenis        Harga       Jumlah ---\n");
    for(i=0;i<*N;i++){
        if(strcmp(b[i].jenis,Cari)==0){
            printf("--- %12s %12s %12d %12d ---\n",b[i].nama,b[i].jenis,b[i].harga,b[i].jumlah);
            printf("\n");
            tes=1;
        }
    }
    if(tes==0)printf("tidak ditemukan\n");
}
void kasir(int *N){
    FILE *fb,*fd;
    fb=fopen("barang.txt","r");
    int no;
    float total=0;
    char tambah='y';
    struct barang{
        char nama[50],jenis[50];
        int jumlah,harga,kode;
    }b[*N];

    for(i=0;i<*N;i++)fscanf(fb,"%s %s %d %d \n",&b[i].nama,&b[i].jenis,&b[i].harga,&b[i].jumlah);
    fclose(fb);

    while(tambah=='y'){
        printf("No         Nama        Jenis        Harga       Jumlah\n");
        for(i=0;i<*N;i++){
            printf("%d. %12s %12s %12d %12d \n",i+1,b[i].nama,b[i].jenis,b[i].harga,b[i].jumlah);
        }
        printf("Nomor Barang(pilih satu): ");
        scanf("%d",&no);
        fflush(stdin);
        if(b[no].jumlah<=0){
            *N=*N-1;
            goto skip;
        }
        no=no-1;
        b[no].jumlah=b[no].jumlah-1;
        total=total+b[no].harga;
        if(b[no].jumlah==0){
            if(no!=*N-1){
                for(int i=no;i<*N-1;i++){
                    strcpy(b[i].nama,b[i+1].nama);
                    b[i].harga=b[i+1].harga;
                    strcpy(b[i].jenis,b[i+1].jenis);
                    b[i].jumlah=b[i+1].jumlah;
                }
            }
            *N=*N-1;
        }
        skip:
        fd=fopen("barang.txt","w");
        for(i=0; i<*N; i++)fprintf(fd,"%s %s %d %d \n",b[i].nama,b[i].jenis,b[i].harga,b[i].jumlah);
        fclose(fd);
        printf("Masih ada lagi? (y/n) ");
        scanf("%c",&tambah);
        fflush(stdin);
    }
       printf ("\n Total Harga = Rp.%.2f\n",total);
}
void menu(){
    FILE *fb;
    fb=fopen("barang.txt","r");
    int pilih,n=0,a;
    char logout;
    tes=0;

    while(fgets(cek,50,fb)!=NULL){
        n=n+1;
        if(feof(fb))break;
    }

    printf("---MENU---\n"
           "1. Tambah barang\n"
           "2. Cari barang\n"
           "3. Kasir\n"
           "4. Log off\n"
           "5. Exit\n"
           "6. Bantuan\n");
    printf("Pilih(1/2/3/4/5/6): ");
    scanf("%d",&pilih);
    fflush(stdin);

    switch(pilih){
        case 1:tambahbarang(&n);menu();
        case 2:if(n==0){printf("Belum ada barang...Silahkan isi data...\n");tambahbarang(&n);menu();}else{caribarang(&n);menu();}
        case 3:if(n==0){printf("Belum ada barang...Silahkan isi data...\n");tambahbarang(&n);menu();}else{kasir(&n);menu();}
        case 4:main();
        case 5:
            printf("Apa anda yakin ingin keluar? (y/n) ");
            scanf("%c",&logout);
            fflush(stdin);
            printf("\n");
            if(logout=='y')exit(0);
            else menu();
        case 6:help();menu();
    }
}
void help(){
    printf("\nPastikan isi file tidak ada spasi dan karakter\n");

}
int main(){
    FILE *fp;
    int pilihan;
    printf("*******************************\n"
           "||||| Halo Selamat Datang |||||\n"
           "*******************************\n");

    if(fp=fopen("data.txt","r")!=NULL){
        fp=fopen("data.txt","r");
        if(fgets(cek,50,fp)==NULL){
            printf("Sepertinya ada kesalahan, silahkan buat akun...\n");
            buatakun(&N);
        }
        rewind(fp);
        while(fgets(cek,50,fp)!=NULL){
            N=N+1;
            if(feof(fp))break;
        }
        login(&N);
    }
    else{
    printf("Belum ada akun...Silahkan buat akun terlebih dahulu...\n");
    buatakun(&N);
    login(&N);
    }
    return 0;
}




