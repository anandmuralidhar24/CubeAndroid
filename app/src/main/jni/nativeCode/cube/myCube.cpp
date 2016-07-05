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

#include "myShader.h"
#include "myCube.h"

/**
 * Class constructor
 */
MyCube::MyCube() {

    MyLOGD("MyCube::MyCube");
    initsDone = false;

    // create MyGLCamera object and set default position for the object
    myGLCamera = new MyGLCamera();
    float pos[]={0.,0.,0.,1,1,0.};
    std::copy(&pos[0], &pos[5], std::back_inserter(modelDefaultPosition));
    myGLCamera->SetModelPosition(modelDefaultPosition);
}

MyCube::~MyCube() {

    MyLOGD("MyCube::~MyCube");
    if (myGLCamera) {
        delete myGLCamera;
    }
}

/**
 * Perform inits and load the triangle's vertices/colors to GLES
 */
void MyCube::PerformGLInits() {

    MyLOGD("MyCube::PerformGLInits");
    if (initsDone) {
        return;
    }

    MyGLInits();

    GLfloat cubeVertices[] = {
            -1.0f,-1.0f,-1.0f,  // face0 left
            -1.0f,-1.0f, 1.0f,  //     0
            -1.0f, 1.0f, 1.0f,  //     0
            -1.0f,-1.0f,-1.0f,  //     0
            -1.0f, 1.0f, 1.0f,  //     0
            -1.0f, 1.0f,-1.0f,  //     0
             1.0f,-1.0f,-1.0f,  // face1 right
             1.0f, 1.0f, 1.0f,  //     1
             1.0f,-1.0f, 1.0f,  //     1
             1.0f,-1.0f,-1.0f,  //     1
             1.0f, 1.0f,-1.0f,  //     1
             1.0f, 1.0f, 1.0f,  //     1
             1.0f,-1.0f, 1.0f,  // face2 down
            -1.0f,-1.0f,-1.0f,  //     2
             1.0f,-1.0f,-1.0f,  //     2
            -1.0f,-1.0f,-1.0f,  //     2
             1.0f,-1.0f, 1.0f,  //     2
            -1.0f,-1.0f, 1.0f,  //     2
            -1.0f, 1.0f, 1.0f,  // face3 top
             1.0f, 1.0f, 1.0f,  //     3
            -1.0f, 1.0f,-1.0f,  //     3
            -1.0f, 1.0f,-1.0f,  //     3
             1.0f, 1.0f, 1.0f,  //     3
             1.0f, 1.0f,-1.0f,  //     3
             1.0f, 1.0f, 1.0f,  // face4 front
            -1.0f, 1.0f, 1.0f,  //     4
             1.0f,-1.0f, 1.0f,  //     4
            -1.0f, 1.0f, 1.0f,  //     4
            -1.0f,-1.0f, 1.0f,  //     4
             1.0f,-1.0f, 1.0f,  //     4
            -1.0f, 1.0f,-1.0f,  // face5 back
             1.0f, 1.0f,-1.0f,  //     5
             1.0f,-1.0f,-1.0f,  //     5
             1.0f,-1.0f,-1.0f,  //     5
            -1.0f,-1.0f,-1.0f,  //     5
            -1.0f, 1.0f,-1.0f   //     5
    };

    // Generate a vertex buffer and load the vertices into it
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    GLfloat cubeFaceColors[] = {
            1.0f, 0.0f, 0.0f, // red    - face0
            1.0f, 0.0f, 0.0f, //              0
            1.0f, 0.0f, 0.0f, //              0
            1.0f, 0.0f, 0.0f, //              0
            1.0f, 0.0f, 0.0f, //              0
            1.0f, 0.0f, 0.0f, //              0
            0.0f, 1.0f, 1.0f, // cyan   - face1
            0.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 0.0f, // green  - face2
            0.0f, 1.0f, 0.0f, //              2
            0.0f, 1.0f, 0.0f, //              2
            0.0f, 1.0f, 0.0f, //              2
            0.0f, 1.0f, 0.0f, //              2
            0.0f, 1.0f, 0.0f, //              2
            1.0f, 0.0f, 1.0f, // violet - face3
            1.0f, 0.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, //              3
            0.0f, 0.0f, 1.0f, // blue   - face4
            0.0f, 0.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, //              4
            1.0f, 1.0f, 0.0f, // yellow - face5
            1.0f, 1.0f, 0.0f, //              5
            1.0f, 1.0f, 0.0f, //              5
            1.0f, 1.0f, 0.0f, //              5
            1.0f, 1.0f, 0.0f, //              5
            1.0f, 1.0f, 0.0f, //              5
    };

    // Generate a vertex buffer and load the colors into it
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeFaceColors), cubeFaceColors, GL_STATIC_DRAW);

    // shader related setup
    std::string vertexShader    = "cubeMVP.vsh";
    std::string fragmentShader  = "cubeMVP.fsh";

    // compile the vertex and fragment shaders, and link them together
    shaderProgramID = LoadShaders(vertexShader, fragmentShader);
    // fetch the locations of "vertexPosition" and "vertexColor" from the shader
    vertexAttribute = GetAttributeLocation(shaderProgramID, "vertexPosition");
    colorAttribute  = GetAttributeLocation(shaderProgramID, "vertexColor");
    MVPLocation     = GetUniformLocation(shaderProgramID, "MVP");

    CheckGLError("Cube::PerformGLInits");
    initsDone = true;
}

/**
 * Render our colorful cube
 */
void MyCube::RenderCube() {
    // use the shader
    glUseProgram(shaderProgramID);

    glm::mat4 MVP = myGLCamera->GetMVP();
    glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, (const GLfloat *) &MVP);

    // enable the vertex buffer
    glEnableVertexAttribArray(vertexAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer( vertexAttribute, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    // enable the color buffer
    glEnableVertexAttribArray(colorAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer( colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    // Draw the colorful triangle
    glDrawArrays(GL_TRIANGLES, 0, 36); // cube has 12 triangles = 36 vertices.

    glDisableVertexAttribArray(vertexAttribute);
    glDisableVertexAttribArray(colorAttribute);
}

/**
 * Render to the display
 */
void MyCube::Render() {

    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderCube();
    CheckGLError("Cube::Render");

}

/**
 * set the viewport, function is also called when user changes device orientation
 */
void MyCube::SetViewport(int width, int height) {

    screenHeight = height;
    screenWidth = width;
    glViewport(0, 0, width, height);
    CheckGLError("Cube::SetViewport");

    myGLCamera->SetAspectRatio((float) width / height);
}


/**
 * reset model's position in double-tap
 */
void MyCube::DoubleTapAction() {

    myGLCamera->SetModelPosition(modelDefaultPosition);
}

/**
 * rotate the model if user scrolls with one finger
 */
void MyCube::ScrollAction(float distanceX, float distanceY, float positionX, float positionY) {

    myGLCamera->RotateModel(distanceX, distanceY, positionX, positionY);
}

/**
 * pinch-zoom: move the model closer or farther away
 */
void MyCube::ScaleAction(float scaleFactor) {

    myGLCamera->ScaleModel(scaleFactor);
}

/**
 * two-finger drag: displace the model by changing its x-y coordinates
 */
void MyCube::MoveAction(float distanceX, float distanceY) {

    myGLCamera->TranslateModel(distanceX, distanceY);
}