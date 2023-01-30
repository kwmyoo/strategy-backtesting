#ifndef DATA_PROCESSOR_PROCESSOR_HPP_
#define DATA_PROCESSOR_PROCESSOR_HPP_

enum FileType {
  CSV
};

class Processor {
 public:
  FileType fileType;
  
  virtual ~Processor() {}

  virtual void process() = 0;
};

#endif // DATA_PROCESSOR_PROCESSOR_HPP_