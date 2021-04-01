
 #include "CMySqlOcciConnException.h"

CMySqlOcciConnException::CMySqlOcciConnException()
{
    m_iCode = 0;
    m_sMessage = "";
}

CMySqlOcciConnException::CMySqlOcciConnException(int pm_iErrorCode, const string& pm_sMessage)
{
    m_iCode = pm_iErrorCode;
    m_sMessage = pm_sMessage;
}  

CMySqlOcciConnException::CMySqlOcciConnException(const CMySqlOcciConnException& pm_OcciConnException)
{
    this->m_iCode = pm_OcciConnException.m_iCode;
    this->m_sMessage = pm_OcciConnException.m_sMessage;
}
    
CMySqlOcciConnException&  CMySqlOcciConnException::operator = (const CMySqlOcciConnException& pm_OcciConnException)
{
    if(this != &pm_OcciConnException)
    {
        this->m_iCode = pm_OcciConnException.m_iCode;
        this->m_sMessage = pm_OcciConnException.m_sMessage;
    }

    return (*this);
}

CMySqlOcciConnException::~CMySqlOcciConnException()
{
}

int CMySqlOcciConnException::getErrorCode() const
{
    return m_iCode;
}

const string& CMySqlOcciConnException::getMessage() const
{
    return m_sMessage;
} 

