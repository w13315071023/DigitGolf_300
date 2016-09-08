#include "MovieVideoLayer.h"
#include "DataMager.h"
#include "SerialMager.h"
#include "RecordClass.h"

MovieVideoLayer::MovieVideoLayer()
{

}
MovieVideoLayer::~MovieVideoLayer()
{
	av_free(m_pFrameImageRGB);
	if (!m_VideoList.empty())
	{
		
		for (int i = 0; i < m_VideoList.size();i++)
		{
			av_free(m_VideoList[i]);
		}
		m_VideoList.clear();
		m_VideoIndex = 0;
	}
}
SwsContext* MovieVideoLayer::pSwsCtx = NULL;
MovieVideoLayer* MovieVideoLayer::create(int Direction)
{
    MovieVideoLayer *pRet = new MovieVideoLayer();
    if (pRet && pRet->init(Direction))
    {
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool MovieVideoLayer::init(int Direction)
{
	if (!CCLayer::init())
    {
        return false;
    }
	printf("≥ı ºªØMovieVideoLayer\n");
	m_Camera = NULL;
	m_ShowIndex = 0;
	m_TransIndex = 0;
	m_IsRecord = false;
	m_Width = 640;
	m_Height = 480;

	if (!pSwsCtx)
	{
		pSwsCtx = sws_getCachedContext(
			pSwsCtx,
			640,
			480,
			AV_PIX_FMT_BGR24,
			640,
			480,
			AV_PIX_FMT_YUV420P,
			SWS_POINT,
			NULL, NULL, NULL);
	}
	if (Ext_cameraNum == 0)
	{
		return true;
	}
    if(Direction == FRONT)
	{
		m_Camera = m_Camera1;
	}
	else
	{
		m_Camera = m_Camera2; 
	}

	for (size_t i = 0; i < Ext_VideoSize * Ext_StepNum; i++)
	{
		unsigned char* FrameData = (unsigned char*)av_malloc(m_Camera->BufferSize);
		m_VideoList.push_back(FrameData);
	}
	
	m_pFrameImageRGB = (unsigned char*)av_malloc(m_Camera->BufferSize);
	this->setRotationX(180);
	CCSprite* beijing2 = CCSprite::create("VideoUI/beijing2.png");
	beijing2->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
	this->addChild(beijing2);
	m_pSprite->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));
	this->addChild(m_pSprite);

    return true;
}
void MovieVideoLayer::update(float dt)
{
	m_ShowIndex = (m_Camera->getBuffIndex() - 1<0) ? m_Camera->m_BufferIndexMax-1 : m_Camera->getBuffIndex() - 1;
	m_FrameImageHead = m_Camera->getBufferByIndex(m_ShowIndex)->FrameHead;
	try
	{
		CameraImageProcess(m_Camera->m_hCamera,
			m_Camera->getBufferByIndex(m_ShowIndex)->FrameData,
			m_pFrameImageRGB,
			&m_FrameImageHead);
	}
	catch (...)
	{
		FILE* CatchMsgFile = fopen("CatchMsgFile.txt", "a");
		fprintf(CatchMsgFile, "CameraImageProssesError!\n");
		fclose(CatchMsgFile);
	}
	m_pTexture->updateVideoWithData(
		m_pFrameImageRGB,
		kTexture2DPixelFormat_RGB888,
		640,
		480,
		CCSize(630, 470));
	m_pSprite->initWithTexture(m_pTexture);
}
void MovieVideoLayer::Record(bool isRecord)
{
	m_IsRecord = isRecord;
	m_IsPlayOver = isRecord;
}
void MovieVideoLayer::TransData()
{
	if (m_TransIndex < 20 || Ext_IsRecordBegin == false)
	{
		return;
	}
	if (m_TransIndex == Ext_VideoSize * Ext_StepNum)
	{
		m_TransIndex = 0;
		return;
	}
	for (size_t i = 0; i < Ext_StepNum; i++)
	{
		int curIndex = m_Camera->getBuffIndex() - Ext_VideoSize * Ext_StepNum + m_TransIndex;
		curIndex = curIndex < 0 ? m_Camera->m_BufferIndexMax + curIndex : curIndex;

		m_FrameImageHead = m_Camera->getBufferByIndex(curIndex)->FrameHead;
		CameraImageProcess(m_Camera->m_hCamera,
			m_Camera->getBufferByIndex(curIndex)->FrameData,
			m_pFrameImageRGB,
			&m_FrameImageHead);
		swap(m_pFrameImageRGB, m_VideoList[m_TransIndex]);
		m_TransIndex ++;
	}
}
void MovieVideoLayer::RecordOk()
{
	int curIndex = 0;
	this->Record(false);
	for (size_t i = 0; i < Ext_VideoSize * Ext_StepNum; i ++)
	{
		if (i == m_TransIndex+20)
		{
			m_TransIndex = i;
			break;
		}
		curIndex = m_Camera->getBuffIndex() - Ext_VideoSize * Ext_StepNum + i;
		curIndex = curIndex < 0 ? m_Camera->m_BufferIndexMax + curIndex : curIndex;
		m_FrameImageHead = m_Camera->getBufferByIndex(curIndex)->FrameHead;
		try
		{
			CameraImageProcess(m_Camera->m_hCamera,
				m_Camera->getBufferByIndex(curIndex)->FrameData,
				m_pFrameImageRGB,
				&m_FrameImageHead);
			swap(m_pFrameImageRGB, m_VideoList[i]);
		}
		catch (...)
		{
			FILE* CatchMsgFile = fopen("CatchMsgFile.txt", "a");
			fprintf(CatchMsgFile, "CameraImageProssesError!\n");
			fclose(CatchMsgFile);
		}
	}
	m_VideoIndex = 0;
}
void MovieVideoLayer::ResetVideoSize()
{
	int curVideoSize = m_VideoList.size();
	if (curVideoSize> Ext_VideoSize * Ext_StepNum)
	{
		curVideoSize = m_VideoList.size();
		for (size_t i = 0; i < curVideoSize - Ext_VideoSize * Ext_StepNum; i++)
		{
			av_free(m_VideoList.back());
			m_VideoList.pop_back();
		}
	}
	if (curVideoSize< Ext_VideoSize * Ext_StepNum)
	{
		for (size_t i = 0; i < Ext_VideoSize * Ext_StepNum - curVideoSize; i++)
		{
			unsigned char* FrameData = (unsigned char*)av_malloc(MovieVideoLayer::m_Camera1->BufferSize);
			m_VideoList.push_back(FrameData);
		}
	}
}
void MovieVideoLayer::Add_audio_viode_stream(OutputStream* viode_st, OutputStream* audio_st, AVFormatContext* oc, AVCodec* video_encoder, AVCodec* audio_encoder)
{
	AVOutputFormat* fmt = oc->oformat;
	if (fmt->video_codec != AV_CODEC_ID_NONE)
	{
		video_encoder = avcodec_find_encoder(fmt->video_codec);
		viode_st->st = avformat_new_stream(oc, video_encoder);
		viode_st->st->id = oc->nb_streams - 1;
		AVCodecContext* codecCtx = viode_st->st->codec;

		codecCtx->codec_id = fmt->video_codec;
		codecCtx->bit_rate = 400000;
		codecCtx->width = m_Width;
		codecCtx->height = m_Height;
		AVRational r = {1,25};
		codecCtx->time_base = r;
		codecCtx->gop_size = 12;
		codecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
		if (codecCtx->codec_id == AV_CODEC_ID_MPEG2VIDEO)
		{
			codecCtx->max_b_frames = 2;
		}
		if (codecCtx->codec_id == AV_CODEC_ID_MPEG1VIDEO)
		{
			codecCtx->mb_decision = 2;
		}
		if (fmt->flags & AVFMT_GLOBALHEADER)
		{
			codecCtx->flags = AV_CODEC_FLAG_GLOBAL_HEADER;
		}

	}
	if (fmt->audio_codec != AV_CODEC_ID_NONE)
	{

	}
}
void MovieVideoLayer::fill_yuv_image(int imageInx)
{
	avpicture_fill((AVPicture*)m_pRGBFrame, (uint8_t*)m_VideoList[imageInx], AV_PIX_FMT_BGR24, m_Width, m_Height);

	m_pRGBFrame->data[0] += m_pRGBFrame->linesize[0] * (480 - 1);
	m_pRGBFrame->linesize[0] *= -1;
	m_pRGBFrame->data[1] += m_pRGBFrame->linesize[1] * (480 / 2 - 1);
	m_pRGBFrame->linesize[1] *= -1;
	m_pRGBFrame->data[2] += m_pRGBFrame->linesize[2] * (480 / 2 - 1);
	m_pRGBFrame->linesize[2] *= -1;

	sws_scale(
		pSwsCtx,
		m_pRGBFrame->data,
		m_pRGBFrame->linesize,
		0,
		480,
		m_pYUVFrame->data,
		m_pYUVFrame->linesize);
}
void MovieVideoLayer::SeveVideo()
{
	int ret = 0;
	int got_packet = 0;
	char* outFilePath;
	if (m_Camera == m_Camera1)
	{
		outFilePath = "Upload/name1.mp4";
	}
	else
	{
		outFilePath = "Upload/name2.mp4";
	}
	
	AVOutputFormat* fmt = { NULL };
	AVFormatContext* fmt_ctx = { NULL };
	AVCodec* videoEncoder = { NULL };
	AVCodec* audioEncoder = { NULL };

	OutputStream video_st = { NULL };
	OutputStream audio_st = { NULL };

	av_register_all();
	avformat_alloc_output_context2(&fmt_ctx, NULL, NULL, outFilePath);
	if (!fmt_ctx)
	{
		avformat_alloc_output_context2(&fmt_ctx, NULL, "mpeg", outFilePath);
	}
	if (!fmt_ctx)
	{
		printf("Error  avformat_alloc_output_context2.\n");
	}
	fmt = fmt_ctx->oformat;

	AVCodecContext* codecCtx;
	if (fmt->video_codec != AV_CODEC_ID_NONE)
	{
		videoEncoder = avcodec_find_encoder(fmt->video_codec);
		video_st.st = avformat_new_stream(fmt_ctx, videoEncoder);
		video_st.st->id = fmt_ctx->nb_streams - 1;
		
		codecCtx = video_st.st->codec;
		codecCtx->codec_id = fmt->video_codec;
		codecCtx->bit_rate = 400000;
		codecCtx->width = m_Width;
		codecCtx->height = m_Height;
		AVRational r = { 1, 25 };
		codecCtx->time_base = r;
		codecCtx->gop_size = 12;
		codecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
		if (codecCtx->codec_id == AV_CODEC_ID_MPEG2VIDEO)
		{
			codecCtx->max_b_frames = 2;
		}
		if (codecCtx->codec_id == AV_CODEC_ID_MPEG1VIDEO)
		{
			codecCtx->mb_decision = 2;
		}
		if (fmt->flags & AVFMT_GLOBALHEADER)
		{
			codecCtx->flags = AV_CODEC_FLAG_GLOBAL_HEADER;
		}

	}
	m_pRGBFrame = av_frame_alloc();
	m_pRGBFrame->format = codecCtx->pix_fmt;
	m_pRGBFrame->width = m_Width;
	m_pRGBFrame->height = m_Height;

	m_pYUVFrame = av_frame_alloc();
	m_pYUVFrame->format = codecCtx->pix_fmt;
	m_pYUVFrame->width = m_Width;
	m_pYUVFrame->height = m_Height;

	av_frame_get_buffer(m_pYUVFrame,32);

	ret = avcodec_open2(codecCtx, videoEncoder, NULL);
	video_st.videoFrame = m_pYUVFrame;

	av_dump_format(fmt_ctx, 0, outFilePath, 1);
	if (!(fmt->flags & AVFMT_NOFILE))
	{
		ret = avio_open(&fmt_ctx->pb, outFilePath, AVIO_FLAG_WRITE);
	}
	ret = avformat_write_header(fmt_ctx, NULL);

	for (size_t i = 0; i < m_VideoList.size()/Ext_FFmpegStep; i++)
	{
		AVPacket pkt;
		av_init_packet(&pkt);
		ret = av_frame_make_writable(video_st.videoFrame);
		fill_yuv_image(i*Ext_FFmpegStep);

		video_st.videoFrame->pts = video_st.next_pts++;

		ret = avcodec_encode_video2(codecCtx, &pkt, m_pYUVFrame, &got_packet);

		if (got_packet)
		{
			av_packet_rescale_ts(&pkt, codecCtx->time_base, video_st.st->time_base);
			pkt.stream_index = video_st.st->index;
			ret = av_interleaved_write_frame(fmt_ctx, &pkt);
		}
	}

	av_write_trailer(fmt_ctx);

	av_frame_free(&m_pYUVFrame);
	av_frame_free(&m_pRGBFrame);

	avcodec_close(video_st.st->codec);
	if (!(fmt->flags & AVFMT_NOFILE))
	{
		avio_close(fmt_ctx->pb);
	}
	avformat_free_context(fmt_ctx);
}
