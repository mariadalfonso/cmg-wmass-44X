/*========================TRGDATA========================*/
begin execute immediate 'drop table TRGDATA';exception when others then null;end;
CREATE TABLE "TRGDATA"
("DATA_ID" NUMBER(20,0),
"ENTRY_ID" NUMBER(20,0),
"ENTRY_NAME" VARCHAR2(56),
"SOURCE" VARCHAR2(128),
"RUNNUM" NUMBER(10,0),
"BITZERONAME" VARCHAR2(56),
"BITNAMECLOB" CLOB,
CONSTRAINT "TRGDATA_PK" PRIMARY KEY ("DATA_ID")
)
PARTITION BY RANGE(RUNNUM)
(
PARTITION THEREST VALUES LESS THAN(MAXVALUE)
);
GRANT SELECT ON "TRGDATA" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON "TRGDATA" TO CMS_LUMI_WRITER;
/*========================TRGDATA_ID========================*/
begin execute immediate 'drop table TRGDATA_ID';exception when others then null;end;
CREATE TABLE "TRGDATA_ID"
("NEXTID" NUMBER(20,0),
CONSTRAINT "TRGDATA_ID_PK" PRIMARY KEY ("NEXTID")
);
INSERT INTO "TRGDATA_ID"("NEXTID") VALUES(0);
GRANT SELECT ON "TRGDATA_ID" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON "TRGDATA_ID" TO CMS_LUMI_WRITER;
/*========================TRGDATA_ENTRIES========================*/
begin execute immediate 'drop table TRGDATA_ENTRIES';exception when others then null;end;
CREATE TABLE "TRGDATA_ENTRIES"
("ENTRY_ID" NUMBER(20,0),
"REVISION_ID" NUMBER(20,0),
"NAME" VARCHAR2(56),
CONSTRAINT "TRGDATA_ENTRIES_PK" PRIMARY KEY ("ENTRY_ID")
)
GRANT SELECT ON "TRGDATA_ENTRIES" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON "TRGDATA_ENTRIES" TO CMS_LUMI_WRITER;
/*========================TRGDATA_ENTRIES_ID========================*/
begin execute immediate 'drop table TRGDATA_ENTRIES_ID';exception when others then null;end;
CREATE TABLE "TRGDATA_ENTRIES_ID"
("NEXTID" NUMBER(20,0),
CONSTRAINT "TRGDATA_ENTRIES_ID_PK" PRIMARY KEY ("NEXTID")
);
INSERT INTO "TRGDATA_ENTRIES_ID"("NEXTID") VALUES(0);
GRANT SELECT ON "TRGDATA_ENTRIES_ID" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON "TRGDATA_ENTRIES_ID" TO CMS_LUMI_WRITER;
/*========================TRGDATA_REV========================*/
begin execute immediate 'drop table TRGDATA_REV';exception when others then null;end;
CREATE TABLE "TRGDATA_REV"
("DATA_ID" NUMBER(20,0),
"REVISION_ID" NUMBER(20,0),
CONSTRAINT "TRGDATA_REV_PK" PRIMARY KEY("DATA_ID","REVISION_ID")
);
GRANT SELECT ON "TRGDATA_REV" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON "TRGDATA_REV" TO CMS_LUMI_WRITER;

/*========================LSTRG========================*/
begin execute immediate 'drop table LSTRG';exception when others then null;end;
CREATE TABLE ""LSTRG"
("DATA_ID" NUMBER(20,0),
"RUNNUM" NUMBER(10,0),
"CMSLSNUM" NUMBER(10,0),
"DEADTIMECOUNT" NUMBER(20,0),
"BITZEROCOUNT" NUMBER(10,0),
"BITZEROPRESCALE" NUMBER(10,0),
"DEADFRAC" BINARY_FLOAT,
"PRESCALEBLOB" BLOB,
"TRGCOUNTBLOB" BLOB,
 CONSTRAINT "LSTRG_PK" PRIMARY KEY ("DATA_ID","CMSLSNUM")
)
PARTITION BY RANGE(DATA_ID)
(
PARTITION THEREST VALUES LESS THAN(MAXVALUE)
);
GRANT SELECT ON "LSTRG" TO PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON "LSTRG" TO CMS_LUMI_WRITER;
