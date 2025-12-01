#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

struct Material{
	char matId[10]; //ma vat tu
	char name[50]; //ten vat tu
	char unit[10]; //don vi vat tu
	int qty; //so luong ton kho
	int status; //trang thai(1 con su dung, 0 het han)
};

struct Transaction{
	char transId[20]; //Ma giao dich(sinh ngau nhien hoac tu tang)
	char matId[10]; //ma vat tu
	char type[5]; //kieu xuat nhap(IN = nhap / OUT = xuat)
	char date[15]; //thoi gian giao dich
	int amount;
	char matName[50];
};

struct Material initList[10]= {
    {"01", "Shisha", "Chiec", 20, 1},
    {"02", "Xang", "Can", 30, 1},
    {"03", "Kim loai", "Tan", 50, 1},
    {"04", "Tao", "Qua", 200, 0},
    {"05", "Chanh", "Thung", 10, 0},
    {"06", "Sua", "Hop", 20, 1},
    {"07", "Nem chua", "Hop", 36, 0},
    {"08", "Snack", "Goi", 80, 1},
    {"09", "Da tang", "Tan", 40, 1},
    {"10", "Keo", "Goi", 40, 1}
};

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int isDuplicateId(struct Material materials[], int length, char matId[]){
	for(int i = 0; i < length; i++){
		if(strcmp(materials[i].matId, matId) == 0){
			return 1;
		}
	}
	return 0;
}

int checkInvalidInput(char *s){
	if(strlen(s) == 0){
		return 1;
	}
	for (int i = 0; s[i] != '\0'; i++) {
        if (!isspace(s[i])) { 
            return 0;
        }
    }
	return 1;
}


void displayMat(struct Material Mat){
    printf("\n Ma vat tu: %s", Mat.matId);
    printf("\n Ten vat tu: %s", Mat.name);
    printf("\n Don vi: %s", Mat.unit);
    printf("\n So luong ton kho: %d", Mat.qty);
}

void addMat(struct Material materials[], int *count){
	struct Material newMaterial;
	
	int index;
	int currentIndex = *count;
	char choiceStr[10];
	
	do{
	printf("Nhap so luong vat tu can them: ");
	if(fgets(choiceStr,sizeof(choiceStr),stdin)==NULL){
		choiceStr[0] = '\0';
	}
	choiceStr[strcspn(choiceStr,"\n")] = 0;
	
	if(checkInvalidInput(choiceStr) == 1){
		printf("So luong vat tu khong duoc de trong hoac chi chua khoang trang. Vui long nhap lai.\n");
		continue;
	}
	
	index = atoi(choiceStr);
	if (index > 0) {
		break;
	} else {
		printf("So luong vat tu can them phai la so nguyen duong. Vui long nhap lai.\n");
	}
	}while(1);;
	


	for(int i = 0 ; i < index ; i++){
		int pos = currentIndex + i;
		
		printf("\n-----Vat tu thu %d-----\n",pos + 1);
 
	do {
        printf("Nhap ma vat tu (matId): ");
        fgets(newMaterial.matId, sizeof(newMaterial.matId), stdin);
        newMaterial.matId[strcspn(newMaterial.matId,"\n")] = 0;
        
        int isDuplicate = isDuplicateId(materials, *count, newMaterial.matId);

        if (checkInvalidInput(newMaterial.matId) == 1) {
            printf("Ma vat tu khong duoc de trong hoac chi chua khoang trang. Vui long nhap lai.\n");
        } 
        else if (isDuplicate) {
            printf("Ma vat tu '%s' da ton tai. Vui long nhap ma khac.\n", newMaterial.matId);
        } 
        else {
            break;
        }
    } while(1);
    
	do {
        printf("Nhap ten vat tu: ");
        fgets(newMaterial.name, sizeof(newMaterial.name), stdin);
        newMaterial.name[strcspn(newMaterial.name,"\n")] = 0;

        if (checkInvalidInput(newMaterial.name) == 1) {
            printf("Ten vat tu khong duoc de trong hoac chi chua khoang trang. Vui long nhap lai.\n");
        } else {
            break;
        }
    } while(1);
	
	do {
        printf("Nhap don vi vat tu: ");
        fgets(newMaterial.unit, sizeof(newMaterial.unit), stdin);
        newMaterial.unit[strcspn(newMaterial.unit,"\n")] = 0;

        if (checkInvalidInput(newMaterial.unit) == 1) {
            printf("Don vi vat tu khong duoc de trong hoac chi chua khoang trang. Vui long nhap lai.\n");
        } else {
            break;
        }
    } while(1);
	
	do {
	printf("Nhap so luong ton kho (qty >= 0): ");
	if(scanf("%d",&newMaterial.qty) == 1 && newMaterial.qty >= 0){
		clearBuffer();
		break;
    }else{
		printf("So luong ton kho khong hop le. Vui long nhap so nguyen >= 0.\n");
		clearBuffer();
	}
	}while(1);
	
	newMaterial.status = 1;
	printf("Trang thai khoi tao: Active (status = %d).\n", newMaterial.status);
	
	materials[*count] = newMaterial;
	(*count)++;
}
}

void updateMat(struct Material materials[], int count){
    char searchId[10];
    int foundIndex = -1;
    int i;

    printf("\n__________CAP NHAT THONG TIN VAT TU__________\n");
    
    printf("Nhap ma cua vat tu ban muon cap nhat: ");
    fgets(searchId, sizeof(searchId), stdin);
    searchId[strcspn(searchId, "\n")] = 0;

    for (i = 0; i < count; i++) {
        if (strcmp(materials[i].matId, searchId) == 0 && materials[i].status == 1) { 
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("\nKhong tim thay vat tu co ma '%s' hoac vat tu da bi vo hieu hoa (Inactive)!\n", searchId);
        return;
    }

    printf("\n--- Bat dau cap nhat thong tin cho vat tu co ma: %s ---\n", materials[foundIndex].matId);


    do {
        printf("Nhap ten vat tu moi: ");
        fgets(materials[foundIndex].name, sizeof(materials[foundIndex].name), stdin);
        materials[foundIndex].name[strcspn(materials[foundIndex].name, "\n")] = 0;

        if (checkInvalidInput(materials[foundIndex].name) == 1) {
            printf("Ten vat tu khong duoc de trong hoac chi chua khoang trang. Vui long nhap lai.\n");
        } else {
            break;
        }
    } while(1);

    do {
        printf("Nhap don vi vat tu moi: ");
        fgets(materials[foundIndex].unit, sizeof(materials[foundIndex].unit), stdin);
        materials[foundIndex].unit[strcspn(materials[foundIndex].unit, "\n")] = 0;

        if (checkInvalidInput(materials[foundIndex].unit) == 1) {
            printf("Don vi vat tu khong duoc de trong hoac chi chua khoang trang. Vui long nhap lai.\n");
        } else {
            break;
        }
    } while(1);

	int newQty;
	do {
	printf("Nhap so luong ton kho moi(qty >= 0): ");
	if(scanf("%d", &newQty) == 1 && newQty >= 0) {
		materials[foundIndex].qty = newQty;
		clearBuffer();
		break;
    } else {
		printf("So luong ton kho khong hop le. Vui long nhap so nguyen >= 0.\n");
		clearBuffer();
    }
	}while(1);

    printf("\n Cap nhat thong tin vat tu co ma %s thanh cong!\n", materials[foundIndex].matId);
}

void manageStatus(struct Material materials[], int count) {
	char searchId[10];
	int foundIndex = -1;
    
	printf("\n__________QUAN LY TRANG THAI VAT TU (KHOA)__________\n");
	printf("Nhap ma vat tu ban muon khoa/xoa: ");
	fgets(searchId, sizeof(searchId), stdin);
    searchId[strcspn(searchId, "\n")] = 0;

    for (int i = 0; i < count; i++) {
		if (strcmp(materials[i].matId, searchId) == 0) {
			foundIndex = i;
			break;
		}
	}

	if (foundIndex == -1) {
		printf("\nLoi: Khong tim thay vat tu co ma '%s'.\n", searchId);
		return;
	}

	if (materials[foundIndex].status == 0) {
		printf("\nVat tu co ma %s da bi khoa (status = 0) tu truoc.\n", materials[foundIndex].matId);
	} else {
		materials[foundIndex].status = 0;
		printf("\nThanh cong! Vat tu co ma %s da duoc khoa/vo hieu hoa (status = 0).\n", materials[foundIndex].matId);
		printf("Vat tu nay khong the thuc hien giao dich xuat/nhap.\n");
	}
}


void searchMat(struct Material materials[], int length){
	int choice;
	char searchKey[50];
	int foundCount = 0;
	char choiceStr[10];

	do{
	printf("\n__________TIM KIEM VAT TU__________\n");
	printf("Ban muon tim kiem theo tieu chi nao?\n");
	printf("1. Ma vat tu (ID - chinh xac)\n");
	printf("2. Ten vat tu (Name - gan dung)\n");
	printf("3. Thoat\n");
	printf("Lua chon cua ban: ");
	
	if(fgets(choiceStr,sizeof(choiceStr),stdin)==NULL){
		choiceStr[0] = '\0';
	}
	choiceStr[strcspn(choiceStr,"\n")] = 0;
	
	if(checkInvalidInput(choiceStr) == 1){
		printf("Lua chon khong duoc de trong.\n");
		continue;
	}
    
    choice = atoi(choiceStr);
    
    if (choice == 3) {
        printf("\nThoat chuc nang tim kiem.\n");
        break;
    }
    
    if (choice != 1 && choice != 2) {
        printf("Lua chon khong hop le. Vui long nhap 1, 2, hoac 3.\n");
        continue;
    }

	printf("Nhap tu khoa can tim kiem: ");
	fgets(searchKey, sizeof(searchKey), stdin);
	searchKey[strcspn(searchKey, "\n")] = 0;
    
	if (checkInvalidInput(searchKey) == 1) {
		printf("Tu khoa khong duoc de trong.\n");
		continue;
	}

	printf("\n--- Ket qua tim kiem ---\n");
	for(int i = 0; i < length; i++){
		if(materials[i].status == 1){ 
			if(choice == 1){
				if(strcmp(searchKey, materials[i].matId) == 0){
					displayMat(materials[i]);
					foundCount++;
				}
			} else if(choice == 2){
				if(strstr(materials[i].name, searchKey) != NULL){
					displayMat(materials[i]);
					foundCount++;
				}
			}
		}
	}
    
	if(foundCount == 0){
		printf("Khong tim thay vat tu nao phu hop voi tu khoa '%s'.\n", searchKey);
    }
	printf("\n");
}while(1);
}


void swap_material(struct Material *a, struct Material *b) {
    struct Material temp = *a;
    *a = *b;
    *b = temp;
}

void sortName(struct Material arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
                swap_material(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void sortQuantity(struct Material arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].qty > arr[j + 1].qty) {
                swap_material(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void displayMaterialList(struct Material materials[], int length) {
    for (int i = 0; i < length; i++) {
        const char *status_str = materials[i].status == 1 ? "Con su dung" : "Het han su dung";
        
        printf("| ID: %s | Name: %s | Unit %s | Quantity: %d | Status: %s |\n", materials[i].matId,materials[i].name, materials[i].unit,materials[i].qty,status_str);
    }
}



void handleSortMenu(struct Material materials[], int currentSize) {
	if (currentSize == 0) {
		printf("Danh sach vat tu hien dang trong. Vui long them vat tu truoc.\n");
		return;
	}

	printf("\n__________SAP XEP DANH SACH VAT TU__________\n");
	printf("Ban muon sap xep theo tieu chi nao?\n");
	printf("1. Ten vat tu (A-Z - Tang dan)\n");
	printf("2. So luong ton kho (Tang dan)\n");
	printf("Lua chon cua ban: ");

	int sort_choice;
	if (scanf("%d", &sort_choice) != 1) {
		printf("Lua chon khong hop le. Khong thuc hien sap xep.\n");
		clearBuffer();
		return;
	}
    clearBuffer();

    if (sort_choice == 1) {
		sortName(materials, currentSize);
		printf("\nSap xep thanh cong theo ten vat tu (A-Z).\n");
	} else if (sort_choice == 2) {
		sortQuantity(materials, currentSize);
		printf("\nSap xep thanh cong theo So luong ton kho (Tang dan).\n");
    } else {
		printf("Lua chon sap xep khong hop le. Khong thuc hien sap xep.\n");
		return;
	}

    displayMaterialList(materials, currentSize);
}


void displayPagingList(struct Material materials[], int length) {
    if (length == 0) {
        printf("Danh sach vat tu hien dang trong. Vui long them vat tu truoc.\n");
        return;
    }

    const int PAGE_SIZE = 5;
    int total_pages = (length + PAGE_SIZE - 1) / PAGE_SIZE;
    int current_page = 1;
    int i, start_index, end_index;
    
    char choiceStr[10];
    int choice;

    do {
        printf("\n__________DANH SACH VAT TU (PHAN TRANG) - Trang %d/%d__________\n", current_page, total_pages);
        start_index = (current_page - 1) * PAGE_SIZE;
        end_index = start_index + PAGE_SIZE;
        if (end_index > length) {
            end_index = length;
        }

        printf("+----------+--------------------------------+------------+----------+----------------+\n");
        printf("| %-8s | %-30s | %-10s | %-8s | %-14s |\n", "ID", "Ten Vat Tu", "Don Vi", "So Luong", "Trang Thai");
        printf("+----------+--------------------------------+------------+----------+----------------+\n");

        for (i = start_index; i < end_index; i++) {
            const char *status_str = materials[i].status == 1 ? "Con su dung" : "Het han su dung";
            
            printf("| %-8s | %-30s | %-10s | %-8d | %-14s |\n", materials[i].matId, materials[i].name, materials[i].unit, materials[i].qty, status_str);
        }
        printf("+----------+--------------------------------+------------+----------+----------------+\n");

        printf("\nTrang %d/%d. Nhap '1' de den trang truoc, '2' de den trang sau, hoac '3' de thoat: ", current_page, total_pages);

        if(fgets(choiceStr,sizeof(choiceStr),stdin)==NULL){
			choiceStr[0] = '\0';
		}
		choiceStr[strcspn(choiceStr,"\n")] = 0;

		if(checkInvalidInput(choiceStr) == 1){
			printf("Lua chon khong duoc de trong hoac chi chua khoang trang. Vui long nhap lai.\n");
			continue;
		}
            choice = atoi(choiceStr);

        if (choice == 1) {
            if (current_page > 1) {
                current_page--;
            } else {
                printf("Ban dang o trang dau tien.\n");
            }
        } else if (choice == 2) {
            if (current_page < total_pages) {
                current_page++;
            } else {
                printf("Ban dang o trang cuoi cung.\n");
            }
        } else if (choice == 3) {
            printf("\nThoat chuc nang phan trang.\n");
            break;
        } else {
            printf("Lua chon khong hop le. Vui long nhap '1', '2', hoac '3'.\n");
        }
        
    } while (1);
}

	struct Transaction history[200]; 
	int transCount = 0;
	int autoTransId = 1000;

void generateTransId(char *id) {
    sprintf(id, "T%04d", autoTransId++);
}

void transMatInOut(struct Material materials[], int length, struct Transaction history[], int *transCount) {
    char matId[10];
    int index = -1;
    int typeChoice;
    int amount;
    char amountStr[20];

    printf("\n__________GIAO DICH XUAT/NHAP VAT TU__________\n");
    
    do {
        printf("Nhap ma vat tu (matId): ");
        fgets(matId, sizeof(matId), stdin);
        matId[strcspn(matId, "\n")] = 0;
        
        if (checkInvalidInput(matId) == 1) {
            printf("Ma vat tu khong duoc de trong. Vui long nhap lai.\n");
            continue;
        }

        for (int i = 0; i < length; i++) {
            if (strcmp(materials[i].matId, matId) == 0) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            printf("Khong tim thay vat tu co ma '%s'. Vui long nhap lai.\n", matId);
        } else {
            break;
        }
    } while(1);

    if (materials[index].status == 0) {
        printf("Loi: Vat tu co ma %s da bi vo hieu hoa (status = 0). Khong the giao dich.\n", matId);
        return;
    }
	
    printf("\n--------------Chon loai giao dich-------------");
	printf("\n1. Nhap vat tu (IN)");
	printf("\n2. Xuat vat tu (OUT)");
	printf("\nLua chon: ");
    if (scanf("%d", &typeChoice) != 1) {
        printf("Lua chon khong hop le.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    if (typeChoice != 1 && typeChoice != 2) {
        printf("Loai giao dich khong hop le.\n");
        return;
    }
    
    
    do {
        printf("Nhap so luong can giao dich: ");
        fgets(amountStr, sizeof(amountStr), stdin);
        amountStr[strcspn(amountStr, "\n")] = 0;
        amount = atoi(amountStr); 

        if (amount <= 0) {
            printf("So luong phai lon hon 0. Vui long nhap lai.\n");
        } else if (typeChoice == 2 && materials[index].qty < amount) {
            printf("Loi: So luong xuat (%d) lon hon so luong ton kho hien tai (%d). Vui long nhap lai.\n", amount, materials[index].qty);
        } else {
            break;
        }
    } while(1);

    if (typeChoice == 1) {
        materials[index].qty += amount;
        printf("\nThanh cong: Da nhap %d '%s'. So luong moi: %d.\n", amount, materials[index].name, materials[index].qty);
    }else{
        materials[index].qty -= amount;
        printf("\nThanh cong: Da xuat %d '%s'. So luong moi: %d.\n", amount, materials[index].name, materials[index].qty);
    }
    
    struct Transaction t;
    generateTransId(t.transId);
    strcpy(t.matId, materials[index].matId);
    strcpy(t.type, typeChoice == 1 ? "IN" : "OUT");
    
    t.amount = amount;
	strcpy(t.matName, materials[index].name);

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(t.date, 15, "%d/%m/%Y", tm_info);

    if (*transCount < 200) {
        history[(*transCount)++] = t;
        printf("Giao dich da duoc luu voi Ma GD: %s.\n", t.transId);
    } else {
        printf("Canh bao: Khong du cho de luu log giao dich.\n");
    }
}

void displayHistory(struct Transaction history[], int transCount) {
    if (transCount == 0) {
        printf("\nChua co giao dich nao duoc thuc hien.\n");
        return;
    }

    printf("\n__________LICH SU XUAT/NHAP VAT TU__________\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("| %-8s | %-8s | %-8s | %-14s | %-8s | %-30s\n", "Ma GD", "Ma VT", "Loai", "Ngay GD","So luong","Ten vat tu");
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < transCount; i++) {
        printf("| %-8s | %-8s | %-8s | %-14s | %-8d | %-30s\n", 
               history[i].transId, 
               history[i].matId,
               strcmp(history[i].type, "IN") == 0 ? "NHAP (IN)" : "XUAT (OUT)",
               history[i].date,
			   history[i].amount,
			   history[i].matName);
    }
    printf("-----------------------------------------------------------------------------------\n");
}


int main(){
	struct Material materials[100]; 
	
	int choice;
	int currentSize = 0;
	int length_init = sizeof(initList) / sizeof(initList[0]);
    for(int i = 0; i < length_init; i++){
        materials[i] = initList[i];
    }
	currentSize = length_init;
	char choiceStr[10];
	
	
	do{
		printf("\n+--------------------MENU--------------------+");
		printf("\n1.Them ma hang moi");
		printf("\n2.Cap nhat thong tin");
		printf("\n3.Quan li trang thai(Khoa/Xoa)");
		printf("\n4.Tra cuu(tim kiem)");
		printf("\n5.Danh sach phan trang");
		printf("\n6.Sap xep danh sach");
		printf("\n7.Giao dich xuat/nhap vat tu");
		printf("\n8.Lich su xuat/nhap");
		printf("\n9.Thoat");
		printf("\n+--------------------------------------------+");
		
		printf("\nLua chon cua ban: ");
		
		if(fgets(choiceStr,sizeof(choiceStr),stdin)==NULL){
			choiceStr[0] = '\0';
		}
		choiceStr[strcspn(choiceStr,"\n")] = 0;

		if(checkInvalidInput(choiceStr) == 1){
			printf("Lua chon khong duoc de trong hoac chi chua khoang trang. Vui long nhap lai.\n");
			continue;
		}
            choice = atoi(choiceStr);
		switch(choice){
			case 1:
				addMat(materials,&currentSize);
				break;
			case 2:
				updateMat(materials,currentSize);
				break;
			case 3:
				manageStatus(materials,currentSize);
				break;
			case 4:
				searchMat(materials,currentSize);
				break;
			case 5:
				displayPagingList(materials,currentSize);
				break;
			case 6:
				handleSortMenu(materials,currentSize);
				break;
			case 7:
				transMatInOut(materials,currentSize,history,&transCount);
				break;
			case 8:
				displayHistory(history,transCount);
				break;
			case 9:
				printf("Chuong trinh ket thuc\n");
				return 0;
			default:
				printf("Vui long chi nhap tu 1 den 9\n");
		}
	}while(1);
	
	return 0;
}
