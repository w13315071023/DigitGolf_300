#include "DemoVideoLayer.h"
#include "PostureAnalysisScene.h"
#include "DataMager.h"

DemoVideoLayer* DemoVideoLayer::create(int Direction)
{
	DemoVideoLayer *pRet = new DemoVideoLayer();
	if (pRet && pRet->init(Direction))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
DemoVideoLayer::DemoVideoLayer()
{
}

DemoVideoLayer::~DemoVideoLayer()
{
	if (!m_VideoList.empty())
	{
		for (int i = 0;i < m_VideoList.size(); i++)
		{
			av_free(m_VideoList[i]);
		}
		m_VideoIndex = 0;
	}
}
bool DemoVideoLayer::init(int Direction)
{
	if (!CCLayer::init())
	{
		return false;
	}
	printf("³õÊ¼»¯DemoVideoLayer\n");
	videoStream = -1;
	pCodecCtx = NULL;
	pFormatCtx = NULL;
	packet = AVPacket();
	m_BitRate = 400000;
	m_Direction = Direction;
	sprintf(outFilePath,
		SELFVIDEO,
		DataMager::shareDataMager()->m_curGender,
		DataMager::shareDataMager()->m_curCuetype,
		Direction);
	filename = new char[64];
	if(Ext_IsDemoVideo)
	{
		sprintf(filename,
			DEMOVIDEO,
			DataMager::shareDataMager()->m_curGender,
			DataMager::shareDataMager()->m_curCuetype,
			Direction);
	}
	else
	{
		sprintf(filename,
			SELFVIDEO,
			DataMager::shareDataMager()->m_curGender,
			DataMager::shareDataMager()->m_curCuetype,
			Direction);
	}
	this->LoadVideo();
	this->ShowVideo();
	CCSprite* beijing2 = CCSprite::create("VideoUI/beijing2.png");
	beijing2->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));
	this->addChild(beijing2);
	m_pSprite->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));
	this->addChild(m_pSprite);

	this->setRotationX(180);
	return true;
}
bool DemoVideoLayer::LoadVideo()
{
	av_register_all();

	if (avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0)
	{
		sprintf(filename,
		DEMOVIDEO,
		DataMager::shareDataMager()->m_curGender,
		DataMager::shareDataMager()->m_curCuetype,
		m_Direction);
		if(avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0)
		{
			CCLog("open");
			return false;
		}
	}
	if (avformat_find_stream_info(pFormatCtx, 0) < 0)
	{
		CCLog("find");
		return false;
	}

	for (int i = 0; i < pFormatCtx->nb_streams; i++)
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
			break;
		}
	if (videoStream == -1)
	{
		CCLog("videoStream");
		return false;
	}
	pCodecCtx = pFormatCtx->streams[videoStream]->codec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		CCLog("pCodec");
		return false;
	}
	if (avcodec_open2(pCodecCtx, pCodec, 0) < 0)
	{
		CCLog("pCodecCtx");
		return false;
	}
	pFrame = av_frame_alloc();
	pFrameRGB = av_frame_alloc();

	if ((pFrame == NULL) || (pFrameRGB == NULL))
	{
		CCLog("pFrame||pFrameRGB");
		return false;
	}
	PictureSize = pCodecCtx->width*pCodecCtx->height*3;

	pSwsCtx = sws_getCachedContext(
		pSwsCtx,
		pCodecCtx->width,
		pCodecCtx->height,
		pCodecCtx->pix_fmt,
		pCodecCtx->width,
		pCodecCtx->height,
		AV_PIX_FMT_BGR24,
		SWS_BICUBIC,
		NULL, NULL, NULL);
	if (!pSwsCtx)
	{
		CCLog("pSwsCtx");
		return false;
	}
	while (av_read_frame(pFormatCtx, &packet) >= 0)
	{
		if (packet.stream_index == videoStream)
		{
			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

			if (frameFinished)
			{
				buf = (uint8_t*)av_malloc(PictureSize);

				avpicture_fill((AVPicture *)pFrameRGB, buf, AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height);

				pFrameRGB->data[0] += pFrameRGB->linesize[0] * (480 - 1);
				pFrameRGB->linesize[0] *= -1;
				pFrameRGB->data[1] += pFrameRGB->linesize[1] * (480 / 2 - 1);
				pFrameRGB->linesize[1] *= -1;
				pFrameRGB->data[2] += pFrameRGB->linesize[2] * (480 / 2 - 1);
				pFrameRGB->linesize[2] *= -1;

				m_Width = pCodecCtx->width;
				m_Height = pCodecCtx->height;
				unsigned char* pVideoRGB24 = buf;
				m_VideoList.push_back(pVideoRGB24);

				sws_scale(
					pSwsCtx,
					(const uint8_t* const*)pFrame->data,
					pFrame->linesize,
					0,
					pCodecCtx->height,
					pFrameRGB->data,
					pFrameRGB->linesize);
			}
		}
		av_packet_unref(&packet);
	}
	m_VideoIndex = 0;
	Ext_VideoSize = m_VideoList.size();

	sws_freeContext(pSwsCtx);
	pSwsCtx = NULL;
	av_free(pFrame);
	av_free(pFrameRGB);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
	return true;
}
