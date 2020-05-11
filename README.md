# JsonParser

# Opis
Projekt zrealizowany w <b>C++ BuilderXE6</b>. Baza danych to <b>PostgreSQL</b>. Do komunikacji między programem a bazą danych użyta została biblioteka <b>FireDAC</b>.

Zadaniem programu jest analiza Jsona(odpowiedzi) wygenerowanego przez publiczne api (https://api-v3.mojepanstwo.pl/dane/krs_podmioty/  <b>+KrsId+</b> .json?layers[]=dzialalnosci&layers[]=firmy&layers[]=reprezentacja&layers[]=graph&layers[]=oddzialy). 
- Uporządkowanie danych do specjalnie przygotowanych kontenerów (klasy dziedziczące oraz templatki w pliku <b>uJbDetails.h</b>)
- Plik <b>uJbDetailsManager.h/cpp</b> odpowiada za zapis/odczyt z bazy.
- Natomiast parsowanie danych otrzymanych z serwera odbywa się w pliku <b>uJsonParser.h/cpp</b>.

Screeny z działania programu (jako przykład bank Ing i Millenium)
![alt text](https://i.ibb.co/9VsLHW2/jsonparserimg1.png)
![alt text](https://i.ibb.co/y06mZ63/jsonparserimg2.png)
