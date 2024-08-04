/* 
 * File:   common.cpp
 * Author: Wouter
 * 
 * Created on January 25, 2009, 9:53 PM
 */

#include "common.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

String Common::filePath(String in)
{
    if (in != 0)
    {
        int len = strlen(in);
        char tmp[256] = { 0 };

        for (int i = len; i >= 0; i--)
        {
            if (in[i] == '/' || in[i] == '\\')
            {
                strncpy(tmp, in, i);
                return (String)tmp;
            }
        }
    }
    return "";
}

String Common::fileBaseName(String in)
{
    const char* basename = strrchr(in, '/');
    if (basename == 0)
            basename = strrchr(in, '\\');
    basename++;

    if (basename != 0)
    {
        int len = strlen(basename);
        char tmp[256] = { 0 };

        for (int i = len; i >= 0; i--)
        {
            if (basename[i] == '.')
            {
                strncpy(tmp, basename, i);
                return (String)tmp;
            }
        }
        return (String)basename;
    }
    return "";
}

String Common::fileName(String in)
{
    const char* filename = strrchr(in, '/');

    if (filename == 0)
        filename = strrchr(in, '\\');

    if (filename != 0)
    {
        filename++;
        return (String)filename;
    }

    return "";
}

String Common::fileExtention(String in)
{
    const char* ext = strrchr(in, '.');

    if (ext != 0)
        return (String)ext;

    return "";
}

int Common::fileTime(String path)
{
    struct stat buf;

    if (stat(path,&buf) == -1)
        return -1;

    return buf.st_mtime;
}
