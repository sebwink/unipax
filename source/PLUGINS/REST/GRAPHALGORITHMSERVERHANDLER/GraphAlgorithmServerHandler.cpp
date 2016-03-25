#include <PLUGINS/REST/GRAPHALGORITHMSERVERHANDLER/GraphAlgorithmServerHandler.h>

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>
#include <UNIPAX/IMPORT/GRAPHML/GraphMLWriter.h>
#include <UNIPAX/IMPORT/GENESET/GeneSetWriter.h>
#include <UNIPAX/COMMON/KernelCollector.h>

#include <UNIPAX/SERVER/HTTP/qhttpconnection.h>

#include <UNIPAX/GRAPH/LEMON/GMLGraphWriter.h>
#include <UNIPAX/GRAPH/LEMON/GraphMLGraphWriter.h>
#include <UNIPAX/GRAPH/LEMON/SIFGraphWriter.h>
#include <UNIPAX/GRAPH/LEMON/GMXGraphWriter.h>

#ifdef ODB_MYSQL
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#elif defined ODB_ORACLE
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#endif

#include <UNIPAX/KERNEL/all.h>
#include <UNIPAX/KERNEL/Kernel.h>

#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <lemon/core.h>
#include <lemon/lgf_writer.h>
#include <lemon/edge_set.h>
#include <lemon/adaptors.h>
#include <lemon/list_graph.h>
#include <lemon/network_simplex.h>
#include <lemon/concepts/maps.h>
#include <lemon/concepts/digraph.h>
#include <lemon/dijkstra.h>
#include <lemon/cost_scaling.h> 

#include <limits>
#include <algorithm>
#include <lemon/math.h>

#include <unistd.h>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <QtXml>

#include <QtCore/qplugin.h>
#include <QtNetwork>

using boost::asio::ip::tcp;


void readAttributesFromFile(std::string, std::map<std::string, double>&, std::set<std::string>&);
int readAttributesFromFile_duplicateFree(std::string, std::map<std::string, double>&, std::set<std::string>&);

double degreeOfDeregulation(double);


//Runs the algorithm
QRegExp GraphAlgorithmServerHandler::shortestPath("/algorithms/shortestPath", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp GraphAlgorithmServerHandler::minCostFlow("/algorithms/minCostFlow", Qt::CaseSensitive, QRegExp::RegExp2);


GraphAlgorithmServerHandler::GraphAlgorithmServerHandler() : RESTServerHandler("Graph Algorithm Server Handler"), _rebuild_mapping_index(false)
{
				_pattern.push_back(GraphAlgorithmServerHandler::shortestPath);
				_pattern.push_back(GraphAlgorithmServerHandler::minCostFlow);
}


GraphAlgorithmServerHandler::~GraphAlgorithmServerHandler(){
				engine = 0;
}

void GraphAlgorithmServerHandler::init(boost::program_options::variables_map & _vm)
{
#ifdef ODB_MYSQL
				mapping_engine = UniPAX::GRAPH::mysql::MySQLMappingEnginePtr(new UniPAX::GRAPH::mysql::MySQLMappingEngine(engine->getDBManager()));
#elif defined ODB_ORACLE
				mapping_engine = UniPAX::GRAPH::oracle::OracleMappingEnginePtr(new UniPAX::GRAPH::oracle::OracleMappingEngine(engine->getDBManager()));
#endif
				dbc = UniPAX::DBConnectorPtr(new UniPAX::DBConnector(UniPAX::SERVER::QueryEnginePtr(engine), boost::dynamic_pointer_cast<UniPAX::GRAPH::MappingEngine>(mapping_engine)));
}

QString GraphAlgorithmServerHandler::help(QString format)
{
				if (format == "html")
				{
								return 	QString("<tr><td colspan=2><b>Returns graph algorithms:</b></td></tr>")
												// shortestPath
												.append("<tr><td valign=top><b>/algorithms/shortestPath</b></td><td>")
												.append("Runs shortest path on network.<br/>")
												.append("<br/>")
												.append("<b>Syntax:</b> /algorithms/shortestPath?result=&lt;ID&gt;&mapping=&lt;metabolic | regulatory | ppi&gt;&source=&lt;ID&gt;&target=&lt;ID&gt;&format=&lt;ids | biopax | graphml | gmx&gt;<br/>")
												.append("<br/>")
												.append("<ul>")
												.append("<li>result - ResultObject ID from which to construct the network.</li>")
												.append("<li>mapping - Network mapping (metabolic | <i>regulatory</i> | ppi).</li>")
												.append("<li>source - Source node of the shortest path.</li>")
												.append("<li>target - Target node of the shortest path.</li>")
												.append("<li>format - specifies the output format (<i>biopax</i> | graphml | gmx)</li>") 
												.append("</ul>")
												.append("</td></tr>")
												// minCostFlow
												.append("<tr><td valign=top><b>/algorithms/minCostFlow</b></td><td>")
												.append("Runs Min-Cost-Flow on regulatory network.<br/>")
												.append("<br/>")
												.append("<b>Syntax:</b> /algorithms/minCostFlow&lt;parameters&gt;<br/>")
												.append("<br/>")
												.append("<b>Parameters:</b> default values are printed <i>italic</i> ")
												.append("<ul>")
												.append("<li>file_phospho - path to phospho file (<i>&lt/home/schnel10/phospho.txt&gt</i>)</li>")
												.append("<li>fileLabel_phospho - indicates the label used in the phospho dataset (geneid | uniprot) - no default</li>")
												.append("<li>file_geneExp - path to geneExp file (<i>&lt/home/schnel10/geneexpression.txt&gt</i>)</li>")
												.append("<li>fileLabel_geneExp - indicates the label used in the gene expression dataset (geneid | uniprot)</li>")
												.append("<li>networktype - (full | extended | <i> analyzed_subnetwork</i>)</li>")
												.append("<li>k - determines size of subnetwork, required flow in target node, default: <i>maximal k</i> to yield a feasible solution</li>")
												.append("<li>format - specifies the output format (<i>sif</i> | na | ea | graviton)</li>") 
												.append("<li>nodelabel - assign node labels (<i>unipax</i> | geneid | reactome | uniprot )</li>")
												.append("<li>nodevalue - assign node values (<i> &lt none &gt </i> | geneexpression | phospho | sourceset | targetset | standardname | xref!geneid | xref!uniprot)</li>")
												//.append("<li>edgelabel - assign edge labels (type | relation) TODO which default</li>")
												.append("<li>edgevalue - assign edge values (<i> &lt none &gt</i> | edgeweight)</li>")
												//.append("<li>filter - filter the network by (pathway!&lt;id&gt; | organism!&lt;id&gt; | nodetype!&lt;type&gt; | edgetype!&lt;type&gt;)+  TODO</li>")
												.append("</ul>")
												.append("<b>Basic sample URL</b>: <a href=\"http://localhost:1302/algorithms/minCostFlow?file_phospho=/home/schnel10/phospho.txt&fileLabel_phospho=uniprot&file_geneExp=/home/schnel10/geneexpression.txt&fileLabel_geneExp=geneid\">http://localhost:1302/algorithms/minCostFlow?file_phospho=/home/schnel10/phospho.txt&fileLabel_phospho=uniprot&file_geneExp=/home/schnel10/geneexpression.txt&fileLabel_geneExp=geneid</a> <br>")
												.append("<b>Extended sample URL</b>: <a href=\"http://localhost:1302/algorithms/minCostFlow?file_phospho=/home/schnel10/phospho.txt&fileLabel_phospho=uniprot&file_geneExp=/home/schnel10/geneexpression.txt&fileLabel_geneExp=geneid&format=na&nodelabel=xref!geneid&nodevalue=phospho\">http://localhost:1302/algorithms/minCostFlow?file_phospho=/home/schnel10/phospho.txt&fileLabel_phospho=uniprot&file_geneExp=/home/schnel10/geneexpression.txt&fileLabel_geneExp=geneid&format=na&nodelabel=xref!geneid&nodevalue=phospho</a><br>")
												.append("</td></tr>")
												;
				}

				return "";

}

bool GraphAlgorithmServerHandler::handle(QHttpRequest *req, QHttpResponse *resp)
{

				QString path(req->path());

				if (GraphAlgorithmServerHandler::shortestPath.exactMatch(path))
				{
								// load ResultObject
								QString result = req->url().queryItemValue("result");
								if (result.size() == 0)
								{
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(404);
												resp->write(QString("ERROR: '/algorithms/shortestPath' needs a ResultObject id as 'result' argument."));
												resp->end();
												return true;

								}
								bool ok;
								UnipaxId result_id = result.toULongLong(&ok);
								if (!ok)
								{
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(404);
												resp->write(QString("ERROR: Could not convert '")
																				.append(result)
																				.append(QString("' to a UnipaxId.")));
												resp->end();
												return true;
								}
								UniPAX::ResultObjectPtr result_obj = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
								if (result_obj == 0)
								{
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(404);
												resp->write(QString("ERROR: Could not load ResultObject from id '")
																				.append(result)
																				.append(QString("'.")));
												resp->end();
												return true;
								}
								// source
								QString source = req->url().queryItemValue("source");
								if (source.size() == 0)
								{
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(404);
												resp->write(QString("ERROR: '/algorithms/shortestPath' needs a ResultObject id as 'source' argument."));
												resp->end();
												return true;

								}
								UnipaxId source_id = source.toULongLong(&ok);
								if (!ok)
								{
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(404);
												resp->write(QString("ERROR: Could not convert '")
																				.append(source)
																				.append(QString("' to a UnipaxId.")));
												resp->end();
												return true;
								}
								if (result_obj->getObjectIds().find(source_id) ==result_obj->getObjectIds().end())
								{
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(404);
												resp->write(QString("ERROR: Source '")
																				.append(source)
																				.append(QString("' is not contained in the selected ResultObject.")));
												resp->end();
												return true;
								}

								// target
								QString target = req->url().queryItemValue("target");
								if (target.size() == 0)
								{
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(404);
												resp->write(QString("ERROR: '/algorithms/shortestPath' needs a ResultObject id as 'target' argument."));
												resp->end();
												return true;

								}
								UnipaxId target_id = target.toULongLong(&ok);
								if (!ok)
								{
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(404);
												resp->write(QString("ERROR: Could not convert '")
																				.append(target)
																				.append(QString("' to a UnipaxId.")));
												resp->end();
												return true;
								}
								if (source_id == target_id)
								{
									resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
									resp->writeHead(404);
									resp->write(QString("ERROR: Source and target are the same: '")
											.append(target));
									resp->end();
									return true;
								}
								if (result_obj->getObjectIds().find(target_id) ==result_obj->getObjectIds().end())
								{
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(404);
												resp->write(QString("ERROR: Target '")
																				.append(target)
																				.append(QString("' is not contained in the selected ResultObject.")));
												resp->end();
												return true;
								}
								// define vector of objects in the result path
								std::vector<UnipaxId> result_path;//, path_edges;
								// create mapping
								QString mapping = req->url().queryItemValue("mapping");
								if (mapping.size() == 0)
								{
												// default:
												mapping.append("regulatory");
								}
								bool show_times = false;
								QString runtime = req->url().queryItemValue("runtime");
								if (mapping.size() != 0)
								{
												show_times = true;
								}
								typedef lemon::ListDigraph SearchGraph;
								typedef UnipaxPtr<SearchGraph>::type SearchGraphPtr;
								typedef SearchGraph::ArcMap<int> LengthMap;
								typedef UnipaxPtr<LengthMap>::type LengthMapPtr;
								typedef SearchGraph::NodeMap<int> DistanceMap;
								typedef UnipaxPtr<DistanceMap>::type DistanceMapPtr;
								typedef lemon::SimplePath<SearchGraph> SearchPath;
								typedef UnipaxPtr<SearchPath>::type SearchPathPtr;
								typedef SearchGraph::ArcMap<UnipaxId> ArcIdMap;
								typedef UnipaxPtr<ArcIdMap>::type ArcIdMapPtr;
								typedef SearchGraph::NodeMap<UnipaxId> NodeIdMap;
								typedef UnipaxPtr<NodeIdMap>::type NodeIdMapPtr;

								std::vector<UniPAX::UPBasePtr> objects;

								if (mapping == "metabolic")
								{
												boost::posix_time::ptime t_start(micro_sec::universal_time());
												UniPAX::GRAPH::MetabolicNetworkPtr network = dbc->createMetabolicNetwork(*result_obj);
												boost::posix_time::time_duration t_end(micro_sec::universal_time() - t_start);
												if (show_times) std::cerr << "Network generation time: " << boost::posix_time::to_iso_string(t_end) << std::endl;
												if (network->id_node_map.find(source_id) == network->id_node_map.end())
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Source '")
																								.append(source)
																								.append(QString("' is not part of the mapped network.")));
																resp->end();
																return true;
												}

												if (network->id_node_map.find(target_id) == network->id_node_map.end())
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Target '")
																								.append(target)
																								.append(QString("' is not part of the mapped network.")));
																resp->end();
																return true;
												}

												SearchPath path;
												t_start = micro_sec::universal_time();
												if(!lemon::dijkstra(network->graph, LengthMap(network->graph, 2))
																				.path(path)
																				.run(network->id_node_map[source_id], network->id_node_map[target_id]))
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Target '")
																								.append(target)
																								.append(QString("' is not reachable from source "))
																								.append(source)
																								.append(QString(".")));
																resp->end();
																return true;
												}
												t_end = micro_sec::universal_time() - t_start;
												if (show_times) std::cerr << "Dijktra runtime: " << boost::posix_time::to_iso_string(t_end) << std::endl;
												// collect ids of path edges and nodes
												for (lemon::PathNodeIt<SearchPath> node(network->graph, path); node != lemon::INVALID; ++node)
												{
																result_path.push_back(network->node_id_map[node]);
												}

												// load the objects from result_path
												if (!dbc->getObjects(objects, result_path))
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Could not load objects from resulting shortest path."));
																resp->end();
																return true;
												}

								}
								else if (mapping == "regulatory")
								{
												boost::posix_time::ptime t_start(micro_sec::universal_time());
												UniPAX::GRAPH::RegulatoryNetworkPtr network = dbc->createRegulatoryNetwork(*result_obj);
												boost::posix_time::time_duration t_end(micro_sec::universal_time() - t_start);
												if (show_times) std::cerr << "Network generation time: " << boost::posix_time::to_iso_string(t_end) << std::endl;
												if (network->id_node_map.find(source_id) == network->id_node_map.end())
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Source '")
																								.append(source)
																								.append(QString("' is not part of the mapped network.")));
																resp->end();
																return true;
												}

												if (network->id_node_map.find(target_id) == network->id_node_map.end())
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Target '")
																								.append(target)
																								.append(QString("' is not part of the mapped network.")));
																resp->end();
																return true;
												}
												SearchPath path;
												t_start = micro_sec::universal_time();
												if(!lemon::dijkstra(network->graph, LengthMap(network->graph, 1))
																				.path(path)
																				.run(network->id_node_map[source_id], network->id_node_map[target_id]))
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Target '")
																								.append(target)
																								.append(QString("' is not reachable from source "))
																								.append(source)
																								.append(QString(".")));
																resp->end();
																return true;
												}
												t_end = micro_sec::universal_time() - t_start;
												if (show_times) std::cerr << "Dijktra runtime: " << boost::posix_time::to_iso_string(t_end) << std::endl;
												// collect ids of path edges and nodes
												SearchPath::ArcIt arc(path);
												for (lemon::PathNodeIt<SearchPath> node(network->graph, path); node != lemon::INVALID; ++node)
												{
																result_path.push_back(network->node_id_map[node]);
																if (arc != lemon::INVALID)
																{
																	result_path.push_back(network->arc_id_map[arc]);
																	++arc;
																}
												}

												// load the objects from result_path
												if (!dbc->getObjects(objects, result_path))
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Could not load objects from resulting shortest path."));
																resp->end();
																return true;
												}

								}
								else if (mapping == "ppi")
								{
									boost::posix_time::ptime t_start(micro_sec::universal_time());
									UniPAX::GRAPH::ProteinProteinInteractionNetworkPtr network = dbc->createPPINetwork(*result_obj);
									boost::posix_time::time_duration t_end(micro_sec::universal_time() - t_start);
									if (show_times) std::cerr << "Network generation time: " << boost::posix_time::to_iso_string(t_end) << std::endl;
									if (network->id_node_map.find(source_id) == network->id_node_map.end())
									{
													resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
													resp->writeHead(404);
													resp->write(QString("ERROR: Source '")
																					.append(source)
																					.append(QString("' is not part of the mapped network.")));
													resp->end();
													return true;
									}

									if (network->id_node_map.find(target_id) == network->id_node_map.end())
									{
													resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
													resp->writeHead(404);
													resp->write(QString("ERROR: Target '")
																					.append(target)
																					.append(QString("' is not part of the mapped network.")));
													resp->end();
													return true;
									}

									SearchPath path;
									UniPAX::GRAPH::ProteinProteinInteractionNetwork::EquiDigraphPtr eq_network = network->createEquivalent();
									t_start = micro_sec::universal_time();
									if(!lemon::dijkstra(eq_network->graph, LengthMap(eq_network->graph, 2))
																	.path(path)
																	.run(eq_network->newNodeRef[network->id_node_map[source_id]], eq_network->newNodeRef[network->id_node_map[target_id]]))
									{
													resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
													resp->writeHead(404);
													resp->write(QString("ERROR: Target '")
																					.append(target)
																					.append(QString("' is not reachable from source "))
																					.append(source)
																					.append(QString(".")));
													resp->end();
													return true;
									}
									t_end = micro_sec::universal_time() - t_start;
									if (show_times) std::cerr << "Dijktra runtime: " << boost::posix_time::to_iso_string(t_end) << std::endl;
									// collect ids of path edges and nodes
									for (lemon::PathNodeIt<SearchPath> node(eq_network->graph, path); node != lemon::INVALID; ++node)
									{
													result_path.push_back(network->node_id_map[eq_network->oriNodeRef[node]]);
									}

									// load the objects from result_path
									if (!dbc->getObjects(objects, result_path))
									{
													resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
													resp->writeHead(404);
													resp->write(QString("ERROR: Could not load objects from resulting shortest path."));
													resp->end();
													return true;
									}
												/*UniPAX::GRAPH::ProteinProteinInteractionNetworkPtr network = dbc->createPPINetwork(*result_obj);
												if (network->id_node_map.find(source_id) == network->id_node_map.end())
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Source '")
																								.append(source)
																								.append(QString("' is not part of the mapped network.")));
																resp->end();
																return true;
												}

												if (network->id_node_map.find(target_id) == network->id_node_map.end())
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Target '")
																								.append(target)
																								.append(QString("' is not part of the mapped network.")));
																resp->end();
																return true;
												}
												SearchPath path;
												if(!lemon::dijkstra(network->graph, LengthMap(network->graph, 1))
																				.path(path)
																				.run(network->id_node_map[source_id], network->id_node_map[target_id]))
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Target '")
																								.append(target)
																								.append(QString("' is not reachable from source "))
																								.append(source)
																								.append(QString(".")));
																resp->end();
																return true;
												}*/
												// collect ids of path edges and nodes
												/*for (SearchPath::ArcIt arc(path); arc != lemon::INVALID; ++arc)
													{
													result_path.push_back(network->arc_id_map[arc]);
													}*/
												/*SearchPath::ArcIt arc(path);
												for (lemon::PathNodeIt<SearchPath> node(network->graph, path); node != lemon::INVALID; ++node)
												{
																result_path.push_back(network->node_id_map[node]);
																if (arc != lemon::INVALID)
																{
																	result_path.push_back(network->arc_id_map[arc]);
																	++arc;
																}
												}

												// load the objects from result_path
												if (!dbc->getObjects(objects, result_path))
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(404);
																resp->write(QString("ERROR: Could not load objects from resulting shortest path."));
																resp->end();
																return true;
												}*/

								}
								//output format transformation
								std::cerr << "ids on path: " << result_path.size() << " objects: " << objects.size() << std::endl;
								if (req->url().queryItemValue("format") == "gmx" || req->url().queryItemValue("format") == "gmt")
								{
												bool gmx_format = true;
												if ((req->url().queryItemValue("format") != "gmx") || objects.size() > 1)
																gmx_format = false;

												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												//				if (gmx_format)
												//					resp->setHeader("Content-Disposition", "attachment; filename=network.gmx");
												//				else
												//					resp->setHeader("Content-Disposition", "attachment; filename=network.gmt");
												resp->writeHead(200);

												std::vector<boost::shared_ptr<UniPAX::UPBase> >::iterator it;
												for (it = objects.begin(); it != objects.end(); it++)
												{
																UniPAX::KernelCollector collector;
																collector.skipPathwaySteps(true);
																collector.collect(*it);

																std::string title;
																std::string description;
																boost::shared_ptr<UniPAX::Entity> first_obj = boost::dynamic_pointer_cast<UniPAX::Entity>(*it);
																if (first_obj)
																{
																				title = first_obj->getStandardName() + " (" + first_obj->getDataSource()->getStandardName() + ")";
																				std::vector<std::string> descriptions = first_obj->getComments();
																				std::string help;
																				for (std::vector<std::string>::iterator it = descriptions.begin(); it != descriptions.end(); it++)
																				{
																								help = *it;
																								std::replace(help.begin(), help.end(), '\n', ' ');
																								description = description + help;
																				}
																}

																UniPAX::GeneSetWriter gmxWriter;
																gmxWriter.setPersistenceManager(collector);
																QTextStream out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));
																out.setCodec("UTF-8");
																gmxWriter.setTitle(title);
																gmxWriter.setDescription(description);
																gmxWriter.write(out,
																								req->url().queryItemValue("geneid") == "true",
																								gmx_format);
												}
												resp->end();
								}
								else if (req->url().queryItemValue("format") == "ids")
								{
												resp->setHeader("Content-Type", "text/xml; charset=UTF-8");
												resp->writeHead(200);
												QString out;
												if (mapping == "ppi")
												{
																for (std::vector<UnipaxId>::const_iterator it = result_path.begin(); it != result_path.end(); ++it)
																{
																				out.append(QString::number(*it))
																								.append(QString("\n"));
																}
												}
												else // metabolic or regulatory
												{
																bool interaction = false;
																for (std::vector<UnipaxId>::const_iterator it = result_path.begin(); it != result_path.end(); ++it)
																{
																				if (interaction)
																				{
																								out.append(QString("\t"))
																												.append(QString::number(*it))
																												.append(QString("\t"))
																												.append(QString::number(*(it+1)))
																												.append(QString("\n"));
																				}
																				else if (it+1 != result_path.end())
																				{
																								out.append(QString::number(*it));
																				}
																				interaction = !interaction;
																}
												}
												resp->write(out);
												resp->end();
												return true;

								}				
								else if (req->url().queryItemValue("format") == "graphml")
								{
												UniPAX::KernelCollector collector;
												collector.skipPathwaySteps(true);
												collector.collect(objects);
												/*for (std::vector<UniPAX::UPBasePtr>::const_iterator it = objects.begin(); it != objects.end(); ++it)
													{
													collector.update(*it);
													}*/

												resp->setHeader("Content-Type", "text/xml; charset=UTF-8");
												resp->writeHead(200);

												UniPAX::GraphMLWriter graphmlWriter;
												//graphmlWriter.setDebug(true);
												//graphmlWriter.restrictToObjects(std::set<UnipaxId>(result_path.begin(), result_path.end()));
												graphmlWriter.setPersistenceManager(collector);

												QXmlStreamWriter out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));
												graphmlWriter.openDocument(out);
												graphmlWriter.writeHeader(out);
												//graphmlWriter.write(out);
												graphmlWriter.writePath(out, result_path);
												graphmlWriter.writeFooter(out);
												graphmlWriter.closeDocument(out);

												resp->end();
								}
								else
								{ // output in biopax format

												UniPAX::KernelCollector collector;
												collector.skipPathwaySteps(true);
												collector.collect(objects);

												resp->setHeader("Content-Type", "text/xml; charset=UTF-8");
												resp->writeHead(200);

												UniPAX::BIOPAXWriter writer;
												writer.setPersistenceManager(collector);

												QXmlStreamWriter out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));
												out.setCodec("UTF-8");
												out.setAutoFormatting(true);
												out.writeStartDocument();

												writer.writeHeader(out);
												bool recursive = false; //TODO check if needed
												if (!recursive)
												{
																writer.write(out);
												}
												else
												{
																for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::const_iterator it(objects.begin()); it != objects.end(); it++)
																{
																				std::stringstream ss;
																				ss << (*it)->getUnipaxId();
																				std::string s;
																				ss >> s;

																				writer.writeObject(s, (*it)->getType(), out);
																}
												}
												writer.writeFooter(out);
												out.writeEndDocument();
												resp->end();
								}


				}
				if ( GraphAlgorithmServerHandler::minCostFlow.exactMatch(path))
				{

								QString networkType = QUrl::fromPercentEncoding(req->url().queryItemValue("networktype").toUtf8());
								if (networkType == "") { //default value
												networkType = "analyzed_subnetwork";
								}


								//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								//(1) CREATE NETWORK	

								// using all entity types
								boost::shared_ptr<UniPAX::GRAPH::RegulatoryNetwork> rg = mapping_engine->createRegulatoryNetwork(UniPAX::Kernel::children("PhysicalEntity", true));
								mapping_engine->addComplexAssemblies(*rg, UniPAX::Kernel::children("PhysicalEntity", true), true);
								mapping_engine->addInteractions(*rg, UniPAX::Kernel::children("PhysicalEntity", true));

								// load regulatory types (ACTIVATION, INHIBITION, REACTION)
								UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcMap<std::string> edgeTypeMap(rg->graph);
								mapping_engine->mapRegulationTypes(*rg, edgeTypeMap);

								// load types the nodes represent
								lemon::ListDigraph::NodeMap<std::string> nodeTypeMap(rg->graph);
								mapping_engine->mapNodeTypes(*rg, nodeTypeMap);

								// load types the arcs represent
								lemon::ListDigraph::ArcMap<std::string> arcTypeMap(rg->graph);
								mapping_engine->mapArcTypes(*rg, arcTypeMap);


								// remove smallMolecules from network
								std::set<UnipaxId> nodesToRemove;
								for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it)
								{
												if ((rg->node_id_map[it] >> 24) == 57) //smallMolecule -> erase
												{
																nodesToRemove.insert(rg->node_id_map[it]);
												}
								}
								rg->removeNodes(nodesToRemove);


								//MinCostFlow variables have to be defined already here to be usable in the 'extendedRegulatoryNetwork'-setting
								lemon::ListDigraph::ArcMap<double> weight(rg->graph);
								lemon::ListDigraph::Node s;
								lemon::ListDigraph::Node t;

								//required flow in target node
								double k=0.0;

								//format-parameter to adapt for graviton early
								QString format = req->url().queryItemValue("format").toLower();


								//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								//(2) ATTACH ATTRIBUTES	

								QString nodelabel = QUrl::fromPercentEncoding(req->url().queryItemValue("nodelabel").toUtf8());
								QString nodevalue = QUrl::fromPercentEncoding(req->url().queryItemValue("nodevalue").toUtf8());

								QString edgelabel = QUrl::fromPercentEncoding(req->url().queryItemValue("edgelabel").toUtf8());
								QString edgevalue = QUrl::fromPercentEncoding(req->url().queryItemValue("edgevalue").toUtf8());


								bool hasNodeLabels = false;
								bool hasEdgeLabels = false;

								UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<std::string> nodeLabelMap(rg->graph);
								UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcMap<std::string> edgeLabelMap(rg->graph);


								//Reactome -------------------------------------------------------------------------------
								UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<std::string> reactomeMap(rg->graph);
								//Load reactome ids from C_ENTITY_DBKEY with "Reactome" as key
								mapping_engine->mapXrefData(*rg, reactomeMap, "Reactome"); 

								//UniProt ---------------------------------------------------------------------------------
								UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<std::string> uniprotMap(rg->graph);
								//Load 'uniprot' ids from C_ENTITY_DBKEY with "UniProt" as key
								mapping_engine->mapXrefData(*rg, uniprotMap, "UniProt");

								//GeneIds ---------------------------------------------------------------------------------
								UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<std::string> geneIdMap(rg->graph);
								//Load 'entrez gene ids' from C_ENTITY_DBKEY with "EntrezGene" as key
								mapping_engine->mapXrefData(*rg, geneIdMap, "EntrezGene");

								//Standard names - read in standard names for unipaxIds from C_NAMES ---------------------
								UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<std::string> standardNamesMap(rg->graph);
								std::string str;
								UnipaxId uId;

								for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
								{
												uId = rg->node_id_map[it];
												str = mapping_engine->getName(uId);
												standardNamesMap[it]=str;
								}



								// KINAXO - read in phospho data ----------------------------------------------------------
								UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<double> phosphoFcMap(rg->graph);

								//Create tmpMap
								std::map<std::string, double> uniprotId_phosphoFc; 
								std::map<std::string, double> geneId_phosphoFc; 

								//special set 
								std::set<std::string> sourceSet;
								//for later visualization of all elements in the source set
								UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<int> InSourceSetMap(rg->graph);

								std::string fileInName_phospho;
								QString phosphoData = QUrl::fromPercentEncoding(req->url().queryItemValue("file_phospho").toUtf8());
								QString fileLabel_phospho = QUrl::fromPercentEncoding(req->url().queryItemValue("fileLabel_phospho").toUtf8());


								if (phosphoData == "") { //default dummy dataset
												fileInName_phospho = "/home/schnel10/phospho.txt"; 
												fileLabel_phospho = "uniprot";
								}
								else { //use actual filepath
												fileInName_phospho = phosphoData.toAscii().data();;
								}


								if (fileLabel_phospho == "uniprot") 
								{	
												readAttributesFromFile_duplicateFree(fileInName_phospho, uniprotId_phosphoFc, sourceSet);

												int phosphoNumber=0;

												//Map UniProtIds to unipaxIds
												for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
												{
																if (uniprotId_phosphoFc.find(uniprotMap[it]) != uniprotId_phosphoFc.end())
																{
																				if (uniprotMap[it].compare("") != 0) {
																								phosphoFcMap[it] = uniprotId_phosphoFc[uniprotMap[it]];
																								++phosphoNumber;
																				}
																				else { 	//Else means that there is just an empty entry - nothing to do
																								phosphoFcMap[it] = 0.0;
																				}

																}
																else { 	//set to dummy value for neutral fold change - these have no phospho-value
																				phosphoFcMap[it] = 0.0; //indifferent standard dummy fold change - or 1.0
																}
												}


												int sourceSetCounter=0;
												//Fill InSourceSetMap
												for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
												{
																if (uniprotId_phosphoFc.find(uniprotMap[it]) != uniprotId_phosphoFc.end()) 	
																{																			
																				if (uniprotMap[it].compare("") != 0) {
																								if (sourceSet.find(uniprotMap[it]) != sourceSet.end()) {
																												InSourceSetMap[it] = 1;
																												++sourceSetCounter;
																								}
																								else { //not belonging to sourceSet
																												InSourceSetMap[it] = 0;
																								}
																				}
																				else { 	//Else means that there is just an empty entry - nothing to do
																								InSourceSetMap[it] = 0;
																				}
																}
																else { //no node found for them ?
																				InSourceSetMap[it] = 0;
																}
												}

								}
								else if (fileLabel_phospho == "geneid") 
								{	
												readAttributesFromFile_duplicateFree(fileInName_phospho, geneId_phosphoFc, sourceSet);

												int phosphoNumber=0;

												//Map UniProtIds to unipaxIds
												for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
												{
																if (geneId_phosphoFc.find(geneIdMap[it]) != geneId_phosphoFc.end())
																{
																				if (geneIdMap[it].compare("") != 0) {
																								phosphoFcMap[it] = geneId_phosphoFc[geneIdMap[it]];
																								++phosphoNumber;
																				}
																				else { 	//Else means that there is just an empty entry - nothing to do
																								phosphoFcMap[it] = 0.0;
																				}

																}
																else { 	//set to dummy value for neutral fold change - these have no phospho-value
																				phosphoFcMap[it] = 0.0; //indifferent standard dummy fold change - or 1.0
																}
												}



												int sourceSetCounter=0;
												//Fill InSourceSetMap
												for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
												{
																if (geneId_phosphoFc.find(geneIdMap[it]) != geneId_phosphoFc.end()) 	
																{																			
																				if (geneIdMap[it].compare("") != 0) {
																								//geneId gefunden, dann für jede entscheiden, ob sie in source set oder nicht
																								if (sourceSet.find(geneIdMap[it]) != sourceSet.end()) {
																												InSourceSetMap[it] = 1;
																												++sourceSetCounter;
																								}
																								else { //not belonging to sourceSet
																												InSourceSetMap[it] = 0;
																								}
																				}
																				else { 	//Else means that there is just an empty entry - nothing to do
																								InSourceSetMap[it] = 0;
																				}
																}
																else { //no node found for them ?
																				InSourceSetMap[it] = 0;
																}
												}

								}
								else {
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(200);
												resp->write(QString("\n Invalid fileLabel_phospho: ").append(fileLabel_phospho).
																				append("\n\n Possible parameters: geneid, uniprot"));
								}



								// Affymetrix - read in gene expression data --------------------------------------------------
								UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<double> geneExpressionFcMap(rg->graph);

								//Create tmpMap
								std::map<std::string, double> geneId_geneExpressionFc;
								std::map<std::string, double> uniprotId_geneExpressionFc;

								//special set 
								std::set<std::string> targetSet;
								//for later visualization of all elements in the source set
								UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<int> InTargetSetMap(rg->graph);


								std::string fileInName_geneExp;
								QString geneExpData = QUrl::fromPercentEncoding(req->url().queryItemValue("file_geneExp").toUtf8());
								QString fileLabel_geneExp = QUrl::fromPercentEncoding(req->url().queryItemValue("fileLabel_geneExp").toUtf8());

								if (geneExpData == "") { //use default dummy test data
												fileInName_geneExp = "/home/schnel10/geneexpression.txt";
												fileLabel_geneExp = "geneid";
								}
								else {
												fileInName_geneExp = geneExpData.toAscii().data();;
								}

								if (fileLabel_geneExp == "geneid")
								{
												readAttributesFromFile_duplicateFree(fileInName_geneExp, geneId_geneExpressionFc, targetSet);

												int geneExpressionNumber=0;

												//Map geneIds to unipaxIds
												//geneIdMap has no own find-method -> run through geneIdMap and call 'find' on geneId_geneExpressionFc
												//and store both in geneExpressionFcMap
												for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
												{
																if (geneId_geneExpressionFc.find(geneIdMap[it]) != geneId_geneExpressionFc.end())
																{
																				if (geneIdMap[it].compare("") != 0) { //Der Knoten ist über eine geneId identifizierbar
																								geneExpressionFcMap[it] = geneId_geneExpressionFc[geneIdMap[it]];
																								++geneExpressionNumber;
																				}
																				else { 	//Else means that node cannot be reached via valid geneId
																								geneExpressionFcMap[it]=0.0;
																				}			
																}
																else { //set to dummy value for neutral fold change - node cannot be mapped
																				geneExpressionFcMap[it] = 0.0; 
																}
												}

												int targetSetCounter=0;
												//Fill InTargetSetMap
												for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
												{
																if (geneId_geneExpressionFc.find(geneIdMap[it]) != geneId_geneExpressionFc.end()) 
																{																	
																				if (geneIdMap[it].compare("") != 0) {
																								//geneId found, decide whether in target set or not
																								if (targetSet.find(geneIdMap[it]) != targetSet.end()) {
																												InTargetSetMap[it] = 1;
																												++targetSetCounter;
																								}
																								else { //not belonging to sourceSet
																												InTargetSetMap[it] = 0;
																								}
																				}
																				else { 	//Else means that there is just an empty entry - nothing to do
																								InTargetSetMap[it] = 0;
																				}

																}
																else { //no node found for them ?
																				InTargetSetMap[it] = 0;
																}
												}

								}

								else if (fileLabel_geneExp == "uniprot")
								{
												readAttributesFromFile_duplicateFree(fileInName_geneExp, uniprotId_geneExpressionFc, targetSet);

												int geneExpressionNumber=0;

												//Map geneIds to unipaxIds
												//uniprotIdMap has no own find-method -> run through uniprotIdMap and call 'find' on uniprotId_geneExpressionFc
												//and store both in geneExpressionFcMap
												for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
												{
																if (uniprotId_geneExpressionFc.find(uniprotMap[it]) != uniprotId_geneExpressionFc.end())
																{
																				if (uniprotMap[it].compare("") != 0) { //Node can be identified by geneId
																								geneExpressionFcMap[it] = uniprotId_geneExpressionFc[uniprotMap[it]];
																								++geneExpressionNumber;
																				}
																				else { 	//Else means that node cannot be reached via valid geneId
																								geneExpressionFcMap[it]=0.0;
																				}			
																}
																else { //set to dummy value for neutral fold change - node cannot be mapped
																				geneExpressionFcMap[it] = 0.0; 
																}
												}

												int targetSetCounter=0;
												//Fill InTargetSetMap
												for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
												{
																if (uniprotId_geneExpressionFc.find(uniprotMap[it]) != uniprotId_geneExpressionFc.end()) 
																{																	
																				if (uniprotMap[it].compare("") != 0) {
																								//uniprotId found, decide whether in source set or not
																								if (targetSet.find(uniprotMap[it]) != targetSet.end()) {
																												InTargetSetMap[it] = 1;
																												++targetSetCounter;
																								}
																								else { //not belonging to sourceSet
																												InTargetSetMap[it] = 0;
																								}
																				}
																				else { 	//Else means that there is just an empty entry - nothing to do
																								InTargetSetMap[it] = 0;
																				}

																}
																else { //no node found for them ?
																				InTargetSetMap[it] = 0;
																}
												}

								}

								else {
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(200);
												resp->write(QString("\n Invalid fileLabel_geneExp: ").append(fileLabel_geneExp).
																				append("\n\n Possible parameters: geneid, uniprot"));
								}



								// FILTERING ////////////////////////////////////////////////////////////////////////////////////////////////7

								QString filter = QUrl::fromPercentEncoding(req->url().queryItemValue("filter").toUtf8());

								if (filter.startsWith("\"") && filter.endsWith("\""))
								{
												filter.remove(0,1);
												filter.remove(filter.size() - 1, 1);
								}

								std::string pathway;
								std::string organism;

								QStringList _filter = filter.split(",");
								for (int i = 0; i < _filter.size(); ++i)
								{

												QString item = _filter[i];
												if (item.startsWith("organism!"))
												{
																item.remove(0, QString("organism!").size());
																std::set<UnipaxId> organismIds;
																organismIds.insert(item.toULongLong());
																mapping_engine->filterByOrganisms(*rg, organismIds);
																organism = mapping_engine->getName(item.toULongLong());

												}
												else if (item.startsWith("pathway!"))
												{
																item.remove(0, QString("pathway!").size());
																mapping_engine->filterByPathway(*rg, item.toULongLong());
																pathway = mapping_engine->getName(item.toULongLong());
												}
												else if (item.startsWith("nodetype!"))
												{
																item.remove(0, QString("nodetype!").size());
																if (UniPAX::Kernel::isType(item.toStdString()))
																{
																				rg->filterNodes(nodeTypeMap, item.toStdString(), std::equal_to<std::string>());
																}
												}
												else if (item.startsWith("edgetype!"))
												{
																item.remove(0, QString("edgetype!").size());
																rg->filterArcs(edgeTypeMap, item.toStdString(), std::equal_to<std::string>());
												}

								}
								rg->eraseDisconnectedNodes();



								//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								//(3) EXTEND NETWORK		

								if (networkType == "analyzed_subnetwork" || networkType == "extended") //default networkType is analyzed_subnetwork
								{


												//(3a) Modify graph: Add artificial source and target

												//Add to digraph
												s = rg->createNode(0); //createNode calls addNode-method
												t = rg->createNode(1); //1 is new unipax-Id for t

												//add label for them
												geneIdMap[s]="source";
												geneIdMap[t]="target";

												standardNamesMap[s]="source";
												standardNamesMap[t]="target";



												//(3b) Create 'special sets' Prot und Gen		

												std::set<UnipaxId> Prot;
												Prot.clear();

												for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
												{
																if (InSourceSetMap[it] == 1) {
																				Prot.insert(rg->node_id_map[it]);
																}
												}


												std::set<UnipaxId> Gen;
												Gen.clear();


												//filled with unipaxIds belonging to elements in targetSet
												for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg->graph); it != lemon::INVALID; ++it) 
												{
																if (InTargetSetMap[it] == 1) {
																				Gen.insert(rg->node_id_map[it]);
																}
												}


												//(3 c) Add edges from source and target to special sets		

												int idCounter=1;

												//Add arcs from s to all elements in Prot
												for (std::set<UnipaxId>::iterator it = Prot.begin(); it!= Prot.end(); it++)
												{
																rg->createEdge(s, rg->id_node_map[*it], idCounter);
																idCounter++;
																//rg->graph.addArc(s, rg->id_node_map[*it]);
												}


												//Add arcs from all elements in Tra to t
												for (std::set<UnipaxId>::iterator it2 = Gen.begin(); it2!= Gen.end(); it2++)
												{
																rg->createEdge(rg->id_node_map[*it2], t, idCounter);
																idCounter++;
																//rg->graph.addArc(rg->id_node_map[*it2], t);			
												}


												//(3 d) Create maps to represent weights, capacities and amounts of required flow	

												double standardWeight = 1.0; //TODO: just test-value

												for (UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcIt it(rg->graph); it != lemon::INVALID; ++it)
												{

																double fC_u,fC_v; // fold changes for u and v
																double dd_u, dd_v; // degree of deregulation for u and v

																//Figure out the participating nodes u and v according to the edge
																lemon::ListDigraph::Arc e = it;
																lemon::ListDigraph::Node u = rg->graph.source(e); 
																lemon::ListDigraph::Node v = rg->graph.target(e);


																if (edgeTypeMap[it].compare("") != 0)
																{

																				//Nodes' fold changes: 
																				//read from geneExpressionMap only if node is in target set
																				if (InTargetSetMap[u] == 1) {
																								if (geneExpressionFcMap[u] != 0.0) {
																												fC_u = geneExpressionFcMap[u];
																								}
																								else {
																												fC_u = 1.0;
																								}
																				}
																				else {
																								if (phosphoFcMap[u] != 0.0) {
																												fC_u = phosphoFcMap[u];
																								}
																								else {
																												fC_u = 1.0;
																								}
																				}

																				if (InTargetSetMap[v] == 1) {
																								if (geneExpressionFcMap[v] != 0.0) {
																												fC_v = geneExpressionFcMap[v];
																								}
																								else {
																												fC_v = 1.0;
																								}
																				}
																				else {
																								if (phosphoFcMap[v] != 0.0) {
																												fC_v = phosphoFcMap[v];
																								}
																								else {
																												fC_v = 1.0;
																								}
																				}


																				//Discriminate between ACTIVATION, INHIBITION and REACTION - but not whether allosteric, competitive etc.
																				if ((QString(edgeTypeMap[it].c_str())).startsWith("ACTIVATION"))
																				{					
																								//Case distinction

																								//Actual weight
																								if ((fC_u>=1 && fC_v>=1) || (fC_u<=-1 && fC_v<=-1)){ //u and v upregulated or u and v downregulated =0 not ok, >/< 1/-1
																												fC_u = degreeOfDeregulation(fC_u);
																												fC_v = degreeOfDeregulation(fC_v);
																												weight[it] = (double) (fC_u + fC_v)/2; 
																								}
																								//Standard weight
																								else{
																												weight[it] = standardWeight; 
																								}					
																				}
																				else if ((QString(edgeTypeMap[it].c_str())).startsWith("INHIBITION"))
																				{					
																								//Case distinction

																								//Actual weight 
																								if ((fC_u>=1 && fC_v<=-1) || (fC_u<=-1 && fC_v>=1)){ //u and v regulated in opposite ways
																												fC_u = degreeOfDeregulation(fC_u);
																												fC_v = degreeOfDeregulation(fC_v);
																												weight[it] = (double) (fC_u + fC_v)/2;
																								}
																								//Standard weight
																								else{
																												weight[it] = standardWeight; 
																								}					
																				}
																				else
																				{
																								//Set to actual weight --------------------------------------------------------------
																								fC_u = degreeOfDeregulation(fC_u);
																								fC_v = degreeOfDeregulation(fC_v);
																								weight[it] = (double) (fC_u + fC_v)/2;
																				}
																} 

																else //Edge type not given
																{
																				//Set to actual weight---------------------------------------------------------------------
																				if (InTargetSetMap[u] == 1) {
																								if (geneExpressionFcMap[u] != 0.0) {
																												fC_u = geneExpressionFcMap[u];
																								}
																								else {
																												fC_u = 1.0;
																								}
																				}
																				else {
																								if (phosphoFcMap[u] != 0.0) {
																												fC_u = phosphoFcMap[u];
																								}
																								else {
																												fC_u = 1.0;
																								}
																				}

																				if (InTargetSetMap[v] == 1) {
																								if (geneExpressionFcMap[v] != 0.0) {
																												fC_v = geneExpressionFcMap[v];
																								}
																								else {
																												fC_v = 1.0;
																								}
																				}
																				else {
																								if (phosphoFcMap[v] != 0.0) {
																												fC_v = phosphoFcMap[v];
																								}
																								else {
																												fC_v = 1.0;
																								}
																				}

																				fC_u = degreeOfDeregulation(fC_u);
																				fC_v = degreeOfDeregulation(fC_v);
																				weight[it] = (double) (fC_u + fC_v)/2;

																				edgeTypeMap[it] = "pp";
																}

																//Weights to Source Set absolute value of element in source set
																if (InSourceSetMap[v]) {
																				weight[it] = degreeOfDeregulation(fC_v);
																				edgeTypeMap[it] = "pp";
																}

																//Weights to target node: standard weights
																if (InTargetSetMap[u]) {
																				weight[it] = standardWeight;
																				edgeTypeMap[it] = "pp";
																}

												}

												//Transform weights via "1/..." with 'new definition of fold change'
												for (UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcIt	it(rg->graph); it != lemon::INVALID; ++it)
												{
																if (weight[it] != 0) {
																				weight[it] = (double) 1/weight[it];
																}
																else { //standard-weight
																				weight[it] = standardWeight;
																}
												}



								} // END of extendedRegulatory-Graph and minCostFlow-case



								//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								//(4) RUN MIN-COST-FLOW		


								if ( networkType == "analyzed_subnetwork") //Begin minCostFlow case
								{				
												lemon::CostScaling<lemon::ListDigraph, double, double> ns(rg->graph);

												//REGISTER THIS MAP IN NETWORK-ALGO
												ns.costMap(weight);

												lemon::ListDigraph::ArcMap<double> upper(rg->graph);

												for (UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcIt it(rg->graph); it != lemon::INVALID; ++it)
												{
																upper[it] = 1.0;
												}

												//REGISTER THIS MAP IN NETWORK-ALGO
												ns.upperMap(upper);

												//Required amount of flow from s to t.
												QString kQString = QUrl::fromPercentEncoding(req->url().queryItemValue("k").toUtf8());
												std::string kString =  kQString.toAscii().data();

												bool feasible=true;
												bool feasible_graviton=true;
												std::istringstream stm_k;
												if (kString == "") { //use large default value
																k=0;

																QDir dir = QDir::root();    
																if (!dir.cd("tmp")) {    
																}
																if (!dir.cd("subnetworks")) { //dos not exist yet
																				//create folder
																				dir.mkdir("subnetworks");
																}
																else {
																}

																while (feasible) {
																				k=k+1;
																				ns.stSupply(s,t,k);
																				feasible = ns.run();


																				if (format == "graviton" && feasible) {

																								//Flow map on archs
																								lemon::ListDigraph::ArcMap<double> flow_map(rg->graph);

																								ns.flowMap(flow_map);

																								std::set<lemon::ListDigraph::Arc> subEdges;
																								//store extended version in subEdges2
																								std::set<lemon::ListDigraph::Arc> subEdges2;

																								//Iterate over all arcs in flow map and select edges where flow goes through
																								for (UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcIt it(rg->graph); it != lemon::INVALID; ++it)
																								{
																												if (flow_map[it] > 0) {
																																subEdges.insert(it);
																																//	subEdges2.insert(it);
																												}
																								}

																								//generate new regulatory network
																								boost::shared_ptr<UniPAX::GRAPH::RegulatoryNetwork> rg_sub = mapping_engine->createRegulatoryNetwork(UniPAX::Kernel::children("PhysicalEntity", true));

																								//delete all nodes
																								std::set<UnipaxId> nodes_to_keep;
																								std::set<lemon::ListDigraph::Arc> edges_to_keep;	

																								//insert special ones to keep-sets
																								for (std::set<lemon::ListDigraph::Arc>::iterator it = subEdges.begin(); it != subEdges.end(); it++)
																								{					
																												nodes_to_keep.insert(rg->node_id_map[rg->graph.source(*it)]);
																												nodes_to_keep.insert(rg->node_id_map[rg->graph.target(*it)]);

																												edges_to_keep.insert(*it);
																								}

																								rg_sub->retainNodes(nodes_to_keep);
																								rg_sub->retainArcs(edges_to_keep);

																								rg_sub->eraseDisconnectedNodes();

																								//now add source, target and edges to all nodes to having a predecessor or child
																								lemon::ListDigraph::Node s2 = rg_sub->createNode(0); //createNode calls addNode-method
																								lemon::ListDigraph::Node t2 = rg_sub->createNode(1); //1 is new unipax-Id for t

																								//create own geneIdMap:
																								UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<std::string> geneIdMap_sub(rg_sub->graph);
																								//Load 'entrez gene ids' from C_ENTITY_DBKEY with "EntrezGene" as key
																								mapping_engine->mapXrefData(*rg_sub, geneIdMap_sub, "EntrezGene"); //create own mapping engine?

																								geneIdMap_sub[s2]="source";
																								geneIdMap_sub[t2]="target";

																								//Create own edgeTypeMap
																								// load regulatory types (ACTIVATION, INHIBITION, REACTION)
																								UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcMap<std::string> edgeTypeMap_sub(rg_sub->graph);
																								mapping_engine->mapRegulationTypes(*rg_sub, edgeTypeMap_sub);

																								//per node: iterate over incoming and outgoing arcs

																								for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt it(rg_sub->graph); it != lemon::INVALID; ++it) 
																								{
																												lemon::ListDigraph::Node n = it; 

																												bool isSource=true; //indicates wheter a node needs to be connected to s

																												for (lemon::ListDigraph::InArcIt it2(rg_sub->graph, n); it2 != lemon::INVALID; ++it2) {
																																isSource=false;
																												}
																												if (isSource) {
																																if (rg_sub->node_id_map[n]!=1 && rg_sub->node_id_map[n]!=0) { //nicht hinzufügen, wenn target dran ist and no self-loop
																																				lemon::ListDigraph::Arc e = rg_sub->graph.addArc(s2, it);
																																				edgeTypeMap_sub[e] = "pp";
																																}
																												}

																												bool isSink=true; //indicates whether a node needs to be connected to t

																												for (lemon::ListDigraph::OutArcIt it2(rg_sub->graph, n); it2 != lemon::INVALID; ++it2) {
																																isSink=false;
																												}
																												if (isSink) {
																																if (rg_sub->node_id_map[n]!=0 && rg_sub->node_id_map[n]!=1) { //nicht hinzufügen, wenn source dran ist and no self-loop
																																				lemon::ListDigraph::Arc e = rg_sub->graph.addArc(it, t2);
																																				edgeTypeMap_sub[e] = "pp";
																																}
																												}

																								}

																								std::stringstream oss;
																								std::string extendedFilename;
																								oss << "/tmp/subnetworks/network.k" << k << ".sif";
																								//oss << "/home/schnel10/subnetworks/network.k" << k << ".sif";
																								oss >> extendedFilename;

																								std::ofstream myfile;
																								myfile.open(extendedFilename.c_str());

																								lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg_sub->graph, myfile);
																								w.labelMap(geneIdMap_sub);
																								w.relationMap(edgeTypeMap_sub).run();

																								myfile.close();

																				}

																}
																k=k-1; //k now set to largest value to obtain feasible solution

												}
												else{
																stm_k.str(kString);
																stm_k >> k;
																if (format == "graviton") {
																				//Warning: graviton only possible without given k
																				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																				resp->writeHead(200);
																				resp->write(QString("\n Conflicting parameters: graviton and k").append(nodelabel).
																												append("\n\n For the usage of graviton, k must not be assigned"));
																}
												}


												//Set supply for source and target
												ns.stSupply(s,t,k);


												//(4 a) Run NetworkSimplex	

												ns.run(); //this is enough with CostScaling algorithm

												//Flow map on archs
												lemon::ListDigraph::ArcMap<double> flow_map(rg->graph);

												ns.flowMap(flow_map);

												std::set<lemon::ListDigraph::Arc> subEdges;

												//Iterate over all arcs in flow map and select edges where flow goes through
												for (UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcIt it(rg->graph); it != lemon::INVALID; ++it)
												{
																if (flow_map[it] > 0) {
																				subEdges.insert(it);
																}
												}

												rg->retainArcs(subEdges); 
												//Only 'disconnected' nodes are removed, but the ones connected to source / target still remain
												//Delete the ones without flow
												//TODO: Not that nice, but works..!
												for (UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcIt it(rg->graph); it != lemon::INVALID; ++it)
												{
																if (flow_map[it] == 0) {
																				rg->graph.erase(it);
																}
												}

												rg->eraseDisconnectedNodes();


								}	//End minCost-Flow-case




								//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								//(5) OUTFILE-WRITER 					

								QTextStream out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));

								std::stringstream ss;

								if (format == "sif" || format == "") //-----------------------------------------------------------------------------------------------------------
								{ 	
												QString tmpString;

												if (networkType == "analyzed_subnetwork") 
												{
																//for custom file name generation with value of k!
																std::stringstream oss;
																std::string extendedFilename;
																oss << "filename=network_k" << k << ".sif";
																oss >> extendedFilename;
																tmpString = QString("attachment; ").append(extendedFilename.c_str());
												}
												else {
																tmpString = QString("attachment; filename=network.sif");
												}

												const QString cString = tmpString;


												if (nodelabel == "uniprot") //mapped to lower case
												{
																resp->setHeader("Content-Disposition", cString);
																resp->writeHead(200);

																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, ss);
																w.labelMap(uniprotMap); //This is supposed to return  in the sif file...
																w.relationMap(edgeTypeMap).run();	
												}

												else if (nodelabel == "reactome") //mapped to lower case
												{
																resp->setHeader("Content-Disposition",  cString);
																resp->writeHead(200);

																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, ss);
																w.labelMap(reactomeMap); //This is supposed to return  in the sif file...
																w.relationMap(edgeTypeMap).run();	
												}

												else if (nodelabel == "geneid")
												{	
																resp->setHeader("Content-Disposition", cString);
																resp->writeHead(200);

																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, ss);
																w.labelMap(geneIdMap); //This is supposed to return geneIds in the sif file...
																w.relationMap(edgeTypeMap).run();	
												}

												else if (nodelabel == "unipax" || nodelabel == "") //regular sif file - with unipaxIds as standard nodelabels
												{
																resp->setHeader("Content-Disposition",  cString);
																resp->writeHead(200);

																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, ss);
																w.labelMap(rg->node_id_map);
																w.relationMap(edgeTypeMap).run();	
												}

												else { //wrong nodelabel set, e.g. nodelabel=geneid instead of nodelabel=xref!geneid
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(200);
																resp->write(QString("\n Invalid nodelabel: ").append(nodelabel).
																								append("\n\n Possible parameters: geneid, reactome, uniprot, unipax"));
												}	
								}


								else if (format == "na") //-----------------------------------------------------------------------------------------------------------
								{	

												QString tmpString;

												if (networkType == "analyzed_subnetwork") 
												{
																//for custom file name generation with value of k!
																std::stringstream oss;
																std::string extendedFilename;
																oss << "filename=" << nodevalue.toAscii().data() << "_k" << k << ".na";
																oss >> extendedFilename;
																tmpString = QString("attachment; ").append(extendedFilename.c_str());
												}
												else {
																tmpString = QString("attachment; filename=").append(nodevalue).append(".na");
												}

												const QString cString = tmpString;

												if (nodevalue == "phospho")
												{
																resp->setHeader("Content-Disposition",  cString);
																resp->writeHead(200);

																//SIF-File is written to std::cout
																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, std::cout);

																if (nodelabel == "geneid")
																{
																				w.labelMap(geneIdMap);
																}
																else if (nodelabel == "reactome")
																{
																				w.labelMap(reactomeMap);
																}
																else if (nodelabel == "uniprot")
																{
																				w.labelMap(uniprotMap);
																}
																else { //not assigned -> unipax
																				w.labelMap(rg->node_id_map);
																}

																w.relationMap(edgeTypeMap);
																w.nodeMap("phospho (class=Double)", phosphoFcMap, ss).run();
												}

												else if (nodevalue == "geneexpression")
												{					
																resp->setHeader("Content-Disposition",  cString);
																resp->writeHead(200);

																//SIF-File is written to std::cout
																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, std::cout);

																if (nodelabel == "geneid")
																{
																				w.labelMap(geneIdMap);
																}
																else if (nodelabel == "reactome")
																{
																				w.labelMap(reactomeMap);
																}
																else if (nodelabel == "uniprot")
																{
																				w.labelMap(uniprotMap);
																}
																else { //not assigned -> unipax
																				w.labelMap(rg->node_id_map);
																}

																w.relationMap(edgeTypeMap);
																w.nodeMap("geneExpression (class=Double)", geneExpressionFcMap, ss).run();
												}

												else if (nodevalue == "sourceset") 
												{
																resp->setHeader("Content-Disposition",  cString);
																resp->writeHead(200);

																//SIF-File is written to std::cout
																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, std::cout);

																if (nodelabel == "geneid")
																{
																				w.labelMap(geneIdMap);
																}
																else if (nodelabel == "reactome")
																{
																				w.labelMap(reactomeMap);
																}
																else if (nodelabel == "uniprot")
																{
																				w.labelMap(uniprotMap);
																}
																else { //not assigned -> unipax
																				w.labelMap(rg->node_id_map);
																}

																w.relationMap(edgeTypeMap);
																w.nodeMap("InSourceSet", InSourceSetMap, ss).run();
												}

												else if (nodevalue == "targetset") 
												{					
																resp->setHeader("Content-Disposition",  cString);
																resp->writeHead(200);

																//SIF-File is written to std::cout 
																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, std::cout);

																if (nodelabel == "geneid")
																{
																				w.labelMap(geneIdMap);
																}
																else if (nodelabel == "reactome")
																{
																				w.labelMap(reactomeMap);
																}
																else if (nodelabel == "uniprot")
																{
																				w.labelMap(uniprotMap);
																}
																else { //not assigned -> unipax
																				w.labelMap(rg->node_id_map);
																}

																w.relationMap(edgeTypeMap);
																w.nodeMap("InTargetSet", InTargetSetMap, ss).run();
												}

												else if (nodevalue == "xref!uniprot") //mapped to lower case
												{
																resp->setHeader("Content-Disposition",  cString);
																resp->writeHead(200);

																//SIF-File is written to std::cout
																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, std::cout);

																if (nodelabel == "geneid")
																{
																				w.labelMap(geneIdMap);
																}
																else if (nodelabel == "reactome")
																{
																				w.labelMap(reactomeMap);
																}
																else if (nodelabel == "uniprot")
																{
																				w.labelMap(uniprotMap);
																}
																else { //not assigned -> unipax
																				w.labelMap(rg->node_id_map);
																}

																w.relationMap(edgeTypeMap);
																w.nodeMap("uniprot (class=String)", uniprotMap, ss).run();
												}

												else if (nodevalue == "xref!geneid")
												{	
																resp->setHeader("Content-Disposition", cString);
																resp->writeHead(200);

																//SIF-File is written to std::cout
																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, std::cout);

																if (nodelabel == "geneid")
																{
																				w.labelMap(geneIdMap);
																}
																else if (nodelabel == "reactome")
																{
																				w.labelMap(reactomeMap);
																}
																else if (nodelabel == "uniprot")
																{
																				w.labelMap(uniprotMap);
																}
																else { //not assigned -> unipax
																				w.labelMap(rg->node_id_map);
																}

																w.relationMap(edgeTypeMap);
																w.nodeMap("geneId (class=String)", geneIdMap, ss).run();
												}

												else if (nodevalue == "standardname")
												{
																resp->setHeader("Content-Disposition",  cString);
																resp->writeHead(200);

																//SIF-File is written to std::cout
																lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, std::cout);

																if (nodelabel == "geneid")
																{
																				w.labelMap(geneIdMap);
																}
																else if (nodelabel == "reactome")
																{
																				w.labelMap(reactomeMap);
																}
																else if (nodelabel == "uniprot")
																{
																				w.labelMap(uniprotMap);
																}
																else { //not assigned -> unipax
																				w.labelMap(rg->node_id_map);
																}

																w.relationMap(edgeTypeMap);
																w.nodeMap("standardName (class==String)", standardNamesMap, ss).run();
												}

												else if (nodevalue == "") // if no nodelabel given or invalid nodelabel - error
												{
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(200);
																resp->write(QString("\n For .na-file a nodevalue has to be assigned").
																								append("\n\n Possible parameters: phospho, geneexpression, sourceset, targetset, standardname, xref!uniprot, xref!geneid"));
												}

												else { //impossible nodelabel given
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(200);
																resp->write(QString("\n Invalid nodelabel: ").append(nodelabel).
																								append("\n\n Possible parameters: phospho, geneexpression, sourceset, targetset, standardname, xref!uniprot, xref!geneid"));
												}
								}

								else if (format == "ea") //-----------------------------------------------------------------------------------------------------------
								{

												if (networkType == "full") { //edgeweights only for extended and mincostflow
																resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																resp->writeHead(200);
																resp->write(QString("\n Invalid networktype: ").append(networkType).
																								append("\n\n Edge weights only computed for networktypes 'extended' and 'analyzed_subnetwork'!"));
												}
												else { //edge weights already computed

																QString tmpString;

																//for custom file name generation with value of k!
																std::stringstream oss;
																std::string extendedFilename;
																if (networkType == "extended")
																{	
																				oss << "filename=edgeweight.ea";
																}
																else {
																				oss << "filename=edgeweight" << "_k" << k << ".ea";
																}
																oss >> extendedFilename;
																tmpString = QString("attachment; ").append(extendedFilename.c_str());

																const QString cString = tmpString;


																if (edgevalue == "edgeweight") {

																				bool firstOne=true;


																				for (UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcIt it(rg->graph); it != lemon::INVALID; ++it)
																				{
																								std::stringstream tmpstream, weightstream;
																								std::string tmpString, weightString;
																								QString test;
																								tmpstream.clear();

																								//edge type: ACTIVATION and INHIBITION need to be written in lower case as pp, phosphorylation and so on
																								if (edgeTypeMap[it] == "ACTIVATION") {
																												edgeTypeMap[it] = "activation";
																								}
																								else if (edgeTypeMap[it] == "INHIBITION") {
																												edgeTypeMap[it] = "inhibition";
																								}

																								if (nodelabel == "" || nodelabel == "unipax") 
																								{
																												if (firstOne) {
																																resp->setHeader("Content-Disposition", cString);
																																resp->writeHead(200);
																																const QString header = QString("edgeWeight (class=Double) \n");
																																resp->write(header);

																																firstOne=false;
																												}
																												tmpstream << rg->node_id_map[rg->graph.source(it)] << "+%28" << edgeTypeMap[it] << "%29+" << rg->node_id_map[rg->graph.target(it)]; 
																								}
																								else if (nodelabel == "geneid")
																								{
																												if (firstOne) {
																																resp->setHeader("Content-Disposition", cString);
																																resp->writeHead(200);
																																const QString header = QString("edgeWeight (class=Double) \n");
																																resp->write(header);

																																firstOne=false;
																												}
																												tmpstream << geneIdMap[rg->graph.source(it)] << "+%28" << edgeTypeMap[it] << "%29+" << geneIdMap[rg->graph.target(it)]; 
																								}
																								else {
																												//these labels not supported -> error message
																												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																												resp->writeHead(200);
																												resp->write(QString("\n Invalid nodelabel: ").append(nodelabel).
																																				append("\n\n For 'edgeweight' only the nodelables 'unipax' and 'geneid' are supported!"));
																												resp->end();
																												return true;
																								}
																								tmpstream >> tmpString;

																								weightstream.clear();
																								weightstream << weight[it];
																								weightstream >> weightString;

																								const QString cString = QString(tmpString.append(" = ").append(weightString).append("\n").c_str());
																								resp->write(cString);
																				}
																}
																else {
																				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
																				resp->writeHead(200);
																				resp->write(QString("\n Invalid edgevalue: ").append(nodelabel).
																												append("\n\n Only 'edgeweight' provided for ea-files!"));
																}
												}
								}

								else if (format == "graviton") // Zip all files that are stored in local folder--------------------------------------------------------------------
								{	

												//zip subnetworks folder
												system("zip -r -j /tmp/subnetworks.zip /tmp/subnetworks");
												//system("zip -r -j /home/schnel10/subnetworks.zip /home/schnel10/subnetworks");

												//empty folder
												system("rm -r -f /tmp/subnetworks");

												//stream zip-file //zipping of file works - streaming not yet

												QFile qfile("/tmp/subnetworks.zip");
												if (!qfile.open( QIODevice::ReadOnly ) ) {
																std::cout << "could not re-open zip file for download" << std::endl;
												}

												//QDataStream out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));			
												QIODevice* out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));			


												QByteArray compressedData = "";
												compressedData=qfile.readAll();			

												qfile.close();

												resp->setHeader("Content-Disposition", "attachment; filename=graviton.zip");
												resp->writeHead(200);

												//out << compressedData; //zip-file not valid -> use write-Function

												out->write(compressedData);

												resp->end();	


												//delete zip again
												system("rm /tmp/subnetworks.zip");

												return true;		

								}

								else // invalid format ------------------------------------------------------------------------------------------
								{ 
												resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
												resp->writeHead(200);
												resp->write(QString("\n Invalid format: ").append(format).
																				append("\n\n Possible parameters: sif, ea, na"));
								}

								out << ss.str().c_str();

								resp->end();

								return true;
				}

				return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * Helper function for reading in attributes from a tab-delimited file of the form
 * <String-Identifier>\tab<numerical value>\tab<indicator of interest> into a map.
 * 
 * @param $first 
 * 		Absolute path to infile.
 * @param $second
 * 		Map in which file entries are stored.
 * @param $third
 * 		Map in which the indicator of interest is stored
 * 
 */

int readAttributesFromFile_duplicateFree (std::string inFile, std::map<std::string, double>& tmpMap, std::set<std::string>& special_set) 
{
				QHttpResponse *resp;

				tmpMap.clear();

				std::string id;
				double foldChange;
				double interesting; //1 if interesting

				double absOld, absNew;

				std::vector<std::vector<std::string> > data;

				QString inFileQ = inFile.c_str();

				if (inFileQ.startsWith("http://")) { 

								inFileQ.remove(0, QString("http://").size());
								std::string inFileString = inFileQ.toAscii().data();

								size_t pos = inFileString.find_first_of("/");

								QString leftSide = inFileQ.left(pos);
								QString rightSide = inFileQ.remove(0,pos);

								//Split inFileQ
								std::string hostString= leftSide.toAscii().data();  //"vred.bioinf.uni-sb.de";
								std::string locationString= rightSide.toAscii().data(); //"/~lschneider/phospho.txt";

								//////////////////////////////////////////////////////	

								std::stringstream httpStream;

								try
								{

												boost::asio::io_service io_service;

												// Get a list of endpoints corresponding to the server name.
												tcp::resolver resolver(io_service);
												tcp::resolver::query query(hostString, "http");
												tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
												tcp::resolver::iterator end;

												// Try each endpoint until we successfully establish a connection.
												tcp::socket socket(io_service);
												boost::system::error_code error = boost::asio::error::host_not_found;
												while (error && endpoint_iterator != end)
												{
																socket.close();
																socket.connect(*endpoint_iterator++, error);
												}

												// Form the request. We specify the "Connection: close" header so that the
												// server will close the socket after transmitting the response. This will
												// allow us to treat all data up until the EOF as the content.
												boost::asio::streambuf request;
												std::ostream request_stream(&request);
												request_stream << "GET " << locationString << " HTTP/1.0\r\n";
												request_stream << "Host: " << hostString << "\r\n";
												request_stream << "Accept: */*\r\n";
												request_stream << "Connection: close\r\n\r\n";

												// Send the request.
												boost::asio::write(socket, request);

												// Read the response status line.
												boost::asio::streambuf response;
												boost::asio::read_until(socket, response, "\r\n");

												// Check that response is OK.
												std::istream response_stream(&response);
												std::string http_version;
												response_stream >> http_version;

												unsigned int status_code;
												response_stream >> status_code;
												std::string status_message;
												std::getline(response_stream, status_message);
												if (!response_stream || http_version.substr(0, 5) != "HTTP/")
												{
																std::cout << "Invalid response\n";
												}
												if (status_code != 200)
												{
																std::cout << "Response returned with status code " << status_code << "\n";
												}

												// Read the response headers, which are terminated by a blank line.
												boost::asio::read_until(socket, response, "\r\n\r\n");

												// Process the response headers.
												std::string header;
												while (std::getline(response_stream, header) && header != "\r")
																std::cout << header << "\n";
												std::cout << "\n";

												// Write whatever content we already have to output.
												if (response.size() > 0)
																httpStream << &response;

												// Read until EOF, writing data to output as we go.
												while (boost::asio::read(socket, response,
																								boost::asio::transfer_at_least(1), error))
												{
																httpStream << &response;
												}
												if (error != boost::asio::error::eof)
																throw boost::system::system_error(error);
								}
								catch (std::exception& e)
								{
												std::cout << "Exception: " << e.what() << "\n";
								}

								///////////////////////////////////////////////////////////////////////////////////

								while (httpStream) 
								{ 
												std::string s;
												if (!getline( httpStream, s )) break;

												std::istringstream ss(s);
												std::vector<std::string> record;

												while (ss)
												{
																std::string s;
																if (!getline( ss, s, '\t' )) break;
																record.push_back( s );
												}

												//three positions contain the tree values: geneId - foldChange - interestingIndicator
												id = record[0];

												std::istringstream stm;
												stm.str(record[1]);
												stm >> foldChange;

												//check, whether in map already
												if (tmpMap.find(id) != tmpMap.end()) { 					//already in map	 

																if (tmpMap.find(id)->second < 0) {					//check if maximal
																				absOld = -tmpMap.find(id)->second;
																}
																else {
																				absOld = tmpMap.find(id)->second;
																}

																if (foldChange < 0) {
																				absNew = -foldChange;
																}
																else {
																				absNew = foldChange;
																}

																if (absOld >= absNew) {
																				//nothing to change
																}
																else {

																				tmpMap.erase(id);									//delete old pair
																				tmpMap.insert(std::make_pair(id, foldChange)); 	//add new pair
																}
												}
												else { // new in map
																tmpMap.insert(std::make_pair(id, foldChange));
												}

												std::stringstream stm2;
												stm2.str(record[2]);
												stm2 >> interesting;

												if (interesting==1) {
																if (special_set.find(id) != special_set.end()) { 		//already in set 
																				//DO nothing
																}
																else { //if not in set yet - store it 
																				special_set.insert(id);
																}
												}
												data.push_back( record );
								}
				}

				//////////////////////////////////////////////////////	

				else { //on file system
								std::ifstream infile(inFile.c_str());
								while (infile)
								{	
												std::string s;
												if (!getline( infile, s )) break;

												std::istringstream ss(s);
												std::vector<std::string> record;

												while (ss)
												{
																std::string s;
																if (!getline( ss, s, '\t' )) break;
																record.push_back( s );
												}

												//three positions contain the tree values: geneId - foldChange - interestingIndicator
												id = record[0];

												std::istringstream stm;
												stm.str(record[1]);
												stm >> foldChange;

												//check, whether in map already
												if (tmpMap.find(id) != tmpMap.end()) { 					//already in map	 

																if (tmpMap.find(id)->second < 0) {					//check if maximal
																				absOld = -tmpMap.find(id)->second;
																}
																else {
																				absOld = tmpMap.find(id)->second;
																}

																if (foldChange < 0) {
																				absNew = -foldChange;
																}
																else {
																				absNew = foldChange;
																}

																if (absOld >= absNew) {
																				//nothing to change
																}
																else {

																				tmpMap.erase(id);									//delete old pair
																				tmpMap.insert(std::make_pair(id, foldChange)); 	//add new pair
																}
												}
												else { // new in map
																tmpMap.insert(std::make_pair(id, foldChange));
												}

												std::stringstream stm2;
												stm2.str(record[2]);
												stm2 >> interesting;

												if (interesting==1) {
																if (special_set.find(id) != special_set.end()) { 		//already in set 
																				//DO nothing
																}
																else { //if not in set yet - store it 
																				special_set.insert(id);
																}
												}
												data.push_back( record );
								}


								if (!infile.eof())
								{
												//What to do here?
								} 
				}

				return 0; //TODO: activate return-statements for error-detection
}


/**
 * Helper function for generating the absolute value for the given 
 * fold change.
 * 
 * @param $first 
 * 		fold change to be converted to absolute score
 *    
 */


double degreeOfDeregulation(double fC)
{
				if (fC >= 0) {
								return fC;
				}
				else {
								return (double) -1*fC;
				}

}




Q_EXPORT_PLUGIN2(GraphAlgorithmServerHandler, GraphAlgorithmServerHandler)






