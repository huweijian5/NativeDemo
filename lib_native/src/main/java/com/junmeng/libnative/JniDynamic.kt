package com.junmeng.libnative

/**
 * 演示动态注册
 */
object JniDynamic {

    init {
        System.loadLibrary("dynamic-lib")
    }

    /**
     * 加１
     * 动态注册演示（比静态注册速度快，静态注册有个查找的过程），在JNI_OnLoad中实现动态注册
     */
    external fun addone(i: Int): Int
    /**
     * 动态注册演示
     */
    external fun stringFromJNI(s:String):String
}