// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

// Begin prologue.
//
//
// End prologue.

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/FragmentFeature-odb.hxx>

#include <cassert>
#include <cstring> // std::memcpy

#include <odb/cache-traits.hxx>
#include <odb/details/shared-ptr.hxx>

#include <odb/oracle/binding.hxx>
#include <odb/oracle/traits.hxx>
#include <odb/oracle/database.hxx>
#include <odb/oracle/transaction.hxx>
#include <odb/oracle/connection.hxx>
#include <odb/oracle/statement.hxx>
#include <odb/oracle/statement-cache.hxx>
#include <odb/oracle/object-statements.hxx>
#include <odb/oracle/container-statements.hxx>
#include <odb/oracle/exceptions.hxx>
#include <odb/oracle/result.hxx>

namespace odb
{
  // FragmentFeature
  //

  // comment
  //

  const char access::object_traits< ::UniPAX::FragmentFeature >::comment_traits::select_all_statement[] =
  "SELECT "
  "\"FragmentFeature_comment\".\"index\","
  "\"FragmentFeature_comment\".\"value\""
  " FROM \"FragmentFeature_comment\" WHERE \"FragmentFeature_comment\".\"object_id\"=:1"
  " ORDER BY \"FragmentFeature_comment\".\"index\""
  ;

  const char access::object_traits< ::UniPAX::FragmentFeature >::comment_traits::insert_one_statement[] =
  "INSERT INTO \"FragmentFeature_comment\" ("
  "\"object_id\","
  "\"index\","
  "\"value\")"
  " VALUES (:1,:2,:3)";

  const char access::object_traits< ::UniPAX::FragmentFeature >::comment_traits::delete_all_statement[] =
  "DELETE FROM \"FragmentFeature_comment\""
  " WHERE \"object_id\"=:1";

  // evidence
  //

  const char access::object_traits< ::UniPAX::FragmentFeature >::evidence_traits::select_all_statement[] =
  "SELECT "
  "\"FragmentFeature_evidence\".\"index\","
  "\"FragmentFeature_evidence\".\"value\""
  " FROM \"FragmentFeature_evidence\" WHERE \"FragmentFeature_evidence\".\"object_id\"=:1"
  " ORDER BY \"FragmentFeature_evidence\".\"index\""
  ;

  const char access::object_traits< ::UniPAX::FragmentFeature >::evidence_traits::insert_one_statement[] =
  "INSERT INTO \"FragmentFeature_evidence\" ("
  "\"object_id\","
  "\"index\","
  "\"value\")"
  " VALUES (:1,:2,:3)";

  const char access::object_traits< ::UniPAX::FragmentFeature >::evidence_traits::delete_all_statement[] =
  "DELETE FROM \"FragmentFeature_evidence\""
  " WHERE \"object_id\"=:1";

  // id_memberFeature
  //

  const char access::object_traits< ::UniPAX::FragmentFeature >::id_memberFeature_traits::select_all_statement[] =
  "SELECT "
  "\"FragmentFeature_id_memberFeatu\".\"index\","
  "\"FragmentFeature_id_memberFeatu\".\"value\""
  " FROM \"FragmentFeature_id_memberFeatu\" WHERE \"FragmentFeature_id_memberFeatu\".\"object_id\"=:1"
  " ORDER BY \"FragmentFeature_id_memberFeatu\".\"index\""
  ;

  const char access::object_traits< ::UniPAX::FragmentFeature >::id_memberFeature_traits::insert_one_statement[] =
  "INSERT INTO \"FragmentFeature_id_memberFeatu\" ("
  "\"object_id\","
  "\"index\","
  "\"value\")"
  " VALUES (:1,:2,:3)";

  const char access::object_traits< ::UniPAX::FragmentFeature >::id_memberFeature_traits::delete_all_statement[] =
  "DELETE FROM \"FragmentFeature_id_memberFeatu\""
  " WHERE \"object_id\"=:1";

  // id_featureLocation
  //

  const char access::object_traits< ::UniPAX::FragmentFeature >::id_featureLocation_traits::select_all_statement[] =
  "SELECT "
  "\"FragmentFeature_id_featureLoca\".\"index\","
  "\"FragmentFeature_id_featureLoca\".\"value\""
  " FROM \"FragmentFeature_id_featureLoca\" WHERE \"FragmentFeature_id_featureLoca\".\"object_id\"=:1"
  " ORDER BY \"FragmentFeature_id_featureLoca\".\"index\""
  ;

  const char access::object_traits< ::UniPAX::FragmentFeature >::id_featureLocation_traits::insert_one_statement[] =
  "INSERT INTO \"FragmentFeature_id_featureLoca\" ("
  "\"object_id\","
  "\"index\","
  "\"value\")"
  " VALUES (:1,:2,:3)";

  const char access::object_traits< ::UniPAX::FragmentFeature >::id_featureLocation_traits::delete_all_statement[] =
  "DELETE FROM \"FragmentFeature_id_featureLoca\""
  " WHERE \"object_id\"=:1";

  // featureLocationType
  //

  const char access::object_traits< ::UniPAX::FragmentFeature >::featureLocationType_traits::select_all_statement[] =
  "SELECT "
  "\"FragmentFeature_featureLocatio\".\"index\","
  "\"FragmentFeature_featureLocatio\".\"value\""
  " FROM \"FragmentFeature_featureLocatio\" WHERE \"FragmentFeature_featureLocatio\".\"object_id\"=:1"
  " ORDER BY \"FragmentFeature_featureLocatio\".\"index\""
  ;

  const char access::object_traits< ::UniPAX::FragmentFeature >::featureLocationType_traits::insert_one_statement[] =
  "INSERT INTO \"FragmentFeature_featureLocatio\" ("
  "\"object_id\","
  "\"index\","
  "\"value\")"
  " VALUES (:1,:2,:3)";

  const char access::object_traits< ::UniPAX::FragmentFeature >::featureLocationType_traits::delete_all_statement[] =
  "DELETE FROM \"FragmentFeature_featureLocatio\""
  " WHERE \"object_id\"=:1";

  void access::object_traits< ::UniPAX::FragmentFeature >::
  bind (oracle::bind* b, image_type& i, oracle::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace oracle;

    std::size_t n (0);

    // EntityFeature base
    //
    object_traits< ::UniPAX::EntityFeature >::bind (b + n, i, sk);
    n += 2UL - (
      sk == statement_select ? 0 : (
        sk == statement_insert ? 0 : 1UL));
  }

  bool access::object_traits< ::UniPAX::FragmentFeature >::
  init (image_type& i, const object_type& o, oracle::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace oracle;

    if (i.change_callback_.callback != 0)
      (i.change_callback_.callback) (i.change_callback_.context);

    bool grew (false);

    // EntityFeature base
    //
    if (object_traits< ::UniPAX::EntityFeature >::init (i, o, sk))
      grew = true;

    return grew;
  }

  void access::object_traits< ::UniPAX::FragmentFeature >::
  init (object_type& o, const image_type& i, database& db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // EntityFeature base
    //
    object_traits< ::UniPAX::EntityFeature >::init (o, i, db);
  }

  struct access::object_traits< ::UniPAX::FragmentFeature >::container_statement_cache_type
  {
    oracle::container_statements_impl< comment_traits > comment;
    oracle::container_statements_impl< evidence_traits > evidence;
    oracle::container_statements_impl< id_memberFeature_traits > id_memberFeature;
    oracle::container_statements_impl< id_featureLocation_traits > id_featureLocation;
    oracle::container_statements_impl< featureLocationType_traits > featureLocationType;

    container_statement_cache_type (oracle::connection& c)
    : comment (c),
      evidence (c),
      id_memberFeature (c),
      id_featureLocation (c),
      featureLocationType (c)
    {
    }
  };

  const char access::object_traits< ::UniPAX::FragmentFeature >::persist_statement[] =
  "INSERT INTO \"FragmentFeature\" ("
  "\"unipaxId\","
  "\"unipaxSource\")"
  " VALUES (:1,:2)";

  const char access::object_traits< ::UniPAX::FragmentFeature >::find_statement[] =
  "SELECT "
  "\"FragmentFeature\".\"unipaxId\","
  "\"FragmentFeature\".\"unipaxSource\""
  " FROM \"FragmentFeature\""
  " WHERE \"FragmentFeature\".\"unipaxId\"=:1";

  const char access::object_traits< ::UniPAX::FragmentFeature >::update_statement[] =
  "UPDATE \"FragmentFeature\" SET "
  "\"unipaxSource\"=:1"
  " WHERE \"unipaxId\"=:2";

  const char access::object_traits< ::UniPAX::FragmentFeature >::erase_statement[] =
  "DELETE FROM \"FragmentFeature\""
  " WHERE \"unipaxId\"=:1";

  const char access::object_traits< ::UniPAX::FragmentFeature >::query_statement[] =
  "SELECT "
  "\"FragmentFeature\".\"unipaxId\","
  "\"FragmentFeature\".\"unipaxSource\""
  " FROM \"FragmentFeature\""
  " LEFT JOIN \"ImportSource\" \"unipaxSource\" ON \"unipaxSource\".\"unipaxId\" = \"FragmentFeature\".\"unipaxSource\""
  " ";

  const char access::object_traits< ::UniPAX::FragmentFeature >::erase_query_statement[] =
  "DELETE FROM \"FragmentFeature\""
  " ";

  const char access::object_traits< ::UniPAX::FragmentFeature >::table_name[] =
  "\"FragmentFeature\"";

  void access::object_traits< ::UniPAX::FragmentFeature >::
  persist (database&, const object_type& obj)
  {
    using namespace oracle;

    oracle::connection& conn (
      oracle::transaction::current ().connection ());
    object_statements< object_type >& sts (
      conn.statement_cache ().find_object<object_type> ());
    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    if (im.version != sts.insert_image_version () || imb.version == 0)
    {
      bind (imb.bind, im, statement_insert);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    id_image_type& i (sts.id_image ());
    init (i, obj.unipaxId);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    comment_traits::persist (
      obj.comment,
      idb,
      sts.container_statment_cache ().comment);

    evidence_traits::persist (
      obj.evidence,
      idb,
      sts.container_statment_cache ().evidence);

    id_memberFeature_traits::persist (
      obj.id_memberFeature,
      idb,
      sts.container_statment_cache ().id_memberFeature);

    id_featureLocation_traits::persist (
      obj.id_featureLocation,
      idb,
      sts.container_statment_cache ().id_featureLocation);

    featureLocationType_traits::persist (
      obj.featureLocationType,
      idb,
      sts.container_statment_cache ().featureLocationType);
  }

  void access::object_traits< ::UniPAX::FragmentFeature >::
  update (database&, const object_type& obj)
  {
    using namespace oracle;

    oracle::connection& conn (
      oracle::transaction::current ().connection ());
    object_statements< object_type >& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& i (sts.id_image ());
    init (i, obj.unipaxId);

    image_type& im (sts.image ());
    if (init (im, obj, statement_update))
      im.version++;

    bool u (false);
    binding& imb (sts.update_image_binding ());
    if (im.version != sts.update_image_version () || imb.version == 0)
    {
      bind (imb.bind, im, statement_update);
      sts.update_image_version (im.version);
      imb.version++;
      u = true;
    }

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.update_id_image_version () || idb.version == 0)
    {
      if (i.version != sts.id_image_version () || idb.version == 0)
      {
        bind (idb.bind, i);
        sts.id_image_version (i.version);
        idb.version++;
      }

      sts.update_id_image_version (i.version);

      if (!u)
        imb.version++;
    }

    if (sts.update_statement ().execute () == 0)
      throw object_not_persistent ();

    comment_traits::update (
      obj.comment,
      idb,
      sts.container_statment_cache ().comment);

    evidence_traits::update (
      obj.evidence,
      idb,
      sts.container_statment_cache ().evidence);

    id_memberFeature_traits::update (
      obj.id_memberFeature,
      idb,
      sts.container_statment_cache ().id_memberFeature);

    id_featureLocation_traits::update (
      obj.id_featureLocation,
      idb,
      sts.container_statment_cache ().id_featureLocation);

    featureLocationType_traits::update (
      obj.featureLocationType,
      idb,
      sts.container_statment_cache ().featureLocationType);
  }

  void access::object_traits< ::UniPAX::FragmentFeature >::
  erase (database&, const id_type& id)
  {
    using namespace oracle;

    oracle::connection& conn (
      oracle::transaction::current ().connection ());
    object_statements< object_type >& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& i (sts.id_image ());
    init (i, id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    comment_traits::erase (
      idb,
      sts.container_statment_cache ().comment);

    evidence_traits::erase (
      idb,
      sts.container_statment_cache ().evidence);

    id_memberFeature_traits::erase (
      idb,
      sts.container_statment_cache ().id_memberFeature);

    id_featureLocation_traits::erase (
      idb,
      sts.container_statment_cache ().id_featureLocation);

    featureLocationType_traits::erase (
      idb,
      sts.container_statment_cache ().featureLocationType);

    if (sts.erase_statement ().execute () != 1)
      throw object_not_persistent ();
  }

  access::object_traits< ::UniPAX::FragmentFeature >::pointer_type
  access::object_traits< ::UniPAX::FragmentFeature >::
  find (database& db, const id_type& id)
  {
    using namespace oracle;

    oracle::connection& conn (
      oracle::transaction::current ().connection ());
    object_statements< object_type >& sts (
      conn.statement_cache ().find_object<object_type> ());
    object_statements< object_type >::auto_lock l (sts);

    if (l.locked ())
    {
      if (!find_ (sts, id))
        return pointer_type ();
    }

    pointer_type p (
      access::object_factory< object_type, pointer_type  >::create ());
    pointer_traits< pointer_type >::guard pg (p);
    pointer_cache_traits< pointer_type >::insert_guard ig (
      pointer_cache_traits< pointer_type >::insert (db, id, p));
    object_type& obj (pointer_traits< pointer_type >::get_ref (p));

    if (l.locked ())
    {
      callback (db, obj, callback_event::pre_load);
      init (obj, sts.image (), db);
      sts.find_statement ().stream_result ();
      load_ (sts, obj);
      sts.load_delayed ();
      l.unlock ();
      callback (db, obj, callback_event::post_load);
    }
    else
      sts.delay_load (id, obj, ig.position ());

    ig.release ();
    pg.release ();
    return p;
  }

  bool access::object_traits< ::UniPAX::FragmentFeature >::
  find (database& db, const id_type& id, object_type& obj)
  {
    using namespace oracle;

    oracle::connection& conn (
      oracle::transaction::current ().connection ());
    object_statements< object_type >& sts (
      conn.statement_cache ().find_object<object_type> ());

    object_statements< object_type >::auto_lock l (sts);

    if (!find_ (sts, id))
      return false;

    reference_cache_traits< object_type >::insert_guard ig (
      reference_cache_traits< object_type >::insert (db, id, obj));

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), db);
    sts.find_statement ().stream_result ();
    load_ (sts, obj);
    sts.load_delayed ();
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    ig.release ();
    return true;
  }

  bool access::object_traits< ::UniPAX::FragmentFeature >::
  reload (database& db, object_type& obj)
  {
    using namespace oracle;

    oracle::connection& conn (
      oracle::transaction::current ().connection ());
    object_statements< object_type >& sts (
      conn.statement_cache ().find_object<object_type> ());

    object_statements< object_type >::auto_lock l (sts);

    if (!find_ (sts, obj.unipaxId))
      return false;

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), db);
    sts.find_statement ().stream_result ();
    load_ (sts, obj);
    sts.load_delayed ();
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    return true;
  }

  bool access::object_traits< ::UniPAX::FragmentFeature >::
  find_ (oracle::object_statements< object_type >& sts, const id_type& id)
  {
    using namespace oracle;

    id_image_type& i (sts.id_image ());
    init (i, id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () || imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    select_statement& st (sts.find_statement ());
    st.execute ();
    select_statement::result r (st.fetch ());
    st.free_result ();
    return r != select_statement::no_data;
  }

  void access::object_traits< ::UniPAX::FragmentFeature >::
  load_ (oracle::object_statements< object_type >& sts, object_type& obj)
  {
    oracle::binding& idb (sts.id_image_binding ());

    comment_traits::load (
      obj.comment,
      idb,
      sts.container_statment_cache ().comment);

    evidence_traits::load (
      obj.evidence,
      idb,
      sts.container_statment_cache ().evidence);

    id_memberFeature_traits::load (
      obj.id_memberFeature,
      idb,
      sts.container_statment_cache ().id_memberFeature);

    id_featureLocation_traits::load (
      obj.id_featureLocation,
      idb,
      sts.container_statment_cache ().id_featureLocation);

    featureLocationType_traits::load (
      obj.featureLocationType,
      idb,
      sts.container_statment_cache ().featureLocationType);
  }

  result< access::object_traits< ::UniPAX::FragmentFeature >::object_type >
  access::object_traits< ::UniPAX::FragmentFeature >::
  query (database&, const query_base_type& q)
  {
    using namespace oracle;
    using odb::details::shared;
    using odb::details::shared_ptr;

    oracle::connection& conn (
      oracle::transaction::current ().connection ());

    object_statements< object_type >& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () || imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    shared_ptr<select_statement> st (
      new (shared) select_statement (
        sts.connection (),
        query_statement + q.clause (),
        q.parameters_binding (),
        imb));

    st->execute ();

    shared_ptr< odb::object_result_impl<object_type> > r (
      new (shared) oracle::object_result_impl<object_type> (
        q, st, sts));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits< ::UniPAX::FragmentFeature >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace oracle;

    oracle::connection& conn (
      oracle::transaction::current ().connection ());

    delete_statement st (
      conn,
      erase_query_statement + q.clause (),
      q.parameters_binding ());

    return st.execute ();
  }
}

// Begin epilogue.
//
//
// End epilogue.

#include <odb/post.hxx>
