/** 
 *  @file    PathHandler.h 
 *  @author  Alex Rickert
 *  @date    04/02/2020
 *  @version 1.0
 */

#ifndef PATHHANDLER
#define PATHHANDLER

#include <SPI.h>
#include <SD.h>

enum PH_ERROR
{
  PH_NO_ERROR = 0,
  PH_CANNOT_LOCATE_SD = 1000,
  PH_CANNOT_OPEN_FILE = 1001   
};

/**  
 *  @class PathHandler
 *  @brief Handles opening and closing of SD module and file structure creation
 */
class PathHandler
{
  public:
  PathHandler();
  int init(byte);
  int init(byte, char*, char*, char*);
  void makePath(char*, char*, char*);
  void setFilePath(char*, char*, char*);
  void printPaths();
  void formatFilePath();
  void setDirectory();
  File* getFile();
  int openFile();    
  void closeFile();

  private:
  char _fullDir[18];
  char _filePath[31]; 
  const size_t _maxNameLen = 8;
  const char _extension[5];
  int _error;
  char* _baseDir;
  char* _branchDir;
  char* _fileName;
  char* _ext;
  File _file;
};

#endif
