# Představení

Ve vývoji docházím k závěru, že existuje více možností, jak naplánovat jeden krok.

### lineární cesta

- Tato cesta probíhá za podmínky, kdy není v trajektorii překážka a cíl je v úhlu pi / 2 a její délka je rovna přeponě pravoúhlého trojúhelníku utvořeného na základě pravoúhlého trojúhelníku.

**JAK STANOVIT BODY?!**

### pohyb po kružnici

- pro kružnici je v každém případě potřeba trojice bodů

- pohyb po kružnici je ale minimálně dvojího typu, a sice

- <img src="./kruznice_2.svg" alt="image-20201124205758210" style="zoom:100%; margin-left:0%" />

  #### pohyb z prostředního bodu

   - V tomto případě se jedná o načrtnutí z bodu osy lokálního souřadnicového systému [0; 0]
      a jsou projety pouze 2 ze 3
      
      <img src="./kruznice_1.svg" alt="image-20201124205758210" style="zoom:120%;" />
      
  - **JAK STANOVIT BODY?!**

    - Jak již bylo napsáno, prostřední bod je vždy v ose souřadnic, což je také bod, na němž by se měl podle lokáních souřadnic měl nacházet
    - Bod [x; y] je stanoven buď podle přesných lokálních souřadnic cíle, nebo se jedná o mezicíl.
      - Proti němu je vygenerován bod, který je mimo záporné y souřadnice identický.

  #### plný pohyb

  - <img src="./kruznice_3.svg" alt="image-20201124205758210" style="zoom:120%;" />
  - **JAK STANOVIT BODY?!**
    - V případě tohoto pohybu je krajní ze tří bodů [0; 0] a pro představu stačí říct, že mezibod je vytvořen ve vzdálenosti dané minimální vzdálenosti překážky a robota a vzdálenosti překážky.
    - <img src="./kruznice_4.svg" alt="image-20201124205758210" style="zoom:120%;" />

### Dalším určením uskutečnění cesty je funkce sinus v absolutní hodnotě

- robot je nasměřován v pi/2 a tam má i |sin(x)| = 1.
  - naopak směrem kol (0 a pí) je 0 → tímto směrem je nejvíc nevýhodné se pohybovat, stejně jako směry blízkými
- pokud je cíl robota vůči němu na x, kde platí, že **|sin(x)| < |cos(x)|**, je vhodné se pohybovat skrze více kroků.

### Další možný určovač pro tvorbu cesty je poměr vzdáleností 

- Tady se pracuje s tím, že **y** středu kružnice **je rovno nule**

  - principem je jednoduché porovnání lokálních vzdáleností (vzdálenost středu a bodu od osy lokálních souřadnic) na ose **x**

    #### střed je blíž:

    - <img src="./kruznice_5.svg" alt="image-20201124205758210" style="zoom:100%;" />

    - <img src="./kruznice_6.svg" alt="image-20201124205758210" style="zoom:100%;" />

      #### Střed je dál nebo je stejně

      - <img src="./kruznice_7.svg" alt="image-20201124205758210" style="zoom:100%;" />

      #### Střed je prostě moc daleko

      - toto je stvořené pro případ, kdy se lze na stejné místo dostat skrze 2 pohyby s tím, že je průměrná rychlost vyšší a dráha menší

      - <img src="./kruznice_10.svg" alt="image-20201124205758210" style="zoom:110%;" />