#ifndef REDIS_HELPER_H
#define REDIS_HELPER_H
#include <hiredis/hiredis.h>
#include <iostream>

class redis_helper
{
public:

  redis_helper(){}

  ~redis_helper()
  {
    this->_connect = NULL;
    this->_reply = NULL;                
  }

  bool connect(std::string host, int port)
  {
    this->_connect = redisConnect(host.c_str(), port);
    if(this->_connect != NULL && this->_connect->err)
    {
      printf("connect error: %s\n", this->_connect->errstr);
      return 0;
    }
    return 1;
  }

  void setAuth()
  {
    this->_reply = (redisReply*)redisCommand(this->_connect, "AUTH %s", "qc2020");//密码访问
    if (this->_reply->type == REDIS_REPLY_ERROR)
      std::cout << "set auth failed!" << std::endl;
  }

  void setDB(int num)
  {
    this->_reply = (redisReply*)redisCommand(this->_connect, "select  %d", num);//密码访问
  }

  int llen(std::string key) //获取列表长度信息
  {
    this->_reply = (redisReply*)redisCommand(this->_connect, "llen %s", key.c_str());
    if (this->_reply == NULL)
      return -1;
    std::cout << "str : " << this->_reply->str << std::endl;
    std::string str = this->_reply->str;
    std::cout << key << " len : " << str << std::endl;
    freeReplyObject(this->_reply);
    return stoi(str);
  }

  std::string get(std::string key)
  {
    this->_reply = (redisReply*)redisCommand(this->_connect, "GET %s", key.c_str());
    if (this->_reply == NULL)
      return NULL;
    std::string str = this->_reply->str;
    freeReplyObject(this->_reply);
    return str;
  }

  void set(std::string key, std::string value)
  {
    redisCommand(this->_connect, "SET %s %s", key.c_str(), value.c_str());
  }

  void lpush(std::string key, std::string value)
  {
    redisCommand(this->_connect, "LPUSH %s %s", key.c_str(), value.c_str());
  }

  std::string lpop(std::string key)
  {
    this->_reply = (redisReply*)redisCommand(this->_connect, "LPOP %s", key.c_str());
    if (this->_reply == NULL)
      return "";
    if (this->_reply->type == REDIS_REPLY_NIL)
      return "";
    std::string str = this->_reply->str;
    freeReplyObject(this->_reply);
    return str;
  }

private:

  redisContext* _connect;
  redisReply* _reply;
                
};

#endif //#REDIS_HELPER_H
