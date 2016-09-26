#include "VideoClass.h"

SwsContext* VideoClass::pSwsCtx = NULL;
VideoClass::VideoClass(void)
{
	m_Width = 640;
	m_Height = 480;
	m_IsPlayOver = true;
	m_pTexture = new CCTexture2D();
	m_pSprite = new CCSprite();
	m_pTexture->initWithData(
		NULL,
		kTexture2DPixelFormat_RGB888,
		0,
		0,
		CCSize(640, 480));
	m_pSprite->initWithTexture(m_pTexture);
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(ccp(0.5,0.5));
}


VideoClass::~VideoClass(void)
{
	m_pTexture->release();
}
void VideoClass::ShowVideo()
{
	if (m_VideoList.empty())
	{
		m_IsPlayOver = true;
		return;
	}
	if (m_VideoIndex < m_VideoList.size())
	{
		if(m_VideoIndex < 0)
		{
			m_VideoIndex = 0;
		}
		m_pTexture->updateVideoWithData(
			m_VideoList[m_VideoIndex],
			kTexture2DPixelFormat_RGB888,
			m_Width,
			m_Height,
			CCSize(630, 470));
		m_pSprite->initWithTexture(m_pTexture);
		//m_VideoIter += Ext_StepNum;
		m_VideoIndex ++;
	}
	else
	{
		m_IsPlayOver = true;
		m_VideoIndex = 0;
	}
}
void VideoClass::ReSetVideo()
{
	m_VideoIndex = 0;
	ShowVideo();
}
void VideoClass::Add_audio_viode_stream(OutputStream* viode_st, OutputStream* audio_st, AVFormatContext* oc, AVCodec* video_encoder, AVCodec* audio_encoder)
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
void VideoClass::fill_yuv_image(int imageInx)
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
void VideoClass::SaveVideo()
{
	int ret = 0;
	int got_packet = 0;

	AVOutputFormat* fmt = NULL;
	AVFormatContext* fmt_ctx = NULL;
	AVCodec* videoEncoder = NULL;
	AVCodec* audioEncoder = NULL;

	OutputStream video_st;
	OutputStream audio_st;
	memset(&video_st,0,sizeof(OutputStream));
	memset(&audio_st,0,sizeof(OutputStream));

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
		codecCtx->bit_rate = m_BitRate;
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
		memset(&pkt,0,sizeof(AVPacket));
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

	sws_freeContext(pSwsCtx);
	pSwsCtx = NULL;
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