/* 
 * File:   common.h
 * Author: Wouter
 *
 * Created on January 25, 2009, 9:53 PM
 */

#ifndef _COMMON_H
#define	_COMMON_H

#include "string.h"

class Common
{
public:
    static String filePath(String in);
    static String fileBaseName(String in);
    static String fileName(String in);
    static String fileExtention(String in);
    static int fileTime(String path);
};

#endif	/* _COMMON_H */

