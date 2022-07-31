#include <server.h>
#include <client.h>
using namespace server;
using namespace client;

int main(int argc, char** argv)
{

    if (argc != 2) {
        cout<<"Invalid arguments"<<endl;
        exit(EXIT_FAILURE);
    }

    string action(argv[1]);

    if (action == "server") {
        try {
            TcpServer srv("127.0.0.1", 1234);
            srv.run();
        } catch (const exception& e) {
            cout<< e.what()<<endl;
        }
    } else if (action == "client") {
        try {
            TcpClient cln;
            cln.connectToSrv("127.0.0.1", 1234);
        } catch (const exception& e) {
            cout<< e.what()<<endl;
        }
    } else {
        exit(EXIT_FAILURE);
    }
}
