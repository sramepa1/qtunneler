# QTunneler #

## Qtunneler jako následník Tunnelera ##
QTunneler je nová a vylepšená imlementace slavné hry pro MS DOS z roku 1991, [Tunnelera](http://www.bestoldgames.net/stare-hry/tunneler.php). Základní myšlenka původní hry je ve využití neobvyklého konceptu podzemního boje dvou tanků v náhodně generované mapě.
Každý tank začíná hru ve své základně aniž by věděl, kde je nebo kde je jeho protivník. Jediné co vidí je hromada hlíny. Začne tedy systematicky kopat v podzemí a vytváří tak tunely, kterými se pohybuje snadněji a stojí jej to méně paliva. Dochází-li mu palivo nebo je li raněn, může se vrátit zpět do své základny kde se zregeneruje. Celou dobu se snaží najít zničit protivníka, což není vůbec snadný úkol vzhledem k velikosti mapy a faktu, že jeho protivník usiluje o totéž. Tunneler je hra pro dva hráče plná dynamiky, strategického myšlení a rychlého rozhodování u které snadno strávíte s kamarádem večer a budete se dobře bavit.

S ohledem na svůj věk má hra však z dnešního pohledu řadu nedostatků. Jsou to například nízké rozlišení hry, absence podpory pro hraní na LAN nebo pro hraní více hráčů. Proto jsem se rozhodl jeho geniální myšlence dát nové programové tělo.

Hlavním cílem vývoje QTunnelera je vytvořit herní jádro Tunnelera v moderní grafické knihovně, ve [QT](http://qt.nokia.com/products/) za použití mechanizmů umožnujících hraní po lokální síti. Dále také umožnit podporu pro budoucí přidání vyššího počtu hráčů, například pro týmy 2v2 nebo konceptu všichni proti všem. Rovněž s ohledem na rozmáhající se vícejaderné procesory by bylo více než vhodné, kdyby QTunneler pracoval s vlákny a tak mohl efektivněji využít prostředky počítače. Dále by měla být hra být provozuschopná jak pod systémem Windows tak Linux.

## Návrh architektury ##
Qtunneler je grafická aplikace řízená hráčem, tedy v podstatě událostmi které hráč vytváří. Pro tento typ programů a her obecně se výborně hodí architektonický vzor (a v podstatě i filozofii) [MVC](http://en.wikipedia.org/wiki/Model%E2%80%93View%E2%80%93Controller), který jsem se zde, v mírně upravené formě, rozhodl použít.

### Síťová komunikace ###
Dále je třeba  navrhnout vhodným způsobem způsob komunikace mezi dvěma a potenciálně i více klienty po LAN. Komunikace na bázi peer-to-peer se nejeví jako dobrá volba. Protože hra musí být poměrně dobře sesynchronizovaná aby byla nedocházelo k nepředvídatelnému chování, zvolil jsem architekturu typu klient-server, kde serverem bude hráč který hru zakládá.

Jelikož jakákoli síťová zpoždění (latence) by mohly vést k de-synchronizaci klientů oproti hernímu serveru, rozhodl jsem se pro pevnou synchronizaci síťových her. Komunikace tedy bude probíhat při každém vyhodnocení herní scény (50 Hz) a to i tehdy, není li žádná změna k odeslání.

Síťová komunikace si žádá vlastní síťový protokol. Pro jednoduchost parsování jsem navrhl protokol o pevné šířce packetu. Každý packet se tak skládá z 5 integerů (20 bytový protokol), kde první hodnota je kód packetu (viz DefaultValues.h), druhý je časová synchronizace a další při jsou datové, interpretované podle použitého kódu.

### Návrh jádra a MVC ###
Nyní je potřeba navrhnout jednotlivé části hry. Jako vhodný začátek se jeví psaní modelu, který bude poskytovat své služby controleru řídícímu hru. V modelu byly navrženy samostatné třídy pro každý objekt vyskytující se ve hře. V zásadě se jedná o objekty kulaté, bitmapové a speciální objekty reprezentující hlínu a její ohraničení. Model také drží logiku k detekci kolizí a změnám jednotlivých objektů.

Nyní je třeba navrhnout controler. Uvážíme-li navrhovanou síťovou archytekturu klient-server, máme v podstatě dva typy controlerů. První (nazval jsem jej Evaluator) je na straně serveru, vyhodnocuje všechny události ve hře a pracuje pouze se svým modelem (který se udržuje synchronizovaný s modely všech klientů). Druhý je na straně klienta a jeho úkolem je zajistit reakce na hráčovy akce. Potom je tu navíc síťový prvek, který se musí starat o rozesílání a příjem packetů a ten bude společná pro oba typy controlerů.

Vzniká tak zajímavý návrh, kde podle typu hráče má buď controler jeden (Controler), nebo v případě zakládajícího hráče dva - jeden (Evaluator) pro herní server a druhý (Controler) pro hráče. Controler a Evaluator mohou být spojeny sítí v případě hráče, nebo pseudosíťovou smyčkou v případě zakládajícího hráče. Z praktických důvodů si Evaluator drží vlastní model.

Co se View týče, jeho úkol je poměrně jednoduchý a to vyjresovat aktuální výřez herní plochy a aktualizovat jej při každém pokyny od controleru. Pro účely právě pohledu byly do modelu přidány různé podpůrné metody pro extrakci požadovaného výřezu z herní plochy.

## Implementace ##
Při implementaci výše nastíněné architektury jsem použil různé možnosti knihovny QT, například signály a sloty pro komunikaci mezi vlákny, dialogová okna pro volbu nastavení síťového spojení a vlákna.

S ohledem na rozsáhlost projektu bych se na tomto místě rozepsal jen o několika zajímavých problémech, na které jsem v průběhu vývoje narazil. Za zmínku stojí poměrně důkladná optimalizace, kterou prošel celý systém detekce kolizí, který sám osobě není triviální (detekce kolizí vektorových a bitmapou reprezentovaných objektů. Další zajímavou části je také vlastní herní plocha, která je s ohledem na svou rozsáhlost reprezentována bitovým polem, čímž se dost výrazně šetří paměť.

## Známé problémy a nedostatky ##
Ve chvíli, když byla celá hra v podstatě hotová a probíhaly jen optimalizace a odvšivování se vynořil jeden problém, který se ukázal jako chyba v návrhu. Jde o onu pevnou časovou synchronizaci, které působí na 100Mb Ethernetu značné lagy a na jakékoli jiné síti, např. WIFI, je hra již jen obtížně použitelná. Pokud by v budoucnu byla hra dále rozvíjena, bylo by dobré opustit pevnou synchronizaci a synchronizovat jen při změně událostí, ne každý herní rámec.

Dále má hra několik známých chyb (bugů), které se z časových a technických důvodů zatím nepodařilo odstranit. Jedná se hlavně o zamrznutí programu (pravděpodobně deadlock), který se zřídka vyskytne a přes použití mnoha technik (debug zprávy, valgrind) se jej nepodařilo vystopovat. Dále je známa chyba restartu po ukončení hry a také nedostatky v herním vyvážení. Tyto chyby zůstávají k vyřešení pro budoucí práci na této hře.

## Zhodnocení a závěr ##
Programování této hry bylo pro mě osobně velkým přínosem. Seznámil jsem se zde se knohovnou QT, které mě skutečně nadchla a naprogramoval jsem s ní svou první hru v C++. Semestrální práce mi rozhodně byla přínosem a umožnila mi nahlédnout do dosud neznámého světa herních enginů a grafických výpočtů.

## Použité zdroje a nástroje ##
  * okumentace [QT](http://doc.qt.nokia.com/4.7/index.html)
  * okumentace [C++](http://www.cplusplus.com/)
  * ývojové prostředí [NetBeans](http://netbeans.org/)
  * he GNU Compiler Collection, [GCC](http://gcc.gnu.org/)
  * ersion control system [SVN](http://subversion.tigris.org/)
  * inimalist GNU for Windows [MINGW](http://www.mingw.org/)