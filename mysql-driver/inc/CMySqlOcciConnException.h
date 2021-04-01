
#ifndef CMYSQLOCCI_CONN_EXCEPTION_H
#define CMYSQLOCCI_CONN_EXCEPTION_H

/****************************************************************************************
  *
  *  1、本类表示COcciConn类本身可能产生的异常。COcciConn类通过本类
  *         的带参构造函数来抛出一个特定的COcciConnException异常。
  * 
  ****************************************************************************************/


#include <string>

using std::string;

class CMySqlOcciConnException
{
public:
    CMySqlOcciConnException();
 
    CMySqlOcciConnException(int pm_iErrorCode, const string& pm_sMessage);

    CMySqlOcciConnException(const CMySqlOcciConnException& pm_OcciConnException);
    
    CMySqlOcciConnException& operator = (const CMySqlOcciConnException& pm_OcciConnException);
        
    ~CMySqlOcciConnException();

    /**
     * 获取异常代码。
     * @return  相关异常代码。
     */         
    int getErrorCode() const;

    /**
     * 获取异常字符串信息。
     * @return  相关异常信息字符串。
     */         
    const string& getMessage() const;   

private:
    int m_iCode;
    string m_sMessage;
};

#endif  /* COCCI_CONN_EXCEPTION_H */

