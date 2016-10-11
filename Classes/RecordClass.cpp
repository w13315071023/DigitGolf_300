#include "RecordClass.h"

//pthread_mutex_t RecordClass::m_mutex1 = NULL;
//pthread_mutex_t RecordClass::m_mutex2 = NULL;
void MySleep(int dTime)
{
	int i = 0;
	while(i <dTime)
	{
		__int64 nop;
		QueryPerformanceCounter((LARGE_INTEGER*)&nop);
		i++;
	}
}
DWORD WINAPI ThreadCallBack( LPVOID lpParam )
{
	RecordClass* pThis = (RecordClass*)lpParam;
	BYTE* bydFrameBuffer;
	tSdkFrameHead FrameInfo;
	float FrameTime = 0;
	float bTime = 0.0;
	float dTime = 0.0;
	int FrameTimeNum = 10000;
	float curTime = 0;
	float lastTime = 0;
	while (!Ext_IsTurnEnd)
	{
		if (Ext_IsThreadOn)
		{
			if (!CameraGetImageBuffer(pThis->m_hCamera, &FrameInfo, &bydFrameBuffer, 20))
			{
				curTime = GetTime();
				dTime = curTime - lastTime;
				bTime = Ext_VideoExposureTime/1000000.0;

				memcpy(pThis->m_Buffer[pThis->m_BufferIndex]->FrameData, bydFrameBuffer, FrameInfo.uBytes);
				pThis->m_Buffer[pThis->m_BufferIndex]->FrameHead = FrameInfo;
				pThis->m_BufferIndex = (pThis->m_BufferIndex + 1) % pThis->m_BufferIndexMax;
				CameraReleaseImageBuffer(pThis->m_hCamera, bydFrameBuffer);

				if (Ext_TiaoShi)
				{
					printf("时间间隔%f\n", dTime);
				}
				if(Ext_IsIndoor == false&&dTime > 0)
				{

					FrameTime = bTime - dTime;

					if(FrameTimeNum<0)
					{
						Ext_IsExpose = true;
						if(FrameTime>0)
						{
							FrameTimeNum = 0;
						}
					}
					else
					{
						Ext_IsExpose = false;
						if(bTime > dTime)
						{
							FrameTimeNum+=10000*(bTime / dTime);
						}
						else
						{
							FrameTimeNum-=20000*(dTime / bTime);
						}
						MySleep(FrameTimeNum);
					}
				}
				lastTime = curTime;
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
	CameraPlay(m_hCamera);

	tSdkImageResolution pImageResolution;
	CameraGetImageResolution(m_hCamera, &pImageResolution);
	BufferSize = pImageResolution.iWidth*pImageResolution.iHeight * 3;

	m_BufferIndexMax = 3*300*Ext_StepNum;

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
void RecordClass::setAeState(bool AeState)
{
	CameraSetAeState(m_hCamera, AeState);
}
