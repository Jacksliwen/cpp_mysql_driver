#ifndef CMYSQLSTATEMENT_H
#define CMYSQLSTATEMENT_H


#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
using namespace sql;

#include <list>
#include <string>
#include "CMySqlOcciConnException.h"
#include "CMySqlResultSet.h"
using namespace std;

class CMySqlStatement
{
public:
    CMySqlStatement();
    
    virtual ~CMySqlStatement();

     CMySqlResultSet *executeQuery();

     int executeUpdate();
        
     void closeResultSet(CMySqlResultSet *pm_pRes);

     void setDouble(unsigned int parameterIndex, double value);

     void setInt(unsigned int parameterIndex, int value);

     void setUInt(unsigned int parameterIndex, unsigned int value);

     void setNull(unsigned int parameterIndex, int sqlType);

     void setString(unsigned int parameterIndex, const string& value);

     void setNumber(unsigned int parameterIndex, long value);
    
    int getUpdateCount();
     

     void setStatement(PreparedStatement *pm_pStatement);
     PreparedStatement *getStatement();
     bool execute();


protected:

private:

    PreparedStatement *m_Statement;


    CMySqlStatement& operator = (const CMySqlStatement& c){ return (*this); }
    CMySqlStatement(const CMySqlStatement& c){}
};

#endif  /* COCCI_CONN_H */

