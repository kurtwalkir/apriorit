#pragma once
#include <filesystem>
#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <map>
using namespace std;



/**
* @brief Implementation of abstract factory method for home work 1
* */
namespace reportNs {

    using FILE_INFO_TYPE = tuple<string, string, string>;

    /**
    * @brief Abstract class for preparing data with information about files.
     */
    class report {
    protected:

        /*! This is an enum class with const of file extensions */
        enum class EXTENSION { TXT = 0,
                              XML,
                              JSON,
                              CSV };

        /*! Associative array with file extensions */
        map<EXTENSION, string > PARSE_TYPE { { EXTENSION::TXT, ".txt" },
                                            { EXTENSION::XML, ".xml" },
                                            { EXTENSION::JSON, ".json" },
                                            { EXTENSION::CSV, ".csv" } };

       /**
        * @brief Parse all files by the given path.
        * @param path another path to the folder.
        * @param type extension of files that need to parse.
        * @return vector file information.
        */
        vector<FILE_INFO_TYPE>& parseData(const string &path, EXTENSION type);

    public:
        virtual ~report() = default;
        /**
        * @brief Prepare data for different file extensions. Need to overload.
        * Need to overriding in child class.
        * @param path another path to the folder.
        * @return vector file information.
        */
        virtual vector<FILE_INFO_TYPE>& prepareData(const string &path) = 0;
    };

    class txtFilesReport: public report {
        vector<FILE_INFO_TYPE>& prepareData(const string &path) override final;
    };

    class xmlFilesReport: public report {
        vector<FILE_INFO_TYPE>& prepareData(const string &path) override final;
    };

    class jsonFilesReport: public report {
        vector<FILE_INFO_TYPE>& prepareData(const string &path) override final;
    };

    class csvFilesReport: public report {
        vector<FILE_INFO_TYPE>& prepareData(const string &path) override final;
    };

    /**
    * @brief Factory method class
    */
    class createReport {
    public:
        virtual ~createReport() = default;
        virtual report* fM() const = 0;
        void create(const string &path) const;
    };

    class createTXTFilesReport: public createReport {
    public:
        report* fM() const override {
            return new txtFilesReport();
        }
    };

    class createXMLFilesReport: public createReport {
    public:
        report* fM() const override {
            return new xmlFilesReport();
        }
    };

    class createJSONFilesReport: public createReport {
    public:
        report* fM() const override {
            return new jsonFilesReport();
        }
    };

        class createXMLReport: public createReport {
    public:
        report* fM() const override {
            return new csvFilesReport();
        }
    };
};
