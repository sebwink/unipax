/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

SET FEEDBACK OFF;
WHENEVER SQLERROR EXIT FAILURE;
WHENEVER OSERROR EXIT FAILURE;

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Rna_id_entityReference" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Rna_id_entityReference_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Rna_id_entityReference_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Rna_id_notFeature" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Rna_id_notFeature_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Rna_id_notFeature_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Rna_id_memberPhysicalEntity" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Rna_id_memberPhysicalEntity_se"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Rna_id_memberPhysicalEntity_tr"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Rna_id_feature" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Rna_id_feature_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Rna_id_feature_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Rna_id_xref" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Rna_id_xref_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Rna_id_xref_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Rna_name" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Rna_name_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Rna_name_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Rna_comments" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Rna_comments_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Rna_comments_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Rna" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Rna_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Rna_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/


CREATE TABLE "Rna" (
  "unipaxId" NUMBER(20) NOT NULL PRIMARY KEY,
  "unipaxSource" NUMBER(20),
  "availability" VARCHAR2(512),
  "standardName" VARCHAR2(512),
  "displayName" VARCHAR2(512),
  "evidence" NUMBER(20),
  "dataSource" NUMBER(20),
  "cellularLocation" NUMBER(20));

CREATE TABLE "Rna_comments" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" VARCHAR2(512),
  CONSTRAINT "Rna_comments_object_id_fk"
    FOREIGN KEY ("object_id")
    REFERENCES "Rna" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Rna_comments_object_id_i"
  ON "Rna_comments" ("object_id");

CREATE INDEX "Rna_comments_index_i"
  ON "Rna_comments" ("index");

CREATE TABLE "Rna_name" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" VARCHAR2(512),
  CONSTRAINT "Rna_name_object_id_fk"
    FOREIGN KEY ("object_id")
    REFERENCES "Rna" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Rna_name_object_id_i"
  ON "Rna_name" ("object_id");

CREATE INDEX "Rna_name_index_i"
  ON "Rna_name" ("index");

CREATE TABLE "Rna_id_xref" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Rna_id_xref_object_id_fk"
    FOREIGN KEY ("object_id")
    REFERENCES "Rna" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Rna_id_xref_object_id_i"
  ON "Rna_id_xref" ("object_id");

CREATE INDEX "Rna_id_xref_index_i"
  ON "Rna_id_xref" ("index");

CREATE TABLE "Rna_id_feature" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Rna_id_feature_object_id_fk"
    FOREIGN KEY ("object_id")
    REFERENCES "Rna" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Rna_id_feature_object_id_i"
  ON "Rna_id_feature" ("object_id");

CREATE INDEX "Rna_id_feature_index_i"
  ON "Rna_id_feature" ("index");

CREATE TABLE "Rna_id_memberPhysicalEntity" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Rna_id_memberPhysicalEntity_ob"
    FOREIGN KEY ("object_id")
    REFERENCES "Rna" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Rna_id_memberPhysicalEntity_ob"
  ON "Rna_id_memberPhysicalEntity" ("object_id");

CREATE INDEX "Rna_id_memberPhysicalEntity_in"
  ON "Rna_id_memberPhysicalEntity" ("index");

CREATE TABLE "Rna_id_notFeature" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Rna_id_notFeature_object_id_fk"
    FOREIGN KEY ("object_id")
    REFERENCES "Rna" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Rna_id_notFeature_object_id_i"
  ON "Rna_id_notFeature" ("object_id");

CREATE INDEX "Rna_id_notFeature_index_i"
  ON "Rna_id_notFeature" ("index");

CREATE TABLE "Rna_id_entityReference" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Rna_id_entityReference_object_"
    FOREIGN KEY ("object_id")
    REFERENCES "Rna" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Rna_id_entityReference_object_"
  ON "Rna_id_entityReference" ("object_id");

CREATE INDEX "Rna_id_entityReference_index_i"
  ON "Rna_id_entityReference" ("index");

ALTER TABLE "Rna" ADD
  CONSTRAINT "Rna_unipaxSource_fk"
    FOREIGN KEY ("unipaxSource")
    REFERENCES "ImportSource" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "Rna" ADD
  CONSTRAINT "Rna_evidence_fk"
    FOREIGN KEY ("evidence")
    REFERENCES "Evidence" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "Rna" ADD
  CONSTRAINT "Rna_dataSource_fk"
    FOREIGN KEY ("dataSource")
    REFERENCES "Provenance" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "Rna" ADD
  CONSTRAINT "Rna_cellularLocation_fk"
    FOREIGN KEY ("cellularLocation")
    REFERENCES "CellularLocationVocabulary" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

EXIT;
