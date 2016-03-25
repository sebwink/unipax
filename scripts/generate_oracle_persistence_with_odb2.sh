#!/bin/bash

source_dir=`readlink -e ../`
build_dir=`readlink -e $1`
gtest_dir=`readlink -e $2`
boost_dir=`readlink -e $3`
odb_dir=`readlink -e $4`

if [ "$source_dir" == "" ]; then
	echo "ERROR: Could not find UniPAX source directory."
	exit 1
fi

echo "Using UniPAX source directory \"${source_dir}\""

if [ "$build_dir" == "" ]; then
	echo "ERROR: Could not find UniPAX build directory."
	exit 1
fi

echo "Using UniPAX build directory \"${build_dir}\""

if [ "$gtest_dir" == "" ]; then
	echo "gtest directory not explicit given. Using standard include dirs."
	gtest_dir=${build_dir}
else
	echo "Using gtest directory \"${gtest_dir}\""
fi

if [ "$boost_dir" == "" ]; then
	echo "boost directory not explicit given. Using standard include dirs."
	boost_dir=${build_dir}
else
	echo "Using boost directory \"${boost_dir}\""
fi

if [ "$odb_dir" == "" ]; then
	echo "odb directory not explicit given. Using standard include dirs."
	odb_dir=${build_dir}
else
	echo "Using odb directory \"${odb_dir}\""
fi


echo "Creating .cxx .hxx .ixx .sql files with ODB for KERNEL/BIOPAX ..."

cd ${source_dir}/include/UNIPAX/KERNEL/BIOPAX/

odb -D ODB_COMPILE -I ${source_dir}/include -I ${build_dir}/include -d oracle --profile boost/smart-ptr --generate-query --generate-schema --include-prefix 'UNIPAX/PERSISTENCE/ORACLE/BIOPAX/' --include-regex '%UNIPAX/PERSISTENCE/ORACLE/BIOPAX/(.+).h%UNIPAX/KERNEL/BIOPAX/$1.h%' --include-regex '%UNIPAX/KERNEL/BIOPAX/(.+).hxx%UNIPAX/PERSISTENCE/ORACLE/BIOPAX/$1.hxx%' --include-regex '%UNIPAX/PERSISTENCE/ORACLE/EXT/(.+).h%UNIPAX/KERNEL/EXT/$1.h%' --include-regex '%UNIPAX/KERNEL/EXT/(.+).hxx%UNIPAX/PERSISTENCE/ORACLE/EXT/$1.hxx%' --include-with-brackets *.h
mv *.cxx ${source_dir}/source/UNIPAX/PERSISTENCE/ORACLE/BIOPAX/
mv *.hxx ${source_dir}/include/UNIPAX/PERSISTENCE/ORACLE/BIOPAX/
mv *.ixx ${source_dir}/include/UNIPAX/PERSISTENCE/ORACLE/BIOPAX/
mv *.sql ${source_dir}/include/UNIPAX/PERSISTENCE/ORACLE/BIOPAX/

echo "Creating .cxx .hxx .ixx .sql files with ODB for KERNEL/EXT ..."

cd ${source_dir}/include/UNIPAX/KERNEL/EXT

odb -D ODB_COMPILE -I ${source_dir}/include -I ${build_dir}/include -I ${odb_dir}/include -I ${gtest_dir}/include -I ${boost_dir} -d oracle --profile boost/smart-ptr --profile boost/date-time/posix-time --generate-query --generate-schema --include-prefix 'UNIPAX/PERSISTENCE/ORACLE/EXT/'    --include-regex '%UNIPAX/PERSISTENCE/ORACLE/BIOPAX/(.+).h%UNIPAX/KERNEL/BIOPAX/$1.h%' --include-regex '%UNIPAX/KERNEL/BIOPAX/(.+).hxx%UNIPAX/PERSISTENCE/ORACLE/BIOPAX/$1.hxx%' --include-regex '%UNIPAX/PERSISTENCE/ORACLE/EXT/(.+).h%UNIPAX/KERNEL/EXT/$1.h%' --include-regex '%UNIPAX/KERNEL/EXT/(.+).hxx%UNIPAX/PERSISTENCE/ORACLE/EXT/$1.hxx%' --include-with-brackets *.h
mv *.cxx ${source_dir}/source/UNIPAX/PERSISTENCE/ORACLE/EXT/
mv *.hxx ${source_dir}/include/UNIPAX/PERSISTENCE/ORACLE/EXT/
mv *.ixx ${source_dir}/include/UNIPAX/PERSISTENCE/ORACLE/EXT/
mv *.sql ${source_dir}/include/UNIPAX/PERSISTENCE/ORACLE/EXT/

cd {source_dir}/include/UNIPAX/PERSISTENCE/ORACLE
cat BIOPAX/*.sql > UniPAX_Oracle.sql
cat EXT/*.sql >> UniPAX_Oracle.sql

cd ${source_dir}/scripts
python sort_oracle_sql.py

cd {source_dir}/include/UNIPAX/PERSISTENCE/ORACLE
mv UniPAX_Oracle_changed.sql UniPAX_Oracle.sql
