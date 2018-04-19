#include <stdio.h>
#include <malloc.h>
#include <string.h>

// bai toan cai ba lo 2
// so luong gioi han san

// dinh nghia
typedef struct {
	char tenDoVat[30];
	float trongLuong, giaTri;
	int soLuong, phuongAn;
} doVat;

// read file
doVat *readFile(float *W, int *n) {
	FILE *f;
	f = fopen("./CaiBalo2.inp", "r");
	fscanf(f, "%f", W); // get trong luong do vat
	
	doVat *dsdv;
	dsdv = (doVat*) malloc(sizeof(doVat)); // cap bo nho
	
	int i = 0;
	while (!feof(f)) {
		// get trong luong va gia tri do vat		
		fscanf(f, "%f%f%d", &dsdv[i].trongLuong, &dsdv[i].giaTri, &dsdv[i].soLuong);
		// get ten do vat
		fgets(dsdv[i].tenDoVat, 30, f);
		dsdv[i].tenDoVat[strlen(dsdv[i].tenDoVat)  - 1] = '\0';
		dsdv[i].phuongAn = 0;
		i++;
		dsdv = (doVat*)realloc(dsdv, sizeof(doVat) * (i+1));
	}
	*n = i;
	// close file
	fclose(f);
	return dsdv;
}

// swap for sort
void swap(doVat *x, doVat *y) {
	doVat temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// bubble sort
void bubbleSort(doVat *dsdv, int n) {
	int i, j;
	for(i = 0; i <= n-2; i++) {
		for (j = n-1; j >= i+1; j--) {
			float donGia_j = dsdv[j].giaTri / dsdv[j].trongLuong;
			float donGia_j_1 = dsdv[j-1].giaTri / dsdv[j-1].trongLuong;
			
			if( donGia_j > donGia_j_1) {
				swap(&dsdv[j], &dsdv[j-1]);
			}			  
		}
	}
}


// greedy
void greedy(doVat *dsdv, float w, int n) {
	for (int i = 0; i < n; i++) {
		dsdv[i].phuongAn = w / dsdv[i].trongLuong;
		if(dsdv[i].phuongAn > dsdv[i].soLuong) {
			dsdv[i].phuongAn = dsdv[i].soLuong;
		}
		
		w -= dsdv[i].phuongAn * dsdv[i].trongLuong;
		
	}
}

// in bang danh sach do vat vs don gia giam dan
void inDsdv(doVat *dsdv, float W, int n) {
	float tongTL = 0.0;
	float tongGT = 0.0;
	
	printf("|----|--------------------|----------|----------|----------|----------|-------|\n");
	printf("|STT |     Ten do vat     | s. luong | T. luong | Gia tri  | Don gia  | p. an |\n");
	printf("|----|--------------------|----------|----------|----------|----------|-------|\n");
	
	for (int i = 0; i < n; i++) {
		printf("| %-3d", i+1);
		printf("|%-20s", dsdv[i].tenDoVat);
		printf("|%-10.1d", dsdv[i].soLuong);
		printf("|%-10.1f", dsdv[i].trongLuong);
		printf("|%-10.1f", dsdv[i].giaTri);
		printf("|%-10.1f", dsdv[i].giaTri / dsdv[i].trongLuong);
		printf("|%-7d|\n", dsdv[i].phuongAn);
		// tinh tong trong luong
		tongTL += dsdv[i].phuongAn * dsdv[i].trongLuong;
		// tinh tong gia tri
		tongGT += dsdv[i].phuongAn * dsdv[i].giaTri;
	}
	
	printf("|----|--------------------|----------|----------|----------|----------|-------|\n");
	// in ttl
	printf("Tong trong luong = %.1f \t", tongTL);
	// in tgt
	printf("Tong gia tri = %.1f \n\n\n", tongGT);
}




int main() {
	float W; // trong luong
	int n; // so luong do vat
	doVat *dsdv;
	dsdv = readFile(&W, &n);
//	printf("Trong luong: %f", W);
//	printf("\nSo luong do vat: %d", n);
//	
	bubbleSort(dsdv, n);
	greedy(dsdv, W, n);
	inDsdv(dsdv, W, n);
	
//	giai phong bo nho
	free(dsdv);
	
	return 0;
	
}
