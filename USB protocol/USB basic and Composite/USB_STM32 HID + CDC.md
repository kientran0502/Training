### 1 Luồng cơ bản của stack USB:

Nếu không có chatgpt giải thích thì nên vào từng hàm đặt lọc để khi chạy 1 giao tiếp cơ bản có thể hình dung ra thứ tự các hàm được gọi cũng như chức năng của nó, đặt các đầy đủ log các tốt.

- ![alt text](image-221.png)

- ![alt text](image-222.png)

- ![alt text](image-223.png)

- ![alt text](image-224.png)

- ![alt text](image-225.png)

- ![alt text](image-226.png)

- ![alt text](image-227.png)

- ![alt text](image-228.png)

### 2. Quy trình  chuyển đổi USB HID Mouse thành Keyboard:

- Bước 1: Cấu hình SYS – Debug -Serial Wire. RCC – HSE – Crystal. Cấu hình GPIO Input(PA9).

![alt text](image-160.png)

![alt text](image-161.png)

![alt text](image-162.png)

Nếu cấu hình ban đầu giữ nguyên generate code ra chạy thì máy tính sẽ nhận diện là HID Mouse.

- Bước 2: Tìm chỉnh sửa trong usbd_hid.c (nó chứa tất cả các mảng descriptor và các hàn chiệu trách nhiệm truyền nhận descriptor cũng như data)

https://tapit.vn/tinh-nang-usb-hid-tren-stm32f103-ban-phim/ (report descriptor nhận diện keyboard ko được)

https://www.youtube.com/watch?v=8i2fl8YVwuI (chạy được, copy code và descriptor theo link github bên dưới)

https://github.com/TechTalkies/YouTube/tree/main/38%20STM32%20Keyboard 

![alt text](image-163.png)

– Bước 3: Tìm đến mảng USBD_HID_CfgDesc rồi thay đổi các mô tả:

>`bInterfaceSubClass`: có thể đổi (hoặc không đổi) 0x01 thành 0x00 (no boot) vì thiết bị chỉ sử dụng Report Protocol, yêu cầu driver HID đầy đủ từ hệ điều hành (OS) để hoạt động (không hỗ trợ Protocol). Và thiết bị của ta là một bàn phím tùy chỉnh, sử dụng Report Descriptor phức tạp hơn, không tương thích với Boot Protocol đơn giản. 
>
>`nInterfaceProtocol`: đổi 0x02 (Mouse) thành 0x01 (keyboard).

- Bước 4: tìm đến `HID_MOUSE_ReportDesc` đổi thành

![alt text](image-177.png)

- Bước 5: Đổi trong usbd_hid.h

![alt text](image-179.png)
![alt text](image-178.png)

> HID_EPIN_SIZE là kích thước gói dữ liệu (report size) mà thiết bị HID (Human Interface Device) gửi về host thông qua endpoint IN. Đơn vị là byte.

![alt text](image-170.png)
>![alt text](image-171.png)

>Lí do CDC và MSC không có EPIN_SiZE là vì ![alt text](image-172.png)

- Bước 6: ![alt text](image-180.png)

![alt text](image-181.png)
![alt text](image-182.png)
![alt text](image-183.png)

### 3. Quy trình chuyển đổi USB HID Keyboard thành USB Composite (HID + CDC):

Ở đây sử dụng (file USB_composite_msc_cdc cũ):

- Bước 1: Tạo file composite .c/.h riêng. Include đúng tên file

![alt text](image-184.png)

- Bước 2: Đổi tên tất cả tên hàm, mảng MSC_CDC thành HID_CDC. sau đó thêm 5 cái struct sau phần `add from User`
![alt text](image-188.png)

và sửa ![alt text](image-189.png)

- Hình như không cần sửa nên chưa sửa cái này ![alt text](image-190.png)

- Bước 3: sửa trong file usbd_desc.h
![alt text](image-191.png)

- Bước 4: Trong usbd_device.h, sửa lại
![alt text](image-192.png)
![alt text](image-193.png)

- Bước 5: thêm các file sau vào project 

![alt text](image-194.png)
![alt text](image-195.png)

- Bước 6: sửa phân vùng RAM cho endpoint trong file usbd_conf.c
![alt text](image-196.png)

**Khả năng bug** device descriptor chưa có thông báo chung cho 2 chức năng.

- Bước 7: Đổi descriptor 

![alt text](image-201.png)

```c
const uint8_t USBD_HID_CDC_CfgDesc[USB_HID_CDC_CONFIG_DESC_SIZ] =
{
#define USB_HID_CDC_CONFIG_DESC_SIZ       100

#define USBD_COMPOSITE_DESC_SIZE		100
#define USBD_IAD_DESC_SIZE 				0x08
#define USBD_IAD_DESCRIPTOR_TYPE		0x0B
#define USBD_HID_INTERFACE				0
#define USBD_CDC_CMD_INTERFACE			1
#define USBD_CDC_DATA_INTERFACE			2
//#define
//#define

/* USB MSC+CDC device Configuration Descriptor */
uint8_t USBD_HID_CDC_CfgDesc[USB_HID_CDC_CONFIG_DESC_SIZ] =
{
		  /* Configuration Descriptor */
		  0x09,   /* bLength: Configuation Descriptor size */
		  USB_DESC_TYPE_CONFIGURATION,   /* bDescriptorType: Configuration */
		  USBD_COMPOSITE_DESC_SIZE,
		  0x00,
		  USBD_MAX_NUM_INTERFACES ,  /* bNumInterfaces: */
		  0x01,   /* BCONFIGURATIONVALUE: 0 Configured value */
		  0x00,   /* iConfiguration: 00 string index */
		  0x80,   /* bmAttributes:no-bus powered and Dissupport Remote Wake-up*/
		  0x32,   /* MaxPower 100 mA  */


//		  /****************************IAD HID************************************/
//		  /* Interface Association Descriptor */
//		  USBD_IAD_DESC_SIZE,                        // BLENGTH IAD Descriptor Size
//		  USBD_IAD_DESCRIPTOR_TYPE,                  // BDescriptortype IAD Descriptor Type
//		  0x00,                                      // bfirstInterface interface descriptor is the number starting from 0 in the total configuration descriptor
//		  0x01,                                      // binterfaceCount interface descriptor quantity
//		  0x03,                                      // BDeviceClass in BFunctionClass device
//		  0x00,                                      // BDeviceSubclass in the BFunctionsUbclass device
//		  0x00,                                      // binterfaceprotocol in the BDeviceProtocol device
//		  0x00,

		  /********************  HID interface ********************/
		  /************** Descriptor of Custom HID interface ****************/
		  /* 09 */
		  0x09,                   /*bLength: Interface Descriptor size*/
		  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
		  USBD_HID_INTERFACE,     /* binterfacenumber: Number of Interface interface number 0 */
		  0x00,                   /* BalternateSetting: Alternate Setting Alternate Interface */
		  0x01,                   /* BNUMENDPOINTS number 1 */
		  0x03,                   /*bInterfaceClass: HID*/
		  0x00,                   /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
		  0x00,                   /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
		  0,                      /*iInterface: Index of string descriptor*/

		  /******************** Descriptor of Custom HID ********************/
		  /* 18 */
		  0x09,                   /*bLength: HID Descriptor size*/
		  HID_DESCRIPTOR_TYPE,    /*bDescriptorType: HID*/
		  0x00,                   /*bcdHID: HID Class Spec release number*/
		  0x01,
		  0x00,                   /*bCountryCode: Hardware target country*/
		  0x01,                   /*bNumDescriptors: Number of HID class descriptors to follow*/
		  0x22,                   /*bDescriptorType*/
		  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
		  0x00,
		  /******************** Descriptor of TouchScreen endpoint ********************/
		  /* 27 */
		  0x07,                   /*bLength: Endpoint Descriptor size*/
		  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

		  HID_EPIN_ADDR,          /*bEndpointAddress: Endpoint Address (IN)*/
		  0x03,                   /*bmAttributes: Interrupt endpoint*/
		  HID_EPIN_SIZE,          /*wMaxPacketSize: 16 Byte max */
		  0x00,
		  HID_FS_BINTERVAL,       /*bInterval: Polling Interval */
		  /* 34 */

		  /****************************CDC************************************/
		  /* IAD descriptor */
		  /* Interface Association Descriptor */
		  USBD_IAD_DESC_SIZE,               // bLength
		  USBD_IAD_DESCRIPTOR_TYPE,         // bDescriptorType
		  0x01,                             // bfirstInterface interface descriptor is the number starting from 0 in the total configuration descriptor 1
		  0x02,                             // binterfaceCount interface descriptor number 2
		  0x02,                             // bFunctionClass     CDC Control
		  0x02,                             // bFunctionSubClass  Abstract Control Model
		  0x01,                             // bInterfaceProtocol  AT Commands: V.250 etc
		  0x00,                             // iFunction

		  /* CDC command interface descriptor */
		  /*Interface Descriptor */
		  0x09,   /* BLENGTH: Interface Descriptor Size Length */
		  USB_DESC_TYPE_INTERFACE,  /* BDEScriptortype: interface number 0x04 */
		  /* Interface descriptor type */
		  USBD_CDC_CMD_INTERFACE,   /* binterfacenumber: Number of Interface interface number, first interface number 1 */
		  0x00,   /* BalternateSetting: Alternate setting interface standby number 0 */
		  0x01,   /* BNUMENDPOINTS: One Endpoints Used Number 1 Number 1 CDC interface only uses an interrupt input endpoint */
		  0x02,   /* binterfaceclass: Class 0x02 in the Communication Interface Class interface */
		  0x02,   /* binterfacesubclass: ABSTRACT Control Model interface used by subclass 0x02 */
		  0x01,   /* BinterfaceProtocol: Common At Commands Using the AT Command Protocol */
		  0x00,   /* IINTERFACE: Interface string index 0 indicates no */

		  /* Class Special Interface Descriptor - Function Descriptor Used to describe the functionality of the interface */
		  /*Header Functional Descriptor*/
		  0x05,   /* BLENGTH: Endpoint Descriptor size descriptor length is 5 bytes */
		  0x24,   /* bdescriptortype: CS_Interface Descriptor Type for class special interface CS_Interface */
		  0x00,   /* bdescriptorsubtype: Header Func Desc Sub-class is Header Func DESC, number 0x00 */
		  0x10,   /* BCDCDC: SPEC Release Number CDC version */
		  0x01,

		  /*Call Management Functional Descriptor*/
		  0x05,   /* bFunctionLength */
		  0x24,   /* bdescriptortype: CS_Interface Descriptor Type for class special interface CS_Interface */
		  0x01,   /* BDEScriptorsubtype: Call Management Func Desc Sub-class Call Management Func DESC Number 0x01 */
		  0x00,   /* BMCapabilities: D0 + D1 device yourself does not manage Call Management */
		  0x01,   /* BDataInterface: 1 has a data class interface for call management */

		  /*ACM Functional Descriptor*/
		  0x04,   /* bFunctionLength */
		  0x24,   /* bdescriptortype: CS_Interface Descriptor Type for class special interface CS_Interface */
		  0x02,   /* bdescriptorsubtype: Abstract Control Management Desc Subclass is Abstract Control Management DESC Number 0x02 */
		  0x02,   /* BMCapabilities Support SET_CONTROL_LINE_STATE, GET_LINE_CODING Request and Serial_State Notifications */

		  /*Union Functional Descriptor*/
		  0x05,   /* bFunctionLength */
		  0x24,   /* bdescriptortype: CS_Interface Descriptor Type for class special interface CS_Interface */
		  0x06,   /* bdescriptorsubtype: UNION FUNC DESC sub-class is UNION FUNC DESC number 0x06 */
		  USBD_CDC_CMD_INTERFACE,    /* BMasterInterface: CMMUNICATION CLASS interface number 1 CDC interface */
		  USBD_CDC_DATA_INTERFACE,   /* BSLAVEINTERFACE0: Data Class Interface Number 2 Data Class Interface */

		  /*Endpoint 2 Descriptor*/
		  0x07,                           /* bLength: Endpoint Descriptor size */
		  USB_DESC_TYPE_ENDPOINT,   			/* bDescriptorType: Endpoint */
		  CDC_CMD_EP,                     /* bEndpointAddress */
		  0x03,                           /* bmAttributes: Interrupt */
		  LOBYTE(CDC_CMD_PACKET_SIZE),    /* wMaxPacketSize: */
		  HIBYTE(CDC_CMD_PACKET_SIZE),
		  CDC_FS_BINTERVAL,                           /* bInterval: */
		  /*---------------------------------------------------------------------------*/

			/* Interface descriptor */
		  /*Data class interface descriptor*/
		  0x09,   /* BLENGTH: Endpoint Descriptor Size Interface Descriptor Length 9 byte */
		  USB_DESC_TYPE_INTERFACE,  /* bdescriptortype: number 0x04 with interface descriptor */
		  USBD_CDC_DATA_INTERFACE,   /* binterfacenumber: Number of interface interface number 2 */
		  0x00,   /* BalternateSetting: Alternate setting This interface is 0 */
		  0x02,   /* BNUMENDPOINTS: TWO Endpoints Used Non 0 End Point Data Device You need to use a pair of batch endpoints, set to 2 */
		  0x0A,   /* binterfaceClass: CDC The class data class interface code used by this interface is 0x0a */
		  0x00,   /* binterfaceSubclass: The subcaters used by the interface are 0 */
		  0x00,   /* binterfaceProtocol: The protocol used by the interface is 0 */
		  0x00,   /* IINTERFACE: The character string of the interface, 0 means no */

			/* Endpoint descriptor of the output endpoint */
		  /*Endpoint OUT Descriptor*/
		  0x07,   /* BLENGTH: Endpoint Descriptor Size Endpoint Descriptor Length 7 bytes */
		  USB_DESC_TYPE_ENDPOINT,               /* bdescriptortype: Endpoint endpoint descriptor number is 0x05 */
		  CDC_OUT_EP,                           /* BenPointAddress endpoint address 0x02 D7 is the direction */
		  0x02,                                 /* BMAttributes: Bulk Batch Transfer */
		  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),  /* WMAXPACKETSIZE: Endpoint's maximum package length 512 bytes */
		  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
		  0x00,                                 /* Binterval: Ignore for Bulk Transfer endpoint query time, invalid for batch endpoints */

			/* Endpoint descriptor of the input end point */
		  /*Endpoint IN Descriptor*/
		  0x07,   /* bLength: Endpoint Descriptor size */
		  USB_DESC_TYPE_ENDPOINT,               /* bdescriptortype: Endpoint endpoint descriptor number is 0x05 */
		  CDC_IN_EP,                            /* BenPointAddress endpoint address 0x82 D7 is the direction */
		  0x02,                                 /* BMAttributes: Bulk Batch Transfer */
		  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),  /* WMAXPACKETSIZE: Endpoint's maximum package length 512 bytes */
		  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
		  0x00                                  /* Binterval: Ignore for Bulk Transfer endpoint query time, invalid for batch endpoints */

};
};

```

- Bước 8: trong file usbd_desc.c, sửa:

![alt text](image-197.png)

![alt text](image-198.png)

- Bước 9: trong file usbd_conf.h sửa
![alt text](image-199.png)
![alt text](image-200.png)

- Bước 10: sửa thêm HID report(cái này là đặc điểm riêng của loại class này mà CDC và MSC không có )

![alt text](image-203.png)

**Tự sửa thêm vì những cái trên chỉ mới vừa giúp nhân diện thôi**

- Bước 1: từ HS thành FS 2 chỗ như này ![alt text](image-202.png)

- Bước 2: Comment toàn bộ `typedef struct` trong usbd_def.h ![alt text](image-204.png), vào file usb_composite_hid_cdc.h tạo typdef struct này ![alt text](image-205.png) với tên struct y chang _USBD_HandleTypedef(vì nó có được đi nghĩa nên không sửa tên được), đồng thời include usbd_def.h vào file này, lúc này tất cả những file nào cần include usbd_def.h ta có thể thay bằng file usb_composite_hid_cdc.h, sửa tất cả các hàm Init, setup,tran/receive,... và tất cả các file trong USB với tham số truyền vào là `USBD_HandleTypeDef` thành `USBD_Composite_HandleTypeDef` hết.

- Bước 3: chuyển đống này từ class cdc và hid qua file usb_composite_hid_cdc.h để tránh bị lỗi

- Bước 4: sửa nốt cái này biến toàn cục này ![alt text](image-206.png) trong usb_device.c và trong file main.c

- Bước 5: Sửa nội dung trong các hàm của các class riêng được generate ra vì lúc này ta đã dùng truyền nhận vào các field mới thêm vào trong struct 
`USBD_Composite_HandleTypeDef`

- Bước 6: Sửa lại cái này trong hàm này của usbd_cdc_if.c

![alt text](image-217.png)
![alt text](image-216.png)

- Đã tự sửa HID các hàm Init/datain/setup,.... giống như CDC mà copy từ code tác giả, chủ yếu là như này ![alt text](image-212.png) và như này![alt text](image-213.png)
![alt text](image-215.png)
![alt text](image-214.png)
>Các hàm như USBD_DataOutStage() và USBD_DataInStage() chính là cầu nối giữa phần điều khiển cấp thanh ghi (hardware) và stack cấp cao (class như CDC, HID, MSC...).
![alt text](image-207.png)
![alt text](image-208.png)
![alt text](image-209.png)
![alt text](image-210.png)


**Tài liệu tham khảo:**

- Tài liệu tham khảo USB joystick: https://wiki.osdev.org/USB_Human_Interface_Devices

- Tài liệu bảng mã kí tự trên USB HID Keyboard: https://d1.amobbs.com/bbs_upload782111/files_47/ourdev_692986N5FAHU.pdf 

- Tài liệu USB HID chuột máy tính: https://tapit.vn/tinh-nang-usb-hid-tren-stm32f103-chuot-may-tinh/

- Link git tham khảo device descriptor: https://github.com/Ludovictor/STM32-USB-Composite-HID-CDC/tree/main
