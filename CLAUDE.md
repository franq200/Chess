# Chess

Gra w szachy w C++, SFML do grafiki, GoogleTest do testów i mocki

## Zasady
- Nie zmieniaj więcej niż wymaga zadanie obecne
- SFML wolno używać tylko w: Window, Mouse, RectangleShape, Texture.
  Istniejące użycia w innych miejscach zostawiamy, dopóki nie dostaniesz zadania, żeby je usunąć.
- Nie commituj sam
- Jeśli polecenie jest niejednoznaczne pytaj zamiast zgadywać
- Po skończeniu zadania napisz krótko: które pliki zmieniłeś i dlaczego.


## Budowanie i Testy
- Build: "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" Chess.sln /p:Configuration=Debug /p:Platform=x64
- Testy: .\x64\Debug\Sample-Test1.exe
- Po każdej zmianie zbuduj projekt i uruchom testy

## Log błędów
- Ścieżka: ai-log.md
- Dodajesz wpis tylko jeśli ci powiem
- Każdy wpis ma mieć datę, feature przy którym się pojawił, model AI który był używany, krótki opis błędu, Kategoria, Jak został wyłapany, Co zostało zmienione aby uniknąć podobnych błędów w przyszłości