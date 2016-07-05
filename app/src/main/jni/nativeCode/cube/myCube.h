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

#ifndef MYCUBE_H
#define MYCUBE_H

#include "myLogger.h"
#include "myGLFunctions.h"
#include "myGLCamera.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string>


class MyCube {
public:
    MyCube();
    ~MyCube();
    void    PerformGLInits();
    void    Render();
    void    SetViewport(int width, int height);
    bool    IsInitsDone(){return initsDone;}
    void    DoubleTapAction();
    void    ScrollAction(float distanceX, float distanceY, float positionX, float positionY);
    void    ScaleAction(float scaleFactor);
    void    MoveAction(float distanceX, float distanceY);
    int     GetScreenWidth() const { return screenWidth; }
    int     GetScreenHeight() const { return screenHeight; }

private:
    void    RenderCube();

    bool    initsDone;
    int     screenWidth, screenHeight;

    std::vector<float> modelDefaultPosition;
    MyGLCamera * myGLCamera;

    GLuint  vertexBuffer, colorBuffer; // vertex buffer for triangle's vertices, colors
    GLuint  vertexAttribute, colorAttribute; // attributes for shader variables
    GLuint  shaderProgramID;
    GLint   MVPLocation; // location of MVP in the shader
};

#endif //MYCUBE_H
