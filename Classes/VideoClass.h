#pragma once
#include "Tools.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include <libavutil/parseutils.h>
#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
}
typedef struct _OutputStream
{
	AVStream* st;
	AVFrame* videoFrame;
	AVFrame* audioFrame;

	int64_t next_pts;
	float t, tincr,tinct2;
	struct SwsContext* sws_ctx;
	struct SwrContext* swr_ctx;
}OutputStream;

class VideoClass :public CCLayer
{
public:
	CCTexture2D* m_pTexture;
	CCSprite* m_pSprite;
	bool m_IsPlayOver;
	bool m_IsRecord;
	float m_Width;
	float m_Height;
	vector<unsigned char*> m_VideoList;
	int m_VideoIndex;

	char outFilePath[32];
	AVFrame* m_pRGBFrame;  //RGB帧数据      
	AVFrame* m_pYUVFrame;  //YUV帧数据  
	static SwsContext* pSwsCtx;
	int m_BitRate;
public:
	VideoClass(void);
	virtual ~VideoClass(void);
	void ShowVideo();
	void ReSetVideo();

	void SaveVideo();
	void Add_audio_viode_stream(OutputStream* viode_st, OutputStream* audio_st, AVFormatContext* oc, AVCodec* video_encoder, AVCodec* audio_encoder);
	void fill_yuv_image(int imageInx);
};

