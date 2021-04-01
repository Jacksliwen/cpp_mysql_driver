/*test*/

#include <iostream>
#include "CMySqlOcciConn.h"


#include <time.h>


using namespace std;

static const int ERROR = -1;
static const int SUCCESS = OCCICOMM_SUCCESS;

int main(int argc, char* argv[])
{
    CMySqlOcciConn *OcciConn = NULL;
    CMySqlStatement* l_state = NULL;
    CMySqlResultSet* l_Rst = NULL;
    OcciConn = new CMySqlOcciConn();

    int iRet = 0;
    
    if (OcciConn->createConnection("root","mysql_root","tcp://192.168.59.245:3306/pubdba") != OCCICOMM_SUCCESS)
    {
        cout << "OcciConn.createConnection error! exit!" << endl;
        return ERROR;
    }
    

    cout << "File:" << __FILE__ << "Line:" << __LINE__ << " iRet: " <<  iRet << endl;
    try
    {
            string l_sSql = "select a.carrier_cd,a.country_code,a.idd_cd from pubdba.carriers a where a.idd_cd =?";
            l_state = OcciConn->createStatement(l_sSql);
            l_state->setNumber(1,91);   
            l_Rst = l_state->executeQuery();
            while(l_Rst->next())
            {   
                    int l_iIndex = 1;   
                    string l_sCarrier = l_Rst->getString(l_iIndex++);   
                    string l_sCountry = l_Rst->getString(l_iIndex++);
                    long l_lIdd = l_Rst->getNumber(l_iIndex++);
                    cout<<"l_sCarrier is "<<l_sCarrier<<endl;
                    cout<<"l_sCountry is "<<l_sCountry<<endl;
                    cout<<"l_lIdd is "<<l_lIdd<<endl;
                    
            }
            l_state->closeResultSet(l_Rst);
            cout<<"delete l_Rst is ok "<<endl;
            l_Rst = NULL;
            OcciConn->terminateStatement(l_state);
            cout<<"delete l_state is ok "<<endl;
            l_state = NULL;
    }
    catch(SQLException &ex)
    {
            cout<<"SQLException error code is "<<ex.getErrorCode();
            //cout<<"SQLException error msg is "<<ex.getMessage();  
    }
    catch(CMySqlOcciConnException &oraex)
    {
            cout<<"COcciConnException error code is "<<oraex.getErrorCode();    
    }

    OcciConn->terminateConnection();
    cout << "File:" << __FILE__ << "Line:" << __LINE__ << " iRet: " <<  iRet << endl;
    return iRet;
}

