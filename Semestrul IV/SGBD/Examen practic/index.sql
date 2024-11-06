USE S9;

CREATE INDEX indexInghetate on Inghetate(Denumire);

select Denumire, Pret from Inghetate order by Denumire;