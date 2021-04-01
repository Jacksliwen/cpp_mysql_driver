
#ifndef CMYSQLOCCI_OPER_H
#define CMYSQLOCCI_OPER_H

/****************************************************************************************
  *
  *  1、本类作为应用相关数据库操作的基类，基于此基类的实例表
  *         示应用相关的一个数据库操作集。
  *  2、本类中，相关的COcciConn成员定义成protected以方便实际使用，
  *         继承COcciOper的类可以直接使用此成员。
  * 
  ****************************************************************************************/

#include "MySqlOccicommDefs.h"
#include "CMySqlOcciConn.h"

class CMySqlOcciOper
{
public:
    CMySqlOcciOper();
    virtual ~CMySqlOcciOper();

    /**
    * 关联到指定连接。
    * @param pm_pOcciConn: 指定的COcciConn连接。    
    * @return 0:  关联到指定连接成功。
    * @return -100001:  参数pm_pOcciConn为空。
    * @return -100201:  之前已经依附到了一个连接还未脱离。
    */  
    int AttachConnection(CMySqlOcciConn *pm_pOcciConn);

    /**
    * 从关联的连接上脱离。
    */      
    void DetachConnection();

    /**
    * 事务回滚。
    * @return 0:  事务回滚成功。    
    * @return -100202:  未关联到任何连接。
    * @return others:  表示OCCI SQLException 或COcciConnException异常代码。
    */          
    int Rollback();

    /**
    * 事务提交。    
    * @return 0:  事务提交成功。
    * @return -100202:  未关联到任何连接。
    * @return others:  表示OCCI SQLException 或COcciConnException异常代码。
    */      
    int Commit();

protected:
    CMySqlOcciConn   *m_pOcciConn;
    
private:
};

#endif  /* COCCI_OPER_H */

