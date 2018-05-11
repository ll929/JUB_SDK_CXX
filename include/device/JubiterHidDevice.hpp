#ifndef __JubiterHidDevice__
#define __JubiterHidDevice__

#ifdef _WIN32

#include <hidapi/hidapi/hidapi.h>
#include <device/DeviceTypeBase.hpp>

namespace jub {

// typedef struct HID_3KHN_PACK {
// //
// #if defined(_WIN32)
//     unsigned char id;
// #endif
//     unsigned char uc0PacketSizeH;   //  数据包长度-高字节
//     unsigned char uc1PacketSizeL;   //  数据包长度-低字节
//                                     //
//     unsigned char uc2BlockOffsetH;  //  数据块偏移-高字节
//     unsigned char uc3BlockOffsetL;  //  数据块偏移-低字节
//                                     //
//     unsigned char uc4BlockSizeH;    //  数据块长度-高字节
//     unsigned char uc5BlockSizeL;    //  数据块长度-低字节
//                                     //
//     unsigned char uc6Buffer[58];    //  存放数据块。
// } HID_3KHN_PACK;
// 
// //在windows系统上用hidapi，发送的时候需要补id共65个字节，收的时候没有，是64个字节
// typedef struct HID_3KHN_PACK_READ_64 {
//     unsigned char uc0PacketSizeH;   //  数据包长度-高字节
//     unsigned char uc1PacketSizeL;   //  数据包长度-低字节
//                                     //
//     unsigned char uc2BlockOffsetH;  //  数据块偏移-高字节
//     unsigned char uc3BlockOffsetL;  //  数据块偏移-低字节
//                                     //
//     unsigned char uc4BlockSizeH;    //  数据块长度-高字节
//     unsigned char uc5BlockSizeL;    //  数据块长度-低字节
//                                     //
//     unsigned char uc6Buffer[58];    //  存放数据块。
// } HID_3KHN_PACK_READ_64;
// #define BUFSIZE 4096
// #define DATA_ONCE_LEN 255
// #define FT3KHN_MAX_REPORT_COUNT 200


#define VID 0x096e
#define PID 0x0603

#define HID_PACKET_SIZE 65
#define HID_PACKET_HEAD_FRIST 8
#define HID_PACKET_HEAD_ROUND 6

#define HID_PACKET_RHEAD_FRIST 7
#define HID_PACKET_RHEAD_ROUND 5


#define HID_PACKET_GNU_SIZE 64

class JubiterHidDevice : public DeviceTypeBase {
   public:
    JubiterHidDevice();
    ~JubiterHidDevice();

   public:
    virtual JUB_RV connect(const std::string path);
    virtual JUB_RV disconnect();

    virtual JUB_RV sendData(IN JUB_BYTE_CPTR sendData, IN JUB_ULONG sendLen,
                            OUT JUB_BYTE_PTR pRetData,
                            INOUT JUB_ULONG_PTR pulRetLen,
                            IN JUB_ULONG ulMiliSecondTimeout = 1200000);

   protected:
	int write(const unsigned char *data, size_t length);
	int read(unsigned char *data, size_t length);

   protected:
    hid_device* m_handle;
    unsigned short vid;
    unsigned short pid;
	std::string _path;
	bool firstCmd;
};

}
#endif // #ifdef _WIN32
#endif  // __JubiterHidDevice__
