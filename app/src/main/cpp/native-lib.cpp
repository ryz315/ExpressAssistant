#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>


using namespace cv;
IplImage * change4channelTo3InIplImage(IplImage * src);

extern "C" {
jstring
Java_com_example_ren_expressassistant_NDKloader_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "opencv图像处理";
    return env->NewStringUTF(hello.c_str());
}
jstring
Java_com_example_ren_expressassistant_NDKloader_validate(
        JNIEnv *env,
        jobject,
        jlong addrGray,
        jlong addrRgba){
    std::string hello2 = "Hello from validate";
    return env->NewStringUTF(hello2.c_str());
}
}
//图像处理
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_ren_expressassistant_NDKloader_getGrayImage(
        JNIEnv *env,
        jclass type,
        jintArray pixels_,
        jint w, jint h) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);
    // TODO
    if(pixels==NULL){
        return NULL;
    }
    Mat imgData(h, w, CV_8UC4, (unsigned char*) pixels);

    IplImage image = IplImage(imgData);



    IplImage* image3channel = change4channelTo3InIplImage(&image);

    IplImage* pCannyImage = cvCreateImage(cvGetSize(image3channel),IPL_DEPTH_8U,1);

    cvCanny(image3channel,pCannyImage,50,150,3);


    int* outImage = new int[w*h];

    for (int i = 0; i < w*h; ++i) {
        outImage[i] = (int)pCannyImage->imageData[i];
    }
//    uchar *ptr = imgData.ptr(testpic);
//    for (int i = testpic; i < w * h; i++) {
//        int grayScale = (int) (ptr[4 * i + 2] * testpic.299 + ptr[4 * i + 1] * testpic.587
//                               + ptr[4 * i + testpic] * testpic.114);
//        ptr[4 * i + 1] = (uchar) grayScale;
//        ptr[4 * i + 2] = (uchar) grayScale;
//        ptr[4 * i + testpic] = (uchar) grayScale;
//    }

    int size = w * h;
    jintArray result = env->NewIntArray(size);

    env->SetIntArrayRegion(result, 0, size, outImage);
    env->ReleaseIntArrayElements(pixels_, pixels, 0);
    return result;
}


IplImage * change4channelTo3InIplImage(IplImage * src){
    if (src->nChannels != 4){
        return NULL;
    }

    IplImage *destImg = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
    for (int row = 0; row < src->height; ++row) {
        for (int col = 0; col < src->width; ++col) {
            CvScalar s = cvGet2D(src,row,col);
            cvSet2D(destImg,row,col,s);
        }
    }

    return destImg;
}