C++ Programmeermethoden, Assignment 4
    by Tim Müller (11774606)


In deze map zijn de bestanden te vinden die samen de oplossing voor assignment
4 vormen.

De bestanden LargeNumber.cpp en LinkedList.cpp bevatten de implementatie van
LargeNumber. Deze zijn te vinden onder 'src/lib', met de header files onder
'src/lib/include'.

De andere bestanden zijn een herorganisatie van de originele SmallNumber.cpp
zodat ik ze zelf beter kan overzien en zodat de algemene structuur consistenter
is, maar de functionaliteit en headers zijn niet aangepast, en dus zou de
LargeNumber.cpp file moeten interfacen met het standaard bestand.

Om de files te compilen, zijn er twee opties. U kunt 'make main' gebruiken,
die een executable genereerd onder 'bin/main.out'. Standaard compiled dit met
de LargeNumber library, maar met 'make main SMALLNUMBER=1' kan de SmallNumber
worden gekozen. De andere optie is om met 'make tests' te compilen, die dan
automatisch een series aan tests uitvoert die de afzonderlijke onderdelen van
zowel de LinkedList als de LargeNumber class test. De source files van deze
tests zijn te vinden onder 'tests/test_linkedlist.cpp' en
'tests/test_largenumber.cpp' respectievelijk.

Nadat u de 'bin/main.out' executable heeft gemaakt, kunt u de functionaliteit
van de executable testen door './compare.sh' uit te voeren (deze moet mogelijk
eerst uitvoerbaar worden gemaakt met 'chmod +x ./compare.sh'). Deze zal een
bestand './output.txt' genereren, wat daarna vergeleken wordt door middel van
het Linux 'cmp'-commando om te kijken of de output hetzelfde is. Als het goed
is zult u zien dat dit wel zo is.

De assignment werkt en compiled op KDE Neon (Ubuntu 18.04.2) met GCC 7.5.0.
