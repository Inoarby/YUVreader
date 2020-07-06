#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t Y_COMP;
typedef uint8_t U_COMP;
typedef uint8_t V_COMP;

typedef struct {

	char* FILE_NAME;
	char* FORMAT;
	
	int frame_count;
	int width, height;
	FILE* fp;

} YUV_FILE;

typedef struct {

	YUV_FILE* yuv_file;

	int frame_count;
	Y_COMP* y_comp;
	U_COMP* u_comp;
	V_COMP* v_comp;

} YUV_FRAME;

/* Open YUV file and set the corresponding parameters. */
YUV_FILE* YUVopen(const char* file_name, int width, int height, const char* format);

/* Construct a yuv frame struct to store a frame. */
YUV_FRAME* create_frame(YUV_FILE* yuv_file);

/* Frame deconstruction. */
int deconstruct_frame(YUV_FRAME* frame);

/* Close yuv file and free structure. */
int YUVclose(YUV_FILE* yuv_file);

/* Read one frame from yuv_file, store y, u and v components separately. */
int YUVread_frame(YUV_FRAME* yuv_frame);

/* Write yuv_frame into fp. */
int YUVwrite_frame(const YUV_FRAME* yuv_frame, FILE* fp);

// To-Do
/* Seek frame number to frame_count if it's valid. */
int YUVseek_frame(int frame_count, YUV_FILE* yuv_file);

/* Return frame_count. */
int YUVtell_frame(YUV_FILE* yuv_file);
