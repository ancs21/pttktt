#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX 100

typedef struct {
	char TenDV[20];
	float TL, GT;
	int PA;
} DoVat;

// khoi tao gia tri
DoVat *dsdv; // Danh sach cac do vat (danh sach dong)
int n; // luu so luong do vat
int x[MAX]; // Luu phuong an tot nhat tam thoi
float W; // Luu trong luong cua Ba lo
float CT; // Luu can tren
float TGT; // Luu Tong gia tri cua cac vat da duoc chon tai moi nut
float GiaLNTT; // Luu Gia lon nhat tam thoi
float TLConLai; // Luu Trong luong con lai cua Ba lo tai moi nut
	
// read file
DoVat *ReadFromFile(float *W, int *n) {
	FILE *f;
	f = fopen("./CaiBalo3.inp", "r");
	// xac dinh trong luong balo
	fscanf(f, "%f", W);

	DoVat *dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while (!feof(f)) {
		fscanf(f, "%f%f", &dsdv[i].TL, &dsdv[i].GT);
		fgets(dsdv[i].TenDV, 20, f);
		dsdv[i].TenDV[strlen(dsdv[i].TenDV) - 1] = '\0';
		dsdv[i].PA = 0;
		i++;
		dsdv = (DoVat*) realloc(dsdv, sizeof(DoVat) * (i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}

// swap
void swap(DoVat *x, DoVat *y) {
	DoVat temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// sap xep bubblesort
void BubbleSort(DoVat *dsdv, int n) {
	int i, j;
	for (i = 0; i <= n-2; i++) {
		for (j = n-1; j >= i+1; j--) {
			float DG_j = dsdv[j].GT / dsdv[j].TL;
			float DG_j_1 = dsdv[j-1].GT / dsdv[j-1].TL;
			if ( DG_j > DG_j_1) swap(&dsdv[j], &dsdv[j-1]);
		}
	}
}

// in bang dsdv
void InDSDV(DoVat *dsdv ,int n, float W){
	int i;
	float TongTL = 0.0, TongGT = 0.0;
	printf("|---|--------------------|---------|---------|---------|---------|\n");
	printf("|%-3s|%-20s|%-9s|%-9s|%-9s|%-9s|\n", "STT", " Ten Do Vat","T.Luong", "Gia Tri", "Don Gia", "P. An");
	printf("|---|--------------------|---------|---------|---------|---------|\n");
	
	for(i = 0;i < n; i++){
		printf("|%-3d", i+1);
		printf("|%-20s", dsdv[i].TenDV);
		printf("|%-9.1f", dsdv[i].TL);
		printf("|%-9.1f", dsdv[i].GT);
		printf("|%-9.1f", dsdv[i].GT / dsdv[i].TL);
		printf("|%-9d|\n", dsdv[i].PA);
		TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
		TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|--------------------|---------|---------|---------|---------|\n");
	printf("Trong luong cua ba lo = %9.1f\n", W);
	printf("Tong trong luong = %9.1f, Tong gia tri = %9.1f\n", TongTL, TongGT);
}

// khoi tao va tinh gia tri tai nut goc
void init(){
	TLConLai = W;
	CT = TLConLai * (dsdv[0].GT / dsdv[0].TL);
	GiaLNTT = 0.0;
	TGT = 0.0;
}

// ghi nhan phuong an tot nhat tam thoi
void GhiNhanKyLuc(){
	int i;
	if(GiaLNTT < TGT){
		GiaLNTT = TGT;
		for(i = 0; i < n; i++)
			dsdv[i].PA = x[i];
	}
}
// thu phuong an moi
void Try(int i) {
	int j; // so do vat dc chon
	for (j = 1; j >= 0; j--) {
		TGT += j*dsdv[i].GT;
		TLConLai -= j*dsdv[i].TL;
		CT = TGT + TLConLai * (dsdv[i+1].GT / dsdv[i+1].TL);
		if (CT > GiaLNTT) { // k cat tia
			x[i] = j;
			if ( i == n-1  || TLConLai == 0) GhiNhanKyLuc();
			else Try(i+1);
		}
		// quay lui xet tip
		x[i] = 0;
		TGT -= j * dsdv[i].GT;
		TLConLai += j * dsdv[i].TL;
	}
}


int main() {
	

	// read file
	dsdv = ReadFromFile(&W, &n);
	
	// sap xep
	BubbleSort(dsdv, n);
	
	// khoi tao nut goc
	init();
	
	// thu tim phuong an tot nhat
	Try(0);
	
	// in dsdv va phuong an
	InDSDV(dsdv, n, W);
	
	// giai phong bo nho
	free(dsdv);
		
	return 0; 	
}
