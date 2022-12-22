//
// Created by w on 2022/12/23.
//

#ifndef STUDENTSYSTEM_TOOLS_HPP
#define STUDENTSYSTEM_TOOLS_HPP

#include "QString"

inline wchar_t *QString2Wchar(QString buf)
{
    return (wchar_t*)reinterpret_cast<const wchar_t *>(buf.utf16());
}


inline QString Wchar2QString(wchar_t *buf)
{
    return QString::fromWCharArray(buf);
}


#endif //STUDENTSYSTEM_TOOLS_HPP
