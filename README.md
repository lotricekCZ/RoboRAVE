# R<sub>e</sub>(a) = d<sub>m</sub> <sup>e</sup>
(Status: vyřazen)
Tento projekt byl tvořen jako software pro robota určeného pro hašení svíček v 
soutěži RoboRAVE v kategorii pro střední školy.
Výsledné stvoření mělo být schopno rozpoznávat objekty v zorném poli a 
orientace v prostoru, stejně tak se pohybovat po herním poli nikoliv na základě náhody,
ale ze "zvědavosti" - periferie(=senzory) měly nějaký range a snímaný úhel a měly být zaznamenávané
veškeré proběhlé kroky. Na základě těchto informací šlo určit prozkoumanou plochu a vybírána místa zajímavá pro prozkoumání.

Repozitář obsahuje atypické členění zdrojových souborů, které je, díky bohu, překonáno.

---
## Proč je to tak ošklivé?
Nikdy jsem nepočítal s jakoukoliv spoluprací (PCB design & assembly, programování, 3D návrhy) a vlastně jsem dělal práci, na kterou pořadatelé doporučují 3-4členný tým. To vše vedle školních povinností. Výsledkem je abolutní absence jakýchkoliv komentářů, které mohly být vodítkem alespoň pro mě.

## Co to ukončilo?
Maturita. A šibeniční termín, jak vidno, poslední commit byl přidán den před konáním soutěže v 23:09, kdy již byla má neúčast jistá.

## Kde hledat výkladní skříň kódu?
[step.hpp](./utils/planners/planner/step.hpp)

<a style="padding:0.5em; text-decoration:none; margin:0.5em; border-radius:0.95em; background-color:#308; font-size: 20px; font-weight:800;" href=./utils/planners/planner/plans/metody_planovani.md>metody plánování </a> 
=======

<a style="padding:0.5em; text-decoration:none; margin:0.5em; border-radius:0.95em; background-color:#085; font-size: 20px; font-weight:800;" href=./utils/planners/planner/plans/metody_planovani.md>hardwarové periferie </a> 

 <a style="padding:0.5em; text-decoration:none; margin:0.5em; border-radius:0.95em; background-color:#700; font-size: 20px; font-weight:800;" href=./utils/planners/planner/plans/metody_planovani.md>geometrie </a> 

 <a style="padding:0.5em; text-decoration:none; margin:0.5em; border-radius:0.95em; background-color:#058; font-size: 20px; font-weight:800;" href=./utils/planners/planner/plans/metody_planovani.md>logy </a>
