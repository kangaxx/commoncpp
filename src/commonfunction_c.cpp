#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#include "inc/commonfunction_c.h"
#define INT_PATH_LENGTH 2048
namespace commonfunction_c {
  int BaseFunctions::GetWorkPath(char* dest)
  {
    if (readlink("/proc/self/exe", dest, INT_PATH_LENGTH) <= 0)
    {
      return -1;
    }
    else
    {
      char* last_slash = strrchr(dest, '/');
      if (last_slash == NULL)
        return -1;
      else
      {
        *last_slash = '\0';
        return last_slash - dest;
      }
    }

  }

}
