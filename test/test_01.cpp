#include <iostream>
#include <stdio.h>
#include <commonfunction_c.h>
#include <redis_helper.h>

#define REDIS_TEST_HOST "10.0.0.14"
#define REDIS_TEST_LIST_NAME "TEST_LIST"
using namespace std;
using namespace commonfunction_c;

int main(int argc, char* argv[])
{
  char* workPath = new char[2048];
  if (commonfunction_c::BaseFunctions::GetWorkPath(workPath) > 0)
    cout << "workPath : " << workPath << endl;

  redis_helper* r = new redis_helper();
  if (!r->connect(REDIS_TEST_HOST, 6379))
  {
    cout << "connect to redis : " << REDIS_TEST_HOST << " failed!" << endl;
  }
  r->setAuth(); 
  r->lpush(REDIS_TEST_LIST_NAME, "123");
  cout << r->lpop(REDIS_TEST_LIST_NAME) << endl; 
}
