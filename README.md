# Ogoras
Jest to silnik do gier.\
Wszystkie pliki czytane przez silnik znajdują się w katalogu **data/**.

# Proces uruchamiania
Przy uruchamianiu *Menu* ładowany jest plik **data/menuBackground.png**.\
Następnie po kliknięciu przycisku *start* ładowana jest grafika bloków dla klasy *Map* z **data/levels/blocks.png**.\
Z katalogu **data/lvl0** informacje są ładowane do klas *Map*, *Npc* i *Player*. Następnie ładowane jest tło z **data/levels/lvl0/map.png**.\
Po tym uruchamiana jest komenda **start main**. Na koniec ładowana jest grafika tła ze ścieżki **data/levels/lvl0/map.png**.\
Klasa *Map* ładuje z pliku **data/levels/lvl0/blocks.ini** informacje o właściwościach bloku. Następnie ładuje z **data/levels/levels/lvl0/map.lvl** układ bloków i informacje dla klasy *Npc*.\
Klasa *Npc* ładuje z pliku **data/levels/lvl0/Npc.ini** informacje o pozycji, kierunku patrzenia, ścieżkę do grafiki, podpis oraz wiadomość pokazywaną przy dotknięciu.\
Klasa *Player* ładuje z pliku **data/levels/lvl0/Player.ini** informacje o pozycji, kierunku patrzenia oraz ścieżkę do grafiki.

# Typy plików
Wszystkie grafiki muszą być w formacie .png

# Bloki
Każdy blok ma 128 pixeli na 128 pixeli.\
Plik **blocks.ini** informuje o grafice dla danego bloka, o jej zmianie oraz o zachowaniu przy interakcji z graczem.\
Plik **map.lvl** informuje o położeniu każdego bloku. Każda linia to jeden rząd bloków. Znakiem końca linii jest 0xff. Jest to blik binarny, do jego edycji niezbędny jest specjalny edytor.

# Skład pliku blocks.ini
blocks.ini	| Objaśnienie
:--			| :--
[BlockX]	| *X* to numer bloku
x			| pozycja x grafiki w pliku **data/blocks.png**
y			| pozycja y grafiki w pliku **data/blocks.png**
command		| komenda wykonywana przy dotknięciu
rotation X	| obrót grafiki o *X* stopni
solid		| informacja czy gracz może przejść przez blok (0 może, 1 nie może), domyślnie 1

## Przykład
[**Block**10]\
**x**=256\
**y**=128\
**command**=tp 3 4\
**rotation**=90\
**solid**=0

# Skład pliku Npc.ini
Npc.ini		| Objaśnienie
:---		| :---
[NpcX]		| *X* to numer npc
name		| podpis pojawiający się nad npc, domyślnie NULL
x			| pozycja x
y			| pozycja y
s			| kierunek patrzenia, może być U - do góry, D - do dołu, R - w prawo, L - w lewo
src 		| ścieżka do grafiki, ułożenie duszków to patrzący do góry, do dołu, w prawo i w lewo, domyślnie Npc*X*
command		| komenda wykonywana po dotknięciu

## Przykład
[**Npc**2]\
**name**=Darek2\
**s**=U\
**x**=4\
**y**=5\
**src**=data/characters/darek.png\
**command**=npc_say 2 500 Czesc!

# Skład pliku Player.ini
Player.ini	| Objaśnienie
:---		| :---
[Player]	|
x			| pozycja x gracza na początku
y			| pozycja y gracza na początku
s			| kierunek patrzenia, zobacz s w Npc.ini
src			| ścieżka do animacji (zobacz uwaga)

## Przyklad
[Player]
**x**=3\
**y**=5\
**s**=R\
**src**=data/characters/player.png\

## Uwaga
Animacja ma być w innym ułożeniu niż grafika npc, w pierwszej kolumnie mają być kolejne klatki animacji dla patrzenia w górę, w drugiej dla patrzenia do dołu, w trzeciej dla patrzenia w prawo, w czwartej dla patrzenia w prawo.\
Musi również istnieć plik *nazwa_pliku_z_animacją*.png.ini. W nim znajduje się informacja o okresie trwania jednej klatki w milisekundach.

### Przykład
[]\
**period**=*tu okres trwania jednej klatki*

# Komendy
Można je wprowadzić w konsoli (uruchamia się ją ~) lub w pliku *.scr.\
Działają dopiero po załadowaniu **data/levels/lvl0**

Komenda			| Działanie
:--- | :---
clear 			| wyczyść konsolę
load X 			| załaduj poziom *X* z katalogu **data/levels/**
start X			| uruchom interpretowanie pliku X.scr, będzie się to działo w innym wątku
stop			| usuń wszystkie wątki
threads			| podaj liczbę obecnie wykonywanych wątków
wait X 			| czekaj *X* milisekund
noclip 1 		| wyłącz kolizję
tp X Y			| teleportuj gracza do *X* *Y*
position		| wypisuje obecną pozycję gracza
say T M			| gracz powie *M* przez *T* milisekund
map_block X Y B	| ustaw blok o numerze *B* na pozycji *X* *Y*
npc_move N X Y	| przesuń npc o numerze *N* o *X* i o *Y*
npc_say	N T M	| npc o numerze *N* powie *M* przez *T* milisekund
npc_touch N		| zasymuluj dotknięcie npc o numerze *N*

# FAQ
## Jak dodać blok?
Należy dodać jego grafikę do **data/blocks.png**, następnie dodać informacje o nim do **data/levels/lvl*X*/blocks.ini**, a na koniec dodać go do **data/levels/lvl*X*/map.lvl** na wybrane pozycje.

## Jak dodać npc?
Należy dodać jego grafikę do **data/characters/**, następnie dodać informacje o nim do **data/levels/lvl*X*/Npc.ini**.
