# Analiza projektu szachowego (C++ / SFML / GoogleTest)

> Data analizy: 2026-05-21
> Zakres: projekt `Chess.sln` (Chess + ChessExe + Sample-Test1)

---

## Spis treści

1. [Stan obecny — co projekt już potrafi](#1-stan-obecny--co-projekt-już-potrafi)
2. [Błędy funkcjonalne](#2-błędy-funkcjonalne-od-krytycznych-do-drobnych)
3. [Ocena architektury](#3-ocena-architektury--czy-potrzebny-duży-refaktor)
4. [Integracja AI — propozycja rozwiązania](#4-integracja-ai--propozycja-rozwiązania)
5. [Backlog rozwojowy na miesiąc](#5-backlog-rozwojowy-na-miesiąc)
6. [Podsumowanie](#podsumowanie-odpowiedzi-na-pytania)

---

## 1. Stan obecny — co projekt już potrafi

**Architektura ogólna:** klasyczna gra hot-seat 2 graczy. `ChessExe/Source.cpp:13` montuje `Game` z `Board`, `Window`, `Mouse` i dwoma `Player`. Zależności wstrzykiwane przez `unique_ptr`, interfejsy w `include/interface/*`, są moki w `Sample-Test1/*Mock.h`.

### Co działa (lub powinno)

- Pełna inicjalizacja planszy 8×8 i 32 figur z teksturami SFML (`Board::CreateWhite/CreateBlack`).
- Wybór figury przez klik / drag-and-drop z animacją (`Board::Animate`, `Gameplay::TryMoveAndSetCurrentFigure`).
- Generowanie ruchów dla wszystkich figur: pion, skoczek, goniec, wieża, hetman, król (`figures/*.cpp`).
- Detekcja kolizji z własnymi i przeciwnika figurami (`Figure::IsCollisionWithCurrentPlayer/Opponent`).
- Bicia (`TakingMoveExecutor`), podświetlenia możliwych ruchów (`Cell::Highlight/HighlightAsTaking`).
- Wykrywanie szacha i sprawdzanie czy ruch nie odsłania własnego króla (`Board::RemoveForbiddenMoves`, `Player::IsKingUnderAttack`).
- Wykrywanie końca gry: `Player::IsAnyMovePossible` zwraca `false` → `Gameplay::Update` zwraca `false` → przejście do `GameState::menu`.
- Szkielet testów jednostkowych (gtest + gmock) z mokami dla wszystkich interfejsów. Workflow MSBuild w GitHub Actions.

### Czego nie ma (luki funkcjonalne)

- **Roszada** — `CastleMoveExecutor::Execute` to pusta funkcja (`IMoveExecutor.cpp:55-58`); `Board::IsShortCastlePossible` jest niedokończona, `IsLongCastlePossible` zwraca tylko `false`.
- **Promocja piona** — `Pawn::IsPromotion` jest zdefiniowana, ale **nigdy nie wywoływana**.
- **Bicie w przelocie (en passant)** — brak.
- **Reguła 50 ruchów / trzykrotne powtórzenie / pat** — `Player::IsAnyMovePossible` wykrywa tylko mat (komentarz `// to do: case dla remisu` w `Player.cpp:103`).
- **Menu, ekran końca gry, restart** — `GameState::menu` istnieje, ale jego `case` jest pusty; po pierwszym końcu gry okno zastyga.
- **Notacja PGN/FEN, historia ruchów, undo** — brak.
- **Zegar szachowy** — brak.
- **AI / przeciwnik komputerowy** — brak (sedno tego raportu, sekcja 4).

---

## 2. Błędy funkcjonalne (od krytycznych do drobnych)

### Krytyczne (UB / błędna logika gry)

1. **UB w `Board::IsShortCastlePossible`** — `Board.cpp:75-85`: brak `return` w przypadku gdy król nie jest atakowany (funkcja kończy się bez wartości). Wywołanie w obecnej formie to undefined behavior. Na szczęście nikt jej jeszcze nie wywołuje.
2. **Sprawdzenie pola pośredniego w ruchu piona o 2 — zły indeks** — `Pawn.cpp:38-44`:
   ```cpp
   if (IsCollisionWithOpponent({moveCell, Pos(moveCell.x, moveCell.y + dir)}, ...))
   ```
   Pole pośrednie to `moveCell.y - dir`, nie `+ dir`. Dla białego piona ruszającego z `y=6` do `y=4`: sprawdza pole `y=3` (już za polem docelowym) zamiast `y=5`. Dodatkowo **w ogóle nie sprawdza, czy pole pośrednie nie jest zajęte przez własną figurę** — pion może „przeskakiwać" własne bierki.
3. **Brak `break` w switchu stanu gry** — `Game.cpp:31-37`: fall-through z `case playing` do `case menu`. Dziś nieszkodliwe (menu nic nie robi), ale typowy bug-magnet po dopisaniu logiki.
4. **`Cell::Cell()` ze statycznym licznikiem nigdy nie resetuje** — `Cell.cpp:10-12`: `static int pos = 0; m_pos = pos++;` — po restarcie partii (gdy go zaimplementujesz) komórki dostają indeksy > 64. Ukryty bug, który ugryzie po dodaniu „new game".
5. **`Figure::operator==` porównuje po `m_startingPos`** — `Figure.cpp:216-219`. Definiuje free function `operator==(shared_ptr<IFigure>, shared_ptr<IFigure>)`, co przeciąża domyślne porównanie `shared_ptr` używane przez `std::find`. Subtelne: po promocji piona (gdy ją zrobisz) nowa figura miałaby tę samą pozycję startową co istniejące i `Clone`/`find` by się posypały. Dereference bez null-checka też.
6. **Texture loading z hardcodowanymi ścieżkami względnymi** — `Gameplay.cpp:106-119` `..\\Chess\\textures\\...`. Działa tylko gdy uruchomisz z konkretnego CWD (Visual Studio default), z poziomu `.exe` w innym katalogu — wyjątek `failed to load textures`.

### Średnie (logika ruchów / UX)

7. **`Player::TryChangeCurrentFigure` używa `sf::Mouse::isButtonPressed` bezpośrednio** — `Player.cpp:45`, łamie abstrakcję `IMouse` (cała reszta klasy używa interfejsów). Sama funkcja w ogóle nie jest wołana z `Gameplay`, czyli jest martwa, ale wprowadza twardą zależność od SFML do `Player`.
8. **`Gameplay::TryMoveAndSetCurrentFigure` ma podwójną logikę ruchu** — `Gameplay.cpp:55-82`: ten sam `Move()` jest wywoływany w gałęzi "click" i w gałęzi "drop". Działa, ale rozjeżdża się przy edge-cases (np. click-without-drag na puste pole po wykonanym ruchu).
9. **`Board::GetCurrentKing` zwraca król bez sprawdzenia, czy `m_whiteKing/m_blackKing` są ustawione** — przy edge-case'ach uruchamiania może segfaultować.
10. **`m_takingMoves` jest filtrowane po `x`** — `Board.cpp:110`: `find_if(... return takingMove.x == moveDestinationPos.x ...)`. Powinno być `== moveDestinationPos` (Pos), inaczej źle podświetla pola na tej samej kolumnie.
11. **`Gameplay::Update`** — gdy zwraca `false` (mat), `Game::Update` wpada do `GameState::menu`, gdzie nic się nie dzieje — gra zamarza zamiast pokazać końcówkę.
12. **`Game::Update` zatrzymuje pollowanie eventów gdy mysz poza oknem** — `Game.cpp:25`: cały blok `if (m_mouse->IsMouseInWindow)` zawiera też `Events()`. Klik na "X" gdy mysz poza obszarem rysowania nie zostanie obsłużony. Naprawa: `Events()` poza ifem.

### Drobne (kod, ale nie psuje gry)

13. **Duplikaty plików** — `include/Bishop.h` / `Knight.h` / `Rook.h` (puste klasy-stuby) vs `include/figures/*` (właściwe). To samo w `source/`. Mylące, śmieci po historii projektu.
14. **`Gameplay.h` deklaruje `Resolution`-using w `Game.h`** — brak hermetyzacji.
15. **`#pragma once` zamiast inkluzji warunkowych**, mieszanie konwencji ścieżek (`interface/IMouse.h` vs `interface\IMouse.h` w `Mouse.h:2`).
16. **`Color::Color()` defaultuje do (0,0,0)** — niewidoczne figury przy zapomnianym `SetFillColor`.
17. **`Player.cpp:47`** — iteracja po wartości `shared_ptr` (`for (auto el : m_figures)`) zamiast `const auto&`. Niewielki overhead.
18. **Test `TEST_F(BoardTest, jjjj)`** — nazwa zaśmiecona w `test.cpp:200`.

---

## 3. Ocena architektury — czy potrzebny duży refaktor?

**Mocne strony:** czysty DI, interfejsy + moki, Move Executor jako Strategy. To dobrze.

**Słabe strony — czerwone flagi z perspektywy dodawania AI i nowych reguł:**

| Problem | Konsekwencja dla rozwoju |
|---|---|
| Brak czystego, niegraficznego modelu pozycji (`Board` trzyma `Cells` z `RectangleShape`, `IFigure` zawiera `m_figureShape`) | AI musiałoby symulować rysowane figury, żeby ocenić ruch. **Killer dla wszystkiego co wymaga search/eval.** |
| Symulowanie ruchu przez `Clone()` na każdej figurze przy każdej walidacji ruchu (`Board::RemoveForbiddenMoves`) — klonuje cały wektor + każdą figurę z `shared_ptr` | O(n²) per legal move check. Dla AI z głębią 3 to katastrofa. |
| `IPlayer` mieszany z UI (`TryChangeCurrentFigure(mousePos)`) | Trudno wstawić "gracza" który nie ma myszy. **Bezpośrednia blokada wstrzyknięcia AI jako Player.** |
| `Figure::operator==` porównuje pozycję startową | Symulacja zmienia identyfikację figury — niespodzianki przy promocji. |
| Brak generatora ruchów w formie czystych danych (`Move {from,to,promotion,flag}`) — wszystko żyje w `IMoveExecutor` z efektami ubocznymi (zmienia `Board`) | AI nie ma "ruch jako dane" — nie może przeglądać drzewa. |
| Stan gry rozproszony: `Board` ma `m_selectedFigureCell`, `m_takingMoves`, `m_mousePosInFigure`; `Figure` ma `m_possibleMoves`, `m_moveCounter`; `Player` ma `m_currentFigure` | Brak jednej snapshotowalnej reprezentacji pozycji. |
| Brak FEN/PGN | Nie zapiszesz partii, nie zainicjalizujesz dowolnej pozycji do testów. |

**Werdykt:** TAK, potrzebny średni refaktor (nie wielki big-bang, ale wyraźna restrukturyzacja). **Kluczowy punkt:** oddzielić **model szachowy** (czysty C++, bez SFML) od **warstwy widoku** (SFML, animacje, mysz). To otwiera drzwi do:

- AI,
- testów regresji bez mocków graficznych,
- zapisu/odczytu partii,
- silnika UCI w przyszłości.

---

## 4. Integracja AI — propozycja rozwiązania

### Wybór silnika

Trzy realistyczne ścieżki:

| Opcja | Plus | Minus |
|---|---|---|
| **A. Stockfish przez UCI (subprocess)** | Najsilniejszy ruch dosłownie za darmo, otwarta licencja GPL, gotowa biblioteka | Wymóg dystrybucji binarki, integracja IPC |
| **B. Własny minimax + alpha-beta + ocena materiału** | Pełna kontrola, edukacyjne, niska zależność | Słaba siła gry, sporo kodu |
| **C. Lc0/inny silnik UCI** | Silne, NN-based | Cięższe niż Stockfish |

**Rekomendacja: hybryda — najpierw B (własny minimax na głębokość 3-4) jako MVP, potem A (Stockfish UCI) jako opcja w UI.** Własny silnik wymusi czysty model szachowy, który i tak jest potrzebny.

### Plan rozwiązania (warstwa po warstwie)

#### Krok 1 — czysty model pozycji (nowy, niegraficzny)

```cpp
// nowy plik: include/model/Position.h
struct Move {
    Pos from, to;
    enum class Flag { Normal, Capture, PawnDouble, EnPassant, ShortCastle, LongCastle, Promotion } flag;
    PieceType promoteTo = PieceType::None;
};

class Position {
public:
    void ApplyMove(const Move&);
    void UndoMove(const Move&);
    std::vector<Move> GenerateLegalMoves(PlayerColor) const;
    bool IsCheck(PlayerColor) const;
    bool IsCheckmate(PlayerColor) const;
    PieceType PieceAt(Pos) const;
    // FEN/Zobrist hash:
    std::string ToFEN() const;
    static Position FromFEN(const std::string&);
    uint64_t ZobristHash() const;
private:
    std::array<std::array<Piece, 8>, 8> m_squares;  // czysta tablica, BEZ tekstury
    PlayerColor m_sideToMove;
    CastlingRights m_castling;
    std::optional<Pos> m_enPassant;
    int m_halfmoveClock, m_fullmoveNumber;
};
```

#### Krok 2 — IPlayer staje się czysto strategiczny

```cpp
// modyfikacja: include/interface/IPlayer.h
class IPlayer {
public:
    virtual Move RequestMove(const Position& currentPosition) = 0;   // <- NOWE
    // usuń: TryChangeCurrentFigure (przenieś do HumanPlayer i wywołuj z Gameplay tylko gdy aktywny)
    ...
};
```

#### Krok 3 — dwie implementacje IPlayer

```cpp
// include/HumanPlayer.h
class HumanPlayer : public IPlayer {
    Move RequestMove(const Position&) override;  // czeka na input z mouse/Gameplay
private:
    std::optional<Move> m_pendingMove;
    // ustawiany przez Gameplay::OnUserClick(from, to)
public:
    void SubmitUserMove(const Move&);
};

// include/AiPlayer.h
class AiPlayer : public IPlayer {
public:
    AiPlayer(int depth, std::unique_ptr<IChessEngine> engine);
    Move RequestMove(const Position&) override;  // synchronicznie lub na wątku
private:
    std::unique_ptr<IChessEngine> m_engine;
    int m_depth;
};

// include/interface/IChessEngine.h
class IChessEngine {
public:
    virtual Move FindBestMove(const Position& pos, int depthOrTimeMs) = 0;
};

// dwie implementacje:
// - MinimaxEngine (własny, alpha-beta + simple eval material+PST)
// - StockfishEngine (subprocess + UCI: pisze "position fen ... go depth N", parsuje "bestmove")
```

#### Krok 4 — Gameplay korzysta z modelu, nie z `IBoard` jako prawdy

```cpp
class Gameplay {
    Position m_position;          // ŹRÓDŁO PRAWDY
    IBoardPtr m_boardView;        // tylko widok — synchronizowany z m_position
    IPlayerPtr m_white, m_black;

    bool Update(IWindowPtr&, IMousePtr&) {
        IPlayer& current = (m_position.SideToMove() == PlayerColor::white) ? *m_white : *m_black;
        if (auto move = current.RequestMove(m_position)) {   // dla AI: blokująca; dla human: jeśli czeka
            m_position.ApplyMove(*move);
            m_boardView->SyncFrom(m_position);               // przepisuje stan na widok SFML
        }
        m_boardView->Draw(window);
        return !m_position.IsGameOver();
    }
};
```

#### Krok 5 — wybór trybu z linii poleceń lub menu

```cpp
// ChessExe/Source.cpp
int main(int argc, char** argv) {
    GameMode mode = ParseArgs(argc, argv);   // PvP | PvAI | AIvAI
    auto white = MakePlayer(mode.white);     // HumanPlayer lub AiPlayer(MinimaxEngine|StockfishEngine)
    auto black = MakePlayer(mode.black);
    ...
}
```

### Miejsca w kodzie wymagające modyfikacji (konkretnie)

| Plik | Co zmienić |
|---|---|
| `include/interface/IPlayer.h`, `source/Player.cpp` | usuń `TryChangeCurrentFigure(mousePos)`, dodaj `RequestMove(const Position&)` lub równoważny callback |
| `include/Gameplay.h:21-41`, `source/Gameplay.cpp:55-82` | wyodrębnij logikę "kto ma teraz wybrać ruch" — zamiast `if (mouse->...)` zapytaj aktualnego gracza |
| `include/interface/IBoard.h`, `source/Board.cpp` | dodaj metodę `SyncFrom(const Position&)` (renderuje stan modelu) i `Position SnapshotPosition() const`; docelowo `IBoard` powinien być view-only |
| `include/figures/Figure.h` + wszystkie figury | usuń `m_figureShape` z modelu logicznego — przenieś rendering do osobnej klasy `FigureView`; figury w `Position` mogą być POD-em (enum + flagi) |
| `include/IMoveExecutor.h` | zostaje, ale jako *adapter* między `Move` (data) a operacją na `Position` i na `Board` view |
| Nowe pliki: `include/model/Position.h`, `include/model/Move.h`, `include/ai/IChessEngine.h`, `include/ai/MinimaxEngine.h`, `include/ai/StockfishEngine.h`, `include/HumanPlayer.h`, `include/AiPlayer.h` | implementacja modelu + AI |
| `Sample-Test1/test.cpp` | testy generowania ruchów (perft do głębokości 3-4 dla pozycji startowej — sprawdzony benchmark poprawności) |
| `ChessExe/Source.cpp` | parser argumentów + fabryka graczy |
| `Chess.sln` / `Chess.vcxproj` | nowe pliki w projekcie |

### Minimalne wymagania funkcjonalne **przed** AI

AI bez tego = lista zła:

- Pełna legalność: roszada (długa i krótka), promocja, en passant, pat → bez tego silnik wybiera ruchy ilegalne.
- Szybkie wykonywanie/cofanie ruchu na modelu (`ApplyMove`/`UndoMove`).
- Generator ruchów zwracający czyste `Move` (data), nie strategie z side-effectami.

---

## 5. Backlog rozwojowy na miesiąc

Założenie: 1 dev, ~4 tygodnie. Tygodnie liczone od **2026-05-21**.

### Tydzień 1 (21–27 maja) — fundament: bug-fixy + porządki

| ID | Zadanie | Czas |
|---|---|---|
| **B-1** | Fix `Pawn.cpp:38-44` — pole pośrednie ruchu o 2 (zły indeks, brak sprawdzenia własnych figur) | 2h |
| **B-2** | Fix `Board::IsShortCastlePossible` (UB - brak `return`) + decyzja: usunąć lub zaimplementować razem z resztą roszady w T2 | 1h |
| **B-3** | Fix `Cell::Cell` statyczny licznik → konstruktor z indeksem przekazanym z `CreateCells` | 1h |
| **B-4** | Fix Gameplay textures: ładuj ścieżki względem `argv[0]` lub `executable path`, nie CWD | 2h |
| **B-5** | Fix `Game::Update` — wyciągnij `Events()` poza `if (mouse in window)` | 0.5h |
| **B-6** | Usuń puste duplikaty `include/Bishop.h`, `Knight.h`, `Rook.h` + ich `.cpp` z projektu | 0.5h |
| **B-7** | Fix `Board::HighlightMoves` (Board.cpp:110) — porównuj cały `Pos`, nie tylko `x` | 0.5h |
| **B-8** | Dopisz testy regresji (perft głębokości 1 i 2 dla pozycji startowej — oczekiwane 20 i 400 ruchów) | 4h |
| **B-9** | Zmień nazwę `TEST_F(BoardTest, jjjj)` na sensowną i wypełnij | 1h |

### Tydzień 2 (28 maja – 3 czerwca) — model szachowy + brakujące reguły

| ID | Zadanie | Czas |
|---|---|---|
| **F-1** | Wprowadź czysty `Position`/`Move` (sekcja 4 krok 1) | 8h |
| **F-2** | Generator legalnych ruchów (zastąpić istniejący przepływ `Figure::CalculatePossibleMoves`) | 8h |
| **F-3** | Implementacja **promocji piona** (UI z wyborem figury + logika) | 4h |
| **F-4** | Implementacja **roszady** (krótka i długa, z testem czy król nie przechodzi przez szachowane pole) | 6h |
| **F-5** | Implementacja **en passant** | 3h |
| **F-6** | Detekcja **pata** i remisu (50 ruchów, 3× powtórzenie z Zobrist hash) | 5h |
| **F-7** | Perft testy do głębokości 4 dla pozycji startowej (197 281 + wariant Kiwipete jako standard) | 3h |

### Tydzień 3 (4–10 czerwca) — separacja modelu od widoku + AI MVP

| ID | Zadanie | Czas |
|---|---|---|
| **R-1** | Refaktor: `IBoard` staje się widokiem, `Position` źródłem prawdy. `Gameplay` operuje na `Position` | 8h |
| **R-2** | Refaktor `IPlayer` → `RequestMove(const Position&)`. `HumanPlayer` + `AiPlayer` | 4h |
| **AI-1** | `IChessEngine` interface | 1h |
| **AI-2** | `MinimaxEngine`: alpha-beta, ewaluacja material + PST (Piece-Square Tables) + mobility. Głębokość 3-4 | 10h |
| **AI-3** | UI: wybór trybu PvP/PvAI/AIvAI z argumentów linii poleceń + prosty menu screen | 4h |
| **AI-4** | Test integracyjny: gra AI vs AI dochodzi do końca bez crashy, w sensownym czasie | 3h |

### Tydzień 4 (11–17 czerwca) — Stockfish, jakość, polish

| ID | Zadanie | Czas |
|---|---|---|
| **AI-5** | `StockfishEngine` (subprocess + UCI): `position fen X`, `go movetime 1000`, parsowanie `bestmove` | 6h |
| **AI-6** | Wybór poziomu trudności (głębokość/czas) w menu | 3h |
| **U-1** | Ekran końca gry: kto wygrał, jak, przycisk Restart. Naprawić `GameState::menu` | 4h |
| **U-2** | Historia ruchów po prawej stronie planszy + eksport do PGN | 5h |
| **U-3** | Zegar szachowy (opcjonalny) | 3h |
| **Q-1** | Pokrycie testami kluczowych ścieżek (legalność, mat, pat, en passant) — cel 70% linii w `model/` | 4h |
| **Q-2** | GitHub Actions: dodać uruchomienie testów (obecny `msbuild.yml` tylko buduje) | 2h |

### Buffer / rezerwa

~10h na bug-fixy z review i nieprzewidziane.

---

## Podsumowanie odpowiedzi na pytania

1. **Co projekt potrafi:** podstawową grę 2 graczy hot-seat z legalnością ruchów, detekcją szacha i mata, drag-and-drop. Bez roszady, promocji, en passant, remisu, AI, restartu i zapisu partii.
2. **Krytyczne bugi:** UB w `IsShortCastlePossible`, zły indeks pola pośredniego w pionku, statyczny licznik w `Cell`, hardcoded ścieżki tekstur, fall-through w switchu, niedziałający restart po końcu gry.
3. **AI:** wstrzyknij jako drugą implementację `IPlayer` z metodą `RequestMove(Position&)`. Wcześniej **konieczny refaktor**: oddzielenie czystego modelu (`Position`/`Move`) od widoku SFML i dokończenie reguł (roszada, promocja, en passant). Bez tego AI generowałby ilegalne ruchy lub byłby bardzo wolny.
4. **Refaktor:** średni, nie wielki. Główne posunięcie: **model bez SFML** + **`IPlayer` bez myszy**. Resztę da się dobudować ewolucyjnie.
