/**
 *
 *  create_swagger.cc
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  https://github.com/an-tao/drogon
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Drogon
 *
 */

#include "create_swagger.h"
#include <drogon/DrTemplateBase.h>
#include <drogon/utils/Utilities.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <io.h>
#include <direct.h>
#endif
#include <fstream>

using namespace drogon_ctl;
static void createSwagger(const std::string &path)
{
    drogon::HttpViewData data;
    data["docs_url"] = "/swagger";
    std::ofstream ctlHeader(path + "/SwaggerCtrl.h", std::ofstream::out);
    std::ofstream ctlSource(path + "/SwaggerCtrl.cc", std::ofstream::out);
    auto templ = DrTemplateBase::newTemplate("swagger_h.csp");
    ctlHeader << templ->genText(data);
    templ = DrTemplateBase::newTemplate("swagger_cc.csp");
    ctlSource << templ->genText(data);
}
void create_swagger::handleCommand(std::vector<std::string> &parameters)
{
    if (parameters.size() < 1)
    {
        std::cout << "please input a path to create the swagger controller"
                  << std::endl;
        exit(1);
    }
    auto path = parameters[0];
    createSwagger(path);
}