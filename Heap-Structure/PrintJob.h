#pragma once

class PrintJob {
private:
  int priority;
  int jobNumber;
  int numPages;

public:
  // constructor for PrintJob
  PrintJob(int priority, int jobNum, int numPages);
  // Getters
  int getPriority() const;
  int getJobNumber() const;
  int getPages() const;
};
