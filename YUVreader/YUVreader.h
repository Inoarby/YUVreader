#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

	char* FILE_NAME;
	char* FORMAT;
	
	int frame_count;
	int width, height;
	FILE* fp;

} YUV_FILE;

/* Open YUV file and set the corresponding parameters. */
YUV_FILE* YUVopen(const char* file_name, int width, int height, const char* format);

/* Close yuv file and free structure. */
int YUVclose(YUV_FILE* yuv_file);

/* Read one frame from yuv_file, store y, u and v components separately. */
int YUVread_frame(uint8_t* y_comp, uint8_t* u_comp, uint8_t* v_comp, YUV_FILE* yuv_file);

/* Write y, u and v components into fp. */
int YUVwrite_frame(const uint8_t* y_comp, const uint8_t* u_comp, const uint8_t* v_comp, 
				   const YUV_FILE* yuv_file, FILE* fp);

// To-Do
/* Seek frame number to frame_count if it's valid. */
int YUVseek_frame(int frame_count, YUV_FILE* yuv_file);

/* Return frame_count. */
int YUVtell_frame(YUV_FILE* yuv_file);
