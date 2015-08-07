#include "SensorLoggerCommunicationServer.h"

#include <SensorLoggerCommunication.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "SensorLoggerCommunication.cpp"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

SensorLoggerCommunicationServer::SensorLoggerCommunicationServer(unsigned int port, SensorDatabase &db, TempReader &reader) {
    shared_ptr<SensorLoggerCommunicationHandler> handler(new SensorLoggerCommunicationHandler(db, reader));
    shared_ptr<TProcessor> processor(new SensorLoggerCommunicationProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    server = new TSimpleServer(processor, serverTransport, transportFactory, protocolFactory);
}

SensorLoggerCommunicationServer::~SensorLoggerCommunicationServer() {
    server->stop();
    delete server;
}

void SensorLoggerCommunicationServer::start() {
    server->serve();
}

void SensorLoggerCommunicationServer::stop() {
    server->stop();
}
