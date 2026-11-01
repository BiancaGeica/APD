Geica Elena-Bianca 333CC

Bonus: Demonstratia corectitudinii
Pentru a demonstra ca programul este corect, se compileaza atat programul paralel cat si cel secvential, apoi se ruleaza,
pentru acelasi numar de elemente N,iar outputul fiecarui program se pune in cate un fisier txt diferit si se face diff intre
cele doua. Acest lucru poate fi verificat folosind si scriptul test_strassen.sh (dupa ce se introduce comanda make).


Demonstrarea scalabilitatii inseamna ca sa demonstram ca programul paralelizat este mai eficient decat programul secvential.

Pentru a masura corect timpul, intai trebuie comentate toate afisarile din cele doua fisiere utilizate in demonstratie, deoarece
afisarile introduc un timp care poate fi semnificativ in masurare.
In plus, pastrez afisarile in caz de eroare deoarece acestea apar doar atunci cand se intampina o problema, deci nu influenteaza
timpul masurat deoarece atunci cand apare o eroare, masurarea este considerata irelevanta.

Pentru demonstratie s-au folosit N = 2000 si fisierele dem_seq.c si dem_parallel.c

Timpul programului secvential (time ./seq 2000 -> real): 0m43.107s

Timpul programului paralel pentru:
1) P = 1 -> time ./parallel -> real -> 0m40.963s
2) P = 2 -> time ./parallel -> real -> 0m23.649s
3) P = 3 -> time ./parallel -> real -> 0m19.459s
4) P = 4 -> time ./parallel -> real -> 0m13.232s

Speed-up-ul reprezinta de cate ori este mai rapid programul paralel fata de cel secvential si este egal cu
raportul dintre timpul programului secvential supra timpul programului paralel.
Speedup:
1) P = 1 -> S = timp_secv / timp_paralel -> S = 43.107 / 40.963 = 1.0523
2) P = 2 -> S = timp_secv / timp_paralel -> S = 43.107 / 23.649 = 1.8227
3) P = 3 -> S = timp_secv / timp_paralel -> S = 43.107 / 19.459 = 2.2152
4) P = 4 -> S = timp_secv / timp_paralel -> S = 43.107 / 13.232 = 3.2577

Eficienta este data de raportul dintre speed-up si numarul de Threaduri si reprezinta ce procent de timp din program a muncit un thread
Eficienta:
1) P = 1 -> E = S / P -> E = 1.0523 / 1 = 1.0523 (irelevant pentru ca se compara program secvential cu program secvential)
2) P = 2 -> E = S / P -> E = 1.8227 / 2 = 0.91135 (aprox 91% din timp)
3) P = 3 -> E = S / P -> E = 2.2152 / 3 = 0.7384
4) P = 4 -> E = S / P -> E = 3.2577 / 4 = 0.8144

Pentru a calcula rapid, am folosit instrumentul bc din bash:
echo "1.8227 / 2" | bc -l

se mai poate folosi si awk:
awk 'BEGIN { print 1.8227 / 2 }'
