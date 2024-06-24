#pragma once
#include"Random.h"
#include"..\\FlightManagement\\passenger_tree.h"

string Ho[] = {
    "Nguyen", "Tran", "Le", "Pham", "Huynh", "Vo", "Phan", "Truong", "Bui", "Dang",
    "Do", "Ngo", "Ho", "Duong", "Dinh", "Doan", "Lam",
    "Cao", "Ly", "Luu","Thai", "Phung", "To",
    "Vuong","Quach", "Lai", "Hua","Chu",
    "La", "Trieu", "Kieu", "Hong",
    "Kim",
};

string TenNam[] = {
    "Huy", "Khang", "Bao", "Minh", "Phuc", "Khoa", "Phat", "Dat", "Khoi",
    "Long", "Nam", "Duy", "Quan", "Kiet", "Thinh", "Tuan", "Hung", "Hoang", "Hieu",
    "Nhan", "Tri", "Tai", "Phong", "Nguyen", "Phu", "Duc", "Dung",
    "Loc", "Khanh", "Vinh", "Tien", "Nghia", "Thien", "Hao", "Hai", "Dang", "Quang",
};

string TenNu[] = {
    "Anh", "Vy", "Ngoc", "Nhi", "Han", "Thu", "Linh", "Nhu", "Ngan", "Phuong",
    "Thao", "My", "Tran", "Quynh", "Nghi", "Trang", "Tram", "An", "Thy", "Chau",
    "Truc", "Uyen", "Yen", "Y", "Tien", "Mai", "Ha", "Van", "Nguyen", "Huong",
    "Quyen", "Duyen", "Kim", "Trinh", "Thanh", "Tuyen", "Hang", "Duong", "Chi", "Giang",
    "Tam", "Lam", "Tu", "Anh", "Hien", "Khanh", "Minh", "Huyen", "Thuy", "Vi",
    "Ly", "Dung", "Nhung", "Phuc", "Lan", "Phung", "An", "Thi", "Khanh", "Ky",
    "Nga", "Tuong", "Thuy", "My", "Hoa", "Tuyet", "Lam", "Thuy", "Dan", "Hanh",
    "Xuan", "Oanh", "Man", "Khue", "Diep", "Thuong", "Nhien", "Bang", "Hong", "Binh",
    "Loan", "Tho", "Phuong", "Mi", "Nha", "Nguyet", "Bich", "Dao", "Diem", "Kieu",
    "Hieu", "Di", "Lien", "Tra", "Tue", "Tham", "Dieu", "Quan", "Nhan", "Doanh"
};

string HoLotNu[] = {"Thi", "Ngoc", "Thu", "Thanh", "Phuong", "Kim", "Hong", "Thuy", "Minh", "My",
        "Bao", "Quynh", "Thuy", "Khanh", "Bich", "Nhu", "Thao", "Mai", "Yen", "Anh",
        "Huyen", "Kieu", "Tuyet", "Hai", "Hoang", "Lan", "Cam", "Hoai", "Ha", "Huong",
        "Anh", "Gia", "Van", "Xuan", "Dieu", "Diem", "Truc", "Tuong", "Tuan", "Thien",
        "Tra", "Thuy", "Nhat", "Le", "Linh", "Huynh", "To", "Ai", "Viet", "Nha", "Nguyet",
        "Mong", "Uyen", "Tram", "Thuc", "Thai", "Hanh", "Nhat", "Le", "Linh", "Huong", "Dung",
        "My", "Trung", "Loan", "Sao", "Hieu", "Phuoc", "Thy", "Luu", "Vinh", "Thien", "Tung",
        "Son", "Thien", "Thoai", "Dai", "Giang", "Duyen", "Thanh", "Oanh", "Duc", "Yen", "Hoan",
        "Buu", "Hoa", "Do", "Hue", "Khai", "Dang", "Cuc", "Thuan", "Nhu", "My", "Dung", "Tran",
        "Tai", "Khiet", "Dinh", "Trieu", "Tinh", "Luong", "Nguyen", "Ly", "Mi", "Huu", "Chieu",
        "My", "Quyen", "Phu", "Vuong", "Cao", "Trinh", "The", "Nhat", "Han", "Nhan", "Ni", "Bach",
        "Quoc", "Long", "Han", "Nu", "Ho", "Nhi", "Thuy", "Quyen", "Sa", "Diu", "Ninh", "Tien",
        "Nghi", "Giao", "Dao", "Phoi", "Song", "Nhi", "Tuan", "Na", "Phong", "Quang", "Kha",
        "Suong", "Cham"};

string HoLotNam[] = {"Van", "Minh", "Duc", "Thanh", "Quoc", "Hoang", "Ngoc", "Quang", "Anh", "Xuan",
        "Thanh", "Tuan", "Dinh", "Huu", "Duy", "Gia", "Trung", "Tien", "Cong", "Tan",
        "Trong", "Manh", "The", "Nhat", "Hong", "Viet", "Dang", "Huy", "Chi", "Bao",
        "Hai", "Thai", "Ba", "Truong", "Khanh", "Hoai", "Viet", "Thien", "Phuc", "Phuoc",
        "Phuc", "Vu", "Khac", "Tri", "Phuong", "Nguyen", "Phi", "Kim", "Vinh", "Le", "Dai",
        "Cao", "Thien", "Nam", "Sy", "Hung", "Tung", "Nhu", "Nhut", "Son", "Binh", "Tran",
        "Quy", "Long", "Huynh", "A", "An", "Danh", "Dac", "Hieu", "Lam", "Tat", "Ha", "Doan",
        "Duong", "Vinh", "Dong", "Kien", "Nhat", "Khai", "Phat", "Quyet", "Chan", "Ky", "Vi",
        "Trieu", "Luong", "Thuan", "Phong", "Nhan", "Chau", "Tuong", "Toan", "Tu", "Nghia",
        "Vuong", "Khang", "Hao", "Dat", "Hao", "Chung", "Khoa", "Thinh", "Mau", "Mai", "Quan",
        "Doan", "Hien", "Dang", "Bach", "Pham", "Truong", "Thuong", "Quan", "Dung", "Anh", "Vo",
        "Kha", "Do", "Hien", "Qui", "Tieu", "Buu", "Loc", "Thach", "Dan", "Dong", "Van", "Hiep",
        "Ta", "Cuong", "Van", "Ich", "Ton", "Tu", "Thang", "Ton", "Luu", "Tuan", "Thuc", "Vy", "Y",
        "Thang", "Tin", "Lam", "Nang", "Quyen", "Tan", "Vi", "Ngo", "Quynh", "Ke", "Tang", "Thieu",
        "Nho", "Dinh", "Quang", "Lap", "Dieu", "Binh", "Uy", "Cat", "Tu", "Phung", "Vien", "My",
        "Trung", "Be", "Bui", "Han", "Truc", "Tri", "Tien", "Trinh"
};

string to_stringn(int a, int n);
string* Create_random_ID_arr(int n);
void CreateName(char *ho, char*ten, char *gioitinh);



//====================================

string to_stringn(int a, int n){
    string s = "";
    for(int i = 0; i < n; i++){
        s = char('0' + a%10) + s;
        a /= 10;
    }
    return s;
}

string* Create_random_ID_arr(int n){
    int *arr1 = random_arr(0, 999999, n),
        *arr2 = random_arr(0, 999999, n);
    string* id = new string[n];
    for(int i = 0; i < n; i++)
        id[i] = to_stringn(arr1[i], 6) + to_stringn(arr2[i], 6);
    delete[] arr1;
    delete[] arr2;
    return id;
}



void CreateName(char *ho, char*ten, char *gioitinh){
    int k;
    string s;
    k = rand()%(sizeof(Ho)/sizeof(string));
    s = Ho[k];
    if(rand()%2 == 0){
        k = rand()%(sizeof(HoLotNam)/sizeof(string));
        s = s + " " +  HoLotNam[k];
       
        strcpy(ho, s.c_str());

        k = rand()%(sizeof(TenNam)/sizeof(string));
        strcpy(ten, TenNam[k].c_str());

        strcpy(gioitinh, "Nam");
    }else{
        k = rand()%(sizeof(HoLotNu)/sizeof(string));
        s = s + " " +  HoLotNu[k];
  
        strcpy(ho, s.c_str());

        k = rand()%(sizeof(TenNu)/sizeof(string));
        strcpy(ten, TenNu[k].c_str());

        strcpy(gioitinh, "Nu");
    }
}

PNode* CreatePassenger(int n){
    string *id = Create_random_ID_arr(n);
    char cccd[13];
    char ho[20];
    char ten[20];
    char sex[4];
    Passenger pas;
    PNode *root = NULL;
    for(int i = 0; i < n; i++){
        strcpy(cccd, id[i].c_str());
        pas.setCccd(cccd);

        CreateName(ho, ten, sex);
        pas.setHo(ho);
        pas.setTen(ten);
        pas.setSex(sex);
        cout << pas.getCccd() << endl
             << "\t"<< pas.getHo() << "-" <<pas.getTen() << "-" << pas.getSex() << endl << endl;
        root = insert(root, pas);
        if(root ==  NULL) cout << "================================err inser" << endl;
    }


    delete[] id;
    return root;
}

