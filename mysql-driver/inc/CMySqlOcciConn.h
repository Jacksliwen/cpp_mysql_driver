#ifndef CMYSQLOCCI_CONN_H
#define CMYSQLOCCI_CONN_H

/****************************************************************************************
  *
  *  数据库连接类表示一个数据库物理连接，和物理资源相关。
  *  1、拷贝与赋值操作私有化，禁止对象之间的拷贝、赋值操作。
  *  2、若需要传递同一个连接对象时，使用指向对象的指针或引用。
  *
  ****************************************************************************************/


#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
using namespace sql;

#include <list>
#include <string>
#include "CMySqlOcciConnException.h"
#include "CMySqlStatement.h"
#include "CMySqlResultSet.h"
#include "MySqlOccicommDefs.h"
using namespace std;

#ifdef DEBUG
#define DBMSG(x) x
#else
#define DBMSG(x)
#endif

class CMySqlOcciConn
{
public:
    CMySqlOcciConn();
    
    virtual ~CMySqlOcciConn();

    /**
    * 以给定的 Environment::Mode创建连接, 默认为 Environment::DEFAULT。
    * @param pm_sDBUser: 数据库用户名。
    * @param pm_sDBPasswd: 数据库用户密码。
    * @param pm_sDBSid: 数据库SID。
    * @param pm_Mode: OCCI环境模型Environment::Mode, 默认为 Environment::DEFAULT。
    * @return 0:  创建连接成功。
    * @return -100101:  之前已经创建了连接还未关闭。
    * @return -100099:  未知错误。
    * @return others: 表示OCCI SQLException 异常代码。
    */  

int createConnection(const string & pm_sDBUser,
                        const string & pm_sDBPasswd,
                        const string & pm_sDBSid);

    /**
    * 释放数据库连接。
    * @return 0:  释放连接成功。
    * @return -100102:  连接还未建立。
    * @return -100099:  未知错误。
    * @return others: 表示OCCI SQLException 异常代码。
    */          
    int terminateConnection();

    //去掉获取连接环境，强制以本类创建Statement。
    //Connection* getConnection() const;
    //Environment* getEnvironment() const;

    /**
    * 创建OCCI Statement。
    * 使用异常机制，调用者应该捕获SQLException与COcciConnException异常。
    */  
    CMySqlStatement* createStatement(const string &pm_sSQL = "");

    /**
    * 释放指定的OCCI Statement。
    * 使用异常机制，调用者应该捕获SQLException与COcciConnException异常。
    */  
    void terminateStatement(CMySqlStatement *pm_Statement);

    /**
    * 释放实例维护的所有Statement。
    * @return 0:  释放连接成功。
    * @return -100102:  连接还未建立。
    * @return -100099:  未知错误。
    * @return others: 表示OCCI SQLException 异常代码。
    */  
    int releaseAllStatement();

    /**
    * 事务提交。
    * 使用异常机制，调用者应该捕获SQLException与COcciConnException异常。
    */  
    void commit();

    /**
    * 事务回滚。
    * 使用异常机制，调用者应该捕获SQLException与COcciConnException异常。
    */      
    void rollback();

    /**
    * 打印已创建但还未释放的Statement列表。用于调试。
    */
    void PrintStatementsList() const;

    /**
    * 获取错误码。
    */
    int getErrCode();
    
    /**
    * 获取错误信息。
    */
    string getErrMessage();
    
    /**
    * 设置自动提交机制。
    */
    void setAutoCommit(bool autoCommit);
    
    Connection  *getDbConn();

private:
    int m_iErrCode;
    string m_sErrMessage;
    Driver *m_Env;
    Connection  *m_Conn;
    list<CMySqlStatement*> m_lstStatement;
    CMySqlOcciConn& operator = (const CMySqlOcciConn& c){ return (*this); }
    CMySqlOcciConn(const CMySqlOcciConn& c){}
    string m_sUser;
    string m_sDbSid;
    string m_sPass;
};


#endif  /* COCCI_CONN_H */

