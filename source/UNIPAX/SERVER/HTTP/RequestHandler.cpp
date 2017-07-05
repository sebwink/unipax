#include <UNIPAX/SERVER/HTTP/RequestHandler.h>

#include <stdlib.h>

//#include <QtXml>


UniPAX::SERVER::RequestHandler::RequestHandler(QHttpRequest *request, QHttpResponse *response): m_request(request), m_response(response)
{
    m_request->storeBody();
    connect(m_request, SIGNAL(end()), this, SLOT(onEnd()));
    connect(m_response, SIGNAL(done()), this, SLOT(deleteLater()));
}

UniPAX::SERVER::RequestHandler::~RequestHandler()
{
    delete m_request;
}

void UniPAX::SERVER::RequestHandler::onEnd()
{
    Q_EMIT requestComplete(m_request, m_response);
}

