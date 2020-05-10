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
Pravidla hry se budou inpirovat původní hrou, ale nebude se jednat o přímou kopii.
Úkolem hráče je projít všechny levely co nejrychleji (a v daném časovém limitu) a získat přitom co nejvíce bodů (například zabitím příšer). Hráč má omezený počet životů.
Během hry může sbírat bonusy, které mu odemknou různé výhody (např. odpalování bomb na dálku, více životů...). Některé bonusy také mohou být jen dočasné.
Jednotlivé herní levely budou čteny ze souborů, které budou obsahovat všechny informace o daném levelu (generované bonusy, spawnované příšery...) 
Pro celou hru bude jedna mapa, která se skládá z nezničitelných zdí. Ta bude načítána ze souboru. Zničitelné zdi budou generovány náhodně.

Hru bude možné hrát ve dvou (třech) režimech:
   1. Singleplayer: Hráč bude klasicky hrát sám za sebe a bude hrát jen proti počítačem řízeným nepřátelům.
   2. Multiplayer: U jednoho počítače budou 2 hráči. Cílem této hry je zabít toho druhého, nebo za celou hru (za všechny levely) nasbírat více bodů než soupeř.
   3. Debug: Tento režim je pouze pro vývojáře a z hotové hry by byl odstraněn. Slouží k usnadnění testování hry. Debug režim se zpřístupní spuštěním hry s přepínačem `-debug`.



###Ovládání
V případě singleplayer hry bude ovládání následující: Pohyb (WASD), Položení bomby (X) a Odpálení bomby (C).

Pro multiplayer hru bude ovládání prvního hráče stejné jako pro singleplayer. 
Druhý hráč bude mít ovládání následující: Pohyb (IJKL), Položení bomby (N) a Odpálení bomby (M).


### Kde mám polymorfismus?
Polymorfismus používám u abstraktní třídy `CEnemy`, která má abstraktní metody `Update()` a `TryKill()`. Implementace `CEnemyDump` a `CEnemySmart` budou tyto metody přetěžovat. Z názvu vyplývá, že hlavní rozdíly budou chování a výdrži jednotlivých implementací. 
Polymorfní volání je ve třídě `CBoard`, kde mám instnace tříd `CEnemyDump` a `CEnemySmart` uložené v poli a pro každý snímek na nich volám metodu `Update()`, která zaktualizuje vnitřní stav daného objektu. 
Při kolizi `CEnemy` s objektem typu `CFire` dojde k zavolání metody `TryKill()`, která se pokusí příšeru zabít.

Polymorfismus také využívám u třídy `CBoost`, která má virtuální metody `Update()` a `Apply()`. Podtřída `CLimitedBoost` tyto metody přetěžuje.
Rozdíl je v tom, že základní metoda aplikuje boost na hráče a objekt je poté zničen. Přetížená metoda jen aplikuje boost a objekt je zničen až po nastaveném čase (časově omezený boost, který je po uplynutí časového limitu hráči odebrán.) 
Odpočet bude realizován v přetížené metodě `Update()`.
Polymorfní volání mám ve třídě `CPlayer`, která zavolá metodu `Apply()` na objektu typu `CBoost`, pokud je s nějakým v kolizi.
