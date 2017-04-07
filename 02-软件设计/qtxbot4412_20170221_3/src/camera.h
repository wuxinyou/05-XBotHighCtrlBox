#ifndef CAMERA_H
#define CAMERA_H

#include <sys/types.h>

#define CLEAR(x) memset (&(x), 0, sizeof (x))
typedef enum {
    IO_METHOD_READ, IO_METHOD_MMAP, IO_METHOD_USERPTR,
} io_method;
struct buffer {
    void * start;
    size_t length;//buffer's length is different from cap_image_size
};

class Camera
{
public:
    Camera(char *DEV_NAME,int w,int h, int camer_type);
    ~Camera();
    bool OpenDevice();//打开设备
    void CloseDevice();
    bool GetBuffer(unsigned char *image);//获取数据流
    unsigned int getImageSize();

private:
    char dev_name[50];
    io_method io;
    int fd;
    int width;
    int height;
    struct buffer * buffers ;
    unsigned int n_buffers ;
    unsigned int cap_image_size ;//to keep the real image size!!

    bool init_device(void);
    //void init_read(unsigned int buffer_size);
    bool init_mmap(void);
    //void init_userp(unsigned int buffer_size);
    void uninit_device(void);
    bool start_capturing(void);
    void stop_capturing(void);
    void mainloop(unsigned char *image);
    int read_frame(unsigned char *image);
    void close_device(void);
    bool open_device(void);
    bool process_image(unsigned char *image,const void * p);

    void errno_exit(const char * s);
    int xioctl(int fd, int request, void * arg);
};

#endif // CAMERA_H

