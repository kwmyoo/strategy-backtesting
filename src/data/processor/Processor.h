#ifndef DATA_PROCESSOR_PROCESSOR_HPP_
#define DATA_PROCESSOR_PROCESSOR_HPP_

#include <memory>
#include <string>

#include "Portfolio.h"
#include "Utilities.h"

class Processor {
 public:
  virtual ~Processor() {}

  virtual PortfolioAsset process(const std::string& fileName) = 0;

  static std::unique_ptr<Processor> createProcessor(FileType fileType);

 protected:
  FileType fileType_;

  TimeOrientation dateOrientation_;
};

#endif // DATA_PROCESSOR_PROCESSOR_HPP_