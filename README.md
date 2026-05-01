# Viktorīnas programma
Vienkārša, C++ valodā rakstīta viktorīnas lietotne, kas nodrošina pilnu satura personalizāciju, nolasot jautājumus no strukturēta JSON faila un tematisko bildi arī no diska.

# Būvēšana
Lai pareizi uzbūvētu lietotni ir nepieciešams CMake projekta pārvaldībai un būvēšanas automatizācijai, Conan 2.0 priekš pakotņu pārvaldības.

Šīs instrukcijas ir domātas priekš Linux (ArchLinux) operētājsistēmas.
1. Instalē lietotnes nepieciešamās atkarības, šis solis arī izveidos **build** direktoriju ja tā vēl neeksistē: `conan install . --output-folder=build --build=missing`
2. Konfigurē projektu. Pārliecinies ka esi **build** direktorijā: `cd build`, `cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release`
3. Uzbūvē lietotni: `make`
