/**
 * @file  File.cpp
 * @brief File
 *
 * Class implementation for File
 *
 * @author     Clay Freeman
 * @date       March 17, 2015
 */

#include <libgen.h>
#include <limits.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "File.hpp"

/**
 * @brief Create
 *
 * Creates a file for the given path if it doesn't exist
 *
 * @param path The path for which to create a file
 *
 * @return true if created, false otherwise
 */
bool File::create(const std::string& path) {
  bool retVal = false;
  if (!File::exists(path)) {
    FILE* fp = fopen(path.c_str(), "w");
    if (fp != nullptr) {
      fclose(fp);
      retVal = true;
    }
  }
  return retVal;
}

/**
 * @brief Directory
 *
 * Computes the directory name for a given path
 *
 * @param path The path for which to compute a directory name
 *
 * @return directory of path
 */
std::string File::directory(const std::string& path) {
  char* dup = strdup(path.c_str());
  std::string retVal{dirname(dup)};
  free(dup);
  return retVal;
}

/**
 * @brief Executable
 *
 * Checks if the given path is executable by the current process
 *
 * @param path The path for which to check access
 *
 * @return true if executable, false otherwise
 */
bool File::executable(const std::string& path) {
  return (access(path.c_str(), X_OK) == 0);
}

/**
 * @brief Exists
 *
 * Checks if a given path exists
 *
 * @param path The path for which to check existence
 *
 * @return true if exists, false otherwise
 */
bool File::exists(const std::string& path) {
  struct stat buffer;
  return (stat(path.c_str(), &buffer) == 0);
}

/**
 * @brief Get Content
 *
 * Fetches the content of the file at the given path
 *
 * @param path The path for which to get content
 *
 * @return content of file at path
 */
std::string File::getContent(const std::string& path) {
  std::string retVal;
  if (File::readable(path)) {
    FILE* fp = fopen(path.c_str(), "rb");
    if (fp != nullptr) {
      fseek(fp, 0, SEEK_END);
      retVal.resize(ftell(fp));
      rewind(fp);
      if (fread(&retVal[0], 1, retVal.size(), fp) == 0) {
        throw std::runtime_error{"The requested file is not readable"};
      }
      fclose(fp);
    }
    else {
      throw std::runtime_error{"The requested file is not readable"};
    }
  }
  else {
    throw std::runtime_error{"The requested file is not readable"};
  }
  return retVal;
}

/**
 * @brief Is Directory
 *
 * Checks if the given path is a directory
 *
 * @param path The path for which to check
 *
 * @return true if directory, false otherwise
 */
bool File::isDirectory(const std::string& path) {
  struct stat buffer;
  return (stat(path.c_str(), &buffer) == 0 && buffer.st_mode & S_IFDIR);
}

/**
 * @brief Is File
 *
 * Checks if the given path is a file
 *
 * @param path The path for which to check
 *
 * @return true if file, false otherwise
 */
bool File::isFile(const std::string& path) {
  struct stat buffer;
  return (stat(path.c_str(), &buffer) == 0 && buffer.st_mode & S_IFREG);
}

/**
 * @brief Name
 *
 * Computes the basename for a given path
 *
 * @param path The path for which to compute a basename
 *
 * @return basename of path
 */
std::string File::name(const std::string& path) {
  char* dup = strdup(path.c_str());
  std::string retVal{basename(dup)};
  free(dup);
  return retVal;
}

/**
 * @brief Put Content
 *
 * Puts the given content in the file at the given path
 *
 * @param path    The path for which to put content
 * @param content The content to put
 * @param append  Whether or not to append [default = false]
 *
 * @return true if put, false otherwise
 */
bool File::putContent(const std::string& path, const std::string& content,
    bool append) {
  bool retVal = false;
  if (File::writable(path)) {
    FILE* fp = fopen(path.c_str(), (append == true ? "ab" : "wb"));
    if (fp != nullptr) {
      fwrite(content.c_str(), sizeof(char), strlen(content.c_str()), fp);
      fclose(fp);
      retVal = true;
    }
  }
  return retVal;
}

/**
 * @brief Readable
 *
 * Checks if the given path is readable by the current process
 *
 * @param path The path for which to check access
 *
 * @return true if readable, false otherwise
 */
bool File::readable(const std::string& path) {
  return (access(path.c_str(), R_OK) == 0);
}

/**
 * @brief Real Path
 *
 * Computes the real path of the given path
 *
 * @param path The path for which to compute real path
 *
 * @return real path
 */
std::string File::realPath(const std::string& path) {
  std::string retVal;
  char* rpath = realpath(path.c_str(), nullptr);
  if (rpath != nullptr) {
    retVal = std::string{rpath};
    free(rpath);
  }
  rpath = nullptr;
  return retVal;
}

/**
 * @brief Remove
 *
 * Unlinks the file (or symlink) at the given path
 *
 * @param path The path for which to unlink
 *
 * @return true if unlinked, false otherwise
 */
bool File::remove(const std::string& path) {
  bool retVal = false;
  if (File::exists(path)) {
    retVal = unlink(path.c_str()) == 0;
  }
  return retVal;
}

/**
 * @brief Truncate
 *
 * Puts an empty string in the file at the given path
 *
 * @param path The path for which to truncate
 *
 * @return true if truncated, false otherwise
 */
bool File::truncate(const std::string& path) {
  return File::putContent(path, std::string{});
}

/**
 * @brief Writable
 *
 * Checks if the given path is writable by the current process
 *
 * @param path The path for which to check access
 *
 * @return true if writable, false otherwise
 */
bool File::writable(const std::string& path) {
  return (access(path.c_str(), W_OK) == 0);
}
