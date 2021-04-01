#include "CMySqlResultSet.h"

CMySqlResultSet::CMySqlResultSet()
{
    m_Cres = NULL;  
}

CMySqlResultSet::~CMySqlResultSet()
{
    if(m_Cres != NULL)  
    {
        delete m_Cres;
        m_Cres = NULL;  
    }
}

bool CMySqlResultSet::next()
{
    return m_Cres->next();
}

void CMySqlResultSet::setResult(ResultSet *pm_pResult)
{
    if(pm_pResult   != NULL)
    {
        m_Cres = pm_pResult;
    }
}
    
ResultSet *CMySqlResultSet::getResultSet()
{
    return  m_Cres;
}

bool CMySqlResultSet::isNull(unsigned int colIndex)
{
    return m_Cres->isNull(colIndex);    
}

int CMySqlResultSet::getInt(unsigned int colIndex)
{
    return m_Cres->getInt(colIndex);    
}

unsigned int CMySqlResultSet::getUInt(unsigned int colIndex)
{
    return  m_Cres->getUInt(colIndex);
}

double CMySqlResultSet::getDouble(unsigned int colIndex)
{
    return  m_Cres->getDouble(colIndex);
}

long CMySqlResultSet::getNumber(unsigned int colIndex)
{
    return  m_Cres->getInt64(colIndex);
}

string CMySqlResultSet::getString(unsigned int colIndex)
{
    return  m_Cres->getString(colIndex);    
}

float CMySqlResultSet::getFloat(unsigned int colIndex)
{
    float l_frst = 0.0;
    string l_srst = m_Cres->getString(colIndex);
    l_frst = atof(l_srst.c_str());
    return l_frst;
}

