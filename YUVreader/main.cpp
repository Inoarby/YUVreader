#include "stdafx.h"
#include "YUVreader.h"
#include <stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{

	char* FILE_NAME		= "..\\BasketballDrill_832x480_50.yuv";
	char* write_file	= "..\\wirte_test_832x480_50.yuv";
	int WIDTH			= 832;
	int HEIGHT			= 480;
	int FRAME_NUM		= 500;
	char* FORMAT		= "i420";

	uint8_t* y_comp = (uint8_t*)malloc(sizeof(uint8_t) * WIDTH * HEIGHT);
	uint8_t* u_comp = (uint8_t*)malloc(sizeof(uint8_t)* (int)(WIDTH * HEIGHT / 4));
	uint8_t* v_comp = (uint8_t*)malloc(sizeof(uint8_t)* (int)(WIDTH * HEIGHT / 4));

	YUV_FILE* yuv_file = YUVopen(FILE_NAME, WIDTH, HEIGHT, FORMAT);

	FILE* wfp = fopen(write_file, "wb");
	while (yuv_file->frame_count <= FRAME_NUM){
		printf("Writing frame %d. \n", yuv_file->frame_count);
		YUVread_frame(y_comp, u_comp, v_comp, yuv_file);
		YUVwrite_frame(y_comp, u_comp, v_comp, yuv_file, wfp);
	}

	fclose(wfp);
	YUVclose(yuv_file);
	return 0;
}


