#include <jni.h>
#include <ALog.h>
#include <cstring>


//java类型对应的签名如下
//boolean       Z
//byte          B
//char          C
//short         S
//int           I
//long          J
//float         F
//double        D
//String        Ljava/lang/String;
//Class         Ljava/lang/Class;
//Throwable     Ljava/lang/Throwable;
//int[]         [I
//Object[]      [Ljava/lang/Object;
//double[][]    [[D

//note:use "/" not "." to splite
char beanPackage[] = "com/junmeng/libnative/bean";

typedef struct{
    int x;
    int y;

}xy_value;

/**
 * 将java对象转为native层结构体
 * @param[in] env
 * @param[in] xy
 * @param[out] xyValue
 * @return 是否成功
 */
bool toXYValue(JNIEnv *env, jobject xy,xy_value * xyValue) {

    jclass xy_cls = env->GetObjectClass(xy);
    if (xy_cls == NULL) {
        LOGE("toXYValue failed.");
        return false;
    }
    jfieldID xFieldID = env->GetFieldID(xy_cls, "x", "I");
    jfieldID yFieldID = env->GetFieldID(xy_cls, "y", "I");

    jint x = env->GetIntField(xy, xFieldID);
    jint y = env->GetIntField(xy, yFieldID);
    xyValue->x = x;
    xyValue->y = y;
    LOGI("toXYValue: x=%d,y=%d", x, y);
    return true;
}

jobject xy2jobject(JNIEnv *env, xy_value xyValue) {
    char cls_path[64];
    strcpy(cls_path, beanPackage);
    strcat(cls_path, "/XY");
    jclass clas = env->FindClass(cls_path);
    if (clas == NULL) {
        LOGE("%s failed.", cls_path);
        return NULL;
    }
    jmethodID construct = env->GetMethodID(clas, "<init>", "()V");//<init>表示构造函数，()V表示无参数无返回值

    //第一种方式
    jobject obj = env->NewObject(clas, construct);

    //第二种方式
    //jobject obj = env->AllocObject(clas);
    //env->CallNonvirtualVoidMethod(obj,clas,construct);


    jfieldID xFieldID = env->GetFieldID(clas, "x", "I");
    jfieldID yFieldID = env->GetFieldID(clas, "y", "I");
    env->SetIntField(obj, xFieldID, xyValue.x);
    env->SetIntField(obj, yFieldID, xyValue.y);
    return obj;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_junmeng_libnative_JniObject_change(
        JNIEnv *env,
        jclass clazz,
        jobject xy) {

    xy_value xyvalue;
    toXYValue(env,xy,&xyvalue);
    xyvalue.x=1;
    xyvalue.y=1;
    jobject obj=xy2jobject(env,xyvalue);

    return obj;
}



