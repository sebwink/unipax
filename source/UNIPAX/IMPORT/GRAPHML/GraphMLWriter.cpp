// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                               UNIPAX 
// --------------------------------------------------------------------------
//  Copyright (C) 2011 -- Oliver Kohlbacher, Hans-Peter Lenhof
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 3 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
// $Id:$
// $Author:$
// $Maintainer:$
// --------------------------------------------------------------------------
//

#include <UNIPAX/IMPORT/GRAPHML/GraphMLWriter.h>
#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/next_prior.hpp>
#include <QtCore/QFile>
#include <QtXml/QXmlSimpleReader>

namespace UniPAX
{

				/*! \brief a standard constructor */
				GraphMLWriter::GraphMLWriter() : xmlfilename(""), debug(false)
				{
								init();
				}

				/*! \brief a standard constructor with filename parameter*/
				GraphMLWriter::GraphMLWriter(const std::string& filename) : debug(false)
				{
								xmlfilename=filename;
								init();
				}

				/*! \brief set file for reading*/
				bool GraphMLWriter::setFilename(const std::string& filename)
				{
								if (filename != "")
								{
												xmlfilename=filename;
												return true;
								}
								else
								{
												return false;
								}
				}

				/*! \brief a copy constructor */
				GraphMLWriter::GraphMLWriter(const GraphMLWriter& arg)  :
								debug(arg.debug),
								manager(arg.manager),
								xmlfilename(arg.xmlfilename),
								object_type(arg.object_type)
				{
				}

				/*! \brief destructor */
				GraphMLWriter::~GraphMLWriter()
				{
				}

				/*! \brief an assignment operator */
				GraphMLWriter& GraphMLWriter::operator=(const GraphMLWriter& arg)
				{
								debug = arg.debug;
								manager = arg.manager;
								xmlfilename = arg.xmlfilename;
								object_type = arg.object_type;

								return (*this);
				}

				void GraphMLWriter::init()
				{
								//	object_type["AlgebraicRule"] = "";
								//	object_type["AssignmentRule"] = "";
								//	object_type["BindingFeature"] = "";
								//	object_type["BioSource"] = "";
								//	object_type["BiochemicalPathwayStep"] = "";
								object_type["BiochemicalReaction"] = "INTERACTION";
								object_type["Catalysis"] = "INTERACTION";
								//	object_type["CellVocabulary"] = "";
								//	object_type["CellularLocationVocabulary"] = "";
								//	object_type["ChemicalStructure"] = "";
								object_type["Complex"] = "OBJECT";
								object_type["ComplexAssembly"] = "INTERACTION";
								//	object_type["Constraint"] = "";
								object_type["Control"] = "INTERACTION";
								//	object_type["ControlledVocabulary"] = "";
								object_type["Conversion"] = "INTERACTION";
								//	object_type["CovalentBindingFeature"] = "";
								object_type["Degradation"] = "INTERACTION";
								//	object_type["Delay"] = "";
								//	object_type["DeltaG"] = "";
								object_type["Dna"] = "OBJECT";
								object_type["DnaReference"] = "OBJECT";
								object_type["DnaRegion"] = "OBJECT";
								object_type["DnaRegionReference"] = "OBJECT";
								object_type["Entity"] = "OBJECT";
								//	object_type["EntityFeature"] = "";
								object_type["EntityReference"] = "OBJECT";
								//	object_type["EntityReferenceTypeVocabulary"] = "";
								object_type["Event"] = "INTERACTION";
								//	object_type["EventAssignment"] = "";
								//	object_type["Evidence"] = "";
								//	object_type["EvidenceCodeVocabulary"] = "";
								//	object_type["Experiment"] = "";
								//	object_type["ExperimentalForm"] = "";
								//	object_type["ExperimentalFormVocabulary"] = "";
								//	object_type["FragmentFeature"] = "";
								//	object_type["FunctionDefinition"] = "";
								object_type["Gene"] = "OBJECT";
								object_type["GeneticInteraction"] = "INTERACTION";
								//	object_type["ImportSource"] = "";
								//	object_type["InitialAssignment"] = "";
								object_type["Interaction"] = "INTERACTION";
								//	object_type["InteractionVocabulary"] = "";
								//	object_type["KPrime"] = "";
								//	object_type["KineticLaw"] = "";
								//	object_type["LocalParameter"] = "";
								//	object_type["Mapping"] = "";
								//	object_type["Math"] = "";
								//	object_type["Model"] = "";
								//	object_type["ModificationFeature"] = "";
								object_type["Modulation"] = "INTERACTION";
								object_type["MolecularInteraction"] = "INTERACTION";
								//	object_type["Parameter"] = "";
								object_type["Pathway"] = "OBJECT";
								//	object_type["PathwayStep"] = "";
								//	object_type["PhenotypeVocabulary"] = "";
								object_type["PhysicalEntity"] = "OBJECT";
								//	object_type["Priority"] = "";
								object_type["Protein"] = "OBJECT";
								object_type["ProteinReference"] = "OBJECT";
								//	object_type["Provenance"] = "";
								//	object_type["PublicationXref"] = "";
								//	object_type["RateRule"] = "";
								//	object_type["RelationshipTypeVocabulary"] = "";
								//	object_type["RelationshipXref"] = "";
								object_type["Rna"] = "OBJECT";
								object_type["RnaReference"] = "OBJECT";
								object_type["RnaRegion"] = "OBJECT";
								object_type["RnaRegionReference"] = "OBJECT";
								//	object_type["Rule"] = "";
								//	object_type["SBase"] = "";
								//	object_type["Sample"] = "";
								//	object_type["Score"] = "";
								//	object_type["SequenceInterval"] = "";
								//	object_type["SequenceLocation"] = "";
								//	object_type["SequenceModificationVocabulary"] = "";
								//	object_type["SequenceRegionVocabulary"] = "";
								//	object_type["SequenceSite"] = "";
								object_type["SmallMolecule"] = "OBJECT";
								object_type["SmallMoleculeReference"] = "OBJECT";
								//	object_type["Stoichiometry"] = "";
								object_type["TemplateReaction"] = "INTERACTION";
								object_type["TemplateReactionRegulation"] = "INTERACTION";
								//	object_type["Thing"] = "";
								//	object_type["TissueVocabulary"] = "";
								object_type["Transport"] = "INTERACTION";
								object_type["TransportWithBiochemicalReaction"] = "INTERACTION";
								//	object_type["Trigger"] = "";
								//	object_type["UPBase"] = "";
								//	object_type["UnificationXref"] = "";
								//	object_type["Unit"] = "";
								//	object_type["UnitDefinition"] = "";
								//	object_type["UtilityClass"] = "";
								//	object_type["Xref"] = "";

								return;
				}


				/*! \brief read file with filename */
				bool GraphMLWriter::write(const std::string& filename)
				{
								setFilename(filename);

								return write();
				}

				/*! \brief read file */
				bool GraphMLWriter::write()
				{

								//Parser is initialized with the file?
								if (xmlfilename!="")
								{

												QFile xmlFile( QString::fromStdString(xmlfilename) );

												if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text))
												{
																std::cerr << "Cannot open the file " << xmlfilename << std::endl;
																return false;
												}

												if (debug) std::cout << "Open the file " << xmlfilename << std::endl;

												QXmlStreamWriter out(&xmlFile);

												openDocument(out);
												writeHeader(out);

												write(out);

												writeFooter(out);
												closeDocument(out);

												if (debug) std::cout << "close file" << std::endl;
												xmlFile.close();
												return true;
								}
								else
								{
												std::cerr << "Please specify a file name" << std::endl;
												return false;
								}
				}

				void GraphMLWriter::openDocument(QXmlStreamWriter& out)
				{
								out.setCodec("UTF-8");
								out.setAutoFormatting(true);
								out.writeStartDocument();
				}

				void GraphMLWriter::writeHeader(QXmlStreamWriter& out)
				{
								// first write the graphml tag
								out.writeStartElement("graphml");
								out.writeAttribute("xmlns", "http://graphml.graphdrawing.org/xmlns");
								out.writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
								out.writeAttribute("xsi:schemaLocation", "http://graphml.graphdrawing.org/xmlns");

								// write label and type attributes to be used by the nodes
								out.writeStartElement("key");
								out.writeAttribute("id", "label");
								out.writeAttribute("for", "all");
								out.writeAttribute("attr.name", "label");
								out.writeAttribute("attr.type", "string");
								out.writeEndElement();
								out.writeStartElement("key");
								out.writeAttribute("id", "type");
								out.writeAttribute("for", "all");
								out.writeAttribute("attr.name", "type");
								out.writeAttribute("attr.type", "string");
								out.writeEndElement();
								out.writeStartElement("graph");
								out.writeAttribute("edgedefault", "undirected");

				}


				void GraphMLWriter::writeFooter(QXmlStreamWriter& out)
				{
								// close graph tag
								out.writeEndElement();
								// close graphml
								out.writeEndElement();
				}

				void GraphMLWriter::closeDocument(QXmlStreamWriter& out)
				{
								out.writeEndDocument();
				}

				bool GraphMLWriter::writePath(QXmlStreamWriter& out, std::vector<UnipaxId> ordered_path_nodes)
				{
								objectsToWrite = std::set<UnipaxId> (ordered_path_nodes.begin(), ordered_path_nodes.end());
								if (debug) std::cout << "fetch instances from persistence manager -> ";
								// fetch all known instances from the persistence manager
								std::map<std::string, std::string> data_type = manager.getIdToType();
								if (debug) std::cout << data_type.size() << std::endl;

								std::map<std::string, std::string>::iterator it;
								std::map<std::string, std::string>::iterator type_it;
								std::string current_id;
								std::string current_type;
								std::vector<std::pair<std::string,std::string> > attributes;
								std::vector<std::pair<std::string,std::string> >::iterator at_it;


								if (debug) std::cout << "writing nodes ... " << std::endl ;
								// go through all nodes of the path
								for (std::vector<UnipaxId>::const_iterator it = ordered_path_nodes.begin(); it != ordered_path_nodes.end(); it++)
								{
												current_id = boost::lexical_cast<std::string>(*it);
												std::map<std::string, std::string>::iterator type_it = data_type.find(current_id);
												if (type_it == data_type.end())
												{
																std::cerr << "GraphMLWriter::writePath: ID " << current_id << " from path not known to the persistence manager." << std::endl;
																return false;
												}
												current_type = type_it->second;

												attributes.clear();
												if (debug) std::cout << "write node for '" << current_type << "' , id '" << current_id << "' -> ";

												// write the instance
												out.writeStartElement("node");
												out.writeAttribute("id", QString::fromStdString(current_id));
												out.writeStartElement("data");
												out.writeAttribute("key", "type");
												out.writeCharacters(QString::fromStdString(object_type.find(current_type)->second));
												if (debug) std::cout << "type is " << object_type.find(current_type)->second << std::endl ;
												out.writeEndElement();

												out.writeStartElement("data");
												out.writeAttribute("key", "label");

												// fetch all attributes of the instance
												manager.getAttribute(current_id, attributes);
												for (at_it = attributes.begin(); at_it != attributes.end(); at_it++)
												{
																if (boost::iequals(at_it->first,"displayName"))
																{
																				if (debug) std::cout << "found displayName ... " << at_it->second << std::endl ;
																				out.writeCharacters(QString::fromStdString(at_it->second));
																				break;
																}
																else if (boost::iequals(at_it->first,"standardName"))
																{
																				if (debug) std::cout << "found standardName ... " << at_it->second << std::endl ;
																				out.writeCharacters(QString::fromStdString(at_it->second));
																				break;
																}
																else if (boost::iequals(at_it->first,"name"))
																{
																				if (debug) std::cout << "found name ... " << at_it->second << std::endl ;
																				out.writeCharacters(QString::fromStdString(at_it->second));
																				break;
																}
																else if (boost::iequals(at_it->first,"controlType"))
																{
																				if (debug) std::cout << "found controlType ... " << at_it->second << std::endl ;
																				out.writeCharacters(QString::fromStdString(at_it->second));
																				break;
																}
												}
												// close the data label instance
												out.writeEndElement();
												// close the node instance
												out.writeEndElement();

								}

								std::map<std::string, bool> edge_map;

								if (debug) std::cout << "writing edges ... " << std::endl ;
								// go through all nodes of the path
								for (std::vector<UnipaxId>::const_iterator it = ordered_path_nodes.begin(); it != ordered_path_nodes.end(); it++)
								{
												current_id = boost::lexical_cast<std::string>(*it);
												std::map<std::string, std::string>::iterator type_it = data_type.find(current_id);
												if (type_it == data_type.end())
												{
																std::cerr << "GraphMLWriter::writePath: ID " << current_id << " from path not known to the persistence manager." << std::endl;
																return false;
												}
												current_type = type_it->second;
												if (object_type[current_type] != "INTERACTION")
												{
																if (debug)
																				std::cout << current_type << " (" << current_id << ") is no interaction type ... continue" << std::endl;
																continue;
												}

												attributes.clear();
												if (debug) std::cout << "write edges for '" << current_type << "' , id '" << current_id << "' -> ";


												// fetch all attributes of the instance
												manager.getAttribute(current_id, attributes);
												for (at_it = attributes.begin(); at_it != attributes.end(); at_it++)
												{
																// check if attribute was object instance
																if (at_it->first[0] == '#')
																{
																				UnipaxId att_id = boost::lexical_cast<UnipaxId>(at_it->second);
																				// check if att_id is in the path
																				if (objectsToWrite.find(att_id) == objectsToWrite.end())
																				{
																								if (debug) std::cout << "attribute " << at_it->first << ": " << at_it->second << " is not in the path." << std::endl;
																								continue;
																				}
																				// check if att_id is neighbor of current
																				// if not - skip it!
																				if (it == ordered_path_nodes.begin()) // first in path
																				{
																								if(*boost::next(it) != att_id)
																								{
																												if (debug) std::cout << "attribute " << at_it->first << ": " << at_it->second << " jumped over from first position." << std::endl;
																												continue;
																								}
																				}
																				else if (boost::next(it) == ordered_path_nodes.end()) // last in path
																				{
																								if (*boost::prior(it) != att_id)
																								{
																												if (debug) std::cout << "attribute " << at_it->first << ": " << at_it->second << " jumped over from last position." << std::endl;
																												continue;
																								}
																				}
																				else if (*boost::prior(it) != att_id && *boost::next(it) != att_id) // inside path
																				{
																												if (debug) std::cout << "attribute " << at_it->first << ": " << at_it->second << " jumped over from inside position." << std::endl;
																								continue;
																				}

																				if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"controlled"))
																				{
																								if (edge_map.find(current_id+"|"+at_it->second) == edge_map.end())
																								{
																												edge_map[current_id+"|"+at_it->second] = true;
																												if (debug) std::cout << "found controlled ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("directed", "true");
																												out.writeAttribute("source", QString::fromStdString(current_id));
																												out.writeAttribute("target", QString::fromStdString(at_it->second));
																												out.writeEndElement();
																								}
																				}
																				else if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"controller"))
																				{
																								if (edge_map.find(at_it->second+"|"+current_id) == edge_map.end())
																								{
																												edge_map[at_it->second+"|"+current_id] = true;
																												if (debug) std::cout << "found controller ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("source", QString::fromStdString(at_it->second));
																												out.writeAttribute("target", QString::fromStdString(current_id));
																												out.writeEndElement();
																								}
																				}


																				else if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"right"))
																				{
																								if (edge_map.find(current_id+"|"+at_it->second) == edge_map.end())
																								{
																												edge_map[current_id+"|"+at_it->second] = true;
																												if (debug) std::cout << "found right ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("directed", "true");
																												out.writeAttribute("source", QString::fromStdString(current_id));
																												out.writeAttribute("target", QString::fromStdString(at_it->second));
																												out.writeEndElement();
																								}
																				}
																				else if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"left"))
																				{
																								if (edge_map.find(at_it->second+"|"+current_id) == edge_map.end())
																								{
																												edge_map[at_it->second+"|"+current_id] = true;
																												if (debug) std::cout << "found left ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("source", QString::fromStdString(at_it->second));
																												out.writeAttribute("target", QString::fromStdString(current_id));
																												out.writeEndElement();
																								}
																				}


																				else if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"participant"))
																				{
																								if (edge_map.find(at_it->second+"|"+current_id) == edge_map.end())
																								{
																												edge_map[at_it->second+"|"+current_id] = true;
																												if (debug) std::cout << "found participant ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("source", QString::fromStdString(at_it->second));
																												out.writeAttribute("target", QString::fromStdString(current_id));
																												out.writeEndElement();
																								}
																				}

																				else if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"Product"))
																				{
																								if (edge_map.find(at_it->second+"|"+current_id) == edge_map.end())
																								{
																												edge_map[at_it->second+"|"+current_id] = true;
																												if (debug) std::cout << "found Product ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("source", QString::fromStdString(at_it->second));
																												out.writeAttribute("target", QString::fromStdString(current_id));
																												out.writeEndElement();
																								}
																				}
																}
												}
								}
								return true;
				}

				/*! \brief read file */
				bool GraphMLWriter::write(QXmlStreamWriter& out)
				{
								if (debug) std::cout << "fetch instances from persistence manager -> ";
								// fetch all known instances from the persistence manager
								std::map<std::string, std::string> data_type = manager.getIdToType();
								if (debug) std::cout << data_type.size() << std::endl;

								std::map<std::string, std::string>::iterator it;
								std::map<std::string, std::string>::iterator type_it;
								std::string current_id;
								std::string current_type;
								std::vector<std::pair<std::string,std::string> > attributes;
								std::vector<std::pair<std::string,std::string> >::iterator at_it;


								if (debug) std::cout << "writing nodes ... " << std::endl ;
								// go through all instances known by the persistence manager
								for (it = data_type.begin(); it != data_type.end(); it++)
								{
												current_id = it->first;
												if (!objectsToWrite.empty())
												{
																if (objectsToWrite.find(boost::lexical_cast<UnipaxId>(current_id)) == objectsToWrite.end())
																{
																				continue;
																}
												}
												current_type = it->second;


												if (object_type.find(current_type) == object_type.end())
												{
																if (debug)
																				std::cout << current_type << " (" << current_id << ") found ... continue" << std::endl;
																continue;
												}

												attributes.clear();
												if (debug) std::cout << "write node for '" << current_type << "' , id '" << current_id << "' -> ";

												// write the instance
												out.writeStartElement("node");
												out.writeAttribute("id", QString::fromStdString(current_id));
												out.writeStartElement("data");
												out.writeAttribute("key", "type");
												out.writeCharacters(QString::fromStdString(object_type.find(current_type)->second));
												if (debug) std::cout << "type is " << object_type.find(current_type)->second << std::endl ;
												out.writeEndElement();

												out.writeStartElement("data");
												out.writeAttribute("key", "label");

												// fetch all attributes of the instance
												manager.getAttribute(current_id, attributes);
												for (at_it = attributes.begin(); at_it != attributes.end(); at_it++)
												{
																if (boost::iequals(at_it->first,"displayName"))
																{
																				if (debug) std::cout << "found displayName ... " << at_it->second << std::endl ;
																				out.writeCharacters(QString::fromStdString(at_it->second));
																				break;
																}
																else if (boost::iequals(at_it->first,"standardName"))
																{
																				if (debug) std::cout << "found standardName ... " << at_it->second << std::endl ;
																				out.writeCharacters(QString::fromStdString(at_it->second));
																				break;
																}
																else if (boost::iequals(at_it->first,"name"))
																{
																				if (debug) std::cout << "found name ... " << at_it->second << std::endl ;
																				out.writeCharacters(QString::fromStdString(at_it->second));
																				break;
																}
																else if (boost::iequals(at_it->first,"controlType"))
																{
																				if (debug) std::cout << "found controlType ... " << at_it->second << std::endl ;
																				out.writeCharacters(QString::fromStdString(at_it->second));
																				break;
																}
												}
												// close the data label instance
												out.writeEndElement();
												// close the node instance
												out.writeEndElement();

								}


								std::map<std::string, bool> edge_map;

								if (debug) std::cout << "writing edges ... " << std::endl ;
								// go through all instances known by the persistence manager
								for (it = data_type.begin(); it != data_type.end(); it++)
								{
												current_id = it->first;
												if (!objectsToWrite.empty())
												{
																if (objectsToWrite.find(boost::lexical_cast<UnipaxId>(current_id)) == objectsToWrite.end())
																{
																				continue;
																}
												}
												current_type = it->second;

												if (object_type.find(current_type) == object_type.end())
												{
																if (debug)
																				std::cout << current_type << " (" << current_id << ") found ... continue" << std::endl;
																continue;
												}


												if (object_type[current_type] != "INTERACTION")
												{
																if (debug)
																				std::cout << current_type << " (" << current_id << ") is no interaction type ... continue" << std::endl;
																continue;
												}

												attributes.clear();
												if (debug) std::cout << "write edges for '" << current_type << "' , id '" << current_id << "' -> ";


												// fetch all attributes of the instance
												manager.getAttribute(current_id, attributes);
												for (at_it = attributes.begin(); at_it != attributes.end(); at_it++)
												{
																// check if attribute was object instance
																if (at_it->first[0] == '#')
																{
																				if (!objectsToWrite.empty())
																				{
																								if (objectsToWrite.find(boost::lexical_cast<UnipaxId>(at_it->second)) == objectsToWrite.end())
																								{
																												continue;
																								}
																				}
																				if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"controlled"))
																				{
																								if (edge_map.find(current_id+"|"+at_it->second) == edge_map.end())
																								{
																												edge_map[current_id+"|"+at_it->second] = true;
																												if (debug) std::cout << "found controlled ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("directed", "true");
																												out.writeAttribute("source", QString::fromStdString(current_id));
																												out.writeAttribute("target", QString::fromStdString(at_it->second));
																												out.writeEndElement();
																								}
																				}
																				else if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"controller"))
																				{
																								if (edge_map.find(at_it->second+"|"+current_id) == edge_map.end())
																								{
																												edge_map[at_it->second+"|"+current_id] = true;
																												if (debug) std::cout << "found controller ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("source", QString::fromStdString(at_it->second));
																												out.writeAttribute("target", QString::fromStdString(current_id));
																												out.writeEndElement();
																								}
																				}


																				else if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"right"))
																				{
																								if (edge_map.find(current_id+"|"+at_it->second) == edge_map.end())
																								{
																												edge_map[current_id+"|"+at_it->second] = true;
																												if (debug) std::cout << "found right ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("directed", "true");
																												out.writeAttribute("source", QString::fromStdString(current_id));
																												out.writeAttribute("target", QString::fromStdString(at_it->second));
																												out.writeEndElement();
																								}
																				}
																				else if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"left"))
																				{
																								if (edge_map.find(at_it->second+"|"+current_id) == edge_map.end())
																								{
																												edge_map[at_it->second+"|"+current_id] = true;
																												if (debug) std::cout << "found left ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("source", QString::fromStdString(at_it->second));
																												out.writeAttribute("target", QString::fromStdString(current_id));
																												out.writeEndElement();
																								}
																				}


																				else if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"participant"))
																				{
																								if (edge_map.find(at_it->second+"|"+current_id) == edge_map.end())
																								{
																												edge_map[at_it->second+"|"+current_id] = true;
																												if (debug) std::cout << "found participant ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("source", QString::fromStdString(at_it->second));
																												out.writeAttribute("target", QString::fromStdString(current_id));
																												out.writeEndElement();
																								}
																				}

																				else if (boost::iequals(at_it->first.substr(1,at_it->first.length()-1),"Product"))
																				{
																								if (edge_map.find(at_it->second+"|"+current_id) == edge_map.end())
																								{
																												edge_map[at_it->second+"|"+current_id] = true;
																												if (debug) std::cout << "found Product ... " << at_it->second << std::endl ;
																												out.writeStartElement("edge");
																												out.writeAttribute("source", QString::fromStdString(at_it->second));
																												out.writeAttribute("target", QString::fromStdString(current_id));
																												out.writeEndElement();
																								}
																				}

																}

																//			if (boost::iequals(at_it->first,"controlType"))
																//			{
																//				if (debug) std::cout << "found controlType ... " << at_it->second << std::endl ;
																//				out.writeStartElement("data");
																//				out.writeAttribute("key", "label");
																//				out.writeCharacters(QString::fromStdString(at_it->second));
																//				out.writeEndElement();
																//				break;
																//			}
												}

								}

								return true;

				}

				void GraphMLWriter::restrictToObjects(std::set<UnipaxId> toWrite)
				{
								objectsToWrite = toWrite;
				}


				void GraphMLWriter::setDebug(bool _debug)
				{
								debug = _debug;
				}


				void GraphMLWriter::setPersistenceManager(PersistenceManager& _manager)
				{
								manager = _manager;
				}


} // namespace
