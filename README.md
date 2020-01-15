# JsonParser
Projekt zaliczeniowy na przedmiot "Systemy kontroli błędów i wersji" WSB semestr V, rok 2019/2020. Grupa INIS_PR 3.2

# Opis
Projekt zrealizowany w <b>C++ BuilderXE6</b>. Baza danych to <b>PostgreSQL</b>. Do komunikacji między programem a bazą danych użyta została biblioteka <b>FireDAC</b>.

Zadaniem programu jest analiza Jsona(odpowiedzi) wygenerowanego przez publiczne api (https://api-v3.mojepanstwo.pl/dane/krs_podmioty/  <b>+KrsId+</b> .json?layers[]=dzialalnosci&layers[]=firmy&layers[]=reprezentacja&layers[]=graph&layers[]=oddzialy). 
- Uporządkowanie danych do specjalnie przygotowanych kontenerów (klasy dziedziczące oraz templatki w pliku <b>uJbDetails.h</b>)
- Plik <b>uJbDetailsManager.h/cpp</b> odpowiada za zapis/odczyt z bazy.
- Natomiast parsowanie danych otrzymanych z serwera odbywa się w pliku <b>uJsonParser.h/cpp</b>.
