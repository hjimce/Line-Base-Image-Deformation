
#include <assert.h>
#include <cmath>
#include <time.h>

/**********************************************************
* 枚举定义
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
	RESULT_FAILED = -1,  // 失败
	RESULT_OK = 1,          // 成功

	/* 详细失败原因 */
	RESULT_FILE_READ_EXCEPTION = 1001,    // 文件读写异常
	RESULT_FILE_STREAM_EMPTY,                   // 图像字节流为空
	RESULT_PARAM_ERROR,                            // 传入参数错误
	RESULT_ALLOC_MEM_FAILED,                   // 内存分配失败
};

/**********************************************************
* 宏定义
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

// 32位深每个像素占用的字节数
#define BPP32_PER_PIXEL_BYTE 4

// 内存分配失败提示消息
#define ALLOC_MEM_FAILED_MSG  "Allocate Memory Failed."

// 函数参数说明
#define IN
#define OUT
#define IN_OUT

#ifndef M_PI
#define M_PI 3.14159f
#endif


#define LOGGIF(msg) TRACE(msg)
