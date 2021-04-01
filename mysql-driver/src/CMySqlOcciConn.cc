#include "CMySqlOcciConn.h"
#include "MySqlOccicommDefs.h"
#include <iostream>
using std::cout;

CMySqlOcciConn::CMySqlOcciConn()
{
    m_Env = NULL;
    m_Conn = NULL;
    m_iErrCode = -11;
    m_sErrMessage = "";
    m_sUser = "";
    m_sDbSid = "";
    m_sPass = "";
    m_lstStatement.clear();
}

CMySqlOcciConn::~CMySqlOcciConn()
{
    terminateConnection();
}

int CMySqlOcciConn::getErrCode()
{
    return m_iErrCode;
}

string CMySqlOcciConn::getErrMessage()
{
    return m_sErrMessage;
}

int CMySqlOcciConn::createConnection(const string & pm_sDBUser,
                            const string & pm_sDBPasswd,
                            const string & pm_sDBSid)
{
    if(m_Env != NULL || m_Conn != NULL)
    {
        m_iErrCode = OCCICOMM_ALREADY_CREATED_CONN;
        m_sErrMessage = "Database connection is not init.";
        return -1;
    }
    m_sUser = pm_sDBUser;
    m_sDbSid = pm_sDBSid;
    m_sPass = pm_sDBPasswd;
    try
    {
        m_Env = get_driver_instance();;
    }
    catch(SQLException &ex)
    {
        m_iErrCode = ex.getErrorCode();
        m_sErrMessage = ex.what();
        return -1;
    }
    catch(...)
    {
        m_iErrCode = OCCICOMM_UNKNOWN_ERR;
        m_sErrMessage = "get_driver_instance Occur Unknown Exception!"; 
        return -1;
    }
    //建立数据库链接
    m_sUser = pm_sDBUser;
    m_sDbSid = pm_sDBSid;
    m_sPass = pm_sDBPasswd;
    try
    {
        m_Conn = m_Env->connect(pm_sDBSid,pm_sDBUser, pm_sDBPasswd);
    }
    catch(SQLException &ex)
    {
        m_Env = NULL;
        m_iErrCode = ex.getErrorCode();
        m_sErrMessage = ex.what();
        return -1;
    }
    catch(...)
    {
        m_Env = NULL;
        m_iErrCode = OCCICOMM_UNKNOWN_ERR;
        m_sErrMessage = "Connect To Database Occur Unknown Exception!";
        return -1;
    }    
    
    return OCCICOMM_SUCCESS;
}

/*
Connection* COcciConn::getConnection() const
{
    return m_Conn;
}

Environment* COcciConn::getEnvironment() const
{
    return m_Env;
}
*/

int CMySqlOcciConn::terminateConnection()
{
    list<CMySqlStatement*>::iterator itor = m_lstStatement.begin();

    if(m_Conn == NULL || m_Env == NULL)
    {
        m_iErrCode = OCCICOMM_CONN_NOT_INITED;
        m_sErrMessage = "Database connection is not valid.";
        return -1;
    }

    try
    {
        for(; itor!=m_lstStatement.end(); itor++)
        {
            delete (*itor);
            *itor = NULL;
        }
        m_lstStatement.clear();
        delete m_Conn; 
        m_Conn = NULL;
        
    }
    catch(SQLException &ex)
    {
        m_iErrCode = ex.getErrorCode();
        m_sErrMessage = ex.what();
        return -1;
    }    
    catch(...)
    {
        m_iErrCode = OCCICOMM_UNKNOWN_ERR;
        m_sErrMessage = "Delete Statement Occur Unknown Exception!";
        return -1;
    }

    return OCCICOMM_SUCCESS;
}

CMySqlStatement* CMySqlOcciConn::createStatement(const string &pm_sSQL)
{   
    CMySqlStatement *pStatement = NULL;
    if(m_Conn != NULL)
    {
        try
        {
            if(m_Conn->isClosed())
            {
                    DBMSG(cout<<"mysql connection is closed "<<endl);
                    delete m_Conn;
                    m_Conn = NULL;
                    m_Conn = m_Env->connect(m_sDbSid,m_sUser, m_sPass); 
            }
            pStatement = new CMySqlStatement();
            DBMSG(cout<<"pm_sSQL is "<<pm_sSQL<<endl);

            PreparedStatement *l_pPreState = NULL;
            l_pPreState = m_Conn->prepareStatement(pm_sSQL);
            if(l_pPreState != NULL)
            {
                    pStatement->setStatement(l_pPreState);
                    m_lstStatement.push_back(pStatement);
                    return pStatement;
            }
            else
            {
                m_iErrCode = -1;
                m_sErrMessage = "Create Statement Occur Falid!";
            }
        }
        catch(SQLException &ex)
        {
             m_iErrCode = ex.getErrorCode();
             m_sErrMessage = ex.what();
        } 
        catch(...)
        {
            m_iErrCode = -1;
            m_sErrMessage = "Create Statement Occur Unknown Exception!";
        }
    }
    else
    {
        m_iErrCode = OCCICOMM_CONN_NOT_INITED;
        m_sErrMessage = "Database connection is not valid.";
    }      
    cout<<"mysql msg :" << m_sErrMessage <<endl;
    throw CMySqlOcciConnException(m_iErrCode, m_sErrMessage);
    return NULL;
}


void CMySqlOcciConn::terminateStatement(CMySqlStatement *pm_Statement)
{
    if(m_Conn != NULL)
    {
        if(pm_Statement != NULL)
        {
            //不管是否异常，不再保持此元素。
            m_lstStatement.remove(pm_Statement);  
            try
            {
                delete pm_Statement;
                pm_Statement = NULL;
            }
            catch(...)
            {
                m_iErrCode = -1;
                m_sErrMessage = "Terminate Statement Occur Unknown Exception!";
                throw CMySqlOcciConnException(m_iErrCode, m_sErrMessage);
                return;
            }      
        }
    }
    else
    {
        m_iErrCode = -1;
        m_sErrMessage = "Database connection is not valid.";
        throw CMySqlOcciConnException(m_iErrCode, m_sErrMessage);
        return;
    }
}

int CMySqlOcciConn::releaseAllStatement()
{
    list<CMySqlStatement*>::iterator itor = m_lstStatement.begin();

    if(m_Conn == NULL || m_Env == NULL)
    {
        m_iErrCode = OCCICOMM_CONN_NOT_INITED;
        m_sErrMessage = "Database connection is not valid.";
        return -1;
    }
    
    try
    {
        for(; itor!=m_lstStatement.end(); itor++)
        {
            delete (*itor);
            *itor = NULL;
        }
        m_lstStatement.clear();
    }
    catch(SQLException &ex)
    {
        m_iErrCode = ex.getErrorCode();
        m_sErrMessage = ex.what();
        return -1;
    }    
    catch(...)
    {
        m_iErrCode = OCCICOMM_UNKNOWN_ERR;
        m_sErrMessage = "Release All Statement Occur Unknown Exception!";
        return -1;
    } 
    return OCCICOMM_SUCCESS;
}

void CMySqlOcciConn::commit()
{
    if(m_Conn != NULL)
    {
        try
        {
            m_Conn->commit();
            return;
        }
        catch(SQLException &ex)
        {
            m_iErrCode = ex.getErrorCode();
            m_sErrMessage = ex.what();
        }  
        catch(...)
        {
            m_iErrCode = OCCICOMM_UNKNOWN_ERR;
            m_sErrMessage = "Commit Occur Unknown Exception!";  
        }
    }
    else
    {
        m_iErrCode = OCCICOMM_CONN_NOT_INITED;
        m_sErrMessage = "Database connection is not valid.";
    }
    throw CMySqlOcciConnException(m_iErrCode, m_sErrMessage);
}

void CMySqlOcciConn::rollback()
{
    if(m_Conn != NULL)
    {
        try
        {
            m_Conn->rollback();
            return;
        }
        catch(SQLException &ex)
        {
            m_iErrCode = ex.getErrorCode();
            m_sErrMessage = ex.what();
        }  
        catch(...)
        {
            m_iErrCode = -1;
            m_sErrMessage = "Rollback Occur Unknown Exception!";   
        }
    }
    else
    {
        m_iErrCode = -1;
        m_sErrMessage = "Database connection is not valid.";
    }
    throw CMySqlOcciConnException(m_iErrCode, m_sErrMessage);
}

void CMySqlOcciConn::PrintStatementsList() const
{
    int i = 0;
    list<CMySqlStatement*>::const_iterator itor = m_lstStatement.begin();
    try
    {
        for(; itor!=m_lstStatement.end(); itor++)
        {
            i++;
        }
    }
    catch(SQLException &ex)
    {
        cout << "PrintStatementsList call catch SQLException. ErrorCode:" << ex.getErrorCode() << endl; 
    }
    catch(...)
    {
        cout << "PrintStatementsList call catch Unknown Exception." << endl; 
    }   
}

Connection  *CMySqlOcciConn::getDbConn()
{
    if(m_Conn != NULL)
    {
        return m_Conn;  
    }   
    else
        return NULL;
}

void CMySqlOcciConn::setAutoCommit(bool autoCommit)
{
    if(m_Conn != NULL)
    {
        try
        {
            m_Conn->setAutoCommit(autoCommit);
            return;
        }
        catch(SQLException &ex)
        {
            m_iErrCode = ex.getErrorCode();
            m_sErrMessage = ex.what();
        }  
        catch(...)
        {
            m_iErrCode = -1;
            m_sErrMessage = "SetAutoCommit Occur Unknown Exception!";  
        }   
    }
    else
    {
        m_iErrCode = -1;
        m_sErrMessage = "Database connection is not valid.";
    }
    throw CMySqlOcciConnException(m_iErrCode, m_sErrMessage);
}
