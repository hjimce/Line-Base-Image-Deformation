
#include <assert.h>
#include <cmath>
#include <time.h>

/**********************************************************
* ö�ٶ���
***********************************************************/
enum MT_COLOR
{
	MT_BLUE = 0,
	MT_GREEN,
	MT_RED,
	MT_ALPHA
};

enum MT_RETURN_RESULT
{
	RESULT_FAILED = -1,  // ʧ��
	RESULT_OK = 1,          // �ɹ�

	/* ��ϸʧ��ԭ�� */
	RESULT_FILE_READ_EXCEPTION = 1001,    // �ļ���д�쳣
	RESULT_FILE_STREAM_EMPTY,                   // ͼ���ֽ���Ϊ��
	RESULT_PARAM_ERROR,                            // �����������
	RESULT_ALLOC_MEM_FAILED,                   // �ڴ����ʧ��
};

/**********************************************************
* �궨��
***********************************************************/
#ifndef MIN
#define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

#undef SAFE_DELETE
#define SAFE_DELETE(x) if((x)!=NULL){delete (x); (x)=NULL;}

#undef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) if((x)!=NULL){delete[] (x); (x)=NULL;}

#define  START_DRAW_POS_X 335
#define  START_DRAW_POS_Y 90

// 32λ��ÿ������ռ�õ��ֽ���
#define BPP32_PER_PIXEL_BYTE 4

// �ڴ����ʧ����ʾ��Ϣ
#define ALLOC_MEM_FAILED_MSG  "Allocate Memory Failed."

// ��������˵��
#define IN
#define OUT
#define IN_OUT

#ifndef M_PI
#define M_PI 3.14159f
#endif


#define LOGGIF(msg) TRACE(msg)
