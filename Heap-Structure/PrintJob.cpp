#include "PrintJob.h"

// Constructor for PrintJob
PrintJob::PrintJob (int setP, int setJ,int numP)
  : priority(setP), jobNumber(setJ), numPages(numP)
{
}

// Getters. Return properties of PrintJob

int PrintJob::getPriority() const {
    return priority;
}

int PrintJob::getJobNumber() const {
    return jobNumber;
}

int PrintJob::getPages() const {
    return numPages;
}
