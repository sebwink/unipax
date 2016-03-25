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

#include<UNIPAX/IMPORT/TFENCYCLOPEDIA/TFEncyclopediaReader.h>
#include<UNIPAX/KERNEL/all.h>
#include<iostream>
#include<sstream>
#include<QtCore/QFile>
#include<QtCore/QStringList>
#include<QtCore/QTextStream>

namespace UniPAX
{

TFEncyclopediaReader::TFEncyclopediaReader() : filename(""), debug(false)
{
}

TFEncyclopediaReader::TFEncyclopediaReader(const std::string& file): filename(file), debug(false)
{
}

bool TFEncyclopediaReader::setFilename(const std::string& file)
{
	if (file != "")
	{
		filename=file;
		return true;
	}
	else
	{
		return false;
	}
}

TFEncyclopediaReader::TFEncyclopediaReader(const TFEncyclopediaReader& to_copy): filename(to_copy.filename),
		manager(to_copy.manager),
		debug(to_copy.debug)
{
}

TFEncyclopediaReader::~TFEncyclopediaReader()
{
}

TFEncyclopediaReader& TFEncyclopediaReader::operator=(const TFEncyclopediaReader& assign)
{
	manager = assign.manager;
	filename = assign.filename;
	debug = assign.debug;

	return (*this);
}

bool TFEncyclopediaReader::parse(const std::string& filename)
{
	setFilename(filename);

	return parse();
}

bool TFEncyclopediaReader::parse()
{
	//Parser is initialized with the file?
	if (filename != "")
	{

		QFile file( QString(filename.c_str()) );
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return false;

		std::vector<std::string> tmp_vec;
		std::map<std::string, std::vector<std::string> > tmp_map;

		QTextStream in(&file);

		// remove header of the file
		if (!in.atEnd())
		{
			in.readLine();
		}


		if (debug) std::cout << "start parsing file" << std::endl;
		boost::shared_ptr<UniPAX::Provenance>  tfe = boost::dynamic_pointer_cast<UniPAX::Provenance>(manager.createInstance("tfe_provenance","Provenance"));
		tfe->addName("Transcription Factor Encyclopedia");

		while (!in.atEnd())
		{
			QString line = in.readLine();
			QString delimiterPattern("\t");
			QStringList ids = line.split(delimiterPattern);

			if (debug) std::cout << "next line: " << line.toStdString() << std::endl;


			std::string tf_id = ids[0].trimmed().toStdString();
			std::string tf_geneid = ids[1].trimmed().toStdString();
			std::string tf_uniprotid = ids[2].trimmed().toStdString();
			std::string tf_symbol = ids[3].trimmed().toStdString();
			QString delimiterPattern2("|");
			QStringList tf_synonyms = ids[4].split(delimiterPattern2);
			QStringList::iterator qit;
			std::string species = ids[5].trimmed().toStdString();
			std::string targetGeneid = ids[6].trimmed().toStdString();
			std::string targetSymbol = ids[7].trimmed().toStdString();
			std::string targetComplex = ids[8].trimmed().toStdString();
			std::string targetEffect = ids[9].trimmed().toStdString();
			QString delimiterPattern3(",");
			QStringList targetPubmed = ids[10].split(delimiterPattern3);
			std::string source = ids[11].trimmed().toStdString();

			bool created = false;
			// transcription factor information
			if (debug) std::cout << "create Protein: " << tf_symbol << "(" << tf_geneid << ")" << std::endl;
			boost::shared_ptr<UniPAX::Protein>  tf = boost::dynamic_pointer_cast<UniPAX::Protein>(manager.createInstance("Protein"+tf_geneid, "Protein", created));
			if (created)
			{
				for (qit = tf_synonyms.begin(); qit != tf_synonyms.end(); qit++)
				{
					tf->addName(qit->trimmed().toStdString());
				}
				tf->setStandardName(tf_symbol);
				tf->setDisplayName(tf_symbol);
				tf->setDataSource(tfe);
			}

			if (debug) std::cout << "create ProteinReference: " << tf_symbol << "(" << tf_geneid << ")" << std::endl;
			boost::shared_ptr<UniPAX::ProteinReference>  tf_ref = boost::dynamic_pointer_cast<UniPAX::ProteinReference>(manager.createInstance("ProteinReference"+tf_geneid, "ProteinReference", created));
			if (created)
			{
				for (qit = tf_synonyms.begin(); qit != tf_synonyms.end(); qit++)
				{
					tf_ref->addName(qit->trimmed().toStdString());
				}
				tf_ref->setStandardName(targetSymbol);
				tf_ref->setDisplayName(targetSymbol);
				tf->addEntityReference(tf_ref);
			}

			if (species != "")
			{
				if (debug) std::cout << "create BioSource: " << species << std::endl;
				boost::shared_ptr<UniPAX::BioSource>  org = boost::dynamic_pointer_cast<UniPAX::BioSource>(manager.createInstance(species, "BioSource", created));
				if (created)
				{
					org->addName(species);
					org->setDisplayName(species);
					org->setStandardName(species);

					tf_ref->setOrganism(org);
				}
			}


			if (tf_uniprotid != "")
			{
				if (debug) std::cout << "create UnificationXref: " << tf_uniprotid << std::endl;
				boost::shared_ptr<UniPAX::UnificationXref>  uxref = boost::dynamic_pointer_cast<UniPAX::UnificationXref>(manager.createInstance("UniProt_" + tf_uniprotid, "UnificationXref", created));
				if (created)
				{
					uxref->setDb("UniProt");
					uxref->setId(tf_uniprotid);
					tf->addXref(uxref);
					tf_ref->addXref(uxref);
				}
			}

			if (debug) std::cout << "create RelationshipXref: " << tf_geneid << std::endl;
			boost::shared_ptr<UniPAX::RelationshipXref>  rxref = boost::dynamic_pointer_cast<UniPAX::RelationshipXref>(manager.createInstance("EntrezGene_" + tf_geneid, "RelationshipXref", created));
			if (created)
			{
				rxref->setDb("EntrezGene");
				rxref->setId(tf_geneid);
				tf->addXref(rxref);
				tf_ref->addXref(rxref);
			}


			// target information
			if (targetGeneid == "0" || targetGeneid == "")
			{
				targetGeneid = targetSymbol;
			}
			if (debug) std::cout << "create Protein: " << targetSymbol << "(" << targetGeneid << ")" << std::endl;
			boost::shared_ptr<UniPAX::Protein>  target = boost::dynamic_pointer_cast<UniPAX::Protein>(manager.createInstance("Protein"+targetGeneid, "Protein", created));
			if (created)
			{
				target->setStandardName(targetSymbol);
				target->setDisplayName(targetSymbol);
				target->setDataSource(tfe);
			}

			if (debug) std::cout << "create ProteinReference: " << targetSymbol << "(" << targetGeneid << ")" << std::endl;
			boost::shared_ptr<UniPAX::ProteinReference>  targetRef = boost::dynamic_pointer_cast<UniPAX::ProteinReference>(manager.createInstance("ProteinReference"+targetGeneid, "ProteinReference", created));
			if (created)
			{
				targetRef->setStandardName(targetSymbol);
				targetRef->setDisplayName(targetSymbol);
				target->addEntityReference(targetRef);

				if (species != "")
				{
					boost::shared_ptr<UniPAX::BioSource>  org = boost::dynamic_pointer_cast<UniPAX::BioSource>(manager.createInstance(species, "BioSource", created));
					if (created)
					{
						org->addName(species);
						org->setDisplayName(species);
						org->setStandardName(species);

						targetRef->setOrganism(org);
					}
				}
			}
			if (targetGeneid == targetSymbol)
			{
				if (debug) std::cout << "create RelationshipXref: " << targetGeneid << std::endl;
				rxref = boost::dynamic_pointer_cast<UniPAX::RelationshipXref>(manager.createInstance("EntrezGene_" + targetGeneid, "RelationshipXref", created));
				if (created)
				{
					rxref->setDb("EntrezGene");
					rxref->setId(targetGeneid);
					target->addXref(rxref);
					targetRef->addXref(rxref);
				}
			}

			if (debug) std::cout << "create TemplateReactionRegulation: ";
			boost::shared_ptr<UniPAX::TemplateReactionRegulation>  regulation = boost::dynamic_pointer_cast<UniPAX::TemplateReactionRegulation>(manager.createInstance("TRR"+tf_geneid + "|" + targetGeneid,"TemplateReactionRegulation", created));
			if (created)
			{
				regulation->addController(tf);
				regulation->setDataSource(tfe);

				if (targetEffect == "UP-REGULATION")
				{
					if (debug) std::cout << " activation" << std::endl;
					regulation->setControlType("ACTIVATION");
				}
				else if (targetEffect == "DOWN-REGULATION")
				{

					if (debug) std::cout << " activation" << std::endl;
					regulation->setControlType("INHIBITION");
				}
				if (debug) std::cout << std::endl;

				if (debug) std::cout << "create TemplateReaction " << std::endl;
				boost::shared_ptr<UniPAX::TemplateReaction>  templateReaction = boost::dynamic_pointer_cast<UniPAX::TemplateReaction>(manager.createInstance("TR"+targetGeneid,"TemplateReaction", created));
				if (created)
				{
					templateReaction->addProduct(target);
					regulation->setControlled(templateReaction);
					templateReaction->setDataSource(tfe);
				}

				if (debug) std::cout << "create PublicationXref " << std::endl;

				for (qit = targetPubmed.begin(); qit != targetPubmed.end(); qit++)
				{
					std::string pubmed_id = qit->trimmed().toStdString();

					if (pubmed_id == "0")
						continue;

					boost::shared_ptr<UniPAX::PublicationXref>  pxref = boost::dynamic_pointer_cast<UniPAX::PublicationXref>(manager.createInstance("PublicationXref" + pubmed_id, "PublicationXref", created));
					if (created)
					{
						pxref->setDb("Pubmed");
						pxref->setId(pubmed_id);
						templateReaction->addXref(pxref);
					}
				}
			}

		}

		return true;
	}
	else
		return false;
}




void TFEncyclopediaReader::setPersistenceManager(PersistenceManager& _manager)
{
	manager = _manager;
}

PersistenceManager& TFEncyclopediaReader::getPersistenceManager()
{
	return manager;
}

const PersistenceManager& TFEncyclopediaReader::getPersistenceManager() const
{
	return manager;
}

void TFEncyclopediaReader::setDebug(bool _debug)
{
	debug = _debug;
}

}
