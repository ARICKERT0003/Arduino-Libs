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

/**
 *  @enum PH_ERROR
 *  @var  PH_NO_ERROR
 *  @var  PH_CANNOT_LOCATE_SD
 *  @var  PH_CANNOT_OPEN_FILE
 */
enum PH_ERROR
{
  PH_NO_ERROR = 0,
  PH_CANNOT_LOCATE_SD = 1000,
  PH_CANNOT_OPEN_FILE = 1001   
};

/**  
 *  @class   PathHandler
 *  @brief   Handles opening and closing of SD module and file structure creation
 *  @details This class wants to be similar to std::filesystem::path but needs
 *           a lot of work. The general idea is to be able to dynamically
 *           create and alter paths in a clean and efficient way. Users need
 *           not worry about syntax and should be able to swap out any segment
 *           without altering the rest of the path.  
 */
class PathHandler
{
  public:

  /**
   *  @fn     PathHandler
   *  @brief  Empty constructor
   */
  PathHandler();

  /**
   *  @fn     init
   *  @brief  Initializes pointers and opens SD 
   *  @param  pin Pin which SD writer is using
   *  @return error @ref PH_ERROR
   */
  int init(byte);

  /**
   *  @fn      init
   *  @brief   Same as above but also populates path with values
   *  @details Each segment of path should be 8 characters long. This will
   *           eventually be changed.
   *  @param   pin
   *  @param   baseDir
   *  @param   branchDir
   *  @param   fileName
   *  @return  error @ref PH_ERROR
   */
  int init(byte, char*, char*, char*);

  /**
   *  @fn      makePath
   *  @brief   Makes base directory, branch directory, and file name
   *  @details Each segment of path should be 8 characters long. This will
   *           eventually be changed.  
   *  @param   baseDir Base Directory
   *  @param   branchDir Branch directory
   *  @param   fileName Name of file
   */
  void makePath(char*, char*, char*);

  /**
   *  @fn      setFilePath
   *  @brief   Should be protected / private
   */
  void setFilePath(char*, char*, char*);

  /**
   *  @deprecated
   *  @fn      printPaths
   *  @brief   Should be deleted
   */
  void printPaths();

  /**
   *  @fn      formatFilePath
   *  @brief   Should be protected / private
   */
  void formatFilePath();

  /**
   *  @fn      setDirectory
   *  @brief   Should be protected / private
   */
  void setDirectory();

  /**
   *  @fn      getFile
   *  @brief   Returns pointer to file at end of path
   *  @return  ptrFile @ref File
   */
  File* getFile();

  /**
   *  @fn      openFile 
   *  @brief   Opens file on SD in write mode
   *  @return  error @ref PH_ERROR
   */
  int openFile();    

  /**
   *  @fn      closeFile
   *  @brief   Closes file on SD
   */
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
