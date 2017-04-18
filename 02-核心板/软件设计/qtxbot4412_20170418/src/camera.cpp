#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>             /* getopt_long() */
#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>          /* for videodev2.h */
#include <linux/videodev2.h>
#include "camera.h"

int c_camera_type = 0;

Camera::Camera(char *DEV_NAME, int w, int h, int camera_type)
{
	//将dev_name数组初始化，否则在dev_name末尾可能出现不为0的情况
	for(int i=0;i<50;i++)
	{
		dev_name[i]=0;
	}
	
    memcpy(dev_name,DEV_NAME,strlen(DEV_NAME));
	printf("************** %s, line = %d,dev_name=%S,strlen(DEV_NAME)=%d\n", __FUNCTION__, __LINE__,dev_name,strlen(DEV_NAME));
	
    io = IO_METHOD_MMAP;//IO_METHOD_READ;//IO_METHOD_MMAP;
    cap_image_size=0;
    width=w;
    height=h;

	if(1 == camera_type)
	{
		c_camera_type = 1;
	}
}

Camera::~Camera(){

}

unsigned int Camera::getImageSize(){
    return cap_image_size;
}

void Camera::CloseDevice() {
    stop_capturing();
    uninit_device();
    close_device();
}

void Camera::errno_exit(const char * s) {
    fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
    exit(EXIT_FAILURE);
}

int Camera::xioctl(int fd, int request, void * arg) {
    int r;
    do
        r = ioctl(fd, request, arg);
    while (-1 == r && EINTR == errno);
    return r;
}

int Camera::read_frame(unsigned char *image) {
    struct v4l2_buffer buf;

    CLEAR (buf);
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
        switch (errno) {
        case EAGAIN:
		printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
            return 0;
        case EIO:
		printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
            /* Could ignore EIO, see spec. */
            /* fall through */
        default:
		printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
            errno_exit("VIDIOC_DQBUF");
        }
    }
	//printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
    assert(buf.index < n_buffers);
	//printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
    memcpy(image,buffers[0].start,cap_image_size);
    if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
        errno_exit("VIDIOC_QBUF");

    return 1;
}
void Camera::stop_capturing(void) {
    enum v4l2_buf_type type;
    switch (io) {
    case IO_METHOD_READ:
        /* Nothing to do. */
        break;
    case IO_METHOD_MMAP:
    case IO_METHOD_USERPTR:
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
            errno_exit("VIDIOC_STREAMOFF");
        break;
    }
}
bool Camera::start_capturing(void) {
    unsigned int i;
    enum v4l2_buf_type type;
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
    for (i = 0; i < n_buffers; ++i) {
        struct v4l2_buffer buf;
        CLEAR (buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
	{
		printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
            return false;
	}
    }
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
    {
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
        return false;
     }
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
    return true;
}
void Camera::uninit_device(void) {
    unsigned int i;
    switch (io) {
    case IO_METHOD_READ:
        free(buffers[0].start);
        break;
    case IO_METHOD_MMAP:
        for (i = 0; i < n_buffers; ++i)
            if (-1 == munmap(buffers[i].start, buffers[i].length))
                errno_exit("munmap");
        break;
    case IO_METHOD_USERPTR:
        for (i = 0; i < n_buffers; ++i)
            free(buffers[i].start);
        break;
    }
    free(buffers);
}

bool Camera::init_mmap(void) {
    struct v4l2_requestbuffers req;
    CLEAR (req);
    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s does not support "
                    "memory mapping\n", dev_name);
            return false;
        } else {
            return false;
        }
    }
    if (req.count < 2) {
        fprintf(stderr, "Insufficient buffer memory on %s\n", dev_name);
        return false;
    }
    buffers = (buffer*)calloc(req.count, sizeof(*buffers));
    if (!buffers) {
        fprintf(stderr, "Out of memory\n");
        return false;
    }
    for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
        struct v4l2_buffer buf;
        CLEAR (buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;
        if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
            errno_exit("VIDIOC_QUERYBUF");
        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start = mmap(NULL /* start anywhere */, buf.length,
                                        PROT_READ | PROT_WRITE /* required */,
                                        MAP_SHARED /* recommended */, fd, buf.m.offset);
        if (MAP_FAILED == buffers[n_buffers].start)
            return false;
    }
    return true;
}

bool Camera::init_device(void) {
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    unsigned int min;
    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) {
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
        if (EINVAL == errno) {
            fprintf(stderr, "%s is no V4L2 device\n", dev_name);
            return false;
        } else {
            return false;
        }
    }
    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
        fprintf(stderr, "%s is no video capture device\n", dev_name);
        return false;
    }
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
    switch (io) {
    case IO_METHOD_READ:
        if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
		printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
            fprintf(stderr, "%s does not support read i/o\n", dev_name);
            return false;
        }
        break;
    case IO_METHOD_MMAP:
    case IO_METHOD_USERPTR:
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
        if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
		printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
            fprintf(stderr, "%s does not support streaming i/o\n", dev_name);
            return false;
        }
        break;
    }

    v4l2_input input;
    memset(&input, 0, sizeof(struct v4l2_input));
    input.index = 0;
    int rtn = ioctl(fd, VIDIOC_S_INPUT, &input);
    if (rtn < 0) {
        printf("VIDIOC_S_INPUT:rtn(%d)\n", rtn);
        return false;
    }
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
    printf("-#-#-#-#-#-#-#-#-#-#-#-#-#-\n");
    printf("\n");
    ////////////crop finished!
    //////////set the format
    CLEAR (fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
    //V4L2_PIX_FMT_YVU420, V4L2_PIX_FMT_YUV420 — Planar formats with 1/2 horizontal and vertical chroma resolution, also known as YUV 4:2:0
    //V4L2_PIX_FMT_YUYV — Packed format with 1/2 horizontal chroma resolution, also known as YUV 4:2:2
    fmt.fmt.pix.pixelformat =V4L2_PIX_FMT_YUV420;// V4L2_PIX_FMT_NV12;//V4L2_PIX_FMT_YUYV;//V4L2_PIX_FMT_YUV420;//V4L2_PIX_FMT_YUYV;
	//fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    //fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
    {
        printf("-#-#-#-#-#-#-#-#-#-#-#-#-#-\n");
        printf("=====will set fmt to (%d, %d)--", fmt.fmt.pix.width,
               fmt.fmt.pix.height);
        if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV) {
            printf("V4L2_PIX_FMT_YUYV\n");
        } else if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUV420) {
            printf("V4L2_PIX_FMT_YUV420\n");
        } else if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_NV12) {
            printf("V4L2_PIX_FMT_NV12\n");
        }
    }
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);

	printf("************** %s, line = %d(camera_type = %d)\n", __FUNCTION__, __LINE__, c_camera_type);

    if(c_camera_type == 0)
    {
    	if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
    	{
		printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
        	return false;
     	}
     }

#if 1
    if(c_camera_type == 0)
    {
    	fmt.type = V4L2_BUF_TYPE_PRIVATE;
    	if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
    	{
        	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
        	return false;
     	}
    }
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
#endif
	// CLEAR (fmt);
#if 1
    if (-1 == xioctl(fd, VIDIOC_G_FMT, &fmt))
    {
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
        return false;
     }
#endif
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
    printf("=====after set fmt\n");
    printf("    fmt.fmt.pix.width = %d\n", fmt.fmt.pix.width);
    printf("    fmt.fmt.pix.height = %d\n", fmt.fmt.pix.height);
    printf("    fmt.fmt.pix.sizeimage = %d\n", fmt.fmt.pix.sizeimage);
    cap_image_size = fmt.fmt.pix.sizeimage;
    printf("    fmt.fmt.pix.bytesperline = %d\n", fmt.fmt.pix.bytesperline);
    printf("-#-#-#-#-#-#-#-#-#-#-#-#-#-\n");
    printf("\n");


    /* Note VIDIOC_S_FMT may change width and height. */
    printf("-#-#-#-#-#-#-#-#-#-#-#-#-#-\n");
    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = (unsigned int)width*height*3/2;
    printf("min:%d\n",min);
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;
    cap_image_size = fmt.fmt.pix.sizeimage;
    printf("After Buggy driver paranoia\n");
    printf("    >>fmt.fmt.pix.sizeimage = %d\n", fmt.fmt.pix.sizeimage);
    printf("    >>fmt.fmt.pix.bytesperline = %d\n", fmt.fmt.pix.bytesperline);
    printf("-#-#-#-#-#-#-#-#-#-#-#-#-#-\n");
    printf("\n");

    init_mmap();

    return true;
}
void Camera::close_device(void) {
    if (-1 == close(fd))
        errno_exit("close");
    fd = -1;
}
bool Camera::open_device(void) {
    struct stat st;
    if (-1 == stat(dev_name, &st)) {
        fprintf(stderr, "Cannot identify '%s': %d, %s\n", dev_name, errno,
                strerror(errno));
        return false;
    }
    if (!S_ISCHR(st.st_mode)) {
        fprintf(stderr, "%s is no device\n", dev_name);
        return false;
    }
    fd = open(dev_name, O_RDWR /* required */| O_NONBLOCK, 0);
    if (-1 == fd) {
        fprintf(stderr, "Cannot open '%s': %d, %s\n", dev_name, errno,
                strerror(errno));
        return false;
    }
    return true;
}

bool Camera::OpenDevice(){
    if (open_device()) {
        printf("open success\n");
        if (init_device()) {
		printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
            if (start_capturing())
		printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
                return true;
        }
	else
	{
		printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
	}
    } else
        printf("open failed\n");

	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
    return false;
}

bool Camera::GetBuffer(unsigned char *image){
    fd_set fds;
    struct timeval tv;
    int r;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    /* Timeout. */
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    r = select(fd + 1, &fds, NULL, NULL, &tv);
    if (-1 == r) {
        errno_exit("select");
    }
    if (0 == r) {
	printf("************** %s, line = %d\n", __FUNCTION__, __LINE__);
        fprintf(stderr, "select timeout\n");
        exit(EXIT_FAILURE);
    }
    read_frame(image);
}

