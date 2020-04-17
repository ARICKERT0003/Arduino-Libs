/** 
 *  @file    CSVData.cpp 
 *  @author  Alex Rickert
 *  @date    04/02/2020
 *  @version 1.0
 */

#include "CSVData.h"

CSVData::CSVData()
{}

void CSVData::save()
{
  _ptrFile->flush();
  _byteCounter = 0;
}

void CSVData::setValue(char* data, unsigned int len, bool isLineEnd)
{
  checkBuffer(len);

  _ptrFile->write(data, len);
  _byteCounter += len;

  if( !isLineEnd )
  { _ptrFile->write(","); } //, 1); }
  else
  { _ptrFile->write("\n"); } //, 1); }

  _byteCounter++;
}

void CSVData::checkBuffer(unsigned int len)
{
  if( _bytesBeforeSave < (_byteCounter + len) )
  { save(); }
}

void CSVData::setFile(File* ptrFile)
{ _ptrFile = ptrFile; }

void CSVData::setSave(unsigned int bytesBeforeSave)
{ _bytesBeforeSave = bytesBeforeSave; }
