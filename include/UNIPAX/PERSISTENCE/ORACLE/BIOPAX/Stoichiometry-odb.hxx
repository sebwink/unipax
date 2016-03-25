// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef STOICHIOMETRY_ODB_HXX
#define STOICHIOMETRY_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 10800UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

// Begin prologue.
//
#include <odb/boost/version.hxx>
#if ODB_BOOST_VERSION != 1080000 // 1.8.0
#  error ODB and C++ compilers see different libodb-boost interface versions
#endif
#include <boost/shared_ptr.hpp>
#include <odb/boost/smart-ptr/pointer-traits.hxx>
#include <odb/boost/smart-ptr/wrapper-traits.hxx>
//
// End prologue.

#include <UNIPAX/KERNEL/BIOPAX/Stoichiometry.h>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/CellularLocationVocabulary-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/ControlledVocabulary-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Entity-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/EntityFeature-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Evidence-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/EvidenceCodeVocabulary-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/ExperimentalForm-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/ExperimentalFormVocabulary-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/PhysicalEntity-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Provenance-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Score-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/SequenceLocation-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/SequenceRegionVocabulary-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Thing-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/UtilityClass-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Xref-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/EXT/ImportSource-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/EXT/UPBase-odb.hxx>

#include <memory>
#include <cstddef>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#ifdef BOOST_TR1_MEMORY_HPP_INCLUDED
#  include <odb/tr1/wrapper-traits.hxx>
#  include <odb/tr1/pointer-traits.hxx>
#endif
#include <odb/container-traits.hxx>
#include <odb/result.hxx>

#include <odb/details/buffer.hxx>
#include <odb/details/unused.hxx>

#include <odb/oracle/version.hxx>
#include <odb/oracle/forward.hxx>
#include <odb/oracle/oracle-types.hxx>
#include <odb/oracle/query.hxx>

namespace odb
{
  // Stoichiometry
  //
  template <>
  struct class_traits< ::UniPAX::Stoichiometry >
  {
    static const class_kind kind = class_object;
  };

  template <const char* table>
  struct pointer_query_columns< ::UniPAX::Stoichiometry, table >: pointer_query_columns< ::UniPAX::UtilityClass, table >
  {
    // UtilityClass
    //
    typedef pointer_query_columns< ::UniPAX::UtilityClass, table > UtilityClass;

    // stoichiometricCoefficient
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        double,
        oracle::id_double >::query_type,
      oracle::id_double >
    stoichiometricCoefficient_type_;

    static const stoichiometricCoefficient_type_ stoichiometricCoefficient;

    // id_physicalEntity
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        long long unsigned int,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    id_physicalEntity_type_;

    static const id_physicalEntity_type_ id_physicalEntity;
  };

  template <const char* table>
  const typename pointer_query_columns< ::UniPAX::Stoichiometry, table >::stoichiometricCoefficient_type_
  pointer_query_columns< ::UniPAX::Stoichiometry, table >::stoichiometricCoefficient (table, "\"stoichiometricCoefficient\"");

  template <const char* table>
  const typename pointer_query_columns< ::UniPAX::Stoichiometry, table >::id_physicalEntity_type_
  pointer_query_columns< ::UniPAX::Stoichiometry, table >::id_physicalEntity (table, "\"id_physicalEntity\"", 20);

  template <>
  class access::object_traits< ::UniPAX::Stoichiometry >
  {
    public:
    typedef ::UniPAX::Stoichiometry object_type;
    typedef ::boost::shared_ptr< ::UniPAX::Stoichiometry > pointer_type;
    typedef object_traits< ::UniPAX::UPBase >::id_type id_type;

    static const bool auto_id = object_traits< ::UniPAX::UPBase >::auto_id;

    typedef object_traits< ::UniPAX::UPBase >::id_image_type id_image_type;

    struct image_type: object_traits< ::UniPAX::UtilityClass >::image_type
    {
      // stoichiometricCoefficient
      //
      double stoichiometricCoefficient_value;
      sb2 stoichiometricCoefficient_indicator;

      // id_physicalEntity
      //
      char id_physicalEntity_value[12];
      ub2 id_physicalEntity_size;
      sb2 id_physicalEntity_indicator;

      std::size_t version;

      oracle::change_callback change_callback_;

      oracle::change_callback*
      change_callback ()
      {
        return &change_callback_;
      }
    };

    // comment
    //
    struct comment_traits: access::object_traits< ::UniPAX::UtilityClass >::comment_traits
    {
      static const std::size_t id_column_count = 1UL;
      static const std::size_t cond_column_count = 1UL;
      static const std::size_t data_column_count = 3UL;

      static const char insert_one_statement[];
      static const char select_all_statement[];
      static const char delete_all_statement[];
    };

    static id_type
    id (const object_type&);

    static id_type
    id (const image_type&);

    static void
    bind (oracle::bind*, image_type&, oracle::statement_kind);

    static void
    bind (oracle::bind*, id_image_type&);

    static bool
    init (image_type&, const object_type&, oracle::statement_kind);

    static void
    init (object_type&, const image_type&, database&);

    static void
    init (id_image_type&, const id_type&);

    typedef oracle::query query_base_type;

    struct query_type;
    struct container_statement_cache_type;

    static const std::size_t column_count = 4UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);

    static void
    persist (database&, const object_type&);

    static pointer_type
    find (database&, const id_type&);

    static bool
    find (database&, const id_type&, object_type&);

    static bool
    reload (database&, object_type&);

    static void
    update (database&, const object_type&);

    static void
    erase (database&, const id_type&);

    static void
    erase (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
    static bool
    find_ (oracle::object_statements< object_type >&, const id_type&);

    static void
    load_ (oracle::object_statements< object_type >&, object_type&);
  };

  // Stoichiometry
  //
  template <const char* table>
  struct query_columns< ::UniPAX::Stoichiometry, table >: query_columns< ::UniPAX::UtilityClass, table >
  {
    // UtilityClass
    //
    typedef query_columns< ::UniPAX::UtilityClass, table > UtilityClass;

    // stoichiometricCoefficient
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        double,
        oracle::id_double >::query_type,
      oracle::id_double >
    stoichiometricCoefficient_type_;

    static const stoichiometricCoefficient_type_ stoichiometricCoefficient;

    // id_physicalEntity
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        long long unsigned int,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    id_physicalEntity_type_;

    static const id_physicalEntity_type_ id_physicalEntity;
  };

  template <const char* table>
  const typename query_columns< ::UniPAX::Stoichiometry, table >::stoichiometricCoefficient_type_
  query_columns< ::UniPAX::Stoichiometry, table >::stoichiometricCoefficient (table, "\"stoichiometricCoefficient\"");

  template <const char* table>
  const typename query_columns< ::UniPAX::Stoichiometry, table >::id_physicalEntity_type_
  query_columns< ::UniPAX::Stoichiometry, table >::id_physicalEntity (table, "\"id_physicalEntity\"", 20);

  struct access::object_traits< ::UniPAX::Stoichiometry >::query_type:
    query_base_type,
    query_columns< ::UniPAX::Stoichiometry, table_name >
  {
    query_type ();
    query_type (bool);
    query_type (const char*);
    query_type (const std::string&);
    query_type (const query_base_type&);
  };
}

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Stoichiometry-odb.ixx>

// Begin epilogue.
//
//
// End epilogue.

#include <odb/post.hxx>

#endif // STOICHIOMETRY_ODB_HXX