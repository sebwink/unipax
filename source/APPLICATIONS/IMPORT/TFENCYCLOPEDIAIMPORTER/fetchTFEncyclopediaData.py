import urllib
import urllib2

def fetch_tf():
    
    tf_list = []
           
    url = "http://www.cisreg.ca/cgi-bin/tfe/api.pl"
    values = {'code' : 'all-tfids'}
    
    data = urllib.urlencode(values)
    req = urllib2.Request(url, data)
    
#    print "open the connection"
    try:
        f = urllib2.urlopen(req) 
        
        while 1:
            line = f.readline().replace("\n","")
            
            if line == "":  
                break
            else:
                tf_list.append(line)
                                   
        f.close()
    except urllib2.HTTPError, e:
        print 'The server couldn\'t fulfill the request.'
        print 'Error code: ', e.code
    except urllib2.URLError, e:
        print 'We failed to reach a server.'
        print 'Reason: ', e.reason
    
    return tf_list


# return the geneid of the transcription factor id
def fetch_tf_geneID(tfid):
    
    url = "http://www.cisreg.ca/cgi-bin/tfe/api.pl"
    values = {'code' : 'entrez-gene-id',
              'tfid' : tfid}
    
    data = urllib.urlencode(values)
    req = urllib2.Request(url, data)
    
#    print "open the connection"
    try:
        f = urllib2.urlopen(req) 
        
        while 1:
            line = f.readline().replace("\n","")
            
            if line == "":  
                break
            else:
                f.close()
                return line.strip()
                                   
        f.close()
    except urllib2.HTTPError, e:
        print 'The server couldn\'t fulfill the request.'
        print 'Error code: ', e.code
        
    except urllib2.URLError, e:
        print 'We failed to reach a server.'
        print 'Reason: ', e.reason
            
    return None


# return the uniprot of the transcription factor id
def fetch_tf_uniprotID(tfid):
    
    url = "http://www.cisreg.ca/cgi-bin/tfe/api.pl"
    values = {'code' : 'uniprot-id',
              'tfid' : tfid}
    
    data = urllib.urlencode(values)
    req = urllib2.Request(url, data)
    
#    print "open the connection"
    try:
        f = urllib2.urlopen(req) 
        
        while 1:
            line = f.readline().replace("\n","")
            
            if line == "":  
                break
            else:
                f.close()
                return line.strip()
                                   
        f.close()
    except urllib2.HTTPError, e:
        print 'The server couldn\'t fulfill the request.'
        print 'Error code: ', e.code
        
    except urllib2.URLError, e:
        print 'We failed to reach a server.'
        print 'Reason: ', e.reason
            
    return None


# return the species of the transcription factor id
def fetch_tf_species(tfid):
    
    url = "http://www.cisreg.ca/cgi-bin/tfe/api.pl"
    values = {'code' : 'species',
              'tfid' : tfid}
    
    data = urllib.urlencode(values)
    req = urllib2.Request(url, data)
    
#    print "open the connection"
    try:
        f = urllib2.urlopen(req) 
        
        while 1:
            line = f.readline().replace("\n","")
            
            if line == "":  
                break
            else:
                f.close()
                return line.strip()
                                   
        f.close()
    except urllib2.HTTPError, e:
        print 'The server couldn\'t fulfill the request.'
        print 'Error code: ', e.code
        
    except urllib2.URLError, e:
        print 'We failed to reach a server.'
        print 'Reason: ', e.reason
            
    return "unknown"



# return the symbol of the transcription factor id
def fetch_tf_symbol(tfid):
    
    url = "http://www.cisreg.ca/cgi-bin/tfe/api.pl"
    values = {'code' : 'symbol',
              'tfid' : tfid}
    
    data = urllib.urlencode(values)
    req = urllib2.Request(url, data)
    
#    print "open the connection"
    try:
        f = urllib2.urlopen(req) 
        
        while 1:
            line = f.readline().replace("\n","")
            
            if line == "":  
                break
            else:
                f.close()
                return line.strip()
                                   
        f.close()
    except urllib2.HTTPError, e:
        print 'The server couldn\'t fulfill the request.'
        print 'Error code: ', e.code
        
    except urllib2.URLError, e:
        print 'We failed to reach a server.'
        print 'Reason: ', e.reason
            
    return "unknown"


# return the synonyms of the transcription factor id
def fetch_tf_synonyms(tfid):
    
    url = "http://www.cisreg.ca/cgi-bin/tfe/api.pl"
    values = {'code' : 'synonyms',
              'tfid' : tfid}
    
    data = urllib.urlencode(values)
    req = urllib2.Request(url, data)
    
    synonyms = ""
    
#    print "open the connection"
    try:
        f = urllib2.urlopen(req) 
        
        while 1:
            line = f.readline().replace("\n","").strip()
            
            if line == "":  
                break
            else:
                if (synonyms == ""):
                    synonyms = synonyms + line
                else:
                    synonyms = synonyms + "|" + line
                                   
        f.close()
    except urllib2.HTTPError, e:
        print 'The server couldn\'t fulfill the request.'
        print 'Error code: ', e.code
        
    except urllib2.URLError, e:
        print 'We failed to reach a server.'
        print 'Reason: ', e.reason
            
    return synonyms




# return the targets of the transcription factor id
def fetch_tf_targets(tfid):
    
    targets = []
    url = "http://www.cisreg.ca/cgi-bin/tfe/api.pl"
    values = {'code' : 'targets',
              'tfid' : tfid}
    
    data = urllib.urlencode(values)
    req = urllib2.Request(url, data)
    
#    print "open the connection"
    try:
        f = urllib2.urlopen(req) 
        
        while 1:
            line = f.readline().replace("\n","")
                        
            if line == "":  
                break
            else:
                targets.append(line.strip())
                    
        f.close()
    except urllib2.HTTPError, e:
        print 'The server couldn\'t fulfill the request.'
        print 'Error code: ', e.code
        
    except urllib2.URLError, e:
        print 'We failed to reach a server.'
        print 'Reason: ', e.reason
        
    
    return targets


file = open("TranscriptionFactorEncyclopedia.txt","w")
file.write("TFID\tTF Entrez Gene ID\tTF Uniprot ID\tTF Symbol\tTF Synonyms\tSpecies\tTarget Entrez Gene ID\tTarget gene symbol\tActing TF complex\tRegulatory effect on target\tPubmed ID\tSource (user or auto)\n")
print "start fetching all TF-ids ... ",
all_Tfs = fetch_tf()
print "done (size: " + str(len(all_Tfs)) + ")"
for tfid in all_Tfs:
    print "Fetch targets of '" + tfid + "' ...",
    gene_id = fetch_tf_geneID(tfid)
    uniprot_id = fetch_tf_uniprotID(tfid)
    if uniprot_id == None:
        uniprot_id = ""
    species = fetch_tf_species(tfid)
    symbol = fetch_tf_symbol(tfid)
    synonyms = fetch_tf_synonyms(tfid)
    targets = fetch_tf_targets(tfid)
    for target in targets:
        file.write(tfid + "\t" + gene_id + "\t" + uniprot_id + "\t" + symbol + "\t" + synonyms + "\t" + species + "\t" + target +"\n")
    print "done (size: " + str(len(targets)) + ")"

file.close()
