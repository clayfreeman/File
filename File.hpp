/**
 * @file  File.h
 * @brief File
 *
 * Class definition for File
 *
 * @author     Clay Freeman
 * @date       March 17, 2015
 */

#ifndef _FILE_H
#define _FILE_H

#include <string>

class File {
  private:
    File();
  public:
    static std::string name(const std::string& path);
    static bool create(const std::string& path);
    static bool remove(const std::string& path);
    static std::string directory(const std::string& path);
    static bool executable(const std::string& path);
    static bool exists(const std::string& path);
    static std::string getContent(const std::string& path);
    static bool isDirectory(const std::string& path);
    static bool isFile(const std::string& path);
    static bool putContent(const std::string& path, const std::string& content,
      bool append = false);
    static bool readable(const std::string& path);
    static std::string realPath(const std::string& path);
    static bool truncate(const std::string& path);
    static bool writable(const std::string& path);
};

#endif
