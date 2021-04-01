

#include "CMySqlOcciOper.h"
#include "MySqlOccicommDefs.h"

CMySqlOcciOper::CMySqlOcciOper()
{
    m_pOcciConn = NULL;
}

CMySqlOcciOper::~CMySqlOcciOper()
{
    DetachConnection();
}

int CMySqlOcciOper::AttachConnection(CMySqlOcciConn *pm_pOcciConn)
{
    if(pm_pOcciConn == NULL)
    {
        return OCCICOMM_PARAM_ERR;
    }

    if(m_pOcciConn != NULL)
    {
        return OCCICOMM_ALREADY_ATTACHED_CONN;
    }

    m_pOcciConn = pm_pOcciConn;

    return OCCICOMM_SUCCESS;
}

void CMySqlOcciOper::DetachConnection()
{ 
    if(m_pOcciConn != NULL)
    {
        m_pOcciConn = NULL;
    }
}

int CMySqlOcciOper::Rollback()
{
    if(m_pOcciConn != NULL)
    {
        try
        {
            m_pOcciConn->rollback();
        }
        catch(SQLException &ex)
        {
            return ex.getErrorCode();
        }
        catch(CMySqlOcciConnException &ex)
        {
            return ex.getErrorCode();  
        }       
    }
    else
    {
        return OCCICOMM_NOT_ATTACHED_CONN;
    }

    return OCCICOMM_SUCCESS;
}

int CMySqlOcciOper::Commit()
{
    if(m_pOcciConn != NULL)
    {
        try
        {
            m_pOcciConn->commit();
        }
        catch(SQLException &ex)
        {
            return ex.getErrorCode();
        }
        catch(CMySqlOcciConnException &ex)
        {
            return ex.getErrorCode();  
        }
    }
    else
    {
        return OCCICOMM_NOT_ATTACHED_CONN;
    }    

    return OCCICOMM_SUCCESS;
}

