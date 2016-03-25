/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

SET FEEDBACK OFF;
WHENEVER SQLERROR EXIT FAILURE;
WHENEVER OSERROR EXIT FAILURE;

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SmallMolecule_id_entityReferen" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SmallMolecule_id_entityReferen"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SmallMolecule_id_entityReferen"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SmallMolecule_id_notFeature" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SmallMolecule_id_notFeature_se"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SmallMolecule_id_notFeature_tr"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SmallMolecule_id_memberPhysica" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SmallMolecule_id_memberPhysica"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SmallMolecule_id_memberPhysica"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SmallMolecule_id_feature" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SmallMolecule_id_feature_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SmallMolecule_id_feature_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SmallMolecule_id_xref" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SmallMolecule_id_xref_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SmallMolecule_id_xref_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SmallMolecule_name" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SmallMolecule_name_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SmallMolecule_name_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SmallMolecule_comments" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SmallMolecule_comments_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SmallMolecule_comments_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SmallMolecule" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SmallMolecule_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SmallMolecule_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/


CREATE TABLE "SmallMolecule" (
  "unipaxId" NUMBER(20) NOT NULL PRIMARY KEY,
  "unipaxSource" NUMBER(20),
  "availability" VARCHAR2(512),
  "standardName" VARCHAR2(512),
  "displayName" VARCHAR2(512),
  "evidence" NUMBER(20),
  "dataSource" NUMBER(20),
  "cellularLocation" NUMBER(20));

CREATE TABLE "SmallMolecule_comments" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" VARCHAR2(512),
  CONSTRAINT "SmallMolecule_comments_object_"
    FOREIGN KEY ("object_id")
    REFERENCES "SmallMolecule" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "SmallMolecule_comments_object_"
  ON "SmallMolecule_comments" ("object_id");

CREATE INDEX "SmallMolecule_comments_index_i"
  ON "SmallMolecule_comments" ("index");

CREATE TABLE "SmallMolecule_name" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" VARCHAR2(512),
  CONSTRAINT "SmallMolecule_name_object_id_f"
    FOREIGN KEY ("object_id")
    REFERENCES "SmallMolecule" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "SmallMolecule_name_object_id_i"
  ON "SmallMolecule_name" ("object_id");

CREATE INDEX "SmallMolecule_name_index_i"
  ON "SmallMolecule_name" ("index");

CREATE TABLE "SmallMolecule_id_xref" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "SmallMolecule_id_xref_object_i"
    FOREIGN KEY ("object_id")
    REFERENCES "SmallMolecule" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "SmallMolecule_id_xref_object_i"
  ON "SmallMolecule_id_xref" ("object_id");

CREATE INDEX "SmallMolecule_id_xref_index_i"
  ON "SmallMolecule_id_xref" ("index");

CREATE TABLE "SmallMolecule_id_feature" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "SmallMolecule_id_feature_objec"
    FOREIGN KEY ("object_id")
    REFERENCES "SmallMolecule" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "SmallMolecule_id_feature_objec"
  ON "SmallMolecule_id_feature" ("object_id");

CREATE INDEX "SmallMolecule_id_feature_index"
  ON "SmallMolecule_id_feature" ("index");

CREATE TABLE "SmallMolecule_id_memberPhysica" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "SmallMolecule_id_memberPhysica"
    FOREIGN KEY ("object_id")
    REFERENCES "SmallMolecule" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "SmallMolecule_id_memberPhysica"
  ON "SmallMolecule_id_memberPhysica" ("object_id");

CREATE INDEX "SmallMolecule_id_memberPhysica"
  ON "SmallMolecule_id_memberPhysica" ("index");

CREATE TABLE "SmallMolecule_id_notFeature" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "SmallMolecule_id_notFeature_ob"
    FOREIGN KEY ("object_id")
    REFERENCES "SmallMolecule" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "SmallMolecule_id_notFeature_ob"
  ON "SmallMolecule_id_notFeature" ("object_id");

CREATE INDEX "SmallMolecule_id_notFeature_in"
  ON "SmallMolecule_id_notFeature" ("index");

CREATE TABLE "SmallMolecule_id_entityReferen" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "SmallMolecule_id_entityReferen"
    FOREIGN KEY ("object_id")
    REFERENCES "SmallMolecule" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "SmallMolecule_id_entityReferen"
  ON "SmallMolecule_id_entityReferen" ("object_id");

CREATE INDEX "SmallMolecule_id_entityReferen"
  ON "SmallMolecule_id_entityReferen" ("index");

ALTER TABLE "SmallMolecule" ADD
  CONSTRAINT "SmallMolecule_unipaxSource_fk"
    FOREIGN KEY ("unipaxSource")
    REFERENCES "ImportSource" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "SmallMolecule" ADD
  CONSTRAINT "SmallMolecule_evidence_fk"
    FOREIGN KEY ("evidence")
    REFERENCES "Evidence" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "SmallMolecule" ADD
  CONSTRAINT "SmallMolecule_dataSource_fk"
    FOREIGN KEY ("dataSource")
    REFERENCES "Provenance" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "SmallMolecule" ADD
  CONSTRAINT "SmallMolecule_cellularLocation"
    FOREIGN KEY ("cellularLocation")
    REFERENCES "CellularLocationVocabulary" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

EXIT;