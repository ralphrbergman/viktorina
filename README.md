# Viktorīnas programma
Vienkārša, C++ valodā rakstīta viktorīnas lietotne, kas nodrošina pilnu satura personalizāciju, nolasot jautājumus no strukturēta JSON faila un tematisko bildi arī no diska.

## Būvēšana
Lai pareizi uzbūvētu lietotni ir nepieciešams CMake projekta pārvaldībai un būvēšanas automatizācijai, Conan 2.0 priekš pakotņu pārvaldības.

Šīs instrukcijas ir domātas priekš Linux (ArchLinux) operētājsistēmas.

Ir divi veidi kā tu vari būvēt lietotni (abiem ir viens un tas pats rezultāts)
* Automātiskais ceļš:
    1. Pārliecinies ka **build.sh** failam ir palaišanas tiesības: `chmod +x build.sh`
    2. Palaid: `./build.sh`
* Manuālais ceļš:
    1. Instalē lietotnes nepieciešamās atkarības, šis solis arī izveidos **build** direktoriju ja tā vēl neeksistē: `conan install . --output-folder=build --build=missing`
    2. Konfigurē projektu. Pārliecinies ka esi **build** direktorijā: `cd build`, `cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release`
    3. Uzbūvē lietotni: `cmake --build . -- -j$(nproc)`

## Lietošana
Lai viktorīnu varētu lietot ir nepieciešams **jautajumi.json** fails mapē kurā atrodas lietotne.
Šis fails ir obligāti jāsatur sekojoša shēma lai strādātu:
```json
{
    "nosaukums": "Mana viktorīna",
    "jautajumi":
    [
        {
            "jautajums": "Kas ir Latvijas galvaspilsēta?",
            "atbilde": "Rīga",
            "varianti": ["Rīga", "Jelgava", "Rēzekne"]
        }
    ]
}
```
Katram atbilžu variantu sarakstei ir jāsatur tikai trīs elementi, vienam no tiem
ir jābūt tieši tādā pašā burtu izmērā kā `atbilde` vērtībā.
Visām vērtībām ir obligāti jābūt pēdiņās!!

Kad **jautajumi.json** fails ir uztaisīts varat uzbūvēt lietotni sekojot [instrukcijām šeit](#būvēšana) un kad esat uzbūvējis, varat mierīgi palaist lietotnes bināro failu.

