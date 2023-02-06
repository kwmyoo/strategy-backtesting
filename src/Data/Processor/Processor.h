#ifndef DATA_PROCESSOR_PROCESSOR_HPP_
#define DATA_PROCESSOR_PROCESSOR_HPP_

#include <memory>
#include <string>

#include "Utilities.h"

class Processor {
 public:
  virtual ~Processor() {}

  virtual HistoricalData Process(const std::string& file_name) = 0;

  static std::unique_ptr<Processor> CreateProcessor(FileType file_type);

 protected:
  FileType file_type_;

  TimeOrientation date_orientation_;
};

#endif // DATA_PROCESSOR_PROCESSOR_HPP_