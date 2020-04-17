#include "PathHandler.h"

PathHandler::PathHandler()
{}

int PathHandler::init(byte chipSelect)
{
  // 0123456789
  // BBBBBBBB/bbbbbbbb/ffffffff.csv    
  _baseDir = &(_filePath[0]);
  _branchDir = &(_filePath[9]);  // 9
  _fileName = &(_filePath[18]);  // 18
  _ext = &(_filePath[26]);

  char temp[] = ".csv";
  strcpy(_extension, temp);

  // Begin SD
  if(! SD.begin(chipSelect) )
  { return PH_CANNOT_LOCATE_SD; }

  return PH_NO_ERROR;
}

int PathHandler::init(byte chipSelect, char* baseDir, char* branchDir, char* fileName)
{
  _error = init(chipSelect);
  if( _error )
  { return _error; }

  setFilePath(baseDir, branchDir, fileName);  
  formatFilePath();
  setDirectory();

  _fullDir[17] = '\0';
  Serial.println(_fullDir);
  
  _filePath[30] = '\0';
  Serial.println(_filePath);
  
  return PH_NO_ERROR;
}

void PathHandler::makePath(char* baseDir, char* branchDir, char* fileName)
{
  setFilePath(baseDir, branchDir, fileName);
  formatFilePath();
  setDirectory();
  //formatDirectory();
  SD.mkdir(_fullDir);
}

void PathHandler::setFilePath(char* baseDir, char* branchDir, char* fileName)
{
  memcpy( _baseDir, baseDir, _maxNameLen);
  memcpy( _branchDir, branchDir, _maxNameLen);
  memcpy( _fileName, fileName, _maxNameLen);
}

void PathHandler::formatFilePath()
{
  int error;
  _filePath[8] = '/';
  _filePath[17] = '/';
  
  _fullDir[17] = '\0';  
  _filePath[30] = '\0';

  memcpy( _ext, &(_extension[0]), 4);
}

//void PathHandler::formatDirectory()
//{ _fullDir[17] = '\0'; }

void PathHandler::setDirectory()
{ memcpy( &(_fullDir[0]), &(_filePath[0]), sizeof(_fullDir)-1 ); }

void PathHandler::printPaths()
{
  Serial.print("Directory: ");
  Serial.println(_fullDir);
  Serial.print("File Path: ");
  Serial.println(_filePath);
}

File* PathHandler::getFile()
{ return &_file; }

int PathHandler::openFile()
{ 
  _file = SD.open(_filePath, FILE_WRITE);

  if(! _file )
  { return PH_CANNOT_OPEN_FILE; }

  return PH_NO_ERROR;
}

void PathHandler::closeFile()
{ _file.close(); }
