/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

SET FEEDBACK OFF;
WHENEVER SQLERROR EXIT FAILURE;
WHENEVER OSERROR EXIT FAILURE;

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Conversion_id_rightEntity" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Conversion_id_rightEntity_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Conversion_id_rightEntity_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Conversion_id_leftEntity" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Conversion_id_leftEntity_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Conversion_id_leftEntity_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Conversion_participantStoichio" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Conversion_participantStoichio"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Conversion_participantStoichio"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Conversion_interactionType" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Conversion_interactionType_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Conversion_interactionType_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Conversion_id_participant" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Conversion_id_participant_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Conversion_id_participant_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Conversion_id_xref" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Conversion_id_xref_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Conversion_id_xref_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Conversion_name" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Conversion_name_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Conversion_name_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Conversion_comments" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Conversion_comments_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Conversion_comments_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Conversion" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Conversion_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Conversion_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/


CREATE TABLE "Conversion" (
  "unipaxId" NUMBER(20) NOT NULL PRIMARY KEY,
  "unipaxSource" NUMBER(20),
  "availability" VARCHAR2(512),
  "standardName" VARCHAR2(512),
  "displayName" VARCHAR2(512),
  "evidence" NUMBER(20),
  "dataSource" NUMBER(20),
  "conversionDirection" VARCHAR2(512),
  "spontaneous" NUMBER(1) NOT NULL,
  "kineticLaw" NUMBER(20));

CREATE TABLE "Conversion_comments" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" VARCHAR2(512),
  CONSTRAINT "Conversion_comments_object_id_"
    FOREIGN KEY ("object_id")
    REFERENCES "Conversion" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Conversion_comments_object_id_"
  ON "Conversion_comments" ("object_id");

CREATE INDEX "Conversion_comments_index_i"
  ON "Conversion_comments" ("index");

CREATE TABLE "Conversion_name" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" VARCHAR2(512),
  CONSTRAINT "Conversion_name_object_id_fk"
    FOREIGN KEY ("object_id")
    REFERENCES "Conversion" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Conversion_name_object_id_i"
  ON "Conversion_name" ("object_id");

CREATE INDEX "Conversion_name_index_i"
  ON "Conversion_name" ("index");

CREATE TABLE "Conversion_id_xref" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Conversion_id_xref_object_id_f"
    FOREIGN KEY ("object_id")
    REFERENCES "Conversion" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Conversion_id_xref_object_id_i"
  ON "Conversion_id_xref" ("object_id");

CREATE INDEX "Conversion_id_xref_index_i"
  ON "Conversion_id_xref" ("index");

CREATE TABLE "Conversion_id_participant" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Conversion_id_participant_obje"
    FOREIGN KEY ("object_id")
    REFERENCES "Conversion" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Conversion_id_participant_obje"
  ON "Conversion_id_participant" ("object_id");

CREATE INDEX "Conversion_id_participant_inde"
  ON "Conversion_id_participant" ("index");

CREATE TABLE "Conversion_interactionType" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20),
  CONSTRAINT "Conversion_interactionType_obj"
    FOREIGN KEY ("object_id")
    REFERENCES "Conversion" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Conversion_interactionType_obj"
  ON "Conversion_interactionType" ("object_id");

CREATE INDEX "Conversion_interactionType_ind"
  ON "Conversion_interactionType" ("index");

CREATE TABLE "Conversion_participantStoichio" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20),
  CONSTRAINT "Conversion_participantStoichio"
    FOREIGN KEY ("object_id")
    REFERENCES "Conversion" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Conversion_participantStoichio"
  ON "Conversion_participantStoichio" ("object_id");

CREATE INDEX "Conversion_participantStoichio"
  ON "Conversion_participantStoichio" ("index");

CREATE TABLE "Conversion_id_leftEntity" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Conversion_id_leftEntity_objec"
    FOREIGN KEY ("object_id")
    REFERENCES "Conversion" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Conversion_id_leftEntity_objec"
  ON "Conversion_id_leftEntity" ("object_id");

CREATE INDEX "Conversion_id_leftEntity_index"
  ON "Conversion_id_leftEntity" ("index");

CREATE TABLE "Conversion_id_rightEntity" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Conversion_id_rightEntity_obje"
    FOREIGN KEY ("object_id")
    REFERENCES "Conversion" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Conversion_id_rightEntity_obje"
  ON "Conversion_id_rightEntity" ("object_id");

CREATE INDEX "Conversion_id_rightEntity_inde"
  ON "Conversion_id_rightEntity" ("index");

ALTER TABLE "Conversion" ADD
  CONSTRAINT "Conversion_unipaxSource_fk"
    FOREIGN KEY ("unipaxSource")
    REFERENCES "ImportSource" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "Conversion" ADD
  CONSTRAINT "Conversion_evidence_fk"
    FOREIGN KEY ("evidence")
    REFERENCES "Evidence" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "Conversion" ADD
  CONSTRAINT "Conversion_dataSource_fk"
    FOREIGN KEY ("dataSource")
    REFERENCES "Provenance" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "Conversion" ADD
  CONSTRAINT "Conversion_kineticLaw_fk"
    FOREIGN KEY ("kineticLaw")
    REFERENCES "KineticLaw" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "Conversion_interactionType" ADD
  CONSTRAINT "Conversion_interactionType_val"
    FOREIGN KEY ("value")
    REFERENCES "InteractionVocabulary" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

ALTER TABLE "Conversion_participantStoichio" ADD
  CONSTRAINT "Conversion_participantStoichio"
    FOREIGN KEY ("value")
    REFERENCES "Stoichiometry" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

EXIT;