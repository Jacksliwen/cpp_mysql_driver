#ifndef CMYSQLRESULTSET_H
#define CMYSQLRESULTSET_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <stdlib.h>
using namespace sql;

#include <list>
#include <string>
#include "CMySqlOcciConnException.h"
using namespace std;

class CMySqlResultSet
{
public:
    CMySqlResultSet();
    
    virtual ~CMySqlResultSet();

    
    bool next();


    void setResult(ResultSet *pm_pResult);
    
    ResultSet *getResultSet();
    
    bool isNull(unsigned int colIndex);
    
    int getInt(unsigned int colIndex);
    
    unsigned int getUInt(unsigned int colIndex);
    
    double getDouble(unsigned int colIndex);
    
    long getNumber(unsigned int colIndex);
    
    string getString(unsigned int colIndex);
    
    float getFloat(unsigned int colIndex);  

protected:

private:

    ResultSet  *m_Cres;

    CMySqlResultSet& operator = (const CMySqlResultSet& c){ return (*this); }
    CMySqlResultSet(const CMySqlResultSet& c){}
};

#endif  /* COCCI_CONN_H */

