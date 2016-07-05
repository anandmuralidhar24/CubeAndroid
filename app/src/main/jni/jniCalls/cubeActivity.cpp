/*
 *    Copyright 2016 Anand Muralidhar
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <jni.h>
#include "myCube.h"
#include "myJNIHelper.h"

#ifdef __cplusplus
extern "C" {
#endif

// global pointer is used in JNI calls to reference to same object of type Cube
MyCube *gCubeObject =NULL;

// global pointer to instance of MyJNIHelper that is used to read from assets
MyJNIHelper * gHelperObject=NULL;

/**
 * Create the persistent native object and also initialize the single helper object
 */
JNIEXPORT void JNICALL
Java_com_anandmuralidhar_cubeandroid_CubeActivity_CreateObjectNative(JNIEnv *env,
                                                                             jobject instance,
                                                                             jobject assetManager,
                                                                             jstring pathToInternalDir) {

    gHelperObject = new MyJNIHelper(env, instance, assetManager, pathToInternalDir);
    gCubeObject = new MyCube();
}

JNIEXPORT void JNICALL
Java_com_anandmuralidhar_cubeandroid_CubeActivity_DeleteObjectNative(JNIEnv *env,
                                                                             jobject instance) {
    if (gCubeObject != NULL) {
        delete gCubeObject;
    }
    gCubeObject = NULL;

    if (gHelperObject != NULL) {
        delete gHelperObject;
    }
    gHelperObject = NULL;
}

#ifdef __cplusplus
}
#endif
