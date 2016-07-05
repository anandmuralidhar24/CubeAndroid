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


#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <vector>
#include "misc.h"

// sensitivity coefficients for translating gestures to model's movements
#define SCALE_TO_Z_TRANSLATION  20
#define TRANSLATION_TO_ANGLE    5
#define XY_TRANSLATION_FACTOR   10

class MyGLCamera {
public:
    MyGLCamera(
            float FOV = 45,          // in degrees
            float zPosition = 10,    // camera's location on Z axis
            float nearPlane = 1.0f, // as large as possible
            float farPlane = 2000.0f // as small as possible
    );
    void        SetModelPosition(std::vector<float> modelPosition);
    void        SetAspectRatio(float aspect);
    glm::mat4   GetMVP(){ return MVP; }
    void        RotateModel(float distanceX, float distanceY, float positionX, float positionY);
    void        ScaleModel(float scaleFactor);
    void        TranslateModel(float distanceX, float distanceY);

private:
    void ComputeMVPMatrix();

    float aspect;
    float FOV;
    float nearPlane, farPlane;

    glm::mat4 projectionViewMat;
    glm::mat4 rotateMat, translateMat;
    glm::mat4 modelMat;
    glm::mat4 viewMat;
    // ModelViewProjection : obtained by multiplying Projection, View, Model mats
    glm::mat4 MVP;

    glm::quat modelQuaternion;
    float xCoord, yCoord, zCoord;
};

#endif //GLCAMERA_H
