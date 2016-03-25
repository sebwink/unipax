#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>


UniPAX::SERVER::QueryEngine::QueryEngine()
{
}

UniPAX::SERVER::QueryEngine::~QueryEngine()
{

}


void UniPAX::SERVER::QueryEngine::rebuildAllIndexes()
{
	rebuildAttributeIndex();
	rebuildNameIndex();
	rebuildIdMapping();
	rebuildPathwayIndex();
}
