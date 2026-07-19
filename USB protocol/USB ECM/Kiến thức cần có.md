### I. Lý thuyết:

1. HTTP (HyperText Transfer Protocol):

- Là hình thức truyền tải siêu văn bản. Là quy tác chuẩn dùng để truyền dữ liệu giữa trình duyệt web(client) và máy chủ web (server).

- Chạy trên nền TCP/IP. Được dùng trong hầu hết các ứng dụng web và API hiện nay.

- Khi ta truy cập `https://example.com`, trình duyệt sẽ gửi đi lệnh ![alt text](image.png) 

    và máy chủ sẽ phản hồi 

    ![alt text](image-1.png)

- HTTPS khác HTTP là có thêm mã hóa và bảo mật dữ liệu, dùng cổng 443 thay vì cổng 80.

2. Giải thích chức năng của USB ECM: Lúc này USB device hoạt động như một card mạng ảo, và chúng ta có thể dùng host(laptop) mở trình duyệt (như 1 client trong http) và truy cập vào USB device(trong USB device sẽ chạy chương trình hoạt động như 1 server nói trên và có thể phản hồi nhữ gói tin mạng) bằng địa chỉ IP như vào 1 trang web thật.
![alt text](image-3.png)

- Ethernet frames: hà đơn vị dữ liệu thấp nhất của mạng Ethernet, chứa header (địa chỉ MAC, loại gói…) và payload (dữ liệu chính, ví dụ như TCP/IP hoặc ICMP).

Khi dùng giao thức ECM, mỗi frame Ethernet được đóng gói vào USB bulk transfer, gửi qua endpoint.

![alt text](image-4.png)

Mô hình OSI:

![alt text](image-5.png)

3. USB CDC là chuẩn có hỗ trợ nhiều Subclass cho các thiết bị mạng khác nhau. Các loại mạng qua Ethernet qua USB được sử dụng:
Ethernet Control Model (ECM), Ethernet Emulation Model (EEM),Network Control Model (NCM).

#### 1. USB ECM:

 USB ECM dùng Bulk transaction
 ![alt text](image-13.png)

- Các Define và Descriptor:

![alt text](image-6.png)
![alt text](image-7.png)

![alt text](image-8.png)
![alt text](image-9.png)
![alt text](image-10.png)
![alt text](image-11.png)

- USB ECM có 2 interface desriptors: CDC Communication interface và CDC Data interface

- Mỗi Ethernet frame: 
![alt text](image-12.png)

- LwIP (Lightweight IP) là một stack giao thức TCP/IP mã nguồn mở được thiết kế để sử dụng trong các hệ thống nhúng có tài nguyên hạn chế như vi điều khiển (MCU).

- TCP/IP là ngôn ngữ chung của Internet — mọi thiết bị (PC, điện thoại, router, camera, thiết bị nhúng...) khi kết nối mạng đều phải dùng TCP/IP để gửi và nhận dữ liệu.

![alt text](image-15.png)

![alt text](image-16.png)

![alt text](image-17.png)

![alt text](image-18.png)

#### 2. Chạy thử USB ECM với TinyUSB trên STM32F7

Hướng dẫn các add USBTiny vào project

Những thư mục cần pull về:
![alt text](image-14.png)

Nếu thêm đường dẫn vào rồi mà nó vẫn báo lỗi vào những trường hợp như này ![alt text](image-22.png) thì lúc này cần chuột phải vào thư mục nhấn vào chỗ xám như trên hình
![alt text](image-21.png)

- Bước 1 vào file tusb_config.h: để cấu hình cho TinyUSB

```C
#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#define CFG_TUSB_MCU OPT_MCU_STM32F7
#define CFG_TUSB_RHPORT0_MODE OPT_MODE_DEVICE
#define CFG_TUD_ENABLED 1
#define CFG_TUD_NET 1
#define CFG_TUD_NET_ECM_RNDIS 1
#define CFG_TUD_NET_MTU 1514

#endif
```

Trong file main.c
![alt text](image-19.png)

Chưa thêm vào file những hàm này:
![alt text](image-20.png)

- Bước 2: