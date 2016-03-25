/*
 * BiologicalNetwork.h
 *
 *  Created on: Nov 18, 2014
 *      Author: niermann
 *
 *      This is the base class for all Biological networks.
 */

#ifndef BIOLOGICALNETWORK_H_
#define BIOLOGICALNETWORK_H_

#include <UNIPAX/COMMON/common.h>

namespace UniPAX
{

namespace GRAPH
{

class UNIPAX_EXPORT BiologicalNetwork
{
protected:
	virtual ~BiologicalNetwork() {};
};

typedef UnipaxPtr<BiologicalNetwork>::type BiologicalNetworkPtr;

} //GRAPH
} //UniPAX

#endif

