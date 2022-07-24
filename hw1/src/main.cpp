#include "report.h"
#include <cassert>

using namespace reportNs;

int main(int argc, char** argv)
{
    try {

        if (argc != 2)
        {
            throw std::invalid_argument("Invalid number of input parametrs.");
        }

        std::unique_ptr<createReport> obj = std::make_unique<createTXTFilesReport>();
        obj->create(argv[1]);

        obj = std::make_unique<createXMLFilesReport>();
        obj->create(argv[1]);

   } catch (const exception& e) {
        cout<< e.what()<<endl;
   }

}
