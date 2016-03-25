#!/bin/bash

cd ..

if test -d build
then
	echo "build exists"
    cd include/UNIPAX/KERNEL/BIOPAX/

else
	echo "create build"
    mkdir build
    cmake ..
    cd include/UNIPAX/KERNEL/BIOPAX/

fi

echo "create .cxx .hxx .ixx .sql files with ODB for KERNEL/BIOPAX ..."
#odb -I ../../../ -I ../../../../build/include -d mysql --generate-query --generate-schema --include-prefix UNIPAX/PERSISTENCE/MYSQL/BIOPAX/ --include-with-brackets *.h
odb -I ../../../ -I ../../../../build/include -d mysql --generate-query --generate-schema --include-prefix UNIPAX/PERSISTENCE/MYSQL/BIOPAX/ --include-regex '%UNIPAX/PERSISTENCE/MYSQL(.+).h>%UNIPAX/KERNEL$1.h>%' --include-regex '%UNIPAX/KERNEL$1.hxx%UNIPAX/PERSISTENCE/MYSQL(.+).hxx%' --include-with-brackets *.h
mv *.cxx ../../../../source/UNIPAX/PERSISTENCE/MYSQL/BIOPAX/
mv *.hxx ../../PERSISTENCE/MYSQL/BIOPAX/
mv *.ixx ../../PERSISTENCE/MYSQL/BIOPAX/
mv *.sql ../../PERSISTENCE/MYSQL/BIOPAX/

echo "create .cxx .hxx .ixx .sql files with ODB for KERNEL/EXT ..."
cd ../EXT
#odb -I ../../../ -I ../../../../build/include -d mysql --generate-query --generate-schema --include-prefix UNIPAX/PERSISTENCE/MYSQL/EXT/ --include-with-brackets *.h
odb -I ../../../ -I ../../../../build/include -d mysql --generate-query --generate-schema --include-prefix UNIPAX/PERSISTENCE/MYSQL/EXT/ --include-regex '%UNIPAX/PERSISTENCE/MYSQL(.+).h>%UNIPAX/KERNEL$1.h>%' --include-regex '%UNIPAX/KERNEL$1.hxx%UNIPAX/PERSISTENCE/MYSQL(.+).hxx%' --include-with-brackets *.h
mv *.cxx ../../../../source/UNIPAX/PERSISTENCE/MYSQL/EXT/
mv *.hxx ../../PERSISTENCE/MYSQL/EXT/
mv *.ixx ../../PERSISTENCE/MYSQL/EXT/
mv *.sql ../../PERSISTENCE/MYSQL/EXT/

# correct includes with vim:
# vim PERSISTENCE/MYSQL/BIOPAX/*.hxx
# :bufdo %s/PERSISTENCE\/MYSQL\(.\+\)\.h>/KERNEL\1\.h>/g | update
# :bufdo %s/KERNEL\(.\+\)\.hxx>/PERSISTENCE\/MYSQL\1\.hxx>/g | update
# same for PERSISTENCE/MYSQL/EXT/*.hxx
