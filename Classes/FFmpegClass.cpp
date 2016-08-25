#include "FFmpegClass.h"
FFmpegClass::FFmpegClass(void)
{
}
FFmpegClass::~FFmpegClass(void)
{
}
bool FFmpegClass::ReadVideo()
{
	AVCodecContext *pCodecCtx;
	AVFormatContext *pFormatCtx;
	AVCodec *pCodec;
	AVFrame *pFrame, *pFrameRGB;
	struct SwsContext *pSwsCtx = NULL;
	AVPacket packet;

	av_register_all();

	if (avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0)
	{
		CCLog("open");
		return false;
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
	PictureSize = avpicture_get_size(AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height);

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
				m_Width = pCodecCtx->width;
				m_Height = pCodecCtx->height;
				unsigned char* pVideoRGB24 = buf;
				m_DemoVideoList.push_back(pVideoRGB24);

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
	m_DemoVideoIter = m_DemoVideoList.begin();
	Ext_VideoSize = m_DemoVideoList.size();

	sws_freeContext(pSwsCtx);
	av_free(pFrame);
	av_free(pFrameRGB);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
	return true;
}
void FFmpegClass::SeveVideo()
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

	av_frame_get_buffer(m_pYUVFrame, 32);

	ret = avcodec_open2(codecCtx, videoEncoder, NULL);
	video_st.videoFrame = m_pYUVFrame;

	av_dump_format(fmt_ctx, 0, outFilePath, 1);
	if (!(fmt->flags & AVFMT_NOFILE))
	{
		ret = avio_open(&fmt_ctx->pb, outFilePath, AVIO_FLAG_WRITE);
	}
	ret = avformat_write_header(fmt_ctx, NULL);

	for (size_t i = 0; i < m_VideoList.size(); i++)
	{
		AVPacket pkt;
		av_init_packet(&pkt);
		ret = av_frame_make_writable(video_st.videoFrame);
		fill_yuv_image(i);

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

	avcodec_close(video_st.st->codec);
	av_freep(m_pYUVFrame->data);
	av_frame_free(&m_pYUVFrame);
	av_frame_free(&m_pRGBFrame);
	if (!(fmt->flags & AVFMT_NOFILE))
	{
		avio_close(fmt_ctx->pb);
	}
	avformat_free_context(fmt_ctx);
}