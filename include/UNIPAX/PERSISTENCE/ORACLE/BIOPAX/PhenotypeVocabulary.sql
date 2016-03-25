/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

SET FEEDBACK OFF;
WHENEVER SQLERROR EXIT FAILURE;
WHENEVER OSERROR EXIT FAILURE;

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "PhenotypeVocabulary_id_xref" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "PhenotypeVocabulary_id_xref_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "PhenotypeVocabulary_id_xref_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "PhenotypeVocabulary_comment" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "PhenotypeVocabulary_comment_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "PhenotypeVocabulary_comment_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "PhenotypeVocabulary" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "PhenotypeVocabulary_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "PhenotypeVocabulary_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/


CREATE TABLE "PhenotypeVocabulary" (
  "unipaxId" NUMBER(20) NOT NULL PRIMARY KEY,
  "unipaxSource" NUMBER(20),
  "term" VARCHAR2(512),
  "patoData" VARCHAR2(512));

CREATE TABLE "PhenotypeVocabulary_comment" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" VARCHAR2(512),
  CONSTRAINT "PhenotypeVocabulary_comment_object_id"
    FOREIGN KEY ("object_id")
    REFERENCES "PhenotypeVocabulary" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "PhenotypeVocabulary_comment_object_id"
  ON "PhenotypeVocabulary_comment" ("object_id");

CREATE INDEX "PhenotypeVocabulary_comment_index_i"
  ON "PhenotypeVocabulary_comment" ("index");

CREATE TABLE "PhenotypeVocabulary_id_xref" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "PhenotypeVocabulary_id_xref_object_id"
    FOREIGN KEY ("object_id")
    REFERENCES "PhenotypeVocabulary" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "PhenotypeVocabulary_id_xref_object_id"
  ON "PhenotypeVocabulary_id_xref" ("object_id");

CREATE INDEX "PhenotypeVocabulary_id_xref_index_i"
  ON "PhenotypeVocabulary_id_xref" ("index");

ALTER TABLE "PhenotypeVocabulary" ADD
  CONSTRAINT "PhenotypeVocabulary_unipaxSource_fk"
    FOREIGN KEY ("unipaxSource")
    REFERENCES "ImportSource" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

EXIT;