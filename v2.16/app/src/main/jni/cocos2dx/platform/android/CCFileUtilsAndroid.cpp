/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCFileUtilsAndroid.h"
#include "support/zip_support/ZipUtils.h"
#include "platform/CCCommon.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "../CCFileUtils.h"

using namespace std;

NS_CC_BEGIN

// record the zip on the resource path
static ZipFile *s_pZipFile = NULL;
//在 s_pZipFile 下添加一个 obb zip包解析
//static ZipFile *s_pZipFileobb = NULL;

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new CCFileUtilsAndroid();
        s_sharedFileUtils->init();
        std::string resourcePath = getApkPath();
        s_pZipFile = new ZipFile(resourcePath, "assets/");
//        getOBBPath();
//        CCFileUtilsAndroid::setOBBPath();
        // begin ------------------代码添加
        //获取obb路径
//         std::string resourcePath_Obb = getObbPath();
         //    创建obbzip
//         s_pZipFileobb = new ZipFile(resourcePath_Obb,"assets/");
//        CCLOG("<==============Zip File obb is %s================>",resourcePath_Obb.c_str());
        // end --------------------代码添加

    }
    return s_sharedFileUtils;
}

// void CCFileUtilsAndroid::setOBBPath(){
    // begin ------------------代码添加
    //获取obb路径
    // std::string resourcePath_Obb = getObbPath();
    // //    创建obbzip
    // s_pZipFileobb = new ZipFile(resourcePath_Obb,"assets/");
//        CCLOG("<==============Zip File obb is %s================>",resourcePath_Obb.c_str());
    // end --------------------代码添加
// }

CCFileUtilsAndroid::CCFileUtilsAndroid()
{
}

CCFileUtilsAndroid::~CCFileUtilsAndroid()
{
    CC_SAFE_DELETE(s_pZipFile);
    //销毁
    // CC_SAFE_DELETE(s_pZipFileobb);
}

bool CCFileUtilsAndroid::init()
{
    m_strDefaultResRootPath = "assets/";
//    m_strDefaultResRootPath = "storage/emulated/0/Android/obb";
    return CCFileUtils::init();
}

bool CCFileUtilsAndroid::isFileExist(const std::string& strFilePath)
{
//    CCLOG("<==============Android : isFileExist================>");
    if (0 == strFilePath.length())
    {
        return false;
    }
//    bool bFound = false;
//
//    if (strFilePath.find("com.jpt.joyland") != std::string::npos)
//    {
//        if (${obbZipFile} && ${obbZipFile}->fileExists(strPath))
//        {
//            bFound = true;
//        }
//    }
    bool bFound = false;
    
    // Check whether file exists in apk.
    if (strFilePath[0] != '/')
    {
        std::string strPath = strFilePath;
        if (strPath.find(m_strDefaultResRootPath) != 0)
        {// Didn't find "assets/" at the beginning of the path, adding it.
//            CCLOG("<==============Android : isFileExist = didn't find assets/ ================>");
            strPath.insert(0, m_strDefaultResRootPath);
        }
        
        if (s_pZipFile->fileExists(strPath))
        {
//            CCLOG("<==============Android : isFileExist = zip is true ================>");
            bFound = true;
        }
        // begin -------------代码添加
//         if(!bFound){
// //            CCLOG("<==============Android : isFileExist = %s ================>",strPath.c_str());
//             if (s_pZipFileobb->fileExists(strPath))
//             {
// //                CCLOG("<==============Android : isFileExist = obb is true ================>");
//                 bFound = true;
//             }
//         }
        // end -----------------代码添加
    }
    else
    {
        FILE *fp = fopen(strFilePath.c_str(), "r");
        if(fp)
        {
            bFound = true;
            fclose(fp);
        }
    }
    return bFound;
}

bool CCFileUtilsAndroid::isAbsolutePath(const std::string& strPath)
{
    // On Android, there are two situations for full path.
    // 1) Files in APK, e.g. assets/path/path/file.png
    // 2) Files not in APK, e.g. /data/data/org.cocos2dx.hellocpp/cache/path/path/file.png, or /sdcard/path/path/file.png.
    // So these two situations need to be checked on Android.
//    CCLOG("<=========isAbsolutePath Android = %s=========>",strPath.c_str());
    if (strPath[0] == '/' || strPath.find(m_strDefaultResRootPath) == 0)
    {
//        CCLOG("<=========isAbsolutePath = true=========>");
        return true;
    }
    return false;
}


unsigned char* CCFileUtilsAndroid::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{    
    return doGetFileData(pszFileName, pszMode, pSize, false);
}

unsigned char* CCFileUtilsAndroid::getFileDataForAsync(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    return doGetFileData(pszFileName, pszMode, pSize, true);
}

unsigned char* CCFileUtilsAndroid::doGetFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize, bool forAsync)
{
//    CCLOG("<==============Android : doGetFileData ================>");
    unsigned char * pData = 0;
    
    if ((! pszFileName) || (! pszMode) || 0 == strlen(pszFileName))
    {
        return 0;
    }
    
    
//    string fullPath = fullPathForFilename(pszFileName);
//
//    // 获取obb文件
//    if ("main.3.com.jpt.joyland.obb" && fullPath.find("main.3.com.jpt.joyland.obb") != std::string::npos){
//
//        if (forAsync)
//        {
//            pData = ${obbZipFile}->getFileData(fullPath.c_str(), pSize, ${obbZipFile}->_dataThread);
//        }
//        else
//        {
//            pData = ${obbZipFile}->getFileData(fullPath.c_str(), pSize);
//        }
//    }
    
    string fullPath = fullPathForFilename(pszFileName);
    
    if (fullPath[0] != '/')
    {
        if (forAsync)
        {
            pData = s_pZipFile->getFileData(fullPath.c_str(), pSize, s_pZipFile->_dataThread);
            // begin -------------代码添加
//             if (! pData)
//             {
//                 pData = s_pZipFileobb->getFileData(fullPath.c_str(), pSize, s_pZipFile->_dataThread);
// //                CCLOG("<=======1======Android : doGetFileData %s================>",pData);
//             }
            //end -------------代码添加
        }
        else
        {
            pData = s_pZipFile->getFileData(fullPath.c_str(), pSize);
            // begin -------------代码添加
//             if (! pData)
//             {
//                 pData = s_pZipFileobb->getFileData(fullPath.c_str(), pSize);
// //                CCLOG("<=======2======Android : doGetFileData %s================>",pData);
//             }
            //end -------------代码添加
        }
    }
    else
    {
        do
        {
            // read rrom other path than user set it
	        //CCLOG("GETTING FILE ABSOLUTE DATA: %s", pszFileName);
            FILE *fp = fopen(fullPath.c_str(), pszMode);
            CC_BREAK_IF(!fp);
            
            unsigned long size;
            fseek(fp,0,SEEK_END);
            size = ftell(fp);
            fseek(fp,0,SEEK_SET);
            pData = new unsigned char[size];
            size = fread(pData,sizeof(unsigned char), size,fp);
            fclose(fp);
            
            if (pSize)
            {
                *pSize = size;
            }
        } while (0);
    }
    
    if (! pData)
    {
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    
    return pData;
}

string CCFileUtilsAndroid::getWritablePath()
{
    // Fix for Nexus 10 (Android 4.2 multi-user environment)
    // the path is retrieved through Java Context.getCacheDir() method
    string dir("");
    string tmp = getFileDirectoryJNI();

    if (tmp.length() > 0)
    {
        dir.append(tmp).append("/");

        return dir;
    }
    else
    {
        return "";
    }
}

NS_CC_END
