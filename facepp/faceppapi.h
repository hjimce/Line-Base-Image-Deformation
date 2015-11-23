#ifndef _FACEPPAPI_H_
#define _FACEPPAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__WIN32__) || defined(_WIN32)

#ifdef FACEPPLIB
	#define FACEPP_EXPORT __declspec(dllexport)
#else
	#define FACEPP_EXPORT __declspec(dllimport)
#endif

#else

#ifdef FACEPPLIB
	#define FACEPP_EXPORT __attribute__ ((visibility("default")))
#else
	#define FACEPP_EXPORT
#endif

#endif

#define FACEPP_DETECTMODEACCURACY_LOW       0x0
#define FACEPP_DETECTMODEACCURACY_TRACKING	0x1
#define FACEPP_DETECTMODEACCURACY_HIGH		0x2

#define FACEPP_ATTRIBUTEMODE_NONE           0x0
#define FACEPP_ATTRIBUTEMODE_LANDMARK       0x1
#define FACEPP_ATTRIBUTEMODE_YAW            0x2
#define FACEPP_ATTRIBUTEMODE_ROLL           0x4
#define FACEPP_ATTRIBUTEMODE_SMILE          0x8
#define FACEPP_ATTRIBUTEMODE_LANDMARK39     0x10

#define FACEPP_YAW_UNKNOW                   -1
#define FACEPP_YAW_LARGELEFT                0x0
#define FACEPP_YAW_MEDIUMLEFT               0x1
#define FACEPP_YAW_SMALLLEFT                0x2
#define FACEPP_YAW_FRONTAL                  0x3
#define FACEPP_YAW_SMALLRIGHT               0x4
#define FACEPP_YAW_MEDIUMRIGHT              0x5
#define FACEPP_YAW_LARGERIGHT               0x6

typedef struct {
    int top, bottom, left, right;
} FACEPP_RECT;

typedef struct {
    int x, y;
} FACEPP_POINT;

typedef enum {
	CONTOUR_CHIN = 0,
	CONTOUR_LEFT1,
	CONTOUR_LEFT2,
	CONTOUR_LEFT4,
	CONTOUR_LEFT6,
	CONTOUR_LEFT8,
	CONTOUR_RIGHT1,
	CONTOUR_RIGHT2,
	CONTOUR_RIGHT4,
	CONTOUR_RIGHT6,
	CONTOUR_RIGHT8,
	LEFT_EYE_BOTTOM,
	LEFT_EYE_LEFT_CORNER,
	LEFT_EYE_PUPIL,
	LEFT_EYE_RIGHT_CORNER,
	LEFT_EYE_TOP,
	LEFT_EYEBROW_LEFT_CORNER,
	LEFT_EYEBROW_LOWER_MIDDLE,
	LEFT_EYEBROW_RIGHT_CORNER,
	LEFT_EYEBROW_UPPER_MIDDLE,
	MOUTH_LEFT_CORNER,
	MOUTH_LOWER_LIP_BOTTOM,
	MOUTH_LOWER_LIP_TOP,
	MOUTH_RIGHT_CORNER,
	MOUTH_UPPER_LIP_BOTTOM,
	MOUTH_UPPER_LIP_TOP,
	NOSE_CONTOUR_LOWER_MIDDLE,
	NOSE_LEFT,
	NOSE_RIGHT,
	NOSE_TIP,
	RIGHT_EYE_BOTTOM,
	RIGHT_EYE_LEFT_CORNER,
	RIGHT_EYE_PUPIL,
	RIGHT_EYE_RIGHT_CORNER,
	RIGHT_EYE_TOP,
	RIGHT_EYEBROW_LEFT_CORNER,
	RIGHT_EYEBROW_LOWER_MIDDLE,
	RIGHT_EYEBROW_RIGHT_CORNER,
	RIGHT_EYEBROW_UPPER_MIDDLE,
	LANDMARK_COUNT
} FACEPP_LANDMARK;

typedef struct {
    int rollangle;//侧脸角度 -180 ~ 180
    int yawAngle;//摇脸角度
    int smileLevel;//微笑程度 0 ~ 100
    FACEPP_RECT rFace;// face position in a rectangle
    FACEPP_POINT pLeftEye, pRightEye; //left and right eye position
    FACEPP_POINT pLeftMouthCorner, pRightMouthCorner; //the position about left and right corner of the mouth
    FACEPP_POINT pNose; // the nose position
    FACEPP_POINT landmarks[LANDMARK_COUNT];
} FACEPP_FACEINFO;

/* initialization function, you need call it first
 */
void FACEPP_EXPORT facepp_init();

/* default is NONE mode
 * example:
 *      facepp_setAttributeMode(FACEPP_ATTRIBUTEMODE_LANDMARK | FACEPP_ATTRIBUTEMODE_ROLL);
 */
void FACEPP_EXPORT facepp_setAttributeMode(int mode);

/* default is high mode, has 3 modes
 * FACEPP_DETECTMODEACCURACY_LOW       <--- faster than high
 * FACEPP_DETECTMODEACCURACY_TRACKING  <--- fastest, but need multiply frams and the result worse than others
 * FACEPP_DETECTMODEACCURACY_HIGH      <--- the highest one
 */
void FACEPP_EXPORT facepp_setDetectionMode(int mode);

/* return value : face number
 * if width x height > 320 x 320 then orientation doesnot work
 * orientation setting :
 *      +----+         +--------+        +----+      +--------+
 * 90 : |    |  180 :  |me      |  270 : |menu|  0 : |      me|
 *      |    |         |nu      |        |    |      |      nu|
 *      |    |         +--------+        |    |      +--------+
 *      |menu|                           |    |
 *      +----+                           +----+
 */
int FACEPP_EXPORT facepp_detect(unsigned char *data, int width, int height, FACEPP_FACEINFO *ptr, int maxFaceNum, int orientation);

/* the same funtion like facepp_setDetectionMode, but use scaled coordinate to output
 * (-1000, -1000)          (1000, -1000)
 *       +---------+----------+
 *       |         |          |
 *       +---------+----------+
 *       |         | (0, 0)   |
 *       +---------+----------+
 * (-1000, 1000)           (1000, 1000)
 */
int FACEPP_EXPORT facepp_detectScaled(unsigned char *data, int width, int height, FACEPP_FACEINFO *ptr, int maxFaceNum, int orientation);

int FACEPP_EXPORT facepp_detect360Tracking(unsigned char *data, int width, int height, FACEPP_FACEINFO *ptr, int maxFaceNum);
int FACEPP_EXPORT facepp_detect360TrackingScaled(unsigned char *data, int width, int height, FACEPP_FACEINFO *ptr, int maxFaceNum);
int FACEPP_EXPORT facepp_detect360High(unsigned char *data, int width, int height, FACEPP_FACEINFO *ptr, int maxFaceNum);
int FACEPP_EXPORT facepp_detect360HighScaled(unsigned char *data, int width, int height, FACEPP_FACEINFO *ptr, int maxFaceNum);

/* orientation : the image right orientation, if return value is 0 the value of orientation would be -1
 */
int FACEPP_EXPORT facepp_detect360TrackingScaled_ornt(unsigned char *data, int width, int height, FACEPP_FACEINFO *ptr, int maxFaceNum, int* orientation);

/* the release funtion, you need call it at last to free the memory
 */
void FACEPP_EXPORT facepp_release();

#ifdef __cplusplus
}
#endif

#endif //_FACEPPAPI_H_
