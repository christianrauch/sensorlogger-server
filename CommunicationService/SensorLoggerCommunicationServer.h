#include <thrift/server/TSimpleServer.h>
#include <SensorDatabase.h>
#include <TempReader.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class SensorLoggerCommunicationServer {
    private:
        TSimpleServer *server;
	public:
        SensorLoggerCommunicationServer(unsigned int port, SensorDatabase &db, TempReader &reader);
        ~SensorLoggerCommunicationServer();
		
		void start();
};
