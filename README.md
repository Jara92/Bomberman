# Bomberman
Autor: Jaroslav Fikar

# Téma z Progtestu

Klasická hra Bomberman

###Implementujte následující varianty:

    1. pro alespoň 2 hráče na jednom počítači
    2. pro hru proti počítači
###Hra musí splňovat následující funkcionality:

    1. Načítání herních levelů (mapy) ze souboru (vytvořte vhodný formát)
    2. Sbírání konfigurovatelných bonusů (zvětšení plamenu, více bomb, odpalování bomb na dálku,...)
    3. Ukládání nejlepšího dosaženého skóre do souboru
###Kde lze využít polymorfismus? (doporučené)

    - Ovládání hráčů: lokální hráč, umělá inteligence (různé druhy), síťový hráč
    - Uživatelské rozhraní: konzolové, ncurses, SDL, OpenGL (různé druhy),...
    - Efekty bonusů a nemocí: zvětšení plamenu, zvýšení počtu bomb,...
Další informace

    - https://en.wikipedia.org/wiki/Bomberman

## Zadání hry
Uživatel hru spustí a pomocí grafického rozhraní bude ovládat celou aplikaci.
Hra obsahuje hlavní menu, nastavení a hlavní herní scénu.
Pravidla hry se budou inpirovat původní hrou, ale nebude se jednat o přímou kopii.
Úkolem hráče je projít všechny levely co nejrychleji (a v daném časovém limitu) a získat přitom co nejvíce bodů (například zabitím příšer, ničením zdí a sbíráním bonusů). Hráč má omezený počet životů a po jejich vyčerpání hra končí.
Hlavní hráčovou schopností je pokládání a odpalování bomb. Pomocí bomb může ničit některé zdi a zabíjet nepřátele.
Ničením zdí si také může zpřístupnit bonusy, které mu odemknou různé výhody (např. odpalování bomb na dálku, více životů...). Některé bonusy také mohou být jen dočasné.
Jednotlivé herní levely budou čteny ze souborů, které budou obsahovat všechny informace o daném levelu (generované bonusy, spawnované příšery...) 
Pro celou hru bude jedna mapa, která se skládá z nezničitelných zdí. Ta bude načítána ze souboru. Zničitelné zdi budou generovány náhodně.

Hru bude možné hrát ve dvou (třech) režimech:
   1. Singleplayer: Hráč bude klasicky hrát sám za sebe a bude hrát jen proti počítačem řízeným nepřátelům.
   2. Multiplayer: U jednoho počítače budou 2 hráči. Cílem této hry je zabít toho druhého, nebo za celou hru (za všechny levely) nasbírat více bodů než soupeř.
   3. Debug: Tento režim je pouze pro vývojáře a z hotové hry by byl odstraněn. 
   Slouží k usnadnění testování hry a umožňuje používat "cheaty". Debug režim se zpřístupní spuštěním hry s přepínačem `-debug`. 
   Vývojář si pak může zvolit singleplayer nebo multiplayer hru.
   
###Ovládání
V případě singleplayer hry bude ovládání následující: Pohyb (WASD), Položení bomby (X) a Odpálení bomby (C).

Pro multiplayer hru bude ovládání prvního hráče stejné jako pro singleplayer. 
Druhý hráč bude mít ovládání následující: Pohyb (IJKL), Položení bomby (N) a Odpálení bomby (M).

Ovládání debug módu zatím není úplně specifikováno, protože debugovací funkce budou teprve doplněny.

F1 - Zabij všechny příšery a bonusové body připiš hráči s nejméně body.

F2 - Znič všechny zdi.

F3 - Přidej všem hráčům 10000 bodů.

...

### Kde mám polymorfismus?
Polymorfismus používám u abstraktní třídy `CEnemy`, která má abstraktní metody `Update()` a `TryKill()`. Implementace `CEnemyDump` a `CEnemySmart` budou tyto metody přetěžovat. Z názvu vyplývá, že hlavní rozdíly budou chování a výdrži jednotlivých implementací. 
Metoda `Update()` aktualizuje vnitřní stav objektu a je v ní nějakým způsobem realizován pohyb pomocí primitivní umělé inteligence.
`TryKill()` se pokusí zabít daný objekt. Různé implementace mohou mít různý počet životů a pokus o zabití nemusí být vždy úspěšný.
Polymorfní volání je ve třídě `CBoard`, kde mám instnace tříd `CEnemyDump` a `CEnemySmart` uložené v jednom poli a pro každý snímek na nich volám jejich metodu`Update()`. 
Při kolizi `CEnemy` s objektem typu `CFire` dojde k zavolání metody `TryKill()`.

Polymorfismus také využívám u třídy `CCollectible`, která má abstraktní metody `Update()` a `Apply()`.
Podtřídy `CDoor` a `CBoost` tyto metody přetěžují. 
`CDoor` je takový sebratelný předmět, který hráče za určitých podmínek posune do dalšího levelu. 
Tato implementace bude mít zatím metodu `Update()` prázdnou, ale je možné ji v budoucnu využít například pro animaci.
`Apply()` posune hráče do dalšího levelu (pokud to pravidla hry v daný moment povolí).
`CBoost` je třída, která dává hráči nějakou výhodu (např. zrychlení). Tato výhoda může být i dočasná.
Metoda `Update()` bude v této implementaci provádět odpočet (časově omezený výhoda) a může být využita i pro animaci objektu. 
Také by se mohlo hodit v případě, že bychom chtěli přidat do hry sebratelný objekt, který po určitém čase zmízí a hráč tím přijde o možnost ho sebrat.
Metoda `Apply()` aktivuje hráči výhodu a zároveň může aktivovat odpočet do zavolání metody `Deactivate()`, která hráči výhodu sebere.
Polymorfní volání mám ve třídě `CBoard`, která pro každý snímek volá správnou metodu `Update()`. 
Pokud došlo ke kolizi mezi hráčem a objektem `CCollectible`, pak je na tomto objektu volána správná metoda `Apply()`.

Původně jsem chtěl udělat pro každý druh Boostu vlastní třídu (např. `CExplosionRadiusBoost`), ale lambda funkce v tomto případě poslouží lépe (aplikace boostu je vždy na 1 - 2 řádky).
Vytvořit třídu `CDoor` se ale vyplatí, protože její implementace bude delší a nebylo by přehledné ji mít v lambda funkci. 
