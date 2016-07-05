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


#include "myGLCamera.h"
#include "myLogger.h"
#include "math.h"

MyGLCamera::MyGLCamera(
        float FOV,
        float zPosition,
        float nearPlane,
        float farPlane) {

    // camera position is fixed
    glm::vec3 cameraPosition = glm::vec3(0, 0, zPosition);  // 3 DOF
    viewMat = glm::lookAt(cameraPosition,        // Camera location in World Space
                          glm::vec3(0, 0, -1),   // direction in which camera it is pointed
                          glm::vec3(0, 1, 0));   // camera is pointing up
    modelMat        = glm::mat4(1.0f);
    translateMat    = glm::mat4(1.0f);
    rotateMat       = glm::mat4(1.0f);
    MVP             = glm::mat4(1.0f);

    this->nearPlane = nearPlane;
    this->farPlane  = farPlane;
    this->FOV       = FOV;

    // 6DOF describing model's position
    xCoord = yCoord = zCoord = 0;            // translations
    modelQuaternion = glm::quat(glm::vec3(0,0,0));
}

/**
 * Use the display's aspect ratio to compute projection matrix
 */
void MyGLCamera::SetAspectRatio(float aspect) {

    glm::mat4 projectionMat;
    projectionMat = glm::perspective(FOV * float(M_PI / 180), aspect,
                                     nearPlane, farPlane);
    projectionViewMat = projectionMat * viewMat;
    ComputeMVPMatrix();

}

/**
 * Model's position has 6 degrees-of-freedom: 3 for x-y-z locations and
 * 3 for alpha-beta-gamma Euler angles
 * Convert euler angles to quaternion and update MVP
 */
void MyGLCamera::SetModelPosition(std::vector<float> modelPosition) {

    xCoord      = modelPosition[0];
    yCoord      = modelPosition[1];
    zCoord      = modelPosition[2];
    float alphaAngle  = modelPosition[3];
    float betaAngle   = modelPosition[4];
    float gammaAngle  = modelPosition[5];

    modelQuaternion = glm::quat(glm::vec3(alphaAngle, betaAngle, gammaAngle));
    rotateMat = glm::toMat4(modelQuaternion);
    ComputeMVPMatrix();
}


/**
 * Compute the translation matrix from x-y-z position and rotation matrix from
 * quaternion describing the rotation
 * MVP = Projection * View * (Translation * Rotation)
 */
void MyGLCamera::ComputeMVPMatrix() {

    translateMat = glm::mat4(1, 0, 0, 0,                  // col1
                             0, 1, 0, 0,	              // col2
                             0, 0, 1, 0,	              // col3
                             xCoord, yCoord, zCoord, 1);  // col4

    modelMat    = translateMat * rotateMat;
    MVP         = projectionViewMat * modelMat;
}

/**
 * Simulate change in scale by pushing or pulling the model along Z axis
 */
void MyGLCamera::ScaleModel(float scaleFactor) {

    zCoord += SCALE_TO_Z_TRANSLATION*(scaleFactor-1);
    ComputeMVPMatrix();
}

/**
 * Finger drag movements are converted to rotation of model by deriving a
 * quaternion from the drag movement
 */
void MyGLCamera::RotateModel(float distanceX, float distanceY, float positionX, float positionY) {

    // algo in brief---
    // assume that a sphere with its center at (0,0), i.e., center of screen, and
    // radius 1 is placed on the device.
    // drag movement on the surface is translated to a drag on the imaginary sphere's surface
    // since we know (x,y) coordinates of the drag, we only need to determine z-coordinate
    // corresponding to the height of sphere's surface corresponding to the drag position.
    // begin and end of drag define two points on sphere and we create two vectors joining those
    // points with the origin (0,0).
    // lastly we create a quaternion responsible for rotation between the two vectors.

    // compute ending vector (using positionX, positionY)
    float dist = sqrt(fmin(1, positionX*positionX + positionY*positionY));
    float positionZ = sqrt(1 - dist*dist);
    glm::vec3 endVec = glm::vec3(positionX, positionY, positionZ);
    endVec = glm::normalize(endVec);

    // compute starting vector by adding (distanceX, distanceY) to ending positions
    positionX += distanceX;
    positionY += distanceY;
    dist = sqrt(fmin(1, positionX*positionX + positionY*positionY));
    positionZ = sqrt(1 - dist*dist);
    glm::vec3 beginVec = glm::vec3(positionX, positionY, positionZ);
    beginVec = glm::normalize(beginVec);

    // compute cross product of vectors to find axis of rotation
    glm::vec3 rotationAxis = glm::cross(beginVec, endVec);
    rotationAxis = glm::normalize(rotationAxis);

    // compute angle between vectors using the dot product
    float dotProduct = fmax(fmin(glm::dot(beginVec, endVec), 1.), -1.);
    float rotationAngle = TRANSLATION_TO_ANGLE*acos(dotProduct);

    // compute quat using above
    modelQuaternion = glm::angleAxis(rotationAngle, rotationAxis);
    rotateMat = glm::toMat4(modelQuaternion)*rotateMat;

    ComputeMVPMatrix();
}

/**
 * displace model by changing x-y coordinates
 */
void MyGLCamera::TranslateModel(float distanceX, float distanceY) {

    xCoord += XY_TRANSLATION_FACTOR*distanceX;
    yCoord += XY_TRANSLATION_FACTOR*distanceY;
    ComputeMVPMatrix();
}