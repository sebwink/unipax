// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include <UNIPAX/PERSISTENCE/MYSQL/EXT/RateRule-odb.hxx>

#include <cassert>
#include <cstring>  // std::memcpy
#include <typeinfo>

#include <odb/polymorphic-map.hxx>

#include <odb/mysql/traits.hxx>
#include <odb/mysql/database.hxx>
#include <odb/mysql/transaction.hxx>
#include <odb/mysql/connection.hxx>
#include <odb/mysql/statement.hxx>
#include <odb/mysql/statement-cache.hxx>
#include <odb/mysql/polymorphic-object-statements.hxx>
#include <odb/mysql/container-statements.hxx>
#include <odb/mysql/exceptions.hxx>
#include <odb/mysql/polymorphic-object-result.hxx>
#include <odb/mysql/enum.hxx>

namespace odb
{
  // RateRule
  //

  struct access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::extra_statement_cache_type
  {
    extra_statement_cache_type (
      mysql::connection&,
      image_type&,
      id_image_type&,
      mysql::binding&,
      mysql::binding&)
    {
    }
  };

  bool access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  grow (image_type& i,
        my_bool* t,
        std::size_t d)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // Rule base
    //
    if (--d != 0)
    {
      if (base_traits::grow (*i.base, t + 1UL))
        i.base->version++;
    }

    // variable
    //
    if (t[0UL])
    {
      i.variable_value.capacity (i.variable_size);
      grew = true;
    }

    return grew;
  }

  void access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  bind (MYSQL_BIND* b,
        const MYSQL_BIND* id,
        std::size_t id_size,
        image_type& i,
        mysql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace mysql;

    std::size_t n (0);

    // unipaxId
    //
    if (sk == statement_insert)
    {
      if (id != 0)
        std::memcpy (&b[n], id, id_size * sizeof (id[0]));
      n += id_size;
    }

    // variable
    //
    b[n].buffer_type = MYSQL_TYPE_STRING;
    b[n].buffer = i.variable_value.data ();
    b[n].buffer_length = static_cast<unsigned long> (
      i.variable_value.capacity ());
    b[n].length = &i.variable_size;
    b[n].is_null = &i.variable_null;
    n++;

    // unipaxId
    //
    if (sk == statement_update)
    {
      if (id != 0)
        std::memcpy (&b[n], id, id_size * sizeof (id[0]));
      n += id_size;
    }

    // Rule base
    //
    if (sk == statement_select)
      base_traits::bind (b + n, *i.base, sk);
  }

  bool access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  init (image_type& i,
        const object_type& o,
        mysql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace mysql;

    bool grew (false);

    // variable
    //
    {
      ::std::string const& v =
        o.variable;

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i.variable_value.capacity ());
      mysql::value_traits<
          ::std::string,
          mysql::id_string >::set_image (
        i.variable_value,
        size,
        is_null,
        v);
      i.variable_null = is_null;
      i.variable_size = static_cast<unsigned long> (size);
      grew = grew || (cap != i.variable_value.capacity ());
    }

    return grew;
  }

  void access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  init (object_type& o,
        const image_type& i,
        database* db,
        std::size_t d)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // Rule base
    //
    if (--d != 0)
      base_traits::init (o, *i.base, db);

    // variable
    //
    {
      ::std::string& v =
        o.variable;

      mysql::value_traits<
          ::std::string,
          mysql::id_string >::set_value (
        v,
        i.variable_value,
        i.variable_size,
        i.variable_null);
    }
  }

  const access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::info_type
  access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::info (
    typeid (::UniPAX::RateRule),
    &object_traits_impl< ::UniPAX::Rule, id_mysql >::info,
    0,
    "UniPAX::RateRule",
    &odb::create_impl< ::UniPAX::RateRule >,
    &odb::dispatch_impl< ::UniPAX::RateRule, id_mysql >,
    &statements_type::delayed_loader);

  static const access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::entry_type
  polymorphic_entry_for_UniPAX_RateRule;

  const char access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::persist_statement[] =
  "INSERT INTO `RateRule` "
  "(`unipaxId`, "
  "`variable`) "
  "VALUES "
  "(?, ?)";

  const char* const access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::find_statements[] =
  {
    "SELECT "
    "`RateRule`.`variable`, "
    "`Rule`.`unipaxId`, "
    "`Rule`.`unipaxSource`, "
    "`Rule`.`metaId`, "
    "`Rule`.`sboTerm`, "
    "`Rule`.`notes`, "
    "`Rule`.`annotation`, "
    "`Rule`.`typeid`, "
    "`Rule`.`math` "
    "FROM `RateRule` "
    "LEFT JOIN `Rule` ON `Rule`.`unipaxId`=`RateRule`.`unipaxId` "
    "WHERE `RateRule`.`unipaxId`=?",

    "SELECT "
    "`RateRule`.`variable` "
    "FROM `RateRule` "
    "WHERE `RateRule`.`unipaxId`=?"
  };

  const std::size_t access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::find_column_counts[] =
  {
    9UL,
    1UL
  };

  const char access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::update_statement[] =
  "UPDATE `RateRule` "
  "SET "
  "`variable`=? "
  "WHERE `unipaxId`=?";

  const char access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::erase_statement[] =
  "DELETE FROM `RateRule` "
  "WHERE `unipaxId`=?";

  const char access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::query_statement[] =
  "SELECT\n"
  "`RateRule`.`variable`,\n"
  "`Rule`.`unipaxId`,\n"
  "`Rule`.`unipaxSource`,\n"
  "`Rule`.`metaId`,\n"
  "`Rule`.`sboTerm`,\n"
  "`Rule`.`notes`,\n"
  "`Rule`.`annotation`,\n"
  "`Rule`.`typeid`,\n"
  "`Rule`.`math`\n"
  "FROM `RateRule`\n"
  "LEFT JOIN `Rule` ON `Rule`.`unipaxId`=`RateRule`.`unipaxId`\n"
  "LEFT JOIN `ImportSource` AS `unipaxSource_ImportSource` ON `unipaxSource_ImportSource`.`unipaxId`=`Rule`.`unipaxSource`\n"
  "LEFT JOIN `Math` AS `math_Math` ON `math_Math`.`unipaxId`=`Rule`.`math`";

  const char access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::erase_query_statement[] =
  "DELETE FROM `RateRule`";

  const char access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::table_name[] =
  "`RateRule`";

  void access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  persist (database& db, const object_type& obj, bool top, bool dyn)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (top);

    using namespace mysql;

    if (dyn)
    {
      const std::type_info& t (typeid (obj));

      if (t != info.type)
      {
        const info_type& pi (root_traits::map->find (t));
        pi.dispatch (info_type::call_persist, db, &obj, 0);
        return;
      }
    }

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    if (top)
      callback (db,
                obj,
                callback_event::pre_persist);

    base_traits::persist (db, obj, false, false);

    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());
    const binding& idb (sts.id_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    if (idb.version != sts.insert_id_binding_version () ||
        im.version != sts.insert_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, idb.bind, idb.count, im, statement_insert);
      sts.insert_id_binding_version (idb.version);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    if (top)
      callback (db,
                obj,
                callback_event::post_persist);
  }

  void access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  update (database& db, const object_type& obj, bool top, bool dyn)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (top);

    using namespace mysql;
    using mysql::update_statement;

    if (dyn)
    {
      const std::type_info& t (typeid (obj));

      if (t != info.type)
      {
        const info_type& pi (root_traits::map->find (t));
        pi.dispatch (info_type::call_update, db, &obj, 0);
        return;
      }
    }

    if (top)
      callback (db, obj, callback_event::pre_update);

    mysql::transaction& tr (mysql::transaction::current ());
    mysql::connection& conn (tr.connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    base_traits::update (db, obj, false, false);

    image_type& im (sts.image ());
    if (init (im, obj, statement_update))
      im.version++;

    const binding& idb (sts.id_image_binding ());
    binding& imb (sts.update_image_binding ());
    if (idb.version != sts.update_id_binding_version () ||
        im.version != sts.update_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, idb.bind, idb.count, im, statement_update);
      sts.update_id_binding_version (idb.version);
      sts.update_image_version (im.version);
      imb.version++;
    }

    update_statement& st (sts.update_statement ());
    if (st.execute () == 0)
      throw object_not_persistent ();

    if (top)
    {
      callback (db, obj, callback_event::post_update);
      pointer_cache_traits::update (db, obj);
    }
  }

  void access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  erase (database& db, const id_type& id, bool top, bool dyn)
  {
    using namespace mysql;

    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (top);

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    if (dyn)
    {
      discriminator_type d;
      root_traits::discriminator_ (sts.root_statements (), id, &d);

      if (d != info.discriminator)
      {
        const info_type& pi (root_traits::map->find (d));

        if (!pi.derived (info))
          throw object_not_persistent ();

        pi.dispatch (info_type::call_erase, db, 0, &id);
        return;
      }
    }

    if (top)
    {
      id_image_type& i (sts.id_image ());
      init (i, id);

      binding& idb (sts.id_image_binding ());
      if (i.version != sts.id_image_version () || idb.version == 0)
      {
        bind (idb.bind, i);
        sts.id_image_version (i.version);
        idb.version++;
      }
    }

    if (sts.erase_statement ().execute () != 1)
      throw object_not_persistent ();

    base_traits::erase (db, id, false, false);

    if (top)
      pointer_cache_traits::erase (db, id);
  }

  void access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  erase (database& db, const object_type& obj, bool top, bool dyn)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (top);

    if (dyn)
    {
      const std::type_info& t (typeid (obj));

      if (t != info.type)
      {
        const info_type& pi (root_traits::map->find (t));
        pi.dispatch (info_type::call_erase, db, &obj, 0);
        return;
      }
    }

    callback (db, obj, callback_event::pre_erase);
    erase (db, id (obj), true, false);
    callback (db, obj, callback_event::post_erase);
  }

  access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::pointer_type
  access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  find (database& db, const id_type& id)
  {
    using namespace mysql;

    {
      root_traits::pointer_type rp (pointer_cache_traits::find (db, id));

      if (!root_traits::pointer_traits::null_ptr (rp))
        return
          root_traits::pointer_traits::dynamic_pointer_cast<object_type> (rp);
    }

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());
    root_statements_type& rsts (sts.root_statements ());

    statements_type::auto_lock l (rsts);
    root_traits::discriminator_type d;

    if (l.locked ())
    {
      if (!find_ (sts, &id))
        return pointer_type ();
      d = root_traits::discriminator (rsts.image ());
    }
    else
      root_traits::discriminator_ (rsts, id, &d);

    const info_type& pi (
      d == info.discriminator ? info : root_traits::map->find (d));

    root_traits::pointer_type rp (pi.create ());
    pointer_type p (
      root_traits::pointer_traits::static_pointer_cast<object_type> (rp));
    pointer_traits::guard pg (p);

    pointer_cache_traits::insert_guard ig (
      pointer_cache_traits::insert (db, id, rp));

    object_type& obj (pointer_traits::get_ref (p));

    if (l.locked ())
    {
      select_statement& st (sts.find_statement (depth));
      ODB_POTENTIALLY_UNUSED (st);

      callback_event ce (callback_event::pre_load);
      pi.dispatch (info_type::call_callback, db, &obj, &ce);
      init (obj, sts.image (), &db);
      load_ (sts, obj, false);

      if (&pi != &info)
      {
        std::size_t d (depth);
        pi.dispatch (info_type::call_load, db, &obj, &d);
      }

      rsts.load_delayed (0);
      l.unlock ();
      ce = callback_event::post_load;
      pi.dispatch (info_type::call_callback, db, &obj, &ce);
      pointer_cache_traits::load (ig.position ());
    }
    else
      rsts.delay_load (id, obj, ig.position (), pi.delayed_loader);

    ig.release ();
    pg.release ();
    return p;
  }

  bool access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  find (database& db, const id_type& id, object_type& obj, bool dyn)
  {
    ODB_POTENTIALLY_UNUSED (dyn);

    using namespace mysql;

    if (dyn)
    {
      const std::type_info& t (typeid (obj));

      if (t != info.type)
      {
        const info_type& pi (root_traits::map->find (t));
        return pi.dispatch (info_type::call_find, db, &obj, &id);
      }
    }

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());
    root_statements_type& rsts (sts.root_statements ());

    statements_type::auto_lock l (rsts);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement (depth));
    ODB_POTENTIALLY_UNUSED (st);

    reference_cache_traits::position_type pos (
      reference_cache_traits::insert (db, id, obj));
    reference_cache_traits::insert_guard ig (pos);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, false);
    rsts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    reference_cache_traits::load (pos);
    ig.release ();
    return true;
  }

  bool access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  reload (database& db, object_type& obj, bool dyn)
  {
    ODB_POTENTIALLY_UNUSED (dyn);

    using namespace mysql;

    if (dyn)
    {
      const std::type_info& t (typeid (obj));

      if (t != info.type)
      {
        const info_type& pi (root_traits::map->find (t));
        return pi.dispatch (info_type::call_reload, db, &obj, 0);
      }
    }

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());
    root_statements_type& rsts (sts.root_statements ());

    statements_type::auto_lock l (rsts);

    const id_type& id  (
      obj.unipaxId);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement (depth));
    ODB_POTENTIALLY_UNUSED (st);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, true);
    rsts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    return true;
  }

  bool access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  find_ (statements_type& sts,
         const id_type* id,
         std::size_t d)
  {
    using namespace mysql;

    if (d == depth)
    {
      id_image_type& i (sts.id_image ());
      init (i, *id);

      binding& idb (sts.id_image_binding ());
      if (i.version != sts.id_image_version () || idb.version == 0)
      {
        bind (idb.bind, i);
        sts.id_image_version (i.version);
        idb.version++;
      }
    }

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding (d));

    if (imb.version == 0 ||
        check_version (sts.select_image_versions (), im))
    {
      bind (imb.bind, 0, 0, im, statement_select);
      update_version (sts.select_image_versions (),
                      im,
                      sts.select_image_bindings ());
    }

    select_statement& st (sts.find_statement (d));

    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      if (grow (im, sts.select_image_truncated (), d))
        im.version++;

      if (check_version (sts.select_image_versions (), im))
      {
        bind (imb.bind, 0, 0, im, statement_select);
        update_version (sts.select_image_versions (),
                        im,
                        sts.select_image_bindings ());
        st.refetch ();
      }
    }

    return r != select_statement::no_data;
  }

  void access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  load_ (statements_type& sts,
         object_type& obj,
         bool reload,
         std::size_t d)
  {
    ODB_POTENTIALLY_UNUSED (reload);

    if (--d != 0)
      base_traits::load_ (sts.base_statements (), obj, reload);
  }

  void access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  load_ (database& db, root_type& r, std::size_t d)
  {
    using namespace mysql;

    object_type& obj (static_cast<object_type&> (r));
    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    d = depth - d;

    if (!find_ (sts, 0, d))
      throw object_not_persistent ();

    select_statement& st (sts.find_statement (d));
    ODB_POTENTIALLY_UNUSED (st);

    init (obj, sts.image (), &db, d);
    load_ (sts, obj, false, d);
  }

  result< access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::object_type >
  access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  query (database&, const query_base_type& q)
  {
    using namespace mysql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding (depth));

    if (imb.version == 0 ||
        check_version (sts.select_image_versions (), im))
    {
      bind (imb.bind, 0, 0, im, statement_select);
      update_version (sts.select_image_versions (),
                      im,
                      sts.select_image_bindings ());
    }

    std::string text (query_statement);
    if (!q.empty ())
    {
      text += "\n";
      text += q.clause ();
    }

    q.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        conn,
        text,
        true,
        true,
        q.parameters_binding (),
        imb));

    st->execute ();

    shared_ptr< odb::polymorphic_object_result_impl<object_type> > r (
      new (shared) mysql::polymorphic_object_result_impl<object_type> (
        q, st, sts, 0));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::UniPAX::RateRule, id_mysql >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace mysql;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());

    std::string text (erase_query_statement);
    if (!q.empty ())
    {
      text += ' ';
      text += q.clause ();
    }

    q.init_parameters ();
    delete_statement st (
      conn,
      text,
      q.parameters_binding ());

    return st.execute ();
  }
}

#include <odb/post.hxx>
