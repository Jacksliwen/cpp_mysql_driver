#include "CMySqlStatement.h"

CMySqlStatement::CMySqlStatement()
{
    m_Statement = NULL; 
}

CMySqlStatement::~CMySqlStatement()
{

    if(m_Statement != NULL)
    {
        delete m_Statement;
        m_Statement = NULL;
    }

}


void CMySqlStatement::setStatement(PreparedStatement *pm_pStatement)
{
    m_Statement = pm_pStatement;    
}

PreparedStatement *CMySqlStatement::getStatement()
{
    return m_Statement; 
}

bool CMySqlStatement::execute()
{
    return  m_Statement->execute();
}


CMySqlResultSet *CMySqlStatement::executeQuery()
{
    CMySqlResultSet *l_PCRst = NULL;
    ResultSet *l_prst = NULL;   
    try
    {
        l_prst = m_Statement->executeQuery();
        l_PCRst = new CMySqlResultSet;
        l_PCRst->setResult(l_prst);     
    }
    catch(SQLException &e)
    {
        cerr<<"CStatement::executeQuery error code is "<<e.getErrorCode()<<"errMessage is "<<e.what()<<endl;
        return NULL;
    }
    catch (std::runtime_error &ex)
    {
        cout<<"errMessage: "<<ex.what()<<endl;
        return NULL;
    }
    catch(...)
    {
        cout<<"mysql occi error..."<<endl;
        return NULL;
    }
    return l_PCRst;
}

int CMySqlStatement::executeUpdate()
{
    return m_Statement->executeUpdate();    
}

void CMySqlStatement::closeResultSet(CMySqlResultSet *pm_pRes)
{

    if(pm_pRes != NULL)
    {
        delete  pm_pRes;
        pm_pRes = NULL;
    }

}

void CMySqlStatement::setDouble(unsigned int parameterIndex, double value)
{
    return  m_Statement->setDouble(parameterIndex,value);
}

void CMySqlStatement::setInt(unsigned int parameterIndex, int value)
{
    return  m_Statement->setInt(parameterIndex,value);  
}

void CMySqlStatement::setUInt(unsigned int parameterIndex, unsigned int value)
{
    return  m_Statement->setUInt(parameterIndex,value); 
}

void CMySqlStatement::setNull(unsigned int parameterIndex, int sqlType)
{
    return  m_Statement->setNull(parameterIndex,sqlType);   
}

void CMySqlStatement::setString(unsigned int parameterIndex, const string& value)
{
    return  m_Statement->setString(parameterIndex,value);       
}

void CMySqlStatement::setNumber(unsigned int parameterIndex, long value)
{
    return  m_Statement->setInt64(parameterIndex,value);    
}

int CMySqlStatement::getUpdateCount()
{
    return m_Statement->getUpdateCount();
}

