#ifndef DATA_PROCESSOR_PROCESSOR_HPP_
#define DATA_PROCESSOR_PROCESSOR_HPP_

#include <memory>
#include <string>

#include "utilities.h"

class Processor {
 public:
  virtual ~Processor() {}

  virtual PeriodQueue Process(const std::string& file_name) = 0;

  std::unique_ptr<Processor> CreateProcessor(FileType file_type);

 protected:
  FileType file_type_;

  DateOrientation date_orientation_;
};

#endif // DATA_PROCESSOR_PROCESSOR_HPP_