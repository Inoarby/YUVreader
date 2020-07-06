#include "stdafx.h"
#include "YUVreader.h"
#include <stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{

	char* FILE_NAME		= "..\\..\\BasketballDrill_832x480_50.yuv";
	char* write_file	= "..\\..\\wirte_test_832x480_50.yuv";
	int WIDTH			= 832;
	int HEIGHT			= 480;
	int FRAME_NUM		= 500;
	char* FORMAT		= "i420";

	YUV_FILE* yuv_file = YUVopen(FILE_NAME, WIDTH, HEIGHT, FORMAT);
	YUV_FRAME* yuv_frame = create_frame(yuv_file);

	FILE* wfp = fopen(write_file, "wb");
	while (yuv_file->frame_count <= FRAME_NUM){
		printf("Writing frame %d. \n", yuv_file->frame_count);
		YUVread_frame(yuv_frame);
		YUVwrite_frame(yuv_frame, wfp);
	}

	fclose(wfp);
	deconstruct_frame(yuv_frame);
	YUVclose(yuv_file);
	return 0;
}
