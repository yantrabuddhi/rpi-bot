#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <string.h> // strerrno
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/*
 gcc -o web v4l2-webcam.c `pkg-config --cflags --libs sdl` -lSDL_image
 */

int main(void){
    int fd;//video0
    if((fd = open("/dev/video1", O_RDWR)) < 0){
        perror("open");
        exit(1);
    }

    // ...
struct v4l2_capability cap;
if(ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0){
    perror("VIDIOC_QUERYCAP");
    exit(1);
}

if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)){
    fprintf(stderr, "The device does not handle single-planar video capture.\n");
    exit(1);
}
struct v4l2_format format;
format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
format.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
format.fmt.pix.width = 800;
format.fmt.pix.height = 600;
 
if(ioctl(fd, VIDIOC_S_FMT, &format) < 0){
    perror("VIDIOC_S_FMT");
    exit(1);
}
struct v4l2_requestbuffers bufrequest;
bufrequest.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
bufrequest.memory = V4L2_MEMORY_MMAP;
bufrequest.count = 1;
 
if(ioctl(fd, VIDIOC_REQBUFS, &bufrequest) < 0){
    perror("VIDIOC_REQBUFS");
    exit(1);
}
struct v4l2_buffer bufferinfo;
memset(&bufferinfo, 0, sizeof(bufferinfo));
 
bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
bufferinfo.memory = V4L2_MEMORY_MMAP;
bufferinfo.index = 0;
 
if(ioctl(fd, VIDIOC_QUERYBUF, &bufferinfo) < 0){
    perror("VIDIOC_QUERYBUF");
    exit(1);
}

void* buffer_start = mmap(
    NULL,
    bufferinfo.length,
    PROT_READ | PROT_WRITE,
    MAP_SHARED,
    fd,
    bufferinfo.m.offset
);
 
if(buffer_start == MAP_FAILED){
    perror("mmap");
    exit(1);
}
 
memset(buffer_start, 0, bufferinfo.length);

//////
/*
struct v4l2_buffer bufferinfo;

memset(&bufferinfo, 0, sizeof(bufferinfo));
bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
bufferinfo.memory = V4L2_MEMORY_MMAP;
bufferinfo.index = 0; /* Queueing buffer index 0. */

// Put the buffer in the incoming queue.
if(ioctl(fd, VIDIOC_QBUF, &bufferinfo) < 0){
    perror("VIDIOC_QBUF");
    exit(1);
}

// Activate streaming
int type = bufferinfo.type;
if(ioctl(fd, VIDIOC_STREAMON, &type) < 0){
    perror("VIDIOC_STREAMON");
    exit(1);
}

SDL_Init(SDL_INIT_VIDEO);
IMG_Init(IMG_INIT_JPG);
 
// Get the screen's surface.
SDL_Surface* screen = SDL_SetVideoMode(
    format.fmt.pix.width,
    format.fmt.pix.height,
    32, SDL_HWSURFACE
);
 
SDL_RWops* buffer_stream;
SDL_Surface* frame;
SDL_Rect position = {.x = 0, .y = 0};
 int cc=0;
while(cc<30*10){
	cc++;
    // Dequeue the buffer.
    if(ioctl(fd, VIDIOC_DQBUF, &bufferinfo) < 0){
        perror("VIDIOC_QBUF");
        exit(1);
    }

    bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufferinfo.memory = V4L2_MEMORY_MMAP;
    /* Set the index if using several buffers */
// Create a stream based on our buffer.
buffer_stream = SDL_RWFromMem(buffer_start, bufferinfo.length);
 
// Create a surface using the data coming out of the above stream.
frame = IMG_Load_RW(buffer_stream, 0);
 
// Blit the surface and flip the screen.
SDL_BlitSurface(frame, NULL, screen, &position);
SDL_Flip(screen);
 
// Free everything, and unload SDL & Co.
SDL_FreeSurface(frame);
SDL_RWclose(buffer_stream);
    // Queue the next one.
    if(ioctl(fd, VIDIOC_QBUF, &bufferinfo) < 0){
        perror("VIDIOC_QBUF");
        exit(1);
    }
}
IMG_Quit();
SDL_Quit();
// Deactivate streaming
if(ioctl(fd, VIDIOC_STREAMOFF, &type) < 0){
    perror("VIDIOC_STREAMOFF");
    exit(1);
}
//////

    close(fd);
    return EXIT_SUCCESS;
}
