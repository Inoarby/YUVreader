#include "stdafx.h"
#include "YUVreader.h"


YUV_FILE* YUVopen(const char* file_name, int width, int height, const char* format){

	YUV_FILE* yuv_file = (YUV_FILE*) malloc(sizeof(YUV_FILE));
	if (yuv_file == NULL) return 0;

	yuv_file->frame_count	= 0;
	yuv_file->width			= width;
	yuv_file->height		= height;
	yuv_file->FILE_NAME		= (char*)malloc(sizeof(char) * 528);
	yuv_file->FORMAT		= (char*)malloc(sizeof(char) * 16);
	strcpy(yuv_file->FILE_NAME, file_name);
	strcpy(yuv_file->FORMAT, format);

	yuv_file->fp			= fopen(file_name, "rb"); // Consider checking fp validity here.

	return(yuv_file);
}

YUV_FRAME* create_frame(YUV_FILE* yuv_file){

	YUV_FRAME* frame = (YUV_FRAME*)malloc(sizeof(YUV_FRAME));

	int res = yuv_file->width * yuv_file->height;
	frame->yuv_file = yuv_file;
	frame->y_comp = (Y_COMP*)malloc(sizeof(Y_COMP) * res);
	frame->u_comp = (U_COMP*)malloc(sizeof(U_COMP) * (int)(res / 4));
	frame->v_comp = (V_COMP*)malloc(sizeof(V_COMP) * (int)(res / 4));

	return(frame);
}

int deconstruct_frame(YUV_FRAME* frame){

	free(frame->y_comp);
	free(frame->u_comp);
	free(frame->v_comp);

	free(frame);
	return(0);
}

int YUVclose(YUV_FILE* yuv_file){

	int i = fclose(yuv_file->fp);
	free(yuv_file);

	if (i == EOF) return(-1);
	return(0);

}


int YUVread_frame(YUV_FRAME* yuv_frame){

	YUV_FILE* yuv_file = yuv_frame->yuv_file;
	int luma_res, chroma_res;
	size_t pixel_depth;

	if (!strcmp(yuv_file->FORMAT, "i420")){
		luma_res = yuv_file->width * yuv_file->height;
		chroma_res = (int)(luma_res / 4);	// What if resolution does not devide 4?
		pixel_depth = sizeof(Y_COMP);
	}

	//yuv_frame->yuv_file = yuv_file;
	yuv_frame->frame_count = yuv_file->frame_count;
	size_t noy = fread(yuv_frame->y_comp, pixel_depth, luma_res, yuv_file->fp);
	size_t nou = fread(yuv_frame->u_comp, pixel_depth, chroma_res, yuv_file->fp);
	size_t nov = fread(yuv_frame->v_comp, pixel_depth, chroma_res, yuv_file->fp);

	// Consider checking read validity here.
	//if () return();
	yuv_file->frame_count += 1;

	return 0;
}


int YUVwrite_frame(const YUV_FRAME* yuv_frame, FILE* fp){

	const YUV_FILE* yuv_file = yuv_frame->yuv_file;
	int luma_res, chroma_res;
	size_t pixel_depth;

	if (!strcmp(yuv_file->FORMAT, "i420")){

		luma_res = yuv_file->width * yuv_file->height;
		chroma_res = (int)(luma_res / 4);
		pixel_depth = sizeof(Y_COMP);		// Why Y_COMP?
	}

	size_t noy = fwrite(yuv_frame->y_comp, pixel_depth, luma_res, fp);
	size_t nou = fwrite(yuv_frame->u_comp, pixel_depth, chroma_res, fp);
	size_t nov = fwrite(yuv_frame->v_comp, pixel_depth, chroma_res, fp);

	return(0);
}


int YUVseek_frame(int frame_count, YUV_FILE* yuv_file);
int YUVtell_frame(YUV_FILE* yuv_file);



