#################################################

           IMPLEMENTIERUNG DES SIMPLEX-
                ALGORITHMUS IN C++
		
################### OPS WS2016 ##################
- - - - - - - - - - - Team 3  - - - - - - - - - -
 
 Mithilfe dieses Programmes soll es moeglich
 sein, Lineare Optimierungsprobleme mithilfe des
 Simplex-Algorithmus loesen zu koennen.
 
 -----------------------------------------------
 
 INSTALLATION
 auf dem Almighty-Server
 
  1. Lorem Ipsum dolor sit amet.
  2. Consectetur.
 
 -----------------------------------------------
 
 AUSFUEHRUNG
 
  - Um das Programm mit einem vorprogrammierten
    Beispiel auszuprobieren, genuegt der Befehl:
	    
		$ main
		
		
  - Eigene Optimierungsprobleme muessen in fol-
    gendem Schema als Textdateien gespeichert
    sein:
	
        n k
        x_1 x_2 . . . x_n
        a_1,1 a_1,2 . . . a_1,n b_1
        a_2,1 a_2,2 . . . a_2,n b_2
            .       .         .
            .         .       .
            .           .     .
        a_k,1 a_k,2 . . . a_k,n b_n
		
    Wobei n die Anzahl der Variablen beschreibt
    und k die Anzahl der Nebenbedingungen.
    Die x_j (j=1...n) stellen die Koeffizienten
    der Zielfunktion dar, die a_i,j (i=1...k, 
    j=1...n) sind die Koeffizienten der i-ten 
    Nebenbedingung und die b_j (j=1...n) stell-
    en die rechten Seiten der Nebenbedingung dar.
    Die einzelnen Elemente muessen durch ein Leer-
    zeichen (<Space>) getrennt werden und jede
    Nebenbedingung muss in einer neuen Zeile ge-
    schrieben sein.
	
    So wuerde eine beispielhafte Texdatei nach
    diesem Schema aussehen:
	
        2 3
        -3 -5
        1 0 4
        0 2 12
        3 2 18
	
    Danach kann das Problem wie folgt in dem
    Programm ausgefuehrt werden:
	
        $ main -f <path>
		
    wobei <path> durch den Dateipfad der Textda-
    tei zu ersetzen ist.
	
		
  - Drei Testbeispiele sind als Dateien ueber
    folgende relative Pfade erreichbar:
	
        testfiles/test.txt
        testfiles/test2.txt
        testfiles/test3.txt
 
#################################################