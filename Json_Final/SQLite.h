#pragma once
#ifndef      __Sqlite_H__
#define      __Sqlite_H__

#include<sqlite3.h>
#include<iomanip>
#include<string>
#include"Docs.h"


static int Callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    static int j = 0;

    if (j == 0)
    {
        for (int i = 0; i < argc; i++)
        {
            cout << setw(20) << azColName[i];
        }
        j++;
    }

    cout << endl;

    for (int i = 0; i < argc; i++)
    {
        cout << setw(20) << argv[i];
    }

    printf("\n");
    return 0;
}

class Database
{
private:
    sqlite3* db;
    char* zErrMsg;
    int rc;
    string sql;
    string announClosed;
    const char* data = "Callback function called";
public:
    Database(const string& ipFile)//tao file database
    {
        //cout << "Phu";
        rc = sqlite3_open(ipFile.c_str(), &db);

        if (rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        }
        else
        {
            cout << ipFile << ": ";
            fprintf(stdout, "Opened database successfully\n");
        }
    }
    ~Database()//no para for destructor
    {
        if (zErrMsg != nullptr)
        {
            cout << "err" << endl;
            delete zErrMsg;
            zErrMsg = nullptr;
        }
        sqlite3_close(db);
        cout << endl;
        cout << announClosed << " is closed" << endl;
    }

    void SetAnnounClosed(const string& ipFile)
    {
        announClosed = ipFile;
    }

    //method
    void CreateTable()
    {
        cout << endl;
        sql = "CREATE TABLE Docs("  \
            "id                 VARCHAR(30)       NOT NULL    PRIMARY KEY," \
            "journal            VARCHAR(30)       NOT NULL," \
            "eissn              VARCHAR(15)       NOT NULL," \
            "publication_date   VARCHAR(15)       NOT NULL," \
            "article_type       VARCHAR(15)       NOT NULL," \
            "author_display     VARCHAR(15)       NOT NULL," \
            "abstract           VARCHAR(15)       NOT NULL," \
            "title_display      VARCHAR(15)       NOT NULL," \
            "score              DECIMAL(5,2)      NOT NULL);";

        rc = sqlite3_exec(db, sql.c_str(), Callback, 0, &zErrMsg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        else
        {
            fprintf(stdout, "Docs Table created successfully\n");
        }
    }
    void InsertDocs(const Docs& ipObject)
    {
        
        cout << endl;
        sql = "INSERT INTO Docs (id, journal, eissn, publication_date, article_type, author_display, abstract, title_display, score) "  \
            "VALUES('" + ipObject.id + "', '" + ipObject.journal + "', '" + ipObject.eissn + "','" + ipObject.publication_date + "', '" \
            + ipObject.article_type+ "','" +ipObject.author_display+ "','" + ipObject.abstract + "','" +ipObject.title_display+"','" + to_string(ipObject.score) + "'); ";
        rc = sqlite3_exec(db, sql.c_str(), Callback, 0, &zErrMsg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        else {
            fprintf(stdout, "Records for Docs table inserted successfully\n");
        }
    }

    void ShowTable()
    {
        sql = "SELECT * FROM Docs";
       
        cout << sql << endl;
        rc = sqlite3_exec(db, sql.c_str(), Callback, (void*)data, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        else
        {
            fprintf(stdout, "Operation done successfully\n");
        }
    }


};

#endif 
