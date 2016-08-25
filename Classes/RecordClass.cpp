#include "RecordClass.h"

//pthread_mutex_t RecordClass::m_mutex1 = NULL;
//pthread_mutex_t RecordClass::m_mutex2 = NULL;

DWORD WINAPI ThreadCallBack( LPVOID lpParam )
{
	RecordClass* pThis = (RecordClass*)lpParam;
	BYTE* bydFrameBuffer;
	tSdkFrameHead FrameInfo;
	while (!Ext_IsTurnEnd)
	{
		if (Ext_IsThreadOn)
		{
			if (!CameraGetImageBuffer(pThis->m_hCamera, &FrameInfo, &bydFrameBuffer, 20))
			{
				if (Ext_TiaoShi)
				{
					pThis->m_curTime = GetTime();
					printf("%p时间间隔%f\n", pThis, pThis->m_curTime - pThis->m_lastTime);
					pThis->m_lastTime = pThis->m_curTime;
				}
				memcpy(pThis->m_Buffer[pThis->m_BufferIndex]->FrameData, bydFrameBuffer, FrameInfo.uBytes);
				pThis->m_Buffer[pThis->m_BufferIndex]->FrameHead = FrameInfo;
				pThis->m_BufferIndex = (pThis->m_BufferIndex + 1) % pThis->m_BufferIndexMax;
				CameraReleaseImageBuffer(pThis->m_hCamera, bydFrameBuffer);
			}
		}
	}
	printf("%d相机退出",pThis->m_hCamera);
	return 0;
}


RecordClass::RecordClass(void)
{
	m_BufferIndex = 0;
	BufferSize = 0;
}


RecordClass::~RecordClass(void)
{
}
void RecordClass::Destructor()
{
	CameraUnInit(m_hCamera);
	if (!m_Buffer.empty())
	{
		for (size_t i = 0; i < m_BufferIndexMax; i++)
		{
			CameraAlignFree(m_Buffer[i]->FrameData);
		}
		m_Buffer.clear();
	}
	//if (m_hCamera == 1)
	//{
	//	pthread_mutex_destroy(&m_mutex1);
	//}
	//else
	//{
	//	pthread_mutex_destroy(&m_mutex2);
	//}
	
}
bool RecordClass::init(tSdkCameraDevInfo CameraInfo)
{
	printf("初始化Camera%s\n", CameraInfo.acFriendlyName);
	CameraInit(&CameraInfo, -1, -1, &m_hCamera);
	CameraGetCapability(m_hCamera, &m_sCameraInfo);
	CameraSetAeState(m_hCamera, false);
	CameraPlay(m_hCamera);

	tSdkImageResolution pImageResolution;
	CameraGetImageResolution(m_hCamera, &pImageResolution);
	BufferSize = pImageResolution.iWidth*pImageResolution.iHeight * 3;

	m_BufferIndexMax = 4*30*Ext_StepNum;

	for (size_t i = 0; i < m_BufferIndexMax; i++)
	{
		VideoRAW* pVideoRGB24 = new VideoRAW();
		pVideoRGB24->FrameData = CameraAlignMalloc(BufferSize/3, 16);
		m_Buffer.push_back(pVideoRGB24);
	}

	//std::thread myThread(&RecordClass::ThreadCallBack, this);
	//SetThreadPriority(myThread.native_handle(), THREAD_PRIORITY_HIGHEST);
	//myThread.detach();
	
	HANDLE hThread;
	DWORD dwThreadId;
	hThread = CreateThread( 
		NULL,                   // default security attributes
		0,                      // use default stack size  
		ThreadCallBack,       // thread function name
		this,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadId);
	CloseHandle(hThread);
	

	return true;
}
VideoRAW* RecordClass::getBufferByIndex(int index)
{
	return m_Buffer[index % m_BufferIndexMax];
}
int RecordClass::getBuffIndex()
{
	return m_BufferIndex;
}
void RecordClass::setExposureTime(float ExposureTime)
{
	CameraSetExposureTime(m_hCamera, ExposureTime);
	CameraSetOnceWB(m_hCamera);
}
void RecordClass::setGain(int Gain)
{
	CameraSetAnalogGain(m_hCamera,Gain);
}
