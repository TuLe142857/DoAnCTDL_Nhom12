# Đồ Án Cấu Trúc Dữ Liệu Và Giải Thuật - Nhóm 12
### Thành viên:
- Lê Ngọc Tú
- Đặng Hữu Hiếu
- Nguyễn Sỹ Kim Bằng

## Table of Contents
- [Đề tài](#1)
- [Xây dựng chương trình](#2)
- [Đọc kỹ hdsd trước khi dùng](#3)
- [Kết quả thi](#4)

### Đề tài<a name = "1"></a>
#### - Quản lý chuyến bay nội địa
#### - Cấu trúc dữ liệu:
- [Máy bay](FlightManagement\\Plane.h): Mảng con trỏ tối đa 300 máy bay. Mỗi máy bay có các thông tin(<u>Số hiệu MB</u>(C15), loại máy bay(C40), số dãy, số dòng); Mỗi máy bay có 1 số hiệu duy nhất; (số chỗ = số dãy * số dòng), số chỗ >= 20.
    Nếu số dãy = 5 nghĩa là máy bay có 5 các dãy A, B, C, D, E; Nếu số dòng = 20 nghĩa là máy bay có các hàng ghế được đánh số từ 1 đến 20.Kết hợp dãy và hàng ghế ta sẽ có số vé
    Theo ví dụ trên, ta có 100 vé với các số vé A01, A02, ....A20, ... E19, E20.
- [Chuyến bay](FlightManagement\\Flight.h): danh sách liên kết đơn( <u>Mã CB</u>(C15), Ngày giờ khời hành, sân bay đến, trạng thái, Số hiệu MB, danh sách vé). Mỗi chuyến bay có 1 mã duy nhất; trạng thái chuyến bay bao gồm: `0: Hủy chuyến` `1: Còn vé` `2: Hết vé` `3: Hoàn tất`; danh sách vé cho biết thông tin vé trên chuyến bay, và số CMND của hành khách đã đặt vé đó. Danh sách vé được cấp phát bộ nhớ tự động dựa vào số chỗ của máy bay thực hiện chuyến bay. **Danh sách chuyến bay luôn có sẵn thứ tự theo mã chuyến bay.**
- [Hành khách](FlightManagement\\passenger_tree.h): cây nhị phân tìm kiếm cân bằng(<u>Số CMND</u>, Ho , Ten, Phai)

#### - Các chức năng theo yêu cầu đề bài:
a) Cập nhật danh sách các máy bay(thêm/ xóa/ hiệu chỉnh)
b) Cập nhật chuyến bay: 
c)
d)
e)
f)
g)
h)
> [!NOTE]
> Lưu ý: Chương trình cho phép lưu các danh sách vào file; Kiểm tra điều kiện khi nhập dữ liệu làm dữ liệu bị sai

### Xây dựng chương trình <a name = "2"></a>
#### - Phân công thành viên:    
- Chương trình có 3 cấu trúc dữ liệu chính => mỗi thành viên code 1 CTDL
- Chương trình xử lý 3 vấn đề(tương tác thêm/chỉnh,... 3 cấu trúc dữ liệu chính), chia chương trình thành 3 phần tương ứng, mỗi thành viên một phần(tương ứng với cấu trúc dữ liệu của người đó code)
#### - Các vấn đề xử lý 
- **`Máy bay`**: 
- **`Chuyến bay`**:
  - Tự quy ước: Thời gian tối thiểu để một máy bay thực hiện hai chuyến bay liên tiếp là 3h = 3 * 60 phút = 180 phút
  - Điều kiện thêm chuyến bay:
  - Điều kiện chỉnh chuyến bay:
    - Chuyến bay có trạng thái `1: Còn vé` hoặc `2: Hết vé`
    - Không được chỉnh thời gian về gần với hiện tại(chỉ được lùi thời gian bay)
      - Nếu đổi máy bay: Máy bay không được xung đột thời gian bay
      - Hành khách không được xung đột thời gian bay
  - Điều kiện đặt/ hủy vé:
  - Điều kiện hủy chuyến bay: 
  - Điều kiện in danh sách hành khách trong chuyến bay: luôn in được
- **`Hành khách`**:

### Hướng dẫn chạy CT + ảnh demo <a name = "3"></a>

#### - Hướng dẫn tải và chạy CT
- Chương trình sử dụng đồ họa Graphics.h
- Biên dịch bằng DevC(chỉ dùng được complier 32 bit)
- Tải DevC và cài đặt thư viện Graphics.h [tại đây](https://www.google.com) :smiley:
- Clone repo về máy
- Dùng DevC mở và chạy [CreateData.dev](CreateData\CreateData.dev) để tạo folder `Data`
- Copy folder `Data` vào folder `FlightManagement`
- Dùng DevC mở và chạy [FlightManagement.dev](FlightManagement\FlightManagement.dev)

> [!NOTE]
> Tìm hiểu thêm về các hàm trong thư viện Graphics.h: <https://home.cs.colorado.edu/~main/bgi/doc/>

#### - Ảnh demo
![](Image\mainmenu.png)

![](Image\planetab1.png)

![](Image\flighttab1.png)

![](Image\passengertab1.png)


### Kết quả thi<a name = "4"></a>
> `25/6/2024`Mai thi mà nay chưa học xong cây AVL với Heap sort :)

- [ ] Qua môn :satisfied:
- [ ] A+
- [ ] A
- [ ] B+
- [ ] B
- [ ] C+
- [ ] C
- [ ] Rớt môn :scream: