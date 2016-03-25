/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

SET FEEDBACK OFF;
WHENEVER SQLERROR EXIT FAILURE;
WHENEVER OSERROR EXIT FAILURE;

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "EntityReferenceTypeVocabulary_id_xref" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "EntityReferenceTypeVocabulary_id_xref_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "EntityReferenceTypeVocabulary_id_xref_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "EntityReferenceTypeVocabulary_comment" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "EntityReferenceTypeVocabulary_comment_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "EntityReferenceTypeVocabulary_comment_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "EntityReferenceTypeVocabulary" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "EntityReferenceTypeVocabulary_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "EntityReferenceTypeVocabulary_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/


CREATE TABLE "EntityReferenceTypeVocabulary" (
  "unipaxId" NUMBER(20) NOT NULL PRIMARY KEY,
  "unipaxSource" NUMBER(20),
  "term" VARCHAR2(512));

CREATE TABLE "EntityReferenceTypeVocabulary_comment" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" VARCHAR2(512),
  CONSTRAINT "EntityReferenceTypeVocabulary_comment_objec"
    FOREIGN KEY ("object_id")
    REFERENCES "EntityReferenceTypeVocabulary" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "EntityReferenceTypeVocabulary_comment_objec"
  ON "EntityReferenceTypeVocabulary_comment" ("object_id");

CREATE INDEX "EntityReferenceTypeVocabulary_comment_index"
  ON "EntityReferenceTypeVocabulary_comment" ("index");

CREATE TABLE "EntityReferenceTypeVocabulary_id_xref" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "EntityReferenceTypeVocabulary_id_xref_objec"
    FOREIGN KEY ("object_id")
    REFERENCES "EntityReferenceTypeVocabulary" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "EntityReferenceTypeVocabulary_id_xref_objec"
  ON "EntityReferenceTypeVocabulary_id_xref" ("object_id");

CREATE INDEX "EntityReferenceTypeVocabulary_id_xref_index"
  ON "EntityReferenceTypeVocabulary_id_xref" ("index");

ALTER TABLE "EntityReferenceTypeVocabulary" ADD
  CONSTRAINT "EntityReferenceTypeVocabulary_unipaxSource_"
    FOREIGN KEY ("unipaxSource")
    REFERENCES "ImportSource" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

EXIT;