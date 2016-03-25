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

#include <UNIPAX/IMPORT/SBML/SBMLReader.h>
#include <sbml/SBMLDocument.h>
#include <iostream>
#include <sstream>
//#include <QtCore/QFile>
#include <QtXml/QXmlSimpleReader>
#include <QtXml/QXmlDefaultHandler>
#include <Qt/QtCore>


namespace UniPAX
{

/*! \brief a standard constructor */
SBMLReader::SBMLReader() : xmlfilename(""), debug(0), objects_only(0), configHandler(), object_counter(0), miriamLink(0)
{
}

/*! \brief a standard constructor with filename parameter*/
SBMLReader::SBMLReader(const std::string& filename) : xmlfilename(filename), debug(0), objects_only(0), configHandler(), object_counter(0), miriamLink(0)
{
}

/*! \brief a copy constructor */
SBMLReader::SBMLReader(const SBMLReader& to_copy): xmlfilename(to_copy.xmlfilename), configHandler(to_copy.configHandler), debug(0), objects_only(0)
{
}

/*! \brief destructor */
SBMLReader::~SBMLReader()
{
	if (miriamLink != 0)
	{
		delete miriamLink;
	}
}


/*! \brief an assignment operator */
SBMLReader& SBMLReader::operator=(const SBMLReader& assign)
{
	xmlfilename = assign.xmlfilename;
	configHandler = assign.configHandler;
	debug = assign.debug;
	objects_only = assign.objects_only;

	return (*this);
}

// initialize before use of reader
bool SBMLReader::init(std::string proxy_host, int proxy_port, std::string config_file_path)
{
	if (miriamLink == 0)
	{
		miriamLink = new UniPAX::MiriamLink();
	}
	miriamLink->setProxy(proxy_host, proxy_port);
	configHandler.setMiriamLink(miriamLink);
	if(!parseConfigFile(config_file_path))
	{
		std::cerr << "SBMLReader not initialized." << std::endl;
	}
	else
	{
		std::cout << "SBMLReader initialized." << std::endl;
	}

	return false;
}

/*! \brief set file for reading*/
bool SBMLReader::setFilename(const std::string& filename)
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

/*! \brief read file with filename */
bool SBMLReader::parse(const std::string& filename)
{
	if (setFilename(filename))
	{
		return parse();
	}
	else
		return false;
}

/*! \brief Read mapping configuration file */
bool SBMLReader::parseConfigFile(std::string mapping_filename)
{

	//configHandler = SBMLConfigHandler();

	QXmlSimpleReader reader;
	reader.setContentHandler( &configHandler );
	reader.setErrorHandler( &configHandler );

	QFile xmlFile( QString( mapping_filename.c_str() ) );
	if (!xmlFile.exists())
	{
		std::cerr << "Could not find file: " << xmlFile.fileName().toStdString() << std::endl;
	}
	if (debug)
	{
		std::cout << "Found file: " << xmlFile.fileName().toStdString() << std::endl;
	}
	QXmlInputSource source( &xmlFile );
	if (debug)
	{
		std::cout << "QXmlInputSource set. Starting parse of config file." << std::endl;
	}

	if (!reader.parse( source ))
	{
		std::cerr << "Parsing of mapping configuration file failed." << std::endl;
		std::cerr << "File location: " << mapping_filename << std::endl;
		return false;
	}
	return true;

}

/*! \brief read file */
bool SBMLReader::parse()
{

	// Parser is initialized with the file?
	if (xmlfilename!="")
	{

		libsbml::SBMLDocument* document = libsbml::readSBMLFromFile(xmlfilename.c_str());
		if (document->getNumErrors() > 0) {
			std::cerr << "During parse the following errors occured:" << std::endl;
			document->printErrors(std::cerr);
			return false;
		}
		// Give some details about the read SBML file
		std::cout << "Read SBML file without errors.\n"
				<< "Document type: SBML level "
				<< document->getLevel()
				<< " version "
				<< document->getVersion()
				<< std::endl;
		// Check if read file is compatible with L3v1
		if (document->checkL3v1Compatibility() != 0) {
			std::cout << "Document is not compatible with SBML level 3 version 1. Aborting ..." << std::endl;
			return false;
		}
		return mapToUniPAX(document, manager);
	}
	else
		return false;
}


bool SBMLReader::mapToUniPAX(libsbml::SBMLDocument* document, UniPAX::PersistenceManager& manager) {
	if (document->checkL3v1Compatibility() == 0) {
		// mapping
		libsbml::Model* model = document->getModel();
		// map sbml::Model attributes
		if (model == 0)
		{
			std::cerr << "document->getModel() returned a null pointer." << std::endl;
			return false;
		}

		if (debug)
		{
			std::cout << "model->getId(): " << model->getId() << std::endl;
			std::cout << "model->getName(): " << model->getName() << std::endl;
			std::cout << "model->getSubstanceUnits(): " <<  model->getSubstanceUnits() << std::endl;
			std::cout << "model->getTimeUnits(): " << model->getTimeUnits() << std::endl;
			std::cout << "model->getVolumeUnits(): " << model->getVolumeUnits() << std::endl;
			std::cout << "model->getAreaUnits(): " << model->getAreaUnits() << std::endl;
			std::cout << "model->getLengthUnits(): " << model->getLengthUnits() << std::endl;
			std::cout << "model->getExtentUnits(): " << model->getExtentUnits() << std::endl;
			std::cout << "model->getConversionFactor(): " << model->getConversionFactor() << std::endl;
		}
		std::stringstream model_id;
		if(model->isSetId())
		{
			model_id << "SBMLMODEL_" << model->getId();
		}
		else if (model->isSetName())
		{
			model_id << "SBMLMODEL_" << model->getName();
		}
		else
		{
			model_id << "SBMLMODEL_NO_ID";
		}
		bool created;

		boost::shared_ptr<UniPAX::Pathway>  pathway = manager.createInstance<UniPAX::Pathway>(createId(model_id.str()), created);
		if(!created)
		{
			std::cerr << "Could not create Pathway object. Aborting parse." << std::endl;
			return false;
		}
		// attributes from SBML::Model
		model_id << "_EXT";
		boost::shared_ptr<UniPAX::Model>  modelExtension = manager.createInstance<UniPAX::Model>(createId(model_id.str()),created);
		if(!created)
		{
			std::cerr << "Could not create Model object. Aborting parse." << std::endl;
			return false;
		}
		pathway->addModelExtension(modelExtension);
		// attributes inherited from SBML::SBase
		std::string content = model->getMetaId();
		if (!content.empty())
			modelExtension->setMetaId(content);
		content = model->getSBOTermID();
		if (!content.empty())
			modelExtension->setSboTerm(content);
		content = model->getNotesString();
		if (!content.empty())
			modelExtension->setNotes(content);
		content = model->getAnnotationString();
		if (!content.empty())
			modelExtension->setAnnotation(content);
		//
		content = model->getId();
		if (!content.empty())
			modelExtension->setId(content);
		content = model->getName();
		if (!content.empty())
			modelExtension->setName(content);
		content = model->getSubstanceUnits();
		if (!content.empty())
			modelExtension->setSubstanceUnits(content);
		content = model->getTimeUnits();
		if (!content.empty())
			modelExtension->setTimeUnits(content);
		content = model->getVolumeUnits();
		if (!content.empty())
			modelExtension->setVolumeUnits(content);
		content = model->getAreaUnits();
		if (!content.empty())
			modelExtension->setAreaUnits(content);
		content = model->getLengthUnits();
		if (!content.empty())
			modelExtension->setLengthUnits(content);
		content = model->getExtentUnits();
		if (!content.empty())
			modelExtension->setExtentUnit(content);
		content = model->getConversionFactor();
		if (!content.empty())
			modelExtension->setConversionFactor(content);

		//	map ListOfFunctionDefinitions
		if(model->getListOfFunctionDefinitions() != 0)
		{
			if (debug)
			{
				std::cout << "ListOfFunctionDefinitions:" << std::endl;
			}
			for (int i=0; i < model->getListOfFunctionDefinitions()->size(); i++)
			{
				if (debug)
					std::cout << i << ". FunctionDefinition: " << model->getListOfFunctionDefinitions()->get(i)->getName() << std::endl;
				boost::shared_ptr<UniPAX::FunctionDefinition>  fd = manager.createInstance<UniPAX::FunctionDefinition>(createId(model->getListOfFunctionDefinitions()->get(i)->getId()), created);
				if (!created)
				{
					std::cerr << "Could not create FunctionDefinition object. Aborting parse." << std::endl;
					return false;
				}

				fd->setId(model->getListOfFunctionDefinitions()->get(i)->getId());
				if (!!model->getListOfFunctionDefinitions()->get(i)->getName().empty())
					fd->setName(model->getListOfFunctionDefinitions()->get(i)->getName());
				//fd->setPathway(pathway);

				fd->setMath(manager.createInstance<UniPAX::Math>(createId(model->getListOfFunctionDefinitions()->get(i)->getId() + "_MATH"), created));
				if (!created)
				{
					std::cerr << "Could not create Math object. Aborting parse." << std::endl;
					return false;
				}
				fd->getMath()->setMathML(model->getListOfFunctionDefinitions()->get(i)->getMath()->getName());

				modelExtension->addFunctionDefinition(fd);
			}
		}

		//  map ListOfUnitDefinitions
		if(model->getListOfUnitDefinitions() != 0)
		{
			if (debug)
				std::cout << "ListOfUnitDefinitions:" << std::endl;

			for (int i=0; i < model->getListOfUnitDefinitions()->size(); i++)
			{
				if (debug)
					std::cout << i << ". UnitDefinition: " << model->getListOfUnitDefinitions()->get(i)->getName() << std::endl;
				boost::shared_ptr<UniPAX::UnitDefinition>  ud = manager.createInstance<UniPAX::UnitDefinition>(createId(model->getListOfUnitDefinitions()->get(i)->getId()), created);
				if (!created)
				{
					std::cerr << "Could not create UnitDefinition object. Aborting parse." << std::endl;
					return false;
				}
				ud->setId(model->getListOfUnitDefinitions()->get(i)->getId());
				if (!model->getListOfUnitDefinitions()->get(i)->getName().empty())
					ud->setName(model->getListOfUnitDefinitions()->get(i)->getName());
				//ud->setPathway(pathway);
				std::stringstream unit_id;
				for (int j=0; j < model->getListOfUnitDefinitions()->get(i)->getListOfUnits()->size(); j++)
				{
					unit_id.str(std::string());
					unit_id << model->getListOfUnitDefinitions()->get(i)->getId() << "_unit_" << j;
					ud->addUnit(manager.createInstance<UniPAX::Unit>(createId(unit_id.str()), created));
					if (!created)
					{
						std::cerr << "Could not create Unit object. Aborting parse. " << std::endl;
						return false;
					}
					ud->getUnits().back()->setExponent(model->getListOfUnitDefinitions()->get(i)->getListOfUnits()->get(j)->getExponent());
					ud->getUnits().back()->setKind(UnitKind_toString(model->getListOfUnitDefinitions()->get(i)->getListOfUnits()->get(j)->getKind()));
					ud->getUnits().back()->setMultiplier(model->getListOfUnitDefinitions()->get(i)->getListOfUnits()->get(j)->getMultiplier());
					ud->getUnits().back()->setScale(model->getListOfUnitDefinitions()->get(i)->getListOfUnits()->get(j)->getScale());
					ud->getUnits().back()->setUnitDefinition(ud);
				}
				modelExtension->addUnitDefinition(ud);
			}
		}
		// map ListOfParameters
		if(model->getListOfParameters() != 0)
		{
			if (debug)
				std::cout << "ListOfParameters:" << std::endl;
			for (int i=0; i < model->getListOfParameters()->size(); i++)
			{
				if (debug)
					std::cout << i << ". Parameter: " << model->getListOfParameters()->get(i)->getMetaId() << std::endl;
				boost::shared_ptr<UniPAX::Parameter>  pa = manager.createInstance<UniPAX::Parameter>(createId(model->getListOfParameters()->get(i)->getId()), created);
				if (!created)
				{
					std::cerr << "Could not create Parameter object. Aborting parse." << std::endl;
					return false;
				}
				pa->setId(model->getListOfParameters()->get(i)->getId());
				if (!model->getListOfParameters()->get(i)->getName().empty())
					pa->setName(model->getListOfParameters()->get(i)->getName());
				if (model->getListOfParameters()->get(i)->getValue() != 0)
					pa->setValue(model->getListOfParameters()->get(i)->getValue());
				if (model->getListOfParameters()->get(i)->isSetUnits())
					pa->setUnits(model->getListOfParameters()->get(i)->getUnits());
				pa->setConstant(model->getListOfParameters()->get(i)->getConstant());
				//pa->setPathway(pathway);
				modelExtension->addParameter(pa);
			}
		}
		// map ListOfInitialAssignments
		if(model->getListOfInitialAssignments() != 0)
		{
			if (debug)
				std::cout << "ListOfInitialAssignments:" << std::endl;
			std::stringstream initialAssignment_id;
			for (int i=0; i < model->getListOfInitialAssignments()->size(); i++)
			{
				if (debug)
					std::cout << i << ". Assignment: " << model->getListOfParameters()->get(i)->getMetaId() << std::endl;
				initialAssignment_id.str(std::string());
				initialAssignment_id << "INITIAL_ASSIGNMENT_" << i;
				boost::shared_ptr<UniPAX::InitialAssignment>  ia =  manager.createInstance<UniPAX::InitialAssignment>(createId(initialAssignment_id.str()), created);
				if (!created)
				{
					std::cerr << "Could not create InitialAssignment object. Aborting parse." << std::endl;
					return false;
				}
				ia->setSymbol(model->getListOfInitialAssignments()->get(i)->getSymbol());
				initialAssignment_id << "_MATH";
				ia->setMath(manager.createInstance<UniPAX::Math>(createId(initialAssignment_id.str()), created));
				if (!created)
				{
					std::cerr << "Could not create Math object. Aborting parse." << std::endl;
					return false;
				}
				ia->getMath()->setMathML(model->getListOfInitialAssignments()->get(i)->getMath()->getName());

				modelExtension->addInitialAssignment(ia);
			}
		}
		// map ListOfRules
		if(model->getListOfRules() != 0)
		{
			if (debug)
				std::cout << "ListOfRules:" << std::endl;
			for (int i=0; i < model->getListOfRules()->size(); ++i)
			{
				if (debug)
					std::cout << i << ". Rule: " << model->getListOfRules()->get(i)->getMetaId() << std::endl;
				boost::shared_ptr<UniPAX::Rule>  ru;
				std::stringstream rule_id;
				rule_id << "RULE_" << i;
				if (model->getListOfRules()->get(i)->isAlgebraic())
				{
					ru = manager.createInstance<UniPAX::AlgebraicRule>(createId(rule_id.str()), created);
					if (!created)
					{
						std::cerr << "Could not create AlgebraicRule object. Aborting parse." << std::endl;
						return false;
					}
					// AlgebraicRule has no special Attributes
				} else if (model->getListOfRules()->get(i)->isAssignment())
				{
					ru = manager.createInstance<UniPAX::AssignmentRule>(createId(rule_id.str()), created);
					if (!created)
					{
						std::cerr << "Could not create AssignmentRule object. Aborting parse." << std::endl;
						return false;
					}
					boost::dynamic_pointer_cast<UniPAX::AssignmentRule> (ru)->setVariable(model->getListOfRules()->get(i)->getVariable());
				} else if (model->getListOfRules()->get(i)->isRate())
				{
					ru = manager.createInstance<UniPAX::RateRule>(createId(rule_id.str()), created);
					if (!created)
					{
						std::cerr << "Could not create RateRule object. Aborting parse." << std::endl;
						return false;
					}
					boost::dynamic_pointer_cast<UniPAX::RateRule>(ru)->setVariable(model->getListOfRules()->get(i)->getVariable());

				}
				// add math
				rule_id << "_MATH";
				ru->setMath(manager.createInstance<UniPAX::Math>(createId(rule_id.str()), created));
				if (!created)
				{
					std::cerr << "Could not create Math object. Aborting parse." << std::endl;
					return false;
				}
				ru->getMath()->setMathML(model->getListOfRules()->get(i)->getMath()->getName());
				modelExtension->addRule(ru);
			}
		}
		// map ListOfConstraints
		if(model->getListOfConstraints() != 0)
		{
			if (debug)
				std::cout << "ListOfConstraints:" << std::endl;
			for (int i=0; i < model->getListOfConstraints()->size(); i++)
			{
				if (debug)
					std::cout << i << ". Constraint: " << model->getListOfConstraints()->get(i)->getMetaId() << std::endl;
				std::stringstream constraint_id;
				constraint_id << "CONSTRAINT_" << i;
				boost::shared_ptr<UniPAX::Constraint>  co = manager.createInstance<UniPAX::Constraint>(createId(constraint_id.str()), created);
				if (!created)
				{
					std::cerr << "Could not create Constraint object. Aborting parse." << std::endl;
					return false;
				}
				if (model->getListOfConstraints()->get(i)->getMessage() != 0)
					co->setMessage(model->getListOfConstraints()->get(i)->getMessageString());
				constraint_id << "_MATH";
				co->setMath(manager.createInstance<UniPAX::Math>(createId(constraint_id.str()), created));
				if (!created)
				{
					std::cerr << "Could not create Math object. Aborting parse." << std::endl;
					return false;
				}
				co->getMath()->setMathML(model->getListOfConstraints()->get(i)->getMath()->getName());

				modelExtension->addConstraint(co);
			}
		}
		// map ListOfEvents
		{
			if (debug)
				std::cout << "ListOfEvents:" << std::endl;
			for (int i=0; i < model->getListOfEvents()->size(); i++)
			{
				if (debug)
					std::cout << i << ". Event: " << model->getListOfEvents()->get(i)->getMetaId() << std::endl;
				std::stringstream event_id;
				event_id << "EVENT_" << i;
				boost::shared_ptr<UniPAX::Event>  ev = manager.createInstance<UniPAX::Event>(createId(event_id.str()), created);
				if (!created)
				{
					std::cerr << "Could not create Event object. Aborting parse." << std::endl;
					return false;
				}
				// base attributes
				ev->setUseValuesFromTriggerTime(model->getListOfEvents()->get(i)->getUseValuesFromTriggerTime());
				if (model->getListOfEvents()->get(i)->isSetId())
				{
					ev->setId(model->getListOfEvents()->get(i)->getId());
				}
				if (model->getListOfEvents()->get(i)->isSetName())
				{
					ev->setName(model->getListOfEvents()->get(i)->getName());
				}
				// trigger object
				std::stringstream trigger_id(event_id.str());
				trigger_id << "_TRIGGER";
				boost::shared_ptr<UniPAX::Trigger>  tr = manager.createInstance<UniPAX::Trigger>(createId(trigger_id.str()), created);
				if (!created)
				{
					std::cerr << "Could not create Trigger object. Aborting parse." << std::endl;
					return false;
				}
				// trigger attributes
				tr->setInitialValue(model->getListOfEvents()->get(i)->getTrigger()->getInitialValue());
				tr->setPersistent(model->getListOfEvents()->get(i)->getTrigger()->getPersistent());
				trigger_id << "_MATH";
				tr->setMath(manager.createInstance<UniPAX::Math>(createId(trigger_id.str()), created));
				if (!created)
				{
					std::cerr << "Could not create Math object. Aborting parse." << std::endl;
					return false;
				}
				tr->getMath()->setMathML(model->getListOfEvents()->get(i)->getTrigger()->getMath()->getName());
				ev->setTrigger(tr);

				// priority
				if (model->getListOfEvents()->get(i)->isSetPriority())
				{
					trigger_id.str(event_id.str());
					trigger_id << "_PRIORITY";
					boost::shared_ptr<UniPAX::Priority>  pr = manager.createInstance<UniPAX::Priority>(createId(trigger_id.str()), created);
					if (!created)
					{
						std::cerr << "Could not create Priority object. Aborting parse." << std::endl;
						return false;
					}
					trigger_id << "_MATH";
					// priority attributes
					pr->setMath(manager.createInstance<UniPAX::Math>(createId(trigger_id.str()), created));
					if (!created)
					{
						std::cerr << "Could not create Math object. Aborting parse." << std::endl;
						return false;
					}
					pr->getMath()->setMathML(model->getListOfEvents()->get(i)->getPriority()->getMath()->getName());
					ev->setPriority(pr);
				}
				// delay
				if (model->getListOfEvents()->get(i)->isSetDelay())
				{
					trigger_id.str(event_id.str());
					trigger_id << "_DELAY";
					boost::shared_ptr<UniPAX::Delay>  dy = manager.createInstance<UniPAX::Delay>(createId(trigger_id.str()), created);
					if (!created)
					{
						std::cerr << "Could not create Delay object. Aborting parse." << std::endl;
						return false;
					}
					// Delay attributes
					trigger_id << "_MATH";
					dy->setMath(manager.createInstance<UniPAX::Math>(createId(trigger_id.str()), created));
					if (!created)
					{
						std::cerr << "Could not create Math object. Aborting parse." << std::endl;
						return false;
					}
					dy->getMath()->setMathML(model->getListOfEvents()->get(i)->getPriority()->getMath()->getName());
					ev->setDelay(dy);
				}
				// EventAssignments
				for (int j=0; j < model->getListOfEvents()->get(i)->getListOfEventAssignments()->size(); j++)
				{
					trigger_id.str(event_id.str());
					trigger_id << "_EVENTASSIGNMENT_" << j;
					boost::shared_ptr<UniPAX::EventAssignment>  ea = manager.createInstance<UniPAX::EventAssignment>(createId(trigger_id.str()), created);
					if (!created)
					{
						std::cerr << "Could not create EventAssignment object. Aborting parse." << std::endl;
						return false;
					}
					trigger_id << "_MATH";
					ea->setMath(manager.createInstance<UniPAX::Math>(createId(trigger_id.str()), created));
					if (!created)
					{
						std::cerr << "Could not create Math object. Aborting parse." << std::endl;
						return false;
					}
					ea->getMath()->setMathML(model->getListOfEvents()->get(i)->getListOfEventAssignments()->get(j)->getMath()->getName());
					ev->addEventAssignment(ea);
				}

				modelExtension->addEvent(ev);
			}

		}

		// map ListOfCompartments
		if(model->getListOfCompartments() != 0)
		{
			if (debug)
				std::cout << "ListOfCompartments:" << std::endl;
			for (int i = 0; i < model->getListOfCompartments()->size(); i++)
			{
				if (debug)
					std::cout << i << ". Compartment: " << model->getListOfCompartments()->get(i)->getMetaId() << std::endl;
				boost::shared_ptr<UniPAX::CellularLocationVocabulary>  cv = manager.createInstance<UniPAX::CellularLocationVocabulary>(createId(model->getListOfCompartments()->get(i)->getId()), created);
				if (!created)
				{
					std::cerr << "Could not create CellularLocationVocabulary object. Aborting parse." << std::endl;
					return false;
				}
				if (model->getListOfCompartments()->get(i)->isSetName())
				{
					cv->setTerm(model->getListOfCompartments()->get(i)->getName());
				}
				else
				{
					cv->setTerm(model->getListOfCompartments()->get(i)->getId());
				}
				// Compartment annotation
				if (model->getListOfCompartments()->get(i)->isSetAnnotation())
				{
					if (debug)
					{
						std::cout << "Found annotation for compartment: " << model->getListOfCompartments()->get(i)->getAnnotationString() << std::endl;
					}

					std::vector<std::string> annotations;
					if (!model->getListOfCompartments()->get(i)->getAnnotationString().empty())
					{
						annotations = parseURIs(model->getListOfCompartments()->get(i)->getAnnotationString());
					}
					std::vector<std::string>::iterator it = annotations.begin();
					while ( it != annotations.end() )
					{
						if (debug)
						{
							std::cout << "Annotation: " << *it << std::endl;

						}
						std::pair<std::string, std::string> miriam = parseMiriamAnnotation(*it);
						std::string xref_id = createId(miriam.second + "_" + miriam.first); // id = <DB>_<Identifier>
						boost::shared_ptr<UniPAX::Xref>  xref = boost::dynamic_pointer_cast<UniPAX::Xref>(manager.getInstance(xref_id, manager.getInstanceType(xref_id)));
						if (xref != 0)
						{ // annotation already there
						}
						else
						{ // new annotation
							xref = manager.createInstance<UniPAX::UnificationXref>(xref_id, created);
							if (!created)
							{
								std::cerr << "Could not create UnificationXref object. Aborting parse." << std::endl;
								return false;
							}
							xref->setId(model->getListOfCompartments()->get(i)->getId() + "_" + miriam.first);
							xref->setDb(miriam.second);
						}
						cv->addXref(xref);
						it++;
					}

				}
			}
		}
		// map ListOfSpecies
		std::vector<std::string> speciesAnnotationNameDBList; // list of databases URI
		std::vector<std::string> speciesAnnotationIdentifierList; // list of ressource identifier
		{
			if (debug)
				std::cout << "ListOfSpecies:" << std::endl;
			for (int i=0; i < model->getListOfSpecies()->size(); i++)
			{
				if (debug)
					std::cout << i << ". Species: " << model->getListOfSpecies()->get(i)->getMetaId() << std::endl;
				std::string physicalEntityType = "";
				boost::shared_ptr<UniPAX::PhysicalEntity>  entity;
				bool isaComplex = false;
				speciesAnnotationNameDBList.clear();
				speciesAnnotationIdentifierList.clear();
				// if species has Annotations use them for improved mapping
				if (model->getListOfSpecies()->get(i)->isSetAnnotation())
				{
					if (debug)
					{
						std::cout << "Found annotation for Species: " << model->getListOfSpecies()->get(i)->getAnnotationString() << std::endl;
					}
					if (model->getListOfSpecies()->get(i)->getAnnotationString().find("bqbiol:hasPart") != -1)
					{
						if (debug) std::cout << "Species is a Complex!" << std::endl;
						isaComplex = true;
						physicalEntityType = "Complex";
					}

					std::vector<std::string> annotations;
					if (!model->getListOfSpecies()->get(i)->getAnnotationString().empty())
					{
						annotations = parseURIs(model->getListOfSpecies()->get(i)->getAnnotationString());
					}
					std::vector<std::string>::iterator it = annotations.begin();
					while ( it != annotations.end() )
					{
						std::pair<std::string, std::string> miriam = parseMiriamAnnotation(*it);
						std::string annotationDB = miriam.second;
						std::string annotationIdentifier = miriam.first;


						if (configHandler.getAnnotationSpecies().find(annotationDB) != configHandler.getAnnotationSpecies().end())
						{
							speciesAnnotationNameDBList.push_back(annotationDB);
							speciesAnnotationIdentifierList.push_back(annotationIdentifier);
							if (physicalEntityType.empty())
							{
								physicalEntityType = configHandler.getAnnotationSpecies()[annotationDB];
							}
							else if ((!isaComplex) && (physicalEntityType.compare(configHandler.getAnnotationSpecies()[annotationDB]) != 0)) // no complex but type change in annotation!
									{
								std::cerr << "Contradictional annotation: " << physicalEntityType << " / " << configHandler.getAnnotationSpecies()[annotationDB] << ". Aborting parse. " << std::endl;
								return false;
									}
						}
						else
						{
							// Test for Ensembl annotation
							//TODO
						}
						it++;
					}

				}
				else // no annotation: map to physical entity
				{
					if (debug)
					{
						std::cout << "No annotation for Species. Creating a PhysicalEntity object." << std::endl;
					}
					physicalEntityType = "PhysicalEntity";
					// boost::shared_ptr<UniPAX::PhysicalEntity>  entity = manager.createInstance(id, "PhysicalEntity");
					// entity = manager.createInstance<UniPAX::UnificationXref>(createId(model->getListOfSpecies()->get(i)));
					/*if (!created)
																									{
																									std::cerr << "Could not create PhysicalEntity object. Aborting parse." << std::endl;
																									return false;
																									}*/
					// set Attributes
				}
				// create entity of type physicalEntityType.
				entity = boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(manager.createInstance(createId(model->getListOfSpecies()->get(i)->getId()), physicalEntityType, created));
				if (debug) std::cout << "Created Species as Type " << physicalEntityType << std::endl;
				if (!created)
				{
					std::cerr << "Could not create " << physicalEntityType << " object. Aborting parse." << std::endl;
					return false;
				}
				// if (.isSetName())
				std::vector<std::string>::const_iterator dbit = speciesAnnotationNameDBList.begin();
				std::vector<std::string>::const_iterator resit = speciesAnnotationIdentifierList.begin();
				while (dbit != speciesAnnotationNameDBList.end())
				{
					std::string xref_id = createId((*dbit) + "_" + (*resit));
					if (debug) std::cout << "Is UnificationXref already known?" << std::endl;
					boost::shared_ptr<UniPAX::UnificationXref>  ux = manager.createInstance<UniPAX::UnificationXref>(createId((*dbit) + "_" + (*resit)), created);
					if (!created)
					{
						if (ux == 0)
						{
							std::cerr << "Could not create UnificationXref object. Aborting parse." << std::endl;
							return false;
						}
						else
						{
							std::cout << "Found existing object." << std::endl;
						}
					}
					ux->setId(model->getListOfSpecies()->get(i)->getId() + "_" + (*resit));
					ux->setDb((*dbit));
					entity->addXref(ux);
					++dbit;
					++resit;
				}
				pathway->addPathwayComponent(entity);
			}
		}
		// map ListOfReactions
		{
			if (debug)
				std::cout << "ListOfReactions:" << std::endl;
			for (int i=0; i < model->getListOfReactions()->size(); i++)
			{
				if (debug)
					std::cout << i << ". Reaction: " << model->getListOfReactions()->get(i)->getMetaId() << std::endl;
				SBMLReader::ControlType controlType = CONTROL;
				SBMLReader::ReactionType reactionType = getReactionType(model->getListOfReactions()->get(i));
				boost::shared_ptr<UniPAX::Conversion>  bioReaction;
				std::string conversion_id = createId(model->getListOfReactions()->get(i)->getId());
				if (debug)
					std::cout << "Try to create Object with ReactionType=" << reactionType<< " ... ";
				if (reactionType == COMPLEX_DISASSEMBLY || reactionType == COMPLEX_ASSEMBLY)
				{
					bioReaction = boost::dynamic_pointer_cast<UniPAX::Conversion>(manager.createInstance<UniPAX::ComplexAssembly>(conversion_id, created));
					if (!created)
					{
						std::cerr << "Could not create Complex object. Aborting parse." << std::endl;
						return false;
					}
					bioReaction->setSpontaneous(true);
					if (reactionType == COMPLEX_ASSEMBLY)
					{
						bioReaction->setConversionDirection("LEFT_TO_RIGHT");
					}
					else
					{
						bioReaction->setConversionDirection("RIGHT_TO_LEFT");
					}
				}
				else if (reactionType == TRANSPORT)
				{
					bioReaction = boost::dynamic_pointer_cast<UniPAX::Conversion>(manager.createInstance<UniPAX::Transport>(conversion_id, created));
					if (!created)
					{
						std::cerr << "Could not create Transport object. Aborting parse." << std::endl;
						return false;
					}
				}
				else
				{
					bioReaction = boost::dynamic_pointer_cast<UniPAX::Conversion>(manager.createInstance<UniPAX::BiochemicalReaction>(conversion_id, created));
					if (!created)
					{
						std::cerr << "Could not create BiochemicalReaction object. Aborting parse." << std::endl;
						return false;
					}
				}
				if (debug)
					std::cout << "Successfully created." << std::endl;
				if (model->getListOfReactions()->get(i)->isSetName())
				{
					bioReaction->addName(model->getListOfReactions()->get(i)->getName());
				}
				else
				{
					bioReaction->addName(model->getListOfReactions()->get(i)->getId());
				}
				// Reaction annotation
				if (model->getListOfReactions()->get(i)->isSetAnnotation())
				{
					if (debug)
					{
						std::cout << "Found annotation for reaction: " << model->getListOfReactions()->get(i)->getAnnotationString() << std::endl;
					}

					std::vector<std::string> annotations;
					if (!model->getListOfReactions()->get(i)->getAnnotationString().empty())
					{
						annotations = parseURIs(model->getListOfReactions()->get(i)->getAnnotationString());
					}
					std::vector<std::string>::iterator it = annotations.begin();
					while ( it != annotations.end() )
					{
						std::pair<std::string, std::string> miriam = parseMiriamAnnotation(*it);
						std::string xref_id = createId(miriam.second + "_" + miriam.first); // id = <DB>_<Identifier>
						if (debug)
							std::cout << "Is Xref '" << xref_id << "' already known? ..." << std::endl;
						boost::shared_ptr<UniPAX::Xref>  xref = boost::dynamic_pointer_cast<UniPAX::Xref>(manager.getInstance(xref_id, manager.getInstanceType(xref_id)));
						if (xref != 0)
						{ // annotation already there
						}
						else
						{ // new annotation
							if (debug)
								std::cout << "Creating Xref Object " << xref_id << std::endl;
							xref = manager.createInstance<UniPAX::UnificationXref>(xref_id, created);
							if (!created)
							{
								std::cerr << "Could not create UnificationXref object. Aborting parse." << std::endl;
								return false;
							}
							xref->setId(model->getListOfReactions()->get(i)->getId() + "_" + miriam.first);
							xref->setDb(miriam.second);
						}
						bioReaction->addXref(xref);
						if (miriam.second.compare("Enzyme Nomenclature") == 0)
						{
							controlType = CATALYSIS;
						}
						it++;
					}

				}

				double stoi_coef;
				libsbml::Species* species;
				std::string sidRef;
				if (debug)
					std::cout << "Educts:" << std::endl;
				// Educts
				for (int j = 0; j < model->getListOfReactions()->get(i)->getNumReactants(); j++)
				{
					sidRef = model->getListOfReactions()->get(i)->getReactant(j)->getSpecies();
					if (debug)
						std::cout << j << ". Educt:" << sidRef << std::endl;
					species = model->getSpecies(sidRef);
					std::stringstream pep_id;
					pep_id << "LEFT_" << j << "_" << conversion_id << "_" << sidRef;
					boost::shared_ptr<UniPAX::PhysicalEntity>  newPEP = manager.createInstance<UniPAX::PhysicalEntity>(createId(pep_id.str()), created);
					if (!created)
					{
						std::cerr << "Could not create PhysicalEntity object. Aborting parse." << std::endl;
						return false;
					}
					newPEP->addMemberPhysicalEntity(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(manager.getInstance(createId(sidRef))));
					newPEP->setCellularLocation(boost::dynamic_pointer_cast<UniPAX::CellularLocationVocabulary>(manager.getInstance(createId(species->getCompartment()), "CellularLocationVocabulary")));
					stoi_coef = model->getListOfReactions()->get(i)->getReactant(j)->getStoichiometry();
					boost::shared_ptr<UniPAX::Stoichiometry>  stoi = manager.createInstance<UniPAX::Stoichiometry>(createId("LEFT_" + conversion_id + "_"+ sidRef +"_STOICHIOMETRY"), created);
					if (!created)
					{
						std::cerr << "Could not create Stoichiometry object. Aborting parse." << std::endl;
						return false;
					}
					stoi->setStoichiometricCoefficient(stoi_coef);
					stoi->setPhysicalEntity(newPEP);

					bioReaction->addParticipantStoichiometry(stoi);
					bioReaction->addLeft(newPEP);

				}

				if (debug)
					std::cout << "Products:" << std::endl;
				// Products
				for (int j = 0; j < model->getListOfReactions()->get(i)->getNumProducts(); j++)
				{
					sidRef = model->getListOfReactions()->get(i)->getProduct(j)->getSpecies();
					if (debug)
						std::cout << j << ". Product: " << sidRef << std::endl;
					species = model->getSpecies(sidRef);
					std::stringstream pep_id;
					pep_id << "RIGHT_" << j << "_" << conversion_id << "_" << sidRef;
					boost::shared_ptr<UniPAX::PhysicalEntity>  newPEP = manager.createInstance<UniPAX::PhysicalEntity>(createId(pep_id.str()), created);
					if (!created)
					{
						std::cerr << "Could not create PhysicalEntity object. Aborting parse." << std::endl;
						return false;
					}
					newPEP->addMemberPhysicalEntity(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(manager.getInstance(createId(sidRef))));
					newPEP->setCellularLocation(boost::dynamic_pointer_cast<UniPAX::CellularLocationVocabulary>(manager.getInstance(createId(species->getCompartment()), "CellularLocationVocabulary")));
					stoi_coef = model->getListOfReactions()->get(i)->getProduct(j)->getStoichiometry();
					std::stringstream stoi_id;
					stoi_id << "RIGHT_" << conversion_id << "_" << sidRef << "_STOICHIOMETRY";
					boost::shared_ptr<UniPAX::Stoichiometry>  stoi = manager.createInstance<UniPAX::Stoichiometry>(createId(stoi_id.str()), created);
					if (!created)
					{
						std::cerr << "Could not create Stoichiometry object. Aborting parse." << std::endl;
						return false;
					}
					stoi->setStoichiometricCoefficient(stoi_coef);
					stoi->setPhysicalEntity(newPEP);

					bioReaction->addParticipantStoichiometry(stoi);
					bioReaction->addRight(newPEP);

				}
				if (debug)
					std::cout << "Control objects:" << std::endl;
				// Control objects
				if(model->getListOfReactions()->get(i)->getNumModifiers() > 0)
				{
					std::string control_id = "control_" + model->getListOfReactions()->get(i)->getId();
					for (int j = 0; j <  model->getListOfReactions()->get(i)->getNumModifiers(); j++)
					{
						sidRef = model->getListOfReactions()->get(i)->getModifier(j)->getSpecies();
						if (debug)
							std::cout << j << ". Control: " << control_id << std::endl;
						species = model->getSpecies(sidRef);
						std::stringstream rc_id;
						rc_id << "PEP" << j << "_" << control_id << "_" << sidRef;
						boost::shared_ptr<UniPAX::Control>  reacControl = manager.createInstance<UniPAX::Control>(createId(rc_id.str()), created);
						if (!created)
						{
							std::cerr << "Could not create Control  object. Aborting parse." << std::endl;
							return false;
						}
						std::stringstream pep_id;
						pep_id << "PEP_" << j << "_" << control_id << "_" << sidRef;
						boost::shared_ptr<UniPAX::PhysicalEntity>  newPEP = manager.createInstance<UniPAX::PhysicalEntity>(createId(pep_id.str()), created);
						if (!created)
						{
							std::cerr << "Could not create PhysicalEntity object. Aborting parse." << std::endl;
							return false;
						}
						newPEP->setCellularLocation(boost::dynamic_pointer_cast<UniPAX::CellularLocationVocabulary>(manager.getInstance(createId(species->getCompartment()), "CellularLocationVocabulary")));
						newPEP->addMemberPhysicalEntity(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(manager.getInstance(createId(sidRef))));
						// Adding controller to the control
						reacControl->addController(newPEP);
						reacControl->setControlled(bioReaction);

						//Creating the controlType
						if(controlType == CONTROL)
						{
							reacControl->setControlType("INHIBITION");
						}
						else // controlType == CATALYSIS
						{
							reacControl->setControlType("ACTIVATION");
						}

					}
				}
				pathway->addPathwayComponent(bioReaction);

			}
		}
		return true;
	}
	return false;
}

SBMLReader::ReactionType SBMLReader::getReactionType(libsbml::Reaction* reaction)
{
	// Difference between number of complex in educts and products
	int complexBalance = 0;
	// # complex in the educts
	for (int i=0; i < reaction->getListOfReactants()->size(); i++)
	{
		if (manager.getInstanceType(createId(reaction->getListOfReactants()->get(i)->getSpecies())).compare("Complex") == 0)
		{
			--complexBalance;
		}
	}
	for (int i=0; i < reaction->getListOfProducts()->size(); i++)
	{
		if (manager.getInstanceType(createId(reaction->getListOfProducts()->get(i)->getSpecies())).compare("Complex") == 0)
		{
			++complexBalance;
		}
	}

	for (int i=0; i < reaction->getListOfReactants()->size(); i++)
	{
		std::string compartmentReac = reaction->getModel()->getSpecies(reaction->getListOfReactants()->get(i)->getSpecies())->getCompartment();
		for (int j=0; j < reaction->getListOfProducts()->size(); j++)
		{
			if (compartmentReac.compare(reaction->getModel()->getSpecies(reaction->getListOfProducts()->get(j)->getSpecies())->getCompartment()) != 0)
			{
				return SBMLReader::TRANSPORT;
			}
		}
	}
	if(complexBalance > 0)
	{
		return SBMLReader::COMPLEX_ASSEMBLY;
	}
	else if(complexBalance < 0)
	{
		return SBMLReader::COMPLEX_DISASSEMBLY;
	}
	else
	{
		return SBMLReader::BIOCHEMICAL_REACTION;
	}
}

void SBMLReader::setDebug(bool debug_)
{
	debug = debug_;
	configHandler.setDebug(debug_);
}

void SBMLReader::createObjectsOnly(bool objects_only_)
{
	objects_only = objects_only_;
}


std::map<std::string, boost::shared_ptr<UniPAX::UPBase> > SBMLReader::getData()
{
	return manager.getData();
}


UniPAX::PersistenceManager& SBMLReader::getPersistenceManager()
{
	return manager;
}

const UniPAX::PersistenceManager& SBMLReader::getPersistenceManager() const
{
	return manager;
}

/*std::string SBMLReader::createId(const ::SBase* object)
					{
					if (object->isSetMetaId())
					{
					return createId(object->getMetaId());
					}
				// TODO other way of id generation???
				return createId(boost::lexical_cast<std::string>(++object_counter));
				}

				std::string SBMLReader::createId(const ASTNode* object)
				{
				return createId(object->getName());
				}*/

std::string SBMLReader::createId(const std::string unique)
{
	std::map<std::string, std::string>::const_iterator it = object_id.find(unique);
	if (it != object_id.end())
	{
		return (*it).second;
	}
	std::string id = boost::lexical_cast<std::string>(++object_counter);
	object_id.insert(std::pair<std::string, std::string> (unique, id));
	return id;
}

std::pair<std::string, std::string> SBMLReader::parseMiriamAnnotation(const std::string annotation)
{
	std::string uri, id, official_urn;
	int pos = annotation.find("#");
	if (pos != -1)
	{
		std::vector<std::string> tokens;
		boost::split(tokens, annotation, boost::is_any_of("#"));
		uri = tokens[0];
		id = tokens[1];
	}
	else
	{
		//pos = annotation.rfind(":");
		pos = annotation.find(":"); // urn:
		pos = annotation.find(":", pos+1); // urn:miriam:
		pos = annotation.find(":", pos+1); // urn:miriam:obo.chebi:
		if (pos != -1)
		{
			uri = annotation.substr(0, pos);
			id = annotation.substr(pos+1);
		}
	}
	if (uri.empty() || id.empty())
		return std::pair<std::string, std::string>();
	official_urn = miriamLink->getOfficialURI(uri);
	if (official_urn.empty())
		official_urn = uri;
	return std::pair<std::string, std::string>(id, official_urn);
}

std::vector<std::string> SBMLReader::parseURIs(std::string annotation)
{
	std::vector<std::string> uris;
	boost::algorithm::split_regex(uris, annotation, boost::regex("<rdf:li"));
	uris.erase(uris.begin());
	std::string key("rdf:resource=\"");
	std::string tmp;
	for (std::vector<std::string>::iterator it = uris.begin(); it != uris.end(); it++)
	{
		tmp = (*it).substr((*it).find(key) + key.length());
		*it = tmp.substr(0, tmp.find("\""));
	}
	return uris;
}

} // namespace
