/** 
 *  @file    CSVData.h 
 *  @author  Alex Rickert
 *  @date    04/02/2020
 *  @version 1.0
 */

#include <SPI.h>
#include <SD.h>

/**
 *  @enum CSV_ERRORS
 *  @var  CSV_NO_ERROR
 *  @var  CSV_CANNOT_OPEN_FILE
 */
enum CSV_ERRORS
{
  CSV_NO_ERROR = 0,
  CSV_CANNOT_OPEN_FILE = 1
};

/**
 *  @class CSVData
 *  @brief Formats data to Comma Separated Value (CSV) and manages writes to file.
 */
class CSVData
{
  public:
  
  /**
   *  @fn    CSVData
   *  @brief Default constructor 
   */
  CSVData();

  /**
   *  @fn    CSVData
   *  @brief Constructor which sets file and bytes before save 
   *  @param pointer to destination file
   *  @param bytesBeforeSave bytes to write before flushing 
   */
  CSVData(File*, int=512);

  /**
   *  @fn    setFile
   *  @brief Setter for file
   *  @param pointer to @ref File
   */
  void setFile(File*);

  /**
   *  @fn      setSave
   *  @brief   Setter for bytesBeforeSave
   *  @param   Number of bytes to write before flushing
   *  @details Bytes written to file are not saved until @ref File::close or
   *           File::flush is called.
   */
  void setSave(unsigned int);

  /**
   *  @fn    setValue
   *  @brief Setter for data in CSV file. Will handle formatting and saving. 
   *  @param character array holding data to write
   *  @param length of character array 
   *  @param (true) Add newline '\n' separator
   *         (false) Add comma ',' separator
   */
  void setValue(char*, unsigned int, bool);

  /**
   *  @fn      save
   *  @brief   Saves data to file, flushes buffer
   *  @details This is handled automatically by setValue.
   */
  void save();
  
  private:
  unsigned int _bytesBeforeSave = 512;
  unsigned int _byteCounter = 0;
  File* _ptrFile = NULL;

  void checkBuffer(unsigned int);
};

#endif
