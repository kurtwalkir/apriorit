#include "report.h"
using namespace reportNs;

vector<FILE_INFO_TYPE>& report::parseData(const string &path, EXTENSION type) {

    static vector <FILE_INFO_TYPE> result {};
    result.clear();

    for (auto& p : std::filesystem::directory_iterator(path)) {
        if (p.is_regular_file()) {
            if (p.path().extension().string() == PARSE_TYPE[type]) {
                result.push_back(std::make_tuple(p.path().parent_path().string(),
                p.path().filename().string(),
                p.path().extension().string()));
            }
        }
    }
    return result;
}

vector<FILE_INFO_TYPE>& txtFilesReport::prepareData(const string &path) {
    return parseData(path, EXTENSION::TXT);
}

vector<FILE_INFO_TYPE>& xmlFilesReport::prepareData(const string &path) {
    return parseData(path, EXTENSION::XML);
}

vector<FILE_INFO_TYPE>& jsonFilesReport::prepareData(const string &path) {
    return parseData(path, EXTENSION::JSON);
}

vector<FILE_INFO_TYPE>& csvFilesReport::prepareData(const string &path) {
    return parseData(path, EXTENSION::CSV);
}

void createReport::create(const string &path) const {
    report* rp = this->fM();
    vector<FILE_INFO_TYPE> data = rp->prepareData(path);

    for (const auto &it: data) {
        cout << "Parent path: " <<  std::get<0>(it) << "Filename: " << std::get<1>(it) << "Extension: " << std::get<2>(it)  << endl;
    }
    delete rp;
}
