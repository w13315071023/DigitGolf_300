#ifndef _MV_CAM_API
#define _MV_CAM_API

#include "CameraDefine.h"
#include "CameraStatus.h"

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

//BIG5 TRANS ALLOWED


/******************************************************/
// ������   : CameraSdkInit
// �������� : ���SDK��ʼ�����ڵ����κ�SDK�����ӿ�ǰ������
//        �ȵ��øýӿڽ��г�ʼ�����ú�����������������
//        �ڼ�ֻ��Ҫ����һ�Ρ�   
// ����     : iLanguageSel ����ѡ��SDK�ڲ���ʾ��Ϣ�ͽ��������,
//               0:��ʾӢ��,1:��ʾ���ġ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSdkInit)(
    int     iLanguageSel
);

/******************************************************/
// ������   : CameraEnumerateDevice
// �������� : ö���豸���������豸�б��ڵ���CameraInit
//        ֮ǰ��������øú���������豸����Ϣ��    
// ����     : pCameraList   �豸�б�����ָ�롣
//            piNums        �豸�ĸ���ָ�룬����ʱ����pCameraList
//                            �����Ԫ�ظ�������������ʱ������ʵ���ҵ����豸������
//              ע�⣬piNumsָ���ֵ�����ʼ�����Ҳ�����pCameraList����Ԫ�ظ�����
//              �����п�������ڴ������
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraEnumerateDevice)(
    tSdkCameraDevInfo* pCameraList, 
    INT*               piNums
);

/******************************************************/
// ������   : CameraIsOpened
// �������� : ����豸�Ƿ��Ѿ�������Ӧ�ó���򿪡��ڵ���CameraInit
//        ֮ǰ������ʹ�øú������м�⣬����Ѿ����򿪣�����
//        CameraInit�᷵���豸�Ѿ����򿪵Ĵ����롣    
// ����     : pCameraList �豸��ö����Ϣ�ṹ��ָ�룬��CameraEnumerateDevice��á�
//            pOpened       �豸��״ָ̬�룬�����豸�Ƿ񱻴򿪵�״̬��TRUEΪ�򿪣�FALSEΪ���С�          
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraIsOpened)(
  tSdkCameraDevInfo*  pCameraList, 
  BOOL*       pOpened
);

/******************************************************/
// ������   : CameraInit
// �������� : �����ʼ������ʼ���ɹ��󣬲��ܵ����κ�����
//        �����صĲ����ӿڡ�    
// ����     : pCameraInfo    ��������豸������Ϣ����CameraEnumerateDevice
//               ������á� 
//            iParamLoadMode  �����ʼ��ʱʹ�õĲ������ط�ʽ��-1��ʾʹ���ϴ��˳�ʱ�Ĳ������ط�ʽ��
//            emTeam         ��ʼ��ʱʹ�õĲ����顣-1��ʾ�����ϴ��˳�ʱ�Ĳ����顣
//            pCameraHandle  ����ľ��ָ�룬��ʼ���ɹ��󣬸�ָ��
//               ���ظ��������Ч������ڵ����������
//               ��صĲ����ӿ�ʱ������Ҫ����þ������Ҫ
//               ���ڶ����֮������֡�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraInit)(
    tSdkCameraDevInfo*  pCameraInfo,
    int         emParamLoadMode,
    int         emTeam,
    CameraHandle*   pCameraHandle
);

/******************************************************/
// ������   : CameraSetCallbackFunction
// �������� : ����ͼ�񲶻�Ļص��������������µ�ͼ������֡ʱ��
//        pCallBack��ָ��Ļص������ͻᱻ���á� 
// ����     : hCamera ����ľ������CameraInit������á�
//            pCallBack �ص�����ָ�롣
//            pContext  �ص������ĸ��Ӳ������ڻص�����������ʱ
//            �ø��Ӳ����ᱻ���룬����ΪNULL��������
//            ������ʱЯ��������Ϣ��
//            pCallbackOld  ���ڱ��浱ǰ�Ļص�����������ΪNULL��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetCallbackFunction)(
    CameraHandle        hCamera,
    CAMERA_SNAP_PROC    pCallBack,
    PVOID               pContext,
    CAMERA_SNAP_PROC*   pCallbackOld
);

/******************************************************/
// ������   : CameraUnInit
// �������� : �������ʼ�����ͷ���Դ��
// ����     : hCamera ����ľ������CameraInit������á�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraUnInit)(
    CameraHandle hCamera
);

/******************************************************/
// ������   : CameraGetInformation
// �������� : ��������������Ϣ
// ����     : hCamera ����ľ������CameraInit������á�
//            pbuffer ָ�����������Ϣָ���ָ�롣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetInformation)(
    CameraHandle    hCamera, 
    char**          pbuffer
);

/******************************************************/
// ������   : CameraImageProcess
// �������� : ����õ����ԭʼ���ͼ�����ݽ��д������ӱ��Ͷȡ�
//        ��ɫ�����У��������ȴ���Ч�������õ�RGB888
//        ��ʽ��ͼ�����ݡ�  
// ����     : hCamera  ����ľ������CameraInit������á�
//            pbyIn    ����ͼ�����ݵĻ�������ַ������ΪNULL�� 
//            pbyOut   �����ͼ������Ļ�������ַ������ΪNULL��
//            pFrInfo  ����ͼ���֡ͷ��Ϣ��������ɺ�֡ͷ��Ϣ
//             �е�ͼ���ʽuiMediaType����֮�ı䡣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraImageProcess)(
    CameraHandle        hCamera, 
    BYTE*               pbyIn, 
    BYTE*               pbyOut,
    tSdkFrameHead*      pFrInfo
);

/******************************************************/
// ������ 	: CameraImageProcessEx
// ��������	: ����õ����ԭʼ���ͼ�����ݽ��д������ӱ��Ͷȡ�
//			  ��ɫ�����У��������ȴ���Ч�������õ�RGB888
//			  ��ʽ��ͼ�����ݡ�	
// ����	    : hCamera      ����ľ������CameraInit������á�
//            pbyIn	     ����ͼ�����ݵĻ�������ַ������ΪNULL��	
//            pbyOut        �����ͼ������Ļ�������ַ������ΪNULL��
//            pFrInfo       ����ͼ���֡ͷ��Ϣ��������ɺ�֡ͷ��Ϣ
//            uOutFormat    �������ͼ��������ʽ
//            uReserved     Ԥ����������������Ϊ0     
//					   �е�ͼ���ʽuiMediaType����֮�ı䡣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraImageProcessEx)(
    CameraHandle        hCamera, 
    BYTE*               pbyIn, 
    BYTE*               pbyOut,
    tSdkFrameHead*      pFrInfo,
    UINT                uOutFormat,
    UINT                uReserved
);


/******************************************************/
// ������   : CameraDisplayInit
// �������� : ��ʼ��SDK�ڲ�����ʾģ�顣�ڵ���CameraDisplayRGB24
//        ǰ�����ȵ��øú�����ʼ����������ڶ��ο����У�
//        ʹ���Լ��ķ�ʽ����ͼ����ʾ(������CameraDisplayRGB24)��
//        ����Ҫ���ñ�������  
// ����     : hCamera   ����ľ������CameraInit������á�
//            hWndDisplay ��ʾ���ڵľ����һ��Ϊ���ڵ�m_hWnd��Ա��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraDisplayInit)(
    CameraHandle    hCamera,
    HWND            hWndDisplay
);

/******************************************************/
// ������   : CameraDisplayInitEx
// �������� : ��ʼ��SDK�ڲ�����ʾģ�顣�ڵ���CameraDisplayRGB24
//        ǰ�����ȵ��øú�����ʼ����������ڶ��ο����У�
//        ʹ���Լ��ķ�ʽ����ͼ����ʾ(������CameraDisplayRGB24)��
//        ����Ҫ���ñ������� �ú����� CameraDisplayInit��������
//        �ú���ʱΪͼ���ļ�����һ��SDK�������ʹ�����ڲ�ISP����ʾ�ӿ�
// ����     : pCameraHandle   ��������ľ����
//            hWndDisplay ��ʾ���ڵľ����һ��Ϊ���ڵ�m_hWnd��Ա��
//            szFileName  ͼ���ļ�����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraDisplayInitEx)(
    CameraHandle*   pCameraHandle,
    HWND            hWndDisplay,
    char*           szFileName
);

/******************************************************/
// ������   : CameraDisplayRGB24
// �������� : ��ʾͼ�񡣱�����ù�CameraDisplayInit����
//        ��ʼ�����ܵ��ñ�������  
// ����     : hCamera  ����ľ������CameraInit������á�
//            pbyRGB24 ͼ������ݻ�������RGB888��ʽ��
//            pFrInfo  ͼ���֡ͷ��Ϣ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraDisplayRGB24)(
    CameraHandle        hCamera,
    BYTE*               pbyRGB24, 
    tSdkFrameHead*      pFrInfo
);

/******************************************************/
// ������   : CameraSetDisplayMode
// �������� : ������ʾ��ģʽ��������ù�CameraDisplayInit
//        ���г�ʼ�����ܵ��ñ�������
// ����     : hCamera  ����ľ������CameraInit������á�
//            iMode    ��ʾģʽ��DISPLAYMODE_SCALE����
//             DISPLAYMODE_REAL,����μ�CameraDefine.h
//             ��emSdkDisplayMode�Ķ��塣    
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetDisplayMode)(
    CameraHandle    hCamera,
    INT             iMode
);

/******************************************************/
// ������   : CameraSetDisplayOffset
// �������� : ������ʾ����ʼƫ��ֵ��������ʾģʽΪDISPLAYMODE_REAL
//        ʱ��Ч��������ʾ�ؼ��Ĵ�СΪ320X240����ͼ���
//        �ĳߴ�Ϊ640X480����ô��iOffsetX = 160,iOffsetY = 120ʱ
//        ��ʾ���������ͼ��ľ���320X240��λ�á�������ù�
//        CameraDisplayInit���г�ʼ�����ܵ��ñ�������
// ����     : hCamera   ����ľ������CameraInit������á�
//            iOffsetX  ƫ�Ƶ�X���ꡣ
//            iOffsetY  ƫ�Ƶ�Y���ꡣ
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetDisplayOffset)(
    CameraHandle    hCamera,
    int             iOffsetX, 
    int             iOffsetY
);

/******************************************************/
// ������   : CameraSetDisplaySize
// �������� : ������ʾ�ؼ��ĳߴ硣������ù�
//        CameraDisplayInit���г�ʼ�����ܵ��ñ�������
// ����     : hCamera   ����ľ������CameraInit������á�
//            iWidth    ���
//            iHeight   �߶�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetDisplaySize)(
    CameraHandle    hCamera, 
    INT             iWidth, 
    INT             iHeight
);

/******************************************************/
// ������   : CameraGetImageBuffer
// �������� : ���һ֡ͼ�����ݡ�Ϊ�����Ч�ʣ�SDK��ͼ��ץȡʱ�������㿽�����ƣ�
//        CameraGetImageBufferʵ�ʻ�����ں��е�һ����������ַ��
//        �ú����ɹ����ú󣬱������CameraReleaseImageBuffer�ͷ���
//        CameraGetImageBuffer�õ��Ļ�����,�Ա����ں˼���ʹ��
//        �û�������  
// ����     : hCamera   ����ľ������CameraInit������á�
//            pFrameInfo  ͼ���֡ͷ��Ϣָ�롣
//            pbyBuffer   ָ��ͼ������ݵĻ�����ָ�롣����
//              �������㿽�����������Ч�ʣ����
//              ����ʹ����һ��ָ��ָ���ָ�롣
//            UINT wTimes ץȡͼ��ĳ�ʱʱ�䡣��λ���롣��
//              wTimesʱ���ڻ�δ���ͼ����ú���
//              �᷵�س�ʱ��Ϣ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetImageBuffer)(
    CameraHandle        hCamera, 
    tSdkFrameHead*      pFrameInfo, 
    BYTE**              pbyBuffer,
    UINT                wTimes
);

/******************************************************/
// ������   : CameraSnapToBuffer
// �������� : ץ��һ��ͼ�񵽻������С���������ץ��ģʽ������
//        �Զ��л���ץ��ģʽ�ķֱ��ʽ���ͼ�񲶻�Ȼ��
//        ���񵽵����ݱ��浽�������С�
//        �ú����ɹ����ú󣬱������CameraReleaseImageBuffer
//        �ͷ���CameraSnapToBuffer�õ��Ļ�������������ο�
//        CameraGetImageBuffer�����Ĺ����������֡�  
// ����     : hCamera   ����ľ������CameraInit������á�
//            pFrameInfo  ָ�룬����ͼ���֡ͷ��Ϣ��
//            pbyBuffer   ָ��ָ���ָ�룬��������ͼ�񻺳����ĵ�ַ��
//            uWaitTimeMs ��ʱʱ�䣬��λ���롣�ڸ�ʱ���ڣ������Ȼû��
//              �ɹ���������ݣ��򷵻س�ʱ��Ϣ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSnapToBuffer)(
    CameraHandle        hCamera,
    tSdkFrameHead*      pFrameInfo,
    BYTE**              pbyBuffer,
    UINT                uWaitTimeMs
);

/******************************************************/
// ������   : CameraReleaseImageBuffer
// �������� : �ͷ���CameraGetImageBuffer��õĻ�������
// ����     : hCamera   ����ľ������CameraInit������á�
//            pbyBuffer   ��CameraGetImageBuffer��õĻ�������ַ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraReleaseImageBuffer)(
    CameraHandle    hCamera, 
    BYTE*           pbyBuffer
);

/******************************************************/
// ������   : CameraPlay
// �������� : ��SDK���빤��ģʽ����ʼ��������������͵�ͼ��
//        ���ݡ������ǰ����Ǵ���ģʽ������Ҫ���յ�
//        ����֡�Ժ�Ż����ͼ��
// ����     : hCamera   ����ľ������CameraInit������á�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraPlay)(
    CameraHandle hCamera
);

/******************************************************/
// ������   : CameraPause
// �������� : ��SDK������ͣģʽ�����������������ͼ�����ݣ�
//        ͬʱҲ�ᷢ�������������ͣ������ͷŴ������
//        ��ͣģʽ�£����Զ�����Ĳ����������ã���������Ч��  
// ����     : hCamera   ����ľ������CameraInit������á�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraPause)(
    CameraHandle hCamera
);

/******************************************************/
// ������   : CameraStop
// �������� : ��SDK����ֹͣ״̬��һ���Ƿ���ʼ��ʱ���øú�����
//        �ú��������ã������ٶ�����Ĳ����������á�
// ����     : hCamera   ����ľ������CameraInit������á�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraStop)(
    CameraHandle hCamera
);

/******************************************************/
// ������   : CameraInitRecord
// �������� : ��ʼ��һ��¼��
// ����     : hCamera   ����ľ������CameraInit������á�
//            iFormat   ¼��ĸ�ʽ����ǰֻ֧�ֲ�ѹ����MSCV���ַ�ʽ��  
//              0:��ѹ����1:MSCV��ʽѹ����
//            pcSavePath  ¼���ļ������·����
//            b2GLimit    ���ΪTRUE,���ļ�����2Gʱ�Զ��ָ
//            dwQuality   ¼����������ӣ�Խ��������Խ�á���Χ1��100.
//            iFrameRate  ¼���֡�ʡ������趨�ı�ʵ�ʲɼ�֡�ʴ�
//              �����Ͳ���©֡��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraInitRecord)(
    CameraHandle    hCamera,
    int             iFormat,
    char*           pcSavePath,
    BOOL            b2GLimit,
    DWORD           dwQuality,
    int             iFrameRate
);

/******************************************************/
// ������   : CameraStopRecord
// �������� : ��������¼�񡣵�CameraInitRecord�󣬿���ͨ���ú���
//        ������һ��¼�񣬲�����ļ����������
// ����     : hCamera   ����ľ������CameraInit������á�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraStopRecord)(
    CameraHandle    hCamera
);

/******************************************************/
// ������   : CameraPushFrame
// �������� : ��һ֡���ݴ���¼�����С��������CameraInitRecord
//        ���ܵ��øú�����CameraStopRecord���ú󣬲����ٵ���
//        �ú������������ǵ�֡ͷ��Ϣ��Я����ͼ��ɼ���ʱ���
//        ��Ϣ�����¼����Ծ�׼��ʱ��ͬ����������֡�ʲ��ȶ�
//        ��Ӱ�졣
// ����     : hCamera     ����ľ������CameraInit������á�
//            pbyImageBuffer    ͼ������ݻ�������������RGB��ʽ��
//            pFrInfo           ͼ���֡ͷ��Ϣ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraPushFrame)(
    CameraHandle    hCamera,
    BYTE*           pbyImageBuffer,
    tSdkFrameHead*  pFrInfo
);

/******************************************************/
// ������   : CameraSaveImage
// �������� : ��ͼ�񻺳��������ݱ����ͼƬ�ļ���
// ����     : hCamera    ����ľ������CameraInit������á�
//            lpszFileName   ͼƬ�����ļ�����·����
//            pbyImageBuffer ͼ������ݻ�������
//            pFrInfo        ͼ���֡ͷ��Ϣ��
//            byFileType     ͼ�񱣴�ĸ�ʽ��ȡֵ��Χ�μ�CameraDefine.h
//               ��emSdkFileType�����Ͷ��塣Ŀǰ֧��  
//               BMP��JPG��PNG��RAW���ָ�ʽ������RAW��ʾ
//               ��������ԭʼ���ݣ�����RAW��ʽ�ļ�Ҫ��
//               pbyImageBuffer��pFrInfo����CameraGetImageBuffer
//               ��õ����ݣ�����δ��CameraImageProcessת��
//               ��BMP��ʽ����֮�����Ҫ�����BMP��JPG����
//               PNG��ʽ����pbyImageBuffer��pFrInfo����
//               CameraImageProcess������RGB��ʽ���ݡ�
//                 �����÷����Բο�Advanced�����̡�   
//            byQuality      ͼ�񱣴���������ӣ���������ΪJPG��ʽ
//                 ʱ�ò�����Ч����Χ1��100�������ʽ
//                           ����д��0��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSaveImage)(
    CameraHandle    hCamera,
    char*           lpszFileName,
    BYTE*           pbyImageBuffer,
    tSdkFrameHead*  pFrInfo,
    UINT            byFileType,
    BYTE            byQuality
);

/******************************************************/
// ������   : CameraGetImageResolution
// �������� : ��õ�ǰԤ���ķֱ��ʡ�
// ����     : hCamera    ����ľ������CameraInit������á�
//            psCurVideoSize �ṹ��ָ�룬���ڷ��ص�ǰ�ķֱ��ʡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetImageResolution)(
    CameraHandle            hCamera, 
    tSdkImageResolution*    psCurVideoSize
);

/******************************************************/
// ������   : CameraSetImageResolution
// �������� : ����Ԥ���ķֱ��ʡ�
// ����     : hCamera      ����ľ������CameraInit������á�
//            pImageResolution �ṹ��ָ�룬���ڷ��ص�ǰ�ķֱ��ʡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetImageResolution)(
    CameraHandle            hCamera, 
    tSdkImageResolution*    pImageResolution
);

/******************************************************/
// ������   : CameraGetMediaType
// �������� : ��������ǰ���ԭʼ���ݵĸ�ʽ�����š�
// ����     : hCamera   ����ľ������CameraInit������á�
//            piMediaType   ָ�룬���ڷ��ص�ǰ��ʽ���͵������š�
//              ��CameraGetCapability�����������ԣ�
//              ��tSdkCameraCapbility�ṹ���е�pMediaTypeDesc
//              ��Ա�У����������ʽ���������֧�ֵĸ�ʽ��
//              piMediaType��ָ��������ţ����Ǹ�����������š�
//              pMediaTypeDesc[*piMediaType].iMediaType���ʾ��ǰ��ʽ�� 
//              ���롣�ñ�����μ�CameraDefine.h��[ͼ���ʽ����]���֡�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetMediaType)(
    CameraHandle    hCamera, 
    INT*            piMediaType
);

/******************************************************/
// ������   : CameraSetMediaType
// �������� : ������������ԭʼ���ݸ�ʽ��
// ����     : hCamera   ����ľ������CameraInit������á�
//            iMediaType  ��CameraGetCapability�����������ԣ�
//              ��tSdkCameraCapbility�ṹ���е�pMediaTypeDesc
//              ��Ա�У����������ʽ���������֧�ֵĸ�ʽ��
//              iMediaType���Ǹ�����������š�
//              pMediaTypeDesc[iMediaType].iMediaType���ʾ��ǰ��ʽ�� 
//              ���롣�ñ�����μ�CameraDefine.h��[ͼ���ʽ����]���֡�   
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetMediaType)(
    CameraHandle    hCamera, 
    INT             iMediaType
);

/******************************************************/
// ������   : CameraSetAeState
// �������� : ��������ع��ģʽ���Զ������ֶ���
// ����     : hCamera   ����ľ������CameraInit������á�
//            bAeState    TRUE��ʹ���Զ��ع⣻FALSE��ֹͣ�Զ��ع⡣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetAeState)(
    CameraHandle    hCamera, 
    BOOL            bAeState
);

/******************************************************/
// ������   : CameraGetAeState
// �������� : ��������ǰ���ع�ģʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            pAeState   ָ�룬���ڷ����Զ��ع��ʹ��״̬��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetAeState)(
    CameraHandle    hCamera, 
    BOOL*           pAeState
);

/******************************************************/
// ������   : CameraSetSharpness
// �������� : ����ͼ��Ĵ�����񻯲�����
// ����     : hCamera  ����ľ������CameraInit������á�
//            iSharpness �񻯲�������Χ��CameraGetCapability
//               ��ã�һ����[0,100]��0��ʾ�ر��񻯴���
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetSharpness)(
    CameraHandle    hCamera, 
    int             iSharpness
);

/******************************************************/
// ������   : CameraGetSharpness
// �������� : ��ȡ��ǰ���趨ֵ��
// ����     : hCamera   ����ľ������CameraInit������á�
//            piSharpness ָ�룬���ص�ǰ�趨���񻯵��趨ֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetSharpness)(
    CameraHandle    hCamera, 
    int*            piSharpness
);

/******************************************************/
// ������   : CameraSetLutMode
// �������� : ��������Ĳ��任ģʽLUTģʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            emLutMode  LUTMODE_PARAM_GEN ��ʾ��٤��ͶԱȶȲ�����̬����LUT��
//             LUTMODE_PRESET    ��ʾʹ��Ԥ���LUT��
//             LUTMODE_USER_DEF  ��ʾʹ���û��Զ���LUT��
//             LUTMODE_PARAM_GEN�Ķ���ο�CameraDefine.h��emSdkLutMode���͡�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetLutMode)(
    CameraHandle    hCamera,
    int             emLutMode
);

/******************************************************/
// ������   : CameraGetLutMode
// �������� : �������Ĳ��任ģʽLUTģʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            pemLutMode ָ�룬���ص�ǰLUTģʽ��������CameraSetLutMode
//             ��emLutMode������ͬ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetLutMode)(
    CameraHandle    hCamera,
    int*            pemLutMode
);

/******************************************************/
// ������   : CameraSelectLutPreset
// �������� : ѡ��Ԥ��LUTģʽ�µ�LUT��������ʹ��CameraSetLutMode
//        ��LUTģʽ����ΪԤ��ģʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            iSel     ��������š���ĸ�����CameraGetCapability
//             ��á�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSelectLutPreset)(
    CameraHandle    hCamera,
    int             iSel
);

/******************************************************/
// ������   : CameraGetLutPresetSel
// �������� : ���Ԥ��LUTģʽ�µ�LUT�������š�
// ����     : hCamera  ����ľ������CameraInit������á�
//            piSel      ָ�룬���ر�������š�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetLutPresetSel)(
    CameraHandle    hCamera,
    int*            piSel
);

/******************************************************/
// ������   : CameraSetCustomLut
// �������� : �����Զ����LUT��������ʹ��CameraSetLutMode
//        ��LUTģʽ����Ϊ�Զ���ģʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//             iChannel ָ��Ҫ�趨��LUT��ɫͨ������ΪLUT_CHANNEL_ALLʱ��
//                      ����ͨ����LUT����ͬʱ�滻��
//                      �ο�CameraDefine.h��emSdkLutChannel���塣
//            pLut     ָ�룬ָ��LUT��ĵ�ַ��LUT��Ϊ�޷��Ŷ��������飬�����СΪ
//           4096���ֱ������ɫͨ����0��4096(12bit��ɫ����)��Ӧ��ӳ��ֵ�� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetCustomLut)(
    CameraHandle    hCamera,
    int       iChannel,
    USHORT*         pLut
);

/******************************************************/
// ������   : CameraGetCustomLut
// �������� : ��õ�ǰʹ�õ��Զ���LUT��
// ����     : hCamera  ����ľ������CameraInit������á�
//             iChannel ָ��Ҫ��õ�LUT��ɫͨ������ΪLUT_CHANNEL_ALLʱ��
//                      ���غ�ɫͨ����LUT��
//                      �ο�CameraDefine.h��emSdkLutChannel���塣
//            pLut       ָ�룬ָ��LUT��ĵ�ַ��LUT��Ϊ�޷��Ŷ��������飬�����СΪ
//           4096���ֱ������ɫͨ����0��4096(12bit��ɫ����)��Ӧ��ӳ��ֵ�� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetCustomLut)(
    CameraHandle    hCamera,
    int       iChannel,
    USHORT*         pLut
);

/******************************************************/
// ������   : CameraGetCurrentLut
// �������� : ��������ǰ��LUT�����κ�LUTģʽ�¶����Ե���,
//        ����ֱ�۵Ĺ۲�LUT���ߵı仯��
// ����     : hCamera  ����ľ������CameraInit������á�
//             iChannel ָ��Ҫ��õ�LUT��ɫͨ������ΪLUT_CHANNEL_ALLʱ��
//                      ���غ�ɫͨ����LUT��
//                      �ο�CameraDefine.h��emSdkLutChannel���塣
//            pLut       ָ�룬ָ��LUT��ĵ�ַ��LUT��Ϊ�޷��Ŷ��������飬�����СΪ
//           4096���ֱ������ɫͨ����0��4096(12bit��ɫ����)��Ӧ��ӳ��ֵ�� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetCurrentLut)(
    CameraHandle    hCamera,
    int       iChannel,
    USHORT*         pLut
);

/******************************************************/
// ������   : CameraSetWbMode
// �������� : ���������ƽ��ģʽ����Ϊ�ֶ����Զ����ַ�ʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            bAuto      TRUE�����ʾʹ���Զ�ģʽ��
//             FALSE�����ʾʹ���ֶ�ģʽ��ͨ������
//                 CameraSetOnceWB������һ�ΰ�ƽ�⡣        
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetWbMode)(
    CameraHandle    hCamera,
    BOOL            bAuto
);

/******************************************************/
// ������   : CameraGetWbMode
// �������� : ��õ�ǰ�İ�ƽ��ģʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            pbAuto   ָ�룬����TRUE��ʾ�Զ�ģʽ��FALSE
//             Ϊ�ֶ�ģʽ�� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetWbMode)(
    CameraHandle    hCamera,
    BOOL*           pbAuto
);

/******************************************************/
// ������   : CameraSetPresetClrTemp
// �������� : ѡ��ָ��Ԥ��ɫ��ģʽ
// ����     : hCamera  ����ľ������CameraInit������á�
//            iSel Ԥ��ɫ�µ�ģʽ�����ţ���0��ʼ
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetPresetClrTemp)(
    CameraHandle    hCamera,
    int             iSel
);

/******************************************************/
// ������   : CameraGetPresetClrTemp
// �������� : ��õ�ǰѡ���Ԥ��ɫ��ģʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            piSel  ָ�룬����ѡ���Ԥ��ɫ��������
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetPresetClrTemp)(
    CameraHandle    hCamera,
    int*            piSel
);

/******************************************************/
// ������   : CameraSetUserClrTempGain
// �������� : �����Զ���ɫ��ģʽ�µ���������
// ����     : hCamera  ����ľ������CameraInit������á�
//            iRgain  ��ɫ���棬��Χ0��400����ʾ0��4��
//            iGgain  ��ɫ���棬��Χ0��400����ʾ0��4��
//            iBgain  ��ɫ���棬��Χ0��400����ʾ0��4��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetUserClrTempGain)(
  CameraHandle  hCamera,
  int       iRgain,
  int       iGgain,
  int       iBgain
);


/******************************************************/
// ������   : CameraGetUserClrTempGain
// �������� : ����Զ���ɫ��ģʽ�µ���������
// ����     : hCamera  ����ľ������CameraInit������á�
//            piRgain  ָ�룬���غ�ɫ���棬��Χ0��400����ʾ0��4��
//            piGgain  ָ�룬������ɫ���棬��Χ0��400����ʾ0��4��
//            piBgain  ָ�룬������ɫ���棬��Χ0��400����ʾ0��4��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetUserClrTempGain)(
  CameraHandle  hCamera,
  int*      piRgain,
  int*      piGgain,
  int*      piBgain
);

/******************************************************/
// ������   : CameraSetUserClrTempMatrix
// �������� : �����Զ���ɫ��ģʽ�µ���ɫ����
// ����     : hCamera  ����ľ������CameraInit������á�
//            pMatrix ָ��һ��float[3][3]������׵�ַ
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetUserClrTempMatrix)(
  CameraHandle  hCamera,
  float*      pMatrix
);


/******************************************************/
// ������   : CameraGetUserClrTempMatrix
// �������� : ����Զ���ɫ��ģʽ�µ���ɫ����
// ����     : hCamera  ����ľ������CameraInit������á�
//            pMatrix ָ��һ��float[3][3]������׵�ַ
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetUserClrTempMatrix)(
  CameraHandle  hCamera,
  float*      pMatrix
);

/******************************************************/
// ������   : CameraSetClrTempMode
// �������� : ���ð�ƽ��ʱʹ�õ�ɫ��ģʽ��
//              ֧�ֵ�ģʽ�����֣��ֱ����Զ���Ԥ����Զ��塣
//              �Զ�ģʽ�£����Զ�ѡ����ʵ�ɫ��ģʽ
//              Ԥ��ģʽ�£���ʹ���û�ָ����ɫ��ģʽ
//              �Զ���ģʽ�£�ʹ���û��Զ����ɫ����������;���
// ����     : hCamera ����ľ������CameraInit������á�
//            iMode ģʽ��ֻ����emSdkClrTmpMode�ж����һ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetClrTempMode)(
  CameraHandle  hCamera,
  int       iMode
);

/******************************************************/
// ������   : CameraGetClrTempMode
// �������� : ��ð�ƽ��ʱʹ�õ�ɫ��ģʽ���ο�CameraSetClrTempMode
//              �й����������֡�
// ����     : hCamera ����ľ������CameraInit������á�
//            pimode ָ�룬����ģʽѡ�񣬲ο�emSdkClrTmpMode���Ͷ���
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetClrTempMode)(
  CameraHandle  hCamera,
  int*      pimode
);


/******************************************************/
// ������   : CameraSetOnceWB
// �������� : ���ֶ���ƽ��ģʽ�£����øú��������һ�ΰ�ƽ�⡣
//        ��Ч��ʱ��Ϊ���յ���һ֡ͼ������ʱ��
// ����     : hCamera  ����ľ������CameraInit������á�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetOnceWB)(
    CameraHandle    hCamera
);

/******************************************************/
// ������   : CameraSetOnceBB
// �������� : ִ��һ�κ�ƽ�������
// ����     : hCamera  ����ľ������CameraInit������á�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetOnceBB)(
    CameraHandle    hCamera
);


/******************************************************/
// ������   : CameraSetAeTarget
// �������� : �趨�Զ��ع������Ŀ��ֵ���趨��Χ��CameraGetCapability
//        ������á�
// ����     : hCamera  ����ľ������CameraInit������á�
//            iAeTarget  ����Ŀ��ֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetAeTarget)(
    CameraHandle    hCamera, 
    int             iAeTarget
);

/******************************************************/
// ������   : CameraGetAeTarget
// �������� : ����Զ��ع������Ŀ��ֵ��
// ����     : hCamera   ����ľ������CameraInit������á�
//            *piAeTarget ָ�룬����Ŀ��ֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetAeTarget)(
    CameraHandle    hCamera, 
    int*            piAeTarget
);

/******************************************************/
// ������   : CameraSetExposureTime
// �������� : �����ع�ʱ�䡣��λΪ΢�롣����CMOS�����������ع�
//        �ĵ�λ�ǰ�����������ģ���ˣ��ع�ʱ�䲢������΢��
//        ���������ɵ������ǻᰴ��������ȡ�ᡣ�ڵ���
//        �������趨�ع�ʱ��󣬽����ٵ���CameraGetExposureTime
//        �����ʵ���趨��ֵ��
// ����     : hCamera      ����ľ������CameraInit������á�
//            fExposureTime �ع�ʱ�䣬��λ΢�롣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetExposureTime)(
    CameraHandle    hCamera, 
    double          fExposureTime
);

//******************************************************/
// ������   : CameraGetExposureLineTime
// �������� : ���һ�е��ع�ʱ�䡣����CMOS�����������ع�
//        �ĵ�λ�ǰ�����������ģ���ˣ��ع�ʱ�䲢������΢��
//        ���������ɵ������ǻᰴ��������ȡ�ᡣ���������
//          ���þ��Ƿ���CMOS����ع�һ�ж�Ӧ��ʱ�䡣
// ����     : hCamera  ����ľ������CameraInit������á�
//            double *pfLineTime ָ�룬����һ�е��ع�ʱ�䣬��λΪ΢�롣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/

typedef    CameraSdkStatus (__stdcall *_CameraGetExposureLineTime)(
    CameraHandle    hCamera, 
    double*         pfLineTime
);

/******************************************************/
// ������   : CameraGetExposureTime
// �������� : ���������ع�ʱ�䡣��μ�CameraSetExposureTime
//        �Ĺ���������
// ����     : hCamera        ����ľ������CameraInit������á�
//            pfExposureTime  ָ�룬���ص�ǰ���ع�ʱ�䣬��λ΢�롣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetExposureTime)(
    CameraHandle    hCamera, 
    double*         pfExposureTime
);

/******************************************************/
// ������   : CameraSetAnalogGain
// �������� : ���������ͼ��ģ������ֵ����ֵ����CameraGetCapability���
//        ��������Խṹ����sExposeDesc.fAnalogGainStep����
//        �õ�ʵ�ʵ�ͼ���źŷŴ�����
// ����     : hCamera   ����ľ������CameraInit������á�
//            iAnalogGain �趨��ģ������ֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetAnalogGain)(
    CameraHandle    hCamera,
    INT             iAnalogGain
);

/******************************************************/
// ������   : CameraGetAnalogGain
// �������� : ���ͼ���źŵ�ģ������ֵ���μ�CameraSetAnalogGain
//        ��ϸ˵����
// ����     : hCamera    ����ľ������CameraInit������á�
//            piAnalogGain ָ�룬���ص�ǰ��ģ������ֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetAnalogGain)(
    CameraHandle    hCamera, 
    INT*            piAnalogGain
);

/******************************************************/
// ������   : CameraSetGain
// �������� : ����ͼ����������档�趨��Χ��CameraGetCapability
//        ��õ�������Խṹ����sRgbGainRange��Ա������
//        ʵ�ʵķŴ������趨ֵ/100��
// ����     : hCamera  ����ľ������CameraInit������á�
//            iRGain   ��ɫͨ��������ֵ�� 
//            iGGain   ��ɫͨ��������ֵ��
//            iBGain   ��ɫͨ��������ֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetGain)(
    CameraHandle    hCamera, 
    int             iRGain, 
    int             iGGain, 
    int             iBGain
);


/******************************************************/
// ������   : CameraGetGain
// �������� : ���ͼ������������档������μ�CameraSetGain
//        �Ĺ����������֡�
// ����     : hCamera  ����ľ������CameraInit������á�
//            piRGain  ָ�룬���غ�ɫͨ������������ֵ��
//            piGGain    ָ�룬������ɫͨ������������ֵ��
//            piBGain    ָ�룬������ɫͨ������������ֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetGain)(
    CameraHandle    hCamera, 
    int*            piRGain, 
    int*            piGGain, 
    int*            piBGain
);


/******************************************************/
// ������   : CameraSetGamma
// �������� : �趨LUT��̬����ģʽ�µ�Gammaֵ���趨��ֵ��
//        ���ϱ�����SDK�ڲ�������ֻ�е�������ڶ�̬
//        �������ɵ�LUTģʽʱ���Ż���Ч����ο�CameraSetLutMode
//        �ĺ���˵�����֡�
// ����     : hCamera  ����ľ������CameraInit������á�
//            iGamma     Ҫ�趨��Gammaֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetGamma)(
    CameraHandle    hCamera, 
    int             iGamma
);

/******************************************************/
// ������   : CameraGetGamma
// �������� : ���LUT��̬����ģʽ�µ�Gammaֵ����ο�CameraSetGamma
//        �����Ĺ���������
// ����     : hCamera  ����ľ������CameraInit������á�
//            piGamma    ָ�룬���ص�ǰ��Gammaֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetGamma)(
    CameraHandle    hCamera, 
    int*            piGamma
);

/******************************************************/
// ������   : CameraSetContrast
// �������� : �趨LUT��̬����ģʽ�µĶԱȶ�ֵ���趨��ֵ��
//        ���ϱ�����SDK�ڲ�������ֻ�е�������ڶ�̬
//        �������ɵ�LUTģʽʱ���Ż���Ч����ο�CameraSetLutMode
//        �ĺ���˵�����֡�
// ����     : hCamera  ����ľ������CameraInit������á�
//            iContrast  �趨�ĶԱȶ�ֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetContrast)(
    CameraHandle    hCamera, 
    int             iContrast
);

/******************************************************/
// ������   : CameraGetContrast
// �������� : ���LUT��̬����ģʽ�µĶԱȶ�ֵ����ο�
//        CameraSetContrast�����Ĺ���������
// ����     : hCamera  ����ľ������CameraInit������á�
//            piContrast ָ�룬���ص�ǰ�ĶԱȶ�ֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetContrast)(
    CameraHandle    hCamera, 
    int*            piContrast
);

/******************************************************/
// ������   : CameraSetSaturation
// �������� : �趨ͼ����ı��Ͷȡ��Ժڰ������Ч��
//        �趨��Χ��CameraGetCapability��á�100��ʾ
//        ��ʾԭʼɫ�ȣ�����ǿ��
// ����     : hCamera    ����ľ������CameraInit������á�
//            iSaturation  �趨�ı��Ͷ�ֵ�� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetSaturation)(
    CameraHandle    hCamera, 
    int             iSaturation
);

/******************************************************/
// ������   : CameraGetSaturation
// �������� : ���ͼ����ı��Ͷȡ�
// ����     : hCamera    ����ľ������CameraInit������á�
//            piSaturation ָ�룬���ص�ǰͼ����ı��Ͷ�ֵ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetSaturation)(
    CameraHandle    hCamera, 
    int*            piSaturation
);

/******************************************************/
// ������   : CameraSetMonochrome
// �������� : ���ò�ɫתΪ�ڰ׹��ܵ�ʹ�ܡ�
// ����     : hCamera ����ľ������CameraInit������á�
//            bEnable   TRUE����ʾ����ɫͼ��תΪ�ڰס�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetMonochrome)(
    CameraHandle    hCamera, 
    BOOL            bEnable
);

/******************************************************/
// ������   : CameraGetMonochrome
// �������� : ��ò�ɫת���ڰ׹��ܵ�ʹ��״����
// ����     : hCamera  ����ľ������CameraInit������á�
//            pbEnable   ָ�롣����TRUE��ʾ�����˲�ɫͼ��
//             ת��Ϊ�ڰ�ͼ��Ĺ��ܡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetMonochrome)(
    CameraHandle    hCamera, 
    BOOL*           pbEnable
);

/******************************************************/
// ������   : CameraSetInverse
// �������� : ���ò�ͼ����ɫ��ת���ܵ�ʹ�ܡ�
// ����     : hCamera  ����ľ������CameraInit������á�
//            bEnable    TRUE����ʾ����ͼ����ɫ��ת���ܣ�
//             ���Ի�����ƽ����Ƭ��Ч����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetInverse)(
    CameraHandle    hCamera, 
    BOOL            bEnable
);

/******************************************************/
// ������   : CameraGetInverse
// �������� : ���ͼ����ɫ��ת���ܵ�ʹ��״̬��
// ����     : hCamera  ����ľ������CameraInit������á�
//            pbEnable   ָ�룬���ظù���ʹ��״̬�� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetInverse)(
    CameraHandle    hCamera, 
    BOOL*           pbEnable
);

/******************************************************/
// ������   : CameraSetAntiFlick
// �������� : �����Զ��ع�ʱ��Ƶ�����ܵ�ʹ��״̬�������ֶ�
//        �ع�ģʽ����Ч��
// ����     : hCamera  ����ľ������CameraInit������á�
//            bEnable    TRUE��������Ƶ������;FALSE���رոù��ܡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetAntiFlick)(
    CameraHandle    hCamera,
    BOOL            bEnable
);

/******************************************************/
// ������   : CameraGetAntiFlick
// �������� : ����Զ��ع�ʱ��Ƶ�����ܵ�ʹ��״̬��
// ����     : hCamera  ����ľ������CameraInit������á�
//            pbEnable   ָ�룬���ظù��ܵ�ʹ��״̬��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetAntiFlick)(
    CameraHandle    hCamera, 
    BOOL*           pbEnable
);

/******************************************************/
// ������   : CameraGetLightFrequency
// �������� : ����Զ��ع�ʱ����Ƶ����Ƶ��ѡ��
// ����     : hCamera      ����ľ������CameraInit������á�
//            piFrequencySel ָ�룬����ѡ��������š�0:50HZ 1:60HZ
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetLightFrequency)(
    CameraHandle    hCamera, 
    int*            piFrequencySel
);

/******************************************************/
// ������   : CameraSetLightFrequency
// �������� : �����Զ��ع�ʱ��Ƶ����Ƶ�ʡ�
// ����     : hCamera     ����ľ������CameraInit������á�
//            iFrequencySel 0:50HZ , 1:60HZ 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetLightFrequency)(
    CameraHandle    hCamera,
    int             iFrequencySel
);

/******************************************************/
// ������   : CameraSetFrameSpeed
// �������� : �趨������ͼ���֡�ʡ�����ɹ�ѡ���֡��ģʽ��
//        CameraGetCapability��õ���Ϣ�ṹ����iFrameSpeedDesc
//        ��ʾ���֡��ѡ��ģʽ������
// ����     : hCamera   ����ľ������CameraInit������á�
//            iFrameSpeed ѡ���֡��ģʽ�����ţ���Χ��0��
//              CameraGetCapability��õ���Ϣ�ṹ����iFrameSpeedDesc - 1   
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetFrameSpeed)(
    CameraHandle    hCamera, 
    int             iFrameSpeed
);

/******************************************************/
// ������   : CameraGetFrameSpeed
// �������� : ���������ͼ���֡��ѡ�������š������÷��ο�
//        CameraSetFrameSpeed�����Ĺ����������֡�
// ����     : hCamera    ����ľ������CameraInit������á�
//            piFrameSpeed ָ�룬����ѡ���֡��ģʽ�����š� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetFrameSpeed)(
    CameraHandle    hCamera, 
    int*            piFrameSpeed
);


/******************************************************/
// ������   : CameraSetParameterMode
// �������� : �趨������ȡ��Ŀ�����
// ����     : hCamera  ����ľ������CameraInit������á�
//            iMode  ������ȡ�Ķ��󡣲ο�CameraDefine.h
//          ��emSdkParameterMode�����Ͷ��塣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetParameterMode)(
    CameraHandle    hCamera, 
    int             iTarget
);

/******************************************************/
// ������   : CameraGetParameterMode
// �������� : 
// ����     : hCamera  ����ľ������CameraInit������á�
//            int* piTarget
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetParameterMode)(
    CameraHandle    hCamera, 
    int*            piTarget
);

/******************************************************/
// ������   : CameraSetParameterMask
// �������� : ���ò�����ȡ�����롣�������غͱ���ʱ����ݸ�
//        ��������������ģ��������Ƿ���ػ��߱��档
// ����     : hCamera ����ľ������CameraInit������á�
//            uMask     ���롣�ο�CameraDefine.h��PROP_SHEET_INDEX
//            ���Ͷ��塣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetParameterMask)(
    CameraHandle    hCamera, 
    UINT            uMask
);

/******************************************************/
// ������   : CameraSaveParameter
// �������� : ���浱ǰ���������ָ���Ĳ������С�����ṩ��A,B,C,D
//        A,B,C,D����ռ������в����ı��档 
// ����     : hCamera  ����ľ������CameraInit������á�
//            iTeam      PARAMETER_TEAM_A ���浽A����,
//             PARAMETER_TEAM_B ���浽B����,
//             PARAMETER_TEAM_C ���浽C����,
//             PARAMETER_TEAM_D ���浽D����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSaveParameter)(
    CameraHandle    hCamera, 
    int             iTeam
);

/******************************************************/
// ������   : CameraReadParameterFromFile
// �������� : ��PC��ָ���Ĳ����ļ��м��ز������ҹ�˾�������
//        ������PC��Ϊ.config��׺���ļ���λ�ڰ�װ�µ�
//        Camera\Configs�ļ����С�
// ����     : hCamera  ����ľ������CameraInit������á�
//            *sFileName �����ļ�������·����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraReadParameterFromFile)(
    CameraHandle    hCamera,
    char*           sFileName
);

/******************************************************/
// ������   : CameraLoadParameter
// �������� : ����ָ����Ĳ���������С�
// ����     : hCamera  ����ľ������CameraInit������á�
//            iTeam    PARAMETER_TEAM_A ����A�����,
//             PARAMETER_TEAM_B ����B�����,
//             PARAMETER_TEAM_C ����C�����,
//             PARAMETER_TEAM_D ����D�����,
//             PARAMETER_TEAM_DEFAULT ����Ĭ�ϲ�����    
//             ���Ͷ���ο�CameraDefine.h��emSdkParameterTeam����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraLoadParameter)(
    CameraHandle    hCamera, 
    int             iTeam
);

/******************************************************/
// ������   : CameraGetCurrentParameterGroup
// �������� : ��õ�ǰѡ��Ĳ����顣
// ����     : hCamera  ����ľ������CameraInit������á�
//            piTeam     ָ�룬���ص�ǰѡ��Ĳ����顣����ֵ
//             �ο�CameraLoadParameter��iTeam������
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetCurrentParameterGroup)(
    CameraHandle    hCamera, 
    int*            piTeam
);

/******************************************************/
// ������   : CameraSetTransPackLen
// �������� : �����������ͼ�����ݵķְ���С��
//        Ŀǰ��SDK�汾�У��ýӿڽ���GIGE�ӿ������Ч��
//        �����������紫��ķְ���С������֧�־�֡��������
//        ���ǽ���ѡ��8K�ķְ���С��������Ч�Ľ��ʹ���
//        ��ռ�õ�CPU����ʱ�䡣
// ����     : hCamera  ����ľ������CameraInit������á�
//            iPackSel   �ְ�����ѡ��������š��ְ����ȿ���
//             ���������Խṹ����pPackLenDesc��Ա������
//             iPackLenDesc��Ա���ʾ����ѡ�ķְ�ģʽ������
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetTransPackLen)(
    CameraHandle    hCamera, 
    INT             iPackSel
);

/******************************************************/
// ������   : CameraGetTransPackLen
// �������� : ��������ǰ����ְ���С��ѡ�������š�
// ����     : hCamera  ����ľ������CameraInit������á�
//            piPackSel  ָ�룬���ص�ǰѡ��ķְ���С�����š�
//             �μ�CameraSetTransPackLen��iPackSel��
//             ˵����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetTransPackLen)(
    CameraHandle    hCamera, 
    INT*            piPackSel
);

/******************************************************/
// ������   : CameraIsAeWinVisible
// �������� : ����Զ��ع�ο����ڵ���ʾ״̬��
// ����     : hCamera    ����ľ������CameraInit������á�
//            pbIsVisible  ָ�룬����TRUE�����ʾ��ǰ���ڻ�
//               ��������ͼ�������ϡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraIsAeWinVisible)(
    CameraHandle    hCamera,
    BOOL*           pbIsVisible
);

/******************************************************/
// ������   : CameraSetAeWinVisible
// �������� : �����Զ��ع�ο����ڵ���ʾ״̬�������ô���״̬
//        Ϊ��ʾ������CameraImageOverlay���ܹ�������λ��
//        �Ծ��εķ�ʽ������ͼ���ϡ�
// ����     : hCamera   ����ľ������CameraInit������á�
//            bIsVisible  TRUE������Ϊ��ʾ��FALSE������ʾ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetAeWinVisible)(
    CameraHandle    hCamera,
    BOOL            bIsVisible
);

/******************************************************/
// ������   : CameraGetAeWindow
// �������� : ����Զ��ع�ο����ڵ�λ�á�
// ����     : hCamera  ����ľ������CameraInit������á�
//            piHOff     ָ�룬���ش���λ�����ϽǺ�����ֵ��
//            piVOff     ָ�룬���ش���λ�����Ͻ�������ֵ��
//            piWidth    ָ�룬���ش��ڵĿ�ȡ�
//            piHeight   ָ�룬���ش��ڵĸ߶ȡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetAeWindow)(
    CameraHandle    hCamera, 
    INT*            piHOff, 
    INT*            piVOff, 
    INT*            piWidth, 
    INT*            piHeight
);

/******************************************************/
// ������   : CameraSetAeWindow
// �������� : �����Զ��ع�Ĳο����ڡ�
// ����     : hCamera  ����ľ������CameraInit������á�
//            iHOff    �������Ͻǵĺ�����
//            iVOff      �������Ͻǵ�������
//            iWidth     ���ڵĿ�� 
//            iHeight    ���ڵĸ߶�
//        ���iHOff��iVOff��iWidth��iHeightȫ��Ϊ0����
//        ��������Ϊÿ���ֱ����µľ���1/2��С����������
//        �ֱ��ʵı仯������仯�����iHOff��iVOff��iWidth��iHeight
//        �������Ĵ���λ�÷�Χ�����˵�ǰ�ֱ��ʷ�Χ�ڣ� 
//          ���Զ�ʹ�þ���1/2��С���ڡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetAeWindow)(
    CameraHandle    hCamera, 
    int             iHOff, 
    int             iVOff, 
    int             iWidth, 
    int             iHeight
);

/******************************************************/
// ������   : CameraSetMirror
// �������� : ����ͼ������������������Ϊˮƽ�ʹ�ֱ��������
// ����     : hCamera  ����ľ������CameraInit������á�
//            iDir     ��ʾ����ķ���0����ʾˮƽ����1����ʾ��ֱ����
//            bEnable  TRUE��ʹ�ܾ���;FALSE����ֹ����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetMirror)(
    CameraHandle    hCamera, 
    int             iDir, 
    BOOL            bEnable
);

/******************************************************/
// ������   : CameraGetMirror
// �������� : ���ͼ��ľ���״̬��
// ����     : hCamera  ����ľ������CameraInit������á�
//            iDir     ��ʾҪ��õľ�����
//             0����ʾˮƽ����1����ʾ��ֱ����
//            pbEnable   ָ�룬����TRUE�����ʾiDir��ָ�ķ���
//             ����ʹ�ܡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetMirror)(
    CameraHandle    hCamera, 
    int             iDir, 
    BOOL*           pbEnable
);

/******************************************************/
// ������   : CameraGetWbWindow
// �������� : ��ð�ƽ��ο����ڵ�λ�á�
// ����     : hCamera  ����ľ������CameraInit������á�
//            PiHOff   ָ�룬���زο����ڵ����ϽǺ����� ��
//            PiVOff     ָ�룬���زο����ڵ����Ͻ������� ��
//            PiWidth    ָ�룬���زο����ڵĿ�ȡ�
//            PiHeight   ָ�룬���زο����ڵĸ߶ȡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetWbWindow)(
    CameraHandle    hCamera, 
    INT*            PiHOff, 
    INT*            PiVOff, 
    INT*            PiWidth, 
    INT*            PiHeight
);

/******************************************************/
// ������   : CameraSetWbWindow
// �������� : ���ð�ƽ��ο����ڵ�λ�á�
// ����     : hCamera ����ľ������CameraInit������á�
//            iHOff   �ο����ڵ����ϽǺ����ꡣ
//            iVOff     �ο����ڵ����Ͻ������ꡣ
//            iWidth    �ο����ڵĿ�ȡ�
//            iHeight   �ο����ڵĸ߶ȡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetWbWindow)(
    CameraHandle    hCamera, 
    INT             iHOff, 
    INT             iVOff, 
    INT             iWidth, 
    INT             iHeight
);

/******************************************************/
// ������   : CameraIsWbWinVisible
// �������� : ��ð�ƽ�ⴰ�ڵ���ʾ״̬��
// ����     : hCamera  ����ľ������CameraInit������á�
//            pbShow   ָ�룬����TRUE�����ʾ�����ǿɼ��ġ� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraIsWbWinVisible)(
    CameraHandle    hCamera,
    BOOL*           pbShow
);

/******************************************************/
// ������   : CameraSetWbWinVisible
// �������� : ���ð�ƽ�ⴰ�ڵ���ʾ״̬��
// ����     : hCamera  ����ľ������CameraInit������á�
//            bShow      TRUE�����ʾ����Ϊ�ɼ����ڵ���
//             CameraImageOverlay��ͼ�������Ͻ��Ծ���
//             �ķ�ʽ���Ӱ�ƽ��ο����ڵ�λ�á�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetWbWinVisible)(
    CameraHandle    hCamera, 
    BOOL            bShow
);

/******************************************************/
// ������   : CameraImageOverlay
// �������� : �������ͼ�������ϵ���ʮ���ߡ���ƽ��ο����ڡ�
//        �Զ��ع�ο����ڵ�ͼ�Ρ�ֻ������Ϊ�ɼ�״̬��
//        ʮ���ߺͲο����ڲ��ܱ������ϡ�
//        ע�⣬�ú���������ͼ�������RGB��ʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            pRgbBuffer ͼ�����ݻ�������
//            pFrInfo    ͼ���֡ͷ��Ϣ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraImageOverlay)(
    CameraHandle    hCamera,
    BYTE*           pRgbBuffer,
    tSdkFrameHead*  pFrInfo
);

/******************************************************/
// ������   : CameraSetCrossLine
// �������� : ����ָ��ʮ���ߵĲ�����
// ����     : hCamera  ����ľ������CameraInit������á�
//            iLine    ��ʾҪ���õڼ���ʮ���ߵ�״̬����ΧΪ[0,8]����9����    
//            x          ʮ��������λ�õĺ�����ֵ��
//            y      ʮ��������λ�õ�������ֵ��
//            uColor     ʮ���ߵ���ɫ����ʽΪ(R|(G<<8)|(B<<16))
//            bVisible   ʮ���ߵ���ʾ״̬��TRUE����ʾ��ʾ��
//             ֻ������Ϊ��ʾ״̬��ʮ���ߣ��ڵ���
//             CameraImageOverlay��Żᱻ���ӵ�ͼ���ϡ�     
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetCrossLine)(
    CameraHandle    hCamera, 
    int             iLine, 
    INT             x,
    INT             y,
    UINT            uColor,
    BOOL            bVisible
);

/******************************************************/
// ������   : CameraGetCrossLine
// �������� : ���ָ��ʮ���ߵ�״̬��
// ����     : hCamera  ����ľ������CameraInit������á�
//            iLine    ��ʾҪ��ȡ�ĵڼ���ʮ���ߵ�״̬����ΧΪ[0,8]����9����  
//            px     ָ�룬���ظ�ʮ��������λ�õĺ����ꡣ
//            py     ָ�룬���ظ�ʮ��������λ�õĺ����ꡣ
//            pcolor     ָ�룬���ظ�ʮ���ߵ���ɫ����ʽΪ(R|(G<<8)|(B<<16))��
//            pbVisible  ָ�룬����TRUE�����ʾ��ʮ���߿ɼ���
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetCrossLine)(
    CameraHandle    hCamera, 
    INT             iLine,
    INT*            px,
    INT*            py,
    UINT*           pcolor,
    BOOL*           pbVisible
);

/******************************************************/
// ������   : CameraGetCapability
// �������� : �����������������ṹ�塣�ýṹ���а��������
//        �����õĸ��ֲ����ķ�Χ��Ϣ����������غ����Ĳ���
//        ���أ�Ҳ�����ڶ�̬������������ý��档
// ����     : hCamera   ����ľ������CameraInit������á�
//            pCameraInfo ָ�룬���ظ�������������Ľṹ�塣
//                        tSdkCameraCapbility��CameraDefine.h�ж��塣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetCapability)(
    CameraHandle            hCamera, 
    tSdkCameraCapbility*    pCameraInfo
);

/******************************************************/
// ������   : CameraWriteSN
// �������� : ������������кš��ҹ�˾������кŷ�Ϊ3����
//        0�������ҹ�˾�Զ����������кţ�����ʱ�Ѿ�
//        �趨�ã�1����2���������ο���ʹ�á�ÿ������
//        �ų��ȶ���32���ֽڡ�
// ����     : hCamera  ����ľ������CameraInit������á�
//            pbySN    ���кŵĻ������� 
//            iLevel   Ҫ�趨�����кż���ֻ����1����2��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraWriteSN)(
    CameraHandle    hCamera, 
    BYTE*           pbySN, 
    INT             iLevel
);

/******************************************************/
// ������   : CameraReadSN
// �������� : ��ȡ���ָ����������кš����кŵĶ�����ο�
//          CameraWriteSN�����Ĺ����������֡�
// ����     : hCamera  ����ľ������CameraInit������á�
//            pbySN    ���кŵĻ�������
//            iLevel     Ҫ��ȡ�����кż���ֻ����1��2��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraReadSN)(
    CameraHandle        hCamera, 
    BYTE*               pbySN, 
    INT                 iLevel
);
/******************************************************/
// ������   : CameraSetTriggerDelayTime
// �������� : ����Ӳ������ģʽ�µĴ�����ʱʱ�䣬��λ΢�롣
//        ��Ӳ�����ź����ٺ󣬾���ָ������ʱ���ٿ�ʼ�ɼ�
//        ͼ�񡣽������ͺŵ����֧�ָù��ܡ�������鿴
//        ��Ʒ˵���顣
// ����     : hCamera    ����ľ������CameraInit������á�
//            uDelayTimeUs Ӳ������ʱ����λ΢�롣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetTriggerDelayTime)(
    CameraHandle    hCamera, 
    UINT            uDelayTimeUs
);

/******************************************************/
// ������   : CameraGetTriggerDelayTime
// �������� : ��õ�ǰ�趨��Ӳ������ʱʱ�䡣
// ����     : hCamera     ����ľ������CameraInit������á�
//            puDelayTimeUs ָ�룬������ʱʱ�䣬��λ΢�롣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetTriggerDelayTime)(
    CameraHandle    hCamera, 
    UINT*           puDelayTimeUs
);

/******************************************************/
// ������   : CameraSetTriggerCount
// �������� : ���ô���ģʽ�µĴ���֡���������������Ӳ������
//        ģʽ����Ч��Ĭ��Ϊ1֡����һ�δ����źŲɼ�һ֡ͼ��
// ����     : hCamera ����ľ������CameraInit������á�
//            iCount    һ�δ����ɼ���֡����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetTriggerCount)(
    CameraHandle    hCamera, 
    INT             iCount
);

/******************************************************/
// ������   : CameraGetTriggerCount
// �������� : ���һ�δ�����֡����
// ����     : hCamera  ����ľ������CameraInit������á�
//            INT* piCount
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetTriggerCount)(
    CameraHandle    hCamera, 
    INT*            piCount
);

/******************************************************/
// ������   : CameraSoftTrigger
// �������� : ִ��һ��������ִ�к󣬻ᴥ����CameraSetTriggerCount
//          ָ����֡����
// ����     : hCamera  ����ľ������CameraInit������á�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSoftTrigger)(
    CameraHandle    hCamera
);

/******************************************************/
// ������   : CameraSetTriggerMode
// �������� : ��������Ĵ���ģʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            iModeSel   ģʽѡ�������š����趨��ģʽ��
//             CameraGetCapability������ȡ����ο�
//               CameraDefine.h��tSdkCameraCapbility�Ķ��塣
//             һ�������0��ʾ�����ɼ�ģʽ��1��ʾ
//             �������ģʽ��2��ʾӲ������ģʽ��  
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetTriggerMode)(
    CameraHandle    hCamera, 
    int             iModeSel
);

/******************************************************/
// ������   : CameraGetTriggerMode
// �������� : �������Ĵ���ģʽ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            piModeSel  ָ�룬���ص�ǰѡ����������ģʽ�������š�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetTriggerMode)(
    CameraHandle    hCamera,
    INT*            piModeSel
);

/******************************************************/
// ������ 	: CameraSetStrobeMode
// ��������	: ����IO���Ŷ����ϵ�STROBE�źš����źſ���������ƿ��ƣ�Ҳ�������ⲿ��е���ſ��ơ�
// ����	    : hCamera ����ľ������CameraInit������á�
//             iMode   ��ΪSTROBE_SYNC_WITH_TRIG_AUTO      �ʹ����ź�ͬ������������������ع�ʱ���Զ�����STROBE�źš�
//                                                         ��ʱ����Ч���Կ�����(CameraSetStrobePolarity)��
//                     ��ΪSTROBE_SYNC_WITH_TRIG_MANUALʱ���ʹ����ź�ͬ����������STROBE��ʱָ����ʱ���(CameraSetStrobeDelayTime)��
//                                                         �ٳ���ָ��ʱ�������(CameraSetStrobePulseWidth)��
//                                                         ��Ч���Կ�����(CameraSetStrobePolarity)��
//                     ��ΪSTROBE_ALWAYS_HIGHʱ��STROBE�źź�Ϊ��,������������
//                     ��ΪSTROBE_ALWAYS_LOWʱ��STROBE�źź�Ϊ��,������������
//
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetStrobeMode)(
    CameraHandle    hCamera, 
    INT             iMode
);

/******************************************************/
// ������ 	: CameraGetStrobeMode
// ��������	: ���ߵ�ǰSTROBE�ź����õ�ģʽ��
// ����	    : hCamera ����ľ������CameraInit������á�
//             piMode  ָ�룬����STROBE_SYNC_WITH_TRIG_AUTO,STROBE_SYNC_WITH_TRIG_MANUAL��STROBE_ALWAYS_HIGH����STROBE_ALWAYS_LOW��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetStrobeMode)(
    CameraHandle    hCamera, 
    INT*            piMode
);

/******************************************************/
// ������ 	: CameraSetStrobeDelayTime
// ��������	: ��STROBE�źŴ���STROBE_SYNC_WITH_TRIGʱ��ͨ���ú�����������Դ����ź���ʱʱ�䡣
// ����	    : hCamera       ����ľ������CameraInit������á�
//             uDelayTimeUs  ��Դ����źŵ���ʱʱ�䣬��λΪus������Ϊ0��������Ϊ������ 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetStrobeDelayTime)(
    CameraHandle    hCamera, 
    UINT            uDelayTimeUs
);

/******************************************************/
// ������ 	: CameraGetStrobeDelayTime
// ��������	: ��STROBE�źŴ���STROBE_SYNC_WITH_TRIGʱ��ͨ���ú����������Դ����ź���ʱʱ�䡣
// ����	    : hCamera           ����ľ������CameraInit������á�
//             upDelayTimeUs     ָ�룬������ʱʱ�䣬��λus��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetStrobeDelayTime)(
    CameraHandle    hCamera, 
    UINT*           upDelayTimeUs
);

/******************************************************/
// ������ 	: CameraSetStrobePulseWidth
// ��������	: ��STROBE�źŴ���STROBE_SYNC_WITH_TRIGʱ��ͨ���ú��������������ȡ�
// ����	    : hCamera       ����ľ������CameraInit������á�
//             uTimeUs       ����Ŀ�ȣ���λΪʱ��us��  
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetStrobePulseWidth)(
    CameraHandle    hCamera, 
    UINT            uTimeUs
);

/******************************************************/
// ������ 	: CameraGetStrobePulseWidth
// ��������	: ��STROBE�źŴ���STROBE_SYNC_WITH_TRIGʱ��ͨ���ú�������������ȡ�
// ����	    : hCamera   ����ľ������CameraInit������á�
//             upTimeUs  ָ�룬���������ȡ���λΪʱ��us��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetStrobePulseWidth)(
    CameraHandle    hCamera, 
    UINT*           upTimeUs
);


/******************************************************/
// ������ 	: CameraSetStrobePolarity
// ��������	: ��STROBE�źŴ���STROBE_SYNC_WITH_TRIGʱ��ͨ���ú�����������Ч��ƽ�ļ��ԡ�Ĭ��Ϊ����Ч���������źŵ���ʱ��STROBE�źű����ߡ�
// ����	    : hCamera   ����ľ������CameraInit������á�
//             iPolarity STROBE�źŵļ��ԣ�0Ϊ�͵�ƽ��Ч��1Ϊ�ߵ�ƽ��Ч��Ĭ��Ϊ�ߵ�ƽ��Ч��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetStrobePolarity)(
    CameraHandle    hCamera, 
    INT             iPolarity
);

/******************************************************/
// ������ 	: CameraGetStrobePolarity
// ��������	: ��������ǰSTROBE�źŵ���Ч���ԡ�Ĭ��Ϊ�ߵ�ƽ��Ч��
// ����	    : hCamera       ����ľ������CameraInit������á�
//             ipPolarity    ָ�룬����STROBE�źŵ�ǰ����Ч���ԡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetStrobePolarity)(
    CameraHandle    hCamera, 
    INT*            ipPolarity
);

/******************************************************/
// ������ 	: CameraSetExtTrigSignalType
// ��������	: ��������ⴥ���źŵ����ࡣ�ϱ��ء��±��ء����߸ߡ��͵�ƽ��ʽ��
// ����	    : hCamera   ����ľ������CameraInit������á�
//             iType     �ⴥ���ź����࣬����ֵ�ο�CameraDefine.h��
//                       emExtTrigSignal���Ͷ��塣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetExtTrigSignalType)(
    CameraHandle    hCamera, 
    INT             iType
);

/******************************************************/
// ������ 	: CameraGetExtTrigSignalType
// ��������	: ��������ǰ�ⴥ���źŵ����ࡣ
// ����	    : hCamera   ����ľ������CameraInit������á�
//             ipType    ָ�룬�����ⴥ���ź����࣬����ֵ�ο�CameraDefine.h��
//                       emExtTrigSignal���Ͷ��塣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetExtTrigSignalType)(
    CameraHandle    hCamera, 
    INT*            ipType
);

/******************************************************/
// ������ 	: CameraSetExtTrigShutterType
// ��������	: �����ⴥ��ģʽ�£�������ŵķ�ʽ��Ĭ��Ϊ��׼���ŷ�ʽ��
//              ���ֹ������ŵ�CMOS���֧��GRR��ʽ��
// ����	    : hCamera   ����ľ������CameraInit������á�
//             iType     �ⴥ�����ŷ�ʽ���ο�CameraDefine.h��emExtTrigShutterMode���͡�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetExtTrigShutterType)(
    CameraHandle    hCamera, 
    INT             iType
);

/******************************************************/
// ������ 	: CameraSetExtTrigShutterType
// ��������	: ����ⴥ��ģʽ�£�������ŵķ�ʽ��Ĭ��Ϊ��׼���ŷ�ʽ��
//              ���ֹ������ŵ�CMOS���֧��GRR��ʽ��
// ����	    : hCamera   ����ľ������CameraInit������á�
//             ipType    ָ�룬���ص�ǰ�趨���ⴥ�����ŷ�ʽ������ֵ�ο�
//                       CameraDefine.h��emExtTrigShutterMode���͡�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetExtTrigShutterType)(
    CameraHandle    hCamera, 
    INT*            ipType
);

/******************************************************/
// ������ 	: CameraSetExtTrigDelayTime
// ��������	: �����ⴥ���ź���ʱʱ�䣬Ĭ��Ϊ0����λΪ΢�롣 
//              �����õ�ֵuDelayTimeUs��Ϊ0ʱ��������յ��ⴥ���źź󣬽���ʱuDelayTimeUs��΢����ٽ���ͼ�񲶻�
// ����	    : hCamera       ����ľ������CameraInit������á�
//             uDelayTimeUs  ��ʱʱ�䣬��λΪ΢�룬Ĭ��Ϊ0.
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetExtTrigDelayTime)(
    CameraHandle    hCamera, 
    UINT            uDelayTimeUs
);

/******************************************************/
// ������ 	: CameraGetExtTrigDelayTime
// ��������	: ������õ��ⴥ���ź���ʱʱ�䣬Ĭ��Ϊ0����λΪ΢�롣 
// ����	    : hCamera   ����ľ������CameraInit������á�
//            UINT* upDelayTimeUs
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetExtTrigDelayTime)(
    CameraHandle    hCamera, 
    UINT*           upDelayTimeUs
);

/******************************************************/
// ������ 	: CameraSetExtTrigJitterTime
// ��������	: ��������ⴥ���źŵ�����ʱ�䡣Ĭ��Ϊ0����λΪ΢�롣
// ����	    : hCamera   ����ľ������CameraInit������á�
//            UINT uTimeUs
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetExtTrigJitterTime)(
    CameraHandle    hCamera,
    UINT            uTimeUs
);

/******************************************************/
// ������ 	: CameraGetExtTrigJitterTime
// ��������	: ������õ�����ⴥ������ʱ�䣬Ĭ��Ϊ0.��λΪ΢��
// ����	    : hCamera   ����ľ������CameraInit������á�
//            UINT* upTimeUs
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetExtTrigJitterTime)(
    CameraHandle    hCamera,
    UINT*           upTimeUs
);

/******************************************************/
// ������ 	: CameraGetExtTrigCapability
// ��������	: �������ⴥ������������
// ����	    : hCamera           ����ľ������CameraInit������á�
//             puCapabilityMask  ָ�룬���ظ�����ⴥ���������룬����ο�CameraDefine.h��
//                               EXT_TRIG_MASK_ ��ͷ�ĺ궨�塣   
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetExtTrigCapability)(
    CameraHandle    hCamera,
    UINT*           puCapabilityMask
);

/******************************************************/
// ������   : CameraGetResolutionForSnap
// �������� : ���ץ��ģʽ�µķֱ���ѡ�������š�
// ����     : hCamera        ����ľ������CameraInit������á�
//            pImageResolution ָ�룬����ץ��ģʽ�ķֱ��ʡ� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetResolutionForSnap)(
    CameraHandle            hCamera,
    tSdkImageResolution*    pImageResolution
);

/******************************************************/
// ������   : CameraSetResolutionForSnap
// �������� : ����ץ��ģʽ��������ͼ��ķֱ��ʡ�
// ����     : hCamera       ����ľ������CameraInit������á�
//            pImageResolution ���pImageResolution->iWidth 
//                 �� pImageResolution->iHeight��Ϊ0��
//                         ���ʾ�趨Ϊ���浱ǰԤ���ֱ��ʡ�ץ
//                         �µ���ͼ��ķֱ��ʻ�͵�ǰ�趨�� 
//                 Ԥ���ֱ���һ����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetResolutionForSnap)(
    CameraHandle            hCamera, 
    tSdkImageResolution*    pImageResolution
);

/******************************************************/
// ������   : CameraCustomizeResolution
// �������� : �򿪷ֱ����Զ�����壬��ͨ�����ӻ��ķ�ʽ
//        ������һ���Զ���ֱ��ʡ�
// ����     : hCamera    ����ľ������CameraInit������á�
//            pImageCustom ָ�룬�����Զ���ķֱ��ʡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraCustomizeResolution)(
    CameraHandle            hCamera,
    tSdkImageResolution*    pImageCustom
);

/******************************************************/
// ������   : CameraCustomizeReferWin
// �������� : �򿪲ο������Զ�����塣��ͨ�����ӻ��ķ�ʽ��
//        ���һ���Զ��崰�ڵ�λ�á�һ�������Զ����ƽ��
//        ���Զ��ع�Ĳο����ڡ�
// ����     : hCamera  ����ľ������CameraInit������á�
//            iWinType   Ҫ���ɵĲο����ڵ���;��0,�Զ��ع�ο����ڣ�
//             1,��ƽ��ο����ڡ�
//            hParent    ���øú����Ĵ��ڵľ��������ΪNULL��
//            piHOff     ָ�룬�����Զ��崰�ڵ����ϽǺ����ꡣ
//            piVOff     ָ�룬�����Զ��崰�ڵ����Ͻ������ꡣ
//            piWidth    ָ�룬�����Զ��崰�ڵĿ�ȡ� 
//            piHeight   ָ�룬�����Զ��崰�ڵĸ߶ȡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraCustomizeReferWin)(
    CameraHandle    hCamera,
    INT             iWinType,
    HWND            hParent, 
    INT*            piHOff,
    INT*            piVOff,
    INT*            piWidth,
    INT*            piHeight
);

/******************************************************/
// ������   : CameraShowSettingPage
// �������� : ��������������ô�����ʾ״̬�������ȵ���CameraCreateSettingPage
//        �ɹ���������������ô��ں󣬲��ܵ��ñ���������
//        ��ʾ��
// ����     : hCamera  ����ľ������CameraInit������á�
//            bShow    TRUE����ʾ;FALSE�����ء�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraShowSettingPage)(
    CameraHandle    hCamera,
    BOOL            bShow
);

/******************************************************/
// ������   : CameraCreateSettingPage
// �������� : ������������������ô��ڡ����øú�����SDK�ڲ���
//        ������������������ô��ڣ�ʡȥ�������¿������
//        ���ý����ʱ�䡣ǿ�ҽ���ʹ����ʹ�øú�����
//        SDKΪ�����������ô��ڡ�
// ����     : hCamera     ����ľ������CameraInit������á�
//            hParent       Ӧ�ó��������ڵľ��������ΪNULL��
//            pWinText      �ַ���ָ�룬������ʾ�ı�������
//            pCallbackFunc ������Ϣ�Ļص�����������Ӧ���¼�����ʱ��
//              pCallbackFunc��ָ��ĺ����ᱻ���ã�
//              �����л��˲���֮��Ĳ���ʱ��pCallbackFunc
//              ���ص�ʱ������ڲ�����ָ������Ϣ���͡�
//              �������Է������Լ������Ľ�����������ɵ�UI
//              ֮�����ͬ�����ò�������ΪNULL��    
//            pCallbackCtx  �ص������ĸ��Ӳ���������ΪNULL��pCallbackCtx
//              ����pCallbackFunc���ص�ʱ����Ϊ����֮һ���롣
//              ������ʹ�øò�������һЩ�����жϡ�
//            uReserved     Ԥ������������Ϊ0��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraCreateSettingPage)(
    CameraHandle            hCamera,
    HWND                    hParent,
    char*                   pWinText,
    CAMERA_PAGE_MSG_PROC    pCallbackFunc,
    PVOID                   pCallbackCtx,
    UINT                    uReserved
);

/******************************************************/
// ������   : CameraSetActiveSettingSubPage
// �������� : ����������ô��ڵļ���ҳ�档������ô����ж��
//        ��ҳ�湹�ɣ��ú��������趨��ǰ��һ����ҳ��
//        Ϊ����״̬����ʾ����ǰ�ˡ�
// ����     : hCamera  ����ľ������CameraInit������á�
//            index      ��ҳ��������š��ο�CameraDefine.h��
//             PROP_SHEET_INDEX�Ķ��塣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetActiveSettingSubPage)(
    CameraHandle    hCamera,
    INT             index
);

/******************************************************/
// ������   : CameraSpecialControl
// �������� : ���һЩ�������������õĽӿڣ����ο���ʱһ�㲻��Ҫ
//        ���á�
// ����     : hCamera  ����ľ������CameraInit������á�
//            dwCtrlCode �����롣
//            dwParam    �������룬��ͬ��dwCtrlCodeʱ�����岻ͬ��
//            lpData     ���Ӳ�������ͬ��dwCtrlCodeʱ�����岻ͬ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSpecialControl)(
    CameraHandle    hCamera, 
    DWORD           dwCtrlCode,
    DWORD           dwParam,
    LPVOID          lpData
);

/******************************************************/
// ������   : CameraGetFrameStatistic
// �������� : ����������֡�ʵ�ͳ����Ϣ����������֡�Ͷ�֡�������
// ����     : hCamera        ����ľ������CameraInit������á�
//            psFrameStatistic ָ�룬����ͳ����Ϣ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetFrameStatistic)(
    CameraHandle            hCamera, 
    tSdkFrameStatistic*     psFrameStatistic
);

/******************************************************/
// ������   : CameraSetNoiseFilter
// �������� : ����ͼ����ģ���ʹ��״̬��
// ����     : hCamera ����ľ������CameraInit������á�
//            bEnable   TRUE��ʹ�ܣ�FALSE����ֹ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraSetNoiseFilter)(
    CameraHandle    hCamera,
    BOOL            bEnable
);

/******************************************************/
// ������   : CameraGetNoiseFilterState
// �������� : ���ͼ����ģ���ʹ��״̬��
// ����     : hCamera  ����ľ������CameraInit������á�
//            *pEnable   ָ�룬����״̬��TRUE��Ϊʹ�ܡ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraGetNoiseFilterState)(
    CameraHandle    hCamera,
    BOOL*           pEnable
);


/******************************************************/
// ������   : CameraRstTimeStamp
// �������� : ��λͼ��ɼ���ʱ�������0��ʼ��
// ����     : CameraHandle hCamera
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef    CameraSdkStatus (__stdcall *_CameraRstTimeStamp)(
    CameraHandle    hCamera
);

/******************************************************/
// ������   : CameraGetCapabilityEx
// �������� : �����������������ṹ�塣�ýṹ���а��������
//        �����õĸ��ֲ����ķ�Χ��Ϣ����������غ����Ĳ���
//        ���أ�Ҳ�����ڶ�̬������������ý��档
// ����     : sDeviceModel    ������ͺţ���ɨ���б��л�ȡ
//             pCameraInfo   ָ�룬���ظ�������������Ľṹ�塣
//             PVOID         hCameraHandle
//            tSdkCameraCapbility��CameraDefine.h�ж��塣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetCapabilityEx)(
    char*                   sDeviceModel, 
    tSdkCameraCapbility*    pCameraInfo,
    PVOID                   hCameraHandle
);

/******************************************************/
// ������   : CameraFreeCapabilityEx
// �������� : 
//        ���أ�Ҳ�����ڶ�̬������������ý��档
// ����     : sDeviceModel    ������ͺţ���ɨ���б��л�ȡ
//            hCameraHandle  ָ��
//                        tSdkCameraCapbility��CameraDefine.h�ж��塣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraFreeCapabilityEx)(
    char*                   sDeviceModel, 
    PVOID                   hCameraHandle
);



/******************************************************/
// ������   : CameraSaveUserData
// �������� : ���û��Զ�������ݱ��浽����ķ����Դ洢���С�
//              ÿ���ͺŵ��������֧�ֵ��û���������󳤶Ȳ�һ����
//              ���Դ��豸�����������л�ȡ�ó�����Ϣ��
// ����     : hCamera    ����ľ������CameraInit������á�
//            uStartAddr  ��ʼ��ַ����0��ʼ��
//            pbData      ���ݻ�����ָ��
//            ilen        д�����ݵĳ��ȣ�ilen + uStartAddr����
//                        С���û�����󳤶�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraSaveUserData)(
    CameraHandle    hCamera,
    UINT            uStartAddr,
    BYTE            *pbData,
    int             ilen
);

/******************************************************/
// ������   : CameraLoadUserData
// �������� : ������ķ����Դ洢���ж�ȡ�û��Զ�������ݡ�
//              ÿ���ͺŵ��������֧�ֵ��û���������󳤶Ȳ�һ����
//              ���Դ��豸�����������л�ȡ�ó�����Ϣ��
// ����     : hCamera    ����ľ������CameraInit������á�
//            uStartAddr  ��ʼ��ַ����0��ʼ��
//            pbData      ���ݻ�����ָ�룬���ض��������ݡ�
//            ilen        ��ȡ���ݵĳ��ȣ�ilen + uStartAddr����
//                        С���û�����󳤶�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraLoadUserData)(
    CameraHandle    hCamera,
    UINT            uStartAddr,
    BYTE            *pbData,
    int             ilen
);



/******************************************************/
// ������   : CameraGetFriendlyName
// �������� : ��ȡ�û��Զ�����豸�ǳơ�
// ����     : hCamera    ����ľ������CameraInit������á�
//            pName      ָ�룬����ָ��0��β���ַ�����
//             �豸�ǳƲ�����32���ֽڣ���˸�ָ��
//             ָ��Ļ�����������ڵ���32���ֽڿռ䡣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetFriendlyName)(
  CameraHandle  hCamera,
  char*     pName
);


/******************************************************/
// ������   : CameraSetFriendlyName
// �������� : �����û��Զ�����豸�ǳơ�
// ����     : hCamera    ����ľ������CameraInit������á�
//            pName      ָ�룬ָ��0��β���ַ�����
//             �豸�ǳƲ�����32���ֽڣ���˸�ָ��
//             ָ���ַ�������С�ڵ���32���ֽڿռ䡣
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraSetFriendlyName)(
  CameraHandle  hCamera,
  char*       pName
);


/******************************************************/
// ������   : CameraSdkGetVersionString
// �������� : 
// ����     : pVersionString ָ�룬����SDK�汾�ַ�����
//                            ��ָ��ָ��Ļ�������С�������
//                            32���ֽ�
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraSdkGetVersionString)(
  char*       pVersionString
);

/******************************************************/
// ������   : CameraCheckFwUpdate
// �������� : ���̼��汾���Ƿ���Ҫ������
// ����     : hCamera ����ľ������CameraInit������á�
//            pNeedUpdate ָ�룬���ع̼����״̬��TRUE��ʾ��Ҫ����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraCheckFwUpdate)(
  CameraHandle  hCamera,
  BOOL*     pNeedUpdate
);

/******************************************************/
// ������   : CameraGetFirmwareVision
// �������� : ��ù̼��汾���ַ���
// ����     : hCamera ����ľ������CameraInit������á�
//            pVersion ����ָ��һ������32�ֽڵĻ�������
//                      ���ع̼��İ汾�ַ�����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetFirmwareVision)(
  CameraHandle  hCamera,
  char*     pVersion
);

/******************************************************/
// ������   : CameraGetEnumInfo
// �������� : ���ָ���豸��ö����Ϣ
// ����     : hCamera ����ľ������CameraInit������á�
//            pCameraInfo ָ�룬�����豸��ö����Ϣ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetEnumInfo)(
  CameraHandle    hCamera,
  tSdkCameraDevInfo*  pCameraInfo
);

/******************************************************/
// ������   : CameraGetInerfaceVersion
// �������� : ���ָ���豸�ӿڵİ汾
// ����     : hCamera ����ľ������CameraInit������á�
//            pVersion ָ��һ������32�ֽڵĻ����������ؽӿڰ汾�ַ�����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetInerfaceVersion)(
  CameraHandle    hCamera,
  char*       pVersion
);

/******************************************************/
// ������   : CameraSetIOState
// �������� : ����ָ��IO�ĵ�ƽ״̬��IOΪ�����IO�����
//              Ԥ���ɱ�����IO�ĸ�����tSdkCameraCapbility��
//              iOutputIoCounts������
// ����     : hCamera ����ľ������CameraInit������á�
//            iOutputIOIndex IO�������ţ���0��ʼ��
//            uState Ҫ�趨��״̬��1Ϊ�ߣ�0Ϊ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraSetIOState)(
  CameraHandle    hCamera,
  INT         iOutputIOIndex,
  UINT        uState
);

/******************************************************/
// ������   : CameraGetIOState
// �������� : ����ָ��IO�ĵ�ƽ״̬��IOΪ������IO�����
//              Ԥ���ɱ�����IO�ĸ�����tSdkCameraCapbility��
//              iInputIoCounts������
// ����     : hCamera ����ľ������CameraInit������á�          
//            iInputIOIndex IO�������ţ���0��ʼ��
//            puState ָ�룬����IO״̬,1Ϊ�ߣ�0Ϊ��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetIOState)(
  CameraHandle      hCamera,
  INT               iInputIOIndex,
  UINT*             puState
);


/******************************************************/
// ������ 	: CameraSetBlackLevel
// ��������	: ����ͼ��ĺڵ�ƽ��׼��Ĭ��ֵΪ0
// ����	    : hCamera	  ����ľ������CameraInit������á� 
//            iBlackLevel Ҫ�趨�ĵ�ƽֵ����ΧΪ0��128��	
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraSetBlackLevel)
(
    CameraHandle    hCamera,
    INT             iBlackLevel
);

/******************************************************/
// ������ 	: CameraGetBlackLevel
// ��������	: ���ͼ��ĺڵ�ƽ��׼��Ĭ��ֵΪ0
// ����	    : hCamera	   ����ľ������CameraInit������á� 
//            piBlackLevel ���ص�ǰ�ĺڵ�ƽֵ����ΧΪ0��128��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetBlackLevel)
(
    CameraHandle    hCamera,
    INT*            piBlackLevel
);


/******************************************************/
// ������ 	: CameraSetWhiteLevel
// ��������	: ����ͼ��İ׵�ƽ��׼��Ĭ��ֵΪ255
// ����	    : hCamera		����ľ������CameraInit������á� 
//            iWhiteLevel	Ҫ�趨�ĵ�ƽֵ����ΧΪ128��255��	
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraSetWhiteLevel)
(
    CameraHandle    hCamera,
    INT             iWhiteLevel
);



/******************************************************/
// ������ 	: CameraGetWhiteLevel
// ��������	: ���ͼ��İ׵�ƽ��׼��Ĭ��ֵΪ255
// ����	    : hCamera	   ����ľ������CameraInit������á� 
//            piWhiteLevel ���ص�ǰ�İ׵�ƽֵ����ΧΪ128��255��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetWhiteLevel)
(
    CameraHandle    hCamera,
    INT*            piWhiteLevel
);


/******************************************************/
// ������ 	: CameraSetIspOutFormat
// ��������	: ����CameraGetImageBuffer������ͼ����������ʽ��֧��
//              CAMERA_MEDIA_TYPE_MONO8��CAMERA_MEDIA_TYPE_RGB8��CAMERA_MEDIA_TYPE_RGBA8
//              (��CameraDefine.h�ж���)���֣��ֱ��Ӧ8λ�Ҷ�ͼ���24��32λ��ɫͼ��
// ����	    : hCamera		����ľ������CameraInit������á� 
//             uFormat	     Ҫ�趨��ʽ��CAMERA_MEDIA_TYPE_MONO8����CAMERA_MEDIA_TYPE_RGB8��CAMERA_MEDIA_TYPE_RGBA8	
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraSetIspOutFormat)
(
    CameraHandle    hCamera,
    UINT            uFormat
);

/******************************************************/
// ������ 	: CameraGetIspOutFormat
// ��������	: ���CameraGetImageBuffer����ͼ����������ʽ��֧��
//              CAMERA_MEDIA_TYPE_MONO8��CAMERA_MEDIA_TYPE_RGB8��CAMERA_MEDIA_TYPE_RGBA8
//              (��CameraDefine.h�ж���)���֣��ֱ��Ӧ8λ�Ҷ�ͼ���24��32λ��ɫͼ��
// ����	    : hCamera		����ľ������CameraInit������á� 
//             puFormat	���ص�ǰ�趨�ĸ�ʽ��CAMERA_MEDIA_TYPE_MONO8����CAMERA_MEDIA_TYPE_RGB8��CAMERA_MEDIA_TYPE_RGBA8	
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetIspOutFormat)
(
    CameraHandle    hCamera,
    UINT*           puFormat
);

/******************************************************/
// ������ 	: CameraGetErrorString
// ��������	: ��ô������Ӧ�������ַ���
// ����	    : iStatusCode		�����롣(������CameraStatus.h��)
// ����ֵ   : �ɹ�ʱ�����ش������Ӧ���ַ����׵�ַ;
//            ���򷵻�NULL��
/******************************************************/
typedef char* (__stdcall *_CameraGetErrorString)(
    CameraSdkStatus     iStatusCode
);

/******************************************************/
// ������ 	: CameraGetImageBufferEx2
// ��������	: ���һ֡ͼ�����ݡ��ýӿڻ�õ�ͼ���Ǿ���������RGB��ʽ���ú������ú�
//			  ����Ҫ���� CameraReleaseImageBuffer �ͷţ�Ҳ��Ҫ����free֮��ĺ����ͷ�
//              ���ͷŸú������ص�ͼ�����ݻ�������
// ����	    : hCamera	    ����ľ������CameraInit������á�
//             pImageData  ����ͼ�����ݵĻ���������С�����uOutFormatָ���ĸ�ʽ��ƥ�䣬�������ݻ����
//             piWidth     ����ָ�룬����ͼ��Ŀ��
//             piHeight    ����ָ�룬����ͼ��ĸ߶�
//             wTimes      ץȡͼ��ĳ�ʱʱ�䡣��λ���롣��
//						wTimesʱ���ڻ�δ���ͼ����ú���
//						�᷵�س�ʱ��Ϣ��
// ����ֵ   : �ɹ�ʱ������RGB���ݻ��������׵�ַ;
//            ���򷵻�0��
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetImageBufferEx2)(
    CameraHandle    hCamera, 
    BYTE*           pImageData,
    UINT            uOutFormat,
    int*            piWidth,
    int*            piHeight,
    UINT            wTimes
);

/******************************************************/
// ������ 	: CameraGetCapabilityEx2
// ��������	: ��ø������һЩ���ԡ�
// ����	    : hCamera		    ����ľ������CameraInit������á� 
//             pMaxWidth	    ���ظ�������ֱ��ʵĿ��
//             pMaxHeight      ���ظ�������ֱ��ʵĸ߶� 
//             pbColorCamera    ���ظ�����Ƿ��ǲ�ɫ�����1��ʾ��ɫ�����0��ʾ�ڰ����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetCapabilityEx2)(
    CameraHandle    hCamera,
    int*            pMaxWidth,
    int*            pMaxHeight,
    int*            pbColorCamera
);


/******************************************************/
// ������ 	: CameraReConnect
// ��������	: ���������豸������USB�豸������ߺ�����
// ����	    : hCamera	   ����ľ������CameraInit������á� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0);
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraReConnect)(
    CameraHandle    hCamera
);


/******************************************************/
// ������ 	: CameraConnectTest
// ��������	: �������������״̬�����ڼ������Ƿ����
// ����	    : hCamera	   ����ľ������CameraInit������á� 
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0)����ʾ�������״̬����;
//            ���򷵻ط�0ֵ�Ĵ�����,��ο�CameraStatus.h
//            �д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraConnectTest)(
    CameraHandle    hCamera
);


/******************************************************/
// ������ 	: CameraSetLedLightless
// ��������	: ���������LED���ȣ�����LED���ͺţ��˺������ش�����룬��ʾ��֧�֡�
// ����	    : hCamera	   ����ľ������CameraInit������á� 
//             index      LED�Ƶ������ţ���0��ʼ�����ֻ��һ���ɿ������ȵ�LED����ò���Ϊ0 ��
//             uLightless LED����ֵ����Χ0��255. 0��ʾ�رգ�255������
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0)����ʾ�������״̬����;
//            ���򷵻� ��0ֵ���ο�CameraStatus.h�д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraSetLedBrightness)(
    CameraHandle    hCamera,
    int             index,
    UINT            uLightless
);

/******************************************************/
// ������ 	: CameraGetLedLightless
// ��������	: ��������LED���ȣ�����LED���ͺţ��˺������ش�����룬��ʾ��֧�֡�
// ����	    : hCamera	   ����ľ������CameraInit������á� 
//             index      LED�Ƶ������ţ���0��ʼ�����ֻ��һ���ɿ������ȵ�LED����ò���Ϊ0 ��
//             uLightless ָ�룬����LED����ֵ����Χ0��255. 0��ʾ�رգ�255������
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0)����ʾ�������״̬����;
//            ���򷵻� ��0ֵ���ο�CameraStatus.h�д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetLedBrightness)(
    CameraHandle    hCamera,
    int             index,
    UINT*           uLightless
);


/******************************************************/
// ������ 	: CameraEnableTransferRoi
// ��������	: ʹ�ܻ��߽�ֹ����Ķ������书�ܣ������ù��ܵ��ͺţ��˺������ش�����룬��ʾ��֧�֡�
//              �ù�����Ҫ����������˽��ɼ������������з֣�ֻ����ָ���Ķ����������ߴ���֡�ʡ�
//              ��������䵽PC�Ϻ󣬻��Զ�ƴ�ӳ��������棬û�б�����Ĳ��֣����ú�ɫ��䡣
// ����	    : hCamera	    ����ľ������CameraInit������á� 
//             index       ROI����������ţ���0��ʼ��
//             uEnableMask ����ʹ��״̬���룬��Ӧ�ı���λΪ1��ʾʹ�ܡ�0Ϊ��ֹ��ĿǰSDK֧��4���ɱ༭����index��ΧΪ0��3����bit0 ��bit1��bit2��bit3����4�������ʹ��״̬��
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0)����ʾ�������״̬����;
//            ���ڲ�֧�ֶ�����ROI������ͺţ��ú����᷵�� CAMERA_STATUS_NOT_SUPPORTED(-4) ��ʾ��֧��   
//            ������0ֵ���ο�CameraStatus.h�д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraEnableTransferRoi)(
    CameraHandle    hCamera,
    UINT            uEnableMask
);


/******************************************************/
// ������ 	: CameraSetTransferRoi
// ��������	: �����������Ĳü�����������ˣ�ͼ��Ӵ������ϱ��ɼ��󣬽��ᱻ�ü���ָ�������������ͣ��˺������ش�����룬��ʾ��֧�֡�
// ����	    : hCamera	   ����ľ������CameraInit������á� 
//             index      ROI����������ţ���0��ʼ��
//             X1,Y1      ROI��������Ͻ�����
//             X2,Y2      ROI��������Ͻ�����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0)����ʾ�������״̬����;
//            ���ڲ�֧�ֶ�����ROI������ͺţ��ú����᷵�� CAMERA_STATUS_NOT_SUPPORTED(-4) ��ʾ��֧��   
//            ������0ֵ���ο�CameraStatus.h�д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraSetTransferRoi)(
    CameraHandle    hCamera,
    int             index,
    UINT            X1,
    UINT            Y1,
    UINT            X2,
    UINT            Y2
);


/******************************************************/
// ������ 	: CameraGetTransferRoi
// ��������	: �����������Ĳü�����������ˣ�ͼ��Ӵ������ϱ��ɼ��󣬽��ᱻ�ü���ָ�������������ͣ��˺������ش�����룬��ʾ��֧�֡�
// ����	    : hCamera	   ����ľ������CameraInit������á� 
//             index      ROI����������ţ���0��ʼ��
//             pX1,pY1      ROI��������Ͻ�����
//             pX2,pY2      ROI��������Ͻ�����
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0)����ʾ�������״̬����;
//            ���ڲ�֧�ֶ�����ROI������ͺţ��ú����᷵�� CAMERA_STATUS_NOT_SUPPORTED(-4) ��ʾ��֧��   
//            ������0ֵ���ο�CameraStatus.h�д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetTransferRoi)(
    CameraHandle    hCamera,
    int             index,
    UINT*           pX1,
    UINT*           pY1,
    UINT*           pX2,
    UINT*           pY2
);

/******************************************************/
// ������ 	: CameraAlignMalloc
// ��������	: ����һ�ζ�����ڴ�ռ䡣���ܺ�malloc���ƣ���
//						�Ƿ��ص��ڴ�����alignָ�����ֽ�������ġ�
// ����	    : size	   �ռ�Ĵ�С�� 
//            align    ��ַ������ֽ�����
// ����ֵ   : �ɹ�ʱ�����ط�0ֵ����ʾ�ڴ��׵�ַ��ʧ�ܷ���NULL��
/******************************************************/

typedef BYTE* (__stdcall *_CameraAlignMalloc)(
    int             size,
    int             align
    );
    
/******************************************************/
// ������ 	: CameraAlignFree
// ��������	: �ͷ���CameraAlignMalloc����������ڴ�ռ䡣
// ����	    : membuffer	   ��CameraAlignMalloc���ص��ڴ��׵�ַ�� 
// ����ֵ   : �ޡ�
/******************************************************/
typedef void (__stdcall *_CameraAlignFree)(
    BYTE*           membuffer
);


/******************************************************/
// ������ 	: CameraSetAutoConnect
// ��������	: �����Զ�ʹ������
// ����	    : hCamera	   ����ľ������CameraInit������á� 
//			  bEnable	   ʹ�������������λTRUEʱ��SDK�ڲ��Զ��������Ƿ���ߣ����ߺ��Լ�������
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0)����ʾ�������״̬����;
//            ���ڲ�֧�ֵ��ͺţ��ú����᷵�� CAMERA_STATUS_NOT_SUPPORTED(-4) ��ʾ��֧��   
//            ������0ֵ���ο�CameraStatus.h�д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraSetAutoConnect)(
    CameraHandle hCamera,
    BOOL bEnable
);

/******************************************************/
// ������ 	: CameraGetReConnectCounts
// ��������	: �������Զ������Ĵ�����ǰ����CameraSetAutoConnect ʹ������Զ��������ܡ�Ĭ����ʹ�ܵġ�
// ����	    : hCamera	   ����ľ������CameraInit������á� 
//			 puCounts	   ���ص����Զ������Ĵ���
// ����ֵ   : �ɹ�ʱ������CAMERA_STATUS_SUCCESS (0)����ʾ�������״̬����;
//            ���ڲ�֧�ֵ��ͺţ��ú����᷵�� CAMERA_STATUS_NOT_SUPPORTED(-4) ��ʾ��֧��   
//            ������0ֵ���ο�CameraStatus.h�д�����Ķ��塣
/******************************************************/
typedef CameraSdkStatus (__stdcall *_CameraGetReConnectCounts)(
    CameraHandle hCamera,
    UINT* puCounts
);


#ifdef API_LOAD_MAIN
#define EXTERN 
#else
#define EXTERN extern
#endif

EXTERN INT gSdkLanguageSel;//0:English 1:Chinese

EXTERN _CameraSdkInit CameraSdkInit;

EXTERN _CameraSetCallbackFunction CameraSetCallbackFunction;

EXTERN _CameraGetInformation CameraGetInformation;

EXTERN _CameraSaveImage CameraSaveImage;
    
EXTERN _CameraInitRecord CameraInitRecord;

EXTERN _CameraStopRecord CameraStopRecord;

EXTERN _CameraPushFrame CameraPushFrame;

EXTERN _CameraSpecialControl CameraSpecialControl;

EXTERN _CameraSnapToBuffer CameraSnapToBuffer;

EXTERN _CameraIsOpened CameraIsOpened;

EXTERN _CameraInit CameraInit;

EXTERN _CameraUnInit CameraUnInit;

EXTERN _CameraPlay CameraPlay;

EXTERN _CameraPause CameraPause;

EXTERN _CameraStop CameraStop;

EXTERN _CameraSetDisplayMode CameraSetDisplayMode;

EXTERN _CameraDisplayRGB24 CameraDisplayRGB24;

EXTERN _CameraSetDisplayOffset CameraSetDisplayOffset;

EXTERN _CameraImageOverlay CameraImageOverlay;

EXTERN _CameraDisplayInit CameraDisplayInit;

EXTERN _CameraDisplayInitEx CameraDisplayInitEx;

EXTERN _CameraSetDisplaySize CameraSetDisplaySize;

EXTERN _CameraGetImageBuffer CameraGetImageBuffer;

EXTERN _CameraReleaseImageBuffer CameraReleaseImageBuffer;

EXTERN _CameraCreateSettingPage CameraCreateSettingPage;

EXTERN _CameraSetActiveSettingSubPage CameraSetActiveSettingSubPage;

EXTERN _CameraCustomizeResolution CameraCustomizeResolution;

EXTERN _CameraSetMirror CameraSetMirror;

EXTERN _CameraGetMirror CameraGetMirror;

EXTERN _CameraSetMonochrome CameraSetMonochrome;

EXTERN _CameraGetMonochrome CameraGetMonoChrome;

EXTERN _CameraSetInverse CameraSetInverse;

EXTERN _CameraGetInverse CameraGetInverse;

EXTERN _CameraGetImageResolution CameraGetImageResolution;

EXTERN _CameraSetImageResolution CameraSetImageResolution;

EXTERN _CameraGetMediaType CameraGetMediaType;

EXTERN _CameraSetMediaType CameraSetMediaType;

EXTERN _CameraSetAeState CameraSetAeState;

EXTERN _CameraGetAeState CameraGetAeState;

EXTERN _CameraSetAeTarget CameraSetAeTarget;

EXTERN _CameraGetAeTarget CameraGetAeTarget;

EXTERN _CameraSetExposureTime CameraSetExposureTime;

EXTERN _CameraGetExposureTime CameraGetExposureTime;

EXTERN _CameraGetExposureLineTime CameraGetExposureLineTime;

EXTERN _CameraSetAnalogGain CameraSetAnalogGain;

EXTERN _CameraGetAnalogGain CameraGetAnalogGain;

EXTERN _CameraSetSharpness CameraSetSharpness;

EXTERN _CameraGetSharpness CameraGetSharpness;

EXTERN _CameraGetPresetClrTemp CameraGetPresetClrTemp;

EXTERN _CameraSetPresetClrTemp CameraSetPresetClrTemp;

EXTERN _CameraSetUserClrTempGain CameraSetUserClrTempGain;

EXTERN _CameraGetUserClrTempGain CameraGetUserClrTempGain;

EXTERN _CameraSetUserClrTempMatrix CameraSetUserClrTempMatrix;

EXTERN _CameraGetUserClrTempMatrix CameraGetUserClrTempMatrix;

EXTERN _CameraSetClrTempMode CameraSetClrTempMode;

EXTERN _CameraGetClrTempMode CameraGetClrTempMode;

EXTERN _CameraSetLutMode CameraSetLutMode;

EXTERN _CameraGetLutMode CameraGetLutMode;

EXTERN _CameraSelectLutPreset CameraSelectLutPreset;

EXTERN _CameraGetLutPresetSel CameraGetLutPresetSel;

EXTERN _CameraSetCustomLut CameraSetCustomLut;

EXTERN _CameraGetCustomLut CameraGetCustomLut;

EXTERN _CameraGetCurrentLut CameraGetCurrentLut;

EXTERN _CameraSetOnceWB CameraSetOnceWB;

EXTERN _CameraSetOnceBB CameraSetOnceBB;

EXTERN _CameraSetWbMode CameraSetWbMode;

EXTERN _CameraGetWbMode CameraGetWbMode;

EXTERN _CameraSetWbWindow CameraSetWbWindow;

EXTERN _CameraSetGain CameraSetGain;

EXTERN _CameraGetGain CameraGetGain;

EXTERN _CameraSetGamma CameraSetGamma;

EXTERN _CameraGetGamma CameraGetGamma;

EXTERN _CameraSetSaturation CameraSetSaturation;

EXTERN _CameraGetSaturation CameraGetSaturation;

EXTERN _CameraSetContrast CameraSetContrast;

EXTERN _CameraGetContrast CameraGetContrast;

EXTERN _CameraSetFrameSpeed CameraSetFrameSpeed;

EXTERN _CameraGetFrameSpeed CameraGetFrameSpeed;

EXTERN _CameraSetAntiFlick CameraSetAntiFlick;

EXTERN _CameraGetAntiFlick CameraGetAntiFlick;

EXTERN _CameraGetLightFrequency CameraGetLightFrequency;

EXTERN _CameraSetLightFrequency CameraSetLightFrequency;

EXTERN _CameraSetTransPackLen CameraSetTransPackLen;

EXTERN _CameraGetTransPackLen CameraGetTransPackLen;

EXTERN _CameraWriteSN CameraWriteSN;

EXTERN _CameraReadSN CameraReadSN;

EXTERN _CameraSaveParameter CameraSaveParameter;

EXTERN _CameraLoadParameter CameraLoadParameter;

EXTERN _CameraGetCurrentParameterGroup CameraGetCurrentParameterGroup;

EXTERN _CameraEnumerateDevice CameraEnumerateDevice;

EXTERN _CameraGetCapability CameraGetCapability;

EXTERN _CameraImageProcess CameraImageProcess;

EXTERN _CameraImageProcessEx CameraImageProcessEx;

EXTERN _CameraSoftTrigger CameraSoftTrigger;

EXTERN _CameraSetTriggerMode CameraSetTriggerMode;

EXTERN _CameraGetTriggerMode CameraGetTriggerMode;

EXTERN _CameraSetStrobeMode CameraSetStrobeMode;

EXTERN _CameraGetStrobeMode CameraGetStrobeMode;

EXTERN _CameraSetStrobeDelayTime CameraSetStrobeDelayTime;

EXTERN _CameraGetStrobeDelayTime CameraGetStrobeDelayTime;

EXTERN _CameraSetStrobePulseWidth CameraSetStrobePulseWidth;

EXTERN _CameraGetStrobePulseWidth CameraGetStrobePulseWidth;

EXTERN _CameraSetStrobePolarity CameraSetStrobePolarity;

EXTERN _CameraGetStrobePolarity CameraGetStrobePolarity;

EXTERN _CameraSetExtTrigSignalType CameraSetExtTrigSignalType;

EXTERN _CameraGetExtTrigSignalType CameraGetExtTrigSignalType;

EXTERN _CameraSetExtTrigShutterType CameraSetExtTrigShutterType;

EXTERN _CameraGetExtTrigShutterType CameraGetExtTrigShutterType;

EXTERN _CameraSetExtTrigDelayTime CameraSetExtTrigDelayTime;

EXTERN _CameraGetExtTrigDelayTime CameraGetExtTrigDelayTime;

EXTERN _CameraSetExtTrigJitterTime CameraSetExtTrigJitterTime;

EXTERN _CameraGetExtTrigJitterTime CameraGetExtTrigJitterTime;

EXTERN _CameraGetExtTrigCapability CameraGetExtTrigCapability;

EXTERN _CameraShowSettingPage CameraShowSettingPage;

EXTERN _CameraGetFrameStatistic CameraGetFrameStatistic;

EXTERN _CameraGetResolutionForSnap CameraGetResolutionForSnap;

EXTERN _CameraSetResolutionForSnap CameraSetResolutionForSnap;

EXTERN _CameraIsAeWinVisible CameraIsAeWinVisible;

EXTERN _CameraIsWbWinVisible CameraIsWbWinVisible;

EXTERN _CameraGetNoiseFilterState CameraGetNoiseFilterState;

EXTERN _CameraSetParameterMode CameraSetParameterMode;

EXTERN _CameraGetParameterMode CameraGetParameterMode;

EXTERN _CameraSetParameterMask CameraSetParameterMask;

EXTERN _CameraGetTriggerCount CameraGetTriggerCount;

EXTERN _CameraGetCrossLine CameraGetCrossLine;

EXTERN _CameraSetCrossLine CameraSetCrossLine;

EXTERN _CameraGetTriggerDelayTime CameraGetTriggerDelayTime;

EXTERN _CameraSetTriggerDelayTime CameraSetTriggerDelayTime;

EXTERN _CameraSetAeWinVisible CameraSetAeWinVisible;

EXTERN _CameraSetNoiseFilter CameraSetNoiseFilter;

EXTERN _CameraSetTriggerCount CameraSetTriggerCount;

EXTERN _CameraCustomizeReferWin CameraCustomizeReferWin;

EXTERN _CameraSetAeWindow CameraSetAeWindow;

EXTERN _CameraReadParameterFromFile CameraReadParameterFromFile;

EXTERN _CameraSetWbWinVisible CameraSetWbWinVisible;

EXTERN _CameraRstTimeStamp CameraRstTimeStamp;

EXTERN _CameraGetCapabilityEx CameraGetCapabilityEx;

EXTERN _CameraSaveUserData CameraSaveUserData;

EXTERN _CameraLoadUserData CameraLoadUserData;

EXTERN _CameraGetFriendlyName CameraGetFriendlyName;

EXTERN _CameraSetFriendlyName CameraSetFriendlyName;

EXTERN _CameraSdkGetVersionString CameraSdkGetVersionString; 

EXTERN _CameraCheckFwUpdate CameraCheckFwUpdate;

EXTERN _CameraGetFirmwareVision CameraGetFirmwareVision;

EXTERN _CameraGetEnumInfo CameraGetEnumInfo;

EXTERN _CameraGetInerfaceVersion CameraGetInerfaceVersion;

EXTERN _CameraSetIOState CameraSetIOState;

EXTERN _CameraGetIOState CameraGetIOState;

EXTERN _CameraSetBlackLevel CameraSetBlackLevel;

EXTERN _CameraGetBlackLevel CameraGetBlackLevel;

EXTERN _CameraSetWhiteLevel CameraSetWhiteLevel;

EXTERN _CameraGetWhiteLevel CameraGetWhiteLevel;

EXTERN _CameraSetIspOutFormat CameraSetIspOutFormat;

EXTERN _CameraGetIspOutFormat CameraGetIspOutFormat;

EXTERN _CameraGetErrorString CameraGetErrorString;

EXTERN _CameraGetCapabilityEx2 CameraGetCapabilityEx2;

EXTERN _CameraGetImageBufferEx2 CameraGetImageBufferEx2;

EXTERN _CameraReConnect CameraReConnect;

EXTERN _CameraConnectTest CameraConnectTest;

EXTERN _CameraSetLedBrightness CameraSetLedBrightness;

EXTERN _CameraGetLedBrightness CameraGetLedBrightness;

EXTERN _CameraEnableTransferRoi CameraEnableTransferRoi;

EXTERN _CameraSetTransferRoi CameraSetTransferRoi;

EXTERN _CameraGetTransferRoi CameraGetTransferRoi;

EXTERN _CameraAlignMalloc CameraAlignMalloc;

EXTERN _CameraAlignFree CameraAlignFree;

EXTERN _CameraSetAutoConnect CameraSetAutoConnect;

EXTERN _CameraGetReConnectCounts CameraGetReConnectCounts;


CameraSdkStatus LoadSdkApi();

CameraSdkStatus UnloadCameraSdk();

#ifdef API_LOAD_MAIN
#undef API_LOAD_MAIN


//���SDK�汾��ƥ�䣬���ܳ���ĳЩ��������ʧ�ܡ�

#define CHCEK_API_LOAD 0 // 1:����API�������⣬�������ʧ�ܣ�������ʾ�� 0:�����(����ͨ��SDK�汾�Ž��жԱ�)��

#if CHCEK_API_LOAD
#define CHECK_API(API) if(API == NULL)\
{\
    MessageBox(NULL,#API,gSdkLanguageSel?"��������ʧ��":"Function load failed!",0);\
    return CAMERA_STATUS_FAILED;\
}
#else
#define CHECK_API(API) 
#endif

HMODULE ghSDK = NULL;

CameraSdkStatus LoadSdkApi()
{
  char strPath[MAX_PATH];
  char strDir[MAX_PATH];
  HKEY hkey = NULL;
  DWORD dwType = REG_SZ;
  DWORD dwSize = MAX_PATH;
  BYTE abyValue[MAX_PATH];
  LONG status;

  gSdkLanguageSel = 0;
  

  RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\MindVision\\Digital Camera Platform\\Settings", 0, NULL, 
    0, KEY_ALL_ACCESS, NULL, &hkey, NULL);
  
  do 
  {
    if (NULL != hkey)
    {
      memset(abyValue, 0x00, MAX_PATH);

      status = RegQueryValueEx(hkey, "Language", NULL, &dwType, abyValue, &dwSize);

      if (ERROR_SUCCESS == status)
      {
        abyValue[MAX_PATH-1] = '\0';
        if (strcmp((const char *)abyValue,"Chinese") == 0)
        {
            gSdkLanguageSel = 1;
        }
		else if (strcmp((const char *)abyValue,"TradChinese") == 0)
		{
			gSdkLanguageSel = 2;
		}

      }

      dwType = REG_SZ;
      dwSize = MAX_PATH;

      status = RegQueryValueEx(hkey, "SdkPath", NULL, &dwType, abyValue, &dwSize);

      if (ERROR_SUCCESS == status)
      {
        abyValue[MAX_PATH-1] = '\0';
        strcpy(strPath,(const char *)abyValue);
        break;
      }
      
    }

    MessageBox(NULL, "Failed to access registry", "Error", 0);
    return CAMERA_STATUS_FAILED;
  } while(0);
  
  
#ifndef _WIN64
  sprintf(strDir,"%s","MVCAMSDK.dll");
#else
  sprintf(strDir,"%s","MVCAMSDK_X64.dll");
#endif
  ghSDK = ::LoadLibrary(strDir);

      
  if (NULL == ghSDK)
  {
    if (gSdkLanguageSel == 1)
    {
        sprintf(strPath,"�ļ�[%s]����ʧ�� ,��ȷ�ϸ�·�����ڸ��ļ��������½��а�װ!",strDir);
        MessageBox(NULL, strPath, "����", 0); 
    }
    else
    {
        sprintf(strPath,"Failed to load file[%s] ,put the file on the directory or re-install the platform and try again!",strDir);
        MessageBox(NULL, strPath, "Error", 0);
    } 
      return CAMERA_STATUS_FAILED;
  }
  
    CameraSdkInit = (_CameraSdkInit)GetProcAddress(ghSDK, "CameraSdkInit");
    CHECK_API(CameraSdkInit); //�������Ҫ��⣬����CHCEK_API_LOAD����Ϊ0   
    CameraSetCallbackFunction = (_CameraSetCallbackFunction)GetProcAddress(ghSDK, "CameraSetCallbackFunction");
    CHECK_API(CameraSetCallbackFunction);
    CameraGetInformation = (_CameraGetInformation)GetProcAddress(ghSDK, "CameraGetInformation");
    CHECK_API(CameraGetInformation);
    CameraInit = (_CameraInit)GetProcAddress(ghSDK, "CameraInit");
    CHECK_API(CameraInit);
    CameraUnInit = (_CameraUnInit)GetProcAddress(ghSDK, "CameraUnInit");
    CHECK_API(CameraUnInit);
    CameraImageProcess = (_CameraImageProcess)GetProcAddress(ghSDK, "CameraImageProcess");
    CHECK_API(CameraImageProcess);
    CameraImageProcessEx = (_CameraImageProcessEx)GetProcAddress(ghSDK, "CameraImageProcessEx");
    CHECK_API(CameraImageProcessEx);
    CameraPlay = (_CameraPlay)GetProcAddress(ghSDK, "CameraPlay");
    CHECK_API(CameraPlay);
    CameraPause = (_CameraPause)GetProcAddress(ghSDK, "CameraPause");
    CHECK_API(CameraPause);
    CameraStop = (_CameraStop)GetProcAddress(ghSDK, "CameraStop");
    CHECK_API(CameraStop);
    CameraDisplayRGB24 = (_CameraDisplayRGB24)GetProcAddress(ghSDK, "CameraDisplayRGB24");
    CHECK_API(CameraDisplayRGB24);
    CameraSetDisplayMode = (_CameraSetDisplayMode)GetProcAddress(ghSDK, "CameraSetDisplayMode");
    CHECK_API(CameraSetDisplayMode);
    CameraImageOverlay = (_CameraImageOverlay)GetProcAddress(ghSDK, "CameraImageOverlay");
    CHECK_API(CameraImageOverlay);
    CameraDisplayInit = (_CameraDisplayInit)GetProcAddress(ghSDK, "CameraDisplayInit");
    CHECK_API(CameraDisplayInit);
    CameraDisplayInitEx = (_CameraDisplayInitEx)GetProcAddress(ghSDK, "CameraDisplayInitEx");
    CHECK_API(CameraDisplayInitEx);
    CameraSetDisplaySize = (_CameraSetDisplaySize)GetProcAddress(ghSDK, "CameraSetDisplaySize");
    CHECK_API(CameraSetDisplaySize);
    CameraSetDisplayOffset = (_CameraSetDisplayOffset)GetProcAddress(ghSDK, "CameraSetDisplayOffset");
    CHECK_API(CameraSetDisplayOffset);
    CameraInitRecord = (_CameraInitRecord)GetProcAddress(ghSDK, "CameraInitRecord");
    CHECK_API(CameraInitRecord);  
    CameraStopRecord = (_CameraStopRecord)GetProcAddress(ghSDK, "CameraStopRecord");
    CHECK_API(CameraStopRecord);  
    CameraPushFrame = (_CameraPushFrame)GetProcAddress(ghSDK, "CameraPushFrame");
    CHECK_API(CameraPushFrame);  
    CameraSpecialControl = (_CameraSpecialControl)GetProcAddress(ghSDK, "CameraSpecialControl");
    CHECK_API(CameraSpecialControl);
    CameraSnapToBuffer = (_CameraSnapToBuffer)GetProcAddress(ghSDK, "CameraSnapToBuffer");
    CHECK_API(CameraSnapToBuffer);
    CameraGetImageBuffer = (_CameraGetImageBuffer)GetProcAddress(ghSDK, "CameraGetImageBuffer");
    CHECK_API(CameraGetImageBuffer);
    CameraReleaseImageBuffer = (_CameraReleaseImageBuffer)GetProcAddress(ghSDK, "CameraReleaseImageBuffer");
    CHECK_API(CameraReleaseImageBuffer);
    CameraCreateSettingPage = (_CameraCreateSettingPage)GetProcAddress(ghSDK, "CameraCreateSettingPage");
    CHECK_API(CameraCreateSettingPage);
    CameraSetActiveSettingSubPage = (_CameraSetActiveSettingSubPage)GetProcAddress(ghSDK, "CameraSetActiveSettingSubPage");
    CHECK_API(CameraSetActiveSettingSubPage);
    CameraSetMirror = (_CameraSetMirror)GetProcAddress(ghSDK, "CameraSetMirror");
    CHECK_API(CameraSetMirror);
    CameraGetMirror = (_CameraGetMirror)GetProcAddress(ghSDK, "CameraGetMirror");
    CHECK_API(CameraGetMirror);
    CameraSetMonochrome = (_CameraSetMonochrome)GetProcAddress(ghSDK, "CameraSetMonochrome");
    CHECK_API(CameraSetMonochrome);
    CameraGetMonoChrome = (_CameraGetMonochrome)GetProcAddress(ghSDK, "CameraGetMonochrome");
    CHECK_API(CameraGetMonoChrome);
    CameraSetInverse = (_CameraSetInverse)GetProcAddress(ghSDK, "CameraSetInverse");
    CHECK_API(CameraSetInverse);
    CameraGetInverse = (_CameraGetInverse)GetProcAddress(ghSDK, "CameraGetInverse");
    CHECK_API(CameraGetInverse);
    CameraCustomizeResolution = (_CameraCustomizeResolution)GetProcAddress(ghSDK, "CameraCustomizeResolution");
    CHECK_API(CameraCustomizeResolution);
    CameraGetImageResolution = (_CameraGetImageResolution)GetProcAddress(ghSDK, "CameraGetImageResolution");
    CHECK_API(CameraGetImageResolution);
    CameraSetImageResolution = (_CameraSetImageResolution)GetProcAddress(ghSDK, "CameraSetImageResolution");
    CHECK_API(CameraSetImageResolution);
    CameraGetMediaType = (_CameraGetMediaType)GetProcAddress(ghSDK, "CameraGetMediaType");
    CHECK_API(CameraGetMediaType);
    CameraSetMediaType = (_CameraSetMediaType)GetProcAddress(ghSDK, "CameraSetMediaType");
    CHECK_API(CameraSetMediaType);
    CameraSetAeState = (_CameraSetAeState)GetProcAddress(ghSDK, "CameraSetAeState");
    CHECK_API(CameraSetAeState);
    CameraGetAeState = (_CameraGetAeState)GetProcAddress(ghSDK, "CameraGetAeState");
    CHECK_API(CameraGetAeState);
    CameraSetAeTarget = (_CameraSetAeTarget)GetProcAddress(ghSDK, "CameraSetAeTarget");
    CHECK_API(CameraSetAeTarget);
    CameraGetAeTarget = (_CameraGetAeTarget)GetProcAddress(ghSDK, "CameraGetAeTarget");
    CHECK_API(CameraGetAeTarget);
    CameraIsAeWinVisible = (_CameraIsAeWinVisible)GetProcAddress(ghSDK, "CameraIsAeWinVisible");
    CHECK_API(CameraIsAeWinVisible);
    CameraSetExposureTime = (_CameraSetExposureTime)GetProcAddress(ghSDK, "CameraSetExposureTime");
    CHECK_API(CameraSetExposureTime);
    CameraGetExposureTime = (_CameraGetExposureTime)GetProcAddress(ghSDK, "CameraGetExposureTime");
    CHECK_API(CameraGetExposureTime);
    CameraGetExposureLineTime = (_CameraGetExposureLineTime)GetProcAddress(ghSDK, "CameraGetExposureLineTime");
    CHECK_API(CameraGetExposureLineTime);
    CameraSetAnalogGain = (_CameraSetAnalogGain)GetProcAddress(ghSDK, "CameraSetAnalogGain");
    CHECK_API(CameraSetAnalogGain);
    CameraGetAnalogGain = (_CameraGetAnalogGain)GetProcAddress(ghSDK, "CameraGetAnalogGain");
    CHECK_API(CameraGetAnalogGain);
    CameraSetSharpness = (_CameraSetSharpness)GetProcAddress(ghSDK, "CameraSetSharpness");
    CHECK_API(CameraSetSharpness);
    CameraGetSharpness = (_CameraGetSharpness)GetProcAddress(ghSDK, "CameraGetSharpness");
    CHECK_API(CameraGetSharpness);
    CameraSetOnceWB = (_CameraSetOnceWB)GetProcAddress(ghSDK, "CameraSetOnceWB");
    CHECK_API(CameraSetOnceWB);
    CameraSetLutMode = (_CameraSetLutMode)GetProcAddress(ghSDK, "CameraSetLutMode");
    CHECK_API(CameraSetLutMode);
    CameraGetLutMode = (_CameraGetLutMode)GetProcAddress(ghSDK, "CameraGetLutMode");
    CHECK_API(CameraGetLutMode);
    CameraSelectLutPreset = (_CameraSelectLutPreset)GetProcAddress(ghSDK, "CameraSelectLutPreset");
    CHECK_API(CameraSelectLutPreset);
    CameraGetLutPresetSel = (_CameraGetLutPresetSel)GetProcAddress(ghSDK, "CameraGetLutPresetSel");
    CHECK_API(CameraGetLutPresetSel);
    CameraSetCustomLut = (_CameraSetCustomLut)GetProcAddress(ghSDK, "CameraSetCustomLut");  
    CHECK_API(CameraSetCustomLut);
    CameraGetCustomLut = (_CameraGetCustomLut)GetProcAddress(ghSDK, "CameraGetCustomLut");
    CHECK_API(CameraGetCustomLut);
    CameraGetCurrentLut = (_CameraGetCurrentLut)GetProcAddress(ghSDK, "CameraGetCurrentLut");
    CHECK_API(CameraGetCurrentLut);
    CameraSetWbMode = (_CameraSetWbMode)GetProcAddress(ghSDK, "CameraSetWbMode");
    CHECK_API(CameraSetWbMode);
    CameraGetWbMode = (_CameraGetWbMode)GetProcAddress(ghSDK, "CameraGetWbMode");
    CHECK_API(CameraGetWbMode);
    CameraSetWbWindow = (_CameraSetWbWindow)GetProcAddress(ghSDK, "CameraSetWbWindow");
    CHECK_API(CameraSetWbWindow);
    CameraIsWbWinVisible = (_CameraIsWbWinVisible)GetProcAddress(ghSDK, "CameraIsWbWinVisible");
    CHECK_API(CameraIsWbWinVisible);
    CameraSaveImage = (_CameraSaveImage)GetProcAddress(ghSDK, "CameraSaveImage");
    CHECK_API(CameraSaveImage);
    CameraSetGain = (_CameraSetGain)GetProcAddress(ghSDK, "CameraSetGain");
    CHECK_API(CameraSetGain);   
    CameraGetGain = (_CameraGetGain)GetProcAddress(ghSDK, "CameraGetGain");
    CHECK_API(CameraGetGain);
    CameraSetGamma = (_CameraSetGamma)GetProcAddress(ghSDK, "CameraSetGamma");
    CHECK_API(CameraSetGamma);
    CameraGetGamma = (_CameraGetGamma)GetProcAddress(ghSDK, "CameraGetGamma");
    CHECK_API(CameraGetGamma);
    CameraSetSaturation = (_CameraSetSaturation)GetProcAddress(ghSDK, "CameraSetSaturation");
    CHECK_API(CameraSetSaturation);
    CameraGetSaturation = (_CameraGetSaturation)GetProcAddress(ghSDK, "CameraGetSaturation");
    CHECK_API(CameraGetSaturation);
    CameraSetContrast = (_CameraSetContrast)GetProcAddress(ghSDK, "CameraSetContrast");
    CHECK_API(CameraSetContrast);
    CameraGetContrast = (_CameraGetContrast)GetProcAddress(ghSDK, "CameraGetContrast");
    CHECK_API(CameraGetContrast);
    CameraSetFrameSpeed = (_CameraSetFrameSpeed)GetProcAddress(ghSDK, "CameraSetFrameSpeed");
    CHECK_API(CameraSetFrameSpeed);
    CameraGetFrameSpeed = (_CameraGetFrameSpeed)GetProcAddress(ghSDK, "CameraGetFrameSpeed");
    CHECK_API(CameraGetFrameSpeed);
    CameraSetAntiFlick = (_CameraSetAntiFlick)GetProcAddress(ghSDK, "CameraSetAntiFlick");
    CHECK_API(CameraSetAntiFlick);    
    CameraGetAntiFlick = (_CameraGetAntiFlick)GetProcAddress(ghSDK, "CameraGetAntiFlick");
    CHECK_API(CameraGetAntiFlick);
    CameraGetLightFrequency = (_CameraGetLightFrequency)GetProcAddress(ghSDK, "CameraGetLightFrequency");
    CHECK_API(CameraGetLightFrequency);
    CameraSetLightFrequency = (_CameraSetLightFrequency)GetProcAddress(ghSDK, "CameraSetLightFrequency");
    CHECK_API(CameraSetLightFrequency);
    CameraSetTransPackLen = (_CameraSetTransPackLen)GetProcAddress(ghSDK, "CameraSetTransPackLen");
    CHECK_API(CameraSetTransPackLen);
    CameraGetTransPackLen = (_CameraGetTransPackLen)GetProcAddress(ghSDK, "CameraGetTransPackLen");
    CHECK_API(CameraGetTransPackLen);
    CameraWriteSN = (_CameraWriteSN)GetProcAddress(ghSDK, "CameraWriteSN");
    CHECK_API(CameraWriteSN);
    CameraReadSN = (_CameraReadSN)GetProcAddress(ghSDK, "CameraReadSN");
    CHECK_API(CameraReadSN);
    CameraGetPresetClrTemp = (_CameraGetPresetClrTemp)GetProcAddress(ghSDK, "CameraGetPresetClrTemp");
    CHECK_API(CameraGetPresetClrTemp);
    CameraSetPresetClrTemp = (_CameraSetPresetClrTemp)GetProcAddress(ghSDK, "CameraSetPresetClrTemp");
    CHECK_API(CameraSetPresetClrTemp);
    CameraSaveParameter = (_CameraSaveParameter)GetProcAddress(ghSDK, "CameraSaveParameter");
    CHECK_API(CameraSaveParameter);
    CameraLoadParameter = (_CameraLoadParameter)GetProcAddress(ghSDK, "CameraLoadParameter");
    CHECK_API(CameraLoadParameter);
    CameraGetCurrentParameterGroup = (_CameraGetCurrentParameterGroup)GetProcAddress(ghSDK, "CameraGetCurrentParameterGroup");
    CHECK_API(CameraGetCurrentParameterGroup);
    CameraEnumerateDevice = (_CameraEnumerateDevice)GetProcAddress(ghSDK, "CameraEnumerateDevice");
    CHECK_API(CameraEnumerateDevice);
    CameraGetCapability = (_CameraGetCapability)GetProcAddress(ghSDK, "CameraGetCapability");
    CHECK_API(CameraGetCapability);
    CameraSoftTrigger = (_CameraSoftTrigger)GetProcAddress(ghSDK, "CameraSoftTrigger");
    CHECK_API(CameraSoftTrigger);
    CameraSetTriggerMode = (_CameraSetTriggerMode)GetProcAddress(ghSDK, "CameraSetTriggerMode");
    CHECK_API(CameraSetTriggerMode);
    CameraGetTriggerMode = (_CameraGetTriggerMode)GetProcAddress(ghSDK, "CameraGetTriggerMode");
    CHECK_API(CameraGetTriggerMode);
    CameraShowSettingPage = (_CameraShowSettingPage)GetProcAddress(ghSDK, "CameraShowSettingPage");
    CHECK_API(CameraShowSettingPage);
    CameraGetFrameStatistic = (_CameraGetFrameStatistic)GetProcAddress(ghSDK, "CameraGetFrameStatistic");
    CHECK_API(CameraGetFrameStatistic);
    CameraGetResolutionForSnap = (_CameraGetResolutionForSnap)GetProcAddress(ghSDK, "CameraGetResolutionForSnap");
    CHECK_API(CameraGetResolutionForSnap);    
    CameraSetResolutionForSnap = (_CameraSetResolutionForSnap)GetProcAddress(ghSDK, "CameraSetResolutionForSnap");
    CHECK_API(CameraSetResolutionForSnap);
    CameraGetNoiseFilterState = (_CameraGetNoiseFilterState)GetProcAddress(ghSDK, "CameraGetNoiseFilterState");
    CHECK_API(CameraGetNoiseFilterState);
    CameraSetParameterMode = (_CameraSetParameterMode)GetProcAddress(ghSDK, "CameraSetParameterMode");
    CHECK_API(CameraSetParameterMode);
    CameraGetParameterMode = (_CameraGetParameterMode)GetProcAddress(ghSDK, "CameraGetParameterMode");
    CHECK_API(CameraGetParameterMode);
    CameraSetParameterMask = (_CameraSetParameterMask)GetProcAddress(ghSDK, "CameraSetParameterMask");
    CHECK_API(CameraSetParameterMask);
    CameraGetTriggerCount = (_CameraGetTriggerCount)GetProcAddress(ghSDK, "CameraGetTriggerCount");
    CHECK_API(CameraGetTriggerCount);
    CameraGetCrossLine = (_CameraGetCrossLine)GetProcAddress(ghSDK, "CameraGetCrossLine");
    CHECK_API(CameraGetCrossLine);
    CameraSetCrossLine = (_CameraSetCrossLine)GetProcAddress(ghSDK, "CameraSetCrossLine");
    CHECK_API(CameraSetCrossLine);
    CameraGetTriggerDelayTime = (_CameraGetTriggerDelayTime)GetProcAddress(ghSDK, "CameraGetTriggerDelayTime");
    CHECK_API(CameraGetTriggerDelayTime);
    CameraSetTriggerDelayTime = (_CameraSetTriggerDelayTime)GetProcAddress(ghSDK, "CameraSetTriggerDelayTime");
    CHECK_API(CameraSetTriggerDelayTime);
    CameraSetAeWinVisible = (_CameraSetAeWinVisible)GetProcAddress(ghSDK, "CameraSetAeWinVisible");
    CHECK_API(CameraSetAeWinVisible);
    CameraSetNoiseFilter = (_CameraSetNoiseFilter)GetProcAddress(ghSDK, "CameraSetNoiseFilter");
    CHECK_API(CameraSetNoiseFilter);
    CameraSetTriggerCount = (_CameraSetTriggerCount)GetProcAddress(ghSDK, "CameraSetTriggerCount");
    CHECK_API(CameraSetTriggerCount);
    CameraCustomizeReferWin = (_CameraCustomizeReferWin)GetProcAddress(ghSDK, "CameraCustomizeReferWin");
    CHECK_API(CameraCustomizeReferWin);
    CameraSetAeWindow = (_CameraSetAeWindow)GetProcAddress(ghSDK, "CameraSetAeWindow");
    CHECK_API(CameraSetAeWindow);
    CameraReadParameterFromFile = (_CameraReadParameterFromFile)GetProcAddress(ghSDK, "CameraReadParameterFromFile");
    CHECK_API(CameraReadParameterFromFile);
    CameraSetWbWinVisible = (_CameraSetWbWinVisible)GetProcAddress(ghSDK, "CameraSetWbWinVisible");
    CHECK_API(CameraSetWbWinVisible);
    CameraRstTimeStamp = (_CameraRstTimeStamp)GetProcAddress(ghSDK, "CameraRstTimeStamp");
    CHECK_API(CameraRstTimeStamp);
    CameraGetCapabilityEx = (_CameraGetCapabilityEx)GetProcAddress(ghSDK, "CameraGetCapabilityEx");
    CHECK_API(CameraGetCapabilityEx);
    CameraLoadUserData = (_CameraLoadUserData)GetProcAddress(ghSDK, "CameraLoadUserData");
    CHECK_API(CameraLoadUserData);
    CameraSaveUserData = (_CameraSaveUserData)GetProcAddress(ghSDK, "CameraSaveUserData");
    CHECK_API(CameraSaveUserData);
    CameraIsOpened = (_CameraIsOpened)GetProcAddress(ghSDK, "CameraIsOpened");
    CHECK_API(CameraIsOpened);
    CameraSetFriendlyName = (_CameraSetFriendlyName)GetProcAddress(ghSDK, "CameraSetFriendlyName");
    CHECK_API(CameraSetFriendlyName);
    CameraGetFriendlyName = (_CameraGetFriendlyName)GetProcAddress(ghSDK, "CameraGetFriendlyName");
    CHECK_API(CameraGetFriendlyName);
    CameraSetUserClrTempGain = (_CameraSetUserClrTempGain)GetProcAddress(ghSDK, "CameraSetUserClrTempGain");
    CHECK_API(CameraSetUserClrTempGain);
    CameraGetUserClrTempGain = (_CameraGetUserClrTempGain)GetProcAddress(ghSDK, "CameraGetUserClrTempGain");
    CHECK_API(CameraGetUserClrTempGain);
    CameraSetUserClrTempMatrix = (_CameraSetUserClrTempMatrix)GetProcAddress(ghSDK, "CameraSetUserClrTempMatrix");
    CHECK_API(CameraSetUserClrTempMatrix);
    CameraGetUserClrTempMatrix = (_CameraGetUserClrTempMatrix)GetProcAddress(ghSDK, "CameraGetUserClrTempMatrix");
    CHECK_API(CameraGetUserClrTempMatrix);
    CameraSetClrTempMode = (_CameraSetClrTempMode)GetProcAddress(ghSDK, "CameraSetClrTempMode");
    CHECK_API(CameraSetClrTempMode);
    CameraGetClrTempMode = (_CameraGetClrTempMode)GetProcAddress(ghSDK, "CameraGetClrTempMode");
    CHECK_API(CameraGetClrTempMode);
    CameraSdkGetVersionString = (_CameraSdkGetVersionString)GetProcAddress(ghSDK, "CameraSdkGetVersionString");
    CHECK_API(CameraSdkGetVersionString);
    CameraCheckFwUpdate = (_CameraCheckFwUpdate)GetProcAddress(ghSDK, "CameraCheckFwUpdate");
    CHECK_API(CameraCheckFwUpdate);
    CameraGetFirmwareVision = (_CameraGetFirmwareVision)GetProcAddress(ghSDK, "CameraGetFirmwareVision");
    CHECK_API(CameraGetFirmwareVision);
    CameraGetEnumInfo = (_CameraGetEnumInfo)GetProcAddress(ghSDK, "CameraGetEnumInfo");
    CHECK_API(CameraGetEnumInfo);
    CameraGetInerfaceVersion = (_CameraGetInerfaceVersion)GetProcAddress(ghSDK, "CameraGetInerfaceVersion");
    CHECK_API(CameraGetInerfaceVersion);
    CameraSetIOState = (_CameraSetIOState)GetProcAddress(ghSDK, "CameraSetIOState");
    CHECK_API(CameraSetIOState);
    CameraGetIOState = (_CameraGetIOState)GetProcAddress(ghSDK, "CameraGetIOState");
    CHECK_API(CameraGetIOState);
    CameraSetBlackLevel = (_CameraSetBlackLevel)GetProcAddress(ghSDK, "CameraSetBlackLevel");
    CHECK_API(CameraSetBlackLevel);
    CameraGetBlackLevel = (_CameraGetBlackLevel)GetProcAddress(ghSDK, "CameraGetBlackLevel");
    CHECK_API(CameraGetBlackLevel);
    CameraSetWhiteLevel = (_CameraSetWhiteLevel)GetProcAddress(ghSDK, "CameraSetWhiteLevel");
    CHECK_API(CameraSetWhiteLevel);
    CameraGetWhiteLevel = (_CameraGetWhiteLevel)GetProcAddress(ghSDK, "CameraGetWhiteLevel");
    CHECK_API(CameraGetWhiteLevel);
    CameraSetIspOutFormat = (_CameraSetIspOutFormat)GetProcAddress(ghSDK, "CameraSetIspOutFormat");
    CHECK_API(CameraSetIspOutFormat);
    CameraGetIspOutFormat = (_CameraGetIspOutFormat)GetProcAddress(ghSDK, "CameraGetIspOutFormat");
    CHECK_API(CameraGetIspOutFormat);
    CameraSetStrobeMode = (_CameraSetStrobeMode)GetProcAddress(ghSDK, "CameraSetStrobeMode");
    CHECK_API(CameraSetStrobeMode);
    CameraGetStrobeMode = (_CameraGetStrobeMode)GetProcAddress(ghSDK, "CameraGetStrobeMode");
    CHECK_API(CameraGetStrobeMode);
    CameraSetStrobeDelayTime = (_CameraSetStrobeDelayTime)GetProcAddress(ghSDK, "CameraSetStrobeDelayTime");
    CHECK_API(CameraSetStrobeDelayTime);
    CameraGetStrobeDelayTime = (_CameraGetStrobeDelayTime)GetProcAddress(ghSDK, "CameraGetStrobeDelayTime");
    CHECK_API(CameraGetStrobeDelayTime);
    CameraSetStrobePulseWidth = (_CameraSetStrobePulseWidth)GetProcAddress(ghSDK, "CameraSetStrobePulseWidth");
    CHECK_API(CameraSetStrobePulseWidth);
    CameraGetStrobePulseWidth = (_CameraGetStrobePulseWidth)GetProcAddress(ghSDK, "CameraGetStrobePulseWidth");
    CHECK_API(CameraGetStrobePulseWidth);
    CameraSetStrobePolarity = (_CameraSetStrobePolarity)GetProcAddress(ghSDK, "CameraSetStrobePolarity");
    CHECK_API(CameraSetStrobePolarity);
    CameraGetStrobePolarity = (_CameraGetStrobePolarity)GetProcAddress(ghSDK, "CameraGetStrobePolarity");
    CHECK_API(CameraGetStrobePolarity);
    CameraSetExtTrigSignalType = (_CameraSetExtTrigSignalType)GetProcAddress(ghSDK, "CameraSetExtTrigSignalType");
    CHECK_API(CameraSetExtTrigSignalType);
    CameraGetExtTrigSignalType = (_CameraGetExtTrigSignalType)GetProcAddress(ghSDK, "CameraGetExtTrigSignalType");
    CHECK_API(CameraGetExtTrigSignalType);
    CameraSetExtTrigShutterType = (_CameraSetExtTrigShutterType)GetProcAddress(ghSDK, "CameraSetExtTrigShutterType");
    CHECK_API(CameraSetExtTrigShutterType);
    CameraGetExtTrigShutterType = (_CameraGetExtTrigShutterType)GetProcAddress(ghSDK, "CameraGetExtTrigShutterType");
    CHECK_API(CameraGetExtTrigShutterType);
    CameraSetExtTrigDelayTime = (_CameraSetExtTrigDelayTime)GetProcAddress(ghSDK, "CameraSetExtTrigDelayTime");
    CHECK_API(CameraSetExtTrigDelayTime);
    CameraGetExtTrigDelayTime = (_CameraGetExtTrigDelayTime)GetProcAddress(ghSDK, "CameraGetExtTrigDelayTime");
    CHECK_API(CameraGetExtTrigDelayTime);
    CameraSetExtTrigJitterTime = (_CameraSetExtTrigJitterTime)GetProcAddress(ghSDK, "CameraSetExtTrigJitterTime");
    CHECK_API(CameraSetExtTrigJitterTime);
    CameraGetExtTrigJitterTime = (_CameraGetExtTrigJitterTime)GetProcAddress(ghSDK, "CameraGetExtTrigJitterTime");
    CHECK_API(CameraGetExtTrigJitterTime);
    CameraGetExtTrigCapability = (_CameraGetExtTrigCapability)GetProcAddress(ghSDK, "CameraGetExtTrigCapability");
    CHECK_API(CameraGetExtTrigCapability);
    CameraGetErrorString = (_CameraGetErrorString)GetProcAddress(ghSDK, "CameraGetErrorString");
    CHECK_API(CameraGetErrorString);
    CameraGetCapabilityEx2 = (_CameraGetCapabilityEx2)GetProcAddress(ghSDK, "CameraGetCapabilityEx2");
    CHECK_API(CameraGetCapabilityEx2);
    CameraGetImageBufferEx2 = (_CameraGetImageBufferEx2)GetProcAddress(ghSDK, "CameraGetImageBufferEx2");
    CHECK_API(CameraGetImageBufferEx2);
    CameraReConnect = (_CameraReConnect)GetProcAddress(ghSDK, "CameraReConnect");
    CHECK_API(CameraReConnect);
    CameraConnectTest = (_CameraConnectTest)GetProcAddress(ghSDK, "CameraConnectTest");
    CHECK_API(CameraConnectTest);
    CameraSetLedBrightness = (_CameraSetLedBrightness)GetProcAddress(ghSDK, "CameraSetLedBrightness");
    CHECK_API(CameraSetLedBrightness);
    CameraGetLedBrightness = (_CameraGetLedBrightness)GetProcAddress(ghSDK, "CameraGetLedBrightness");
    CHECK_API(CameraGetLedBrightness);
    CameraEnableTransferRoi = (_CameraEnableTransferRoi)GetProcAddress(ghSDK, "CameraEnableTransferRoi");
    CHECK_API(CameraEnableTransferRoi);
    CameraSetTransferRoi = (_CameraSetTransferRoi)GetProcAddress(ghSDK, "CameraSetTransferRoi");
    CHECK_API(CameraSetTransferRoi);
    CameraGetTransferRoi = (_CameraGetTransferRoi)GetProcAddress(ghSDK, "CameraGetTransferRoi");
    CHECK_API(CameraGetTransferRoi);
    CameraAlignMalloc = (_CameraAlignMalloc)GetProcAddress(ghSDK, "CameraAlignMalloc");
    CHECK_API(CameraAlignMalloc);
    CameraAlignFree = (_CameraAlignFree)GetProcAddress(ghSDK, "CameraAlignFree");
    CHECK_API(CameraAlignFree);
    CameraSetAutoConnect = (_CameraSetAutoConnect)GetProcAddress(ghSDK, "CameraSetAutoConnect");
    CHECK_API(CameraSetAutoConnect);
    CameraGetReConnectCounts = (_CameraGetReConnectCounts)GetProcAddress(ghSDK, "CameraGetReConnectCounts");
    CHECK_API(CameraGetReConnectCounts);

    


  return CAMERA_STATUS_SUCCESS;
}

CameraSdkStatus UnloadCameraSdk()
{
  if (ghSDK)
  {
    FreeLibrary(ghSDK); 
  } 
  return CAMERA_STATUS_SUCCESS;
}
#endif

#endif
