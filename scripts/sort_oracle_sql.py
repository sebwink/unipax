import os
import re

def sort_file(file):
     
    in_file = open(file,"r")
    out_file = open(file.replace(".sql","")+"_changed.sql","w")  
        
    alter = 0
    alter_string = ""
    create_string = ""
    index_map = {}
    constraint_map = {}
    while 1:
        line = in_file.readline()
        
        if line == "":
            in_file.close()
            break
        
        if "EXIT;" in line:
            continue
        
        if "ALTER TABLE" in line:
            alter = 1
            alter_string = alter_string + line
            continue
        
        if ";" in line and alter == 1:
            alter = 0
            alter_string = alter_string + line
            continue
            
        if alter == 1:
            m = re.compile('CONSTRAINT \"([A-Za-z0-9\_]+)\"').search(line)
            if (m != None):
                if constraint_map.has_key(m.group(1)):
                    for i in range(0,10):
                        tmp = m.group(1)[0:len(m.group(1))-1]+str(i)
                        if constraint_map.has_key(tmp):
                            continue
                        constraint_map[tmp] = 0 
                        alter_string = alter_string + "CONSTRAINT \"" + tmp + "\"\n"
                        break
                else:
                    constraint_map[m.group(1)] = 0
                    alter_string = alter_string + line
            else:
                alter_string = alter_string + line
        else:                      
            m = re.compile('CREATE INDEX \"([A-Za-z0-9\_]+)\"').search(line)
            if (m != None):
                if index_map.has_key(m.group(1)):
                    for i in range(0,10):
                        tmp = m.group(1)[0:len(m.group(1))-1]+str(i)
                        if index_map.has_key(tmp):
                            continue
                        index_map[tmp] = 0 
                        create_string = create_string + "CREATE INDEX \"" + tmp + "\"\n"
                        break
                else:
                    index_map[m.group(1)] = 0
                    create_string = create_string + line
            else:    
                m = re.compile('CONSTRAINT \"([A-Za-z0-9\_]+)\"').search(line)
                if (m != None):
                    if constraint_map.has_key(m.group(1)):
                        for i in range(0,10):
                            tmp = m.group(1)[0:len(m.group(1))-1]+str(i)
                            if constraint_map.has_key(tmp):
                                continue
                            constraint_map[tmp] = 0 
                            create_string = create_string + "CONSTRAINT \"" + tmp + "\"\n"
                            break
                    else:
                        constraint_map[m.group(1)] = 0
                        create_string = create_string + line
                else:
                    create_string = create_string + line            
                
                
    
    out_file.write(create_string)
    out_file.write(alter_string)         
    in_file.close()
    out_file.close()

sort_file("../include/UNIPAX/PERSISTENCE/ORACLE/unipax_oracle.sql")