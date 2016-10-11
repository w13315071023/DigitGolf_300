#pragma once
#include "Tools.h"
#include "pthread\pthread.h"

class RecordClass
{
public:

	CameraHandle    m_hCamera;
	INT				cameraNum;
	tSdkCameraCapbility m_sCameraInfo;

	//static pthread_mutex_t m_mutex1;
	//static pthread_mutex_t m_mutex2;

	float m_curTime;
	float m_lastTime;
	int m_BufferIndexMax;
	int m_BufferIndex;
	int BufferSize;
	vector<VideoRAW*> m_Buffer;
public:
	RecordClass(void);
	~RecordClass(void);
	void Destructor();
	bool init(tSdkCameraDevInfo CameraInfo);
	VideoRAW* getBufferByIndex(int index);
	int getBuffIndex();
	void setExposureTime(float ExposureTime);
	void setGain(int Gain);
	void setAeState(bool AeState);
};
extern DWORD WINAPI ThreadCallBack( LPVOID lpParam );
extern void MySleep(int dTime);
