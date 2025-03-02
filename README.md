# Progetto Pac-Man per Scheda LandTiger

Questo repository contiene l'implementazione del gioco Pac-Man per la scheda LandTiger, sviluppato come parte del corso **"Architetture dei Sistemi di Elaborazione"**.

⚠️ **Avviso**: Questo progetto è stato sviluppato **esclusivamente a scopo didattico** e **non deve essere utilizzato come template per l'esame**. Sono presenti alcune **modifiche nelle librerie utilizzate**.

## Panoramica del Progetto

Il progetto implementa un gioco Pac-Man sulla scheda LandTiger, con le seguenti caratteristiche:

- Un labirinto con pillole da raccogliere
- Tracciamento del punteggio
- Fantasma controllato da IA
- Effetti sonori
- Comunicazione CAN

## Requisiti del Progetto

### Specifiche Extra Points #1

#### Labirinto e Pillole:

- Il labirinto deve contenere esattamente 240 Pillole Standard.
- 6 Pillole Potenti posizionate in posizioni casuali che sostituiscono le Pillole Standard.
- Le Pillole Potenti appaiono casualmente sia per posizione che per tempo.

#### Movimento del Giocatore:

- Controllo di Pac-Man tramite joystick (sinistra, destra, su, giù).
- Pac-Man continua a muoversi nella direzione selezionata finché:
  - Il giocatore seleziona una nuova direzione.
  - Pac-Man incontra un muro (si ferma e attende l'input).

#### Teletrasporto:

- Quando Pac-Man raggiunge le posizioni centrali di teletrasporto, esce da un lato e rientra dall'altro.
- La direzione del movimento viene mantenuta durante il teletrasporto.

#### Sistema di Punteggio:

- Pillole Standard: +10 punti.
- Pillole Potenti: +50 punti.
- Ogni 1000 punti assegna una vita extra (partendo con 1 vita).

#### Controlli di Gioco:

- **INT0**: Pausa/Ripresa del gioco. In pausa, appare un messaggio "PAUSA" al centro dello schermo.
- Il gioco inizia in modalità "PAUSA".

#### Timer di Gioco e Condizioni di Fine:

- Il conto alla rovescia parte da 60 secondi.
- La schermata di vittoria appare quando tutte le pillole sono raccolte.
- La schermata **Game Over** appare se il timer del conto alla rovescia raggiunge 0.

### Specifiche Extra Points #2

#### Fantasma Controllato da IA (Blinky):

- Implementa due strategie di IA:
  - **Modalità Inseguimento**: Insegue attivamente Pac-Man utilizzando algoritmi di pathfinding (algoritmo A*).
  - **Modalità Spaventata**: Attivata quando Pac-Man mangia una Pillola Potente.
    - Il fantasma diventa blu per 10 secondi, fugge da Pac-Man e può essere mangiato da Pac-Man per ulteriori 100 punti.
    - Riappare dopo 3 secondi nel punto di spawn centrale.

#### Effetti Sonori:

- Speaker configurato per riprodurre effetti sonori e musica di sottofondo.

#### Comunicazione CAN:

- Utilizza la periferica CAN per trasmettere lo stato del gioco.
- Implementata in modalità "loopback" esterna utilizzando CAN1 (trasmettitore) e CAN2 (ricevitore).
- **Formato del messaggio** (32-bit unsigned int): 
  - Copy | Tempo rimanente (8 bit) | Vite rimanenti (8 bit) | Punteggio (16 bit)

## Requisiti Hardware

- Scheda LandTiger con microcontrollore LPC1768.
- Display per mostrare il labirinto e lo stato del gioco.
- Joystick per controllare Pac-Man.
- Speaker per effetti sonori.
- Pulsante INT0 per la funzionalità di pausa.


