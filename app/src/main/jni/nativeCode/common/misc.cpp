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

#include "misc.h"

/**
 * Strip out the path and return just the filename
 */
std::string GetFileName(std::string file_name) {

    // assume filename is of the form "<path>/<name>.<type>"
    std::string::size_type slashIndex = file_name.find_last_of("/");

    std::string only_name;
    if (slashIndex == std::string::npos) {
        only_name = file_name.substr(0, std::string::npos);
    } else {
        only_name = file_name.substr(slashIndex + 1, std::string::npos);
    }

    return only_name;
}

/**
 * Print the contents of a Glm 4x4 matrix
 */
void PrintGlmMat(glm::mat4 testMat) {

    MyLOGD("%f %f %f %f", testMat[0][0],testMat[1][0],testMat[2][0],testMat[3][0]);
    MyLOGD("%f %f %f %f", testMat[0][1],testMat[1][1],testMat[2][1],testMat[3][1]);
    MyLOGD("%f %f %f %f", testMat[0][2],testMat[1][2],testMat[2][2],testMat[3][2]);
    MyLOGD("%f %f %f %f", testMat[0][3],testMat[1][3],testMat[2][3],testMat[3][3]);

}